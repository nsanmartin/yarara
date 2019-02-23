#ifndef _ANGLE_H
#define _ANGLE_H

class Angle {
public:
    int mRot;
    Angle(int r = 0) : mRot{r} {}
    
    Angle& operator+=(int r) { if (r < 0) {r = r * (r/360) + 360;}; mRot += r; mRot %= 360; return *this; }
    Angle& operator-=(int r) { mRot += -r; return *this; }
    Angle& operator+=(const Angle & o) { return (*this += o.mRot); }
    Angle& operator-=(const Angle & o) { return (*this -= o.mRot); }
};

#endif
