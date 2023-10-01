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

void clVertex2f(float x,float y)
{
 glVertex2f( clx(x) , cly(y) );
}

/*draw rectangle by calling defining and drawing a polygon with 4 vertices*/

void clRectf( float x1, float y1, float x2, float y2 )
{
 glBegin(GL_POLYGON);
 clVertex2f(x1, y1);
 clVertex2f(x2, y1);
 clVertex2f(x2, y2);
 clVertex2f(x1, y2);
 glEnd();
}



void clColor3ub(unsigned char r,unsigned char g,unsigned char b)
{
 glColor3ub(r,g,b);
}



void clRectLinef( float x1, float y1, float x2, float y2 )
{
 glBegin(GL_LINE_LOOP);
 clVertex2f(x1+1, y1+1);
 clVertex2f(x2-1, y1+1);
 clVertex2f(x2-1, y2-1);
 clVertex2f(x1+1, y2-1);
 glEnd();
}


void clLinef( float x1, float y1, float x2, float y2 )
{
 glBegin(GL_LINES);
 clVertex2f(x1, y1);
 clVertex2f(x2, y2);
 glEnd();
}



