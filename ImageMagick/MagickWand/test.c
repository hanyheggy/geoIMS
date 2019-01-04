/*-----------------------------------------------------------------------------------------------*/    
/*                                Draw Vector and Generate Image                                 */
/*-----------------------------------------------------------------------------------------------*/    

/*-----------------------------------------------------------------------------------------------*/    
/* After the MagickWand's image sequence's image format has been set with MagickSetImageFormat() */
/* MagickGetImageBlob() fails if the images in the MagickWand's image sequence have no image     */
/* formats or filenames set.                                                                     */
/* The API does not seem to automatically recognize and use the MagickWand's image format as     */
/* the required parent / output format.                                                          */
/*-----------------------------------------------------------------------------------------------*/    

/*-----------------------------------------------------------------------------------------------*/    
/*                                   Inculde Files                                               */
/*-----------------------------------------------------------------------------------------------*/    
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

#define CLEAR_FILENAME( mgck_wnd, GetFilenameFunc, SetFilenameFunc )            \
{                                                                               \
 char *orig_filename  ;                                                         \
 int   filename_valid ;                                                         \
                                                                                \
 orig_filename = (char *) (GetFilenameFunc ( mgck_wnd ));                       \
 filename_valid = !(orig_filename == (char *) NULL || *orig_filename == '\0');  \
                                                                                \
 if ( filename_valid ) {  SetFilenameFunc ( mgck_wnd, "" );  }                  \
}

/*-----------------------------------------------------------------------------------------------*/    
/*                                  Function Forward Decleration                                 */
/*-----------------------------------------------------------------------------------------------*/
    
MagickBooleanType WriteImageFile   (MagickWand *mgck_wnd, char *file_name);
MagickBooleanType WriteImagesFile  (MagickWand *mgck_wnd, char *file_name);
MagickBooleanType FilePutBlob      (char *file_name     , unsigned char *BLOB , size_t BLOB_len         );
MagickBooleanType AddDrawNewImages (MagickWand *mgck_wnd, DrawingWand *drw_wnd, unsigned long num_images);



/*-----------------------------------------------------------------------------------------------*/    
/*-----------------------------------------------------------------------------------------------*/    
/*                                           main ()                                             */
/*-----------------------------------------------------------------------------------------------*/    
/*-----------------------------------------------------------------------------------------------*/    
int main( int argc, char **argv )
{
 MagickWand    *mgck_wnd    ;
 DrawingWand   *drw_wnd     ;
 PixelWand     *color       ;
 unsigned char *blob        ;
 size_t         blob_length ;

    
 // Create PixelWand, then Set Draw Color
 color = NewPixelWand();
 if ( PixelSetColor( color, "green" ) == MagickFalse )
    {
     CHECK_WAND_ERROR( color, PixelGetException, __LINE__ );
     DestroyPixelWand( color );
     exit( -1 );
    }

 // Create MagickWand  
 mgck_wnd = NewMagickWand();
    
 // Create DrawingWand
 drw_wnd = NewDrawingWand();

 // Set DrawingWand Parameters
 DrawSetFontSize ( drw_wnd , 50            );
 DrawSetGravity  ( drw_wnd , CenterGravity );
 DrawSetFillColor( drw_wnd , color         );

    
 if ( AddDrawNewImages( mgck_wnd, drw_wnd, 10 ) == MagickTrue ) 
    {
     // The following explicitly clears the MagickWand's filename 
     CLEAR_FILENAME( mgck_wnd, MagickGetFilename, MagickSetFilename );

     // Setting the MagickWand's image format to GIF 
     if ( MagickSetImageFormat( mgck_wnd, "GIF" ) == MagickTrue ) 
	{
         /* Fails, as it should, as no image format or filename exists for the current active image */
         // MagickClearException( mgck_wnd );
         blob = MagickGetImageBlob( mgck_wnd, &blob_length );
         if ( blob_length > 0 ) 
	    {
             FilePutBlob( "./image_blob.gif", blob, blob_length );
             MagickRelinquishMemory( blob );
            }
         else 
	    {
             fprintf( stderr, "\nAnticipated error -> " );
             CHECK_WAND_ERROR( mgck_wnd, MagickGetException, __LINE__ );
            }

         /* Succeeds */
         //MagickClearException( mgck_wnd );
         if ( MagickWriteImage( mgck_wnd, "./image_write.gif" ) == MagickFalse ) 
	    {
             CHECK_WAND_ERROR( mgck_wnd, MagickGetException, __LINE__ );
            }
            
         /* Succeeds */
         //MagickClearException( mgck_wnd );
         if ( WriteImageFile( mgck_wnd, "./image_file.gif" ) == MagickFalse ) 
	    {
             CHECK_WAND_ERROR( mgck_wnd, MagickGetException, __LINE__ );
            }
            
         // The following attempt to get the BLOB of the MagickWand's image sequence
         // SHOULD NOT FAIL, but it still does.
         // Unlike the attempt to get an individual image's BLOB above, (in the absence
         // of an image filename or a set format), the format of the MagickWand's image
         // equence was set previously, and should be used.
            
         //MagickClearException( mgck_wnd );
         blob = MagickGetImageBlob( mgck_wnd, &blob_length );
         if ( blob_length > 0 ) 
	    {
             FilePutBlob( "./images_blob.gif", blob, blob_length );
             MagickRelinquishMemory( blob );
            }
         else 
	    {
             CHECK_WAND_ERROR( mgck_wnd, MagickGetException, __LINE__ );
            }

         /* Succeeds */
         //MagickClearException( mgck_wnd );
         if ( MagickWriteImages( mgck_wnd, "./images_write.gif", MagickTrue ) == MagickFalse )
            {
             CHECK_WAND_ERROR( mgck_wnd, MagickGetException, __LINE__ );
            }

         /* Succeeds */
         //MagickClearException( mgck_wnd );
         if ( MagickWriteImages( mgck_wnd, "./images_write.gif", MagickFalse ) == MagickFalse )
            {
             CHECK_WAND_ERROR( mgck_wnd, MagickGetException, __LINE__ );
            }

         /* Succeeds */
         //MagickClearException( mgck_wnd );
         if ( WriteImagesFile( mgck_wnd, "./images_file.gif" ) == MagickFalse ) 
	    {
             CHECK_WAND_ERROR( mgck_wnd, MagickGetException, __LINE__ );
            }
        }
     else 
        {
         CHECK_WAND_ERROR( mgck_wnd, MagickGetException, __LINE__ );
        }
    }

 /////////////////   
 // Free Memeory
 /////////////////   
 DestroyMagickWand ( mgck_wnd );
 DestroyDrawingWand( drw_wnd  );

 return( 0 );
 
}
/*-----------------------------------------------------------------------------------------------*/    
/*                                   WriteImageFile ()                                           */
/*-----------------------------------------------------------------------------------------------*/    
MagickBooleanType WriteImageFile( MagickWand *mgck_wnd, char *file_name )
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
     if ( MagickWriteImageFile( mgck_wnd, fp_o ) == MagickTrue ) 
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
MagickBooleanType WriteImagesFile ( MagickWand *mgck_wnd, char *file_name )
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
     if ( MagickWriteImageFile( mgck_wnd, fp_o ) == MagickTrue ) 
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
MagickBooleanType AddDrawNewImages( MagickWand *mgck_wnd, DrawingWand *drw_wnd, unsigned long num_images )
{
 MagickBooleanType rc      ;
 PixelWand         *black        ;
 unsigned long     i             ;
 long              last_idx      ;
 char              idx_str[ 50 ] ;

 
 black = NewPixelWand();

 for ( i = 0; i < num_images; i++ ) 
     {
      rc = MagickFalse;

      if ( MagickNewImage ( mgck_wnd, 500, 500, black ) == MagickTrue ) 
         {
          last_idx = (long) ( MagickGetNumberImages( mgck_wnd ) - 1 );
          printf( "Created new image at MagickWand index %ld\n", last_idx );

          if ( MagickSetImageIndex( mgck_wnd, last_idx ) == MagickTrue ) 
             {
              DrawLine ( drw_wnd, 1, 1, 199, 199 );
              sprintf( idx_str, "hany %ld", last_idx );

              if ( (MagickAnnotateImage( mgck_wnd, drw_wnd, 0, 0, 0, idx_str ) == MagickTrue) &&
                   (MagickSetImageDelay( mgck_wnd, 50 ) == MagickTrue) )
                 {
                  rc = MagickTrue;
                  CLEAR_FILENAME( mgck_wnd, MagickGetImageFilename, MagickSetImageFilename);
                 }
             }
         }

      if ( rc == MagickFalse ) 
         {
          break;
         }
     }

 DestroyPixelWand( black );

 if ( rc == MagickFalse ) 
    {
     CHECK_WAND_ERROR( mgck_wnd, MagickGetException, __LINE__ );
    }

 return rc;
 
}
