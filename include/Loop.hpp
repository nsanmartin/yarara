#ifndef _LOOP_H
#define _LOOP_H

#include <vector>

#include <Media.hpp>
#include <Cajita.hpp>

class Loop {

    bool mContinue;
    Media mMedia;
    std::vector<Cajita> mCajitas;
    size_t mActiveCajita;
public:

    Loop() : mContinue{true}, mMedia{}, mActiveCajita{} {}
    void Run();
    void Update();
    void PushCajita(Cajita c) { mCajitas.push_back(c); }
    bool ExistsActiveCajita() { mActiveCajita < mCajitas.size(); }

    Cajita& GetActiveCajita() { return mCajitas[mActiveCajita];}
};


#endif
