#include "reader.h" // Brings in <string>

#include <fstream>
#include <iostream>

/*
 * A static class used for accessing the dictionary file
 * Needs no constructors or destructors
 */

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
            return str;
        }
        i++;
    }

    return "Error!";
}
