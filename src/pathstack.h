#ifndef _PATHSTACK_H
#define _PATHSTACK_H

/* struct node - pojedynczy element stosu
 *
 * Pola:
 *   - int val: wartość przechowywana przez element
 *   - struct node* next: wskaźnik na następny element stosu
 */
struct node {
    int val;
    struct node* next;
};

/* struct pathstack - stos wykorzystywany w zapisie ścieżek zarówno w
 * generowaniu, jak i rozwiązywaniu labiryntu
 *
 * Stos przystosowany jest do przechowywania liczb całkowitych >= 0, takich jak
 * id komórek w labiryncie.
 *
 * Pola:
 *   - struct node* head: element na górze stosu (najpóźniej dodany)
 */
struct pathstack {
    struct node* head;
};

/* stck_push - dodaje wartość na stos. Miejsce w pamięci alokowane jest ręcznie,
 * wartości należy usuwać ostrożnie lub korzystać z funkcji `stck_pop`
 *
 * Argumenty:
 *   - struct pathstack* stos: wskaźnik na stos
 *   - int val: wartość do dodania
 *
 * Zwraca int:
 *   - 0 jeśli poprawnie dodano wartość na stos
 *   - 1 jeśli wystąpił błąd podczas alokacji
 */
int stck_push(struct pathstack* stack, int val);

/* stck_pop - usuwa wartość z góry stosu. Wartość zostaje też dealokowana
 *
 * Argumenty:
 *   - struct pathstack* stack: wskaźnik na stos
 *
 * Zwraca int:
 *   - wartość usuniętą ze stosu
 *   - -1 jeśli stos jest pusty
 */
int stck_pop(struct pathstack* stack);

/* stck_clear - pustoszy stos, dealokując wszystkie dotychczasowe wartości */
void stck_clear(struct pathstack* stack);

/* stck_preview - podgląda wartość z góry stosu bez usuwania jej
 *
 * Argumenty:
 *   - struct pathstack* stack: wskaźnik na stos
 *
 * Zwraca int:
 *   - wartość na górze stosu
 *   - -1 jeśli stos jest pusty
 */
int stck_preview(struct pathstack* stack);

/* stck_search - sprawdza czy podana wartość jest już na stosie, iterując przez
 * stos
 *
 * Argumenty:
 *   - struct pathstack* stack: wskaźnik na stos
 *   - int val: poszukiwana wartość
 *
 * Zwraca:
 *   - 0 jeśli wartość nie znajduje się na stosie
 *   - 1 jeśli wartość znajduje się na stosie
 */
int stck_search(struct pathstack* stack, int val);

#endif
