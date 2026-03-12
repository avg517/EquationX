#include "functionclass.hpp"
#include <iostream>
//TODO:add expect function in function::executecommand
// Constructor for commandnode
commandnode::commandnode(commandtype cmdconstuct, commandnode* nextcmdtemp,expressnode* expresstemp) : cmd(cmdconstuct), nextcmdnode(nextcmdtemp), expression(expresstemp) {}
commandnode::commandnode(commandtype cmdconstuct, commandnode* nextcmdtemp,expressnode* expresstemp,std::string varname) : cmd(cmdconstuct), nextcmdnode(nextcmdtemp), expression(expresstemp) ,name(varname) {}
// function methods
void function::appendacommand(commandtype cmdtp,commandnode *nextcmdnode,expressnode *expresstemp,std::string fname="") {
        //constructing the command to append
        commandnode* cmdtoappend=new commandnode(cmdtp,nextcmdnode,expresstemp);
        if (!commandptr){
                //appending command to linked list
                lastcmdptr->nextcmdnode=cmdtoappend;
                //setting the last command to the current last
                lastcmdptr=cmdtoappend;
        } else {
                //if there is no command pointer...this is it's creation commandptr=lastcmdptr=cmdtoappend;
                commandptr=cmdtoappend;
                lastcmdptr=cmdtoappend;
        }
}

void function::executecommand(){
        //this is the best part(sarcasm detected)
        if (currcmdptr->cmd == DEFINE){
                //i need that expect function...
                currcmdptr=currcmdptr->nextcmdnode;
        }
}

void function::evalcommands() {
        commandnode* currentcommand = commandptr;
        while (currentcommand) {
                std::cout << currentcommand->cmd;
                currentcommand = currentcommand->nextcmdnode;
        }
}

void function::deletevariables() {
        for (auto i : function::variables) {
                delete i.second;
        }
        function::variables.clear();
}

void function::deletecommandnode(commandnode* cmdptr) {
        if (cmdptr==nullptr || cmdptr==NULL){
                return;
        }
        if (cmdptr->nextcmdnode) {
                function::deletecommandnode(cmdptr->nextcmdnode);
        }
        delete cmdptr;
}

void function::empty(){
        deletecommandnode(function::commandptr);
        deletevariables();        
}
