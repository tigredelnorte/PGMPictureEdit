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

struct Galeria
{
	int iloscObrazow;
	struct ObrazekPGM* obrazy;
};

void wyswietlMenu(char* gwiazdki, int iloscObrazow, char* aktywnyNazwa)
{
	if (aktywnyNazwa == NULL) aktywnyNazwa = "BRAK";
	printf("*********************************************************\n");
	printf("                  Menu Galerii \"J\"                     \n");
	printf("*********************************************************\n");
	printf("               Obrazy w galerii: %d                      \n", iloscObrazow);
	printf("               Aktywny obraz: %s                         \n", aktywnyNazwa);
	printf("*********************************************************\n");

	//printf("\n                    MENU\n");
	printf("1. Pobierz nowy obraz z pliku do galerii         [%c]\n", gwiazdki[0]);
	printf("2. Ustaw aktywny obraz                           [%c]\n", gwiazdki[1]);
	printf("3. Przetwarzaj aktywny obraz                     [%c]\n", gwiazdki[2]);
	printf("4. Zamknij aktywny obraz                         [%c]\n", gwiazdki[3]);
	printf("5. Usun obraz z galerii                          [%c]\n", gwiazdki[4]);
	printf("6. Zakoncz program                               [%c]\n", gwiazdki[5]);
	printf("Wybierz opcje (1-6): ");
}

void wyswietlMenuPrzetwarzania(struct ObrazekPGM* aktywnyObrazek)
{
	printf("\n*********************************************************\n");
	printf("            PRZETWARZANIE AKTYWNEGO OBRAZU               \n");
	printf("*********************************************************\n");
	printf("            Aktywny obraz: %s                            \n", aktywnyObrazek->nazwaPliku);
	printf("*********************************************************\n");

	//printf("\n                    MENU\n");
	printf("1. Obrot o 90-k stopni         \n");
	printf("2. Historiogram                \n");
	printf("3. Negatyw                     \n");
	printf("4. Pieprz i sol                \n");
	printf("5. Filtr Gaussa                \n");
	printf("6. Cofnij zmiany               \n");
	printf("7. Zapisz zmiany               \n");
	printf("8. Wyjdz do Menu Galerii       \n");
	printf("Wybierz opcje (1-8): ");
}

void przetwarzajAktywnyObraz(struct ObrazekPGM* aktywnyObrazek) {
	int wyborMenuPrzetwarzania = 0;
	do {
		wyswietlMenuPrzetwarzania(/*gwiazdki, galeriaJ.iloscObrazow, */aktywnyObrazek);
		while (scanf("%d", &wyborMenuPrzetwarzania) != 1)
		{
			printf("!!! BLAD !!!\nWybierz opcje (1-8): ");
			scanf("%*[^\n]");
			printf("\n");
		}
		switch (wyborMenuPrzetwarzania) {
		case 1: // Obrot o 90-k stopni
			printf("\n");
			break;
		case 2: // Historiogram
			printf("\n");
			break;
		case 3: // Negatyw
			printf("\n");
			break;
		case 4: // Pieprz i sol
			printf("\n");
			break;
		case 5: // Filtr Gaussa
			printf("\n");
			break;
		case 6: // Cofnij zmiany
			printf("\n");
			break;
		case 7: // Zapisz zmiany
			printf("\n");
			break;
		case 8: // Wyjdz do Menu Galerii
			printf("\n");
			break;
		default:
			printf("Nieprawidlowy wybor. Wybierz opcje od 1 do 8.\n");
			printf("\n");
			break;
		}
	} while (wyborMenuPrzetwarzania != 8);
}

// Funkcja do odczytu danych z pliku PGM
void wczytajObraz(struct ObrazekPGM* obrazek) {

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
	while (fgets(linia, sizeof(linia), plik) != NULL) {
		if (!(linia[0] == '#'))
		{
			break; // Jeœli linia nie jest komentarzem, przerywamy pêtlê
		}
	}
	if (sscanf(linia, "%d %d", &obrazek->szerokosc, &obrazek->wysokosc) != 2)
	{
		printf("Blad pliku PGM");
		return;
	};

	while (fgets(linia, sizeof(linia), plik) != NULL) {
		if (!(linia[0] == '#'))
		{
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
	if (obrazek->piksele != NULL)
	{
		for (int i = 0; i < obrazek->wysokosc; i++) {
			obrazek->piksele[i] = (int*)malloc(obrazek->szerokosc * sizeof(int));
			if (obrazek->piksele[i] != NULL)
			{
				do fgets(linia, sizeof(linia), plik);
				while ((linia[0] == '#'));
				obrazek->piksele[i] = (int*)malloc(obrazek->szerokosc * sizeof(int));
				char* ptr = linia; // Ustawienie wskaŸnika pomocniczego na pocz¹tku linii
				int index = 0;
				for (int j = 0; j < obrazek->szerokosc; j++) {
					sscanf(ptr, "%d%n", &obrazek->piksele[i][j], &index);
					//printf("Odczyt[%d][%d]: %d\n", i, j, obrazek->piksele[i][j]);
					ptr += index;
				}
			}
		}
	}
}

void dodajObrazDoGalerii(struct Galeria* galeria, struct ObrazekPGM obraz) {
	if ((galeria)->iloscObrazow == 0) {
		(galeria)->obrazy = (struct ObrazekPGM*)malloc(sizeof(struct ObrazekPGM));
		if ((galeria)->obrazy == NULL) {
			printf("B³¹d alokacji pamiêci\n");
			return;
		}
	}
	else {
		struct ObrazekPGM* nowe_obrazy = (struct ObrazekPGM*)realloc((galeria)->obrazy, ((galeria)->iloscObrazow * 2) * sizeof(struct ObrazekPGM));
		if (nowe_obrazy == NULL) {
			printf("B³¹d realokacji pamiêci\n");
			return;
		}
		(galeria)->obrazy = nowe_obrazy;
	}
	for (int i = 0; i < (galeria)->iloscObrazow; i++)
	{
		if (strcmp(galeria->obrazy[i].nazwaPliku, obraz.nazwaPliku) == 0) return;
	}
	(galeria)->obrazy[(galeria)->iloscObrazow] = obraz;
	(galeria)->iloscObrazow += 1;
}

void usunObrazZGalerii(struct Galeria* galeria, int* indeks) {
	//do {
	//	printf("Wybierz obraz do usuniêcia: ");
	//	scanf("%d", &indeks);
	//	if (indeks < 1 || indeks > galeria->iloscObrazow) {
	//		printf("Nieprawidlowy numer obrazu. Podaj liczbe z zakresu 1-%d\n", galeria->iloscObrazow);
	//	}
	//} while (indeks < 1 || indeks > galeria->iloscObrazow);
	printf("Wybierz obraz do usuniecia: ");
	scanf("%d", indeks);
	if (*indeks <= 0 || *indeks > galeria->iloscObrazow) {
		printf("Nieprawid³owy indeks obrazu\n");
		return;
	}

	free(galeria->obrazy[*indeks - 1].piksele); // Zwolnienie pamiêci dla pikseli obrazu
	for (int i = *indeks - 1; i < galeria->iloscObrazow - 1; ++i) {
		galeria->obrazy[i] = galeria->obrazy[i + 1]; // Przesuniêcie obrazów w tablicy o jedno miejsce w lewo
	}

	galeria->iloscObrazow -= 1; // Zmniejszenie liczby obrazów w galerii
	galeria->obrazy = (struct ObrazekPGM*)realloc(galeria->obrazy, galeria->iloscObrazow * sizeof(struct ObrazekPGM)); // Skrócenie tablicy obrazów
	if (galeria->obrazy == NULL && galeria->iloscObrazow > 0) {
		printf("B³¹d realokacji pamiêci\n");
		return;
	}
}

void wypiszNazwyObrazow(struct Galeria* galeria) {
	printf("\nObrazy w Galerii \"J\":\n");
	for (int i = 0; i < galeria->iloscObrazow; ++i) {
		printf("%d. %s\n", i + 1, galeria->obrazy[i].nazwaPliku);
	}
}

void ustawAktywnyObraz(struct Galeria* galeria, int* indeks, struct ObrazekPGM* aktywnyObraz) {
	do {
		printf("Wybierz aktywny obraz: ");
		scanf("%d", indeks);
		if (*indeks < 1 || *indeks > galeria->iloscObrazow) {
			printf("Nieprawidlowy numer obrazu. Podaj liczbe z zakresu 1-%d\n", galeria->iloscObrazow);
		}
	} while (*indeks < 1 || *indeks > galeria->iloscObrazow);

	// Skopiowanie wybranego obrazu do struktury wczytanyObraz
	*aktywnyObraz = galeria->obrazy[*indeks - 1];
}

void zamknijAktywnyObraz(struct ObrazekPGM* aktywnyObrazek, int* indeks)
{
	indeks = NULL;
	strcpy((*aktywnyObrazek).nazwaPliku, "Brak");
	(*aktywnyObrazek).skalaSzarosci = 0;
	(*aktywnyObrazek).szerokosc = 0;
	(*aktywnyObrazek).wysokosc = 0;
}

int main() {
	char gwiazdki[] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
	char star = '*';
	char spacja = ' ';
	int wyborMenu = 0;
	int indeksAktywnyObraz = NULL;
	int indeksUsunObraz = NULL;
	struct ObrazekPGM wczytanyObrazek;
	struct ObrazekPGM aktywnyObrazek;
	strcpy(aktywnyObrazek.nazwaPliku, "Brak");

	struct Galeria galeriaJ;
	galeriaJ.iloscObrazow = 0;
	galeriaJ.obrazy = (struct ObrazekPGM*)malloc(sizeof(struct ObrazekPGM));


	do
	{
		wyswietlMenu(gwiazdki, galeriaJ.iloscObrazow, aktywnyObrazek.nazwaPliku);
		while (scanf("%d", &wyborMenu) != 1)
		{
			printf("!!! BLAD !!!\nWybierz opcje (1-6): ");
			scanf("%*[^\n]");
			printf("\n");
		}

		switch (wyborMenu) {
		case 1: // Pobierz nowy obraz z pliku do galerii  
			wczytajObraz(&wczytanyObrazek);
			//printf("Nazwa pliku: %s\n", wczytanyObrazek.nazwaPliku);
			//printf("Szerokosc: %d\n", wczytanyObrazek.szerokosc);
			//printf("Wysokosc: %d\n", wczytanyObrazek.wysokosc);
			//printf("Skala szarosci: %d\n", wczytanyObrazek.skalaSzarosci);
			//
			//printf("XXXXXXXXX\n");
			//for (int i = 0; i < wczytanyObrazek.wysokosc; i++) {
			//	for (int j = 0; j < wczytanyObrazek.szerokosc; j++) {
			//		printf("%d ", wczytanyObrazek.piksele[i][j]);
			//	}
			//	printf("\n");
			//}
			//printf("XXXXXXXXX\n");
			dodajObrazDoGalerii(&galeriaJ, wczytanyObrazek);
			//printf("Nazwa pliku: %s\n", galeriaJ.obrazy[0].nazwaPliku);
			//printf("Szerokosc: %d\n", galeriaJ.obrazy[0].szerokosc);
			//printf("Wysokosc: %d\n", galeriaJ.obrazy[0].wysokosc);
			//printf("Skala szarosci: %d\n", galeriaJ.obrazy[0].skalaSzarosci);
			//printf("XXXXXXXXX\n");
			//for (int i = 0; i < galeriaJ.obrazy[0].wysokosc; i++) {
			//	for (int j = 0; j < galeriaJ.obrazy[0].szerokosc; j++) {
			//		printf("%d ", galeriaJ.obrazy[0].piksele[i][j]);
			//	}
			//	printf("\n");
			//}
			//printf("XXXXXXXXX\n");
			printf("\n");
			break;
		case 2: // Ustaw aktywny obraz
			wypiszNazwyObrazow(&galeriaJ);
			ustawAktywnyObraz(&galeriaJ, &indeksAktywnyObraz, &aktywnyObrazek);
			printf("\nNazwa pliku: %s\n", aktywnyObrazek.nazwaPliku);
			printf("Szerokosc: %d\n", aktywnyObrazek.szerokosc);
			printf("Wysokosc: %d\n", aktywnyObrazek.wysokosc);
			printf("Skala szarosci: %d\n", aktywnyObrazek.skalaSzarosci);
			printf("XXXXXXXXX\n");
			for (int i = 0; i < aktywnyObrazek.wysokosc; i++) {
				for (int j = 0; j < aktywnyObrazek.szerokosc; j++) {
					printf("%d ", aktywnyObrazek.piksele[i][j]);
				}
				printf("\n");
			}
			printf("XXXXXXXXX\n");
			printf("\n");
			break;
		case 3: // Przetwarzaj aktywny obraz
			przetwarzajAktywnyObraz(&aktywnyObrazek);
			printf("\n");
			break;
		case 4: // Zamknij aktywny obraz 
			zamknijAktywnyObraz(&aktywnyObrazek, &indeksAktywnyObraz);
			printf("\n");
			break;
		case 5: // Usun obraz z galerii  
			wypiszNazwyObrazow(&galeriaJ);
			usunObrazZGalerii(&galeriaJ, &indeksUsunObraz);
			if (indeksAktywnyObraz == indeksUsunObraz)
			{
				zamknijAktywnyObraz(&aktywnyObrazek, &indeksAktywnyObraz);
			}
			printf("\n");
			break;
		case 6: // Zakoncz program  
			printf("Program zostal zakonczony.\n");
			printf("\n");
			break;
		default:
			printf("Nieprawidlowy wybor. Wybierz opcje od 1 do 6.\n");
			printf("\n");
			break;
		}
	} while (wyborMenu != 6);

	// Na koniec zwolnij pamiêæ zaalokowan¹ dla tablicy pikseli
	return 0;
}