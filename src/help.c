#include <stdio.h>

#include "help.h"

void print_help(char *scriptname) {
    printf("Użycie: %s ROZMIAR [OPCJE]\n", scriptname);

    fputs("\
Generuje losowy labirynt o wymiarach ROZMIAR na ROZMIAR.\n\
Z programu można wyjść w każdej chwili wciskając klawisz <ESC> lub Q.\n\
\n\
Możliwe OPCJE:\n\
  -s    nie wyświetlaj fazy generowania labiryntu (polecane dla ROZMIAR > 10,\n\
        w przeciwnym razie labirynt może generować się BARDZO długo).\n\
", stdout);
}
