#include <ncurses.h>
//#include <math.h>
#include <stdlib.h>
#include "terminal-constants.h"

void init_ncurses(){//initialisez ncurses
    initscr();
    cbreak();
    noecho();
    refresh();


}
char** init_buffer(){
    char** buffer = (char**) malloc((1+COLS)*sizeof(char));
    for(int i=0;i<COLS;i++){
        buffer[i]=(char*) malloc((1+LINES)*sizeof(char));
        for(int j=0;j<LINES;j++){
            buffer[i][j]='0';
        }
    }
    return buffer;
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
    pixels[0]=(char*) malloc((1+dx)*sizeof(char));//the first vector stores x value// but in the first position it will store the size of the vector
    pixels[1]=(char*) malloc((1+dx)*sizeof(char));//the second one stores y value
    int i=0;
    for(i=1;x<=x2;i++){
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
    pixels[0][0]=i;
    return pixels;

}

bool render_sprite(int x,int y,char** sprite,char** buffer){//this function renders the line from the render_line function,but the previous one only computes the pixels you need to "light up",this one puts it on the video buffer at some coordonates you specify
    for(int i=1;i<=sprite[0][0];i++){
        int x=2;//sprite[0][i];
        int y=2;//sprite[1][i];
        if(x>COLS || y > LINES){
            return false;//returns false when the line is outside of the screen(but it doesn't mean it should stop the program,only to not continue rendering the line)
        }else{
            buffer[x][y]= LINE;
        }


    }
    return true;
}

void render_buffer(char** buffer){//the buffer needs to be the size of the window for this to work
    //a solution would be to make a very large buffer (for a terminal screen,but in memory it won't be that big)


    //void getmaxyx(WINDOW *win, int y, int x); //this function gets the maximum size of the terminal
    //also,this variables are initiliazed by ncurses after initializing the screen: COLS, LINES
    for(int x=0;x<COLS;x++){
        for(int y=0;y<LINES;x++){
            mvaddch(y,x,buffer[x][y]);
        }
    }
    refresh();
}

void stop_ncurses(){
    refresh();
    endwin();
}