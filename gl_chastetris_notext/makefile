glfw_linux:
	gcc -Wall -ansi -pedantic main.c -o main -lglfw -lOpenGL -lm && ./main
glfw_static:
	gcc -Wall -ansi -pedantic main.c -o main `pkg-config --cflags --static --libs glfw3` -lOpenGL && ./main
glfw_win:
	gcc -Wall -ansi -pedantic main.c -o main -lglfw3 -lOpenGL32 -lm && ./main
glfw_win_static:
	gcc -Wall -ansi -pedantic main.c -o main -lglfw3 -lOpenGL32 -lgdi32 -lm -static && ./main
	strip main.exe

