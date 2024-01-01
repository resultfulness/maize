#include <stdlib.h>

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
        if (!maze.cells[i].in_maze)
            return 1;
    }
    return 0;
}

void update_maze(struct maze* maze, struct pathstack* pstack) {
    int cid, prevcid;
    prevcid = -1;
    while ((cid = stck_pop(pstack)) != -1) {
        maze->cells[cid].in_maze = true;
        if (prevcid == -1) {
            prevcid = cid;
            continue;
        }
        maze->cells[cid].adjacents += delta2dir(*maze, cid, prevcid);
        maze->cells[prevcid].adjacents += delta2dir(*maze, prevcid, cid);
        prevcid = cid;
    }
}

int count_b1s(int n) {
    int cnt = 0;
    while (n != 0) {
        n &= (n - 1);
        cnt++;
    }
    return cnt;
}

int init_mazeadj(struct maze* maze) {
    int cid, j, k, adjs, len;

    for (cid = 0; cid < maze->ccnt; cid++) {
        adjs = maze->cells[cid].adjacents;
        len = count_b1s(adjs);

        maze->adjacency_list[cid].visited = false;
        maze->adjacency_list[cid].length = len;
        maze->adjacency_list[cid].cell_ids = malloc(len * sizeof(int));
        if (maze->adjacency_list[cid].cell_ids == NULL)
            return 1;

        k = 0;
        for (j = 0; j < DIRECTION_COUNT; j++) {
            if (((adjs >> j) & 1) == 0)
                continue;
            enum direction d = 1 << j;
            maze->adjacency_list[cid].cell_ids[k++] =
                get_adj_cell(*maze, cid, d);
        }
    }

    return 0;
}
