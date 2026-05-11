//the ifndef is for the libary to not be included twice
#pragma once
#ifndef INCLUD_PARSEVARS
#define INCLUD_PARSEVARS


#define OPER(name, key) float name(float a,float b){return(float)((a) key (b));}
#include <unordered_map>
#include <string>
#include <deque>
//global variables to parse
int current=0;
bool parseerror=false;
std::deque<std::string> problems;
std::deque<int> tokenids;
int num_tokens=0;
//expressnode definition
struct expressnode {
        std::string value;
        expressnode* left;
        expressnode* right;
        bool isidentifier;
        expressnode(std::string v,bool ident) : value(v),left(nullptr), right(nullptr), isidentifier(ident) {}
        expressnode(std::string v, expressnode* l, expressnode* r) : value(v), left(l), right(r) {}
};


//defining base operators
std::unordered_map<std::string, int> precedence = {{"+", 10},{"-", 10},{"*", 20},{"/", 20},{"%", 20}};
float mod(float a,float b){
        float temp=a; 
        a=std::max(a,b);
        b=std::min(temp,b);
        if (b<0){
                b=-b;
                a=std::max(a,b);
                b=std::min(temp,b);
        }
        while (a>b){
                a=a-b;
        }
        return a;
}
OPER(add,+)
OPER(sub,-)
OPER(mul,*)
OPER(div,/)
OPER(eq,==)
OPER(ne,!=)
OPER(lt,<)
OPER(gt,>)
OPER(le,<=)
OPER(ge,>=)

std::unordered_map<std::string,float*> variables;
std::unordered_map<std::string,float (*)(float,float)> baseoperators;

struct core {
        std::string funcname;
        float (*func)(float, float)=NULL;
};

//createing base operators
void definebasecommands(){
        core temp;
        auto push = [](core temp){baseoperators[temp.funcname]=temp.func;};
        
        temp={"+",&add};push(temp);
        temp={"-",&sub};push(temp);
        temp={"*",&mul};push(temp);
        temp={"/",&div};push(temp);
        temp={"%",&mod};push(temp);
        temp={"==",&eq};push(temp);
        temp={"!=",&ne};push(temp);
        temp={"<",&lt};push(temp);
        temp={">",&gt};push(temp);
        temp={"<=",&le};push(temp);
        temp={">=",&ge};push(temp);
        
}


void cleardeques(){
        problems.clear();
        baseoperators.clear();
        tokenids.clear();
}

#endif
