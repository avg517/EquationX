#include <iostream>
#include <string>
#include <unordered_map>
#include <cmath>

constexpr double pi=3.1415926535;
class valeu{
        public:
                double value=0;
                double calcsin(){
                        double rads=angtorad(value);
                        return std::sin(rads);
                }
                double calccos(){ 
                        double rads=angtorad(value);
                        return std::cos(rads);
                }
                double calctan(){
                        return calcsin()/calccos();
                }
                double calccotan(){
                        return calccos()/calcsin();
                }
        private:
                double angtorad(double you){
                        double me;
                        me=you*pi/180;
                        return me;
                }
};

std::unordered_map<std::string, valeu*> variables;

void defvar(std::string varname,double valm){
        valeu* val=new valeu;
        val->value=valm;
        variables[varname]=val;
}
