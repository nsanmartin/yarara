#ifndef _WORLD_STATE_PRESENTATION_H
#define _WORLD_STATE_PRESENTATION_H

#include <World.hpp>
#include <State/WorldState.hpp>

class WorldStatePresentation : public WorldState {
    World& mWorld;
public:
    WorldStatePresentation(World& w) : mWorld{w} {}
    void handleInput() override;
    void update() override;
    void onEnter() override;
    void onExit() override;

};

#endif
