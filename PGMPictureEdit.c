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
	printf("                  PRZETWARZANIE OBRAZOW                  \n");
	printf("                   Obrazy w galerii: %d                  \n", iloscObrazow);
	printf("                  Aktywny obraz: %s                  \n", aktywnyNazwa);
	printf("*********************************************************\n");

	//printf("\n                    MENU\n");
	printf("1. Pobierz nowy obraz z pliku                    [%c]\n", gwiazdki[0]);
	printf("2. Wczytaj aktywny obraz z galerii               [%c]\n", gwiazdki[1]);
	printf("4. Usun obraz z galerii                          [%c]\n", gwiazdki[3]);
	printf("5. Zakoncz program                               [%c]\n", gwiazdki[3]);
	printf("Wybierz opcje (1-5): ");
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
					printf("Odczyt[%d][%d]: %d\n", i, j, obrazek->piksele[i][j]);
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

	(galeria)->obrazy[(galeria)->iloscObrazow] = obraz;
	(galeria)->iloscObrazow += 1;
}

void usunObrazZGalerii(struct Galeria* galeria, int indeks) {
	if (indeks < 0 || indeks >= galeria->iloscObrazow) {
		printf("Nieprawid³owy indeks obrazu\n");
		return;
	}

	free(galeria->obrazy[indeks].piksele); // Zwolnienie pamiêci dla pikseli obrazu
	for (int i = indeks; i < galeria->iloscObrazow - 1; ++i) {
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
	printf("\nLista wczytanych obrazow:\n");
	for (int i = 0; i < galeria->iloscObrazow; ++i) {
		printf("%d. %s\n", i + 1, galeria->obrazy[i].nazwaPliku);
	}
}

void wczytajWybranyObraz(struct Galeria* galeria, int indeks, struct ObrazekPGM* aktywnyObraz) {
	do {
		printf("Wybierz numer obrazu do wczytania: ");
		scanf("%d", &indeks);
		if (indeks < 1 || indeks > galeria->iloscObrazow) {
			printf("Nieprawidlowy numer obrazu. Podaj liczbe z zakresu 1-%d\n", galeria->iloscObrazow);
		}
	} while (indeks < 1 || indeks > galeria->iloscObrazow);

	// Skopiowanie wybranego obrazu do struktury wczytanyObraz
	*aktywnyObraz = galeria->obrazy[indeks - 1];
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

	struct Galeria galeriaJ;
	galeriaJ.iloscObrazow = 0;
	galeriaJ.obrazy = (struct ObrazekPGM*)malloc(sizeof(struct ObrazekPGM));


	do
	{
		wyswietlMenu(gwiazdki, galeriaJ.iloscObrazow, aktywnyObrazek.nazwaPliku);
		while (scanf("%d", &wyborMenu) != 1)
		{
			printf("!!! BLAD !!!\nWybierz opcje (1-9): ");
			scanf("%*[^\n]");
		}

		switch (wyborMenu) {
		case 1:
			wczytajObrazek(&wczytanyObrazek);
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
			//
			//printf("XXXXXXXXX\n");
			//for (int i = 0; i < galeriaJ.obrazy[0].wysokosc; i++) {
			//	for (int j = 0; j < galeriaJ.obrazy[0].szerokosc; j++) {
			//		printf("%d ", galeriaJ.obrazy[0].piksele[i][j]);
			//	}
			//	printf("\n");
			//}
			//printf("XXXXXXXXX\n");
			////2
			//wczytajObrazek(&wczytanyObrazek);
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
			//dodajObrazDoGalerii(&galeriaJ, wczytanyObrazek);
			//printf("Nazwa pliku: %s\n", galeriaJ.obrazy[0].nazwaPliku);
			//printf("Szerokosc: %d\n", galeriaJ.obrazy[0].szerokosc);
			//printf("Wysokosc: %d\n", galeriaJ.obrazy[0].wysokosc);
			//printf("Skala szarosci: %d\n", galeriaJ.obrazy[0].skalaSzarosci);
			//
			//printf("XXXXXXXXX\n");
			//for (int i = 0; i < galeriaJ.obrazy[1].wysokosc; i++) {
			//	for (int j = 0; j < galeriaJ.obrazy[1].szerokosc; j++) {
			//		printf("%d ", galeriaJ.obrazy[1].piksele[i][j]);
			//	}
			//	printf("\n");
			//}
			//printf("XXXXXXXXX\n");
			//printf("Obrazy w galerii %d\n", galeriaJ.iloscObrazow);
			break;
		case 2:
			wypiszNazwyObrazow(&galeriaJ, &indeksAktywnyObraz);
			wczytajWybranyObraz(&galeriaJ, &indeksAktywnyObraz, &aktywnyObrazek);
			break;
		case 3:
			wypiszNazwyObrazow(&galeriaJ, &indeksUsunObraz);
			usunObrazZGalerii(&galeriaJ, &indeksUsunObraz);
			break;
		case 4:
			//menuZapisDoPliku();
			break;
		case 5:
			printf("Program zostal zakonczony.\n");
			break;
		default:
			printf("Nieprawidlowy wybor. Wybierz opcje od 1 do 4.\n");
			break;
		}
	} while (wyborMenu != 5);



	// Do dalszego przetwarzania, np. obracania obrazka
	// Mo¿esz u¿yæ wczytanyObrazek.piksele do dostêpu do wartoœci pikseli

	// Na koniec zwolnij pamiêæ zaalokowan¹ dla tablicy pikseli
	return 0;
}