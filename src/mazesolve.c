#include "mazesolve.h"

int visit_top_node(struct pathstack* pstack, struct maze maze) {
    int cid = stck_pop(pstack);
    if (!maze.adjacency_list[cid].visited) {
        maze.adjacency_list[cid].visited = true;
        for (int i = 0; i < maze.adjacency_list[cid].length; i++) {
            int adjcid = maze.adjacency_list[cid].cell_ids[i];
            if (stck_push(pstack, adjcid) != 0)
                return 1;
        }
    }
    return 0;
}
