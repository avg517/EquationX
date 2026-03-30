#include <ncurses.h>
//#include <math.h>
#include <stdlib.h>
#include "terminal-constants.h"


unsigned char* generate_graphics(){
    unsigned char* graphics =(unsigned char*) calloc(256,sizeof(char));
    for(int j=0x1;j<=0xFF;j+=0x1){
        graphics[j]=j;
    }
    return graphics;
}
void init_ncurses(){//initialisez ncurses
    initscr();
    noecho();
    cbreak();
}
char** init_buffer(){
    char** buffer = (char**) malloc((2*COL)*sizeof(char));
    for(int i=0;i<COL;i++){
        buffer[i]=(char*) malloc((2*LIN)*sizeof(char));
        for(int j=0;j<LIN;j++){
            buffer[i][j]=' ';
        }
    }
    return buffer;
}
/*char** clear_buffer(char** buffer){
    for(int i=0;i<COL;i++){
        int n=0;
    }
}*/

//time to use Bresenham's line algorithm :)
char** render_line(int x1,int y1,int x2,int y2){//don't use this function to render the line, the one below works better
    //the function returns a matrix pointer which describes every point that needs to be rendered
    //it can be used with another function that renders it on the terminal
    int dx=abs(x2-x1);
    int dy=abs(y2-y1);
    double slope =(dy)/(dx);
    int p= 2*dy - dx;
    int x=x1,y=y1;

    char** pixels =(char**) malloc(2*sizeof(char));
    pixels[0]=(char*) malloc((2+dx)*sizeof(char));//the first vector stores x value// but in the first position it will store the size of the vector
    pixels[1]=(char*) malloc((2+dy)*sizeof(char));//the second one stores y value
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
    pixels[0][0]=i-1;
    return pixels;

}

char** plotLine(int x0, int y0, int x1, int y1)//not made by me,but it's modified to work for this program, it's from this guy's site: https://zingl.github.io/bresenham.html
{
    int dx =  abs(x1-x0), sx = x0<x1 ? 1 : -1;
    int dy = -abs(y1-y0), sy = y0<y1 ? 1 : -1; 
    int err = dx+dy, e2; /* error value e_xy */
    char** pixels =(char**) malloc(2*sizeof(char));
    pixels[0]=(char*) malloc((2+dx)*sizeof(char));//the first vector stores x value// but in the first position it will store the size of the vector
    pixels[1]=(char*) malloc((2+abs(dy))*sizeof(char));//the second one stores y value
    int i;
    for(i=1;;i++){  /* loop */
        //setPixel(x0,y0);
        pixels[0][i]=x0;
        pixels[1][i]=y0;
        if (x0==x1 && y0==y1) break;
        e2 = 2*err;
        if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
        if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
    }
    pixels[0][0]=i-1;
    return pixels;
}



bool render_sprite(int x,int y,char** sprite,char** buffer){//this function renders the line from the render_line function,but the previous one only computes the pixels you need to "light up",this one puts it on the video buffer at some coordonates you specify
    for(int i=1;i<=sprite[0][0];i++){
        int x=sprite[0][i];
        int y=sprite[1][i];
        if(x>=COL || y >= LIN){
            return false;//returns false when the line is outside of the screen(but it doesn't mean it should stop the program,only to not continue rendering the line)
        }else{
            buffer[x][y]=LINE;
        }


    }
    return true;
}

void render_equation(int x, int y,char*** points,char** buffer){//this function renders a collection of "line" vectors to the buffer(used for rendering equations)
    //"line" vectors are the vectors that store the pixels on the screen needed to render a line from point A to point B, like in the render_sprite function
    for(int j=1;j<=points[0][0][0];j++){
        for(int i=1;i<=points[j][0][0];i++){
            int x=points[j][0][i];
            int y=points[j][1][i];
            if(x>=COL || y >= LIN){
                return; //false;//returns false when the line is outside of the screen(but it doesn't mean it should stop the program,only to not continue rendering the line)
            }else{
                buffer[x][y]=LINE;
            }


        }
    }
}


void render_buffer(char** buffer,unsigned char* graphics){//the buffer needs to be the size of the window for this to work
    //a solution would be to make a very large buffer (for a terminal screen,but in memory it won't be that big)

    //refresh();
    //void getmaxyx(WINDOW *win, int y, int x); //this function gets the maximum size of the terminal
    //also,this variables are initiliazed by ncurses after initializing the screen: COLS, LINES

    //buffer[2][3]='#';
    move(0,0);
    for(int y=0;y<LIN;y++){
        for(int x=0;x<COL;x++){
            //mvaddch(y,x,buffer[x][y]);
            addch(graphics[buffer[x][y]]);
            //addch(buffer[x][y]);
            //addch(graphics[34]);
            //addch('#');
            //if(x==LINES-1){addch('s');}
            if(x==COL-1){
                //addch('O');
                move(y+1,0);
            }
        }
    }
    refresh();
}

void stop_ncurses(){
    refresh();
    endwin();
}

