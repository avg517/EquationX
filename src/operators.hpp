#pragma once
#include <unordered_map>
#include <string>
#define OPER(name, key) float name(float a,float b){return(float)((a) key (b));}
//operator functions+precedence
namespace operators {
        //precedence and baseoperator function pointers
        std::unordered_map<std::string, int> precedence = {{"+", 10},{"-", 10},{"*", 20},{"/", 20},{"%", 20}};
        std::unordered_map<std::string,float (*)(float,float)> baseoperators;        
        
        //defining the operator function struct
        struct operatorcommand {
                std::string funcname;
                float (*func)(float, float)=NULL;
        };

        //defining opreators
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
        float mod(float a,float b){//special child cause a%b with floats doesnt work in c++
                float temp=a; 
                a=std::max(a,b);
                b=std::min(temp,b);
                if (b<0){
                        b=-b;
                        a=std::max(a,b);
                        b=std::min(temp,b);
                }
                while (a>b){a=a-b;}
                return a;
        }
        //initializing the base operators hashmap
        void definebaseoperators(){
                operators::operatorcommand temp;//creating a temp value
                auto push = [](operators::operatorcommand temp){operators::baseoperators[temp.funcname]=temp.func;};//creating a lambda function that automatically pushes the struct into the baseoprators
                //pushing every operator
                temp={"+",&operators::add};push(temp);
                temp={"-",&operators::sub};push(temp);
                temp={"*",&operators::mul};push(temp);
                temp={"/",&operators::div};push(temp);
                temp={"%",&operators::mod};push(temp);
                temp={"==",&operators::eq};push(temp);
                temp={"!=",&operators::ne};push(temp);
                temp={"<",&operators::lt};push(temp);
                temp={">",&operators::gt};push(temp);
                temp={"<=",&operators::le};push(temp);
                temp={">=",&operators::ge};push(temp);
        }//have fun working with this
}
