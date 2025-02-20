#include "display.h"
#include "crossy.h"

const int entity_ID[LABEL_COUNT] ={
    11*CAR_LANE_UP,
    11*CAR_LANE_DOWN,
    11*TRUCK_LANE_UP,
    11*TRUCK_LANE_DOWN,
    11*RIVER_UP,
    11*RIVER_DOWN,
    11*TRAIN_UP,
    11*TRAIN_DOWN,
    11*SOLID_GROUND
};


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
        
        if (game->grid[line*COLUMN_SIZE + col] == 1){
            //attron(A_BOLD);
            attron(COLOR_PAIR(entity_ID[surface]));
            printw("%%");
            attroff(COLOR_PAIR(entity_ID[surface]));
            //attroff(A_BOLD);
        }else{
            attron(COLOR_PAIR(surface));
            printw("\"");
            attroff(COLOR_PAIR(surface));
        }
    }
}

void initColors(void){
    init_pair(SOLID_GROUND, COLOR_GREEN, COLOR_BLACK);
    init_pair(entity_ID[SOLID_GROUND], COLOR_GREEN, COLOR_BLACK);

    init_pair(RIVER_DOWN, COLOR_BLUE, COLOR_BLACK);
    init_pair(RIVER_UP, COLOR_BLUE, COLOR_BLACK);
    init_pair(entity_ID[RIVER_UP], COLOR_BROWN, COLOR_BLACK);
    init_pair(entity_ID[RIVER_DOWN], COLOR_BROWN, COLOR_BLACK);
}

void printGame(gamestate* game, bool debug){
    erase();
    if (debug) printw("cln:%d, ln:%d; dth:%d\n", game->chicken % COLUMN_SIZE, game->chicken / COLUMN_SIZE, game->death);
    if (debug) printw("  ");
    printHat(ACS_ULCORNER, ACS_URCORNER);

    int iter = LINE_SIZE-1; // print all the lines
    for (int line = ((game->death % GRID_SIZE) + LINE_SIZE - 1) % LINE_SIZE; iter > 0; line--, iter--){
        if(line < 0){
            line = LINE_SIZE-1;
        }
        if (debug) printw("%d ", game->grid[line*COLUMN_SIZE]);
        addch(ACS_VLINE);
        printLine(game, line, game->grid[line*COLUMN_SIZE]);
        addch(ACS_VLINE);
        printw("\n");
    }
    if (debug) printw("  ");
    printHat(ACS_LLCORNER, ACS_LRCORNER);
    if(game->chicken!=AU_COIN) printw("score: %d\nPress 'q' to quit.", game->death);
}
