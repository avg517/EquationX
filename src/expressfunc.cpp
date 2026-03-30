#pragma once
#include <cstdlib>
#include <iostream>
#include "parservariables.hpp"
#include "./tokenizer/tokens.h"
#include "parser.hpp"
#include "functionclass.cpp"
int peek() {
        if (current < num_tokens){
                return tokenids[current];
        }
        return -1;
}
std::string peek_string(){
        if (current < num_tokens){
                return problems[current];
        }
        return "no";
}
void advance() {
        current++;
}
bool advance_expect(std::string errmsg){
        advance();
        if(current>=num_tokens){
                std::cout<<errmsg;
                return false;
        }
        return true;
}
expressnode* parseExpression(int min_bp = 0,int maxparse=num_tokens) {
        expressnode* left = nullptr;
        bool identifiersgn=false;
        int type = peek();
        if (type == numbersign) {
                //fukcing dumbass i deleted this
                identifiersgn=false;
                left = new expressnode(peek_string(),identifiersgn);
                advance();
        } else if (type == identifiersign) {
                /*if (checkvariable(currentfuncrunning,problems[current])==2){//function support variables, idk if this will work or not(probably not)
                        identifiersgn=true;
                } else {
                        parseerror=true;
                        std::cout<<problems[current]<<" not defined\n";
                        return nullptr;
                }*/
                identifiersgn=true;
                left = new expressnode(peek_string(),identifiersgn);
                advance();
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
                std::cout << "Unexpected token\n"<<tokenids[current];
                return nullptr;
        }
        while (true) {
                if (current >= num_tokens) {break;}
                int type = peek();
                if (type == semicolonsign) {break;}
                std::string op = problems[current];
                if (operators::precedence.find(op) == operators::precedence.end()) {break;}
                int bp = operators::precedence[op];
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
                                std::cout<<"Variable named \""<<node->value<<"\" wasnt declared in this scope\n";
                                parseerror=true;
                                return -1;
                        } else {
                                std::cout<<"Something went wrong, its the code's fault, not yours\n";
                                exit(EXIT_FAILURE);
                        }
                        std::cout<<node->value<<" ";
                } else {
                        return std::stof(node->value); 
                }
        }
        auto it = operators::baseoperators.find(node->value);
        if (it == operators::baseoperators.end()) {
                std::cout << "Unknown operator: " << node->value << "\n";
                return 0;
        }
        float left = evaluate(node->left,func);
        float right = evaluate(node->right,func);
        return it->second(left, right);
}


