#include <stdio.h>

#include "help.h"

void print_help(char *scriptname) {
    printf("Użycie: %s ROZMIAR [OPCJE]\n", scriptname);
    printf("Generuje losowy labirynt o wymiarach ROZMIAR na ROZMIAR.\n\n");

    printf("Możliwe OPCJE:\n");
    printf("  -s, --skip-gen\tnie wyświetlaj fazy generowania labiryntu (polecane dla\n\t\t\tROZMIAR > 10, w przeciwnym razie labirynt generuje się\n\t\t\tBARDZO długo)\n");
}
