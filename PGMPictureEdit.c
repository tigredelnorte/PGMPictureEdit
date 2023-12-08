#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

// Struktura przechowujπca informacje o obrazku PGM
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
    while (fgets(linia, sizeof(linia), plik) != NULL) {
        if (!(linia[0] == '#'))
        {
            break; // Jeúli linia nie jest komentarzem, przerywamy pÍtlÍ
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
            break; // Jeúli linia nie jest komentarzem, przerywamy pÍtlÍ
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
                char* ptr = linia; // Ustawienie wskaünika pomocniczego na poczπtku linii
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

void dodajObrazDoGalerii(struct Galeria** galeria, struct ObrazekPGM obraz)
{
    //dodawanie
    //(*galeria)->obrazy = (struct ObrazekPGM*)realloc((*galeria)->obrazy, ((*galeria)->iloscObrazow + 1) * sizeof(struct ObrazekPGM));
    //if ((*galeria)->obrazy != NULL)
    //{
    //    //tablica struktury i zmienna strukturalna
    //    (*galeria)->obrazy[(*galeria)->iloscObrazow] = obraz;
    //    (*galeria)->iloscObrazow += 1;
    //}
    //zabezpieczyc realloc
}

int main() {
    char gwiazdki[] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
    char star = '*';
    char spacja = ' ';
    int wyborMenu = 0;

    struct ObrazekPGM wczytanyObrazek;
    struct Galeria* galeriaJ;
    //struct (*galeria) nowa(*galeria);
    //struct (*galeria) (*galeria)ObrazowPrzetworzonych;


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

            printf("XXXXXXXXX\n");
            for (int i = 0; i < wczytanyObrazek.wysokosc; i++) {
                for (int j = 0; j < wczytanyObrazek.szerokosc; j++) {
                    printf("%d ", wczytanyObrazek.piksele[i][j]);
                }
                printf("\n");
            }
            printf("XXXXXXXXX\n");
            //dodajObrazDoGalerii(&galeriaJ, wczytanyObrazek);
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
    // Moøesz uøyÊ wczytanyObrazek.piksele do dostÍpu do wartoúci pikseli

    // Na koniec zwolnij pamiÍÊ zaalokowanπ dla tablicy pikseli
    return 0;
}