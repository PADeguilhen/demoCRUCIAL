#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

#include "crossy.h"
#include "display.h"

int main(){
    srand(time(NULL));
    initscr();
    cbreak();
    //nodelay(stdscr, true);
    noecho();
    keypad(stdscr, TRUE);
    start_color();
    use_default_colors();

    init_pair(SOLID_GROUND, COLOR_GREEN, COLOR_BLACK);

    init_pair(RIVER_DOWN, COLOR_BLUE, COLOR_BLACK);
    init_pair(RIVER_UP, COLOR_BLUE, COLOR_BLACK);

    //init_pair(666, COLOR_WHITE, COLOR_BLACK);

    gamestate* game = initGame();

    printGame(game);
    
    time_t t1 = time(NULL);
    time_t t2;
    int frame_cpt = 0;
    int oldPos;
    char c;
    while((c = getch()) != 'q') { // change logic for frame generation
        oldPos = game->chicken;
        update_game_tic(game);
        switch (c) {
        case 3:
            updateChicken(game, UP);
            break;
        case 2:
            updateChicken(game, DOWN);
            break;
        case 4:
            updateChicken(game, LEFT);
            break;
        case 5:
            updateChicken(game, RIGHT);
            break; 
        case 'q': // end of game.
            break;
        }
        frame_cpt ++;
        if(game->chicken == AU_COIN){ // end of game the chicken is au coin
            do{
                printGame(game);
                printw("you have lost. GG!\nPress 'q' to quit.\n");
            } while ((c = getch()) != 'q');
            break;
        }
        printGame(game);
        t1 = t2;
    }

    endwin();
    deleteGame(game);
}
