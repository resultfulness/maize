#ifndef _MAZESOLVE_H
#define _MAZESOLVE_H

#include "maze.h"
#include "mazegen.h"
#include "pathstack.h"
#include "queue.h"

/* struct adj - reprezentuje pojedynczy element (komórkę) listy sąsiedztwa
 *
 * Pola:
 *   - int* cell_ids: lista id sąsiadujących komórek
 *   - int length: długość listy sąsiadujących komórek
 *   - int parent: komórka z której 'wszedł' do komórki algorytm rozwiązywania
 *   labiryntu
 *   - bool visited: czy dana komórka została już rozpatrzona przez algorytm
 *   rozwiązywania labiryntu
 *   - double value: wartość komórki
 */
struct adj {
    int* cell_ids;
    int length;
    int parent;
    bool visited;
    double value;
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

/* bfs_visit_adj - część algorytmu rozwiązywującego labirynt. Odwiedza wszystkie
 * komórki sąsiądujące z podaną, które nie zostały jeszcze odwiedzone,
 * ustawiając ich pole `parent` na podaną. Następnie dodaje je do kolejki
 * do sprawdzenia później
 *
 * Argumenty:
 *   - int cid: komórka, której nieodwiedzeni sąsiedzi zostaną odwiedzeni
 *   - struct queue* queue: kolejka w której zapisani zostaną sąsiedzi
 *   - struct adj* adjlist: lista sąsiedztwa, w której działa algorytm
 *
 * Zwraca int:
 *   - 0 jeśli poprawnie przeprowadzono odwiedzenie
 *   - 1 jeśli wystąpił błąd alokacji podczas dodawania sąsiadów do kolejki
 */
int bfs_visit_adj(int cid, struct queue* queue, struct adj* adjlist);

#endif
