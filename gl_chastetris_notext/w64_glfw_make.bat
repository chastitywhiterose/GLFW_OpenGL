SET DEVKIT=C:\w64devkit
SET COMPILER_PATH=%DEVKIT%\bin
SET PATH=%COMPILER_PATH%

gcc -Wall -ansi -pedantic main.c -o main -I%DEVKIT%\include -L%DEVKIT%\lib -lglfw3 -lOpenGL32 -lgdi32 && main
strip main.exe
