#include <iostream>
#include <chrono>
#include <thread>


#include <World.hpp>
#include <State/WorldStatePresentation.hpp>
#include <State/WorldStateMove.hpp>

World::World()
    :
        mContinue{true},
        mMedia{*this},
        mActiveCajita{},
        mActivePolygon{},
        mStates{new WorldStatePresentation{*this}, new WorldStateMove{*this}},
        mPresentState{}
{ }


World::~World() {
    for (auto state : mStates) { delete state; }
    for (auto poly : mPolygons) { delete poly; }
}
    

void World::loop() {
    mMedia.init();

    while (mContinue) {
        handleInput();
        update();
        mMedia.clear();
        //for (auto& cajita : mCajitas) { mMedia.Draw(cajita); }
        for (auto poly : mPolygons) { poly->draw(mMedia); }
        
        mMedia.presentScreen();
        
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
        
    }
    
    mMedia.close();
    std::cout << "bye" << std::endl;
}


void World::update() {
    //todo:
}

