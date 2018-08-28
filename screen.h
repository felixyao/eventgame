#pragma once

#include <ncurses.h>
#include "gameplay.h"
WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);
void status_printw(const char * out, ...);
extern GAMEPLAY game;