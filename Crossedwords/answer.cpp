#include "answer.h" // Brings in <string>

#include <locale> // For toUpper()
#include <iostream>
#include <algorithm> // For transform()
#include <iostream>

#include "point.h"

std::string baseStr;
short sX;
short sY;
int direction;

enum Direction {
    North = 1,
    East = 2,
    South = 3,
    West = 4,
};

// Hoists declaration
std::string toUpperCase(std::string str);

Answer::Answer(std::string str, short startX, short startY, int dir)
{
    if(startX < 0 || startY < 0) {
        std::cout << "ERROR: Invalid Answer position" << std::endl;
        return;
    }

    baseStr = toUpperCase(str);
    sX = startX;
    sY = startY;
    direction = dir;
    std::cout << "Answer created (" << baseStr << ")" << std::endl;
}

Answer::Answer() {
    baseStr = "TEST";
    sX = 0;
    sY = 0;
    direction = Direction::East;
    std::cout << "Answer created (Default)" << std::endl;
}

Answer::~Answer() {
    std::cout << "Answer destroyed (" << baseStr << ")" << std::endl;
}

std::string toUpperCase(std::string str)
{
    std::transform(str.begin(), str.end(), str.begin(), toupper);
    return str;
}

short Answer::getEndLetterX()
{
    switch(direction) {
        case Direction::North:
            return sX;
        case Direction::South:
            return sX;
        case Direction::East:
            return sX + baseStr.length() - 1;
        case Direction::West:
            return sX - baseStr.length() - 1;
        default:
            std::cout << "Error in getEndLetterX()" << std::endl;
            return -1;
    }

    return -1;
}

short Answer::getEndLetterY()
{
    switch(direction) {
        case Direction::North:
            return sY - baseStr.length() - 1;
        case Direction::South:
            return sY + baseStr.length() - 1;
        case Direction::East:
            return sY;
        case Direction::West:
            return sY;
        default:
            std::cout << "Error in getEndLetterY()" << std::endl;
            return -1;
    }

    return -1;
}

bool Answer::doesOverlap(Answer* ans_p) {
    // First, make a bunch of points for each letter
    Point thisPts[this->baseStr.length()];
    switch(this->direction) {
        case Direction::North:
            for (unsigned short i = 0; i < this->baseStr.length(); i++) {
                thisPts[i] = Point(this->sX, this->sY - i);
            }
            break;
        case Direction::South:
            for (unsigned short i = 0; i < this->baseStr.length(); i++) {
                thisPts[i] = Point(this->sX, this->sY + i);
            }
            break;
        case Direction::East:
            for (unsigned short i = 0; i < this->baseStr.length(); i++) {
                thisPts[i] = Point(this->sX + i, this->sY);
            }
            break;
        case Direction::West:
            for (unsigned short i = 0; i < this->baseStr.length(); i++) {
                thisPts[i] = Point(this->sX - i, this->sY);
            }
            break;
    }
    Point thosePts[ans_p->baseStr.length()];
    switch(ans_p->direction) {
        case Direction::North:
            for (unsigned short i = 0; i < ans_p->baseStr.length(); i++) {
                thosePts[i] = Point(ans_p->sX, ans_p->sY - i);
            }
            break;
        case Direction::South:
            for (unsigned short i = 0; i < ans_p->baseStr.length(); i++) {
                thosePts[i] = Point(ans_p->sX, ans_p->sY + i);
            }
            break;
        case Direction::East:
            for (unsigned short i = 0; i < ans_p->baseStr.length(); i++) {
                thosePts[i] = Point(ans_p->sX + i, ans_p->sY);
            }
            break;
        case Direction::West:
            for (unsigned short i = 0; i < ans_p->baseStr.length(); i++) {
                thosePts[i] = Point(ans_p->sX - i, ans_p->sY);
            }
            break;
    }

    return false;
}
