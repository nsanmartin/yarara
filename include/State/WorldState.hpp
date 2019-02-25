#ifndef _WORLD_STATE_H
#define _WORLD_STATE_H


class WorldState {
public:
    virtual ~WorldState() {};
    virtual void HandleInput() = 0;
    virtual void Update() = 0;
};

#endif
