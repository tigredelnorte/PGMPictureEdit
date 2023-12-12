#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
	printf("5. Exportuj obraz do pliku PGM                   [%c]\n", gwiazdki[4]);
	printf("6. Usun obraz z galerii                          [%c]\n", gwiazdki[4]);
	printf("7. Zakoncz program                               [%c]\n", gwiazdki[5]);
	printf("Wybierz opcje (1-7): ");
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
	printf("7. Zapisz                     \n");
	printf("8. Zapisz jako                 \n");
	printf("9. Wyjdz do Menu Galerii       \n");
	printf("Wybierz opcje (1-9): ");
}

//void obrotObrazu(struct obrazekPGM* obrazek, int wybor)
//{
//	int K = 0;
//	printf("Szerokosc: %d", obrazek.szerokosc);
//	printf("%d", obrazek->wysokosc);
//	/*  printf("Podaj kierunek obrotu obrazu: \n");
//	  do
//	  {
//		  printf("Obrót zgodnie z ruchem wskazówek zegara: 1.\n Obrot przeciwnie do ruchu wskazowek zegara: 2 \n");
//
//		  while (scanf("%d", &wybor) != 1)
//		  {
//			  printf("!!! BLAD !!!\nWybierz opcje 1 lub 2");
//			  scanf("%*[^\n]");
//		  }
//		  if (!(wybor == 1 || wybor == 2))
//			  printf("\nBLAD Sproboj ponownie\n");
//	  } while (!(wybor == 1 || wybor == 2));*/
//
//	printf("Podaj K, jest to wielokrotnoœæ 90 stopni\n");
//	while (scanf("%d", &K) != 1)
//	{
//		printf("!!! BLAD !!!\nPodaj poprawn¹ iloœæ obrotów: ");
//		scanf("%*[^\n]");
//	}
//	printf("Obraz zostanie obrócony o %d x 90 stopni\n", K);
//
//	int temp;
//	if (wybor == 1)
//	{
//
//		for (int k = 0; k < K; k++)
//		{
//			// Transpozycja macierzy
//			for (int i = 0; i < obrazek->wysokosc; i++)
//			{
//				for (int j = 0; j < obrazek->szerokosc; j++)
//				{
//					temp = obrazek->piksele[i][j];
//					obrazek->piksele[i][j] = obrazek->piksele[j][i];
//					obrazek->piksele[j][i] = temp;
//					printf("Odczyt[%d][%d]: %d\n", i, j, obrazek->piksele[i][j]);
//				}
//			}
//			for (int i = 0; i < obrazek->wysokosc; i++)
//			{
//				for (int j = 0; j < obrazek->szerokosc; j++)
//				{
//					printf("%d", obrazek->piksele[j][i]);
//				}
//			}
//			printf("\n");
//		}
//	}
//	//// Odwrócenie kolumn macierzy
//	//for (int i = 0; i < obrazek->wysokoscObrazu; i++)
//	//{
//	//    for (int j = 0; j < obrazek->szerokoscObrazu / 2; j++)
//	//    {
//	//        temp = obrazek->piksele[i][j];
//	//        obrazek->piksele[i][j] = obrazek->piksele[i][obrazek->szerokoscObrazu - 1 - j];
//	//        obrazek->piksele[i][obrazek->szerokoscObrazu - 1 - j] = temp;
//	//    }
//	//}
//}

void histogram(struct ObrazekPGM* obrazek)
{
	int scale = obrazek->skalaSzarosci;
	if (obrazek->skalaSzarosci != NULL) {

	}
	//odcienie szarosci
	int histogram[100];
	//przechodzenie przez piksele obrazu i zliczanie wartoœci intensywnoœci
	for (int i = 0; i < obrazek->wysokosc; ++i)
	{
		for (int j = 0; j < obrazek->szerokosc; ++j)
		{
			int szarosc = obrazek->piksele[i][j];
			histogram[szarosc]++;
		}
	}
	
	char nazwa[20];
	printf("Podaj nazwe pliku: ");
	scanf("%20s", nazwa);
	char buf[0x26];
	snprintf(buf, sizeof(nazwa) + 5, "%s.csv", nazwa);
	FILE* plik = fopen(buf, "w");

	if (plik == NULL)
	{
		printf("\nBlad otwarcia pliku %s\n", buf);
	}

	// Zapis do pliku CSV
	//tab w excel
	fprintf(plik, "Szarosc,Piksele\n");
	for (int i = 0; i < 1000; ++i)
	{
		fprintf(plik, "%d,%d\n", i, histogram[i]);
	}

	fclose(plik);
	printf("Histogram zostal zapisany do pliku %s.\n", nazwa);
}

//void odbicieOsi(struct obrazekPGM* obrazek, int wybor)
//{
//
//	printf("Podaj oœ wzglêdem której obraz bêdzie odbity: \n");
//	do
//	{
//		printf("Wzglêdem osi X: 1.\n Wzglêdem osi Y: 2 \n");
//
//		while (scanf("%d", &wybor) != 1)
//		{
//			printf("!!! BLAD !!!\nWybierz opcje 1 lub 2");
//			scanf("%*[^\n]");
//		}
//		if (!(wybor == 1 || wybor == 2))
//			printf("\nBLAD Sproboj ponownie\n");
//		int temp = 0;
//		if (wybor == 1)
//		{
//			//zmiana piksela wewnatrz kazdego wiersza
//			for (int i = 0; i < obrazek->wysokosc / 2; i++)
//			{
//				for (int j = 0; j < obrazek->szerokosc; j++)
//				{
//					int temp = obrazek->piksele[i][j];
//					obrazek->piksele[i][j] = obrazek->piksele[obrazek->wysokosc - 1 - i][j];
//					obrazek->piksele[obrazek->wysokosc - 1 - i][j] = temp;
//				}
//			}
//		}
//		else
//		{
//			for (int i = 0; i < obrazek->wysokosc; i++)
//			{
//				for (int j = 0; j < obrazek->szerokosc / 2; j++)
//				{
//					int temp = obrazek->piksele[i][j];
//					obrazek->piksele[i][j] = obrazek->piksele[i][obrazek->szerokosc - 1 - j];
//					obrazek->piksele[i][obrazek->szerokosc - 1 - j] = temp;
//				}
//			}
//		}
//	} while (!(wybor == 1 || wybor == 2));
//
//	printf("Wyœwietlony obraz");
//	for (int i = 0; i < obrazek->wysokosc; i++)
//	{
//		for (int j = 0; j < obrazek->szerokosc; j++)
//		{
//			printf("%d ", obrazek->piksele[i][j]);
//		}
//		printf("\n");
//	}
//}

void kopjujObraz(struct ObrazekPGM* zrodlo, struct ObrazekPGM* target) {
	target->szerokosc = zrodlo->szerokosc;
	target->wysokosc = zrodlo->wysokosc;
	target->skalaSzarosci = zrodlo->skalaSzarosci;

	// Alokacja pamiêci dla pikseli tylko jeœli nie by³a wczeœniej zaalokowana
	if (target->piksele != NULL) {
		target->piksele = (int**)malloc(zrodlo->wysokosc * sizeof(int*));
		if (target->piksele == NULL) {
			printf("B³¹d alokacji pamiêci\n");
			return;
		}
	}
	for (int i = 0; i < zrodlo->wysokosc; i++) {
		if (target->piksele[i] != NULL) {
			target->piksele[i] = (int**)malloc(zrodlo->wysokosc * sizeof(int*));
			if (target->piksele[i] == NULL) {
				printf("B³¹d alokacji pamiêci\n");
				return;
			}
		}
		
		//if (target->piksele[i] == NULL) {
		//// Zwolnienie zaalokowanej pamiêci
		//for (int j = 0; j < i; j++) {
		//	free(target->piksele[j]);
		//}
		//free(target->piksele);
		//printf("B³¹d alokacji pamiêci\n");
		//return;
		//}
		memcpy(target->piksele[i], zrodlo->piksele[i], zrodlo->szerokosc * sizeof(int));
		//for (int j = 0; j < target->szerokosc; j++) {
		//	printf("test: %d", target->piksele[i][j]);
		//}
	}
	strcpy((target)->nazwaPliku, (zrodlo)->nazwaPliku);
}


void przetwarzajAktywnyObraz(struct ObrazekPGM* aktywnyObrazek) {
	int wyborMenuPrzetwarzania = 0;
	struct ObrazekPGM kopiaObrazka;
	kopjujObraz(aktywnyObrazek, &kopiaObrazka);
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
			//obrotObrazu(&kopiaObrazka, 1);
			printf("\n");
			break;
		case 2: // Historiogram
			histogram(&kopiaObrazka);
			printf("\n");
			break;
		case 3: // Odbicie wzgledem osi
			//odbicieOsi(&kopiaObrazka, 1);
			printf("\n");
			break;
		case 4: // Pieprz i sol
			printf("\n");
			break;
		case 5: // Filtr Gaussa
			printf("\n");
			break;
		case 6: // Cofnij zmiany
			kopjujObraz(aktywnyObrazek, &kopiaObrazka);
			//kopiaObrazka = aktywnyObrazek;
			break;
		case 7: // Zapisz 
			kopjujObraz(&kopiaObrazka, aktywnyObrazek);
			printf("Obraz zostal zapisany do galerii.\n");
			wyborMenuPrzetwarzania = 9;
			break;
		case 8: // Zapisz jako
			printf("Podaj nazwe pliku: ");
			char nazwa[20];
			scanf("%20s", nazwa);
			char buf[30];
			snprintf(buf, sizeof(nazwa) + 5, "%s.pgm", nazwa);
			kopjujObraz(&kopiaObrazka, aktywnyObrazek);
			strcpy(aktywnyObrazek->nazwaPliku, buf);
			printf("Obraz zostal zapisany do galerii.\n");
			wyborMenuPrzetwarzania = 9;
			break;
		case 9: // Wyjdz do Menu Galerii
			printf("\n");
			break;
		default:
			printf("Nieprawidlowy wybor. Wybierz opcje od 1 do 9.\n");
			printf("\n");
			break;
		}
	} while (wyborMenuPrzetwarzania != 9);
}

void pobierzNastepnaLinie(FILE* plik, char** linia) {
	size_t rozmiar = 1000; // Domyœlny rozmiar pocz¹tkowy
	*linia = (char*)malloc(rozmiar * sizeof(char));

	if (*linia == NULL) {
		printf("B³¹d alokacji pamiêci\n");
		return;
	}

	char* wynik = fgets(*linia, rozmiar, plik);
	if (wynik == NULL) {
		free(*linia);
		return;
	}

	while ((*linia)[0] == '#') {
		wynik = fgets(*linia, rozmiar, plik);
		if (wynik == NULL) {
			free(*linia);
			return;
		}
	}
	return;
}

// Funkcja do odczytu danych z pliku PGM
bool wczytajObraz(struct ObrazekPGM* obrazek) {

	char nazwa[20];
	printf("Podaj nazwe pliku PGM do wczytania: ");
	scanf("%s", nazwa);

	char buf[0x26]; //to ma przyjac nazwe +PGM
	//do bufforu nastepuje przypisuje pamiec nazwa + 5 jednostek pamieci na .PGMEOF
	snprintf(buf, sizeof(nazwa) + 5, "%s.pgm", nazwa);
	FILE* plik = fopen(buf, "r");
	if (plik == NULL)
	{
		printf("\nBlad otwarcia pliku.\n");
		return false;
	}
	char standard[3];
	fscanf(plik, "%s\n", standard);
	if (standard[0] != 'P' || standard[1] != '2')
	{
		printf("Niewlasciwy standard obrazu");
		fclose(plik);
		return false;
	}

	strcpy(obrazek->nazwaPliku, buf);

	char* linia;

	pobierzNastepnaLinie(plik, &linia);
	if (sscanf(linia, "%d %d", &obrazek->szerokosc, &obrazek->wysokosc) != 2)
	{
		printf("Blad pliku PGM");
		return false;
	};

	pobierzNastepnaLinie(plik, &linia);
	if (sscanf(linia, "%d", &obrazek->skalaSzarosci) != 1)
	{
		printf("Blad pliku PGM");
		return false;
	};

	printf("Szerokosc: %d, Wysokosc: %d, Szarosc: %d\n", obrazek->szerokosc, obrazek->wysokosc, obrazek->skalaSzarosci);

	obrazek->piksele = (int**)malloc(obrazek->wysokosc * sizeof(int*));
	if (obrazek->piksele != NULL)
	{
		for (int i = 0; i < obrazek->wysokosc; i++) {
			obrazek->piksele[i] = (int*)malloc(obrazek->szerokosc * sizeof(int));
			if (obrazek->piksele[i] != NULL)
			{
				pobierzNastepnaLinie(plik, &linia);
				int index = 0;
				int tempDigit = 0;
				for (int j = 0; j < obrazek->szerokosc; j++) {
					int scan = sscanf(linia, "%d%n", &tempDigit, &index);
					if (scan != 1)
					{
						pobierzNastepnaLinie(plik, &linia);
						j--;
					}
					else 
					{
						obrazek->piksele[i][j] = tempDigit;
						linia += index;
					}
				}
			}
		}
	}
	return true;
}

bool obrazWGalerii(struct Galeria* galeria, struct ObrazekPGM obraz)
{
	for (int i = 0; i < (galeria)->iloscObrazow; i++)
	{
		if (strcmp(galeria->obrazy[i].nazwaPliku, obraz.nazwaPliku) == 0) 
			return true;
	}
	return false;
}

void dodajObrazDoGalerii(struct Galeria* galeria, struct ObrazekPGM obraz) {
	if (obrazWGalerii(galeria, obraz)) return;
	for (int i = 0; i < (galeria)->iloscObrazow; i++)
	{
		if (strcmp(galeria->obrazy[i].nazwaPliku, obraz.nazwaPliku) == 0) return;
	}
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

void usunObrazZGalerii(struct Galeria* galeria, int* indeks) {
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

void nadpiszObrazWGalerii(struct Galeria* galeria, int* indeks, struct ObrazekPGM obraz) 
{
	(galeria)->obrazy[*indeks] = obraz;
}

void wypiszNazwyObrazow(struct Galeria* galeria) {
	printf("\nObrazy w Galerii \"J\":\n");
	for (int i = 0; i < galeria->iloscObrazow; ++i) {
		printf("%d. %s\n", i + 1, galeria->obrazy[i].nazwaPliku);
	}
}

void ustawAktywnyObraz(struct Galeria* galeria, int* indeks, struct ObrazekPGM* aktywnyObraz) {
	do {
		printf("Wybierz aktywny obraz (CYFRA): ");
		//scanf("%d", indeks);

		while (scanf("%d", indeks) != 1)
		{
			printf("!!! BLAD !!! Podaj cyfre: ");
			scanf("%*[^\n]");
		}

		if (*indeks < 1 || *indeks > galeria->iloscObrazow) {
			printf("Nieprawidlowy numer obrazu. Podaj liczbe z zakresu od 1 do %d\n", galeria->iloscObrazow);
		}
	} while (*indeks < 1 || *indeks > galeria->iloscObrazow);

	// Skopiowanie wybranego obrazu do struktury wczytanyObraz
	*aktywnyObraz = galeria->obrazy[*indeks - 1];
}

int wybierzDoEksportu(int iloscObrazow) {
	int indeks = 0;
	do {
		printf("Wybierz obraz do zapisania do pliku PGM (CYFRA): ");
		//scanf("%d", indeks);

		while (scanf("%d", &indeks) != 1)
		{
			printf("!!! BLAD !!! Podaj cyfre: ");
			scanf("%*[^\n]");
		}

		if (indeks < 1 || indeks > iloscObrazow) {
			printf("Nieprawidlowy numer obrazu. Podaj liczbe z zakresu od 1 do %d\n", iloscObrazow);
		}
	} while (indeks < 1 || indeks > iloscObrazow);
	return indeks;
}

void zamknijAktywnyObraz(struct ObrazekPGM* aktywnyObrazek, int* indeks)
{
	indeks = NULL;
	strcpy((*aktywnyObrazek).nazwaPliku, "Brak");
	(*aktywnyObrazek).skalaSzarosci = 0;
	(*aktywnyObrazek).szerokosc = 0;
	(*aktywnyObrazek).wysokosc = 0;
}

void eksportDoPGM(struct ObrazekPGM obrazek)
{
	char nazwa[20];
	char buf[30];
	bool equal;
	do
	{
		printf("Podaj nazwe pliku: ");
		scanf("%20s", nazwa);
		snprintf(buf, sizeof(nazwa) + 5, "%s.pgm", nazwa);
		equal = strcmp(obrazek.nazwaPliku, buf);
		if ( equal == 0 )
		{
			printf("\nTa sama nazwa co plik zrodlowy. Podaj unikatowa nazwe!");
		}
	} while (equal == 0);

	FILE* plik = fopen(buf, "w");

	if (plik != NULL)
	{
		fprintf(plik, "P2\n");
		fprintf(plik, "%d %d\n", obrazek.wysokosc, obrazek.szerokosc);
		fprintf(plik, "%d\n", obrazek.skalaSzarosci);
		for (int i = 0; i < obrazek.wysokosc; i++)
		{
			for (int j = 0; j < obrazek.szerokosc; j++)
			{
				fprintf(plik, "%d ", obrazek.piksele[i][j]);
			}
			fprintf(plik, "\n");
		}
		fclose(plik);
		printf("\nDane zosatly pomyslnie zapisane do pliku %s\n\n", buf);
	}
	else
	{
		printf("\nBlad otwarcia pliku.\n");
	}
	scanf("%*[^\n]");
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
		if (!(wyborMenu != 1 && galeriaJ.iloscObrazow == 0))
		{
			switch (wyborMenu) {
			case 1: // Pobierz nowy obraz z pliku do galerii  
				printf("\n");
				bool obrazWczytanyPoprawnie = wczytajObraz(&wczytanyObrazek);
				if (obrazWczytanyPoprawnie) dodajObrazDoGalerii(&galeriaJ, wczytanyObrazek);
				printf("\n");
				break;
			case 2: // Ustaw aktywny obraz
				if (galeriaJ.iloscObrazow > 0)
				{
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
					printf("XXXXXXXXX\n\n");
				}
				else printf("Brak obrazow w galerii. Dodaj nowy obraz.\n\n");
				break;
			case 3: // Przetwarzaj aktywny obraz
				if (indeksAktywnyObraz == 0)
				{
					printf("\nBrak wybranego aktywnego obrazu.\n");
				}
				else
				{
					przetwarzajAktywnyObraz(&aktywnyObrazek);
					// zapisz do galerii bez weryfikacji nazwy
					printf("Nazwa Pliku: %s\n", aktywnyObrazek.nazwaPliku);
					if (obrazWGalerii(&galeriaJ, aktywnyObrazek))
					{
						galeriaJ.obrazy[indeksAktywnyObraz - 1] = aktywnyObrazek;
						//nadpiszObrazWGalerii(&galeriaJ, &indeksAktywnyObraz, aktywnyObrazek);
					}
					else
					{
						dodajObrazDoGalerii(&galeriaJ, aktywnyObrazek);
					}
				}
				break;
			case 4: // Zamknij aktywny obraz 
				if (indeksAktywnyObraz == 0)
				{
					printf("\nBrak wybranego aktywnego obrazu.\n");
				}
				else
				{
					zamknijAktywnyObraz(&aktywnyObrazek, &indeksAktywnyObraz);
					printf("\n");
				}
				break;
			case 5: //export do pliku .pgm
				if (galeriaJ.iloscObrazow > 0)
				{
					wypiszNazwyObrazow(&galeriaJ);
					int eksportIndeks = wybierzDoEksportu(galeriaJ.iloscObrazow);
					eksportDoPGM(galeriaJ.obrazy[eksportIndeks - 1]);
				}
				break;
			case 6: // Usun obraz z galerii  
				wypiszNazwyObrazow(&galeriaJ);
				usunObrazZGalerii(&galeriaJ, &indeksUsunObraz);
				if (indeksAktywnyObraz == indeksUsunObraz)
				{
					zamknijAktywnyObraz(&aktywnyObrazek, &indeksAktywnyObraz);
				}
				printf("\n");
				break;
			case 7: // Zakoncz program  
				printf("Program zostal zakonczony.\n");
				printf("\n");
				break;
			default:
				printf("Nieprawidlowy wybor. Wybierz opcje od 1 do 7.\n");
				printf("\n");
				break;
			}
		}
		else if (wyborMenu != 7)
		{
			printf("\nBrak obrazow dodanych do Galerii.\nNajpier dodaj nowy obraz.\n\n");
		}
	} while (wyborMenu != 7);
	printf("\nDziekujemy za odwiedzienie Galerii \"J\".\nDo Zobaczenia.\n");
	// Na koniec zwolnij pamiêæ zaalokowan¹ dla tablicy pikseli
	return 0;
}

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