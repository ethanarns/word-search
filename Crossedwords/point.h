#ifndef POINT_H
#define POINT_H

#include <string>

class Point
{
public:
    short x;
    short y;
    Point();
    Point(short xIn, short yIn);
    ~Point();
    bool doesOverlap(Point* p);
    bool doesOverlap(short xIn, short yIn);
    std::string toString();
};

#endif // POINT_H
