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
    start_color();          //allow the use of colors
    cbreak();               //make input characters immediately available for the program
    nodelay(stdscr, true);  //getch doesn't wait for input.
    noecho();               //don't echo the tiped char
    curs_set(false);        //remove cursor
    keypad(stdscr, TRUE);   //define where to read the keaboard
    use_default_colors();

    initColors();

    gamestate* game = initGame();

    int frame_cpt = 1;
    char c;
    while((c = getch()) != 'q') { // change logic for frame generation? (multihtreading...)
        if (frame_cpt % 10000 == 0){ // make the board move
            update_game_tic(game);
        }
        printGame(game, debug);
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
        default:
            frame_cpt ++;
            break;
        }
        if(game->chicken == AU_COIN){ // end of game the chicken is au coin
            do{
                printGame(game, debug);
                printw("you have lost. GG!\nPress 'q' to quit.\n");
            } while ((c = getch()) != 'q');
            break;
        }
        printw("\nOn frame nb: %d\n", frame_cpt);
    }

    endwin();
    deleteGame(game);

    return 0;
}
