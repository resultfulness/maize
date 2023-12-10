#ifndef _MAZEGEN_H
#define _MAZEGEN_H

#include "maze.h"

enum direction {
    N = 8,
    E = 4,
    S = 2,
    W = 1
};
#define DIRECTION_COUNT 4
#define DIRECTION_BASE_MASK N+E+S+W

enum direction delta2dir(struct maze maze, int cid1, int cid2);
int dir2delta(struct maze maze, enum direction d);

int get_cell_allow_dirs(struct maze maze, int cid);

/* Funkcja get_adj_cell
 *
 * Funkcja przy podanym kierunku oraz id komórki sprawdza, czy możliwe jest
 * przejście z niej w podanym kierunku
 *
 * Argumenty:
 * - maze {struct maze}
 * - cid  {int}
 * - d    {enum direction}
 *
 * Zwraca:
 * id sąsiadującej komórki, lub -1, jeśli nie można iść w danym kierunku
 * (ściana labiryntu)
 */
int get_adj_cell(struct maze maze, int cid, enum direction d);
int are_all_cells_filled(struct maze maze);

#endif
