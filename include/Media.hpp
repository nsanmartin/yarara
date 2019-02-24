#ifndef _MEDIA_H
#define _MEDIA_H

#include <deque>
#include <SDL2/SDL.h>
#include <Cajita.hpp>


class Media {
public:
    enum class Key { a, b, r, q, Left, Right, Up, Down };
private:
    SDL_Window *mWin;
    int mWindowWidth, mWindowHeight;
    SDL_Renderer *mRenderer;

    SDL_Event mEvent;
    std::deque<Key> mKeyQueue;
    
public:

    Media(): mWin{nullptr}, mWindowWidth{640}, mWindowHeight{480},
             mRenderer{nullptr} {}
    void Init();
    void Close();
    void PollEvents();
    void Clear();
    void PresentScreen() {SDL_RenderPresent(mRenderer); }

    bool HasEvents() { return !mKeyQueue.empty(); }

    Key PopKey() {
        Key res{mKeyQueue.front()};
        mKeyQueue.pop_front();
        return res;
    }

    void Draw(Cajita c) ;
    };


#endif
