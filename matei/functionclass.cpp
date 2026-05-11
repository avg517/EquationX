#pragma once
#include "functionclass.hpp"
#include "expressfunc.hpp"
#include "basefunctions.cpp"
#include <cstdlib>
#include <iostream>
#include <string>
//TODO:add expect function in function::executecommand
// Constructor for commandnode
commandnode::commandnode(commandtype cmdconstuct, commandnode* nextcmdtemp,expressnode* expresstemp) : cmd(cmdconstuct), nextcmdnode(nextcmdtemp), expression(expresstemp) {}
commandnode::commandnode(commandtype cmdconstuct, commandnode* nextcmdtemp,expressnode* expresstemp,std::string varname) : cmd(cmdconstuct), nextcmdnode(nextcmdtemp), expression(expresstemp) ,name(varname) {}
// function methods
void function::appendacommand(commandtype cmdtp,commandnode *nextcmdnode,expressnode *expresstemp,std::string fname="") {
        //constructing the command to append
        commandnode* cmdtoappend=new commandnode(cmdtp,nextcmdnode,expresstemp,fname);
        if (!commandptr){
                //creating the first commandptr
                //appending command to linked list
                this->commandptr=cmdtoappend;
                //setting the last command to the current last
                this->lastcmdptr=cmdtoappend;
                this->currcmdptr=cmdtoappend;
        } else {
                //creating nextcommandptr
                this->lastcmdptr->nextcmdnode=cmdtoappend; //appending linked list pointer to last
                this->lastcmdptr=lastcmdptr->nextcmdnode; //setting the last last to new last
        }
}

void function::executecommand(){//this will execute simple specific commands like EXPRESSION, RETURN,IDENT (which is just x=20)
        std::string newvarname;//im defining this here becase of a weird define error in switch{}
        //this is the best part(sarcasm detected)
        int checkyvar;
        switch (this->currcmdptr->cmd) {
                case commandtype::DEFINE:
                        //i need that expect function...
                        newvarname=this->currcmdptr->name;
                        //currcmdptr=currcmdptr->nextcmdnode; bug right here advance() exists lil bro
                        definevariable(newvarname, 0, this);
                        if (this->advance()){
                                if (this->currcmdptr->cmd==EXPRESSION){
                                        float value=evaluate(this->currcmdptr->expression,this);
                                        *this->variables[newvarname]=value;
                                }
                        }
                        break;
                case commandtype::IDENT:

                        //if its an identifier like X ill have something along the lines of X=20;
                        newvarname=this->currcmdptr->name; //reusing newvarname to my advantage :D
                        checkyvar=checkvariable(this, newvarname);
                        //checkvariable() returns -1 when the variable doesnt exist
                        if (checkyvar==-1){
                                std::cout<<"Variable "<<newvarname<<" was not declared in this scope\n";
                        }
                        //checkvariable returns 1 if its in the function and returns 2 if its in the global variables
                        if(this->advance() && this->currcmdptr->cmd==EXPRESSION){
                                float value=evaluate(this->currcmdptr->expression,this);
                                if(checkyvar==1){
                                        *this->variables[newvarname]=value;
                                } else if (checkyvar==2) {
                                        *variables[newvarname]=value;
                                }
                        }
                break; 
                case commandtype::RETURN:
                        //simple enough if there isnt an expression it'll return 0, if there is however it'll evaluate it
                        if (this->advance() && this->currcmdptr->cmd==EXPRESSION){
                                this->returncode=evaluate(this->currcmdptr->expression, this);
                        } else {
                                this->returncode=0;
                        }
                        //after return it'll delete local variables
                        //important, do not use empty, cause it deletes the functions nodes too       
                        this->deletevariables();
                        this->endedfunc=true;
                break;
                case commandtype::EXPRESSION:
                        //this->returncode=the expression;
                        //i thought it would've been neat to add something other than RETURN y'know?
                        this->returncode=evaluate(this->currcmdptr->expression, this);
                break;
                case commandtype::IFSTART:
                        if (!advance()){
                                std::cout<<"Wtf did you put inside the if statement bro?\n";
                                return;
                        }
                        commandnode* currcmdptrcopy=this->currcmdptr;//this temorarily remembers IFSTART command
                        while((!this->advance()) && !(this->currcmdptr->cmd==IFEND)) {}
                        if (this->currcmdptr->cmd==IFEND){
                                commandnode* cmdtemp=this->currcmdptr;
                                this->currcmdptr=currcmdptrcopy;
                        }
                break;
        }
        if (!this->advance()){
                this->endedfunc=true;
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
        //while it aint the last keep going... wait a sec i see a bug
        /* this executes until the last command(but doesnt execute the very last one)
           while (this->currcmdptr!=this->lastcmdptr){
                executecommand();
        }*/
        //lets try this again ill define and ended func in the functions parameters
        while (!endedfunc){
                executecommand();
        }
        this->endedfunc=false;//gotta reset it for the next use
}

void function::deletevariables() {
        for (auto i : function::variables) {
                delete i.second;
        }
        function::variables.clear();
}

void function::deletecommandnode(commandnode* cmdptr) {//just pass in the linked list and it'll erase everything(including the expression trees) i hope i didnt forget anything to delete cause itll be a pain to debug
        if (cmdptr==nullptr || cmdptr==NULL){
                return;
        }
        if (cmdptr->nextcmdnode) {
                this->deletecommandnode(cmdptr->nextcmdnode);
        }
        if (cmdptr->expression) {
                freeTree(cmdptr->expression);
        }
        delete cmdptr;
}

void function::empty(){
        //it'll delete the commands
        this->deletecommandnode(function::commandptr);
        //it'll erase the variables
        this->deletevariables();
        //TODO:if i add subfunctions (functions inside of functions) ill have to delete them too here with function.empty()
}
