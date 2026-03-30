#pragma once
#include "functionclass.hpp"
#include "basefunctions.cpp"
#include "expressfunc.cpp"
#include "parservariables.hpp"
#include <charconv>
#include <cstdlib>
#include <iostream>
#include <string>
//TODO:add expect function in function::executecommand
// Constructor for commandnode
commandnode::commandnode(commandtype cmdconstuct, commandnode* nextcmdtemp,expressnode* expresstemp) : cmd(cmdconstuct), nextcmdnode(nextcmdtemp), expression(expresstemp) {}
commandnode::commandnode(commandtype cmdconstuct, commandnode* nextcmdtemp,expressnode* expresstemp,std::string varname) : cmd(cmdconstuct), nextcmdnode(nextcmdtemp), expression(expresstemp) ,name(varname) {}
commandnode::commandnode(commandtype cmdconstuct, commandnode* nextcmdtemp,expressnode* expresstemp,commandnode* cmpjmpptr,std::string varname) : cmd(cmdconstuct), nextcmdnode(nextcmdtemp), expression(expresstemp),jumptocmdnode(cmpjmpptr),name(varname) {}
// function methods
void function::appendacommand(commandtype cmdtp,commandnode* nextcmdnode,expressnode *expresstemp,std::string fname) {
        //constructing the command to append
        commandnode* cmdtoappend=new commandnode(cmdtp,nullptr,expresstemp,fname);
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
void function::appendacommand(commandtype cmdtp){
        //uses the same logic as the last appendacommand()
        commandnode* cmdtoappend=new commandnode(cmdtp,nullptr,nullptr,"");
        if (!this->commandptr){
                this->commandptr=cmdtoappend;
                this->lastcmdptr=cmdtoappend;
                this->currcmdptr=cmdtoappend;
        } else {
                this->lastcmdptr->nextcmdnode=cmdtoappend;
                this->lastcmdptr=lastcmdptr->nextcmdnode;
        }
}
void function::appendacommand(commandtype cmdtp,expressnode* expresstemp){
        commandnode* cmdtoappend=new commandnode(cmdtp,nullptr,expresstemp,"");
        
}
bool evalifstatement(function* func){
        //try to advance forward, if not, end of function reached without closing the if
        if (!func->advance()){
                //nice error handling
                std::cout<<"Uhm you sure you made the if statement right?\nI reached the end of the function:\""<<func->funcname<<"\" without finishing the if statement\n";
                return false;
        }
        //if the next command is not a condition then wtf is the user trying to define?
        float value;
        if (!(func->currcmdptr->cmd==EXPRESSION)){
                std::cout<<"Nice try buddy but you fucked up the condition in function:\""<<func->funcname<<"\"\n";
                return false;
        }
        value=evaluate(func->currcmdptr->expression, func);//calculating the condition's value
        //lets find the endif
        commandnode* ifendptr=NULL;
        /*while(func->advance()){//this won't work for nested if's
                if (func->currcmdptr->cmd==IFEND){
                        break;
                }
        }*/

        //ifcommand(value, func, );
        return 0;
}

void function::executecommand(){//this will execute simple specific commands like EXPRESSION, RETURN,IDENT (which is just x=20)
        std::string newvarname;//im defining this here becase of a weird define error in switch{}
        //this is the best part(sarcasm detected)
        int checkyvar;
        
        //for if 
        float condition;
        commandnode* rememberifstart;
        switch (this->currcmdptr->cmd) {
                case commandtype::GOTO:
                        this->currcmdptr=this->currcmdptr->jumptocmdnode;//thats it...i just need to jump...
                break;
                case commandtype::DEFINE:
                        //i need that expect function...
                        newvarname=this->currcmdptr->name;
                        //currcmdptr=currcmdptr->nextcmdnode; bug right here advance() exists lil bro
                        if (this->advance()){
                                if (this->currcmdptr->cmd==EXPRESSION){
                                        float value=evaluate(this->currcmdptr->expression,this);
                                        definevariable(newvarname, value, this);
                                } else if (this->currcmdptr->cmd==SEPARATOR){
                                        definevariable(newvarname, 0, this);
                                        
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
                        rememberifstart=this->currcmdptr;//remembering the start of the if statement
                        if (!advance()){
                                std::cout<<"Wtf did you put inside the if statement bro?\n";
                                return;
                        }//advancing
                        if (this->currcmdptr->cmd!=EXPRESSION){
                                std::cout<<"The fuck happened with the condition?\n";
                                return;
                        }
                        //uhm i fucked something up here...cause im on the EXPRESSION command node now... theres no jumptocmdnode
                        //let's try again with a trash implementation :D 
                        
                        condition=condition=evaluate(this->currcmdptr->expression,this);
                        ifcommand(condition,this,rememberifstart->jumptocmdnode);
                break;
                case commandtype::CALLFUNC:
                        //this is temporary as a better CALLFUNC will be added in "basefunctions.cpp"
                        if(global_functions.find(this->currcmdptr->name)==global_functions.end()){
                                //WRONG:not defined i guess
                                std::cout<<"Function:\""<<this->currcmdptr->name<<"\" was not declared in this scope\n";
                        }
                        //running it
                        function* functorun=global_functions[this->currcmdptr->name];
                        float value;
                        functorun->evalcommands();
                        value=functorun->returncode;
                        functorun->returncode=0;
                        functorun->deletevariables();
                        //idk if i even used my own code right :D
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
        if (!this->currcmdptr){
                if (!this->commandptr){
                        std::cout<<"No commands to run\n";
                        return;
                } else {
                        this->currcmdptr=this->commandptr;
                }
        }
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
