/*
To avoid corrupting my font library during development, I created this source file to make a set of functions entirely dedicated to my new file format.
*/

typedef uint32_t Uint32;

struct lgbt
{
 Uint32 width,height,bpp;
 Uint32 *pixels;
};

struct lgbt main_lgbt;

int lgbt_main_color=0xFFFFFF; /*global color for all drawn text*/





/*
A function to load my lgbt image format.

This function uses fread to read the data from the file in a way that works best with standard library functions.
*/
struct lgbt lgbt_load(const char *filename)
{
 char id_string[16];
 int x,y,pixel,x2,c,bitcount,bits;
 FILE* fp;
 struct lgbt new_lgbt;
 new_lgbt.pixels=NULL; /*default to NULL for pixels before allocation*/

 fp=fopen(filename,"rb");
 printf("This function loads a LGBT file into a structure.\n");
 if(fp==NULL)
 {
  printf("Failed to read file \"%s\": Doesn't exist.\n",filename);
  return new_lgbt;
 }

 fread(id_string,sizeof(*id_string),4,fp);
 if(strncmp(id_string,"LGBT",4)!=0){printf("Error not an LGBT file!\n");return new_lgbt;}
 fread(&new_lgbt.width,4,1,fp);
 fread(&new_lgbt.height,4,1,fp);
 fread(&new_lgbt.bpp,4,1,fp);

 printf("new_lgbt width=%d height=%d bpp=%d\n",new_lgbt.width,new_lgbt.height,new_lgbt.bpp);

 new_lgbt.pixels=(uint32_t*)malloc((new_lgbt.width*new_lgbt.height)*sizeof(*new_lgbt.pixels));
 if(new_lgbt.pixels==NULL){printf("Error: malloc failed,\n");}
 else
 {
  printf("Allocated the pixels for lgbt image.\n");

  y=0;
  while(y<new_lgbt.height)
  {


   bitcount=0;
   x=0;
   while(x<new_lgbt.width)
   {
    if(bitcount%8==0)
    {
     c=fgetc(fp);
     if(feof(fp))
     {
      printf("End of file reached.\n");
     }
      
    }
   
    bits=c >> (8-new_lgbt.bpp);
    c<<=new_lgbt.bpp;
    c&=255;
    bitcount+=new_lgbt.bpp;

   /*bits^=1;*/

    /*convert gray into a 24 bit RGB equivalent.*/
    pixel=0;
    x2=0;
    while(x2<24)
    {
     pixel<<=new_lgbt.bpp;
     pixel|=bits;
     x2+=new_lgbt.bpp;
    }

    new_lgbt.pixels[x+y*new_lgbt.width]=pixel;
    x++;
   }
   y++;

  }
  
 }

 fclose(fp);
 printf("Loaded from file: %s\n",filename);
 return new_lgbt;
}





/*
An SDL_Rect structure because a lot of this code was copied from the SDL version of Chaste Tris.
SDL is not required but I have the rectangle structure and this ports it easily.
*/
typedef struct SDL_Rect
{
    int x, y;
    int w, h;
} SDL_Rect;

SDL_Rect rect;




/*
This uses direct pixel access of the source lgbt font to draw only when the source pixel is not black.
*/
void lgbt_draw_text(const char *s,int cx,int cy,int scale)
{
 int x,y,i,c,cx_start=cx;
 int sx,sy,sx2,sy2,dx,dy; /*x,y coordinates for both source and destination*/
 Uint32 pixel,r,g,b; /*pixel that will be read from*/
 SDL_Rect rect_source,rect_dest;
 int char_width=main_lgbt.width/95; /*there are 95 characters in my font files*/
 int char_height=main_lgbt.height;

 if(main_lgbt.pixels==NULL){/*printf("Error: Font is NULL!\n");*/return;}

 i=0;
 while(s[i]!=0)
 {
  c=s[i];
  if(c=='\n'){ cx=cx_start; cy+=char_height*scale;}
  else
  {
   x=(c-' ')*char_width;
   y=0*char_height;

   /*set up source rectangle where this character will be copied from*/
   rect_source.x=x;
   rect_source.y=y;
   rect_source.w=char_width;
   rect_source.h=char_height;
 
   /*Now for the ultra complicated stuff that only Chastity can read and understand!*/
   sx2=rect_source.x+rect_source.w;
   sy2=rect_source.y+rect_source.h;
   
   dx=cx;
   dy=cy;
   
   sy=rect_source.y;
   while(sy<sy2)
   {
    dx=cx;
    sx=rect_source.x;
    while(sx<sx2)
    {
     pixel=main_lgbt.pixels[sx+sy*main_lgbt.width];
     pixel&=0xFFFFFF;
     
     if(pixel!=0) /*only if source pixel is nonzero(not black) draw square to destination*/
     {
      rect_dest.x=dx;
      rect_dest.y=dy;
      rect_dest.w=scale;
      rect_dest.h=scale;
      
      pixel=lgbt_main_color;
      
      r=(pixel&0xFF0000)>>16;
      g=(pixel&0x00FF00)>>8;
      b=(pixel&0x0000FF);
      
      clColor3ub(r,g,b);
      clRectf(rect_dest.x,rect_dest.y,rect_dest.x+rect_dest.w,rect_dest.y+rect_dest.h);
      
     }
     
     sx++;
     dx+=scale;
    }
    sy++;
    dy+=scale;
   }
   /*End of really complicated section*/
   cx+=char_width*scale;
  }
  i++;
 }

}






































