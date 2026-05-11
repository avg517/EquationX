#pragma once
#include "functionclass.hpp"
#include "parservariables.hpp"
#include "basefunctions.hpp"
#include <iostream>
#include <fstream>
std::ofstream outlogforfunc("functionlogs.txt");
#ifdef FUNC_LOGS
bool funclogs=true;
#else
bool funclogs=false;
#endif

void definefunction(std::string funcname){//creates a new gloabal function with funcname
        //if it already exists...nice try but it aint gonna work kid
        if(global_functions.find(funcname)!=global_functions.end()){
                std::cout<<"Redefinition of function:"<<funcname<<"\n";
                return;
        }
        //green flag...create the new function* with function name
        global_functions[funcname]=new function;
        global_functions[funcname]->funcname=funcname;
}

void delete_all_functions(){//this function deletes everything
        for (auto i:global_functions){
                //weird ass syntax here...
                i.second->empty();
                delete i.second;
                
        }
}

void definevariable(std::string varname,float value,function* func){//defines a variable with value and varname
        float* temp=new float(value);
        //!func->create the variable globally if possible
        if (!func){
                //if function is not there...define it globally
                if (variables.find(varname)!=variables.end()){
                        std::cout<<"Redefinition of global variable: \""<<varname<<"\"\n";
                        return;
                }
                if (funclogs) {
                        //logs the global creation of the variable with varname and value
                        outlogforfunc<<"Variable \""<<varname<<"\" created with value:"<<value<<" globally\n";
                }
                variables[varname]=temp;
                return;
        }
        //checks if the variable exists in the function 
        if (func->variables.find(varname)!=func->variables.end()){//if the variable is found in function...then tell the fucking user
                std::cout<<"Redefinition of variable:"<<varname<<"\n"<<"In function \""<<func->funcname<<"\"";
                return;
        }
        //creating the variable (on the heap of course like everything else)
        func->variables[varname]=new float(value);
        if (funclogs){
                //logs the variable created, the name, value and functioname 
                //FORESHADOWING:i swear this fuck(help) us up in debugging
                outlogforfunc<<"Variable \""<<varname<<"\" created with value:"<<value<<" in function \""<<func->funcname<<"\"\n";
        }
}

void returnfunc(float value, function *func){
        //sets returncode to value AND deletes all the variables...dont be a dumbass to call empty or delete subfunctions(future me)
        func->returncode=value;
        func->deletevariables();
}
void ifcommand(float condition,function* func,commandnode* ifend){
        if (condition!=0){
                return;
        }
        func->currcmdptr=ifend;
        return;
}
