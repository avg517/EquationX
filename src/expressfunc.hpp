#include <iostream>
#include "parservariables.hpp"
#include "tokens.h"
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
                if (checkvariable(current)){
                        //problems[current]=std::to_string(*variables[problems[current]]);
                        //tokenids[current]=numbersign;
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
float evaluate(expressnode* node) {
        if (!node->left && !node->right) {
                if (node->isidentifier){
                        return *variables[node->value]; 
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
        float left = evaluate(node->left);
        float right = evaluate(node->right);
        return it->second(left, right);
}


