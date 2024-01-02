#include <stdlib.h>

#include "mazesolve.h"

int count_b1s(int n) {
    int cnt = 0;
    while (n != 0) {
        n &= (n - 1);
        cnt++;
    }
    return cnt;
}

int adjlist_init(struct adj* adjlist, struct maze* maze) {
    int cid, j, k, adjs, len;

    for (cid = 0; cid < maze->ccnt; cid++) {
        adjs = maze->cells[cid].adjacents;
        len = count_b1s(adjs);

        adjlist[cid].visited = false;
        adjlist[cid].length = len;
        adjlist[cid].cell_ids = malloc(len * sizeof(int));
        if (adjlist[cid].cell_ids == NULL)
            return 1;

        k = 0;
        for (j = 0; j < DIRECTION_COUNT; j++) {
            if (((adjs >> j) & 1) == 0)
                continue;
            enum direction d = 1 << j;
            adjlist[cid].cell_ids[k++] =
                get_adj_cell(*maze, cid, d);
        }
    }

    return 0;
}

int visit_top_node(struct pathstack* pstack, struct adj* adjlist) {
    int cid = stck_pop(pstack);
    if (!adjlist[cid].visited) {
        adjlist[cid].visited = true;
        for (int i = 0; i < adjlist[cid].length; i++) {
            int adjcid = adjlist[cid].cell_ids[i];
            if (stck_push(pstack, adjcid) != 0)
                return 1;
        }
    }
    return 0;
}
