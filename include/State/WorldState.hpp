#ifndef _WORLD_STATE_H
#define _WORLD_STATE_H


class WorldState {
public:
    virtual ~WorldState() {};
    virtual void handleInput() = 0;
    virtual void update() = 0;
    virtual void onEnter() = 0;
    virtual void onExit() = 0;
};

#endif
