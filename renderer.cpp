#include "renderer.h"

FractalRenderer::FractalRenderer(
                SDL_Surface* p_screen,
                FractalGenerator* p_fractal,
                int width, int height) {

        screen_width = width;
        screen_height = height;
        screen = p_screen;
        fractal = p_fractal;
}

FractalRenderer::FractalRenderer(
                SDL_Surface* p_screen,
                int width, int height) {

        screen_width = width;
        screen_height = height;
        screen = p_screen;
        fractal = NULL;
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
                                } break;
                }
        }
}

void FractalRenderer::drawScreen(){
        getEvents();                    // poll for events
        if (SDL_MUSTLOCK(screen)){      // SDL secret handshake
                SDL_LockSurface(screen);
        }

        // let's draw some quick bullshit I think
        int x, y;
        int counter = 0;
        for (y = 0; y < screen_height; y++) {
                for (x = 0; x < screen_width; x++) {
                        char* pixel_pointer = ((char*)screen->pixels) + 4*(x + y*screen_width);
                        // Set the B, G, and R components separately.
                        // The fourth byte is reserved for alpha, but not used in RGB video mode for alignment reasons.
                        pixel_pointer[0] = x+y + counter;
                        pixel_pointer[1] = y-x + counter;
                        pixel_pointer[2] = x*y*counter;
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