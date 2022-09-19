#ifndef _WORLD_H
#define _WORLD_H

#include <vector>

#include <Media.hpp>
#include <Cajita.hpp>
#include <Polygon/Polygon.hpp>
#include <State/WorldState.hpp>

class World {
public:
    enum class StateEnum { Presentation = 0, Move };
private:
    bool mContinue;
    Media mMedia;
    std::vector<Cajita> mCajitas;
    //todo: use unique ptrs
    std::vector<Polygon*> mPolygons;
    size_t mActiveCajita;
    size_t mActivePolygon;
    //todo: use unique ptrs
    std::vector<WorldState*> mStates;
    StateEnum mPresentState;
public:
    
    World();
    ~World();
    void loop();
    void update();
    void quit() { mContinue = false; }
    WorldState* getState() {
        return mStates.at(static_cast<size_t>(mPresentState));
    }
    void handleInput() { getState()->handleInput(); }
    void pushCajita(Cajita c) { mCajitas.push_back(c); }
    void popCajita() { mCajitas.pop_back(); }
    bool existsActiveCajita() { return mActiveCajita < mCajitas.size(); }

    Cajita& getActiveCajita() { return mCajitas[mActiveCajita];}

    void pushPolygon(Polygon* p) { mPolygons.push_back(p); }
    void popPolygon() { mPolygons.pop_back(); }
    bool existsActivePolygon() const {
        return mActivePolygon < mPolygons.size();
    }

    Polygon* getActivePolygon() { return mPolygons[mActivePolygon];}

    void changeState(StateEnum nextState) {
        if (nextState != mPresentState) {
            getState()->onExit();
            mPresentState = nextState;
            getState()->onEnter();
        }
    }
};


#endif
