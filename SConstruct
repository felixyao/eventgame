import os
env = Environment(**os.environ)
env["ENV"]["PKG_CONFIG_PATH"] = os.environ.get("PKG_CONFIG_PATH")
env.ParseConfig("pkg-config libevent --cflags --libs")
env.ParseConfig("pkg-config ncurses --cflags --libs")
env.Program('snake', ['screen.c', 'event.c', 'control.c', 'gameplay.c', 'gameboard.c', 'tile.c'])