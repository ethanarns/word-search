#ifndef READER_H
#define READER_H

#include <string>

class Reader
{
public:
    Reader();
    ~Reader();
    static std::string getRandomWord();
    static long getFileLength();
};

#endif // READER_H
