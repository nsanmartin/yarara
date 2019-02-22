#include <iostream>

#include <Media.hpp>

void Media::Init() {
    
    if (SDL_Init (SDL_INIT_VIDEO) < 0) {
        std::cout << "Couldn't initialize SDL: %s\n"; exit (1);
    }
    
    atexit (SDL_Quit);

    //Window
    mWin = SDL_CreateWindow(
        "HW", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        640, 480, SDL_WINDOW_SHOWN);
    
    if (mWin == nullptr) {
        std::cout << "SDL_CreateWindow error: " << SDL_GetError()
                  << std::endl;
        exit(1);
    }
    
    //Renderer
    mRenderer = SDL_CreateRenderer(
        mWin, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    if (mRenderer == nullptr){
        SDL_DestroyWindow(mWin);
        std::cout << "SDL_CreateRenderer Error: "
                  << SDL_GetError() << std::endl;
        exit(1);
    }
}

void Media::Close() {
    SDL_DestroyWindow(mWin);
}

void Media::Clear() {
    SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255);
    SDL_RenderClear(mRenderer);
}


void Media::PollEvents() {
    /* Poll for events */
    while( SDL_PollEvent( &mEvent ) ){
                
        switch( mEvent.type ){
            /* Keyboard event */
            /* Pass the event data onto PrintKeyInfo() */
        case SDL_KEYDOWN:
            switch( mEvent.key.keysym.sym ){
            case SDLK_LEFT:
                mKeyQueue.push_front(Key::Left);
                break;
            case SDLK_RIGHT:
                mKeyQueue.push_front(Key::Right);
                break;
            case SDLK_UP:
                mKeyQueue.push_front(Key::Up);
                break;
            case SDLK_DOWN:
                mKeyQueue.push_front(Key::Down);
                break;
            case SDLK_q:
                mKeyQueue.push_front(Key::q);
                break;

            default:
                break;
            }
            break;
        case SDL_KEYUP:
            //PrintKeyInfo( &mEvent.key );
            break;

            /* SDL_QUIT event (window close) */
        case SDL_QUIT:
            mKeyQueue.push_front(Key::q);
            break;

        default:
            break;
        }

    }
}


void Media::Draw(Cajita c) {
    SDL_Rect rect = {c.mPosX, c.mPosY, c.mX, c.mY}; // the rectangle
    SDL_SetRenderDrawColor( mRenderer, 0, 0, 255, 255 );
    SDL_RenderFillRect(mRenderer, &rect);

}
