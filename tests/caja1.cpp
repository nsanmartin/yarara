#include <Loop.hpp>


int main () {
    Loop l{};
    l.PushCajita(Cajita{100, 100});
    l.Run();
}
