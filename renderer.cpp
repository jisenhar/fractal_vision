#include "renderer.h"
#include <iostream>

using namespace std;

FractalRenderer::FractalRenderer(
                SDL_Surface* p_screen,
                FractalGenerator* p_fractal,
                int width, int height) {

        screen_width = width;
        screen_height = height;
        frame_buf = new uint32_t [height*width];
        screen = p_screen;
        fractal = p_fractal;

}

void FractalRenderer::getEvents(){
        // Event handling -- key presses, etc.
        SDL_Event ev;
        while (SDL_PollEvent(&ev)) {
                switch (ev.type) {
                        case SDL_QUIT:
                                SDL_Quit();
                                exit(0);
                                break;
                        case SDL_KEYDOWN:
                                // this is a user hitting escape
                                if (ev.key.keysym.sym == 27) {
                                        SDL_Quit();
                                        exit(0);
                                } else if (ev.key.keysym.sym == SDLK_UP) {
                                        key_up = 1;
                                } else if (ev.key.keysym.sym == SDLK_DOWN) {
                                        key_down = 1;
                                } else if (ev.key.keysym.sym == SDLK_RIGHT) {
                                        key_right = 1;
                                } else if (ev.key.keysym.sym == SDLK_LEFT) {
                                        key_left = 1;
                                } else if (ev.key.keysym.sym == SDLK_0){
                                        zoom_in = 1;
                                } else if (ev.key.keysym.sym == SDLK_1){
                                        zoom_out = 1;
                                }
                                break;
                        case SDL_KEYUP:
                                // clear flags when keys are released
                                if (ev.key.keysym.sym == SDLK_UP) {
                                        key_up = 0;
                                } else if (ev.key.keysym.sym == SDLK_DOWN) {
                                        key_down = 0;
                                } else if (ev.key.keysym.sym == SDLK_RIGHT) {
                                        key_right = 0;
                                } else if (ev.key.keysym.sym == SDLK_LEFT) {
                                        key_left = 0;
                                } else if (ev.key.keysym.sym == SDLK_0){
                                        zoom_in = 0;
                                } else if (ev.key.keysym.sym == SDLK_1){
                                        zoom_out = 0;
                                }
                                break;
                }
        }
}

void FractalRenderer::drawScreen(){
        
        getEvents();                    // poll for events
        if (zoom_in){
                fractal->increaseZoom();
        } else if (zoom_out){
                fractal->decreaseZoom();
        }
        if (key_up || key_down) {
                fractal->panY(key_down);
        } else if (key_right || key_left) {
                fractal->panX(key_right);
        }
        if (SDL_MUSTLOCK(screen)){      // SDL secret handshake
                SDL_LockSurface(screen);
        }

        int x, y;       // iterators

        fractal->fillBuffer(frame_buf, screen_height, screen_width);
        int i = 0;
        // std::cout << "renderer" << std::endl;
        for (y=0; y < screen_height; y++){
                for (x=0; x < screen_width; x++){
                        char* pixel_pointer = ((char*)screen->pixels) + 4*(x + y*screen_width);
                        uint32_t RGB = frame_buf[i];
                        // cout << hex << RGB;
                        uint8_t red = RGB >> 24;
                        uint8_t green = RGB >> 16;
                        uint8_t blue = RGB >> 8;
                        pixel_pointer[0] = red;
                        pixel_pointer[1] = green;
                        pixel_pointer[2] = blue;
                        i++;
                }
        }
        // another SDL secret handshake
        if (SDL_MUSTLOCK(screen)){
                SDL_UnlockSurface(screen);
        }

        // flipping the double buffer to update the screen with our changes
        SDL_Flip(screen);
}


int FractalRenderer::getScreenWidth(){return screen_width;};
int FractalRenderer::getScreenHeight(){return screen_height;};

void FractalRenderer::setFractal(FractalGenerator* p_fractal){
        fractal = p_fractal;
}

void FractalRenderer::setScreenWidth(int width){
        screen_width = width;
}

void FractalRenderer::setScreenHeight(int height){
        screen_height = height;
}

void FractalRenderer::setScreen(SDL_Surface* p_screen){
        screen = p_screen;
}

