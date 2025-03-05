CC		= gcc
CFLAGS	= -std=c99 -ggdb3 -Wall -Wextra -Wconversion -Wpedantic
LDFLAGS	= -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

all: button/button

button/button: button/button.c ../rlui_elems.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
