#include "terminal-constants.h"
#include "render.h"
#include <ncurses.h>
#include <cstdlib>


int main(){
    char** buffer = init_buffer();
    char** sprite = render_line(5,5,10,15);
    render_sprite(2,4,sprite,buffer);
    unsigned char* graphics=generate_graphics();
    init_ncurses();
    while(true){
        //buffer[3][3]='o';
        render_buffer(buffer,graphics);
        //mvaddch(24,24,'o');
        //printw("sa bag botswana in codul lui matei");
        napms(16);
    }
    //std::cout<<LINES<<" "<<COLS;
    stop_ncurses();

    free(buffer);
    free(sprite);
    free(graphics);

    return 0;
}