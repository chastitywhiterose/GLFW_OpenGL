/*
 This file contains a CreateWindow function which sets up the OpenGL context.
 The goal is to reduce the size of the main.c file and clean up everything.
*/

/*function only for printing errors*/
void error_callback(int error,const char *description)
{
 fprintf(stderr,"Error: %s\n",description);
}

int CreateWindow(int width,int height)
{
 glfwSetErrorCallback(error_callback);

 if(!glfwInit()){return 1;} /*Initialize GLFW*/
  
 glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,2); /*Using version 2.1 of OpenGL*/
 glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,1);
 glfwWindowHint(GLFW_DOUBLEBUFFER,GLFW_FALSE); /*single buffered window*/

 window=glfwCreateWindow(width,height,"OpenGL Legacy",NULL,NULL);

 if(!window)
 {
  glfwTerminate();
  printf("Failed to create window %s\n",glGetString(GL_VERSION));
  return 1;}

  glfwMakeContextCurrent(window);
  printf("The OpenGL version is: %s\n",glGetString(GL_VERSION));

  /*2D orthographic matrix*/
  /*the following line commented out. Only for historical purposes.*/
  /*glOrtho(0,width,height,0,-1,1);*/

  glClearColor(0.0,0.0,0.0,1.0); /*color used to clear the window*/

 return 0;
}
