#ifdef __cplusplus
extern "C" {
#endif

unsigned char* generate_graphics();
void init_ncurses();
char** init_buffer();
char** render_line(int x1,int y1,int x2,int y2);
bool render_sprite(int x,int y,char** sprite,char** buffer);
void render_buffer(char** buffer,unsigned char* grafica);
void stop_ncurses();

#ifdef __cplusplus
}
#endif