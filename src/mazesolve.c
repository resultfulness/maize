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
        adjlist[cid].parent = -1;
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

int bfs_visit_adj(int cid, struct queue* queue, struct adj* adjlist) {
    for (int i = 0; i < adjlist[cid].length; i++) {
        int adjcid = adjlist[cid].cell_ids[i];
        if (!adjlist[adjcid].visited) {
            adjlist[adjcid].visited = true;
            adjlist[adjcid].parent = cid;
            if (queue_enqueue(queue, adjcid) != 0)
                return 1;
        }
    }
    return 0;
}
