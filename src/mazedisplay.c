#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#include "mazedisplay.h"

int init_SDL(SDL_Window** wndw, SDL_Renderer** rndrr, struct maze maze) {
    const int SCREEN_WIDTH = TILE_SIZE * maze.size;
    const int SCREEN_HEIGHT = TILE_SIZE * maze.size;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr,
                "Błąd SDL_Init: %s\n",
                SDL_GetError());
        return 1;
    }

    *wndw = SDL_CreateWindow(WIN_TITLE,
                            SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED,
                            SCREEN_WIDTH,
                            SCREEN_HEIGHT,
                            SDL_WINDOW_SHOWN);
    if (wndw == NULL) {
        fprintf(stderr, "Błąd SDL_CreateWindow: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    *rndrr = SDL_CreateRenderer(*wndw,
                               -1,
                               SDL_RENDERER_ACCELERATED |
                               SDL_RENDERER_PRESENTVSYNC);
    if (rndrr == NULL) {
        fprintf(stderr, "Błąd SDL_CreateRenderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(*wndw);
        SDL_Quit();
        return 1;
    }

    return 0;
}

void close_SDL(SDL_Texture* texture, SDL_Renderer* rndrr, SDL_Window* wndw) {
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(rndrr);
    SDL_DestroyWindow(wndw);
    SDL_Quit();
}

int load_texture(SDL_Renderer** rndrr, SDL_Texture** texture, char* img_src) {
    SDL_Surface* texture_srfc = IMG_Load(img_src);
    if (texture_srfc == NULL) {
        fprintf(stderr, "Błąd IMG_Load: %s\n", IMG_GetError());
        return 1;
    }

    *texture = SDL_CreateTextureFromSurface(*rndrr, texture_srfc);
    SDL_FreeSurface(texture_srfc);

    if (*texture == NULL) {
        return 1;
    }

    return 0;
}

void clear_wndw(SDL_Renderer* rndrr) {
    SDL_SetRenderDrawColor(rndrr, RGBA_BLACK);
    SDL_RenderClear(rndrr);
}

void draw_maze(SDL_Renderer* rndrr, SDL_Texture* tileset, struct maze maze) {
    int i;
    for (i = 0; i < maze.ccnt; i++) {
        struct cell c = maze.cells[i];
        if (!c.in_maze)
            continue;
        const int src_offset_x = (c.adjacents % 4) * TILE_SIZE;
        const int src_offset_y = (c.adjacents / 4) * TILE_SIZE;
        const int dest_offset_x = (i % maze.size) * TILE_SIZE;
        const int dest_offset_y = (i / maze.size) * TILE_SIZE;
        const SDL_Rect src = { src_offset_x, src_offset_y, TILE_SIZE, TILE_SIZE };
        const SDL_Rect dest = { dest_offset_x, dest_offset_y, TILE_SIZE, TILE_SIZE };
        SDL_RenderCopy(rndrr, tileset, &src, &dest);
    }
}

void draw_cell(SDL_Renderer *rndrr, struct maze maze, int cid, char *colour) {
    int x, y;
    x = (cid % maze.size) * TILE_SIZE;
    y = (cid / maze.size) * TILE_SIZE;

    SDL_Rect rect = { x, y, TILE_SIZE, TILE_SIZE };

    if (strcmp(colour, "black") == 0) {
        SDL_SetRenderDrawColor(rndrr, RGBA_BLACK);
    } else if (strcmp(colour, "grey") == 0) {
        SDL_SetRenderDrawColor(rndrr, RGBA_DIMGREY);
    } else {
        SDL_SetRenderDrawColor(rndrr, RGBA_BLACK);
    }

    SDL_RenderFillRect(rndrr, &rect);
}

int userexit() {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            return 1;
        } else if (e.type == SDL_KEYDOWN) {
            if (e.key.keysym.sym == SDLK_ESCAPE ||
                e.key.keysym.sym == SDLK_q) {
                return 1;
            }
        }
    }
    return 0;
}

