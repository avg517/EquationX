#include <cstddef>
#include <iostream>
#include <string>
#include "parser.cpp"
int main(){
        std::string input;
        while (input!="quit"){
                std::getline(std::cin,input);
                runequ(input);
        }
        return 0;
}
