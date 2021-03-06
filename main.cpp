#include <iostream>
#include "main.h"
#include <unistd.h>

int screen_width, screen_height;
SDL_Surface* screen;

using namespace std;

void refresh(FractalRenderer renderer){
        while(1){
                renderer.drawScreen();
        }
}

int main(){
        sleep(1);
        if (SDL_Init(SDL_INIT_VIDEO) != 0){
                cout << "SDL_Init Error: " << SDL_GetError() << endl;
                return 1;
        }
        const SDL_VideoInfo* info = SDL_GetVideoInfo();
        if (info == NULL){
                cout << "Video info error: " << *SDL_GetError() << endl;
                return 1;
        }
        // try to fullscreen
        screen_width  = info->current_w;
        screen_height = info->current_h;
        screen_width = 600;
        screen_height = 400;
        int video_flags = 0;
        // setting SDL video flags -- first two for video performance
        video_flags |= SDL_GL_DOUBLEBUFFER;
        video_flags |= SDL_HWPALETTE;
        // fullscreen flag
        //video_flags |= SDL_FULLSCREEN;
        screen = SDL_SetVideoMode(screen_width, screen_height, 32, video_flags);
        if (screen == NULL) {
                cout << "Couldn't set video mode: " << SDL_GetError() << endl;
                SDL_Quit();
                exit(1);
        }
        // initialize FractalGenerator and FractalRenderer objects
        MandelbrotGenerator generator = MandelbrotGenerator();
        generator.updateColorTable(screen_height, screen_width);
        FractalRenderer renderer(screen, &generator, screen_width, screen_height);
        //int go=0;                                                                                  
        //while (!go) sleep(1);  
        // begin rendering loop
        refresh(renderer);
        return 0;
}

