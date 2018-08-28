#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/eventfd.h>
#include <event.h>
#include <unistd.h>
#include "screen.h"

static int loop_started = 0;
static struct event stop_event;
int event_fd = -1;
void start_event_loop()
{
	loop_started = 1;
	int events = 0;
	do {
		event_loop(EVLOOP_ONCE);
		events++;
	}while(loop_started);
}

static void event_fd_cb(int event_fd, short what, void * arg)
{
	status_printw("stop event");
	loop_started = 0;
	close(event_fd);
	event_fd = -1;
}

void stop_event_loop()
{
	memset(&stop_event, 0, sizeof(stop_event));
	int event_fd = eventfd(0,  0);
	if (event_initialized(&stop_event))
		event_del(&stop_event);
	event_set(&stop_event, event_fd, EV_READ, event_fd_cb,
		    NULL);
	event_add(&stop_event, NULL);
	long long  ev = 1;
	write(event_fd, &ev, sizeof(ev));
}