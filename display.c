#include <ncurses.h>
#include <stdlib.h>

#include "crossy.h"

void printHat(const chtype left, const chtype right){
    addch(left);
    for (int i = 0; i<COLUMN_SIZE-1; i++){
        addch(ACS_HLINE);
    }
    addch(right);
    printw("\n");
}

void printLine(gamestate* game, int line, enum lineLabel surface){
    for (int col = 1; col<COLUMN_SIZE; col ++){
        if (line*COLUMN_SIZE + col == game->chicken % GRID_SIZE){
            attron(A_BLINK);
            printw("@");
            attroff(A_BLINK);
            continue;
        }
        attron(COLOR_PAIR(surface));
        if (game->grid[line*COLUMN_SIZE + col] == 1){
            attron(A_BOLD);
            printw("%%");
            attroff(A_BOLD);
        }else{
            printw("\"");
        }
        attroff(COLOR_PAIR(surface));
    }
}

void printGame(gamestate* game){
    erase();
    printw("  ");
    printHat(ACS_ULCORNER, ACS_URCORNER);

    int iter = LINE_SIZE-1; // print all the lines
    for (int line = ((game->death % GRID_SIZE) + LINE_SIZE - 1) % LINE_SIZE; iter > 0; line--, iter--){
        if(line < 0){
            line = LINE_SIZE-1;
        }
        printw("%d ", game->grid[line*COLUMN_SIZE]);
        addch(ACS_VLINE);
        printLine(game, line, game->grid[line*COLUMN_SIZE]);
        addch(ACS_VLINE);
        printw("\n");
    }
    printw("  ");
    printHat(ACS_LLCORNER, ACS_LRCORNER);
    if(game->chicken!=AU_COIN) printw("score: %d\nPress 'q' to quit.", game->death);
}
