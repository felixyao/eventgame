#include "tile.h"


static void move_tile(int fd, short what, void *arg)
{  
    TILE * tile = (TILE*)arg; 
    struct timeval one_sec = { 1, 0 };
    evtimer_add(&tile->move_timer, &one_sec);
    switch (tile->direction) {
        case 0:
            tile->y++;
            break;
        case 1:
            tile->x++;
            break;
        case 2:
            tile->y--;
            break;
        case 3:
            tile->x--;
            break;
        default:
            break;
    }
}

void tile_init(TILE * tile)
{
    tile->direction = 0; //up
    tile->shape = '*';
    tile->x = 1;
    tile->y = 1;
    struct timeval one_sec = { 1, 0 };
    evtimer_set(&tile->move_timer, move_tile, (void*)tile);
    evtimer_add(&tile->move_timer, &one_sec);
}

void tile_change_direction(TILE * tile, int direction)
{
    tile->direction = direction;
}

int tile_hit_border(const TILE * tile, const GAME_BOARD* board)
{
    if (tile->x == 0 || tile->y == 0 || tile->x ==  board->width || tile->y == board->height){
        return 1;
    }
    return 0;
}

int tile_hit_another_tile(const TILE * self, const TILE * another)
{
    return (self->x == another->x && self->y == another->y);
}

void tile_draw(const TILE * tile, const GAME_BOARD * board)
{
    wmove(board->game_pane, tile->y, tile->x);
    wprintw(board->game_pane, &tile->shape);
}