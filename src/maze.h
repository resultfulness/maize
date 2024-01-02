#ifndef _MAZE_H
#define _MAZE_H

#include <stdbool.h>

/* struct cell - reprezentuje pojedynczą komórkę labiryntu
 *
 * Pola:
 *   - bool in_maze: informuje o tym, czy dana komórka została dodana do
 *   labiryntu w procesie jego generowania
 *   - unsigned int adjacents (4): 4-bitowa wartość, opisująca z którymi
 *   pobliskimi komórkami połączona jest komórka; patrz: `enum direction`
 */
struct cell {
    bool in_maze;
    unsigned int adjacents : 4;
};

/* struct maze - reprezentuje labirynt
 *
 * Pola:
 *   - int size: szerokość (wysokość) labiryntu
 *   - int ccnt: liczba komórek w labiryncie
 *   - struct cell* cells: lista komórek labiryntu
 */
struct maze {
    int size;
    int ccnt;
    struct cell* cells;
};

/* maze_init - wypełnia pola `size` oraz `ccnt` labiryntu, wykorzystując
 * podany rozmiar w postaci ciągu znaków
 *
 * Argumenty:
 *   - struct maze* maze: wskaźnik na labirynt
 *   - char* mazesize: rozmiar labiryntu w postaci ciągu znaków
 *
 * Zwraca int:
 *   - 0 jeśli podany ciąg znaków zinterpretowano jako liczbę całkowitą > 0
 *   - 1 jeśli podanego ciągu znaków nie można było zinterpretować jako liczba
 *  całkowita < 0
 * */
int maze_init(struct maze* maze, char* mazesize);

/* get_rnd_cell - wybiera id losowej komórki labiryntu
 *
 * Argumenty:
 *   - struct maze maze: labirynt z którego wybrane jest id komórki
 *
 * Zwraca int:
 *   - losowe id komórki labiryntu
 * */
int get_rnd_cell(struct maze maze);

#endif
