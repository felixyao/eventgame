#pragma once

#include <ncurses.h>


typedef struct game_board {
    int height;
    int width;
    WINDOW * game_pane;
}GAME_BOARD;

int init_game_board(GAME_BOARD * board);
void end_game_board(GAME_BOARD * board);
void reset_game_board(GAME_BOARD * board);