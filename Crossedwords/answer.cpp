#include "answer.h"
#include <string>
#include <locale> // For toUpper()
#include <iostream>
#include <algorithm> // For transform()

std::string baseStr;
short sX;
short sY;
int direction;

enum Direction {
    North = 1,
    Northeast = 2,
    East = 3,
    Southeast = 4,
    South = 5,
    Southwest = 6,
    West = 7,
    Northwest = 8
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
            return -1;
    }

    return -1;
}
