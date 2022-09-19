#ifndef _POLYGON_H
#define _POLYGON_H

#include <cstdint>
#include <vector>
#include <iostream>
#include <Angle.hpp>
#include <Point.hpp>

class Media;

class Polygon {
protected:
    uint64_t mColor;
public:
    std::vector<Point> mVertices;
    Point mPos;
    Angle mAngle;

    Polygon(std::vector<Point> vertices, uint64_t color,
            Point pos = Point{})
        : mColor{color}, mVertices{vertices}, mPos{}, mAngle{}
        {}
    virtual ~Polygon() {}
    
    void moveX(int i) { mPos += Point{i, 0}; }
    void moveY(int i) { mPos += Point{0, i}; }
    void rotate(int i) { mAngle += i; }
    int verticesCount() const { return mVertices.size(); }
    std::vector<Point> getPoints() { return mVertices; }

    virtual void draw(Media& m) const;
};



#endif
