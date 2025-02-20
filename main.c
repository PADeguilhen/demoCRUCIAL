#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

#include "crossy.h"
#include "display.h"

int main(int argc, char* argv[]){
    bool debug = false;

    if (argc > 1 && strcmp(argv[1], "debug") == 0) debug = true;

    srand(time(NULL));
    initscr();
    cbreak();
    //nodelay(stdscr, true);
    noecho();
    keypad(stdscr, TRUE);
    start_color();
    use_default_colors();

    initColors();

    gamestate* game = initGame();

    printGame(game, debug);
    
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
                printGame(game, debug);
                printw("you have lost. GG!\nPress 'q' to quit.\n");
            } while ((c = getch()) != 'q');
            break;
        }
        printGame(game, debug);
    }

    endwin();
    deleteGame(game);
}
