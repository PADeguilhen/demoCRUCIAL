#include "crossy.h"
#include "display.h"

int random_in_range(int a, int b){
    return a + rand() % (b-a);
}

void gen_line(gamestate* game, int index){
    enum lineLabel type = random_in_range(0, LABEL_COUNT);
    game->grid[index] = type; // the default type is the ground

    switch (type) {
    case RIVER_DOWN:
    case RIVER_UP:{
        int pos1 = random_in_range(1, COLUMN_SIZE);
        int size1 = random_in_range(1, MAX_LOG_SIZE);

        for(int i = 1; i<COLUMN_SIZE; i++) game->grid[index + i] = 0;

        for(; size1 >= 0; size1--) {
            if ((pos1 + size1) % COLUMN_SIZE == 0) pos1 = 1;
            game->grid[index + ((pos1 + size1) % COLUMN_SIZE)] = 1;
        }
        break;
    }
    default:
        game -> grid[index] = SOLID_GROUND;
        game -> grid[index + 1] = 1; // trees...
        game -> grid[index + 2] = 1;
        game -> grid[index + COLUMN_SIZE - 1] = 1;
        game -> grid[index + COLUMN_SIZE - 2] = 1;
        
        int r;
        for(int i = 3; i<COLUMN_SIZE-2; i++){
            r = random_in_range(0, TREE_RATE);
            if (r == 0){
                game -> grid[index + i] = 1;
            }else{
                game -> grid [index + i] = 0;
            }
        }
        break;
    }
}

void moveLine(gamestate* game, int index, enum direction dir){
    switch (dir){
    case LEFT:
    {
        int start = game->grid[index + 1];
        for(int i=1; i<COLUMN_SIZE-1; i++){
            game->grid[index + i] = game->grid[index + i + 1];
        }
        game->grid[index + COLUMN_SIZE-1] = start;
    }
    case RIGHT:
    {
        int end = game->grid[index + COLUMN_SIZE - 1];
        for(int i=COLUMN_SIZE-1; i>1; i--){
            game->grid[index + i] = game->grid[index + i - 1];
        }
        game->grid[index + 1] = end;
        break;
    }
    default:
        break;
    }
}

void update_game_tic(gamestate* game){
    for(int line=0; line<LINE_SIZE; line++){
        switch (game->grid[line*COLUMN_SIZE]){
        case RIVER_DOWN:
            moveLine(game, line*COLUMN_SIZE, DOWN);
            break;
        case RIVER_UP:
            moveLine(game, line*COLUMN_SIZE, UP);
            break;
        default:
            break;
        }
    }
}

gamestate* initGame(void){
    gamestate* res = malloc(sizeof(gamestate));

    memset(res->grid, 0, GRID_SIZE*sizeof(int)); // initialise the grid to 0
    
    for(int i=0; i<LINE_SIZE; i++){
        gen_line(res, i*COLUMN_SIZE);
    }
    res->death = FIRST_GEN;
    res->chicken = STARTING_CHICKEN;
    return res;
}

void deleteGame(gamestate* game){
    free(game);
}

//only trees are implemented...
void manage_collisions(gamestate* game, int newPos){
    int pos = newPos % GRID_SIZE;
    if (game->grid[(pos/COLUMN_SIZE)*COLUMN_SIZE] == SOLID_GROUND && game->grid[pos] == 1){
        return ;
    }
    game->chicken = newPos;
}

void updateChicken(gamestate* game, enum direction dir){
    update_game_tic(game);
    if(game->chicken == AU_COIN) return ;
    int pos = game->chicken % GRID_SIZE;
    int new;
    switch (dir) {
        case UP:
            new = (game->chicken + COLUMN_SIZE);
            break;
        case DOWN:
            new = (game->chicken - COLUMN_SIZE);
            break;
        case LEFT:
            new = game->chicken - 1;
            break;
        case RIGHT:
            new = game->chicken + 1;
            break;
    }

    manage_collisions(game, new);

    // if we are out of bounds or we go to the corner.
    if (pos % COLUMN_SIZE == 0 || (game->death >= game->chicken / COLUMN_SIZE)){
        game->chicken = AU_COIN;
        return ;
    }

    if(dir == UP && (game->chicken/COLUMN_SIZE - game->death > D_CHK_DTH) && pos < new){
        game->death++;
        gen_line(game, (game->death*COLUMN_SIZE) % GRID_SIZE);
    }
}
