

/* this function is now the official welcome screen*/
void welcome_screen_chaste_font()
{
 int scale=8;
 int text_x=width/100;
 int char_size=main_lgbt.width/95;

 double delay=1.0/fps;

 loop=1;
 while(loop && !glfwWindowShouldClose(window))
 {
  glfwseconds=glfwGetTime();
  glfwseconds1=glfwseconds+delay;

  glClear(GL_COLOR_BUFFER_BIT);

 scale=width/100;
 sprintf(text,"%s",gamename);

 lgbt_draw_text(text,text_x,height/32,scale);

 scale=width/300;

 sprintf(text,"Programming: Chastity White Rose");
 lgbt_draw_text(text,text_x,char_size*5*scale,scale);

 sprintf(text,"Inspiration:    River Black Rose");
 lgbt_draw_text(text,text_x,char_size*6*scale,scale);


 sprintf(text,"Email: chastitywhiterose@gmail.com");
 lgbt_draw_text(text,text_x,char_size*8*scale,scale);

 sprintf(text,"Press Enter to Begin game.");
 lgbt_draw_text(text,text_x,height*10/16,scale);

 scale=width/400;

 sprintf(text,"https://www.patreon.com/ChastityWhiteRoseProgramming");
 
 lgbt_draw_text(text,text_x,height*7/16,scale);

 scale=width/500;

 sprintf(text,"All physics code in this game was written by Chastity White Rose using the\nC Programming Language. The font handling is done with the font library\nChastity wrote and named Chaste Font.\n\nGLFW is used for the OpenGL context.\n\nCredit goes to Alexey Pajitnov for creating the original Tetris game which\nChaste Tris is based on. I also like to thank Henk Rogers for helping\nTetris become the worldwide hit that it is.");
 
 lgbt_draw_text(text,text_x,height*12/16,scale);
 
 /*flush all gl commands and display to the screen*/
 glfwSwapBuffers( window );

 /*check for keypresses or other events*/
 glfwPollEvents();

 /*time loop used to slow the game down so users can see it*/
 while(glfwseconds<glfwseconds1)
 {
  glfwseconds=glfwGetTime();
 }
  
 }
}





/*
function to draw stats of the game
*/

 void draw_stats()
 {
  int scale=8;
  int char_size=main_lgbt.width/95;
  int text_x=width/320;

  scale=width*1/140;

  /*printf("Scale %d\n",scale);*/

  lgbt_draw_text("Chaste\n Tris",text_x,32,scale);
 
  scale=width/360;

  sprintf(text,"Score %d",score);
  lgbt_draw_text(text,text_x,char_size*8*scale,scale);

  sprintf(text,"Lines %d",lines_cleared_total);
  lgbt_draw_text(text,text_x,char_size*9*scale,scale);

  sprintf(text,"This %c",main_block.id);
  lgbt_draw_text(text,text_x,char_size*10*scale,scale);

  sprintf(text,"Hold %c",hold_block.id);
  lgbt_draw_text(text,text_x,char_size*11*scale,scale);

  sprintf(text,"Move %d",moves);
  lgbt_draw_text(text,text_x,char_size*12*scale,scale);

  sprintf(text,"B2B %d",back_to_back);
  lgbt_draw_text(text,text_x,char_size*13*scale,scale);

  sprintf(text,"Combo %d",combo);
  lgbt_draw_text(text,text_x,char_size*14*scale,scale);

  
  time(&time1);
  
  seconds=time1-time0; /*subtract current time from start time to get seconds since game started*/
  
/* 
  if(seconds!=0)
  {
   fps_current=frame/seconds;
   sprintf(text,"FPS %d",fps_current);
   chaste_font_draw_string(text,text_x,main_font.char_height*16);
  }
*/
  
  minutes=seconds/60;
  seconds%=60;
  hours=minutes/60;
  minutes%=60;
  
  sprintf(text,"Time %d:%02d:%02d",hours,minutes,seconds);
  lgbt_draw_text(text,text_x,char_size*16*scale,scale);

  /*sprintf(text,"Frame %d",frame);
  chaste_font_draw_string_scaled(text,text_x,main_font.char_height*17*scale,scale);*/

 }

