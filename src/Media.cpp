#include <iostream>

#include <Media.hpp>
#include <Point.hpp>
#include <World.hpp>


void Media::Init() {
    
    if (SDL_Init (SDL_INIT_VIDEO) < 0) {
        std::cout << "Couldn't initialize SDL: %s\n"; exit (1);
    }
    
    atexit (SDL_Quit);

    //Window
    mWin = SDL_CreateWindow(
        "HW", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        mWindowHeight, mWindowWidth, SDL_WINDOW_SHOWN);
    
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
    mWorld->ExistsActiveCajita();
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
            case SDLK_r:
                mKeyQueue.push_front(Key::r);
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


void Media::Draw(Cajita caja) {
    int npoints{10};
    int displ {1};
    Point desp{caja.mX/2, caja.mY/2};
    
    Point center { desp + Point {caja.mPosX, caja.mPosY}};
    Point pos{caja.mPosX, caja.mPosY};
    
    // int x {caja.mX/2};
    // int y {caja.mY/2};

    Point a {Point{-desp.mX, -desp.mY}};
    Point b {Point{-desp.mX, desp.mY}};
    Point c {Point{desp.mX, desp.mY}};
    Point d {Point{desp.mX, -desp.mY}};

    a.Rotate(caja.mAngle.mRot);
    b.Rotate(caja.mAngle.mRot);
    c.Rotate(caja.mAngle.mRot);
    d.Rotate(caja.mAngle.mRot);

    pos += desp;
    
    a += center;
    b += center;
    c += center;
    d += center;
    
    SDL_Point points[npoints] = {
        {a.mX, a.mY},
        {b.mX, b.mY},
        {c.mX, c.mY},
        {d.mX, d.mY },
        {a.mX, a.mY},

        {a.mX + displ, a.mY + displ},
        {b.mX + displ, b.mY - displ},
        {c.mX - displ, c.mY - displ},
        {d.mX - displ, d.mY + displ},
        {a.mX + displ, a.mY + displ}

    };

    SDL_SetRenderDrawColor( mRenderer, 0, 0, 255, 255 );
    SDL_RenderDrawLines(mRenderer, points, npoints);

}
