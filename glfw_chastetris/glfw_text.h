

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
 glFlush();

 /*check for keypresses or other events*/
 glfwPollEvents();

 /*time loop used to slow the game down so users can see it*/
 while(glfwseconds<glfwseconds1)
 {
  glfwseconds=glfwGetTime();
 }
  
 }
}



