/*
gl_graphics.h

this is the file containing the gameloop function
*/




/*more global variables to be defined before game loop function*/
int block_size;
int border_size;
int grid_offset_x;



void gl_chastetris()
{
 int pixel,r,g,b;
 int x=0,y=0;
 double delay;

 /*setup the grid display*/
 block_size=height/grid_height;
 grid_offset_x=(width-(20/2*block_size))/2; /*formula for grid to center of screen*/
 border_size=block_size;

 /*printf("block_size==%d\n",block_size);*/

 spawn_block();


 /*first empty the grid*/
 y=0;
 while(y<grid_height)
 {
  x=0;
  while(x<grid_width)
  {
   main_grid.array[x+y*grid_width]=empty_color;
   x+=1;
  }
  y+=1;
 }

 delay=1.0/fps;

 /*get time before the game starts using standard library time function*/
 time(&time0);
 
 loop=1;
  /* Loop until the user closes the window */
 while(loop && !glfwWindowShouldClose(window))
 {
  glfwseconds=glfwGetTime();
  glfwseconds1=glfwseconds+delay;

  /*SDL_SetRenderDrawColor(renderer,0,0,0,255);
  SDL_RenderClear(renderer);*/

  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

 /*make backup of entire grid*/
  temp_grid=main_grid;

  /*draw block onto temp grid at it's current location*/
  y=0;
  while(y<max_block_width)
  {
   x=0;
   while(x<max_block_width)
   {
    if(main_block.array[x+y*max_block_width]!=0)
    {
     if(temp_grid.array[main_block.x+x+(main_block.y+y)*grid_width]!=0)
     {
      printf("Error: Block in Way\n");

      /*because a collision has occurred. We will restore everything back to the way it was before block was moved.*/

      break;
     }
     else
     {
      main_color=main_block.color;
      /*main_color=chaste_palette[block_color_index[block_type]];*/
      temp_grid.array[main_block.x+x+(main_block.y+y)*grid_width]=main_color;
     }
    }
    x+=1;
   }
   y+=1;
  }



/*display the tetris grid*/

 y=0;
 while(y<grid_height)
 {
  x=0;
  while(x<grid_width)
  {
   pixel=temp_grid.array[x+y*grid_width];
   r=(pixel&0xFF0000)>>16;
   g=(pixel&0x00FF00)>>8;
   b=(pixel&0x0000FF);

   glColor3ub(r,g,b);


   /*set up the rectangle structure with the needed data to square the squares*/
   rect.x=grid_offset_x+x*block_size;
   rect.y=y*block_size;
   rect.w=block_size;
   rect.h=block_size;

   clRectf(rect.x,rect.y,rect.x+rect.w,rect.y+rect.h);

   x+=1;
  }
  y+=1;
 }


 /*draw the boundary walls*/

/*
 set up the rectangle structure with the needed data to square the walls
*/

 glColor3ub(128,128,128);

 rect.x=grid_offset_x-border_size;
 rect.y=0*block_size;
 rect.w=border_size;
 rect.h=height;

 clRectf(rect.x,rect.y,rect.x+rect.w,rect.y+rect.h);

 rect.x=grid_offset_x+grid_width*block_size;

 clRectf(rect.x,rect.y,rect.x+rect.w,rect.y+rect.h);

 /*end of drawing code for grid*/

 draw_stats();

 /*optionally, get input from another file instead of keyboard if I have this enabled.*/
 next_file_input();

 /*check for keypresses or other events*/
 glfwPollEvents();

 /*flush all gl commands and display to the screen*/
 glfwSwapBuffers( window );

 /*time loop used to slow the game down so users can see it*/
 while(glfwseconds<glfwseconds1)
 {
  glfwseconds=glfwGetTime();
 }

 frame++;

 }

}
