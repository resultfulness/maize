#include <stdlib.h>

#include "queue.h"

int queue_enqueue(struct queue *q, int val) {
    struct queue_node* n = malloc(sizeof(struct queue_node));
    if (n == NULL)
        return 1;
    n->val = val;
    if (q->tail == NULL) {
        /* kolejka jest pusta */
        n->next = NULL;
        n->prev = NULL;
        q->tail = n;
        q->head = n;
    } else {
        n->next = NULL;
        n->prev = q->tail;
        q->tail->next = n;
        q->tail = n;
    }

    return 0;
}

int queue_dequeue(struct queue *q) {
    struct queue_node* prev_head = q->head;
    if (prev_head == NULL)
        return -1;
    const int val = q->head->val;
    if (q->head->next == NULL) {
        /* po usunięciu kolejka będzie pusta */
        q->head = NULL;
        q->tail = NULL;
    } else {
        q->head = q->head->next;
        q->head->prev = NULL;
    }
    free(prev_head);
    return val;
}
