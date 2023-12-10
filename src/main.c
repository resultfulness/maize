#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "help.h"
#include "maze.h"
#include "mazedisplay.h"
#include "mazegen.h"
#include "pathstack.h"

int main(int argc, char** argv) {
    srand(time(NULL));

    /* procesowanie argumentów wywołania */
    if (argc < 2) {
        fprintf(stderr,
                "%s: brak rozmiaru labiryntu\n"
                "w celu uzyskania więcej informacji wpisz '%s --help'\n",
                argv[0],
                argv[0]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "--help") == 0) {
        print_help(argv[0]);
        return EXIT_SUCCESS;
    }

    struct maze* maze = malloc(sizeof(struct maze));
    if (maze == NULL) {
        fprintf(stderr, "%s: nie udało się alokować pamięci\n", argv[0]);
        return EXIT_FAILURE;
    }
    if(maze_init(maze, argv[1]) != 0) {
        fprintf(stderr,
                "%s: rozmiar labiryntu powinien być dodatnią liczbą całkowitą; "
                "otrzymano '%s'\n",
                argv[0],
                argv[1]);
        return EXIT_FAILURE;
    }
    maze->cells = calloc(maze->ccnt, sizeof(struct cell));
    if (maze->cells == NULL) {
        fprintf(stderr, "%s: nie udało się alokować pamięci\n", argv[0]);
        return EXIT_FAILURE;
    }


    /* definicje zmiennych do algorytmu */
    struct cell* cells = maze->cells;
    int cid, x, y;
    cid = get_rnd_cell(*maze);
    cells[cid].in_maze = 1;

    enum direction d;
    struct pathstack* pstack = malloc(sizeof(struct pathstack));

    /* inicjalizacja okna */
    SDL_Window* wndw = NULL;
    SDL_Renderer* rndrr = NULL;
    SDL_Texture* tileset = NULL;
    if (init_SDL(&wndw, &rndrr, *maze) != 0) {
        return EXIT_FAILURE;
    }
    if (load_texture(&rndrr, &tileset, TILESET_SRC) != 0) {
        close_SDL(tileset, rndrr, wndw);
        return EXIT_FAILURE;
    }

    /* generowanie labiryntu */
    while (are_all_cells_filled(*maze)) {
        SDL_SetRenderDrawColor(rndrr, 0, 0, 0, 255);
        SDL_RenderClear(rndrr);
        draw_maze(rndrr, tileset, *maze);

        /* komórka startowa */
        do {
            cid = get_rnd_cell(*maze);
        } while (cells[cid].in_maze);
        stck_push(pstack, cid);

        /* ścieżka z komórki startowej do dowolnej w labiryncie */
        while (!cells[stck_preview(pstack)].in_maze) {
            d = 1 << (rand() % DIRECTION_COUNT);

            int adjcid = get_adj_cell(*maze, stck_preview(pstack), d);

            int moving_into_wall = adjcid == -1;
            if (moving_into_wall)
                continue;

            int cell_already_walked = stck_search(pstack, adjcid) == 1; 
            if (cell_already_walked) { 
                while ((cid = stck_pop(pstack)) != adjcid) {
                    x = (cid % maze->size) * TILE_SIZE;
                    y = (cid / maze->size) * TILE_SIZE;

                    SDL_Rect rect = { x, y, TILE_SIZE, TILE_SIZE };

                    SDL_SetRenderDrawColor(rndrr, 0, 0, 0, 255);
                    SDL_RenderFillRect(rndrr, &rect);
                }
            }

            stck_push(pstack, adjcid);

            x = (adjcid % maze->size) * TILE_SIZE;
            y = (adjcid / maze->size) * TILE_SIZE;

            SDL_Rect rect = { x, y, TILE_SIZE, TILE_SIZE };

            SDL_SetRenderDrawColor(rndrr, 33, 33, 33, 255);
            SDL_RenderFillRect(rndrr, &rect);

            SDL_RenderPresent(rndrr);
            draw_maze(rndrr, tileset, *maze);
            SDL_Delay(DRAW_DELAY);
        }

        /* aktualizacja labiryntu o nową ścieżkę */
        int prevcid = -1;
        while ((cid = stck_pop(pstack)) != -1) {
            cells[cid].in_maze = 1;
            if (prevcid == -1) { 
                prevcid = cid;
                continue;
            }
            cells[cid].adjacents += delta2dir(*maze, cid, prevcid);
            cells[prevcid].adjacents += delta2dir(*maze, prevcid, cid);
            prevcid = cid;
        }
    }

    /* komórka początkowa i końcowa */
    cells[0].adjacents += N;
    cells[maze->ccnt - 1].adjacents += S;
    
    /* maze->adjacency_list = malloc(maze->ccnt * sizeof(int*));
    if (adj_to_adjlist(maze) != 0) {
        fprintf(stderr, "%s: nie udało się alokować pamięci\n", argv[0]);
        return EXIT_FAILURE;
    };
    */

    int quit = 0;

    while (!quit) {
        check_for_exit(&quit);
        
        SDL_SetRenderDrawColor(rndrr, 0, 0, 0, 255);
        SDL_RenderClear(rndrr);

        draw_maze(rndrr, tileset, *maze);

        SDL_RenderPresent(rndrr);
    }

    /* czyszczenie */
    free(maze->adjacency_list);
    free(maze->cells);
    free(maze);
    free(pstack);

    close_SDL(tileset, rndrr, wndw);

    return EXIT_SUCCESS;
}
