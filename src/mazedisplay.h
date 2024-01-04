#ifndef _MAZEDISPLAY_H
#define _MAZEDISPLAY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "maze.h"
#include "mazegen.h"
#include "mazesolve.h"

#define WIN_TITLE "Maize 🌽"

/* TILE_SIZE - rozmiar pojedynczej wyświetlanej komórki, a także komórki
 * pobieranej z tilesetu */
#define TILE_SIZE 16

/* LINE_SIZE - rozmiar linii pokazywanych podczas rozwiązywania labiryntu
 */
#define LINE_SIZE 8

/* ścieżka do tilesetu labiryntu */
#define RES_DIR "res"
#define TILESET_SRC RES_DIR "/maze_tileset.png"

/* DRAW_DELAY - określa odstęp w czasie między klatkami */
#define DRAW_DELAY 50

/* kolory wykorzystywane przez program */
#define RGBA_WHITE 255, 255, 255, 255
#define RGBA_DIMGREY 105, 105, 105, 255
#define RGBA_BLACK 0, 0, 0, 255
#define RGBA_ORANGERED 255, 69, 0, 255
#define RGBA_FORESTGREEN 34, 139, 34, 255
#define RGBA_PUREBLUE 0, 186, 255, 255

#define COLOUR_BACKGROUND RGBA_BLACK
#define COLOUR_GENERATION_PATH RGBA_DIMGREY
#define COLOUR_SOLVING_PATH RGBA_ORANGERED
#define COLOUR_CURRENT_SOLVING_PATH RGBA_PUREBLUE
#define COLOUR_FINAL_SOLUTION RGBA_FORESTGREEN

/* init_SDL - inicjalizuje okno biblioteki SDL o rozmiarze na podstawie rozmiaru
 * labiryntu
 *
 * Argumenty:
 *   - SDL_Window** wndw: okno w którym zainicjalizować bibliotekę
 *   - SDL_Renderer** rndrr: renderer wykorzystywany przez okno
 *   - struct maze maze: labirynt specyfikujący rozmiar okna
 *
 * Zwraca int:
 *   - 0 jeśli poprawnie zainicjalizowano okno
 *   - 1 jeśli wystąpił problem z inicjalizacją
 * */
int init_SDL(SDL_Window **wndw, SDL_Renderer **rndrr, struct maze maze);

/* close_SDL - zamyka uchwyty do biblioteki SDL
 *
 * Argumenty:
 *   - SDL_Texture* texture: wskaźnik na teksturę do zamknięcia
 *   - SDL_Renderer* rndrr: wskaźnik na renderer do zamknięcia
 *   - SDL_Window* wndw: wskaźnik na okno do zamknięcia
 */
void close_SDL(SDL_Texture *texture, SDL_Renderer *rndrr, SDL_Window *wndw);

/* load_texture - pobiera obraz z systemu plików do wykorzystania przez SDL jako
 * tekstura
 *
 * Argumenty:
 *   - SDL_Renderer** rndrr: renderer w kontekście którego załadowana będzie
 *   tekstura
 *   - SDL_Texture** texture: tekstura do której załadowany będzie obraz
 *   - char* img_src: ścieżka do obrazu
 *
 * Zwraca int:
 *   - 0 jeśli poprawnie załadowano teksturę
 *   - 1 jeśli wystąpił błąd ładowania obrazu
 */
int load_texture(SDL_Renderer **rndrr, SDL_Texture **texture, char *img_src);

/* clear_wndw - wypełnia całą powierzchnię okna kolorem tła
 *
 * Argumenty:
 *   - SDL_Renderer* rndrr: wskaźnik na renderer do wykorzystania przy
 *   czyszczeniu
 */
void clear_wndw(SDL_Renderer *rndrr);

/* draw_maze - wyświetla labirynt w oknie. Wyświetla jedynie komórki dodane do
 * labiryntu w procesie jego generowania
 *
 * Argumenty:
 *   - SDL_Renderer* rndrr: wskaźnik renderer do wykorzystania przy wyświetlaniu
 *   - SDL_Texture* tileset: wskaźnik na teksturę z układem do wyświetlania
 *   labiryntu
 *   - struct maze maze: labirynt do wyświetlenia
 */
void draw_maze(SDL_Renderer *rndrr, SDL_Texture *tileset, struct maze maze);

/* draw_cell - koloruje pojedynczą komórkę kolorem renderowania
 *
 * Argumenty:
 *   - SDL_Renderer* rndrr: wskaźnik na wykorzystywany renderer
 *   - struct maze maze: labirynt w którym zostanie pokolorowana komórka
 *   - int cid: id komórki do pokolorowania
 */
void draw_cell(SDL_Renderer *rndrr, struct maze maze, int cid);

/* userexit - sprawdza czy użytkownik chce wyjść z programu. Funkcja sprawdza
 * czy użytkownik poprosił system operacyjny o wyjście lub nacisnął jeden z
 * klawiszy - `<ESC>` lub `Q`
 *
 * Zwraca int:
 *   - 0 jeśli użytkownik nie poprosił o wyjście
 *   - 1 jeśli użytkownik poprosił o wyjście z programu
 */
int userexit();

/* get_con_rect - wytwarza obiekt `SDL_Rect`, który wyświetlony na labiryncie
 * połączy środek komórki pierwszej z drugą. Szerokość połączenia zależy od
 * `LINE_SIZE` oraz `TILE_SIZE`.
 *
 * Argumenty:
 *   - int cid1: pierwsza komórka do połączenia
 *   - int cid2: druga komórka do połączenia
 *   - struct maze maze: labirynt w którym zachodzi połączenie
 *
 * Zwraca SDL_Rect:
 *   - obiekt typu prostokąt biblioteki SDL
 */
SDL_Rect get_con_rect(int cid1, int cid2, struct maze maze);

/* draw_visited - zaznacza ścieżki odwiedzone przez algorytm rozwiązywania
 * labiryntu
 *
 * Argumenty:
 *   - SDL_Renderer* rndrr: wskaźnik na renderer do wykorzystania
 *   - struct maze maze: rozwiązywany labirynt
 *   - struct adj* adjlist: lista sąsiedztwa w której zapisywane są odwiedzenia
 */
void draw_visited(SDL_Renderer *rndrr, struct maze maze, struct adj *adjlist);

/* draw_until - zaznacza ścieżkę do komórki ze startu labiryntu, pozwalając
 * na wyświetlanie obecnie analizowanej przez algorytm ścieżki
 *
 * Argumenty:
 *   - SDL_Renderer* rndrr: wskaźnik na renderer do wykorzystania
 *   - struct maze maze: rozwiązywany labirynt
 *   - struct adj* adjlist: lista sąsiedztwa w której zapisywane są odwiedzenia
 *   - int until: do której komórki wyświetlana jest ścieżka
 */
void draw_until(SDL_Renderer* rndrr,
                struct maze maze,
                struct adj* adjlist,
                int until);

/* draw_solution - zaznacza końcowe rozwiązanie algorytmu, wykorzystując pole
 * `parent` elementów listy sąsiedztwa wypełnionych przez algorytm rozwiązywania
 * labiryntu
 *
 * Argumenty:
 *   - SDL_Renderer* rndrr: wskaźnik na renderer do wykorzystania
 *   - struct maze maze: rozwiązywany labirynt
 *   - struct adj* adjlist: lista sąsiedztwa z rozwiązaniem w postaci
 *   wypełnionych pół `parent` elementów
 *   - int endcid: id komórki będącej końcem rozwiązania (wyjściem z labiryntu)
 * */
void draw_solution(SDL_Renderer *rndrr, struct maze maze, struct adj *adjlist,
                   int endcid);

/* print_path - drukuje ścieżkę zapisaną w liście sąsiedztwa od pierwszej
 * komórki do drugiej oraz jej długość
 *
 * Argumenty:
 *   - int startcid: pierwsza komórka
 *   - int endcid: druga komórka
 *   - struct adj* adjlist: lista sąsiedztwa, w której zapisana jest ścieżka
 */
void print_path(int startcid, int endcid, struct adj* adjlist);

#endif
