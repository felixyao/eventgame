#include "screen.h"
#include "gameboard.h"
    int max_row, max_col;
int init_game_board(GAME_BOARD * board)
{

    getmaxyx(stdscr, max_row, max_col);
    board->height = 32;
    board->width = 62;
    const int height =  board->height ;
    const int length = board->width;
    if ((max_row < height + 2) || (max_col < length +2)) {
        status_printw("Error: terminal is not suit for the game!");
        return -1;
    }
    board->game_pane  = create_newwin(height, length, 1, (max_col - length)/2);
    return 0;
 
}

void reset_game_board(GAME_BOARD *board)
{
    const int height =  board->height ;
    const int length = board->width;
    destroy_win(board->game_pane);
    board->game_pane  = create_newwin(height, length, 1, (max_col - length)/2);
}

void end_game_board(GAME_BOARD * board)
{
    board->height = 0;
    board->width = 0;
    destroy_win(board->game_pane);
}