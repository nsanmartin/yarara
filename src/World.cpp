#include <iostream>
#include <chrono>
#include <thread>


#include <World.hpp>
#include <State/WorldStatePresentation.hpp>
#include <State/WorldStateMove.hpp>

World::World()
    : mContinue{true}, mMedia{*this}, mActiveCajita{},
      mStates{new WorldStatePresentation{*this},
              new WorldStateMove{*this}},
      mPresentState{}
{

}


World::~World() {
    for (auto state : mStates) {
        delete state;
    }
}

void World::Loop() {
    std::cout << "run!" << std::endl;
    mMedia.Init();

    while (mContinue) {
        HandleInput();
        Update();
        mMedia.Clear();
        for (auto& cajita : mCajitas) {
            mMedia.Draw(cajita);
        }
        mMedia.PresentScreen();
        
        std::this_thread::sleep_for(
            std::chrono::milliseconds(16));
        
    }
    
    mMedia.Close();
    std::cout << "bye" << std::endl;
}


void World::Update() {
    //todo:
}

