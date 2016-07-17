#include "reader.h"

#include <fstream>
#include <string>
#include <iostream>

Reader::Reader()
{
    std::cout << "Reader initialized" << std::endl;
}

Reader::~Reader()
{
    std::cout << "Reader destructed" << std::endl;
}

long Reader::getFileLength() {
    std::ifstream file("./dictionary.txt");
    std::string line;
    long length = 0;
    while(std::getline(file, line)) {
        length++;
    }
    return length;
}

std::string Reader::getRandomWord() {
    long length = getFileLength();
    if(length < 1) {
        return "Error, file empty";
    }
    long randNum = rand()%length;
    std::ifstream file("./dictionary.txt");
    std::string line;
    int i = 0;
    while(std::getline(file, line)) {
        if(i == randNum){
            std::string str = "";
            for(unsigned short i = 0; i < line.length(); i++) {
                if(line.substr(i,1) != "'")
                    str += line.substr(i,1);
                else
                    break;
            }
            std::cout << "Random word: " << str << std::endl;
            return str;
        }
        i++;
    }

    return "Error!";
}
