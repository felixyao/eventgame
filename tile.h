#pragma once
#include "gameboard.h"
#include <event.h>
typedef struct tile_s {
    int x;
    int y;
    int direction;
    char shape;
    struct event move_timer;
}TILE;

void tile_init(TILE * tile);
int tile_hit_border(const TILE * tile, const GAME_BOARD* board);
int tile_hit_another_tile(const TILE * self, const TILE * another);
void tile_draw(const TILE * tile, const GAME_BOARD * board);
void tile_change_direction(TILE * tile, int direction);