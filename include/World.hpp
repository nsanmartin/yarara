#ifndef _WORLD_H
#define _WORLD_H

#include <vector>

#include <Media.hpp>
#include <Cajita.hpp>
#include <State/WorldState.hpp>

class World {

    bool mContinue;
    Media mMedia;
    std::vector<Cajita> mCajitas;
    size_t mActiveCajita;
    std::vector<WorldState*> mStates;
    size_t mPresentState;
public:

    World();
    ~World();
    void Loop();
    void Update();
    void PushCajita(Cajita c) { mCajitas.push_back(c); }
    bool ExistsActiveCajita() { return mActiveCajita < mCajitas.size(); }

    Cajita& GetActiveCajita() { return mCajitas[mActiveCajita];}
};


#endif
