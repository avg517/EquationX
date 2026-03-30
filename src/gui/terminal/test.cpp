#include "terminal-constants.h"
#include "render.h"
#include <ncurses.h>
#include <cstdlib>

bool program_on=true;

int main(){
    init_ncurses();
    char** buffer = init_buffer();
    //char** sprite = render_line(5,5,6,70);
    char** sprite = plotLine(5,5,36,10);
    render_sprite(2,4,sprite,buffer);
    //unsigned char* graphics = nullptr;
    //graphics=generate_graphics();
    
    while(program_on){
        //buffer[3][3]='o';
        render_buffer(buffer);
        if(getch()=='q'){program_on=false;}
        //mvaddch(24,24,'o');
        //printw("sa bag botswana in codul lui matei");
        napms(16);
    }
    //std::cout<<LINES<<" "<<COLS;
    stop_ncurses();

    free(buffer);
    free(sprite);
    //free(graphics);

    return 0;
}