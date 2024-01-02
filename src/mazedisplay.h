#ifndef _MAZEDISPLAY_H
#define _MAZEDISPLAY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "maze.h"

#define WIN_TITLE "Maize 🌽"

/* TILE_SIZE - rozmiar pojedynczej wyświetlanej komórki, a także komórki
 * pobieranej z tilesetu */
#define TILE_SIZE 16

#define RES_DIR "res"
#define TILESET_SRC RES_DIR"/maze_tileset.png"

/* DRAW_DELAY - określa odstęp w czasie między klatkami */
#define DRAW_DELAY 50

#define RGBA_WHITE 255, 255, 255, 255
#define RGBA_DIMGREY 105, 105, 105, 255
#define RGBA_BLACK 0, 0, 0, 255

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
int init_SDL(SDL_Window** wndw, SDL_Renderer** rndrr, struct maze maze);

/* close_SDL - zamyka uchwyty do biblioteki SDL
 *
 * Argumenty:
 *   - SDL_Texture* texture: wskaźnik na teksturę do zamknięcia
 *   - SDL_Renderer* rndrr: wskaźnik na renderer do zamknięcia
 *   - SDL_Window* wndw: wskaźnik na okno do zamknięcia
 */
void close_SDL(SDL_Texture* texture,
               SDL_Renderer* rndrr,
               SDL_Window* wndw);

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
int load_texture(SDL_Renderer** rndrr, SDL_Texture** texture, char* img_src);

/* clear_wndw - wypełnia całą powierzchnię okna kolorem czarnym
 *
 * Argumenty:
 *   - SDL_Renderer* rndrr: wskaźnik na renderer do wykorzystania przy
 *   czyszczeniu
 */
void clear_wndw(SDL_Renderer* rndrr);

/* draw_maze - wyświetla labirynt w oknie. Wyświetla jedynie komórki dodane do
 * labiryntu w procesie jego generowania
 *
 * Argumenty:
 *   - SDL_Renderer* rndrr: wskaźnik renderer do wykorzystania przy wyświetlaniu
 *   - SDL_Texture* tileset: wskaźnik na teksturę z układem do wyświetlania
 *   labiryntu
 *   - struct maze maze: labirynt do wyświetlenia
 */
void draw_maze(SDL_Renderer* rndrr, SDL_Texture* tileset, struct maze maze);

/* draw_cell - koloruje pojedynczą komórkę na podany kolor. Możliwe kolory:
 *   - "black" - czarny (domyślny)
 *   - "grey" - szary
 * W przypadku podania innego koloru funkcja wykorzysta kolor domyślny
 *
 * Argumenty:
 *   - SDL_Renderer* rndrr: wskaźnik na wykorzystywany renderer
 *   - struct maze maze: labirynt w którym zostanie pokolorowana komórka
 *   - int cid: id komórki do pokolorowania
 *   - char* colour: nowy kolor komórki
 */
void draw_cell(SDL_Renderer* rndrr, struct maze maze, int cid, char* colour);

/* userexit - sprawdza czy użytkownik chce wyjść z programu. Funkcja sprawdza
 * czy użytkownik poprosił system operacyjny o wyjście lub nacisnął jeden z
 * klawiszy - `<ESC>` lub `Q`
 *
 * Zwraca int:
 *   - 0 jeśli użytkownik nie poprosił o wyjście
 *   - 1 jeśli użytkownik poprosił o wyjście z programu
 */
int userexit();

#endif
