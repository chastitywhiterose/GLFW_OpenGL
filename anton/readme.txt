The files in this folder were made when I was learning from Anton's OpenGL tutorials. His tutorials are available for free on his website, but I also bought the Kindle edition of his ebook.

https://antongerdelan.net/opengl/

I used Anton's example source code "00_hello_triangle" as the base of my own Modern OpenGL code. It can be found on his his github repository here:

https://github.com/capnramses/antons_opengl_tutorials_book

I don't use his makefiles though. I just use the following which works for me on Ubuntu Linux.

glfw_linux:
	gcc -Wall -ansi -pedantic main.c -o main -lglfw -lOpenGL -lGLEW -lm && ./main

After getting the hello_triangle example working, I then followed the part of the tutorial at the following link.

https://antongerdelan.net/opengl/vertexbuffers.html


