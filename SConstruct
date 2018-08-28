env = Environment()
env.ParseConfig("pkg-config libevent --cflags --libs")
env.ParseConfig("pkg-config ncurses --cflags --libs")
env.Program('snake', ['screen.c', 'event.c', 'control.c', 'gameplay.c', 'gameboard.c', 'tile.c'])