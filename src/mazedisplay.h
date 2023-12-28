#ifndef _MAZEDISPLAY_H
#define _MAZEDISPLAY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "maze.h"

#define TILE_SIZE 16
#define WIN_TITLE "Maize 🌽"
#define RES_DIR "res"
#define TILESET_SRC RES_DIR"/maze_tileset.png"

#define DRAW_DELAY 50

#define RGBA_WHITE 255, 255, 255, 255
#define RGBA_DIMGREY 105, 105, 105, 255
#define RGBA_BLACK 0, 0, 0, 255

int init_SDL(SDL_Window** wndw, SDL_Renderer** rndrr, struct maze maze);
void close_SDL(SDL_Texture* texture,
               SDL_Renderer* rndrr,
               SDL_Window* wndw);
int load_texture(SDL_Renderer** rndrr, SDL_Texture** texture, char* img_src);
void clear_wndw(SDL_Renderer* rndrr);
void draw_maze(SDL_Renderer* rndrr, SDL_Texture* tileset, struct maze maze);
void draw_cell(SDL_Renderer* rndrr, struct maze maze, int cid, char* colour);
int userexit();

#endif
