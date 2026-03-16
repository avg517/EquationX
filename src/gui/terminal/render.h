#ifdef __cplusplus
extern "C" {
#endif

void init_ncurses();
char** init_buffer();
char** render_line(int x1,int y1,int x2,int y2);
bool render_sprite(int x,int y,char** sprite,char** buffer);
void render_buffer(char** buffer);


#ifdef __cplusplus
}
#endif