#ifndef ANSWER_H
#define ANSWER_H
#include <string>

class Answer
{
public:
    Answer(std::string str, short startX, short startY, int dir);
    ~Answer();
    short getEndLetterX();
    short getEndLetterY();
    std::string baseStr;
    short sX;
    short sY;
    short direction;
};

#endif // ANSWER_H
