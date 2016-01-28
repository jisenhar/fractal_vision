
CFLAGS=-Wall `sdl-config --cflags --libs`

all: main

main: main.cpp Makefile
	g++ -o $@ $< $(CFLAGS)

