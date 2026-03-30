#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include "basefunctions.cpp"
#include "expressfunc.cpp"
#include "functionclass.cpp"
#include "functionclass.hpp"
#include "parser.hpp"
#include "parservariables.hpp"
#include "tokenizer/tokenizer.h"
#include "parser.cpp"
void initzaparser(std::string input){
        //create temporary variables for za parser
        int* identifiers=NULL;
        char** rawstrings=NULL;
        //tokenizing
        tokenize(input.c_str(), input.size(),&identifiers, &rawstrings, &num_tokens);
        //initializing symbols
        operators::definebaseoperators();
        //adding tonkens to the global variables of the parser
        for (int i=0;i<num_tokens;++i){
                problems.push_back(rawstrings[i]);
                tokenids.push_back(identifiers[i]);
        }
        //free(tokens) for no leakage
        free_tokens(identifiers, rawstrings, num_tokens);
}


int main(){
        std::ifstream fin("simpletest.math");
        //express yourself :D
        std::ostringstream fstr;
        fstr<<fin.rdbuf();
        std::string inputstr=fstr.str();
        initzaparser(inputstr);
        //dumbass i parsedExpression before i initialized the tokens :D
        parseroot();
        global_functions["main"]->evalcommands();
        std::cout<<"Function testfunc returned:"<<global_functions["main"]->returncode<<"\n";
        //if(global_functions["testfunc"]->variables["testvariable"]){std::cout<<*global_functions["testfunc"]->variables["testvariable"];} else {
          //      std::cout<<"muie variabila nu a fost creata\n";
        //}
        delete_all_functions();
        return 0;
}
