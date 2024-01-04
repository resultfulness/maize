#include <stdio.h>

#include "help.h"

void print_help(char *scriptname) {
    printf("Użycie: %s ROZMIAR [OPCJE]\n", scriptname);

    fputs("\
Generuje losowy labirynt o wymiarach ROZMIAR na ROZMIAR.\n\
Z programu można wyjść w każdej chwili wciskając klawisz <ESC> lub Q.\n\
\n\
Możliwe OPCJE:\n\
  -s    wyświetlaj rozwiązywanie labiryntu tak szybko jak to możliwe (odstęp\n\
        między klatkami = 0) i pomiń wyświetlanie generowania labiryntu:\n\
        polecane jeśli ROZMIAR > 10\n\
", stdout);
}
