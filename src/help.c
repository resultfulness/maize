#include <stdio.h>

#include "help.h"

void print_help(char *scriptname) {
    printf("Użycie: %s ROZMIAR [OPCJE]\n", scriptname);
    printf("Generuje losowy labirynt o wymiarach ROZMIAR na ROZMIAR.\n\n");

    printf("Możliwe OPCJE:\n");
    printf("  -s, --skip-gen-draw\tnie wyświetlaj fazy generowania labiryntu (polecane dla\n"
           "\t\t\tROZMIAR > 10, w przeciwnym razie labirynt może generować\n"
           "\t\t\tsię BARDZO długo).\n");
}
