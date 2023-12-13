#ifndef _MAZE_H
#define _MAZE_H

#include <stdbool.h>

struct cell {
    bool in_maze;
    unsigned int adjacents : 4;
};

struct maze {
    int size;
    int ccnt;
    struct cell* cells;
    int** adjacency_list;
};

int maze_init(struct maze* maze, char* mazesize);
int get_rnd_cell(struct maze maze);

#endif
