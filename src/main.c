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
#include "queue.h"

int main(int argc, char** argv) {
    int result = 0;
    bool skip_gen = false;

    /* procesowanie argumentów wywołania */
    if (argc < 2) {
        fprintf(stderr,
                "%s: brak rozmiaru labiryntu\n"
                "w celu uzyskania więcej informacji wpisz '%s --help'\n",
                argv[0],
                argv[0]);
        result = 1;
        goto out_nofree;
    }
    if (argc > 3) {
        fprintf(stderr,
                "%s: zbyt dużo argumentów\n"
                "w celu uzyskania więcej informacji wpisz '%s --help'\n",
                argv[0],
                argv[0]);
        result = 1;
        goto out_nofree;
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
            result = 1;
            goto out_nofree;
        }
    }
    if (strcmp(argv[1], "--help") == 0) {
        print_help(argv[0]);
        goto out_nofree;
    }

    /* inicjalizacja struktur i zmiennych */
    struct maze* maze = malloc(sizeof(struct maze));
    if (maze == NULL) {
        fprintf(stderr, "%s: nie udało się alokować pamięci\n", argv[0]);
        result = 1;
        goto out_nofree;
    }
    if(maze_init(maze, argv[1]) != 0) {
        fprintf(stderr,
                "%s: rozmiar labiryntu powinien być dodatnią liczbą całkowitą; "
                "otrzymano '%s'\n",
                argv[0],
                argv[1]);
        result = 1;
        goto out_free_maze;
    }
    maze->cells = calloc(maze->ccnt, sizeof(struct cell));
    if (maze->cells == NULL) {
        fprintf(stderr, "%s: nie udało się alokować pamięci\n", argv[0]);
        result = 1;
        goto out_free_maze;
    }

    srand(time(NULL));

    struct cell* cells = maze->cells;
    int cid;
    /* początkowo do labiryntu dodana zostaje losowa komórka */
    cid = get_rnd_cell(*maze);
    cells[cid].in_maze = true;

    enum direction d;
    struct pathstack* pstack = malloc(sizeof(struct pathstack));
    if (pstack == NULL) {
        fprintf(stderr, "%s: nie udało się alokować pamięci", argv[0]);
        result = 1;
        goto out_free_cells;
    }

    /* inicjalizacja okna */
    SDL_Window* wndw = NULL;
    SDL_Renderer* rndrr = NULL;
    SDL_Texture* tileset = NULL;
    if (init_SDL(&wndw, &rndrr, *maze) != 0) {
        result = 1;
        goto out_free_pstack;
    }
    if (load_texture(&rndrr, &tileset, TILESET_SRC) != 0) {
        result = 1;
        goto out_free_SDL;
    }

    /* algorytm generowania labiryntu */
    printf("%s: labirynt jest generowany...\n", argv[0]);
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
            result = 1;
            goto out_free_SDL;
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
                SDL_SetRenderDrawColor(rndrr, COLOUR_BACKGROUND);
                while ((cid = stck_pop(pstack)) != adjcid) {
                    if (!skip_gen)
                        draw_cell(rndrr, *maze, cid);
                }
            }

            if (stck_push(pstack, adjcid) != 0) {
                fprintf(stderr,
                        "%s: nie udało się alokować pamięci\n",
                        argv[0]);
                result = 1;
                goto out_free_SDL;
            }

            if (userexit())
                goto out_free_SDL;

            if (!skip_gen) {
                SDL_SetRenderDrawColor(rndrr, COLOUR_GENERATION_PATH);
                draw_cell(rndrr, *maze, adjcid);

                SDL_RenderPresent(rndrr);
                draw_maze(rndrr, tileset, *maze);
                SDL_Delay(DRAW_DELAY);
            }
        }

        /* aktualizacja labiryntu o nową ścieżkę */
        update_maze(maze, pstack);
    }

    /* konwersja na listę sąsiedztwa */
    struct adj* adjlist = malloc(maze->ccnt * sizeof(struct adj));
    if (adjlist == NULL) {
        fprintf(stderr, "%s: nie udało się alokować pamięci\n", argv[0]);
        result = 1;
        goto out_free_SDL;
    }
    if (adjlist_init(adjlist, maze) != 0) {
        fprintf(stderr,
                "%s: wystąpił błąd podczas tworzenia listy sąsiedztwa\n",
                argv[0]);
        result = 1;
        goto out_free_adjlist;
    }

    int startcid = rand() % maze->size;
    cells[startcid].adjacents += N;
    int endcid = maze->ccnt - rand() % maze->size - 1;
    cells[endcid].adjacents += S;

    printf("%s: labirynt wygenerowany pomyślnie\n", argv[0]);
    printf("%s: id komórki startowej: %i; końcowej: %i\n",
           argv[0],
           startcid,
           endcid);

    /* rozwiązywanie labiryntu algorytmem BFS */
    printf("%s: labirynt jest rozwiązywany...\n", argv[0]);
    struct queue* queue = malloc(sizeof(struct queue));
    if (queue == NULL) {
        fprintf(stderr, "%s: nie udało się alokować pamięci\n", argv[0]);
        result = 1;
        goto out_free_adjlist;
    }
    queue->head = NULL;
    queue->tail = NULL;

    adjlist[startcid].parent = startcid - maze->size;
    adjlist[startcid].visited = true;
    if (queue_enqueue(queue, startcid) != 0) {
        fprintf(stderr, "%s: nie udało się alokować pamięci\n", argv[0]);
        result = 1;
        goto out_free_queue;
    }

    printf("%s: algorytm odwiedza komórki [ id(wartość) ]:\n", argv[0]);
    while ((cid = queue_dequeue(queue)) != -1) {
        if (cid == endcid)
            break;
        /* dopóki kolejka nie jest pusta lub napotkana komórka jest końcowa */

        bfs_visit_adj(cid, queue, adjlist);

        clear_wndw(rndrr);
        draw_maze(rndrr, tileset, *maze);
        draw_visited(rndrr, *maze, adjlist);
        SDL_RenderPresent(rndrr);
        SDL_Delay(DRAW_DELAY * !skip_gen);
        if (userexit())
            goto out_free_queue;
    }

    printf("%s: znaleziono rozwiązanie, ścieżka:\n", argv[0]);
    fputs(" * ", stdout);
    print_path(startcid, endcid, adjlist);

    printf("\n%s: oczekiwanie na wyjście z programu...\n", argv[0]);
    /* wyświetlanie końcowe */
    while (!userexit()) {
        clear_wndw(rndrr);
        draw_maze(rndrr, tileset, *maze);
        draw_solution(rndrr, *maze, adjlist, endcid);
        SDL_RenderPresent(rndrr);
    }

out_free_queue:
    free(queue);

out_free_adjlist:
    for (int i = 0; i < maze->ccnt; i++) {
        if (adjlist[i].cell_ids)
            free(adjlist[i].cell_ids);
    }
    free(adjlist);

out_free_SDL:
    close_SDL(tileset, rndrr, wndw);

out_free_pstack:
    stck_clear(pstack);
    free(pstack);

out_free_cells:
    free(maze->cells);

out_free_maze:
    free(maze);

out_nofree:
    return result;
}
