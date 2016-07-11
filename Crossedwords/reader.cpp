#include "reader.h"

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>

Reader::Reader()
{

}

std::string Reader::getRandomWord() {
    std::ifstream file("./dictionary.txt");
    std::string line;
    unsigned int length = 0;
    while(std::getline(file, line)) {
        length++;
        std::cout << line << std::endl;
    }
    if(length == 0)
        return "Error, no words in file";

    return "yep";
}
