#include "functionclass.hpp"
#include "basefunctions.hpp"
#include <iostream>
#include <fstream>
std::ofstream outlogforfunc("functionlogs.txt");
#ifdef FUNC_LOGS
bool funclogs=true;
#else
bool funclogs=false;
#endif


void definevariable(std::string varname,float value,function* func){
        float* temp=new float(value);
        auto finder=func->variables.find(varname);
        if (finder!=func->variables.end()){
                std::cout<<"Redefinition of variable:"<<varname<<"\n";
                return;
        }
        func->variables[varname]=new float(value);
        if (funclogs){
                outlogforfunc<<"Variable \""<<varname<<"\" created with value:"<<value<<"\n";
        }
}

void returnfunc(float value, function *func){
        func->returncode=value;
        func->deletevariables();
}
