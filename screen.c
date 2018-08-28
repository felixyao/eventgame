#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "eventt.h"
#include "control.h"
#include "screen.h"
#include "gameplay.h"

WINDOW *create_newwin(int height, int width, int starty, int startx)
{	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0 , 0);		/* 0, 0 gives default characters 
					 * for the vertical and horizontal
					 * lines			*/
	wrefresh(local_win);		/* Show that box 		*/

	return local_win;
}


void destroy_win(WINDOW *local_win)
{	
	/* box(local_win, ' ', ' '); : This won't produce the desired
	 * result of erasing the window. It will leave it's four corners 
	 * and so an ugly remnant of window. 
	 */
	wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	/* The parameters taken are 
	 * 1. win: the window on which to operate
	 * 2. ls: character to be used for the left side of the window 
	 * 3. rs: character to be used for the right side of the window 
	 * 4. ts: character to be used for the top side of the window 
	 * 5. bs: character to be used for the bottom side of the window 
	 * 6. tl: character to be used for the top left corner of the window 
	 * 7. tr: character to be used for the top right corner of the window 
	 * 8. bl: character to be used for the bottom left corner of the window 
	 * 9. br: character to be used for the bottom right corner of the window
	 */
	wrefresh(local_win);
	delwin(local_win);
}

static WINDOW * status_pane;
GAMEPLAY game;

static void init_screen()
{
    initscr();
    raw();
    noecho();
    cbreak();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    refresh();
}

static void init_status_pane()
{
    int max_row, max_col;
    getmaxyx(stdscr, max_row, max_col);
    const int height = 3;
    const int length = max_col - 2;
    status_pane = create_newwin(height, length, max_row-1 - height, 1);
}

void status_printw(const char * out, ...)
{
    va_list ap;
    va_start(ap, out);
    wmove(status_pane, 1, 1);
    vwprintw(status_pane, out, ap);
    va_end(ap);
    wrefresh(status_pane);
}


static void setup_default_color()
{
    if(has_colors())
    {
        start_color();
        init_pair(1, COLOR_RED, COLOR_BLACK);
        init_pair(2, COLOR_GREEN, COLOR_BLACK);
        init_pair(3, COLOR_YELLOW, COLOR_BLACK);
        init_pair(4, COLOR_BLUE, COLOR_BLACK);
        init_pair(5, COLOR_CYAN, COLOR_BLACK);
        //attron(COLOR_PAIR(color));
    }
}

void refresh_screen()
{
    refresh();
}

int main(int argc, char * argv[])
{
    init_screen();
    //setup_default_color();
    //attron(COLOR_PAIR(1));
    event_init();
    init_status_pane();

    if (gameplay_init(&game)) {
        return -1;
    }

    control_init();
    start_event_loop();
    destroy_win(status_pane);
    gameplay_finish(&game);
    endwin();
    return 0;
}