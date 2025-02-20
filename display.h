#pragma once
#include "crossy.h"
#include <stdlib.h>
#include <ncurses.h>

#define COLOR_BROWN 6

void initColors(void);

void printGame(gamestate* game, bool debug);
