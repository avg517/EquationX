#include <cstddef>
#include <iostream>
#include "functionclass.cpp"
#include "basefunctions.cpp"
#include "functionclass.hpp"
#include "parser.cpp"
#include "parservariables.hpp"

void initzaparser(std::string input){
        int* identifiers=NULL;
        char** rawstrings=NULL;
        tokenize(input.c_str(), input.size(),&identifiers, &rawstrings, &num_tokens);
        definebasecommands();
        for (int i=0;i<=num_tokens;++i){
                problems.push_back(rawstrings[i]);
                tokenids.push_back(identifiers[i]);
        }
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
        func.appendacommand(IDENT, nullptr, exprnode,"a");
        func.empty();
        return 0;
}
