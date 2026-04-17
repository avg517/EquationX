#pragma once
#include <string>
#include "functionclass.hpp"
#include "parservariables.hpp"
int peek();
std::string advance();
expressnode* parseExpression(int min_bp,int maxparse);
void freeTree(expressnode* node);
short checkvariable(function* func,std::string varname);
float evaluate(expressnode* node,function* func);

