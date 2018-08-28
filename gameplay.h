#pragma once 
#include "gameboard.h"
#include "tile.h"
#include <event.h>

typedef struct gameplay {
    GAME_BOARD board;
    TILE tile;
    struct event redraw_timer;
}GAMEPLAY;

int gameplay_init(GAMEPLAY * game);
void gameplay_finish(GAMEPLAY * game);
void gameplay_change(GAMEPLAY * game, int direction);