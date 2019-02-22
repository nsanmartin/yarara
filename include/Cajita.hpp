#ifndef _CAJITA_H
#define _CAJITA_H

#include <cstdint>



class Cajita {
    double mRot;
    uint64_t mColor;
public:
    int mX, mY, mZ;
    int mPosX, mPosY;

    Cajita(int x = 1, int y = 1)
        : mX{x}, mY{y}, mZ{1}, mPosX{}, mPosY{}, mRot{} {}
    void MoveY(int i) { mPosY += i; }
    void MoveX(int i) { mPosX += i; }

};



#endif
