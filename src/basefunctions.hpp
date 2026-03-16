#ifndef BASE_FUNCTIONS
#define BASE_FUNCTIONS

#include <string>
#include <fstream>

class function;  // forward declaration

extern std::ofstream outlogforfunc;
extern bool funclogs;

void definevariable(std::string varname, float value, function* func);
void returnfunc(float value,function* func);
#endif
