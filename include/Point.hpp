#ifndef _POINT_H
#define _POINT_H


class Point {
public:
    int mX, mY;
    Point(int x = 0, int y = 0) : mX{x}, mY{y} {}
    void Rotate(int angle);
    Point& operator += (const Point &p) {
        mX += p.mX; mY += p.mY; return *this;
    }
    Point& operator -= (const Point &p) {
        mX -= p.mX; mY -= p.mY; return *this;
    }

    Point operator -() { return Point(-mX, -mY); }
    Point& operator/=(int d) { mX/=d; mY/=d; return *this;}
};

Point operator+ (const Point& p, const Point& q);
Point operator- (const Point& p, const Point& q);

#endif
