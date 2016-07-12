#ifndef ANSWER_H
#define ANSWER_H
#include <string>

class Answer
{
public:
    Answer(std::string str, short startX, short startY, int dir);
    short getEndLetterX();
    short getEndLetterY();
    std::string baseStr;
    short int sX;
    short int sY;
    short int direction;
};

#endif // ANSWER_H
