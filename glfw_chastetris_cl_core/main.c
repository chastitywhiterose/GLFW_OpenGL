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

/*modern opengl variables*/

  /*
   geometry to use. these are 3 xyz points (9 floats total) to make a triangle
   we will draw two triangles to make a complete rectangle, so there are actually 18 floats for both
   the vertex positions and the vertex colors
 */
  GLfloat points[] =
  {
   -0.5f,  0.5f, 0.0f,
    0.5f,  0.5f, 0.0f,
   -0.5f, -0.5f, 0.0f,

    0.5f, -0.5f, 0.0f,
    0.5f,  0.5f, 0.0f,
   -0.5f, -0.5f, 0.0f,
  };

  GLfloat colours[] =
  {
   1.0f, 0.0f, 0.0f,
   0.0f, 1.0f, 0.0f,
   0.0f, 0.0f, 1.0f,

   0.0f, 1.0f, 1.0f,
   1.0f, 0.0f, 1.0f,
   1.0f, 1.0f, 0.0f 
  };


  GLuint points_vbo;
  GLuint colours_vbo;

  GLuint vao;


  const GLubyte* renderer;
  const GLubyte* version;



  /* these are the strings of code for the shaders
  the vertex shader positions each vertex point */
  const char* vertex_shader =
    "#version 410\n"
"layout(location = 0) in vec3 vertex_position;"
"layout(location = 1) in vec3 vertex_colour;"
"out vec3 colour;"
    "void main () {"
	"colour = vertex_colour;"
	"gl_Position = vec4(vertex_position, 1.0);"
    "}";

  /* the fragment shader colours each fragment (pixel-sized area of the
  triangle) */
  const char* fragment_shader =
    "#version 410\n"
"in vec3 colour;"
"out vec4 frag_colour;"
    "void main () {"
	"frag_colour = vec4 (colour, 1.0);"
    "}";

  /* GL shader objects for vertex and fragment shader [components] */
  GLuint vert_shader, frag_shader;
  /* GL shader programme object [combined, to link] */
  GLuint shader_programme;


/*end of global modern opengl variables*/


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

 CreateWindow(width,height);

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
