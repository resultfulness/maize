#include <stdio.h>
#include <stdlib.h>

#include "pathstack.h"

int stck_push(struct pathstack* stack, int val) {
    struct node* n = malloc(sizeof(struct node));
    if (n == NULL)
        return 1;
    n->val = val;
    n->next = stack->head;
    stack->head = n;

    return 0;
}

int stck_pop(struct pathstack* stack) {
    if (stack->head == NULL)
        return -1;

    struct node* prev_head = stack->head;
    const int val = prev_head->val;
    stack->head = prev_head->next;
    free(prev_head);
    return val;
}

void stck_clear(struct pathstack *stack) {
    while (stck_pop(stack) != -1)
        ;
}

int stck_preview(struct pathstack* stack) {
    if (stack->head == NULL)
        return -1;
    return stack->head->val;
}

int stck_search(struct pathstack* stack, int val) {
    struct node* n = stack->head;

    while (n != NULL) {
        if (n->val == val)
            return 1;
        n = n->next;
    }
    return 0;
}
