#ifndef _MAZESOLVE_H
#define _MAZESOLVE_H

#include "maze.h"
#include "mazegen.h"
#include "pathstack.h"

/* struct adj - reprezentuje pojedynczy element (komórkę) listy
 * sąsiedztwa
 *
 * Pola:
 *   - int* cell_ids: lista id sąsiadujących komórek
 *   - int length: długość listy sąsiadujących komórek
 *   - bool visited: czy dana komórka została już rozpatrzona przez algorytm
 *   rozwiązywania algorytmu
 */
struct adj {
    int* cell_ids;
    int length;
    bool visited;
};

/* count_b1s - zlicza jedynki występujące w reprezentacji binarnej liczby,
 * iterując przez wszystkie bity reprezentacji binarnej liczby
 *
 * Argumenty:
 *   - int n: liczba w której zliczane są jedynki
 *
 * Zwraca int:
 *   - liczbę jedynek w reprezentacji binarnej podanej liczby
 */
int count_b1s(int n);

/* init_mazeadj - wypełnia listę sąsiedztwa na podstawie wygenerowanego
 * labiryntu. Podczas wypełniania w każdym elemencie listy pole `cell_ids` jest
 * alokowane ręcznie.
 *
 * Argumenty:
 *   - struct adj* adjlist: lista sąsiedztwa
 *   - struct maze* maze: wskaźnik na wygenerowany labirynt
 *
 * Zwraca int:
 *   - 0 jeśli wytworzono listę sąsiedztwa bez problemów
 *   - 1 jeśli wystąpił błąd alokacji
 */
int adjlist_init(struct adj* adjlist, struct maze* maze);

/* visit_top_node - odwiedza górę stosu, usuwając ją ze stosu, oznaczając
 * komórkę jako odwiedzoną, i dodając wszystkie sąsiadujące komórki na stos
 *
 * Argumenty:
 *   - struct pathstack* pstack: wskaźnik na stos
 *   - struct adj* adjlist: lista sąsiedztwa, w której oznaczane są odwiedzenia i z
 *   której pobierane są sąsiadujące komórki
 *
 * Zwraca:
 *   - 0 jeśli poprawnie dodano sąsiadujące komórki na stos
 *   - 1 jeśli wystąpił błąd w dodawaniu komórek na stos
 */
int visit_top_node(struct pathstack* pstack, struct adj* adjlist);

#endif
