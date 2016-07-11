#include "reader.h"

#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>

Reader::Reader()
{

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
            return line;
        }
        i++;
    }

    return "Error!";
}
