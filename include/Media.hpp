#ifndef _MEDIA_H
#define _MEDIA_H

#include <deque>
#include <SDL2/SDL.h>
#include <Cajita.hpp>
#include <Polygon/Polygon.hpp>
#include <Polygon/Triangle.hpp>

class World;

class Media {
public:
    enum class Key { a, b, r, q, Left, Right, Up, Down };
private:
    SDL_Window *mWin;
    int mWindowWidth, mWindowHeight;
    SDL_Renderer *mRenderer;

    SDL_Event mEvent;
    std::deque<Key> mKeyQueue;
    World& mWorld;
public:

    Media(World& w)
        : mWin{nullptr}, mWindowWidth{640}, mWindowHeight{480},
          mRenderer{nullptr}, mWorld{w} {}
    void init();
    void close();
    void pollEvents();
    void clear();
    void presentScreen() {SDL_RenderPresent(mRenderer); }

    bool hasEvents() const { return !mKeyQueue.empty(); }

    Key PopKey() {
        Key res{mKeyQueue.front()};
        mKeyQueue.pop_front();
        return res;
    }

    void draw(const Cajita& c) const;
    void draw(const Polygon& p) const;
    void draw(const SDL_Point* pts, int count) const;
    void fillTriangle(std::vector<Point> pts);

};


#endif
