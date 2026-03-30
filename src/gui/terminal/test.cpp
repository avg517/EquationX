#include "terminal-constants.h"
#include "render.h"
#include <ncurses.h>
#include <cstdlib>

bool program_on=true;

int main(){
    init_ncurses();
    char** buffer = init_buffer();
    //empty_buffer(buffer); //this function will be repaired later
    //char** sprite = render_line(5,5,6,70); 
    char** sprite = plotLine(5,5,115,125);
    render_sprite(2,4,sprite,buffer);
    //unsigned char* graphics = nullptr;
    //graphics=generate_graphics();
    
    while(program_on){
        //buffer[3][3]='o'; 
        //render_sprite(2,4,sprite,buffer);
        render_buffer(buffer);
        if(getch()=='q'){program_on=false;}
        //mvaddch(24,24,'o');
        napms(16);
    }
    //std::cout<<LINES<<" "<<COLS;
    stop_ncurses();

    free(buffer);
    free(sprite);
    //free(graphics);

    return 0;
}