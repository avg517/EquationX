#pragma once

#include <string>
#include <unordered_map>
#include "parservariables.hpp"
#include "operators.hpp"
std::unordered_map<std::string,float*> variables;//this will probably be used for global constants like pi or smh
class function;//forward definition for some fucking reason
class expressnode;
function* current_function_parsing=nullptr;
function* current_function_running=nullptr;
//parser.cpp functions these also need to be moved to parser class
bool checkode(expressnode* nodetocheck);
void endparsing();
bool parsefunctioninputs(std::string func_name);
bool recognizeidentifier();
bool parseidentity();
bool parsecommand();
bool parsebrackets();
bool parsefunction();
bool parseroot();
int runequ();//except you pookie cause youre special(depricated and just for testing)
void cleardeques();
//that absolutely works (expressfunc.cpp functions), these need to be moved to their respective classes
int peek();//parser class (to be created)
std::string peek_string();//parser class
void advance();//parser class
bool advance_expect(std::string errmsg);//parser class
expressnode* parseExpression(int min_bp,int maxparse);//parser class
void freeTree(expressnode* node);//expressnode class
short checkvariable(function* func,std::string varname);//the fuck are you even doing in these files???
float evaluate(expressnode* node,function* func);//expression class
