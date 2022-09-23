#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <numeric>

#include <Media.hpp>
#include <Point.hpp>
#include <World.hpp>


void Media::init() {
    
    if (SDL_Init (SDL_INIT_VIDEO) < 0) {
        std::cerr << "Couldn't initialize SDL\n"; exit (1);
    }
    
    atexit (SDL_Quit);

    //Window
    mWin = SDL_CreateWindow(
        "HW", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        mWindowHeight, mWindowWidth, SDL_WINDOW_SHOWN);
    
    if (mWin == nullptr) {
        std::cerr << "SDL_CreateWindow error: " << SDL_GetError()
                  << std::endl;
        exit(1);
    }
    
    //Renderer
    mRenderer = SDL_CreateRenderer(
        mWin, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    if (mRenderer == nullptr){
        SDL_DestroyWindow(mWin);
        std::cerr << "SDL_CreateRenderer Error: "
                  << SDL_GetError() << std::endl;
        exit(1);
    }
}

void Media::close() {
    SDL_DestroyWindow(mWin);
}

void Media::clear() {
    SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255);
    SDL_RenderClear(mRenderer);
}


void Media::pollEvents() {
    // mWorld.ExistsActiveCajita();
    // /* Poll for events */
    // while( SDL_PollEvent( &mEvent ) ){
                
    //     switch( mEvent.type ){
    //         /* Keyboard event */
    //         /* Pass the event data onto PrintKeyInfo() */
    //     case SDL_KEYDOWN:
    //         switch( mEvent.key.keysym.sym ){
    //         case SDLK_LEFT:
    //             mKeyQueue.push_front(Key::Left);
    //             break;
    //         case SDLK_RIGHT:
    //             mKeyQueue.push_front(Key::Right);
    //             break;
    //         case SDLK_UP:
    //             mKeyQueue.push_front(Key::Up);
    //             break;
    //         case SDLK_DOWN:
    //             mKeyQueue.push_front(Key::Down);
    //             break;
    //         case SDLK_r:
    //             mKeyQueue.push_front(Key::r);
    //             break;
    //         case SDLK_q:
    //             mKeyQueue.push_front(Key::q);
    //             break;

    //         default:
    //             break;
    //         }
    //         break;
    //     case SDL_KEYUP:
    //         //PrintKeyInfo( &mEvent.key );
    //         break;

    //         /* SDL_QUIT event (window close) */
    //     case SDL_QUIT:
    //         mKeyQueue.push_front(Key::q);
    //         break;

    //     default:
    //         break;
    //     }

    // }
}


void Media::draw(const Cajita& caja) const {
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

void Media::draw(const Polygon& poly) const {

    Point center{};
    for (auto& p : poly.mVertices) {
        if (p.mX > center.mX) center.mX = p.mX;
        if (p.mY > center.mY) center.mY = p.mY;
    }
    
    center /= 2;
    Point pos {poly.mPos};
    int rotation {poly.mAngle.mRot};
    
    std::vector<SDL_Point> vertices;
    std::transform(poly.mVertices.begin(),poly.mVertices.end(),
                   std::back_inserter(vertices),
                   [&center, &rotation, &pos](const Point& p) {
                       Point res {p - center};
                       res.Rotate(rotation);
                       res += pos + center;
                       return SDL_Point{res.mX, res.mY};
                   });
    
    vertices.push_back(vertices[0]);
        
    SDL_SetRenderDrawColor( mRenderer, 0, 0, 255, 255 );
    SDL_RenderDrawLines(
        mRenderer, vertices.data(), vertices.size());
    
}


void Media::draw(const SDL_Point* p, int count) const {
    
}


void Media::fillTriangle(std::vector<Point> vertices) {
    //todo: bound with zero, mWinWidth and mWinHeight
    std::sort(vertices.begin(), vertices.end(),
              [](Point& p, Point& q) {return p.mX < q.mX;});

    std::vector<SDL_Point> pts;
    int xA{vertices[0].mX};
    int yA{vertices[0].mY};
    
    int xB{vertices[1].mX};
    int yB{vertices[1].mY};
    
    int xC{vertices[2].mX};
    int yC{vertices[2].mY};

    assert(xA <= xB && xB <= xC);
    double ab_slope{static_cast<double>(yB - yA) / static_cast<double>(xB - xA)};
    double ac_slope{static_cast<double>(yC - yA) / static_cast<double>(xC - xA)};
    double bc_slope{static_cast<double>(yC - yB) / static_cast<double>(xC - xB)};

    std::function<int(double)> ab_line = [&xA, &yA, &ab_slope] (int x) { return yA + ab_slope * (x - xA);};
    std::function<int(double)> ac_line = [&xA, &yA, &ac_slope] (int x) { return yA + ac_slope * (x - xA);};
    std::function<int(double)> bc_line = [&xB, &yB, &bc_slope] (int x) { return yB + bc_slope * (x - xB);};

    for (int x = xA; x < xB; ++x) {
        std::vector<int> ys(std::abs(ac_line(x) - ab_line(x)));
        std::iota(ys.begin(), ys.end(), std::min(ac_line(x), ab_line(x)));
        std::transform(ys.begin(), ys.end(),
                       back_inserter(pts), [&x] (int y)
                       {
                           return SDL_Point{x, y};
                       });
    }

    for (int x = xB; x <= xC ; ++x) {
        std::vector<int> ys(std::abs(ac_line(x) - bc_line(x)));
        std::iota(ys.begin(), ys.end(), std::min(ac_line(x), bc_line(x)));
        std::transform(ys.begin(), ys.end(),
                       back_inserter(pts), [&x] (int y)
                       {
                           return SDL_Point{x, y};
                       });

    }


    SDL_SetRenderDrawColor( mRenderer, 0, 0, 102, 205 );
    SDL_RenderDrawPoints(
        mRenderer, pts.data(), pts.size());

}

