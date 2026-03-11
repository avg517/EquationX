#include <ncurses.h>
#include <cmath>
#include "terminal-constants.h"

void init_ncurses(){//initialisez ncurses


}


//time to use Bresenham's line algorithm :)
char** render_line(int x1,int y1,int x2,int y2){//the function returns a matrix pointer which describes every point that needs to be rendered
    //it can be used with another function that renders it on the terminal
    int dx=abs(x2-x1);
    int dy=abs(y2-y1);
    double slope =(dy)/(dx);
    int p= 2*dy - dx;
    int x=x1,y=y1;

    char** pixels =(char**) malloc(2*sizeof(char));
    pixels[0]=(char*) malloc(dx*sizeof(char));//the first vector stores x value
    pixels[1]=(char*) malloc(dx*sizeof(char));//the second one stores y value

    for(int i=0;x<=x2;i++){
        pixels[0][i]=x;
        pixels[1][i]=y;
        x++;
        if(p<0){
            p = p +2*dy;
        }else if(p>0){
            p=p+2*dy - 2*dx;
            y++;
        }
    }


}



void render_buffer(char** buffer){//the buffer needs to be the size of the window for this to work
    //a solution would be to make a very large buffer (for a terminal screen,but in memory it won't be that big)


    //void getmaxyx(WINDOW *win, int y, int x); //this function gets the maximum size of the terminal
    //also,this variables are initiliazed by ncurses after initializing the screen: COLS, LINES
    for(int x;x<COLS;x++){
        for(int y;y<COLS;x++){
            mvaddch(y,x,buffer[x][y]);
        }
    }
}
