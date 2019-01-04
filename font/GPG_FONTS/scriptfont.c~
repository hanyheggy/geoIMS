/*------------------------------------------------------------------------*/
/*                    geoINFO/6000  Enhance script Font                   */
/*------------------------------------------------------------------------*/

/*------------------------------------------------------------------------*/
/*                          Standard Include Files                        */
/*------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <math.h>

/*------------------------------------------------------------------------*/
/*                         Global Variables                               */
/*------------------------------------------------------------------------*/


int   i  , ii , j           ;

FILE  *fp_i                 ; /* Input  file pointer                  */
FILE  *fp_o                 ; /* Output file pointer                  */
char  InputFile  [51]       ; /* Input  file name                     */
char  OutputFile [51]       ; /* Output file name                     */

typedef struct
  {
   int    stroke         ;
   int    grid           ;
   int    mv_draw [200]  ;
   int    x       [200]  ;
   int    y       [200]  ;
  } Symbols ;

Symbols   symb[300]      ; /* Symbol set data                      */

int  x_shift   ;
int  y_shift   ;
int  grid_size ;

int  min_x     ;
int  max_x     ;
int  grid     = 0  ;
char string [51]   ;


/*------------------------------------------------------------------------*/
/*                                main()                                  */
/*------------------------------------------------------------------------*/

main(int argc, char *argv[])
{


 if ( argc == 2 )
    {
     sscanf(argv[1],"%s",InputFile );
    }

 printf ("\n InputFile = %s  ",InputFile );


/*---------------------------------------------------------------------*/
/*                        Read geoINFO Font file                       */
/*---------------------------------------------------------------------*/

 fp_i = fopen (InputFile,"rt");
 if  ( fp_i == NULL )
     {
      printf ("\n Can't open input file  !");
      return ;
     }

 printf ("\n processing geoINFO Font file .." );

 while ( fscanf(fp_i,"%s", &string) != EOF ) /* Symbol Name                */
       {
        min_x =  1000 ;

	fscanf(fp_i,"%d", &i             );  /* Symbol Number              */
	fscanf(fp_i,"%d", &symb[i].grid  );  /* Symbol Max Grid Coordinate */
	fscanf(fp_i,"%d", &symb[i].stroke);  /* Number of strokes          */

	for ( ii=1 ; ii<=symb[i].stroke ; ii++ )
	    {
	     fscanf(fp_i,"%d", &symb[i].mv_draw[ii]);
	     fscanf(fp_i,"%d", &symb[i].x[ii]);
	     fscanf(fp_i,"%d", &symb[i].y[ii]);

	     /* Calculate Min x_stroke */
	     if ( symb[i].x[ii] < min_x ) { min_x = symb[i].x[ii] ; }
	    }

        grid = symb[i].grid ;


	/*  Script Font shift Enhancement */
        // if ( min_x > (-1*grid/2)  &&  grid != 0 &&  i >= 97  && i <= 122 )
	   
        if ( grid != 0 &&  i >= 97  && i <= 122 )
	   {
	    x_shift = min_x - (int)grid/2 ;

            switch(i)
	          {
	           case 100:	
	           case 120:
	           case 97:		   
                        x_shift = 3 ;
			break;

	          
		   case 107:
		   case 117:	
		   case 122:		
		   case 98:
		   case 111:	
		   case 104:	
		   case 121:		
		   case 103:	
		   case 118:	
                        x_shift = 4 ;
			break;

	           case 106:
                        x_shift = 11;
			break;
	         
	           case 116:
                        x_shift = 7 ;
			break;

		   case 105:
                        x_shift = 8 ;
			break;
		   
		   case 108:		
		   case 112:	
                        x_shift = 7 ;
			break;
		   
		   case 102:		
			x_shift = 10 ;
			break;
		   
		   case 109:
	           case 119:
			x_shift = 1  ;
			break;
		
	           case 110:
			x_shift = 2  ;
			break;

	           case 114:
		   case 113:		
			x_shift = 5  ;
			break;
		   
		   
		   default:
                        x_shift = 6 ;
			break;
		  }
	    
		
	    for ( ii=1 ; ii<=symb[i].stroke ; ii++ )
	        {
	         symb[i].x[ii] -= x_shift  ;
		}
	   }


       }

 fclose(fp_i);

 /*-------------------------------------------------------------*/
 /*                    Save geoINFO font                        */
 /*-------------------------------------------------------------*/

 strcpy (OutputFile,InputFile);
 strcat (OutputFile,".font");

 fp_o=fopen(OutputFile,"wt");
 if  ( fp_o== NULL )
     {
      printf ("\nERROR : Can't save font file !\n");
      return ;
     }

 printf ("\n processing geoINFO font file ..\n" );

 /* write space charcter ' '  */

 fprintf(fp_o,"\n\n' '");
 fprintf(fp_o,"\n32");
 fprintf(fp_o,"\n0" );
 fprintf(fp_o,"\n0" );


 for ( i=1; i<= 255; i++ )
     {
      if (symb[i].stroke != 0)
	 {
	  fprintf(fp_o,"\n\n'"               ) ;
	  fputc  ( i  ,fp_o                  ) ;
	  fprintf(fp_o,"'"                   ) ;
	  fprintf(fp_o,"\n%d", i             ) ;
	  fprintf(fp_o,"\n%d", symb[i].grid  ) ;
	  fprintf(fp_o,"\n%d", symb[i].stroke) ;

	  for ( ii=1 ; ii<=symb[i].stroke ; ii++ )
	      {
	       fprintf(fp_o,"\n%d   ", symb[i].mv_draw[ii]) ;
	       fprintf(fp_o,"%3d    ", symb[i].x[ii]) ;
	       fprintf(fp_o,"%3d    ", symb[i].y[ii]) ;
	      }
	 }
     }

 fclose(fp_o);

}
