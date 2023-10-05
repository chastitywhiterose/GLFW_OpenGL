#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/*size of window*/
int width=1280,height=720;
int loop=1;
/*ideal for fullscreen*/
/*int width=1920,height=1080;*/
int fullscreen=0;

int frame=0;

time_t time0,time1;

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

FILE *fp; /*to save a file of moves played*/
char filename[256]; /*name of move log file*/
FILE *fp_input; /*file to get input from instead of the keyboard*/



#include "./cl/CreateWindow.h"
#include "./cl/clRect.h"

/*header for different operating modes*/
#include "chastetris.h"
#include "chastetris_gamesave.h"
#include "glfw_lgbt.h"
#include "glfw_text.h"
#include "glfw_input.h"
#include "glfw_graphics.h"






int main(int argc, char **argv)
{
 int x;

 strcpy(gamename,"Chaste Tris");

 x=CreateWindow(width,height);
 if(x!=0)
 {
  printf("Error Creating Window. Program Closing\n");
  return 1;
 }

 main_lgbt=lgbt_load("./font/FreeBASIC Font 8.lgbt");
 
 /*now that context,fonts,and colors are loaded, can start a program!*/

 sprintf(filename,"imovelog.txt");
 fp_input=fopen(filename,"rb+");
 if(fp_input==NULL)
 {
  printf("Failed to open input file \"%s\".\n",filename);
  printf("This is not an error. It just means input is keyboard only. \"%s\".\n",filename);
 }
 else
 {
  printf("input file \"%s\" is opened.\n",filename);
  printf("Will read commands from this file before keyboard. \"%s\".\n",filename);
 }

 glBindVertexArray( vao ); //bind vertex array object before starting
 glDrawArrays( GL_TRIANGLES, 0, 6 );

 glfwSetKeyCallback(window,key_callback_title);
 welcome_screen_chaste_font();
 
 glfwSetKeyCallback(window,key_callback_game);
 gl_chastetris();

  /*
  After the game ends, we will attempt to save the movelog to a file.
  Keeping the movelog in memory and only writing at the end speeds up the program and simplifies things.
 */
 
  /*open the file to record moves*/
 sprintf(filename,"omovelog.txt");
 fp=fopen(filename,"wb+");
 if(fp==NULL){printf("Failed to create file \"%s\".\n",filename);}
 else
 {
  x=0;
  while(x<moves)
  {
   /*printf("%d %c\n",x,move_log[x]);*/
   fputc(move_log[x],fp);
   x++;
  }
 }

 if(fp!=NULL){fclose(fp);}
 if(fp_input!=NULL){fclose(fp_input);}

 glfwTerminate();
 return 0;
}
