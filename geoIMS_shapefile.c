/*------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
/*                                     geoIMS Beta Version                                        */
/*------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------------------------*/
/*                                    geoIMS Include Files                                        */
/*------------------------------------------------------------------------------------------------*/
#include "include/geoIMS.h"

/*------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
/*                                          main()                                                */
/*------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
int main ()
{
 import_shapefile("/home/geoinfo/geoIMS/SOURCE/data/ARCINFO/st.shp");




}
/*------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
/*                                    import_shapefile()                                          */
/*------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
import_shapefile(  char *InputFile)
{
 /*--------------------*/
 /* Local Variables    */
 /*--------------------*/
 long    shape_int    ;
 double  shape_double ;

 unsigned long   file_lenght  ;
 long    shape_type   ;

 double  shape_xmin   ;
 double  shape_ymin   ;
 double  shape_xmax   ;
 double  shape_ymax   ;


 fp_i = fopen (InputFile,"rb");
 if  ( fp_i == NULL )
     {
      printf(" ERROR : Can't open input file  !\n");
      return ;
     }

 printf ("---------------------------------------------------------------------------\n");
 printf ("INFO  : File Header \n");
 printf ("---------------------------------------------------------------------------\n");
 fread (&shape_int,   sizeof(shape_int)   ,1,fp_i);
 printf("File Header[1]  >> File code   [%d]\n",shape_int>>16  );

 fread (&shape_int,   sizeof(shape_int)   ,1,fp_i); // printf("File Header[2]  >> unsed    [%d]\n",shape_int  );
 fread (&shape_int,   sizeof(shape_int)   ,1,fp_i); // printf("File Header[3]  >> unsed    [%d]\n",shape_int  );
 fread (&shape_int,   sizeof(shape_int)   ,1,fp_i); // printf("File Header[4]  >> unsed    [%d]\n",shape_int  );
 fread (&shape_int,   sizeof(shape_int)   ,1,fp_i); // printf("File Header[5]  >> unsed    [%d]\n",shape_int  );
 fread (&shape_int,   sizeof(shape_int)   ,1,fp_i); // printf("File Header[6]  >> unsed    [%d]\n",shape_int  );

 fread (&file_lenght, sizeof(file_lenght) ,1,fp_i);
 printf("File Header[7]  >> File length [%d]\n",file_lenght>>16);
 printf("File Header[7]  >> File length [%X]\n",file_lenght>>16);

 fread (&shape_int  , sizeof(shape_int)   ,1,fp_i);
 printf("File Header[8]  >> version     [%d]\n",shape_int  );
 printf("File Header[8]  >> version     [%X]\n",shape_int  );

 fread (&shape_type, sizeof(shape_type)  ,1,fp_i); printf("File Header[9]  >> shape type  [%d]\n",shape_type );

 fread (&shape_xmin,sizeof(shape_xmin),1,fp_i); printf("File Header[10] >> Xmin        [%f]\n",shape_xmin);
 fread (&shape_ymin,sizeof(shape_ymin),1,fp_i); printf("File Header[11] >> Ymin        [%f]\n",shape_ymin);
 fread (&shape_xmax,sizeof(shape_xmax),1,fp_i); printf("File Header[12] >> Xmax        [%f]\n",shape_xmax);
 fread (&shape_ymax,sizeof(shape_ymax),1,fp_i); printf("File Header[13] >> Ymax        [%f]\n",shape_ymax);

 fread (&shape_double,sizeof(shape_double),1,fp_i); printf("File Header[14] >> Zmin        [%f]\n",shape_double);
 fread (&shape_double,sizeof(shape_double),1,fp_i); printf("File Header[15] >> Zmax        [%f]\n",shape_double);
 fread (&shape_double,sizeof(shape_double),1,fp_i); printf("File Header[16] >> Mmin        [%f]\n",shape_double);
 fread (&shape_double,sizeof(shape_double),1,fp_i); printf("File Header[17] >> Mmax        [%f]\n",shape_double);
 printf ("---------------------------------------------------------------------------\n");


 printf ("---------------------------------------------------------------------------\n");
 printf ("INFO  : Record Header \n");
 printf ("---------------------------------------------------------------------------\n");
 fread (&shape_int,   sizeof(shape_int)   ,1,fp_i); printf("Record Header[1]  >> Record number [%d]\n",shape_int>>24  );
 fread (&shape_int,   sizeof(shape_int)   ,1,fp_i); printf("Record Header[1]  >> Record length [%d]\n",shape_int>>24  );


 fclose(fp_i);

 printf(" INFO : Import Shape_File Function Completed \n");
}

/*------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
/*                                      export_shapefile()                                        */
/*------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
/*
void export_shapefile(char *OutputFile)
{
 int   xcolor ;
 char  *str   ;

 strcat(OutputFile,".infb");

 fp_o = fopen (OutputFile,"wb");

 if  ( fp_o == NULL )
     {
      fprintf (stderr,"ERROR : Can't open output file  !\n");
      return ;
     }

 printf ("INFO  : Processing output file ..\n");

      if ( DB_UNIT == 1 ) strcpy (DB_UNIT_name , "MM") ;
 else if ( DB_UNIT == 2 ) strcpy (DB_UNIT_name , "CM") ;
 else if ( DB_UNIT == 3 ) strcpy (DB_UNIT_name , "DM") ;
 else if ( DB_UNIT == 4 ) strcpy (DB_UNIT_name , "M" ) ;
 else if ( DB_UNIT == 5 ) strcpy (DB_UNIT_name , "KM") ;


 fwrite (&DB_UNIT_name , sizeof(DB_UNIT_name) , 1 , fp_o) ;
 fwrite (&x_min        , sizeof(x_min)        , 1 , fp_o) ;
 fwrite (&y_min        , sizeof(y_min)        , 1 , fp_o) ;
 fwrite (&x_max        , sizeof(x_max)        , 1 , fp_o) ;
 fwrite (&y_max        , sizeof(y_max)        , 1 , fp_o) ;


 for ( i=1 ; i <= feat_count ; i++  )
     {
	   if (feat[i].color == blue.pixel  ){ xcolor=blue.pixel  ; feat[i].color = 1  ;}
      else if (feat[i].color == red.pixel   ){ xcolor=red.pixel   ; feat[i].color = 2  ;}
      else if (feat[i].color == pink.pixel  ){ xcolor=pink.pixel  ; feat[i].color = 3  ;}
      else if (feat[i].color == green.pixel ){ xcolor=green.pixel ; feat[i].color = 4  ;}
      else if (feat[i].color == cyan.pixel  ){ xcolor=cyan.pixel  ; feat[i].color = 5  ;}
      else if (feat[i].color == yellow.pixel){ xcolor=yellow.pixel; feat[i].color = 6  ;}
      else if (feat[i].color == white.pixel ){ xcolor=white.pixel ; feat[i].color = 7  ;}
      else if (feat[i].color == black.pixel ){ xcolor=black.pixel ; feat[i].color = 8  ;}
      else if (feat[i].color == gray.pixel  ){ xcolor=gray.pixel  ; feat[i].color = 9  ;}
      else if (feat[i].color == wheat.pixel ){ xcolor=wheat.pixel ; feat[i].color = 10 ;}
      else if (feat[i].color == brown.pixel ){ xcolor=brown.pixel ; feat[i].color = 11 ;}
      else if (feat[i].color == orange.pixel){ xcolor=orange.pixel; feat[i].color = 12 ;}
      else if (feat[i].color == lgray.pixel ){ xcolor=lgray.pixel ; feat[i].color = 13 ;}
      else       /* default color */     /*    { xcolor=white.pixel ; feat[i].color = 7  ;}

      fwrite (&feat[i] , sizeof(feat[i]) , 1 , fp_o) ;

      feat[i].color = xcolor ;


      if  ( feat[i].xy_count > 0 )
	  {
	   for ( ii=1 ; ii<=feat[i].xy_count ; ii++ )
	       {
		fwrite (&x[feat[i].xy+ii],sizeof(x[0]),1,fp_o) ;
		fwrite (&y[feat[i].xy+ii],sizeof(y[0]),1,fp_o) ;
	       }
	  }

      if  ( feat[i].has_text[0] == 'Y' )
	  {
	   for ( ii=1 ; ii<=feat[i].text_count ; ii++ )
	       {
		fwrite (&text[feat[i].text+ii],sizeof(text[0]),1,fp_o) ;
	       }
	  }


     } /* main loop */
/*
 fclose(fp_o);
 // normal_cursor();

 xstr = XmStringCreate(" INFO : Export Binary inf Function Completed",CS);
 XtSetArg(args[0], XmNlabelString ,  xstr);
 XtSetValues(output_label,args,1);
}

*/
