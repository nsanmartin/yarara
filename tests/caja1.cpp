#include <World.hpp>


int main () {
    World w{};
    w.PushCajita(Cajita{100, 100});
    w.Loop();
}
