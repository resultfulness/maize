#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "help.h"
#include "maze.h"
#include "mazedisplay.h"
#include "mazegen.h"
#include "mazesolve.h"
#include "pathstack.h"

int main(int argc, char** argv) {
    srand(time(NULL));
    bool skip_gen = false;

    /* procesowanie argumentów wywołania */
    if (argc < 2) {
        fprintf(stderr,
                "%s: brak rozmiaru labiryntu\n"
                "w celu uzyskania więcej informacji wpisz '%s --help'\n",
                argv[0],
                argv[0]);
        return EXIT_FAILURE;
    }
    if (argc > 3) {
        fprintf(stderr,
                "%s: zbyt dużo argumentów\n"
                "w celu uzyskania więcej informacji wpisz '%s --help'\n",
                argv[0],
                argv[0]);
        return EXIT_FAILURE;
    }
    if (argc == 3) {
        if (strcmp(argv[2], "-s") == 0 ||
            strcmp(argv[2], "--skip-gen-drawing") == 0) {
            skip_gen = true;
        } else {
            fprintf(stderr,
                    "%s: niepoprawny argument: %s\n"
                    "w celu uzyskania więcej informacji wpisz '%s --help'\n",
                    argv[0],
                    argv[2],
                    argv[0]);
            return EXIT_FAILURE;
        }
    }
    if (strcmp(argv[1], "--help") == 0) {
        print_help(argv[0]);
        return EXIT_SUCCESS;
    }

    /* inicjalizacja struktur i zmiennych */
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

    struct cell* cells = maze->cells;
    int cid;
    cid = get_rnd_cell(*maze);
    cells[cid].in_maze = true;

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

    /* algorytm generowania labiryntu */
    while (are_all_cells_filled(*maze)) {
        if (!skip_gen) {
            clear_wndw(rndrr);
            draw_maze(rndrr, tileset, *maze);
        }

        /* komórka startowa */
        do {
            cid = get_rnd_cell(*maze);
        } while (cells[cid].in_maze);
        if (stck_push(pstack, cid) != 0) {
            fprintf(stderr, "%s: nie udało się alokować pamięci\n", argv[0]);
            return EXIT_FAILURE;
        }

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
                    if (!skip_gen)
                        draw_cell(rndrr, *maze, cid, "black");
                }
            }

            if (stck_push(pstack, adjcid) != 0) {
                fprintf(stderr,
                        "%s: nie udało się alokować pamięci\n",
                        argv[0]);
                return EXIT_FAILURE;
            }

            if (userexit()) {
                close_SDL(tileset, rndrr, wndw);
                free(maze->cells);
                free(maze);
                free(pstack);
                return EXIT_SUCCESS;
            }
            if (!skip_gen) {
                draw_cell(rndrr, *maze, adjcid, "grey");

                SDL_RenderPresent(rndrr);
                draw_maze(rndrr, tileset, *maze);
                SDL_Delay(DRAW_DELAY);
            }
        }

        /* aktualizacja labiryntu o nową ścieżkę */
        update_maze(maze, pstack);
    }

    /* konwersja na listę sąsiedztwa */
    maze->adjacency_list = malloc(maze->ccnt * sizeof(struct adjacency));
    if (maze->adjacency_list == NULL) {
        fprintf(stderr, "%s: nie udało się alokować pamięci\n", argv[0]);
        return EXIT_FAILURE;
    }
    if (init_mazeadj(maze) != 0) {
        fprintf(stderr,
                "%s: wystąpił błąd podczas tworzenia listy sąsiedztwa\n",
                argv[0]);
        return EXIT_FAILURE;
    }

    int startcid = rand() % maze->size;
    cells[startcid].adjacents += N;
    int endcid = maze->ccnt - rand() % maze->size - 1;
    cells[endcid].adjacents += S;

    /* rozwiązywanie labiryntu algorytmem DFS */
    while (stck_pop(pstack) != -1)
        ;
    if (stck_push(pstack, startcid) != 0) {
        fprintf(stderr, "%s: nie udało się alokować pamięci\n", argv[0]);
        return EXIT_FAILURE;
    }

    while (stck_preview(pstack) != -1) {
        if (visit_top_node(pstack, *maze) != 0) {
            fprintf(stderr, "%s: nie udało się alokować pamięci\n", argv[0]);
            return EXIT_FAILURE;
        }

        clear_wndw(rndrr);
        draw_maze(rndrr, tileset, *maze);
        SDL_RenderPresent(rndrr);
        SDL_Delay(DRAW_DELAY);

        if (maze->adjacency_list[endcid].visited)
            break;
    }

    /* wyświetlanie końcowe */
    while (!userexit()) {
        clear_wndw(rndrr);
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
