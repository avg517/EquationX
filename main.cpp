//this is the main cpp program file used to link all together

#include "src/basefunctions.hpp"
#include "src/expressfunc.hpp"
#include "src/functionclass.hpp"
#include "src/includethemall.hpp"
#include "src/parser.hpp"
//#include "src/simplecalculator.hpp"
#include "src/graph-plotting/graph_generator.hpp"
#include "src/gui/terminal/render.h"
#include "./src/tokenizer/tokens.h"

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

int get_flag(){
    char input =getch();
    switch(input){
        case '-';
            return minussign;
        case '+':
            return addsign;
        case '*':
            return multiplysign;
        case '/':
            return dividesign;
    }
}



double** create_graph(){//it is like in vim.In this mode you enter commands(and equations in this case to compute)
    double lower_bound =scanw();
    double upper_bound =scanw();
    double** graph = generate_empty_graph_double(lower_bound,upper_bound);
    double rate =scanw();
    initialize_graph(graph,rate,lower_bound,upper_bound);
    return graph;

}

void add_to_graph(double** graph){
    int flag=get_flag();
    int number=scanw();
    compute_graph(graph,flag,number);
}

void handle_input(char** buffer){
    char input = getch();
    if(input=='q'){program_on=false}
    if(input==0x1B){
        move(LINES-1,0);
        echo();
        create_graph();
        
        double** graph=create_graph();
        add_to_graph(graph);
        int*** points =generate_equation_sprite(graph);
        render_equation(4,4,points,buffer);//the beggining of the graph will be in a fixed position for the purpose of this demo
        
    }
}

void render(){//the function renders the graph 
    init_ncurses();
    char** buffer = init_buffer();
    char* input_command=(char*) calloc(256,sizeof(char));
    while(program_on){
        handle_input(buffer);
        render_buffer(buffer);
        napms(16);
    }
    //std::cout<<LINES<<" "<<COLS;
    stop_ncurses();

    free(buffer);
    free(sprite);
    //free(graphics);
}

int main(int argc, char *argv[]){
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