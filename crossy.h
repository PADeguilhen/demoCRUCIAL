#pragma once

/*
The idea is that the first element of every line contains the info of what is on the line
with special codes for:
    - the nature of the line (road, ground, river) 
    - the the direction of the road or river (in what direction does it flow)
    - the current position of the player? (maybe put it in a variable accessible in the gamestate for fast lookup)
*/

#define LINE_SIZE   24
#define COLUMN_SIZE 15
#define GRID_SIZE   (LINE_SIZE * COLUMN_SIZE)

#define FIRST_GEN           0               // the position of the first visible line
#define D_CHK_DTH           3               // distance between the chicken and death
#define STARTING_CHICKEN    (D_CHK_DTH * COLUMN_SIZE + (COLUMN_SIZE - 1) / 2)

#define AU_COIN -1 // when the player has made a move that is illegal

#define TREE_RATE 7     // 1 in TREE_RATE chance to get a tree
#define MAX_LOG_SIZE 6  // max size of a log in a river

/*
We are going to generate the next gamestates iteratively by modifying the lines at: center / LINE_SIZE
then increment center. (so that the grid moves...)
(Maybe keep a buffer to generate the rivers and roads in one go that way there is no rupture in continuity on the grid)
*/
typedef struct gamestate{
    int grid[GRID_SIZE];
    int death;
    int chicken;
} gamestate;

/*
Information that is in the col of evrey line of the grid of the game that gives the information on what is in the column
*/
enum lineLabel {
    CAR_LANE_UP,
    CAR_LANE_DOWN,
    TRUCK_LANE_UP,
    TRUCK_LANE_DOWN,
    RIVER_UP,
    RIVER_DOWN,
    TRAIN_UP,
    TRAIN_DOWN,
    SOLID_GROUND,
    // this enum will have the number of lables assigned to it (keep it at the bottom)
    LABEL_COUNT
};

enum direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

gamestate* initGame(void);
void deleteGame(gamestate* game);

//handeling moving in bounds.
void updateChicken(gamestate* game, enum direction dir);

void update_game_tic(gamestate* game);
