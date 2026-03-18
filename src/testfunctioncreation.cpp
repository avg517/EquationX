#include <cstddef>
#include <iostream>
#include "basefunctions.cpp"
#include "expressfunc.cpp"
#include "functionclass.cpp"
#include "functionclass.hpp"
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
        definebasecommands();
        //adding tonkens to the global variables of the parser
        for (int i=0;i<num_tokens;++i){
                problems.push_back(rawstrings[i]);
                tokenids.push_back(identifiers[i]);
        }
        //free(tokens) for no leakage
        free_tokens(identifiers, rawstrings, num_tokens);
}


int main(){
        //express yourself :D
        std::string inputstr="(3+5)*4;testvariable;";
        initzaparser(inputstr);
        //dumbass i parsedExpression before i initialized the tokens :D
        expressnode* exprnode=parseExpression();//parsing (3+5)*4
        if (parseerror==true){
                std::cout<<"Parse error occured quitting...\n";
                return -1;
        }
        current=8;
        //got an error...a not defined...fuck...this aint good
        //ill remove the parsing protections, they're annoying and i check into evaluate anyway... 
        expressnode* noder=parseExpression(0,num_tokens);//parsing "testvariable;"
        
        if (parseerror==true){
                std::cout<<"Parse error occured quitting...\n";
                return -1;
        }
        //creating a function tree manually i guess(fuck testing)
        definefunction("testfunc");
        global_functions["testfunc"]->appendacommand(DEFINE, nullptr, nullptr, "testvariable");
        global_functions["testfunc"]->appendacommand(EXPRESSION, nullptr, exprnode);
        global_functions["testfunc"]->appendacommand(SEPARATOR,nullptr, nullptr);
        global_functions["testfunc"]->appendacommand(EXPRESSION,nullptr,noder);
        global_functions["testfunc"]->evalcommands();
        std::cout<<"Function testfunc returned:"<<global_functions["testfunc"]->returncode<<"\n";
        //if(global_functions["testfunc"]->variables["testvariable"]){std::cout<<*global_functions["testfunc"]->variables["testvariable"];} else {
          //      std::cout<<"muie variabila nu a fost creata\n";
        //}
        delete_all_functions();
        return 0;
}
