//this is the main cpp program file used to link all together

//#include "basefunctions.hpp"
//#include "expressfunc.hpp"
//#include "functionclass.hpp"
//#include "includethemall.hpp"
//#include "parser.hpp"
//#include "simplecalculator.hpp"
#include "./graph-plotting/graph_generator.hpp"
#include "./gui/terminal/render.h"
#include "./tokenizer/tokens.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
/*COMMAND LINE ARGUMENTS:
-h --help           prints the help screen
-r --render <file>  renders a function defined in a file
*/

int pos=0;

bool program_on=true;
/*char* tokenizer(char* string,char* argument){//you give it the argv and from what position in the vector to start,and it identifies an argument
    int i=0;
    for(i=pos;string[i]!=' ';i++){}
    argument =(char*) std::calloc(i+1,sizeof(char));
    for(i=pos;string[i]!=' ';i++){
        argument[i-pos]=string[i];
    }
    return argument;
}*/


std::ifstream fin;



void handle_input(char** buffer,double** graph){
    char input = getch();
    if(input=='q'){program_on=false;}
    if(input==0x1B){
        move(LINES-1,0);
        echo();
        create_graph();
        
        graph=create_graph();
        add_to_graph(graph);
        int*** points =generate_equation_sprite(graph);
        render_equation(4,4,points,buffer);//the beggining of the graph will be in a fixed position for the purpose of this demo
        std::free(points);
    }
}

void render(){//the function renders the graph 
    init_ncurses();
    double** graph=NULL;
    char** buffer = init_buffer();
    char* input_command=(char*) calloc(256,sizeof(char));
    while(program_on){
        handle_input(buffer,graph);
        render_buffer(buffer);
        napms(16);
    }
    //std::cout<<LINES<<" "<<COLS;
    stop_ncurses();

    std::free(buffer);
    std::free(input_command);
    free(graph);
    //free(graphics);
}

void read_file(char** buffer){
    double x0,x1,y0,y1;
    while(fin>>x0>>y0>>x1>>y1){
    	int** sprite = plotLine(x0,y0,x1,y1);
    	render_sprite(1,1,sprite,buffer); 
    	std::free(sprite);
    }
}



void handle_input2(){
    char input = getch();
    if(input=='q'){program_on=false;}
}

//curently this is the function we use to render
void render2(){
    init_ncurses();
    double** graph=NULL;
    char** buffer = init_buffer();
    while(program_on){
        read_file(buffer);
        render_buffer(buffer);
        handle_input2();
        napms(16);
    }
    //std::cout<<LINES<<" "<<COLS;
    stop_ncurses();


    std::free(buffer);
    //std::free(input_command);
    free(graph);
    //free(graphics);
}


int main(int argc, char *argv[]){
    //render();
    //std::ifstream fin(argv[1]);
    fin.open(argv[1]);
    render2();
    
    
    /*while(argv[pos-1]!=' '){
        pos++;
    }
    int argument_count=0;
    for(int i=0;i<argc;i++){
        if(argv[i]==' '&&argv[i+1]!=' '){
            argument_count++;
        }
    }
    char** args =(char**) std::calloc(argument_count,sizeof(char));
    for(int i=0;i<argument_count;i++){
        args[i]=(char*) std::calloc(20,sizeof(char));
    }
    for(int i=0;pos<=argc;i++){
        tokenizer

    } 
    I will let matei handle reading arguments*/



}
