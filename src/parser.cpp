#include <charconv>
#include <iostream>
#include <fstream>
#include <deque>
#include <string>
#include <unordered_map>
#include <variant>
#include "tokens.h"
#include "parser.hpp"
#include "tokenizer.h"
int current=0;//current global token
bool parseerror=false;
//TODO make negative numbers work
struct Node {
        std::string value;
        Node* left;
        Node* right;

        Node(std::string v) : value(v), left(nullptr), right(nullptr) {}
        Node(std::string v, Node* l, Node* r) : value(v), left(l), right(r) {}
};

std::unordered_map<std::string, int> precedence = {
    {"+", 10},
    {"-", 10},
    {"*", 20},
    {"/", 20},
    {"%", 20}
};

int definevar(int posvarname,int posvalue){
        auto temp=variables.find(problems[posvarname]);
        if (temp!=variables.end()){
                std::cout<<"redefinition of variable\n";
                return -1;
        }
        temp=variables.find(problems[posvalue]);
        if(temp!=variables.end()){
                float* temp=new float;
                *temp=*variables[problems[posvalue]];
                variables[problems[posvarname]]=temp;
                return 1;
        } else {
                std::cout<<"WTF ARE YOU DEFINING BRO\n";
                return -1;
        }
        return 0;
}



bool checkvariable(int varpos){
        auto temp=variables.find(problems[varpos]);
        if (temp!=variables.end()){
                return 1;
        }
        return 0;
}
bool checknode(Node* nodetocheck){
        if (nodetocheck){
                return 1;
        } else {
                return 0;
        }
}

int peek() {
        if (current < num_tokens)
                return tokenids[current];
        return -1;
}

std::string advance() {
        return problems[current++];
}
Node* parseExpression(int min_bp = 0) {
        Node* left = nullptr;

        int type = peek();
        if (type == numbersign) {
                //fukcing dumbass i deleted this
                left = new Node(advance());
        } else if (type == identifiersign) {
                if (checkvariable(current)){
                        problems[current]=std::to_string(*variables[problems[current]]);
                        tokenids[current]=numbersign;
                } else {
                        parseerror=true;
                        std::cout<<problems[current]<<" not defined\n";
                        return nullptr;
                }
                left = new Node(advance());
        } else if (type == oparantesesign) {
                advance();
                left = parseExpression();
                if (peek() != cparantesesign) {
                        std::cout << "Error: Missing ')'\n";
                        parseerror=true;
                        return nullptr;
                }
                advance();
        } else {
                parseerror=true;
                std::cout << "Unexpected token\n";
                return nullptr;
        }
        while (true) {
        if (current >= tokenids.size()) {break;}
        int type = peek();
        if (type == semicolonsign) {break;}
        std::string op = problems[current];
        if (precedence.find(op) == precedence.end()) {break;}
        int bp = precedence[op];
        if (bp < min_bp) {break;}
        advance(); 
        Node* right = parseExpression(bp + 1); // right binding
        left = new Node(op, left, right);
        }
        return left;
}
void freeTree(Node* node) {
        if (!node) return;
        freeTree(node->left);
        freeTree(node->right);
        delete node;
}
float evaluate(Node* node) {
        if (!node->left && !node->right) {
                return std::stof(node->value); 
        }
        auto it = baseoperators.find(node->value);
        if (it == baseoperators.end()) {
                std::cout << "Unknown operator: " << node->value << "\n";
                return 0;
        }
        float left = evaluate(node->left);
        float right = evaluate(node->right);
        return it->second(left, right);
}

void endparsing(){
        cleardeques();
        num_tokens=0;
        current=0;
        parseerror=false;
}
int runequ(std::string strtoparse){
        int* identifiers=NULL;
        char** commands=NULL;
        tokenize(strtoparse.c_str(),strtoparse.size(),&identifiers,&commands,&num_tokens);
        definebasecommands();
        for (int i=0;i<num_tokens;++i){
                problems.push_back(commands[i]);
                tokenids.push_back(identifiers[i]);
        }
        variables["a"]=new float(2);
        Node* tree=parseExpression();
        if (!tree || parseerror){
                endparsing();
                std::cout<<"parsing failed\n";
                return -1;
        }
        float answer=evaluate(tree);
        std::cout<<answer<<'\n';
        freeTree(tree);
        free_tokens(identifiers, commands, num_tokens);
        endparsing();
        return 0;
}
