/*
glfw_input.h
*/


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

