#pragma once
#ifdef __cplusplus
extern "C" {
#endif

//unsigned char* generate_graphics(); 
void init_ncurses();
char** init_buffer();
void empty_buffer(char** buffer);
//char** clear_buffer(char** buffer);
char** render_line(int x1,int y1,int x2,int y2);
int** plotLine(int x0, int y0, int x1, int y1);
int*** generate_equation_sprite(double** graph);
bool render_sprite(int x,int y,int** sprite,char** buffer);
void render_equation(int x, int y,int*** points,char** buffer);
void render_buffer(char** buffer);
void stop_ncurses();

#ifdef __cplusplus
}
#endif