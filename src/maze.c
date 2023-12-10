#include <stdlib.h>
#include <string.h>

#include "maze.h"

int maze_init(struct maze* maze, char* mazesize) {
    char* endptr = NULL;
    maze->size = strtol(mazesize, &endptr, 10);
    maze->ccnt = maze->size * maze->size;

    int n_numeric_fnd = mazesize && *endptr != 0;

    if (maze->size <= 0 || n_numeric_fnd)
        return 1;

    return 0;
}

int get_rnd_cell(struct maze maze) {
    return rand() % maze.ccnt;
}

