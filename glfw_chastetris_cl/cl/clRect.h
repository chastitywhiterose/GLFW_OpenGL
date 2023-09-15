/*
clrect.h

This header file is all about drawing filled rectangles.
The idea is to be able to switch out which function is used by renaming it.
For example, glRecti is a real function that exists in OpenGL.
Whichever of my function is named clRecti at the time will be used by the program I am running.
This means that I can change one function and control the output every time the program attempts to draw a rectangle.
It also means I can then port this function over to other graphics library to make an OpenGL emulator.
However, I am limited to 2D graphics because that is all I care about.

*/

/*draw rectangle by calling defining and drawing a polygon with 4 vertices*/

void clRecti( GLint x1, GLint y1, GLint x2, GLint y2 )
{
 glBegin(GL_POLYGON);
 glVertex2i(x1, y1);
 glVertex2i(x2, y1);
 glVertex2i(x2, y2);
 glVertex2i(x1, y2);
 glEnd();
}


/*draw rectangle by calling clRecti with identical arguments*/

void clRecti_1( GLint x1, GLint y1, GLint x2, GLint y2 )
{
 glRecti( x1, y1, x2, y2 );
}
