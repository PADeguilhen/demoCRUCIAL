#pragma once
#include "crossy.h"
#include <stdlib.h>
#include <ncurses.h>

#define TO_ENTITY_INDEX(label) (label - LABEL_COUNT - 1)
#define COLOR_BROWN 3

void initColors(void);

void printGame(gamestate* game, bool debug);
