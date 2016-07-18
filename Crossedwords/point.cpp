#include "point.h"

short x;
short y;

Point::Point()
{
    x = 0;
    y = 0;
}

Point::Point(short xIn, short yIn)
{
    x = xIn;
    y = yIn;
}

Point::~Point()
{

}

bool Point::doesOverlap(Point* p)
{
    return (p->x == this->x) && (p->y == this->y);
}

bool Point::doesOverlap(short xIn, short yIn)
{
    return (xIn == this->x) && (yIn == this->y);
}

std::string Point::toString() {
    std::string fuck("Point(");
    fuck += "" + std::to_string(x) + ", " + std::to_string(y) + ")";
    return fuck;
}
