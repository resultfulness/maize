#ifndef _PATHSTACK_H
#define _PATHSTACK_H

struct node {
    int val;
    struct node* next;
};

struct pathstack {
    struct node* head;
    struct node* tail;
};

int stck_push(struct pathstack* stack, int val);
int stck_pop(struct pathstack* stack);
int stck_preview(struct pathstack* stack);
int stck_search(struct pathstack* stack, int val);
int stck_len(struct pathstack* stack);

#endif
