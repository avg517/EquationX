#include "terminal-constants.h"
#include "render.h"
#include <ncurses.h>

int main(){
    char** buffer = init_buffer();
    init_ncurses();
    char** sprite = render_line(2,2,5,5);
    render_sprite(4,4,sprite,buffer);

    return 0;
}