#include "mazegen.h"

enum direction delta2dir(struct maze maze, int cid1, int cid2) {
    int delta = cid1 - cid2;
    enum direction d;

    if (delta == maze.size)
        d = N;
    if (delta == -maze.size)
        d = S;
    if (delta == 1)
        d = W;
    if (delta == -1)
        d = E;

    return d;
}

int dir2delta(struct maze maze, enum direction d) {
    int delta;

    if (d == N)
        delta = -maze.size;
    if (d == S)
        delta = maze.size;
    if (d == W)
        delta = -1;
    if (d == E)
        delta = 1;

    return delta;
}

int get_cell_allow_dirs(struct maze maze, int cid) {
    int mask = DIRECTION_BASE_MASK;

    if (cid < maze.size)
        mask -= N;
    if (cid >= maze.ccnt - maze.size)
        mask -= S;
    if (cid % maze.size == 0)
        mask -= W;
    if (cid % maze.size == maze.size - 1)
        mask -= E;

    return mask;
}

int get_adj_cell(struct maze maze, int cid, enum direction d) {
    d &= get_cell_allow_dirs(maze, cid);

    if (d == 0)
        return -1;

    return cid + dir2delta(maze, d);
}

int are_all_cells_filled(struct maze maze) {
    int i;
    for (i = 0; i < maze.ccnt; i++) {
        if (maze.cells[i].in_maze == 0)
            return 1;
    }
    return 0;
}

int adj_to_adjlist(struct maze *maze) {
    return 1;
    return 0;
}
