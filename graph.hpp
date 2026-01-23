#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <cstdlib>
#include <exception>
#include <iostream>
class graphing{
        public:
                int xres,yres;//x resolution, y resolution
                float backr,backb,backg;
                void initwindow(){
                        if (!glfwInit()){
                                std::cerr<<"failed to init glfw \n";
                        }
                        GLFWwindow* window= glfwCreateWindow(xres,yres,"Graph",NULL,NULL);
                        if(!window){
                                std::cerr<<"couldn't create window \n";
                        }
                        glfwMakeContextCurrent(window);
                        while(!glfwWindowShouldClose(window)){
                                glClear(GL_COLOR_BUFFER_BIT);
                                running();
                                glfwSwapBuffers(window);
                                glfwPollEvents();
                        }
                }
                void running(){
                        glBegin(GL_LINE_STRIP);
                        
                        glVertex2f(0.6, 0.7);
                        glVertex2f(-0.6, -0.9);
                        glEnd();
                }
        private:
                void initgrid(int numsegs,float space_between){
                        int negnumsegs=-numsegs;
                        glBegin(GL_LINE_STRIP)
                        for (int i=numsegs;i<=numsegs;++i){
                                glVertex2f(i*space_between,0);
                        }
                        glEnd();
                        glBegin(GL_LINE_STRIP)
                        for (int i=-numsegs;i<=numsegs;++i){
                                glVertex2f(i*space_between,0);
                        }
                        glEnd();
                } 
};
