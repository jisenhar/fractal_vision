#ifndef RENDERER_H
#define RENDERER_H

#include "SDL/SDL.h"
#include "Mandelbrot.h"
#include <cstdint>


class FractalRenderer{
        private:
                int screen_width;
                int screen_height;
                SDL_Surface* screen;
                FractalGenerator* fractal;
                uint32_t * frame_buf;
                void getEvents();

                int key_up = 0;
                int key_down = 0;
                int key_right = 0;
                int key_left = 0;
                int zoom_in = 0;
                int zoom_out = 0;

        public:
                FractalRenderer(SDL_Surface* p_screen,
                                FractalGenerator* p_fractal,
                                int width,
                                int height);

                void drawScreen();

                int getScreenWidth();
                int getScreenHeight();

                void setFractal(FractalGenerator* p_fractal);

                void setScreenWidth(int width);
                void setScreenHeight(int height);
                void setScreen(SDL_Surface* p_screen);
};

#endif
