/*
clrect.h

This header file is all about drawing filled rectangles.
The idea is to be able to switch out which function is used by renaming it.
For example, glRectf is a real function that exists in OpenGL.

The problem arises from the fact that OpenGL commands take floating point arguments which must be in the range -1 to +1. Additionally, 0 is in the middle of the screen for X and Y coordinates. To make OpenGL compatible with the same coordinate system used in SDL, I have made a collection of functions which convert screen pixel coordinates to OpenGL coordinates. This means that I am no longer dependent on the "glOrtho" any more. It also means I have greater control of the fixed function pipeline than I ever have before.

Whichever of my function is named clRectf at the time will be used by the program I am running.
This means that I can change one function and control the output every time the program attempts to draw a rectangle.
It also means I can then port this function over to other graphics library to make an OpenGL emulator.
However, I am limited to 2D graphics because that is all I care about.
*/


float clx(float f)
{
 f=f*2/width-1; /*printf("X=%f\n",f);*/
 return f;
}

float cly(float f)
{
 f=f*2/height-1; /*printf("Y=%f\n",f);*/
 return -f;
}


int vertex_index=0;

int color_index=0;
float v_red=1.0,v_green=1.0,v_blue=1.0;

void clColor3ub(unsigned char red,unsigned char green,unsigned char blue)
{

 v_red=red/255.0;
 v_green=green/255.0;
 v_blue=blue/255.0;

/*printf("R%d G%d B%d\n",red,green,blue);*/

}


void clVertex2f(float x,float y)
{
 //glVertex2f( clx(x) , cly(y) );

 points[vertex_index]=clx(x); vertex_index++;
 points[vertex_index]=cly(y); vertex_index++;
 points[vertex_index]=0.0; vertex_index++;

 colours[color_index]=v_red; color_index++;
 colours[color_index]=v_green; color_index++;
 colours[color_index]=v_blue; color_index++;
 
}

/*draw rectangle by calling defining and drawing a polygon with 4 vertices*/

void clRectf( float x1, float y1, float x2, float y2 )
{
 vertex_index=0;
 color_index=0;

 clVertex2f(x1, y1);
 clVertex2f(x2, y1);
 clVertex2f(x1, y2);

 clVertex2f(x2, y2);
 clVertex2f(x2, y1);
 clVertex2f(x1, y2);

  glBindBuffer( GL_ARRAY_BUFFER, points_vbo );
  glBufferData( GL_ARRAY_BUFFER, 18 * sizeof( GLfloat ), points, GL_STATIC_DRAW );
  glBindBuffer( GL_ARRAY_BUFFER, colours_vbo );
  glBufferData( GL_ARRAY_BUFFER, 18 * sizeof( GLfloat ), colours, GL_STATIC_DRAW );
  glDrawArrays( GL_TRIANGLES, 0, 6 );
}




