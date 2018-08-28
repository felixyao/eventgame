#include "eventt.h"
#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include "screen.h"
#include "gameplay.h"

static  struct event stdin_event;

static void control_cb(int stdin, short what, void * arg)
{
    int ch = getch();
    static int times = 0;
    status_printw("Get a Key %c %d", (char)ch, times++);
    switch (ch) {
        case ERR:
            stop_event_loop();
            break;
        case KEY_DOWN:
            gameplay_change(&game, 0);
            break;
        case KEY_UP:
            gameplay_change(&game, 2);
            break;
        case KEY_RIGHT:
            gameplay_change(&game, 1);
            break;
        case KEY_LEFT:
            gameplay_change(&game, 3);
            break;
        case 'q':
            stop_event_loop();
            break;
        case 'c':
            break;
        case KEY_BACKSPACE:
            stop_event_loop();
        default:
            break;
    }
	event_add(&stdin_event, NULL);
}

void control_init(void)
{
    memset(&stdin_event, 0, sizeof(stdin_event));
	if (event_initialized(&stdin_event))
		event_del(&stdin_event);
	event_set(&stdin_event, 0, EV_READ, control_cb,
		    NULL);
	event_add(&stdin_event, NULL);
}
