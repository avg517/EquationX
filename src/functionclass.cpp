#include "functionclass.hpp"
#include "expressfunc.hpp"
#include "basefunctions.hpp"
#include <iostream>
#include <string>
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
        switch (this->currcmdptr->cmd) {
                case commandtype::DEFINE:
                        //i need that expect function...
                        currcmdptr=currcmdptr->nextcmdnode;
                        std::string newvarname=this->currcmdptr->name;
                        if (this->advance()){
                                if (this->currcmdptr->cmd==EXPRESSION){
                                        float value=evaluate(this->currcmdptr->expression,this);
                                        definevariable(newvarname,value,this);
                                } else {
                                        definevariable(newvarname, 0, this);
                                }
                        }
                        advance();
                break;
                case commandtype::IDENT:
                        if(this->advance()){
                                //if this->currcmdptr->cmd==
                        }
                break;
        }
}
//if it can advance it returns true if not false 
bool function::advance(){
        if (this->currcmdptr->nextcmdnode){
                this->currcmdptr=this->currcmdptr->nextcmdnode;
                return true;
        }
        return false;
}
void function::evalcommands() {
        while (this->advance()){
                executecommand();
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
                this->deletecommandnode(cmdptr->nextcmdnode);
        }
        delete cmdptr;
}

void function::empty(){
        this->deletecommandnode(function::commandptr);
        this->deletevariables();        
}
