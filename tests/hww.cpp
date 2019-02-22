//File: main.cpp

//Program: SDL_HelloWorld

#include <iostream>
using std::cout;
using std::endl;

//SDL stuff.
#include <SDL2/SDL.h>

int main (int argc, char *argv[]) {
    cout << "Hello World!\n";
    
    if (SDL_Init (SDL_INIT_VIDEO) < 0) {
        cout << "Couldn't initialize SDL: %s\n"; exit (1);
    }
    
    atexit (SDL_Quit);

    //Window
    SDL_Window *win = SDL_CreateWindow("HW", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    if (win == nullptr) {
        cout << "SDL_CreateWindow error: " << SDL_GetError() << endl;
        exit(1);
    }
    
    //Renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr){
        SDL_DestroyWindow(win);
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        exit(1);
    }
    
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);



    SDL_Rect rect = {0, 0, 100, 50}; // the rectangle
    SDL_SetRenderDrawColor( renderer, 0, 0, 255, 255 );

    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer); // copy to screen


    SDL_Delay(3000);
    //Clean up
    SDL_DestroyWindow(win);

    return 0;
}


