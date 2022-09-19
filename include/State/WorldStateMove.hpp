#ifndef _WORLD_STATE_MOVE_H
#define _WORLD_STATE_MOVE_H

#include <World.hpp>
#include <State/WorldState.hpp>

class WorldStateMove : public WorldState {
    World& mWorld;
public:
    WorldStateMove(World& w) : mWorld{w} {}
    void handleInput() override;
    void update() override;
    void onEnter() override;
    void onExit() override;
};

#endif
