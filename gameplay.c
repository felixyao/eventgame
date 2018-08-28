
#include "gameplay.h"
#include "screen.h"
#include <event.h>
#include <sys/time.h>

static void redraw_game(int fd, short what, void *arg)
{  
    GAMEPLAY * game = (GAMEPLAY*)arg; 
    struct timeval half_sec = { 0, 500*1000 };
    evtimer_add(&game->redraw_timer, &half_sec);
    reset_game_board(&game->board);
    tile_draw(&game->tile, &game->board);
    wrefresh(game->board.game_pane);
    if (tile_hit_border(&game->tile, &game->board)) {
        evtimer_del(&game->redraw_timer);
        status_printw("game finished!");
    }
}

int gameplay_init(GAMEPLAY * game)
{
    if (init_game_board(&game->board) ) {
        return -1;
    }
    struct timeval half_sec = { 0, 500*1000 };
    evtimer_set(&game->redraw_timer, redraw_game, (void*)game);
    evtimer_add(&game->redraw_timer, &half_sec);
    tile_init(&game->tile);
    tile_draw(&game->tile, &game->board);
    wrefresh(game->board.game_pane);
    return 0;
}

void gameplay_change(GAMEPLAY * game, int direction)
{
    tile_change_direction(&game->tile, direction);
}

void gameplay_finish(GAMEPLAY * game)
{
    end_game_board(&game->board);
}