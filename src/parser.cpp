#include <cstring>
#include <fstream>
#include <iostream>
#include <deque>
#include <string>
#include <unordered_map>
#include "basefunctions.cpp"
#include "parservariables.hpp"
#include "tokenizer/tokens.h"
#include "tokenizer/tokenizer.h"
#include "functionclass.hpp"
#include "expressfunc.cpp"
#include "parser.hpp"
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
        cleardeques();//this clears the deques like problems and tokenids
        num_tokens=0;//number of tokens is reset for obvious reasons
        current=0;//current is also reset to 0
        parseerror=false;//parse error also resetted
} 

bool parsefunctioninputs(std::string func_name){
        while(peek()!=cparantesesign && current<=num_tokens){ 
                if(peek()!=identifiersign && peek()!=commasign){
                        std::cout<<"Wrong parameters in function:\""<<func_name<<"\"\n";
                        return false;
                }
                advance();
        }//this is not done yet, i'll check after actually adding parameters in functions 😭
        if (peek()!=cparantesesign){
                std::cout<<"Reached EOF before parsing function parameters\n";
                return false;
        }
        return true;
}

bool recognizeidentifier(){
        std::string peeker=peek_string();
        if (peeker == "def"){return 1;}
        if (peeker == "if"){return 1;}
        if (peeker == "for"){return 1;}
        if (peeker == "while"){return 1;}
        if (peeker == "return"){return 1;}
        return 0;
}

bool parseidentity(){//i dont have an identity, thank you very much
        std::string peeker=peek_string();//peek into the string
        //lets check surface level commands:
        if (!recognizeidentifier()){
                //if its in the functions then its a function
                if(global_functions.find(peeker)!=global_functions.end()){
                        //then its a function call
                        current_function_parsing->appendacommand(CALLFUNC);
                        return true;
                } else if (checkvariable(current_function_parsing, peeker)){ //or maybe its just an expression caue why not
                        //aight the variable exists, this is definetly an parseExpression
                        expressnode* expression=parseExpression(0, num_tokens);//parsing the expression
                        current_function_parsing->appendacommand(EXPRESSION, expression);//good now appending it along with the SEPARATOR
                        current_function_parsing->appendacommand(SEPARATOR);
                        return true;
                }
                std::cout<<"Something got fucked error\n";
                return false;
        }
        //if it got this far then it was recognized as a command :D 
        if (peeker=="def"){
                std::cout<<"Defining variable\n";
                if (!advance_expect("Unexpected EOF\n")){return false;}
                //advance and check the identifier
                if(!(peek()==identifiersign)){
                        return false;
                }
                std::string varname=peek_string();
                //advance and check if there is an equal sign or ";"
                if (!advance_expect("Unexpected EOF\n")){return false;}
                if (peek()==semicolonsign){
                        current_function_parsing->appendacommand(DEFINE, nullptr, nullptr,varname);
                        current_function_parsing->appendacommand(SEPARATOR);
                        return true;
                } else if (peek()==equalsign){//if its an equalsign advance and guess what? parseExpression
                        if (!advance_expect("Unexpected EOF\n")){return false;}//EOF error here 
                        //parse the expression
                        expressnode* expression=parseExpression(0,num_tokens);
                        //append the full DEFINE command along with the SEPARATOR
                        current_function_parsing->appendacommand(DEFINE, nullptr, nullptr,varname);
                        current_function_parsing->appendacommand(EXPRESSION, expression);
                        current_function_parsing->appendacommand(SEPARATOR);
                }
                return true;//if it got here it worked
        } else if (peeker=="return"){
                std::cout<<"Returning\n";
                if (!advance_expect("Unexpected EOF\n")){return false;}//EOF error here 
                if(peek()==semicolonsign){//it its return; then we dont add the expression to it
                        current_function_parsing->appendacommand(RETURN);
                        current_function_parsing->appendacommand(SEPARATOR);
                        return true;
                }
                //else parse the damn expression
                expressnode* expression=parseExpression(0,num_tokens);
                current_function_parsing->appendacommand(RETURN);
                current_function_parsing->appendacommand(EXPRESSION, expression);
                current_function_parsing->appendacommand(SEPARATOR);
        } else if (peeker=="if"){
                std::cout<<"If starting\n";//starting the if statement
                
                if (!advance_expect("Unexpected EOF\n")){return false;}//expects the advance
                
                expressnode* thecondition=parseExpression(0,num_tokens);//parsing the condition like if a==4;{code here;}
                
                current_function_parsing->appendacommand(IFSTART);//appending the IFSTART
                
                if (parseerror){return false;}//bullshit error out here
                
                if (!advance_expect("Unexpected EOF\n")){return false;}//expects the advance again
                
                if (!(peek()==obracketsign)){return false;}//ofc we expect the bracket open sign
                
                commandnode *cmdifstartpointer=current_function_parsing->lastcmdptr;
                current_function_parsing->appendacommand(EXPRESSION, thecondition);
                current_function_parsing->appendacommand(SEPARATOR);
                if(!parsebrackets()){return false;}//something went wrong in the if statement and also dont forget it parses the commands inside
                
                current_function_parsing->appendacommand(IFEND);//adding ifend to the end of the function
                
                cmdifstartpointer->jumptocmdnode=current_function_parsing->lastcmdptr;//now the last step is to make the if statement jump to the ifend cause yes
        } else if (peeker=="while") {
                if (!advance_expect("Unexpected EOF\n")){return false;}//expects the advance
                expressnode* thecondition=parseExpression(0,num_tokens);
                if (parseerror){return false;}
                if (!advance_expect("Unexpected EOF\n")){return false;}//expects the advance
        }
        return true;
}

bool parsecommand(){
        int peeker=peek();
        switch (peeker) {
                case identifiersign:
                        //wtf type of command is it you may ask well...idk either :D?
                        //could be a function call...could be a define could be an if or a for
                        parseidentity();
                break;
                case numbersign:
                        //definetly an expression
                        expressnode* expression=parseExpression(0, num_tokens);
                        if (parseerror){return false;}//if theres a parseExpression error fucking stop it
                        current_function_parsing->appendacommand(EXPRESSION, expression);
                        current_function_parsing->appendacommand(SEPARATOR);
                break;
        }
        return true;
}

bool parsebrackets(){
        //defining the end of file error message
        std::string eoferrmsg="Reached EOF before closing bracket closing in function \""+current_function_parsing->funcname+"\"\n";
        while (advance_expect(eoferrmsg)){
                parsecommand();
                if (peek()==cbracketsign){
                        break;
                }
        }
        return true;
}

bool parsefunction(){
        //some function variables so that i can define the function
        std::string func_name;
        if (!advance_expect("Reached EOF before defining function")){return false;}//expects im able to advance
        //gets the function name
        if (!(peek()==identifiersign)){
                std::cout<<"Expected identifier to create function name, got:\""<<peek_string()<<"\"\n";
                return false;//error shit here
        }//expects a name not something else
        func_name=peek_string();//got the function func_name
        if (!advance_expect("Reached EOF before defining function")){return false;}//expects im able to advance again
        if (peek()!=oparantesesign){
                std::cout<<"Expected function parameters";
        }
        //expect function parameter definition to be right
        if (!advance_expect("Reached EOF before defining function")){return false;}//expects im able to advance again
        if (!parsefunctioninputs(func_name)){return false;}//checks the parsefunctioninputs i guess
        if (!advance_expect("Reached EOF before defining function")){return false;}//expects im able to advance again
        if (peek()!=obracketsign){
                std::cout<<"Expected actual function definition dumbass in \""<<func_name<<"\"\n";
        }
        definefunction(func_name);
        current_function_parsing=global_functions[func_name];
        parsebrackets();
        return true;
}

bool parseroot(){
        while (current<num_tokens){
                int peeker=peek();
                if (peeker==identifiersign){
                        std::string current_string=peek_string();
                        if (current_string=="func"){
                                parsefunction();
                        }
                }
                advance();
        }
        return true;
}
int runequ(std::string strtoparse){//do not use this function, this is to test the parseExpression function
        int* identifiers=NULL;
        char** rawstrings=NULL;
        tokenize(strtoparse.c_str(),strtoparse.size(),&identifiers,&rawstrings,&num_tokens);
        operators::definebaseoperators();
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

