#pragma once
#include <charconv>
#include <cstdarg>
#include <cstdlib>
#include <unordered_map>
#include <string>
#include <deque>
#include "parser.hpp"
//TODO: slowly empty this depricated damn file and move everything into parser.cpp and parser.hpp 
//global variables to parse
int current=0;
bool parseerror=false;
std::deque<std::string> problems;
std::deque<int> tokenids;
int num_tokens=0;
//expressnode definition
/*
Structs are kinda...old know ;)
struct expressnode {
        std::string value;
        expressnode* left;
        expressnode* right;
        bool isidentifier;
        expressnode(std::string v,bool ident) : value(v),left(nullptr), right(nullptr), isidentifier(ident) {}
        expressnode(std::string v, expressnode* l, expressnode* r) : value(v), left(l), right(r) {}
};*/

class expressnode {//class definition of expressnode (this is literally to add the functions inside the expressnode instead of holding them in 500 different files)
        public:
                std::string value;
                expressnode* left;
                expressnode* right;
                bool isidentifier;
                //constructors
                expressnode(std::string v, bool ident) {
                        this->value=v;
                        this->left=nullptr;
                        this->right=nullptr;
                        this->isidentifier=ident;
                }
                expressnode(std::string v, expressnode* l, expressnode* r){
                        this->value=v;
                        this->left=l;
                        this->right=r;
                        this->isidentifier=false;
                }
};

void cleardeques(){
        problems.clear();
        operators::baseoperators.clear();
        tokenids.clear();
}
