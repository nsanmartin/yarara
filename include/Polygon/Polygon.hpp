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
    ~Polygon() {}
    
    void MoveX(int i) { mPos += Point{i, 0}; }
    void MoveY(int i) { mPos += Point{0, i}; }
    void Rotate(int i) { mAngle += i; }
    int VerticesCount() const { return mVertices.size(); }
    std::vector<Point> GetPoints() { return mVertices; }

    virtual void Draw(Media& m) const;
};



#endif
