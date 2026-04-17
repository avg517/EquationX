#pragma once
#include <cstring>
#include <iostream>
#include <deque>
#include <string>
#include <unordered_map>
#include "parservariables.hpp"
#include "tokenizer/tokens.h"
#include "tokenizer/tokenizer.h"
#include "functionclass.hpp"
#include "expressfunc.hpp"
#include "expressfunc.cpp"
//TODO make negative numbers work
//TODO make functions

bool checknode(expressnode* nodetocheck){
        if (nodetocheck){
                return 1;
        } else {
                return 0;
        }
}
void endparsing(){
        cleardeques();
        num_tokens=0;
        current=0;
        parseerror=false;
} 

void parserootfunc(){
        //parse parameters
        std::string adv=advance();
        int peeker=peek();
        if (peeker != oparantesesign){
                parseerror=true;
                return;
        }
        std::deque<std::string> params;
        while (peeker != cparantesesign){
               if (peeker!=identifiersign){
                       //ERROR:expected identifers, got something else
                       parseerror=true;
                       return;
               }
                
        }
        
}
void parsecommands(std::string strtoparse,bool* parsefail){//this function is work in progress
        //tokenizing the whole string
        int* identifiers=NULL;
        char ** rawstrings=NULL;
        tokenize(strtoparse.c_str(),strtoparse.size(), &identifiers, &rawstrings, &num_tokens);
        //pushing into the memory
        for (int i=0;i<num_tokens;++i){
                problems.push_back(rawstrings[i]);
                tokenids.push_back(identifiers[i]);
        }
        free_tokens(identifiers, rawstrings, num_tokens);
        //finished tokenizing, now doing whole thing
        while (current<num_tokens){
               int peeker=peek();
               if (peeker==identifiersign){
                        if (problems[current]=="func"){
                                
                        } else if (problems[current]=="def"){
                                
                        }
               }
        }
        
}

int runequ(std::string strtoparse){//do not use this function, this is to test the parseExpression function
        int* identifiers=NULL;
        char** rawstrings=NULL;
        tokenize(strtoparse.c_str(),strtoparse.size(),&identifiers,&rawstrings,&num_tokens);
        definebasecommands();
        for (int i=0;i<num_tokens;++i){
                problems.push_back(rawstrings[i]);
                tokenids.push_back(identifiers[i]);
        }
        variables["a"]=new float(2);
        expressnode* tree=parseExpression(0, num_tokens);
        if (!tree || parseerror){
                endparsing();
                std::cout<<"parsing failed\n";
                return -1;
        }
        float answer=evaluate(tree, nullptr);
        std::cout<<answer<<'\n';
        freeTree(tree);
        free_tokens(identifiers, rawstrings, num_tokens);
        endparsing();
        return 0;
}

