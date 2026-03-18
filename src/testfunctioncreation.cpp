#include <cstddef>
#include <iostream>
#include "functionclass.cpp"
#include "basefunctions.cpp"
#include "functionclass.hpp"
#include "parser.cpp"
#include "parservariables.hpp"

void initzaparser(std::string input){
        //create temporary variables for za parser
        int* identifiers=NULL;
        char** rawstrings=NULL;
        //tokenizing
        tokenize(input.c_str(), input.size(),&identifiers, &rawstrings, &num_tokens);
        //initializing symbols
        definebasecommands();
        //adding tonkens to the global variables of the parser
        for (int i=0;i<=num_tokens;++i){
                problems.push_back(rawstrings[i]);
                tokenids.push_back(identifiers[i]);
        }
        //free(tokens) for no leakage
        free_tokens(identifiers, rawstrings, num_tokens);
}


int main(){
        function func;
        std::string input="(3+5)*4";
        func.funcname="thefunction";
        expressnode* exprnode=parseExpression();
        initzaparser(input);
        if (parseerror==true){
                std::cout<<"Parse error occured quitting...\n";
                return -1;
        }
        func.appendacommand(DEFINE, nullptr, nullptr);
        func.appendacommand(IDENT, nullptr, nullptr,"a");
        
        func.empty();
        return 0;
}
