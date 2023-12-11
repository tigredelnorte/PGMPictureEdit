#include <cstdio>
#include <stdlib.h>
#include "ModeleDanych.h"
#include "ObrazReadWrite.h"

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