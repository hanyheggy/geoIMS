/*-----------------------------------------------------------------------------------------------*/    
/*                                Draw Vector and Generate Image                                 */
/*-----------------------------------------------------------------------------------------------*/    

/*-----------------------------------------------------------------------------------------------*/    
/*                                   Inculde Files                                               */
/*-----------------------------------------------------------------------------------------------*/    
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wand/magick_wand.h>

#define ThrowWandException(wand) \
    { \
      char \
        *description; \
     \
      ExceptionType \
        severity; \
     \
      description=MagickGetException(wand,&severity); \
      (void) fprintf(stderr,"%s %s %ld %s\n",GetMagickModule(),description); \
      description=(char *) MagickRelinquishMemory(description); \
      exit(-1); \
    }
    
/*-----------------------------------------------------------------------------------------------*/    
/*                                           main ()                                             */
/*-----------------------------------------------------------------------------------------------*/    
int main(int argc,char **argv)
{
 MagickBooleanType    status      ;
 MagickWand          *magick_wand ;
 
 DrawingWand         *draw_wand   ;
 PixelWand           *stroke_wand ;   
 
      
 // Create Draw_Wand ( Drawing Tile ) 
 draw_wand=NewDrawingWand();  

         
 /* DrawSetStrokeColor ( DrawingWand *wand, const PixelWand *stroke_wand ); */
// DrawSetStrokeColor ( draw_wand, stroke_wand);       
 
 /* DrawLine ( DrawingWand *wand, const double sx, const double sy, const double ex, const double ey ); */
 DrawLine ( draw_wand, 0, 0, 100, 100 );
      
 // Turn the images into a thumbnail sequence 
 /*
 MagickResetIterator(magick_wand);
 while (MagickNextImage(magick_wand) != MagickFalse)
 MagickResizeImage(magick_wand,106,80,LanczosFilter,1.0);
 */
 
 // Write the image as MIFF and destroy it 
 status=MagickWriteImages((MagickWand)draw_wand,"image1.png",True);
 if (status == MagickFalse)
    { 
     ThrowWandException(draw_wand);
    } 
      
      
 // Destory Draw_Wand 
 DestroyDrawingWand ( draw_wand );
 
 // return 
 return(0);
 
}
