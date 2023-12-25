#ifndef _MAZE_H
#define _MAZE_H

struct cell {
    unsigned int in_maze : 1;
    unsigned int adjacents : 4;
};

struct adjacency {
    int* cell_ids;
    int length;
};

struct maze {
    int size;
    int ccnt;
    struct cell* cells;
    struct adjacency* adjacency_list;
};

int maze_init(struct maze* maze, char* mazesize);
int get_rnd_cell(struct maze maze);

#endif
