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
#include "gl_graphics.h"

/*
Resource for key names:
https://www.glfw.org/docs/latest/group__keys.html
*/
void key_callback(GLFWwindow* window,int key,int scancode,int action,int mods)
{
 if(action==GLFW_PRESS || action==GLFW_REPEAT)
 {
  
  switch(key)
  {
   /* Exit on escape key press */
   case GLFW_KEY_ESCAPE:
    /*glfwSetWindowShouldClose(window,GLFW_TRUE);*/
    loop=0;
   break;

   /*keys that move the current block*/
   case GLFW_KEY_UP:
   case GLFW_KEY_W:
   tetris_move_up();
   break;
   case GLFW_KEY_LEFT:
   case GLFW_KEY_A:
   tetris_move_left();
   break;
   case GLFW_KEY_DOWN:
   case GLFW_KEY_S:
    tetris_move_down();
   break;
   case GLFW_KEY_RIGHT:
   case GLFW_KEY_D:
 /*make backup of block location*/
tetris_move_right();
   break;

   case GLFW_KEY_X:
   block_rotate_right_basic();
   break;
   case GLFW_KEY_Z:
   block_rotate_left_basic();
   break;

   case GLFW_KEY_C:
   block_hold();
   break;

   case GLFW_KEY_COMMA:
   tetris_load_state();
   break;
   case GLFW_KEY_PERIOD:
   tetris_save_state();
   break;

  }

 }
}


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
 
 /*now that context,fonts,and colors are loaded, can start a program!*/
 
 gl_chastetris();

 glfwTerminate();
 return 0;
}
