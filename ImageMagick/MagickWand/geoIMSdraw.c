/*-----------------------------------------------------------------------------------------------*/    
/*                                         geoIMSdraw.c                                          */
/*-----------------------------------------------------------------------------------------------*/    

/*-----------------------------------------------------------------------------------------------*/    
/*                                   Inculde Files                                               */
/*-----------------------------------------------------------------------------------------------*/    
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*-----------------------------------------------------------------------------------------------*/    
/*                               ImageMagick Inculde Files                                       */
/*-----------------------------------------------------------------------------------------------*/    
#include <wand/magick_wand.h>
#include <magick/api.h>

/*-----------------------------------------------------------------------------------------------*/    
/*                                   Defined Macros                                              */
/*-----------------------------------------------------------------------------------------------*/    
#define CHECK_WAND_ERROR( wand, ErrFuncName, line )                                                       \
{                                                                                                         \
 char         *description ;                                                                              \
 ExceptionType severity    ;                                                                              \
                                                                                                          \
 description = ErrFuncName ( wand, &severity );                                                           \
 fprintf(stderr,"An error was reported on line %d (" #ErrFuncName "() output): %s\n\n",line,description); \
 MagickRelinquishMemory( description );                                                                   \
}

#define CLEAR_FILENAME( magick_wand, GetFilenameFunc, SetFilenameFunc )         \
{                                                                               \
 char *orig_filename  ;                                                         \
 int   filename_valid ;                                                         \
                                                                                \
 orig_filename = (char *) (GetFilenameFunc ( magick_wand ));                    \
 filename_valid = !(orig_filename == (char *) NULL || *orig_filename == '\0');  \
                                                                                \
 if ( filename_valid ) {  SetFilenameFunc ( magick_wand, "" );  }               \
}

/*-----------------------------------------------------------------------------------------------*/    
/*                                  Function Forward Decleration                                 */
/*-----------------------------------------------------------------------------------------------*/
    
MagickBooleanType WriteImageFile   (MagickWand *magick_wand, char *file_name);
MagickBooleanType WriteImagesFile  (MagickWand *magick_wand, char *file_name);
MagickBooleanType FilePutBlob      (char *file_name        , unsigned char *BLOB   , size_t BLOB_len         );
MagickBooleanType AddDrawNewImages (MagickWand *magick_wand, DrawingWand *draw_wand, unsigned long num_images);


/*-----------------------------------------------------------------------------------------------*/    
/*                                  Global Variables                                             */
/*-----------------------------------------------------------------------------------------------*/
 PixelWand     *color[256]   ;

 
/*-----------------------------------------------------------------------------------------------*/    
/*-----------------------------------------------------------------------------------------------*/    
/*                                           main ()                                             */
/*-----------------------------------------------------------------------------------------------*/    
/*-----------------------------------------------------------------------------------------------*/    
int main( int argc, char **argv )
{
 MagickWand    *magick_wand ;
 DrawingWand   *draw_wand   ;
 unsigned char *blob        ;
 size_t         blob_length ;
 long           i           ;

 // Create Main Objects   
 magick_wand = NewMagickWand ();  // Create MagickWand  ( The Image   object ) 
 draw_wand   = NewDrawingWand();  // Create DrawingWand ( The Drawing object )
 
 // Create PixelWand (Color Map), Assign Colors 
 for ( i=1 ; i<=14 ; i++ )  
     {
      color [i] = NewPixelWand() ;  
      switch (i)
        { 
         case 1: 
             if ( PixelSetColor(color[i],"blue") == MagickFalse )
	        { 
		 printf("ERROR :  allocating blue color"); 
		}
	     break ;
         case 2: 
             if ( PixelSetColor (color[i],"red") == MagickFalse )  
	        { 
		 printf("ERROR :  allocating red color"); 
		}
	     break ;
         case 3: 
             if ( PixelSetColor (color[i],"pink") == MagickFalse )  
	        { 
		 printf("ERROR :  allocating pink color"); 
		}
	     break ;
         case 4: 
             if ( PixelSetColor (color[i],"green") == MagickFalse )  
	        { 
		 printf("ERROR :  allocating green color"); 
		}
	     break ;
         case 5: 
             if ( PixelSetColor (color[i],"cyan") == MagickFalse )  
	        { 
		 printf("ERROR :  allocating cyan color"); 
		}
	     break ;
         case 6: 
             if ( PixelSetColor (color[i],"yellow") == MagickFalse )  
	        { 
		 printf("ERROR :  allocating yellow color"); 
		}
	     break ;
         case 7: 
             if ( PixelSetColor (color[i],"white") == MagickFalse )  
	        { 
		 printf("ERROR :  allocating white color"); 
		}
	     break ;
         case 8: 
             if ( PixelSetColor (color[i],"black") == MagickFalse )  
	        { 
		 printf("ERROR :  allocating black color"); 
		}
	     break ;
         case 9: 
             if ( PixelSetColor (color[i],"gray") == MagickFalse )  
	        { 
		 printf("ERROR :  allocating gray color"); 
		}
	     break ;
         case 10: 
             if ( PixelSetColor (color[i],"wheat") == MagickFalse )  
	        { 
		 printf("ERROR :  allocating wheat color"); 
		}
	     break ;
         case 11: 
             if ( PixelSetColor (color[i],"brown") == MagickFalse )  
	        { 
		 printf("ERROR :  allocating brown color"); 
		}
	     break ;
         case 12: 
             if ( PixelSetColor (color[i],"orange") == MagickFalse )  
	        { 
		 printf("ERROR :  allocating orange color"); 
		}
	     break ;
         case 13: 
             if ( PixelSetColor (color[i],"light gray") == MagickFalse )  
	        { 
		 printf("ERROR :  allocating light gray color"); 
		}
	     break ;
         case 14: 
             if ( PixelSetColor (color[i],"magenta") == MagickFalse )  
	        { 
		 printf("ERROR :  allocating magenta color"); 
		}
	     break ;
	     
	}     
     } 
 
 /* Create Color Map
 if ( PixelSetColor( color, "green" ) == MagickFalse )   // Set Draw Color
    {
     CHECK_WAND_ERROR( color, PixelGetException, __LINE__ );
     DestroyPixelWand( color );
     exit( -1 );
    }
*/

 // Set DrawingWand Parameters
 DrawSetFontSize ( draw_wand , 100           );
 DrawSetGravity  ( draw_wand , CenterGravity );
 DrawSetFillColor( draw_wand , color[1]      );

    
 if ( AddDrawNewImages( magick_wand, draw_wand, 2 ) == MagickTrue ) 
    {
     // The following explicitly clears the MagickWand's filename 
     CLEAR_FILENAME( magick_wand, MagickGetFilename, MagickSetFilename );

     // Setting the MagickWand's image format to GIF 
     if ( MagickSetImageFormat( magick_wand, "GIF" ) == MagickTrue ) 
	{
         /* Fails, as it should, as no image format or filename exists for the current active image */
         // MagickClearException( magick_wand );
         blob = MagickGetImageBlob( magick_wand, &blob_length );
         if ( blob_length > 0 ) 
	    {
             FilePutBlob( "./image_blob.gif", blob, blob_length );
             MagickRelinquishMemory( blob );
            }
         else 
	    {
             fprintf( stderr, "\nAnticipated error -> " );
             CHECK_WAND_ERROR( magick_wand, MagickGetException, __LINE__ );
            }

         /* Succeeds */
         //MagickClearException( magick_wand );
         if ( MagickWriteImage( magick_wand, "./image_write.gif" ) == MagickFalse ) 
	    {
             CHECK_WAND_ERROR( magick_wand, MagickGetException, __LINE__ );
            }
            
         /* Succeeds */
         //MagickClearException( magick_wand );
         if ( WriteImageFile( magick_wand, "./image_file.gif" ) == MagickFalse ) 
	    {
             CHECK_WAND_ERROR( magick_wand, MagickGetException, __LINE__ );
            }
            
         // The following attempt to get the BLOB of the MagickWand's image sequence
         // SHOULD NOT FAIL, but it still does.
         // Unlike the attempt to get an individual image's BLOB above, (in the absence
         // of an image filename or a set format), the format of the MagickWand's image
         // equence was set previously, and should be used.
            
         //MagickClearException( magick_wand );
         blob = MagickGetImageBlob( magick_wand, &blob_length );
         if ( blob_length > 0 ) 
	    {
             FilePutBlob( "./images_blob.gif", blob, blob_length );
             MagickRelinquishMemory( blob );
            }
         else 
	    {
             CHECK_WAND_ERROR( magick_wand, MagickGetException, __LINE__ );
            }

         /* Succeeds */
         //MagickClearException( magick_wand );
         if ( MagickWriteImages( magick_wand, "./images_write.gif", MagickTrue ) == MagickFalse )
            {
             CHECK_WAND_ERROR( magick_wand, MagickGetException, __LINE__ );
            }

         /* Succeeds */
         //MagickClearException( magick_wand );
         if ( MagickWriteImages( magick_wand, "./images_write.gif", MagickFalse ) == MagickFalse )
            {
             CHECK_WAND_ERROR( magick_wand, MagickGetException, __LINE__ );
            }

         /* Succeeds */
         //MagickClearException( magick_wand );
         if ( WriteImagesFile( magick_wand, "./images_file.gif" ) == MagickFalse ) 
	    {
             CHECK_WAND_ERROR( magick_wand, MagickGetException, __LINE__ );
            }
        }
     else 
        {
         CHECK_WAND_ERROR( magick_wand, MagickGetException, __LINE__ );
        }
    }

    
 /////////////////   
 // Free Memeory
 /////////////////   
 for ( i=1 ; i<=14 ; i++ )  
     {
      DestroyPixelWand( color[i] );
     } 
 DestroyMagickWand ( magick_wand );
 DestroyDrawingWand( draw_wand  );

 return( 0 );
 
}
/*-----------------------------------------------------------------------------------------------*/    
/*                                   WriteImageFile ()                                           */
/*-----------------------------------------------------------------------------------------------*/    
MagickBooleanType WriteImageFile( MagickWand *magick_wand, char *file_name )
{
 FILE             *fp_o             ;
 MagickBooleanType rc = MagickFalse ;

 
 fp_o = fopen( file_name, "w" );
 if ( fp_o == (FILE *) NULL ) 
    {
     fprintf( stderr, "*****Could not open filehandle to file '%s'*****\n", file_name );
     return rc;
    }
 else 
    {
     if ( MagickWriteImageFile( magick_wand, fp_o ) == MagickTrue ) 
        {
         rc = MagickTrue;
        }
     else 
        {
         fprintf( stderr, "WriteImageFile(): FAILED writing to %s filehandle: ", file_name );
        }
     fclose( fp_o );
    }
    
 return rc;

}
/*-----------------------------------------------------------------------------------------------*/    
/*                                   WriteImagesFile ()                                          */
/*-----------------------------------------------------------------------------------------------*/    
MagickBooleanType WriteImagesFile ( MagickWand *magick_wand, char *file_name )
{
 FILE             *fp_o             ;
 MagickBooleanType rc = MagickFalse ;

 
 fp_o = fopen( file_name, "w" );
 if ( fp_o == (FILE *) NULL ) 
    {
     fprintf( stderr, "*****Could not open filehandle to file '%s'*****\n", file_name );
     return rc;
    }
 else 
    {
     if ( MagickWriteImageFile( magick_wand, fp_o ) == MagickTrue ) 
        {
         rc = MagickTrue;
        }
     else 
        {
         fprintf( stderr, "WriteImagesFile(): FAILED writing to %s filehandle: ", file_name );
        }
     
     fclose( fp_o );
    }
    
 return rc;
 
}
/*-----------------------------------------------------------------------------------------------*/    
/*                                   FilePutBlob()                                               */
/*-----------------------------------------------------------------------------------------------*/    
MagickBooleanType FilePutBlob( char *file_name, unsigned char *BLOB, size_t BLOB_len )
{
 FILE             *fp_o             ;
 MagickBooleanType rc = MagickFalse ;

 
 fp_o = fopen( file_name, "w" );
 if ( fp_o == (FILE *) NULL ) 
    {
     fprintf( stderr, "*****Could not open filehandle to file '%s'*****\n", file_name );
     return rc;
    }
 else 
    {
     if ( BLOB_len == fwrite( BLOB, sizeof(unsigned char), BLOB_len, fp_o ) ) 
        {
         rc = MagickTrue;
        }
     else 
        {
         printf( "FilePutBlob(): FAILED in writing image(s) to filehandle opened on file %s\n",file_name );
        }
	
     fclose( fp_o );
    }
    
 return rc;
 
}
/*-----------------------------------------------------------------------------------------------*/    
/*                                   AddDrawNewImages()                                          */
/*-----------------------------------------------------------------------------------------------*/    
MagickBooleanType AddDrawNewImages( MagickWand *magick_wand, DrawingWand *draw_wand, unsigned long num_images )
{
 MagickBooleanType rc            ;
 unsigned long     i             ;
 long              last_idx      ;
 char              idx_str[ 50 ] ;

 
 
 DrawSetStrokeColor ( draw_wand, color[4]);
 DrawSetStrokeWidth ( draw_wand, 1       );

 for ( i = 0; i < num_images; i++ ) 
     {
      rc = MagickFalse;

      if ( MagickNewImage ( magick_wand, 500, 500, color[5]  ) == MagickTrue ) 
         {
          last_idx = (long) ( MagickGetNumberImages( magick_wand ) - 1 );
          printf( "Created new image at MagickWand index %ld\n", last_idx );

          if ( MagickSetImageIndex( magick_wand, last_idx ) == MagickTrue ) 
             {
              DrawLine ( draw_wand, 1, 1, 199, 199 );
              MagickDrawImage ( magick_wand, draw_wand );	      
              rc = MagickTrue;

	      /*
              sprintf( idx_str, "hany %ld", last_idx );
              if ( (MagickAnnotateImage( magick_wand, draw_wand, 0, 0, 0, idx_str ) == MagickTrue) &&
                   (MagickSetImageDelay( magick_wand, 50 ) == MagickTrue) )
                 {
                  rc = MagickTrue;
                  CLEAR_FILENAME( magick_wand, MagickGetImageFilename, MagickSetImageFilename);
                 }*/
             }
         }

      if ( rc == MagickFalse ) 
         {
          break;
         }
     }

// DestroyPixelWand( color );
// DestroyPixelWand( bg_color );

 if ( rc == MagickFalse ) 
    {
     CHECK_WAND_ERROR( magick_wand, MagickGetException, __LINE__ );
    }

 return rc;
 
}
