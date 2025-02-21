#include "display.h"
#include "crossy.h"

const int entity_ID[LABEL_COUNT] ={
    CAR_LANE_LEFT + LABEL_COUNT,
    CAR_LANE_RIGHT + LABEL_COUNT,
    TRUCK_LANE_LEFT + LABEL_COUNT,
    TRUCK_LANE_RIGHT + LABEL_COUNT,
    RIVER_LEFT + LABEL_COUNT,
    RIVER_RIGHT + LABEL_COUNT,
    TRAIN_LEFT + LABEL_COUNT,
    TRAIN_RIGHT + LABEL_COUNT,
    SOLID_GROUND + LABEL_COUNT
};

const char* entity_chr[LABEL_COUNT] = {
    " ",    // car up
    " ",    // car down
    " ",    // truck up
    " ",    // truck down
    "=",    // log
    "=",    // log
    " ",    // train up
    " ",    // train down
    "%",    // tree
};

const char* surface_chr[LABEL_COUNT] = {
    " ",    // road
    " ",    // road
    " ",    // road
    " ",    // road
    "~",    // water
    "~",    // water
    "·",    // tracks
    "·",    // tracks
    "\"",   // grass
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
            attron(COLOR_PAIR(entity_ID[TO_ENTITY_INDEX(surface)]));
            printw("%s", entity_chr[TO_ENTITY_INDEX(surface)]);
            attroff(COLOR_PAIR(entity_ID[TO_ENTITY_INDEX(surface)]));
            //attroff(A_BOLD);
        }else{
            attron(COLOR_PAIR(surface));
            printw("%s", surface_chr[TO_ENTITY_INDEX(surface)]);
            attroff(COLOR_PAIR(surface));
        }
    }
}

void initColors(void){
    init_pair(SOLID_GROUND, COLOR_GREEN, COLOR_BLACK);
    init_pair(entity_ID[TO_ENTITY_INDEX(SOLID_GROUND)], COLOR_GREEN, COLOR_BLACK);

    init_pair(RIVER_RIGHT, COLOR_BLUE, COLOR_BLACK);
    init_pair(RIVER_LEFT, COLOR_BLUE, COLOR_BLACK);
    init_pair(entity_ID[TO_ENTITY_INDEX(RIVER_LEFT)], COLOR_BROWN, COLOR_BLACK);
    init_pair(entity_ID[TO_ENTITY_INDEX(RIVER_RIGHT)], COLOR_BROWN, COLOR_BLACK);
}

void printGame(gamestate* game, bool debug){
    erase();
    if (debug) printw("cln:%d, ln:%d; dth:%d\n", game->chicken % COLUMN_SIZE, game->chicken / COLUMN_SIZE, game->death);
    if (debug) printw("typ");
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
    if (debug) printw("   ");
    printHat(ACS_LLCORNER, ACS_LRCORNER);
    if(game->chicken!=AU_COIN) printw("score: %d\nPress 'q' to quit.", game->death);
}
