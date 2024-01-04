#ifndef _QUEUE_H
#define _QUEUE_H

/* struct queue_node - pojedynczy element kolejki
 *
 * Pola:
 *   - int val: wartość przechowywana przez element
 *   - struct queue_node* prev: wskaźnik na poprzedni element kolejki
 *   - struct queue_node* next: wskaźnik na kolejny element kolejki
 */
struct queue_node {
    int val;
    struct queue_node* next;
    struct queue_node* prev;
};

/* struct queue - kolejka wykorzystywana w rozwiązywaniu labiryntu
 *
 * Kolejka przystosowana jest do przechowywania liczb całkowitych >= 0, takich
 * jak id komórek w labiryncie.
 *
 * Pola:
 *   - struct queue_node* head: element na górze kolejki (dodany najwcześniej)
 *   - struct queue_node* tail: element na dole kolejki (ostatnio dodany)
 *
 * */
struct queue {
    struct queue_node* head;
    struct queue_node* tail;
};

/* queue_enqueue - dodaje wartość do kolejki
 *
 * Argumenty:
 *   - struct queue* q: wskaźnik na kolejkę
 *   - int val: wartość do dodania
 *
 * Zwraca int:
 *   - 0 jeśli poprawnie zakolejkowano wartość
 *   - 1 jeśli wystąpił błąd podczas alokacji pamięci
 */
int queue_enqueue(struct queue* q, int val);

/* queue_dequeue - usuwa wartość z kolejki
 *
 * Argumenty:
 *   - struct queue* q; wskaźnik na kolejkę
 *
 * Zwraca int:
 *   - wartość usuniętą z kolejki
 *   - -1 jeśli kolejka jest pusta
 */
int queue_dequeue(struct queue* q);

#endif
