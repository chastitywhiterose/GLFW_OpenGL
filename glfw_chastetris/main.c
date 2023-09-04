#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <GLFW/glfw3.h>

/*size of window*/
int width=1280,height=720;
int loop=1;
/*ideal for fullscreen*/
/*int width=1920,height=1080;*/
int fullscreen=0;

int frame=0;

char text[0x200];
char movetext[256],move_id;

char gamename[256];
int blocks_used=7;


/*frames per second and other animation variables*/
int fps=60,framelimit=1,seconds=0,minutes=0,hours=0;

/*
 Timer variables,used for delay. They are double and not to be confused with integer variables of display times.
*/
double glfwseconds,glfwseconds1;

GLFWwindow* window; /*window pointer*/
int text_switch=1;

/*header for different operating modes*/
#include "chastetris.h"
#include "glfw_graphics.h"
#include "glfw_input.h"

#include "glfw_lgbt.h"
#include "glfw_text.h"

void error_callback(int error,const char *description)
{
 fprintf(stderr,"Error: %s\n",description);
}





int main(int argc, char **argv)
{
 strcpy(gamename,"Chaste Tris");


 glfwSetErrorCallback(error_callback);
 
 if(!glfwInit()){return 1;} /*Initialize GLFW*/
  
 glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,2); /*Using version 2.1 of OpenGL*/
 glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,1);
 glfwWindowHint(GLFW_DOUBLEBUFFER,GLFW_FALSE); /*single buffered window*/

 if(fullscreen!=0)
 {
  width=1920;height=1080;
  window=glfwCreateWindow(width,height,gamename,glfwGetPrimaryMonitor(),NULL);
 }
 else
 {
  width=1280;height=720;
  window=glfwCreateWindow(width,height,gamename,NULL,NULL);
 }

 if(!window){glfwTerminate();return 1;}
 
 glfwMakeContextCurrent(window);
 glfwSetKeyCallback(window,key_callback);


 glOrtho(0.0,width,height,0.0,-1.0,1.0); /*2D orthographic matrix*/
 glClearColor(0.0,0.0,0.0,1.0); /*color used to clear the window*/
  
 printf("The OpenGL version is: %s\n",glGetString(GL_VERSION));

 main_lgbt=lgbt_load("./font/FreeBASIC Font 8.lgbt");
 
 /*now that context,fonts,and colors are loaded, can start a program!*/

 welcome_screen_chaste_font();
 
 gl_chastetris();

 glfwTerminate();
 return 0;
}
