#pragma once
#include "parservariables.hpp"
#include <deque>
#include <unordered_map>
#include <string>

enum commandtype {
    EXPRESSION,
    IDENT,
    DEFINE,    
    SEPARATOR,
    IFSTART,
    IFEND,
    RETURN,
    CALLFUNC,
    GOTO
};

struct commandnode {
    commandtype cmd;
    std::string name;
    commandnode* nextcmdnode;
    commandnode* jumptocmdnode;
    expressnode* expression;

    commandnode(commandtype cmdconstuct,commandnode* nextcmdtemp,expressnode* expresstemp);
    commandnode(commandtype cmdconstuct,commandnode* nextcmdtemp,expressnode* expresstemp,std::string varname);
    commandnode(commandtype cmdconstuct,commandnode* nextcmdtemp,expressnode* expresstemp,commandnode* cmdjmpptr,std::string varname);
};

class function {
public:
        std::string funcname;
        std::unordered_map<std::string, float*> variables;
        std::deque<std::string> parserdefinedvariables;//this is to tell the parser if a variable is defined or not
        commandnode* commandptr = nullptr;
        commandnode* lastcmdptr = nullptr;
        commandnode* currcmdptr = nullptr;
        float returncode=0;
        bool endedfunc=false;
        void appendacommand(commandtype cmdtp, commandnode *nextcmdnode, expressnode *expresstemp, std::string fname);
        void appendacommand(commandtype cmdtp);
        void appendacommand(commandtype cmdtp,expressnode *expresstemp);
        void appendacommand(commandtype cmdtp, std::string fname);
        bool advance();
        void executecommand();
        void evalcommands();
        void empty();
        void deletevariables();
        void deletecommandnode(commandnode* cmdptr); 
};
std::unordered_map<std::string,function*> global_functions;//global_functions[name]=function*;
