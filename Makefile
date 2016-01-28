
CFLAGS=-Wall `sdl-config --cflags --libs`

all: main

CXX = g++

main: main.cpp Makefile
	$(CXX) -o $@ $< $(CFLAGS) -std=c++11

