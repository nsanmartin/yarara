#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <numeric>


#include <Media.hpp>
#include <Polygon/Triangle.hpp>

void Triangle::draw(Media& media) const {

    Point center{};
    for (auto& p : mVertices) {
        if (p.mX > center.mX) center.mX = p.mX;
        if (p.mY > center.mY) center.mY = p.mY;
    }
    
    center /= 2;
    Point pos {mPos};
    int rotation {mAngle.mRot};
    
    std::vector<Point> vertices;
    std::transform(mVertices.begin(), mVertices.end(),
                   std::back_inserter(vertices),
                   [&center, &rotation, &pos](const Point& p) {
                       Point res {p - center};
                       res.Rotate(rotation);
                       res += pos + center;
                       return Point{res.mX, res.mY};
                   });
    
    media.fillTriangle(vertices);
};
