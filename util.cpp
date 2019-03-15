#include <iostream>
#include "util.h"

void readFile(std::vector <std::string> & words, std::string path){
    std::ifstream in(path.c_str());
    if(!in.is_open()) std::cout << "Open Failed!" << std::endl;
    char c;
    bool flag = true;
    std::string buffer = "";
    while ((c = in.get()) != EOF){
        if(isalpha(c)){
            if(c >= 'A' && c <= 'Z')
                c = tolower(c);
            buffer += c;
            flag = true;
        } else if(flag == true){
            words.push_back(buffer);
            buffer = "";
            flag = false;
        }
    }
}
