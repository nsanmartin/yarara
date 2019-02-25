#ifndef _WORLD_STATE_MOVE_H
#define _WORLD_STATE_MOVE_H

#include <World.hpp>
#include <State/WorldState.hpp>

class WorldStateMove : public WorldState {
    World& mWorld;
public:
    WorldStateMove(World& w) : mWorld{w} {}
    void HandleInput() override;
    void Update() override;
    void OnEnter() override;
    void OnExit() override;
};

#endif
