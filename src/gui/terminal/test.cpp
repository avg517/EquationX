#include "terminal-constants.h"
#include "render.h"
#include <ncurses.h>
//#include <iostream>

int main(){
    char** buffer = init_buffer();
    init_ncurses();
    char** sprite = render_line(2,2,10,15);
    //render_sprite(2,4,sprite,buffer);
    while(getch()!='q'){
        buffer[3][3]='o';
        render_buffer(buffer);
        //mvaddch(24,24,'o');
        
    }
    //std::cout<<LINES<<" "<<COLS;
    stop_ncurses();
    return 0;
}