#include <World.hpp>
#include <iostream>

int main () {
    std::cout << "Press `s' to start\n"
              << "Arrows to move\n"
              << "`r' od `R' to rotate\n"
              << "`Esc' to clear the triangle\n"
              << "`q' to quit\n";
    World w{};
    w.Loop();
}
