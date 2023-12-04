#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// Struktura przechowuj¹ca informacje o obrazku PGM
struct ObrazekPGM {
    char nazwaPliku[100];
    int szerokosc;
    int wysokosc;
    int skalaSzarosci;
    int** piksele;
};

void wyswietlMenu(char* gwiazdki)
{
    printf("*********************************************************\n");
    printf("*                 PRZETWARZANIE OBRAZOW                 *\n");
    printf("*********************************************************\n");

    printf("\n                    MENU\n");
    printf("1. Wczytaj obraz z pliku                         [%c]\n", gwiazdki[0]);
    printf("2. Przetworz obraz                               [%c]\n", gwiazdki[1]);
    printf("3. Zapisz obraz do pliku                         [%c]\n", gwiazdki[2]);
    printf("4. Zakoncz program                               [%c]\n", gwiazdki[3]);
    printf("Wybierz opcje (1-4): ");
}

// Funkcja do odczytu danych z pliku PGM
void wczytajObrazek(struct ObrazekPGM* obrazek) {

    char nazwa[20];
    printf("Podaj nazwe pliku PGM do wczytania: ");
    scanf("%s", nazwa);

    char buf[0x26]; //to ma przyjac nazwe +PGM
    //do bufforu nastepuje przypisuje pamiec nazwa + 5 jednostek pamieci na .PGMEOF
    snprintf(buf, sizeof(nazwa) + 5, "%s.PGM", nazwa);
    FILE* plik = fopen(buf, "r");
    if (plik == NULL)
    {
        printf("\nBlad otwarcia pliku.\n");
        return;
    }
    char standard[3];
    fscanf(plik, "%s\n", standard);
    if (standard[0] != 'P' || standard[1] != '2')
    {
        printf("Niewlasciwy standard obrazu");
        fclose(plik);
        return;
    }

    strcpy(obrazek->nazwaPliku, buf);

    char linia[100];
    char* komentarz;
    while (fgets(linia, sizeof(linia), plik) != NULL) {
        if (!(linia[0] == '#' || linia[0] == '/' && linia[1] == '/'))
        {
            // strstr(linia, "//") == NULL) {
            break; // Jeœli linia nie jest komentarzem, przerywamy pêtlê
        }
    }
    if (sscanf(linia, "%d %d", &obrazek->szerokosc, &obrazek->wysokosc) != 2)
    {
        printf("Blad pliku PGM");
        return;
    };

    while (fgets(linia, sizeof(linia), plik) != NULL) {
        if (!(linia[0] == '#' || linia[0] == '/' && linia[1] == '/'))
        {
            // strstr(linia, "//") == NULL) {
            break; // Jeœli linia nie jest komentarzem, przerywamy pêtlê
        }
    }
    if (sscanf(linia, "%d", &obrazek->skalaSzarosci) != 1)
    {
        printf("Blad pliku PGM");
        return;
    };

    printf("Szerokosc: %d, Wysokosc: %d, Szarosc: %d\n", obrazek->szerokosc, obrazek->wysokosc, obrazek->skalaSzarosci);

    obrazek->piksele = (int**)malloc(obrazek->wysokosc * sizeof(int*));
    for (int i = 0; i < obrazek->wysokosc; i++) {
        while (fgets(linia, sizeof(linia), plik) != NULL) {
            if ((linia[0] == '#' || linia[0] == '/' && linia[1] == '/'))
            {
                continue; // Jeœli linia nie jest komentarzem, przerywamy pêtlê
            }
            int j = 0;
            obrazek->piksele[i] = (int*)malloc(obrazek->szerokosc * sizeof(int));
            char* ptr = linia; // Ustawienie wskaŸnika pomocniczego na pocz¹tku linii
            int index = 0;
            while (sscanf(ptr, "%d%n", &obrazek->piksele[i][j], &index) == 1) {
                printf("Odczyt[%d][%d]: %d\n", i, j, obrazek->piksele[i][j]);
                ptr += index;
                j++;
            }
        }

        //for (int j = 0; j < obrazek->szerokosc; j++) {          
        //    if (sscanf(linia, "%d", &obrazek->piksele[i][j]) != 1)
        //    {
        //        printf("Blad pliku PGM");
        //        return;
        //    }
        //    printf("Odczyt[%d][%d]: %d\n", i, j, obrazek->piksele[i][j]);
        //}
    }
}

int main() {

    struct ObrazekPGM wczytanyObrazek;
    char gwiazdki[] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
    char star = '*';
    char spacja = ' ';
    int wyborMenu = 0;

    do
    {
        wyswietlMenu(gwiazdki);
        while (scanf("%d", &wyborMenu) != 1)
        {
            printf("!!! BLAD !!!\nWybierz opcje (1-9): ");
            scanf("%*[^\n]");
        }

        switch (wyborMenu) {
        case 1:
            wczytajObrazek(&wczytanyObrazek);
            printf("Nazwa pliku: %s\n", wczytanyObrazek.nazwaPliku);
            printf("Szerokosc: %d\n", wczytanyObrazek.szerokosc);
            printf("Wysokosc: %d\n", wczytanyObrazek.wysokosc);
            printf("Skala szarosci: %d\n", wczytanyObrazek.skalaSzarosci);
            for (int i = 0; i < wczytanyObrazek.wysokosc; i++) {
                for (int j = 0; j < wczytanyObrazek.szerokosc; j++) {
                    printf("XXXXXXXXX\n");

                printf("Odczyt[%d][%d]: %d\n", i, j, wczytanyObrazek.piksele[i][j]);
                }
                printf("\n");
            }
            break;
        case 2:
            //przetworzenieObrazu(gwiazdki, wyborMenu);
            break;
        case 3:
            //menuZapisDoPliku();
            break;
        case 4:
            printf("Program zostal zakonczony.\n");
            break;
        default:
            printf("Nieprawidlowy wybor. Wybierz opcje od 1 do 4.\n");
            break;
        }
    } while (wyborMenu != 4);



    // Do dalszego przetwarzania, np. obracania obrazka
    // Mo¿esz u¿yæ wczytanyObrazek.piksele do dostêpu do wartoœci pikseli

    // Na koniec zwolnij pamiêæ zaalokowan¹ dla tablicy pikseli
    for (int i = 0; i < wczytanyObrazek.wysokosc; i++) {
        free(wczytanyObrazek.piksele[i]);
    }
    free(wczytanyObrazek.piksele);

    return 0;
}

//void wczytanieObrazuZPliku(struct obraz* nowyObraz)
//{
//	char nazwa[20];
//	printf("Podaj nazwe obrazu: \n");
//	scanf("%s", nazwa);
//	char buf[0x26]; //to ma przyjac nazwe +PGM
//	//do bufforu nastepuje przypisuje pamiec nazwa + 5 jednostek pamieci na .PGMEOF
//	snprintf(buf, sizeof(nazwa) + 5, "%s.PGM", nazwa);
//	FILE* plik = fopen(buf, "r");
//	if (plik == NULL)
//	{
//		printf("\nBlad otwarcia pliku.\n");
//		return;
//	}
//
//	char standard[3];
//	fscanf(plik, "%s", standard);
//	if (standard[0] != 'P' || standard[1] != '2')
//	{
//		printf("Niewlasciwy standard obrazu");
//		fclose(plik);
//		return;
//	}
//	fscanf(plik, "%d %d %d", &nowyObraz->szerokoscObrazu, &nowyObraz->wysokoscObrazu, &nowyObraz->skalaSzarosci);
//	printf("Szerokosc: %d, Wysokosc: %d, Szarosc: %d\n", nowyObraz->szerokoscObrazu, nowyObraz->wysokoscObrazu, nowyObraz->skalaSzarosci);
//	int** pixTemp;
//
//	//pixTemp = (int**)malloc(nowyObraz->wysokoscObrazu * sizeof(int*));
//	//if (pixTemp == NULL) {
//	//	printf("Blad alokacji pamieci dla tablicy pikseli.\n");
//	//	return;
//	//}
//
//	//for (int i = 0; i < nowyObraz->wysokoscObrazu; i++) {
//	//	(*pixTemp)[i] = (int*)malloc(5 * sizeof(int));
//	//	if (pixTemp[i] == NULL) {
//	//		printf("Blad alokacji pamieci dla wiersza %d.\n", i);
//	//		return;
//	//	}
//	//}
//
//
//	nowyObraz->piksele = (int**)malloc(nowyObraz->wysokoscObrazu * sizeof(int*));
//	for (int i = 0; i < nowyObraz->wysokoscObrazu; i++) {
//		nowyObraz->piksele[i] = (int*)malloc(nowyObraz->szerokoscObrazu * sizeof(int));
//		for (int j = 0; j < nowyObraz->szerokoscObrazu; j++) {
//			fscanf(plik, "%d", nowyObraz->piksele[i][j]);
//		}
//	}
//
//	fclose(plik);
//}
//
//void menuWygenerowaniaObrazu(char* gwiazdki, int* wybor)
//{
//	//wczytanieObrazuZPliku(nowyObraz, standard[]);
//
//	printf("Czy chcesz: \n");
//	do
//	{
//		printf("Dodac nastepny obraz: 1.\n Usunac obraz: 2. \n Ponownie wyœwietlic liste obrazow: 3.\n Wybrac aktywny obrazu z tablicy: 4.\n");
//		//wyswietListaObrazow();
//		while (scanf("%d", wybor) != 1)
//		{
//			printf("!!! BLAD !!!\nWybierz opcje (1-4): ");
//			//scanf("%*[^\n]");
//		}
//		if (!(*wybor == 1 || *wybor == 2 || *wybor == 3 || *wybor == 4)) printf("\nBLAD Sproboj ponownie\n");
//	} while (!(*wybor == 1 || *wybor == 2 || *wybor == 3 || *wybor == 4));
//
//	//wybraneObrazy;
//	printf("Obraz wybrane: ilosc, nazwy");
//}
//
//void przetworzenieObrazu(char* gwiazdki, int* wybor)
//{
//	//wybraneObrazy();
//
//	printf("Jak chcesz przetworzyc obraz: \n");
//	do
//	{
//		printf("Obrot o 90·k stopni: 1.\n Histogram z zapisem do pliku.CSV: 2.\n Wybierz jedno: progowanie z dowolnym progiem / negatyw / odbicie wzglêdem osi: 3.\n Dodawanie szumu typu pieprz i sol: 4.\n Wybierz jedno : filtr Gaussa / filtr medianowy(oba z oknem 3x3): 5.\n");
//
//		while (scanf("%d", wybor) != 1)
//		{
//			printf("!!! BLAD !!!\nWybierz opcje (1-5): ");
//			//scanf("%*[^\n]");
//		}
//		if (!(*wybor == 1 || *wybor == 2 || *wybor == 3 || *wybor == 4 || *wybor == 5)) printf("\nBLAD Sproboj ponownie\n");
//	} while (!(*wybor == 1 || *wybor == 2 || *wybor == 3 || *wybor == 4 || *wybor == 5));
//}
//
//void menuZapisDoPliku(bool* czyZapisac)
//{
//	int wybor;
//	do
//	{
//		printf("\nCzy chcesz zapisac przetworzone obrazy do pliku\n1. Tak \n2. Nie: ");
//		while (scanf("%d", &wybor) != 1)
//		{
//			printf("!!! BLAD !!!\nWybierz opcje (1-2: ");
//			scanf("%*[^\n]");
//		}
//		if (!(wybor == 1 || wybor == 2)) printf("\nBLAD Sproboj ponownie\n");
//	} while (!(wybor == 1 || wybor == 2));
//	if (wybor == 1) *czyZapisac = true;
//	else printf("\nOdszumianie zakonczone bez zapisywania danych do pliku\n");
//	scanf("%*[^\n]");
//}
//
////void zapisDoPlikuOdszum(double* odszumionySygnalY, double* daneOryginalneY, double* wybranySygnalX, int rozmiar)
////{
////	char nazwa[20];
////	printf("Podaj nazwe pliku: ");
////	scanf("%20s", nazwa);
////	char buf[30]; //to ma przyjac nazwe +csv
////	//do bufforu nastepuje przypisuje pamiec nazwa + 5 jednostek pamieci na .csvEOF
////	snprintf(buf, sizeof(nazwa) + 5, "%s.csv", nazwa);
////	FILE* plik = fopen(buf, "w");
////
////	if (plik != NULL)
////	{
////		for (int i = 0; i < rozmiar; i++)
////		{
////			fprintf(plik, " %lf ; %lf ; %lf\n", wybranySygnalX[i], daneOryginalneY[i], odszumionySygnalY[i]);
////		}
////		fclose(plik);
////		printf("\nDane w formacie - X ; Y(zaszumione) : #Y(odszumione) - zosatly zapisane do pliku %s\n", buf);
////	}
////	else
////	{
////		printf("\nBlad otwarcia pliku.\n");
////	}
////	scanf("%*[^\n]");
////}
////deklaracja struktury
////typedef struct
////{
////	char tytul[100];
////	double szerokoscObrazu;
////	double wysokoscObrazu;
////	int szarosc;
////}obraz;
//			   //struct obraz named obraz
////void print_obraz(struct obraz obraz)
////{
////
////	printf("Tytul: %s\n", obraz.tytul);
////	printf("Szerokosc Obrazu: %lf\n", obraz.szerokoscObrazu);
////	printf("Wysokosc Obrazu: %lf\n", obraz.wysokoscObrazu);
////	printf("Szarosc: %d\n", obraz.szarosc);
////}
////void wczytanieZPliku()
////{
////	char nazwa[20];
////	printf("Podaj nazwe obrazu: ");
////	scanf("%s", nazwa);
////	char buf[0x26]; //to ma przyjac nazwe +csv
////	//do bufforu nastepuje przypisuje pamiec nazwa + 5 jednostek pamieci na .csvEOF
////	snprintf(buf, sizeof(nazwa) + 5, "%s.PGM", nazwa);
////	FILE* plik = fopen(buf, "r");
////	if (plik == NULL)
////	{
////		printf("\nBlad otwarcia pliku.\n");
////		return;
////	}
//	//int rozmiar = 1;
//	//int n = 0; //sledzenie ktory raz wykonuje sie petla jesli n wieksze rowne od rozmiaru to rozmiar podwoic
//	////alokacja pojedynczej jednostki wartosci
//	//*tablicaY = malloc(sizeof(double));
//	//*tablicaX = malloc(sizeof(double));
//	//double x, y;
//	//while (fscanf(plik, "%lf ; %lf\n", &x, &y) == 2)
//	//{
//	//	if (rozmiar <= n)
//	//	{
//	//		double* schowek1, * schowek2;
//	//		rozmiar = 2 * rozmiar; //zwiekszenie rozmiaru w tablicy
//	//		schowek1 = realloc(*tablicaX, (rozmiar) * sizeof(double));
//	//		schowek2 = realloc(*tablicaY, (rozmiar) * sizeof(double));
//	//		if (schowek1 != NULL || schowek2 != NULL)
//	//		{
//	//			*tablicaX = schowek1;
//	//			*tablicaY = schowek2;
//	//		}
//	//		else
//	//		{
//	//			printf("\nBLAD realokacji pamieci\nSproboj ponownie za chwile :)\n");
//	//			return;
//	//		}
//	//	}
//	//	//wywolanie dla podwojnego wskaznika   *(tablicaX + n) = &x;   *(tablicaY + n) = &y;
//	//	(*tablicaX)[n] = x;
//	//	(*tablicaY)[n] = y;
//	//	printf("- Przyjeto wartosc X: %lf i  Y: %lf \n", (*tablicaX)[n], (*tablicaY)[n]);
//	//	n++;
//	//}
//	//rozmiarOdczytanychDanych[0] = n;
//	//printf("\nDane zosatly odczytane z pliku %s\n", buf);
//	//printf("Przyjete odczyty: %d\n", n);
//	//fclose(plik);
////}