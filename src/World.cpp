#include <iostream>
#include <chrono>
#include <thread>


#include <World.hpp>

void World::Loop() {
    std::cout << "run!" << std::endl;
    mMedia.Init();

    while (mContinue) {
        mMedia.PollEvents();
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
    while (mMedia.HasEvents()) {
        Media::Key k{mMedia.PopKey()};
        switch (k) {
        case Media::Key::Left:
            if (ExistsActiveCajita()) {
                Cajita& c{GetActiveCajita()};
                c.MoveX(-2);
            }
            break;
        case Media::Key::Right:
            if (ExistsActiveCajita()) {
                Cajita& c{GetActiveCajita()};
                c.MoveX(2);
            }
            break;
        case Media::Key::Up:
            if (ExistsActiveCajita()) {
                Cajita& c{GetActiveCajita()};
                c.MoveY(-2);
            }
            break;
        case Media::Key::Down:
            if (ExistsActiveCajita()) {
                Cajita& c{GetActiveCajita()};
                c.MoveY(2);
            }
            break;
        case Media::Key::r:
            if (ExistsActiveCajita()) {
                Cajita& c{GetActiveCajita()};
                c.Rotate(6);
            }
            break;
        case Media::Key::q:
            std::cout << "quiting...";
            mContinue = false;
        default:
            break;
        }
            
    }
}

