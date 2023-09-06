/*
glfw_input.h
*/

void key_callback_title(GLFWwindow* window,int key,int scancode,int action,int mods)
{
 if(action==GLFW_PRESS || action==GLFW_REPEAT)
 {
  switch(key)
  {
   /* Exit on escape key press */
   case GLFW_KEY_ESCAPE:
    loop=0;
   break;
   case GLFW_KEY_ENTER:
    loop=0;
   break;
  }
 }
}

/*
Resource for key names:
https://www.glfw.org/docs/latest/group__keys.html
*/
void key_callback_game(GLFWwindow* window,int key,int scancode,int action,int mods)
{
 if(action==GLFW_PRESS || action==GLFW_REPEAT)
 {
  
  switch(key)
  {
   /* Exit on escape key press */
   case GLFW_KEY_ESCAPE:
    loop=0;
   break;

   /*keys that move the current block*/
   case GLFW_KEY_UP:
   case GLFW_KEY_W:
    move_id='W';
    tetris_move_up();
   break;
   case GLFW_KEY_LEFT:
   case GLFW_KEY_A:
    move_id='A';
    tetris_move_left();
   break;
   case GLFW_KEY_DOWN:
   case GLFW_KEY_S:
    move_id='S';
    tetris_move_down();
   break;
   case GLFW_KEY_RIGHT:
   case GLFW_KEY_D:
    move_id='D';
    tetris_move_right();
   break;

   case GLFW_KEY_Z:
   move_id='Z';
   block_rotate_left_basic();
   break;

   case GLFW_KEY_X:
     move_id='X';
   block_rotate_right_basic();
   break;

   case GLFW_KEY_C:
   move_id='C';
   block_hold();
   break;

    /*keys after this are for managing save states*/
    
    case GLFW_KEY_I:
     move_id='I';
     save_gamesave();
    break;
    case GLFW_KEY_P:
     move_id='P';
     load_gamesave();
    break;

   case GLFW_KEY_0:
    save_index=0;
    printf("State %d selected.\n",save_index);
   break;
   case GLFW_KEY_1:
    save_index=1;
    printf("State %d selected.\n",save_index);
   break;
   case GLFW_KEY_2:
    save_index=2;
    printf("State %d selected.\n",save_index);
   break;
   case GLFW_KEY_3:
    save_index=3;
    printf("State %d selected.\n",save_index);
   break;
  case GLFW_KEY_4:
   save_index=4;
   printf("State %d selected.\n",save_index);
   break;
  case GLFW_KEY_5:
   save_index=5;
   printf("State %d selected.\n",save_index);
  break;
  case GLFW_KEY_6:
   save_index=6;
   printf("State %d selected.\n",save_index);
  break;
  case GLFW_KEY_7:
   save_index=7;
   printf("State %d selected.\n",save_index);
  break;
  case GLFW_KEY_8:
   save_index=8;
   printf("State %d selected.\n",save_index);
  break;
  case GLFW_KEY_9:
   save_index=9;
   printf("State %d selected.\n",save_index);
  break;


  }

 }
}


















/*
this function gets input from a previous log file and autoplays the moves from  it.
this is a highly experimental feature and probably won't be in the published game
*/
void next_file_input()
{
 int c;
 if(fp_input==NULL){return;}

 c=fgetc(fp_input);

 if(feof(fp_input))
 {
  printf("End of file reached.\n");
  printf("Now use keyboard input.\n");
  /*
   printf("Going back to beginning\n");
   fseek(fp_input,0,SEEK_SET);
  */

  fclose(fp_input); fp_input=NULL;  return;
 }

 else
 {
  /*printf("Character==%c\n",c);*/

  move_id=c;

  if(c=='W'){tetris_move_up();}
  if(c=='S'){tetris_move_down();}
  if(c=='A'){tetris_move_left();}
  if(c=='D'){tetris_move_right();}

  if(c=='Z'){block_rotate_left_basic();}
  if(c=='X'){block_rotate_right_basic();}
  if(c=='C'){block_hold();}
  
  if(c=='[')
  {
   move_log[moves]=c;
   moves++;
  }
  if(c==']')
  {
   move_log[moves]=c;
   moves++;
  }
  
 }

}






