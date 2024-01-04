#ifndef _MAZEGEN_H
#define _MAZEGEN_H

#include "datastructures/pathstack.h"
#include "maze.h"

/* enum direction - reprezentuje kierunki wykorzystywane podczas generowania
 * labiryntu
 */
enum direction {
    N = 8, /* 0b1000 */
    E = 4, /* 0b0100 */
    S = 2, /* 0b0010 */
    W = 1  /* 0b0001 */
};

/* DIRECTION_COUNT - liczba pól `enum direction` */
#define DIRECTION_COUNT 4

/* DIRECTION_BASE_MASK - suma pól `enum direction`, wykorzystywana jako maska
 * podstawowa podczas ograniczania labiryntu ścianami
 */
#define DIRECTION_BASE_MASK N+E+S+W

/* delta2dir - zamienia różnicę w id dwóch komórek na kierunek potrzebny, by
 * przejść z pierwszej komórki do drugiej
 *
 * Argumenty:
 *   - struct maze maze: labirynt w którym badana jest różnica
 *   - int cid1: id komórki pierwszej
 *   - int cid2: id komórki drugiej
 *
 * Zwraca enum direction:
 *   - kierunek potrzebny do przejścia z pierwszej do drugiej komórki
 */
enum direction delta2dir(struct maze maze, int cid1, int cid2);

/* dir2delta - zamienia kierunek na różnicę w id komórek
 *
 * Argumenty:
 *   - struct maze maze: labirynt, w którym badany jest kierunek
 *   - enum direction d: badany kierunek
 *
 * Zwraca int
 *   - różnicę w id, która odpowiada przejściu w danym kierunku
 */
int dir2delta(struct maze maze, enum direction d);

/* get_adj_cell - sprawdza, na co napotka algorytm w wypadku poruszenia się
 * z danej komórki w danym kierunku
 *
 * Argumenty:
 *   - struct maze maze: labirynt w którym badane jest przejście
 *   - int cid: id badanej komórki
 *   - enum direction d: kierunek w którym nastąpić ma przejście
 *
 * Zwraca int:
 *   - id sasiadującej komórki jeśli nie napotkano ściany
 *   - -1 jeśli napotkano ścianę labiryntu
 */
int get_adj_cell(struct maze maze, int cid, enum direction d);

/* are_all_cells_filled - sprawdza, czy wszystkie komórki labiryntu zostały
 * przydzielone do ścieżek, iterując przez wszystkie komórki
 *
 * Argumenty:
 *   - struct maze maze: sprawdzany labirynt
 *
 * Zwraca int:
 *   - 1 jeśli napotkano komórkę nieprzydzieloną do ścieżki
 *   - 0 jeśli generowanie labiryntu zakończyło się
 */
int are_all_cells_filled(struct maze maze);

/* update_maze - aktualizuje labirynt o podaną ścieżkę, przełączając pola
 * `in_maze` komórek znajdujących się na stosie i aktualizując ich sąsiedztwa
 * w polu `adjacents`. Wykonanie funkcji spowoduje opustoszenie podanego jako
 * argument stosu.
 *
 * Argumenty:
 *   - struct maze* maze: wskaźnik na aktualizowany labirynt
 *   - struct pathstack* pstack: wskaźnik na stos ze ścieżką do dodania
 */
void update_maze(struct maze* maze, struct pathstack* pstack);

#endif
