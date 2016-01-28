
CFLAGS=-Wall `sdl-config --cflags --libs`

all: main

CXX = g++
SOURCES = main.cpp renderer.cpp mandelbrot.cpp
main: $(SOURCES) 
	$(CXX) -o $@ $^ $(CFLAGS) -std=c++11 -g

