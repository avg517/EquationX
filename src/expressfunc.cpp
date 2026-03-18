#pragma once
#include <cstdlib>
#include <iostream>
#include "parservariables.hpp"
#include "tokens.h"
#include "expressfunc.hpp"
#include "functionclass.cpp"
function* currentfuncrunning=nullptr;
int peek() {
        if (current < num_tokens)
                return tokenids[current];
        return -1;
}

std::string advance() {
        return problems[current++];
}
expressnode* parseExpression(int min_bp = 0,int maxparse=num_tokens) {
        expressnode* left = nullptr;
        bool identifiersgn=false;
        int type = peek();
        if (type == numbersign) {
                //fukcing dumbass i deleted this
                identifiersgn=false;
                left = new expressnode(advance(),identifiersgn);
        } else if (type == identifiersign) {
                if (checkvariable(currentfuncrunning,problems[current])==2){
                        identifiersgn=true;
                } else {
                        parseerror=true;
                        std::cout<<problems[current]<<" not defined\n";
                        return nullptr;
                }
                left = new expressnode(advance(),identifiersgn);
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
                if (current >= num_tokens) {break;}
                int type = peek();
                if (type == semicolonsign) {break;}
                std::string op = problems[current];
                if (precedence.find(op) == precedence.end()) {break;}
                int bp = precedence[op];
                if (bp < min_bp) {break;}
                advance(); 
                expressnode* right = parseExpression(bp + 1); // right binding
                left = new expressnode(op, left, right);
        }
        return left;
}
void freeTree(expressnode* node) {
        if (!node) return;
        freeTree(node->left);
        freeTree(node->right);
        delete node;
}
short checkvariable(function* func,std::string varname){
        //if it exists in the function then return 1;
        if (func){
                if (func->variables.find(varname)!=func->variables.end()) {
                        return 1;
                }
        }
        //if it doesnt exist in the function search the global variables
        if (variables.find(varname) != variables.end()){
                return 2;
        }
        //if it doesnt exist at all return -1;
        return -1;
}

float evaluate(expressnode* node,function* func=nullptr) {
        if (!node->left && !node->right) {
                if (node->isidentifier){
                        //check if variable is defined:
                        short checkvar=checkvariable(func,node->value);
                        if (checkvar==1){
                                return *func->variables[node->value];
                        } else if (checkvar==2){
                                return *variables[node->value];
                        } else if (checkvar==-1){
                                return -1;
                                parseerror=true;
                        } else {
                                std::cout<<"Something went wrong, its the code's fault, not yours\n";
                                exit(EXIT_FAILURE);
                        }
                        std::cout<<node->value<<" ";
                }{
                        return std::stof(node->value); 
                }
        }
        auto it = baseoperators.find(node->value);
        if (it == baseoperators.end()) {
                std::cout << "Unknown operator: " << node->value << "\n";
                return 0;
        }
        float left = evaluate(node->left,func);
        float right = evaluate(node->right,func);
        return it->second(left, right);
}


