#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#include "crossy.h"

void gen_line(gamestate* game, enum lineLabel type, int index){
    switch (type) {
    case SOLID_GROUND:
        game -> grid[index + 1] = 1; // trees...
        game -> grid[index + 2] = 1;
        game -> grid[index + COLUMN_SIZE - 1] = 1;
        game -> grid[index + COLUMN_SIZE - 2] = 1;
        
        int r;

        for(int i = 3; i<COLUMN_SIZE-2; i++){
            r = rand() % TREE_RATE;
            if (r == 0){
                game -> grid[index + i] = 1;
            }else{
                game -> grid [index + i] = 0;
            }
        }
        break;
    default:
        break;
    }
}

gamestate* initGame(void){
    gamestate* res = malloc(sizeof(gamestate));

    memset(res->grid, 0, GRID_SIZE*sizeof(int)); // initialise the grid to 0
    
    for(int i=0; i<LINE_SIZE; i++){
        res->grid[i*COLUMN_SIZE] = SOLID_GROUND;
        gen_line(res, SOLID_GROUND, i*COLUMN_SIZE);
    }
    res->death = FIRST_GEN;
    res->chicken = STARTING_CHICKEN;

    return res;
}

void deleteGame(gamestate* game){
    free(game->grid);
    free(game);
}

//only trees are implemented...
void manage_collisions(gamestate* game, int newPos){
    if (game->grid[(newPos/COLUMN_SIZE)*COLUMN_SIZE] == SOLID_GROUND && game->grid[newPos] == 1){
        return ;
    }
    game->chicken = newPos;
}

void updateChicken(gamestate* game, enum direction dir){
    if(game->chicken == AU_COIN) return ;

    int new;
    switch (dir) {
        case UP:
            new = (game->chicken + COLUMN_SIZE) % GRID_SIZE;
            break;
        case DOWN:
            if ((game->chicken - COLUMN_SIZE) % GRID_SIZE < 0){
                new = GRID_SIZE - COLUMN_SIZE + (game->chicken % COLUMN_SIZE);
            } else {
                new = (game->chicken - COLUMN_SIZE) % GRID_SIZE;
            }
            break;
        case LEFT:
            new = game->chicken - 1;
            break;
        case RIGHT:
            new = game->chicken + 1;
            break;
    }

    manage_collisions(game, new);

    // if we are out of bounds we go to the lost corner.
    if (game->chicken % COLUMN_SIZE == 0 ||
        (game->death == game->chicken/COLUMN_SIZE)){
        game->chicken = AU_COIN;
        return ;
    }
    if(dir == UP){
        if (game->chicken/COLUMN_SIZE >= D_CHK_DTH){
            game->death = (game->chicken/COLUMN_SIZE - D_CHK_DTH);
        }
        else if (game->chicken/COLUMN_SIZE < D_CHK_DTH){
            game->death = LINE_SIZE - D_CHK_DTH + game->chicken/COLUMN_SIZE;
        }
        gen_line(game, SOLID_GROUND, game->death*COLUMN_SIZE);
    }
}
