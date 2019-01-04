/*------------------------------------------------------------------------*/
/*                geoINFO/6000  Plotting    ( geoplot.c )                 */
/*------------------------------------------------------------------------*/

/*------------------------------------------------------------------------*/
/*                       Standard Include Files                           */
/*------------------------------------------------------------------------*/
#include "include/geoIMSextern.h"

/*------------------------------------------------------------------------*/
/*                         Functions Prototypes                           */
/*------------------------------------------------------------------------*/
void cancelPlotCB() ;
void okPlotCB()     ;
void plot_symb()    ;
void plot_text()    ;

/*------------------------------------------------------------------------*/
/*                           Widget Definition                            */
/*------------------------------------------------------------------------*/
Widget  PlotShell          ;
Widget  PlotForm           ;
Widget  Plot_ok_button     ;
Widget  Plot_cancel_button ;
Widget  Label[10]          ;
Widget  Field[10]          ;

/*------------------------------------------------------------------------*/
/*                   File Level Global Variable Definition                */
/*------------------------------------------------------------------------*/
XtAppContext  Plot_context       ;
Display       *PlotDisplay       ;
XEvent        PlotEvent          ;

int           done = 0           ;

static  int   plot_scale         ;
static  int   plot_width         ;
static  int   plot_hight         ;
static  int   x_min_plt          ;
static  int   y_min_plt          ;
static  int   x_max_plt          ;
static  int   y_max_plt          ;


/*------------------------------------------------------------------------*/
/*                        plot_fit_to_paper()                             */
/*------------------------------------------------------------------------*/
void plot_fit_to_paper()
{
 int  ESC = 27       ;
 char cmd[50]        ;


 activateMenubar = 1 ;
 // wait_cursor()       ;


 fp_o = fopen ("geoinfo.gl","wt");
 if  ( fp_o == NULL )
     {
      printf ("\nERROR : Can't open PLOT file !");
      // normal_cursor () ;
      return ;
     }

 printf ("\nINFO  : Processing PLOT file ..");

 x_min_plot = x_min ;
 y_min_plot = y_min ;
 x_max_plot = x_max ;
 y_max_plot = y_max ;

 x_min1 = x_min_plot - SYMBCLIPBUFFER/2 ;
 y_min1 = y_min_plot - SYMBCLIPBUFFER/2 ;
 x_max1 = x_max_plot + SYMBCLIPBUFFER/2 ;
 y_max1 = y_max_plot + SYMBCLIPBUFFER/2 ;

 x_min2 = x_min_plot - LINECLIPBUFFER ;
 y_min2 = y_min_plot - LINECLIPBUFFER ;
 x_max2 = x_max_plot + LINECLIPBUFFER ;
 y_max2 = y_max_plot + LINECLIPBUFFER ;

 x_diff = x_max_plot - x_min_plot ;
 switch (DB_UNIT)
      {
       case MM: scale = ( x_diff * .1  ) / SCREEN_CM ; break ;
       case CM: scale = ( x_diff * 1   ) / SCREEN_CM ; break ;
       case DM: scale = ( x_diff * 10  ) / SCREEN_CM ; break ;
       case  M: scale = ( x_diff * 100 ) / SCREEN_CM ; break ;
       case KM: scale = ( x_diff * 1000) / SCREEN_CM ; break ;
       default: scale = ( x_diff * 100 ) / SCREEN_CM ;
		printf("\nERROR : Data Base Unit not Defined");
		break ;
      }

      if ( scale > 0     &&  scale <= 2500  ) sc_range = 0 ;
 else if ( scale > 2500  &&  scale <= 5000  ) sc_range = 1 ;
 else if ( scale > 5000  &&  scale <= 10000 ) sc_range = 2 ;
 else if ( scale > 10000 &&  scale <= 25000 ) sc_range = 3 ;
 else if ( scale > 25000                    ) sc_range = 4 ;


 fputc(ESC,fp_o );        // HP Printer Escape Charcter
 fprintf(fp_o ,"%1B");    // HP Printer Switch to GL Mode

 fprintf(fp_o ,"\nIN;");
 fprintf(fp_o ,"\nSC%d,%d,%d,%d,1;",(int)x_min_plot,(int)x_max_plot,(int)y_min_plot,(int)y_max_plot);
 fprintf(fp_o ,"\nLT;");
 fprintf(fp_o ,"\nSP7;");
 fprintf(fp_o ,"\nPA0,0;");
 fprintf(fp_o ,"\nPU%d,%d;",(int)x_min_plot,(int)y_min_plot);
 fprintf(fp_o ,"PD%d,%d,%d,%d,%d,%d,%d,%d,%d,%d;",
		 (int)x_min_plot,(int)y_min_plot,
		 (int)x_max_plot,(int)y_min_plot,
		 (int)x_max_plot,(int)y_max_plot,
		 (int)x_min_plot,(int)y_max_plot,
		 (int)x_min_plot,(int)y_min_plot  );


 for ( i=1 ; i<=feat_count ; i++ )
     {
      if      (feat[i].color == blue.pixel   )  color = 1  ;
      else if (feat[i].color == red.pixel    )  color = 2  ;
      else if (feat[i].color == pink.pixel   )  color = 3  ;
      else if (feat[i].color == green.pixel  )  color = 4  ;
      else if (feat[i].color == cyan.pixel   )  color = 5  ;
      else if (feat[i].color == yellow.pixel )  color = 6  ;
      else if (feat[i].color == white.pixel  )  color = 7  ;
      else if (feat[i].color == black.pixel  )  color = 8  ;
      else if (feat[i].color == gray.pixel   )  color = 9  ;
      else if (feat[i].color == wheat.pixel  )  color = 10 ;
      else if (feat[i].color == brown.pixel  )  color = 11 ;
      else if (feat[i].color == orange.pixel )  color = 12 ;
      else     color = 7  ;

      switch (feat[i].type)
       {
	case 1:    /*---------- Plot type one -------------- */

	 x_base = feat[i].xbase ;
	 y_base = feat[i].ybase ;

	 /* BASE POINT CLIPPING & MIN SYMBOL SIZE = 1 */
	 if ( (feat[i].displayed[0] == 'Y'         ) &&
	      (feat[i].scale_range[sc_range] == 'Y') &&
	      ((feat[i].symb_size/ONE_PIXEL) >= 1  ) &&
	      (x_base > x_min1)&&(x_base < x_max1) &&
	      (y_base > y_min1)&&(y_base < y_max1) )
	    {

	     /*....................*/
	     /*  PLOT TEXT IF ANY  */
	     /*....................*/
	     if (feat[i].has_text[0] == 'Y')
		{
		 for(ii=1; ii<=feat[i].text_count; ii++)
		    {
		     text_index = feat[i].text + ii ;
		     plot_text(text_index);
		    }
		}

	     /*...............*/
	     /*  PLOT SYMBOL  */
	     /*...............*/

	     plot_symb(feat[i].symb_num,x_base,y_base,color,feat[i].symb_size,feat[i].symb_angle);
	    }

	 break ;

	case 2:    /*-------------- Plot type two --------------------*/

	 x_base = feat[i].xbase ;
	 y_base = feat[i].ybase ;
	 x_end  = feat[i].xend  ;
	 y_end  = feat[i].yend  ;

	 /* END POINTS CLIPPING */
	 if ( (feat[i].displayed[0] == 'Y'         ) &&
	      (feat[i].scale_range[sc_range] == 'Y') &&
	      (((x_base>x_min2)&&(x_base<x_max2)&&(y_base>y_min2)&&(y_base<y_max2)) ||
	       ((x_end >x_min2)&&(x_end <x_max2)&&(y_end >y_min2)&&(y_end <y_max2))) )
	 {

	  /* fprintf(fp_o ,"\nPW%d",(int)feat[i].linewidth) ; */

	  /*....................*/
	  /*  PLOT TEXT IF ANY  */
	  /*....................*/
	  if (feat[i].has_text[0] == 'Y')
	     {
	      for(ii=1; ii<=feat[i].text_count; ii++)
		 {
		  text_index = feat[i].text + ii ;
		  plot_text(text_index);
		 }
	     }

	 /*..............*/
	 /*  PLOT LINE   */
	 /*..............*/
	 for ( ii=0 ; ii<=(feat[i].xy_count+1) ; ii++ )
	     {
	      switch (ii)
		  {
		   case 0:
		       x1_db = x_base ;
		       y1_db = y_base ;

		       SP_flag = 0 ;
		       break ;

		  default:
		       if ( ii <= feat[i].xy_count )
			  {
			   x2_db = x[feat[i].xy+ii] ;
			   y2_db = y[feat[i].xy+ii] ;
			  }
		       else
			  {
			   x2_db = x_end ;
			   y2_db = y_end ;
			  }

		      if (( x1_db>=x_min_plot && x1_db<=x_max_plot && y1_db>=y_min_plot && y1_db<=y_max_plot ) &&
			  ( x2_db>=x_min_plot && x2_db<=x_max_plot && y2_db>=y_min_plot && y2_db<=y_max_plot ))
			 {
			  if (SP_flag == 0) { fprintf(fp_o,"\nSP%d;",color); SP_flag =1; }
			  fprintf(fp_o ,"\nPU,%d,%d;",(int)x1_db,(int)y1_db);
			  fprintf(fp_o ,"PD%d,%d,%d,%d;",(int)x1_db,(int)y1_db,(int)x2_db,(int)y2_db);
			 }

		 else if ( x1_db>=x_min_plot && x1_db<=x_max_plot && y1_db>=y_min_plot && y1_db<=y_max_plot )
			 {
			  if ( x1_db == x2_db )   /* VL Segment */
			     {
			      if ( y2_db > y1_db )
				 {
				  y2_db = y_max_plot ;
				 }
			       else
				 {
				  y2_db = y_min_plot ;
				 }
			      if (SP_flag == 0) { fprintf(fp_o,"\nSP%d;",color); SP_flag =1; }
			      fprintf(fp_o ,"\nPU,%d,%d;",(int)x1_db,(int)y1_db);
			      fprintf(fp_o ,"PD%d,%d,%d,%d;",(int)x1_db,(int)y1_db,(int)x2_db,(int)y2_db);
			      goto endplot ;
			     }

			  if ( y1_db == y2_db )    /* HZ Segment */
			     {
			      if ( x2_db > x1_db )
				 {
				  x2_db = x_max_plot ;
				 }
			       else
				 {
				  x2_db = x_min_plot ;
				 }
			      if (SP_flag == 0) { fprintf(fp_o,"\nSP%d;",color); SP_flag =1; }
			      fprintf(fp_o ,"\nPU,%d,%d;",(int)x1_db,(int)y1_db);
			      fprintf(fp_o ,"PD%d,%d,%d,%d;",(int)x1_db,(int)y1_db,(int)x2_db,(int)y2_db);
			      goto endplot ;
			     }

			  b = (y2_db - y1_db)/(x2_db - x1_db) ;
			  a = y1_db - (b * x1_db) ;

			  x_bot   = (y_min_plot - a) / b ;
			  x_top   = (y_max_plot - a) / b ;
			  y_left  = a + (b * x_min_plot) ;
			  y_right = a + (b * x_max_plot) ;

			  if ((x_bot>x_min_plot && x_bot<x_max_plot) &&
			     ((x_bot>x1_db && x_bot<x2_db) || (x_bot>x2_db && x_bot<x1_db)))
			     {
			      if (SP_flag == 0) { fprintf(fp_o,"\nSP%d;",color); SP_flag =1; }
			      fprintf(fp_o ,"\nPU,%d,%d;",(int)x1_db,(int)y1_db);
			      fprintf(fp_o ,"PD%d,%d,%d,%d;",(int)x1_db,(int)y1_db,(int)x_bot,(int)y_min_plot);
			     }
		     else if ((x_top>x_min_plot && x_top<x_max_plot) &&
			     ((x_top>x1_db && x_top<x2_db) || (x_top>x2_db && x_top<x1_db)))
			     {
			      if (SP_flag == 0) { fprintf(fp_o,"\nSP%d;",color); SP_flag =1; }
			      fprintf(fp_o ,"\nPU,%d,%d;",(int)x1_db,(int)y1_db);
			      fprintf(fp_o ,"PD%d,%d,%d,%d;",(int)x1_db,(int)y1_db,(int)x_top,(int)y_max_plot);
			     }
		     else if ((y_left>y_min_plot && y_left<y_max_plot) &&
			     ((y_left>y1_db && y_left<y2_db) || (y_left>y2_db && y_left<y1_db)))
			     {
			      if (SP_flag == 0) { fprintf(fp_o,"\nSP%d;",color); SP_flag =1; }
			      fprintf(fp_o ,"\nPU,%d,%d;",(int)x1_db,(int)y1_db);
			      fprintf(fp_o ,"PD%d,%d,%d,%d;",(int)x1_db,(int)y1_db,(int)x_min_plot,(int)y_left);
			     }
		     else if ((y_right>y_min_plot && y_right<y_max_plot) &&
			     ((y_right>y1_db && y_right<y2_db) || (y_right>y2_db && y_right<y1_db)))
			     {
			      if (SP_flag == 0) { fprintf(fp_o,"\nSP%d;",color); SP_flag =1; }
			      fprintf(fp_o ,"\nPU,%d,%d;",(int)x1_db,(int)y1_db);
			      fprintf(fp_o ,"PD%d,%d,%d,%d;",(int)x1_db,(int)y1_db,(int)x_max_plot,(int)y_right);
			     }
			 }

		 else if ( x2_db>=x_min_plot && x2_db<=x_max_plot && y2_db>=y_min_plot && y2_db<=y_max_plot )
			 {

			  if ( x1_db == x2_db )   /* VL Segment */
			     {
			      if ( y1_db > y2_db )
				 {
				  y1_db = y_max_plot ;
				 }
			       else
				 {
				  y1_db = y_min_plot ;
				 }
			      if (SP_flag == 0) { fprintf(fp_o,"\nSP%d;",color); SP_flag =1; }
			      fprintf(fp_o ,"\nPU,%d,%d;",(int)x1_db,(int)y1_db);
			      fprintf(fp_o ,"PD%d,%d,%d,%d;",(int)x1_db,(int)y1_db,(int)x2_db,(int)y2_db);
			      goto endplot ;
			     }

			  if ( y1_db == y2_db )    /* HZ Segment */
			     {
			      if ( x1_db > x2_db )
				 {
				  x1_db = x_max_plot ;
				 }
			       else
				 {
				  x1_db = x_min_plot ;
				 }
			      if (SP_flag == 0) { fprintf(fp_o,"\nSP%d;",color); SP_flag =1; }
			      fprintf(fp_o ,"\nPU,%d,%d;",(int)x1_db,(int)y1_db);
			      fprintf(fp_o ,"PD%d,%d,%d,%d;",(int)x1_db,(int)y1_db,(int)x2_db,(int)y2_db);
			      goto endplot ;
			     }

			  b = (y2_db - y1_db)/(x2_db - x1_db) ;
			  a = y1_db - (b * x1_db) ;

			  x_bot   = (y_min_plot - a) / b ;
			  x_top   = (y_max_plot - a) / b ;
			  y_left  = a + (b * x_min_plot) ;
			  y_right = a + (b * x_max_plot) ;

			  if ((x_bot>x_min_plot && x_bot<x_max_plot) &&
			     ((x_bot>x1_db && x_bot<x2_db) || (x_bot>x2_db && x_bot<x1_db)))
			     {
			      if (SP_flag == 0) { fprintf(fp_o,"\nSP%d;",color); SP_flag =1; }
			      fprintf(fp_o ,"\nPU,%d,%d;",(int)x2_db,(int)y2_db);
			      fprintf(fp_o ,"PD%d,%d,%d,%d;",(int)x2_db,(int)y2_db,(int)x_bot,(int)y_min_plot);
			     }
		     else if ((x_top>x_min_plot && x_top<x_max_plot) &&
			     ((x_top>x1_db && x_top<x2_db) || (x_top>x2_db && x_top<x1_db)))
			     {
			      if (SP_flag == 0) { fprintf(fp_o,"\nSP%d;",color); SP_flag =1; }
			      fprintf(fp_o ,"\nPU,%d,%d;",(int)x2_db,(int)y2_db);
			      fprintf(fp_o ,"PD%d,%d,%d,%d;",(int)x2_db,(int)y2_db,(int)x_top,(int)y_max_plot);
			     }
		     else if ((y_left>y_min_plot && y_left<y_max_plot) &&
			     ((y_left>y1_db && y_left<y2_db) || (y_left>y2_db && y_left<y1_db)))
			     {
			      if (SP_flag == 0) { fprintf(fp_o,"\nSP%d;",color); SP_flag =1; }
			      fprintf(fp_o ,"\nPU,%d,%d;",(int)x2_db,(int)y2_db);
			      fprintf(fp_o ,"PD%d,%d,%d,%d;",(int)x2_db,(int)y2_db,(int)x_min_plot,(int)y_left);
			     }
		     else if ((y_right>y_min_plot && y_right<y_max_plot) &&
			     ((y_right>y1_db && y_right<y2_db) || (y_right>y2_db && y_right<y1_db)))
			     {
			      if (SP_flag == 0) { fprintf(fp_o,"\nSP%d;",color); SP_flag =1; }
			      fprintf(fp_o ,"\nPU,%d,%d;",(int)x2_db,(int)y2_db);
			      fprintf(fp_o ,"PD%d,%d,%d,%d;",(int)x2_db,(int)y2_db,(int)x_max_plot,(int)y_right);
			     }
			 }

		     else
			 {
			  b = (y2_db - y1_db)/(x2_db - x1_db) ;
			  a = y1_db - (b * x1_db) ;

			  /* --------------------- CASE I ----------------------- */
			  if ((y1_db < y_min_plot && y2_db > y_max_plot) || (y2_db < y_min_plot && y1_db > y_max_plot))
			     {
			      if ( x2_db == x1_db )  /* VL Segment */
				 {
				  x1_clip = x1_db ;  y1_clip = y_min_plot ;
				  x2_clip = x2_db ;  y2_clip = y_max_plot ;

				  if (SP_flag == 0) { fprintf(fp_o,"\nSP%d;",color); SP_flag =1; }
				  fprintf(fp_o ,"\nPU,%d,%d;",(int)x1_clip,(int)y1_clip);
				  fprintf(fp_o ,"PD%d,%d,%d,%d;",(int)x1_clip,(int)y1_clip,(int)x2_clip,(int)y2_clip);
				  goto endplot ;
				 }

			      x_bot = (y_min_plot - a) / b ;
			      x_top = (y_max_plot - a) / b ;

			      if (x_bot > x_min_plot && x_bot < x_max_plot)
				 {
				  x1_clip = x_bot ;
				  y1_clip = y_min_plot ;
				 }
			      else
				 { goto next2 ; }

			      if (x_top  > x_min_plot && x_top  < x_max_plot)
				 {
				  x2_clip = x_top ;
				  y2_clip = y_max_plot ;

				  if (SP_flag == 0) { fprintf(fp_o,"\nSP%d;",color); SP_flag =1; }
				  fprintf(fp_o ,"\nPU,%d,%d;",(int)x1_clip,(int)y1_clip);
				  fprintf(fp_o ,"PD%d,%d,%d,%d;",(int)x1_clip,(int)y1_clip,(int)x2_clip,(int)y2_clip);
				  goto endplot ;
				 }
			     }
			  next2:
			  /* --------------------- CASE II ---------------------- */
			  if ((x1_db < x_min_plot && x2_db > x_max_plot) || (x2_db < x_min_plot && x1_db > x_max_plot))
			     {
			      y_left  = a + (b * x_min_plot) ;
			      y_right = a + (b * x_max_plot) ;

			      if (y_left > y_min_plot && y_left < y_max_plot)
				 {
				  x1_clip = x_min_plot  ;
				  y1_clip = y_left ;
				 }
			      else
				 { goto next3 ; }

			      if (y_right > y_min_plot && y_right < y_max_plot)
				 {
				  x2_clip = x_max_plot   ;
				  y2_clip = y_right ;

				  if (SP_flag == 0) { fprintf(fp_o,"\nSP%d;",color); SP_flag =1; }
				  fprintf(fp_o ,"\nPU,%d,%d;",(int)x1_clip,(int)y1_clip);
				  fprintf(fp_o ,"PD%d,%d,%d,%d;",(int)x1_clip,(int)y1_clip,(int)x2_clip,(int)y2_clip);
				  goto endplot ;
				 }
			     }
			  next3:
			  /* --------------------- CASE III --------------------- */
			  if ((y1_db < y_min_plot && x2_db > x_max_plot) || (y2_db < y_min_plot && x1_db > x_max_plot))
			     {
			      x_bot   = (y_min_plot - a) / b ;
			      y_right = a + (b * x_max_plot) ;

			      if (x_bot > x_min_plot && x_bot < x_max_plot)
				 {
				  x1_clip = x_bot ;
				  y1_clip = y_min_plot ;
				 }
			      else
				 { goto next4 ; }

			      if (y_right > y_min_plot && y_right < y_max_plot)
				 {
				  x2_clip = x_max_plot   ;
				  y2_clip = y_right ;

				  if (SP_flag == 0) { fprintf(fp_o,"\nSP%d;",color); SP_flag =1; }
				  fprintf(fp_o ,"\nPU,%d,%d;",(int)x1_clip,(int)y1_clip);
				  fprintf(fp_o ,"PD%d,%d,%d,%d;",(int)x1_clip,(int)y1_clip,(int)x2_clip,(int)y2_clip);
				  goto endplot ;
				 }
			     }
			  next4:
			  /* --------------------- CASE IV ---------------------- */
			  if ((y1_db < y_min_plot && x2_db < x_min_plot) || (y2_db < y_min_plot && x1_db < x_min_plot))
			     {
			      x_bot  = (y_min_plot - a) / b ;
			      y_left = a + (b * x_min_plot) ;

			      if (x_bot > x_min_plot && x_bot < x_max_plot)
				 {
				  x1_clip = x_bot ;
				  y1_clip = y_min_plot ;
				 }
			      else
				 { goto next5 ; }

			      if (y_left > y_min_plot && y_left < y_max_plot)
				 {
				  x2_clip = x_min_plot   ;
				  y2_clip = y_left  ;

				  if (SP_flag == 0) { fprintf(fp_o,"\nSP%d;",color); SP_flag =1; }
				  fprintf(fp_o ,"\nPU,%d,%d;",(int)x1_clip,(int)y1_clip);
				  fprintf(fp_o ,"PD%d,%d,%d,%d;",(int)x1_clip,(int)y1_clip,(int)x2_clip,(int)y2_clip);
				  goto endplot ;
				 }
			     }
			  next5:
			  /* --------------------- CASE V ----------------------- */
			  if ((y2_db > y_max_plot && x1_db > x_max_plot) || (y1_db > y_max_plot && x2_db > x_max_plot))
			     {
			      x_top   = (y_max_plot - a) / b ;
			      y_right = a + (b * x_max_plot) ;

			      if (x_top  > x_min_plot && x_top  < x_max_plot)
				 {
				  x1_clip = x_top ;
				  y1_clip = y_max_plot ;
				 }
			      else
				 { goto next6 ; }

			      if (y_right > y_min_plot && y_right < y_max_plot)
				 {
				  x2_clip = x_max_plot   ;
				  y2_clip = y_right ;

				  if (SP_flag == 0) { fprintf(fp_o,"\nSP%d;",color); SP_flag =1; }
				  fprintf(fp_o ,"\nPU,%d,%d;",(int)x1_clip,(int)y1_clip);
				  fprintf(fp_o ,"PD%d,%d,%d,%d;",(int)x1_clip,(int)y1_clip,(int)x2_clip,(int)y2_clip);
				  goto endplot ;
				 }
			     }
			  next6:
			  /* --------------------- CASE VI ---------------------- */
			  if ((y2_db > y_max_plot && x1_db < x_min_plot) || (y1_db > y_max_plot && x2_db < x_min_plot))
			     {
			      x_top  = (y_max_plot - a) / b ;
			      y_left = a + (b * x_min_plot) ;

			      if (x_top  > x_min_plot && x_top  < x_max_plot)
				 {
				  x1_clip = x_top ;
				  y1_clip = y_max_plot ;
				 }
			      else
				 { goto endplot ; }

			      if (y_left > y_min_plot && y_left < y_max_plot)
				 {
				  x2_clip = x_min_plot   ;
				  y2_clip = y_left  ;

				  if (SP_flag == 0) { fprintf(fp_o,"\nSP%d;",color); SP_flag =1; }
				  fprintf(fp_o ,"\nPU,%d,%d;",(int)x1_clip,(int)y1_clip);
				  fprintf(fp_o ,"PD%d,%d,%d,%d;",(int)x1_clip,(int)y1_clip,(int)x2_clip,(int)y2_clip);
				  goto endplot ;
				 }
			     }

			  }

		       endplot:

		       x1_db = x[feat[i].xy+ii] ;
		       y1_db = y[feat[i].xy+ii] ;
		       break ;
		 }
	    }
	}
	break ;


       default:   /*---------------- Do nothing ----------------------*/
	 break ;
      }
     }

 fprintf(fp_o ,"\nPU;");
 fprintf(fp_o ,"\nSP0;");

 fprintf(fp_o ,"\n");
 fputc  (ESC,fp_o );
 fprintf(fp_o ,"%1A");

 fclose(fp_o);

 strcpy (cmd ,"xterm -e lpr -P ");
 strcat (cmd , queue_name       );
 strcat (cmd ," geoinfo.gl"     );
 system (cmd);

 // normal_cursor();
}
/*------------------------------------------------------------------------*/
/*                          plot_using_temp()                             */
/*------------------------------------------------------------------------*/
void plot_using_temp()
{
 int       argc = 1   ;
 char      **argv     ;
 XmString  xstr       ;
 Arg       args[20]   ;
 int       i , n      ;
 char      value[50]  ;
 char      value1[50] ;



 /*------ Make sure XtToolkitInitialize is only called once -----------*/

 if (ToolkitInitialized == 0)
    {
     XtToolkitInitialize() ;
     ToolkitInitialized = 1;
    }

 /*------ create the application context ------------------------------*/

 Plot_context = XtCreateApplicationContext();


 /*---------------------  Open Display --------------------------------*/

 PlotDisplay = XtOpenDisplay(Plot_context,NULL,NULL,"PlotShell",NULL,0,&argc,argv);

 if (PlotDisplay == NULL)
    {
     fprintf(stderr,"Plot : Can not open display\n");
     return ;
    }


 /*-------------------  Application Shell --------------------*/
 n = 0;
 XtSetArg(args[n],XmNwidth        ,  400);n++;
 XtSetArg(args[n],XmNheight       ,  350);n++;

 PlotShell=XtAppCreateShell(NULL,"PlotShell",applicationShellWidgetClass,PlotDisplay,args,n);

 /*----------------------- Form ------------------------------*/
 sprintf (value,"Plotting");
 xstr = XmStringCreate(value,CS);
 n=0;
 XtSetArg(args[n],XmNdialogTitle  , xstr);n++;
 XtSetArg(args[n], XmNx           ,    0);n++;
 XtSetArg(args[n], XmNy           ,    0);n++;
 XtSetArg(args[n], XmNwidth       ,  400);n++;
 XtSetArg(args[n], XmNheight      ,  350);n++;

 PlotForm = XmCreateForm(PlotShell,"PlotForm", args,n);
 XtManageChild(PlotForm);

 /*------------------------- OK button ------------------------*/
 xstr = XmStringCreate("OK",CS);
 n=0;
 XtSetArg(args[n] , XmNlabelString , xstr);n++;
 XtSetArg(args[n] , XmNx           ,   70);n++;
 XtSetArg(args[n] , XmNy           ,  300);n++;
 XtSetArg(args[n] , XmNwidth       ,   80);n++;
 XtSetArg(args[n] , XmNheight      ,   30);n++;

 Plot_ok_button = XmCreatePushButton(PlotForm,"Button",args,n);
 XtAddCallback(Plot_ok_button,XmNactivateCallback,okPlotCB,PlotForm);
 XtManageChild(Plot_ok_button);


 /*---------------------- Cancel button ----------------------*/
 xstr = XmStringCreate("Cancel",CS);
 n=0;
 XtSetArg(args[n] , XmNlabelString , xstr);n++;
 XtSetArg(args[n] , XmNx           ,  230);n++;
 XtSetArg(args[n] , XmNy           ,  300);n++;
 XtSetArg(args[n] , XmNwidth       ,   80);n++;
 XtSetArg(args[n] , XmNheight      ,   30);n++;

 Plot_cancel_button = XmCreatePushButton(PlotForm,"Button",args,n);
 XtAddCallback(Plot_cancel_button,XmNactivateCallback,cancelPlotCB,PlotForm);
 XtManageChild(Plot_cancel_button);


 /*---------------------- Label[0]     ----------------------*/
 xstr = XmStringCreate("Plot Scale ",CS);
 n=0;
 XtSetArg(args[n] , XmNlabelString , xstr);n++;
 XtSetArg(args[n] , XmNx           ,   10);n++;
 XtSetArg(args[n] , XmNy           ,   50);n++;
 XtSetArg(args[n] , XmNwidth       ,  100);n++;
 XtSetArg(args[n] , XmNheight      ,   30);n++;

 Label[0] = XmCreateLabel(PlotForm,"Label0",args,n);
 XtManageChild(Label[0]);

 /*---------------------- Field[0]     ----------------------*/
 n=0;
 XtSetArg(args[n] , XmNx           ,       120);n++;
 XtSetArg(args[n] , XmNy           ,        50);n++;
 XtSetArg(args[n] , XmNwidth       ,       150);n++;
 XtSetArg(args[n] , XmNheight      ,        30);n++;
 XtSetArg(args[n] , XmNbackground  ,gray.pixel);n++;
 XtSetArg(args[n] , XmNvalue       ,plot_scale);n++;

 Field[0] = XmCreateTextField(PlotForm,"Field0",args,n);
 XtManageChild(Field[0]);

 /*---------------------- Label[1]     ----------------------*/
 xstr = XmStringCreate("Plot width (cm)",CS);
 n=0;
 XtSetArg(args[n] , XmNlabelString , xstr);n++;
 XtSetArg(args[n] , XmNx           ,   10);n++;
 XtSetArg(args[n] , XmNy           ,  100);n++;
 XtSetArg(args[n] , XmNwidth       ,  100);n++;
 XtSetArg(args[n] , XmNheight      ,   30);n++;

 Label[1] = XmCreateLabel(PlotForm,"Label1",args,n);
 XtManageChild(Label[1]);

 /*---------------------- Field[1]     ----------------------*/
 n=0;
 XtSetArg(args[n] , XmNx           ,       120);n++;
 XtSetArg(args[n] , XmNy           ,       100);n++;
 XtSetArg(args[n] , XmNwidth       ,       150);n++;
 XtSetArg(args[n] , XmNheight      ,        30);n++;
 XtSetArg(args[n] , XmNbackground  ,gray.pixel);n++;
 XtSetArg(args[n] , XmNvalue       ,plot_width);n++;

 Field[1] = XmCreateTextField(PlotForm,"Field1",args,n);
 XtManageChild(Field[1]);


 /*---------------------- Label[2]     ----------------------*/
 xstr = XmStringCreate("Plot hight (cm)",CS);
 n=0;
 XtSetArg(args[n] , XmNlabelString , xstr);n++;
 XtSetArg(args[n] , XmNx           ,   10);n++;
 XtSetArg(args[n] , XmNy           ,  150);n++;
 XtSetArg(args[n] , XmNwidth       ,  100);n++;
 XtSetArg(args[n] , XmNheight      ,   30);n++;

 Label[2] = XmCreateLabel(PlotForm,"Label2",args,n);
 XtManageChild(Label[2]);

 /*---------------------- Field[2]     ----------------------*/
 /* sprintf (value1,"%d",kva1); */
 n=0;
 XtSetArg(args[n] , XmNx           ,       120);n++;
 XtSetArg(args[n] , XmNy           ,       150);n++;
 XtSetArg(args[n] , XmNwidth       ,       150);n++;
 XtSetArg(args[n] , XmNheight      ,        30);n++;
 XtSetArg(args[n] , XmNbackground  ,gray.pixel);n++;
 XtSetArg(args[n] , XmNvalue       ,plot_hight);n++;

 Field[2] = XmCreateTextField(PlotForm,"Field2",args,n);
 XtManageChild(Field[2]);

 /*---------------------- Label[3]     ----------------------*/
 xstr = XmStringCreate("Plot x-orign",CS);
 n=0;
 XtSetArg(args[n] , XmNlabelString , xstr);n++;
 XtSetArg(args[n] , XmNx           ,   10);n++;
 XtSetArg(args[n] , XmNy           ,  200);n++;
 XtSetArg(args[n] , XmNwidth       ,  100);n++;
 XtSetArg(args[n] , XmNheight      ,   30);n++;

 Label[3] = XmCreateLabel(PlotForm,"Label3",args,n);
 XtManageChild(Label[3]);

 /*---------------------- Field[3]     ----------------------*/
 n=0;
 XtSetArg(args[n] , XmNx           ,      120);n++;
 XtSetArg(args[n] , XmNy           ,      200);n++;
 XtSetArg(args[n] , XmNwidth       ,      150);n++;
 XtSetArg(args[n] , XmNheight      ,       30);n++;
 XtSetArg(args[n] , XmNbackground  ,gray.pixel);n++;
 XtSetArg(args[n] , XmNvalue       ,x_min_plt);n++;

 Field[3] = XmCreateTextField(PlotForm,"Field3",args,n);
 XtManageChild(Field[3]);


 /*---------------------- Label[4]     ----------------------*/
 xstr = XmStringCreate("Plot y_origin",CS);
 n=0;
 XtSetArg(args[n] , XmNlabelString , xstr);n++;
 XtSetArg(args[n] , XmNx           ,   10);n++;
 XtSetArg(args[n] , XmNy           ,  250);n++;
 XtSetArg(args[n] , XmNwidth       ,  100);n++;
 XtSetArg(args[n] , XmNheight      ,   30);n++;

 Label[4] = XmCreateLabel(PlotForm,"Label4",args,n);
 XtManageChild(Label[4]);

 /*---------------------- Field[4]     ----------------------*/
 n=0;
 XtSetArg(args[n] , XmNx           ,       120);n++;
 XtSetArg(args[n] , XmNy           ,       250);n++;
 XtSetArg(args[n] , XmNwidth       ,       150);n++;
 XtSetArg(args[n] , XmNheight      ,        30);n++;
 XtSetArg(args[n] , XmNbackground  ,gray.pixel);n++;
 XtSetArg(args[n] , XmNvalue       ,y_min_plt);n++;

 Field[4] = XmCreateTextField(PlotForm,"Field4",args,n);
 XtManageChild(Field[4]);


 /*------------------- Inialize X -----------------------------*/

  XtRealizeWidget(PlotShell);      /* display the interface */


 /* check if any events pending..this will force display of the dialog */
  while (XtAppPending(Plot_context))
	{
	 XtAppNextEvent(Plot_context, &PlotEvent);
	 XtDispatchEvent(&PlotEvent);
	}

  done = 0 ;

  /***********  running from the regular event loop  *************/

  while (done == 0)  /* close button callback sets done to 1 */
	{
	 XtAppNextEvent(Plot_context, &PlotEvent);
	 XtDispatchEvent( &PlotEvent);
	}
  XtUnrealizeWidget(PlotShell);
  XtDestroyWidget(PlotShell);
  XSync(PlotDisplay, False);

}

/*------------------------CALL BACKS ------------------------------*/
/*------------------------CALL BACKS ------------------------------*/
/*------------------------CALL BACKS ------------------------------*/
/*------------------------CALL BACKS ------------------------------*/


/*----------------------- cancelPlotCB() --------------------------*/
void cancelPlotCB()
{
   done = 1 ;
}


/*------------------------- okPlotCB() ----------------------------*/
void okPlotCB(Widget w,caddr_t client_data,ANYCBS *call_data)
{
 Arg       args[20]   ;
 char     *str;
 char     command[50];

 char      value[50]  ;


/*
 XmStringGetLtoR(call_data->value ,CS ,&str);
 strcpy(InputFile,str );
*/

 XtSetArg(args[0],XmNvalue,command);
 XtGetValues(Field[0],args,1);

 printf("\n Feature Number = %10s \n",XmTextGetString(Field[0]));
 printf("\n Feature code   = %10s \n",XmTextGetString(Field[1]));


 strcpy (value ,XmTextGetString(Field[0]));
 sscanf (value ,"%d",&plot_scale);

 strcpy (value ,XmTextGetString(Field[1]));
 sscanf (value ,"%d",&plot_width);

 strcpy (value ,XmTextGetString(Field[2]));
 sscanf (value ,"%d",&plot_hight);

 strcpy (value ,XmTextGetString(Field[3]));
 sscanf (value ,"%d",&x_min_plt);

 strcpy (value ,XmTextGetString(Field[4]));
 sscanf (value ,"%d",&y_min_plt);


 printf("\n Plot scale   = %s",XmTextGetString(Field[0]));
 printf("\n plot width   = %s",XmTextGetString(Field[1]));
 printf("\n plot hight   = %s",XmTextGetString(Field[2]));
 printf("\n plot x-orign = %s",XmTextGetString(Field[3]));
 printf("\n plot y-orign = %s",XmTextGetString(Field[4]));

 x_max_plt = x_min_plt + plot_width * plot_scale ;
 y_max_plt = y_min_plt + plot_hight * plot_scale ;



 fp_o = fopen ("geoinfo.gl","wt");
 if  ( fp_o == NULL )
     {
      printf ("\nERROR : Can't open PLOT file  !");
      return ;
     }

 printf ("\nINFO  : Processing PLOT file ..");

 x_min1 = x_min_plt - SYMBCLIPBUFFER ;
 y_min1 = y_min_plt - SYMBCLIPBUFFER ;
 x_max1 = x_max_plt + SYMBCLIPBUFFER ;
 y_max1 = y_max_plt + SYMBCLIPBUFFER ;

 x_min2 = x_min_plt - LINECLIPBUFFER ;
 y_min2 = y_min_plt - LINECLIPBUFFER ;
 x_max2 = x_max_plt + LINECLIPBUFFER ;
 y_max2 = y_max_plt + LINECLIPBUFFER ;

 x_diff = x_max_plt - x_min_plt ;
 switch (DB_UNIT)
      {
       case MM: scale = ( x_diff * .1  ) / SCREEN_CM ; break ;
       case CM: scale = ( x_diff * 1   ) / SCREEN_CM ; break ;
       case DM: scale = ( x_diff * 10  ) / SCREEN_CM ; break ;
       case  M: scale = ( x_diff * 100 ) / SCREEN_CM ; break ;
       case KM: scale = ( x_diff * 1000) / SCREEN_CM ; break ;
       default:
		scale = ( x_diff * 100 ) / SCREEN_CM ;
		printf("\nERROR : Data Base Unit not Defined");
		break ;
      }


      if ( scale > 0     &&  scale <= 2500  ) sc_range = 0 ;
 else if ( scale > 2500  &&  scale <= 5000  ) sc_range = 1 ;
 else if ( scale > 5000  &&  scale <= 10000 ) sc_range = 2 ;
 else if ( scale > 10000 &&  scale <= 25000 ) sc_range = 3 ;
 else if ( scale > 25000                    ) sc_range = 4 ;


 fprintf(fp_o ,"IN;");
 fprintf(fp_o ,"\nSC%d,%d,%d,%d,1;",(int)x_min_plt,(int)x_max_plt,(int)y_min_plt,(int)y_max_plt);
 fprintf(fp_o ,"\nLT;");
 fprintf(fp_o ,"\nSP7;");
 fprintf(fp_o ,"\nPA0,0;");
 fprintf(fp_o ,"\nPU%d,%d;",(int)x_min_plt,(int)y_min_plt);
 fprintf(fp_o ,"PD%d,%d,%d,%d,%d,%d,%d,%d,%d,%d;",
		 (int)x_min_plt,(int)y_min_plt,
		 (int)x_max_plt,(int)y_min_plt,
		 (int)x_max_plt,(int)y_max_plt,
		 (int)x_min_plt,(int)y_max_plt,
		 (int)x_min_plt,(int)y_min_plt  );

/* Grid PLOT  48,103  */

x1_db = x_min_plt ;
for ( i=1 ; i<=23 ; i++ )
    {
     x1_db = x1_db + (x_max_plt - x_min_plt)/24 ;
     fprintf(fp_o ,"\nPU%d,%d;",(int)x_min_plt,(int)y_min_plt);
     fprintf(fp_o ,"PD%d,%d,%d,%d;",(int)x1_db,(int)y_min_plt,(int)x1_db,(int)y_max_plt);
    }

y1_db = y_min_plt ;
for ( i=1 ; i<=55  ; i++ )
    {
     y1_db = y1_db + (y_max_plt - y_min_plt)/56   ;
     fprintf(fp_o ,"\nPU%d,%d;",(int)x_min_plt,(int)y_min_plt);
     fprintf(fp_o ,"PD%d,%d,%d,%d;",(int)x_min_plt,(int)y1_db,(int)x_max_plt,(int)y1_db);
    }





for ( i=1 ; i<=feat_count ; i++ )
{
 printf ("\n feat_code  %s",feat[i].code );
 printf ("\n feat_color %d",feat[i].color);

 if      (feat[i].color == blue.pixel   )  color = 1  ;
 else if (feat[i].color == red.pixel    )  color = 2  ;
 else if (feat[i].color == pink.pixel   )  color = 3  ;
 else if (feat[i].color == green.pixel  )  color = 4  ;
 else if (feat[i].color == cyan.pixel   )  color = 5  ;
 else if (feat[i].color == yellow.pixel )  color = 6  ;
 else if (feat[i].color == white.pixel  )  color = 7  ;
 else if (feat[i].color == black.pixel  )  color = 8  ;
 else if (feat[i].color == gray.pixel   )  color = 9  ;
 else if (feat[i].color == wheat.pixel  )  color = 10 ;
 else if (feat[i].color == brown.pixel  )  color = 11 ;
 else if (feat[i].color == orange.pixel )  color = 12 ;
 else     color = 7  ;

 switch (feat[i].type)
  {

   case 1:    /*---------- Plot type one -------------- */

    x_base = feat[i].xbase ;
    y_base = feat[i].ybase ;

    /* BASE POINT CLIPPING & MIN SYMBOL SIZE = 1 */
    if ( (feat[i].displayed[0] == 'Y'         ) &&
	 (feat[i].scale_range[sc_range] == 'Y') &&
	 ((feat[i].symb_size/ONE_PIXEL) >= 1  ) &&
	 (x_base >= x_min1)&&(x_base <= x_max1) &&
	 (y_base >= y_min1)&&(y_base <= y_max1) )
       {
	plot_symb(feat[i].symb_num,x_base,y_base,color,feat[i].symb_size,feat[i].symb_angle);
       }

    break ;

   case 2:    /*-------------- Plot type two --------------------*/

    x_base = feat[i].xbase                    ;
    y_base = feat[i].ybase                    ;
    x_end  = x[feat[i].xy + feat[i].xy_count] ;
    y_end  = x[feat[i].xy + feat[i].xy_count] ;

    /* END POINTS CLIPPING */
    if ( (feat[i].displayed[0] == 'Y'         ) &&
	 (feat[i].scale_range[sc_range] == 'Y') &&
	 (((x_base>x_min2)&&(x_base<x_max2)&&(y_base>y_min2)&&(y_base<y_max2)) ||
	 ((x_end>x_min2)&&(x_end<x_max2)&&(y_end>y_min2)&&(y_end<y_max2))) )
    {

    for ( ii=0; ii<=feat[i].xy_count; ii++)
	{
	 switch (ii)
	     {
	      case 0:
		   SP_flag = 0  ;
		   x1_db = feat[i].xbase ;
		   y1_db = feat[i].ybase ;
		   /* fprintf(fp_o ,"\nSP%d;",color); */
		   break ;

	      default:
		   x2_db = x[feat[i].xy+ii] ;
		   y2_db = y[feat[i].xy+ii] ;

		  if (( x1_db>x_min_plt && x1_db<x_max_plt && y1_db>y_min_plt && y1_db<y_max_plt ) &&
		      ( x2_db>x_min_plt && x2_db<x_max_plt && y2_db>y_min_plt && y2_db<y_max_plt ))
		     {
		      if (SP_flag == 0) { fprintf(fp_o,"\nSP%d;",color); SP_flag =1; }
		      fprintf(fp_o ,"\nPU,%d,%d;",(int)x1_db,(int)y1_db);
		      fprintf(fp_o ,"PD%d,%d,%d,%d;",(int)x1_db,(int)y1_db,(int)x2_db,(int)y2_db);
		     }

	     else if ( x1_db>x_min_plt && x1_db<x_max_plt && y1_db>y_min_plt && y1_db<y_max_plt )
		     {
		      b = (y2_db - y1_db)/(x2_db - x1_db) ;
		      a = y1_db - (b * x1_db) ;

		      x_bot   = (y_min_plt - a) / b ;
		      x_top   = (y_max_plt - a) / b ;
		      y_left  = a + (b * x_min_plt) ;
		      y_right = a + (b * x_max_plt) ;

		      if ((x_bot>x_min_plt && x_bot<x_max_plt) &&
			 ((x_bot>x1_db && x_bot<x2_db) || (x_bot>x2_db && x_bot<x1_db)))
			 {
			  if (SP_flag == 0) { fprintf(fp_o,"\nSP%d;",color); SP_flag =1; }
			  fprintf(fp_o ,"\nPU,%d,%d;",(int)x1_db,(int)y1_db);
			  fprintf(fp_o ,"PD%d,%d,%d,%d;",(int)x1_db,(int)y1_db,(int)x_bot,(int)y_min_plt);
			 }
		 else if ((x_top>x_min_plt && x_top<x_max_plt) &&
			 ((x_top>x1_db && x_top<x2_db) || (x_top>x2_db && x_top<x1_db)))
			 {
			  if (SP_flag == 0) { fprintf(fp_o,"\nSP%d;",color); SP_flag =1; }
			  fprintf(fp_o ,"\nPU,%d,%d;",(int)x1_db,(int)y1_db);
			  fprintf(fp_o ,"PD%d,%d,%d,%d;",(int)x1_db,(int)y1_db,(int)x_top,(int)y_max_plt);
			 }
		 else if ((y_left>y_min_plt && y_left<y_max_plt) &&
			 ((y_left>y1_db && y_left<y2_db) || (y_left>y2_db && y_left<y1_db)))
			 {
			  if (SP_flag == 0) { fprintf(fp_o,"\nSP%d;",color); SP_flag =1; }
			  fprintf(fp_o ,"\nPU,%d,%d;",(int)x1_db,(int)y1_db);
			  fprintf(fp_o ,"PD%d,%d,%d,%d;",(int)x1_db,(int)y1_db,(int)x_min_plt,(int)y_left);
			 }
		 else if ((y_right>y_min_plt && y_right<y_max_plt) &&
			 ((y_right>y1_db && y_right<y2_db) || (y_right>y2_db && y_right<y1_db)))
			 {
			  if (SP_flag == 0) { fprintf(fp_o,"\nSP%d;",color); SP_flag =1; }
			  fprintf(fp_o ,"\nPU,%d,%d;",(int)x1_db,(int)y1_db);
			  fprintf(fp_o ,"PD%d,%d,%d,%d;",(int)x1_db,(int)y1_db,(int)x_max_plt,(int)y_right);
			 }
		     }

	     else if ( x2_db>x_min_plt && x2_db<x_max_plt && y2_db>y_min_plt && y2_db<y_max_plt )
		     {
		      b = (y2_db - y1_db)/(x2_db - x1_db) ;
		      a = y1_db - (b * x1_db) ;

		      x_bot   = (y_min_plt - a) / b ;
		      x_top   = (y_max_plt - a) / b ;
		      y_left  = a + (b * x_min_plt) ;
		      y_right = a + (b * x_max_plt) ;

		      if ((x_bot>x_min_plt && x_bot<x_max_plt) &&
			 ((x_bot>x1_db && x_bot<x2_db) || (x_bot>x2_db && x_bot<x1_db)))
			 {
			  if (SP_flag == 0) { fprintf(fp_o,"\nSP%d;",color); SP_flag =1; }
			  fprintf(fp_o ,"\nPU,%d,%d;",(int)x2_db,(int)y2_db);
			  fprintf(fp_o ,"PD%d,%d,%d,%d;",(int)x2_db,(int)y2_db,(int)x_bot,(int)y_min_plt);
			 }
		 else if ((x_top>x_min_plt && x_top<x_max_plt) &&
			 ((x_top>x1_db && x_top<x2_db) || (x_top>x2_db && x_top<x1_db)))
			 {
			  if (SP_flag == 0) { fprintf(fp_o,"\nSP%d;",color); SP_flag =1; }
			  fprintf(fp_o ,"\nPU,%d,%d;",(int)x2_db,(int)y2_db);
			  fprintf(fp_o ,"PD%d,%d,%d,%d;",(int)x2_db,(int)y2_db,(int)x_top,(int)y_max_plt);
			 }
		 else if ((y_left>y_min_plt && y_left<y_max_plt) &&
			 ((y_left>y1_db && y_left<y2_db) || (y_left>y2_db && y_left<y1_db)))
			 {
			  if (SP_flag == 0) { fprintf(fp_o,"\nSP%d;",color); SP_flag =1; }
			  fprintf(fp_o ,"\nPU,%d,%d;",(int)x2_db,(int)y2_db);
			  fprintf(fp_o ,"PD%d,%d,%d,%d;",(int)x2_db,(int)y2_db,(int)x_min_plt,(int)y_left);
			 }
		 else if ((y_right>y_min_plt && y_right<y_max_plt) &&
			 ((y_right>y1_db && y_right<y2_db) || (y_right>y2_db && y_right<y1_db)))
			 {
			  if (SP_flag == 0) { fprintf(fp_o,"\nSP%d;",color); SP_flag =1; }
			  fprintf(fp_o ,"\nPU,%d,%d;",(int)x2_db,(int)y2_db);
			  fprintf(fp_o ,"PD%d,%d,%d,%d;",(int)x2_db,(int)y2_db,(int)x_max_plt,(int)y_right);
			 }
		     }

		 else
		     {
		      b = (y2_db - y1_db)/(x2_db - x1_db) ;
		      a = y1_db - (b * x1_db) ;

		      /* --------------------- CASE I ----------------------- */
		      if ((y1_db < y_min_plt && y2_db > y_max_plt) || (y2_db < y_min_plt && y1_db > y_max_plt))
			 {
			  if ((x2_db - x1_db) == 0)
			     {
			      x1_clip = x1_db ;  y1_clip = y_min_plt ;
			      x2_clip = x2_db ;  y2_clip = y_max_plt ;

			      if (SP_flag == 0) { fprintf(fp_o,"\nSP%d;",color); SP_flag =1; }
			      fprintf(fp_o ,"\nPU,%d,%d;",(int)x1_clip,(int)y1_clip);
			      fprintf(fp_o ,"PD%d,%d,%d,%d;",(int)x1_clip,(int)y1_clip,(int)x2_clip,(int)y2_clip);
			      goto endplot ;
			     }

			  x_bot = (y_min_plt - a) / b ;
			  x_top = (y_max_plt - a) / b ;

			  if (x_bot > x_min_plt && x_bot < x_max_plt)
			     {
			      x1_clip = x_bot ;
			      y1_clip = y_min_plt ;
			     }
			  else
			     { goto next2 ; }

			  if (x_top  > x_min_plt && x_top  < x_max_plt)
			     {
			      x2_clip = x_top ;
			      y2_clip = y_max_plt ;

			      if (SP_flag == 0) { fprintf(fp_o,"\nSP%d;",color); SP_flag =1; }
			      fprintf(fp_o ,"\nPU,%d,%d;",(int)x1_clip,(int)y1_clip);
			      fprintf(fp_o ,"PD%d,%d,%d,%d;",(int)x1_clip,(int)y1_clip,(int)x2_clip,(int)y2_clip);
			      goto endplot ;
			     }
			 }
		      next2:
		      /* --------------------- CASE II ---------------------- */
		      if ((x1_db < x_min_plt && x2_db > x_max_plt) || (x2_db < x_min_plt && x1_db > x_max_plt))
			 {
			  y_left  = a + (b * x_min_plt) ;
			  y_right = a + (b * x_max_plt) ;

			  if (y_left > y_min_plt && y_left < y_max_plt)
			     {
			      x1_clip = x_min_plt  ;
			      y1_clip = y_left ;
			     }
			  else
			     { goto next3 ; }

			  if (y_right > y_min_plt && y_right < y_max_plt)
			     {
			      x2_clip = x_max_plt   ;
			      y2_clip = y_right ;

			      if (SP_flag == 0) { fprintf(fp_o,"\nSP%d;",color); SP_flag =1; }
			      fprintf(fp_o ,"\nPU,%d,%d;",(int)x1_clip,(int)y1_clip);
			      fprintf(fp_o ,"PD%d,%d,%d,%d;",(int)x1_clip,(int)y1_clip,(int)x2_clip,(int)y2_clip);
			      goto endplot ;
			     }
			 }
		      next3:
		      /* --------------------- CASE III --------------------- */
		      if ((y1_db < y_min_plt && x2_db > x_max_plt) || (y2_db < y_min_plt && x1_db > x_max_plt))
			 {
			  x_bot   = (y_min_plt - a) / b ;
			  y_right = a + (b * x_max_plt) ;

			  if (x_bot > x_min_plt && x_bot < x_max_plt)
			     {
			      x1_clip = x_bot ;
			      y1_clip = y_min_plt ;
			     }
			  else
			     { goto next4 ; }

			  if (y_right > y_min_plt && y_right < y_max_plt)
			     {
			      x2_clip = x_max_plt   ;
			      y2_clip = y_right ;

			      if (SP_flag == 0) { fprintf(fp_o,"\nSP%d;",color); SP_flag =1; }
			      fprintf(fp_o ,"\nPU,%d,%d;",(int)x1_clip,(int)y1_clip);
			      fprintf(fp_o ,"PD%d,%d,%d,%d;",(int)x1_clip,(int)y1_clip,(int)x2_clip,(int)y2_clip);
			      goto endplot ;
			     }
			 }
		      next4:
		      /* --------------------- CASE IV ---------------------- */
		      if ((y1_db < y_min_plt && x2_db < x_min_plt) || (y2_db < y_min_plt && x1_db < x_min_plt))
			 {
			  x_bot  = (y_min_plt - a) / b ;
			  y_left = a + (b * x_min_plt) ;

			  if (x_bot > x_min_plt && x_bot < x_max_plt)
			     {
			      x1_clip = x_bot ;
			      y1_clip = y_min_plt ;
			     }
			  else
			     { goto next5 ; }

			  if (y_left > y_min_plt && y_left < y_max_plt)
			     {
			      x2_clip = x_min_plt   ;
			      y2_clip = y_left  ;

			      if (SP_flag == 0) { fprintf(fp_o,"\nSP%d;",color); SP_flag =1; }
			      fprintf(fp_o ,"\nPU,%d,%d;",(int)x1_clip,(int)y1_clip);
			      fprintf(fp_o ,"PD%d,%d,%d,%d;",(int)x1_clip,(int)y1_clip,(int)x2_clip,(int)y2_clip);
			      goto endplot ;
			     }
			 }
		      next5:
		      /* --------------------- CASE V ----------------------- */
		      if ((y2_db > y_max_plt && x1_db > x_max_plt) || (y1_db > y_max_plt && x2_db > x_max_plt))
			 {
			  x_top   = (y_max_plt - a) / b ;
			  y_right = a + (b * x_max_plt) ;

			  if (x_top  > x_min_plt && x_top  < x_max_plt)
			     {
			      x1_clip = x_top ;
			      y1_clip = y_max_plt ;
			     }
			  else
			     { goto next6 ; }

			  if (y_right > y_min_plt && y_right < y_max_plt)
			     {
			      x2_clip = x_max_plt   ;
			      y2_clip = y_right ;

			      if (SP_flag == 0) { fprintf(fp_o,"\nSP%d;",color); SP_flag =1; }
			      fprintf(fp_o ,"\nPU,%d,%d;",(int)x1_clip,(int)y1_clip);
			      fprintf(fp_o ,"PD%d,%d,%d,%d;",(int)x1_clip,(int)y1_clip,(int)x2_clip,(int)y2_clip);
			      goto endplot ;
			     }
			 }
		      next6:
		      /* --------------------- CASE VI ---------------------- */
		      if ((y2_db > y_max_plt && x1_db < x_min_plt) || (y1_db > y_max_plt && x2_db < x_min_plt))
			 {
			  x_top  = (y_max_plt - a) / b ;
			  y_left = a + (b * x_min_plt) ;

			  if (x_top  > x_min_plt && x_top  < x_max_plt)
			     {
			      x1_clip = x_top ;
			      y1_clip = y_max_plt ;
			     }
			  else
			     { goto endplot ; }

			  if (y_left > y_min_plt && y_left < y_max_plt)
			     {
			      x2_clip = x_min_plt   ;
			      y2_clip = y_left  ;

			      if (SP_flag == 0) { fprintf(fp_o,"\nSP%d;",color); SP_flag =1; }
			      fprintf(fp_o ,"\nPU,%d,%d;",(int)x1_clip,(int)y1_clip);
			      fprintf(fp_o ,"PD%d,%d,%d,%d;",(int)x1_clip,(int)y1_clip,(int)x2_clip,(int)y2_clip);
			      goto endplot ;
			     }
			 }

		      }

		   endplot:

		   x1_db = x[feat[i].xy+ii] ;
		   y1_db = y[feat[i].xy+ii] ;
		   break ;
	     }
	}
    }
    break ;


   default:   /*---------------- Do nothing ----------------------*/
     break ;
  }
 }

 fprintf(fp_o ,"\nPU;");
 fprintf(fp_o ,"\nSP0;");
 fclose(fp_o);


 cls_flag = 1         ;
 move_fun = CROSSHAIR ;
 point_counter = 1    ;
 // normal_cursor()      ;
 done = 1 ;
}

/*------------------------------------------------------------------------*/
/*                        plot_using_window()                             */
/*------------------------------------------------------------------------*/
void plot_using_window()
{


}


/*------------------------------------------------------------------------*/
/*                             plot_symb()                                */
/*------------------------------------------------------------------------*/
void plot_symb(symb_no,x_screen,y_screen,color,size,angle1)
{

 fprintf(fp_o,"\nSP%d;",color);

 symb_factor = (float)size / symb[symb_no].grid ;
 angle = (float)angle1 / DEG2RAD ;

 for ( ii=1; ii<=symb[symb_no].stroke; ii++)
   {
    switch (symb[symb_no].mv_draw[ii])
     {
      case 0:     /*  Move  */

	angle_sym = symb[symb_no].angle[ii] + angle ;
	x1_screen = x_screen + symb_factor * symb[symb_no].distance[ii] * cos(angle_sym) ;
	y1_screen = y_screen + symb_factor * symb[symb_no].distance[ii] * sin(angle_sym) ;
	fprintf(fp_o ,"\nPU,%d,%d;",x1_screen,y1_screen);
	break ;

      case 1:     /*  Draw  */

	angle_sym = symb[symb_no].angle[ii] + angle ;
	x2_screen = x_screen + symb_factor * symb[symb_no].distance[ii] * cos(angle_sym) ;
	y2_screen = y_screen + symb_factor * symb[symb_no].distance[ii] * sin(angle_sym) ;
	fprintf(fp_o ,"PD%d,%d,%d,%d;",x1_screen,y1_screen,x2_screen,y2_screen);

	x1_screen = x2_screen ;
	y1_screen = y2_screen ;
	break ;

      default:    /* Do nothing */
	break ;
     }
   }
}
/*------------------------------------------------------------------------*/
/*                             plot_text()                                */
/*------------------------------------------------------------------------*/
void plot_text(text_index)
{
 int previous_symb ;

 x_db = text[text_index].x    ;
 y_db = text[text_index].y    ;
 size = text[text_index].size ;

 /*  TEXT PLOT CLIPPING  */
 if ( (x_db >= x_min1)&&(x_db <= x_max1) &&
      (y_db >= y_min1)&&(y_db <= y_max1) &&
      ((size/ONE_PIXEL) >= 1)  )
    {
     fprintf(fp_o,"\nSP%d;",color);

     font_no = text[text_index].font                    ;
     angle   = (double)text[text_index].angle / DEG2RAD ;
     length  = strlen (text[text_index].string) - 1     ;

     switch (text[text_index].just)
	    {
	     case 1:
		    x_db -= (size/2) * sin(angle);             /* Bottom */
		    y_db += (size/2) * cos(angle);
		    x_db += (size/2) * cos(angle);             /* Left   */
		    y_db += (size/2) * sin(angle);
		    break;

	     case 2:
		    x_db -= (size/2) * sin(angle);             /* Bottom */
		    y_db += (size/2) * cos(angle);
		    x_db -= (length*size/2) * cos(angle);      /* Center */
		    y_db -= (length*size/2) * sin(angle);
		    break;

	     case 3:
		    x_db -= (size/2) * sin(angle);             /* Bottom */
		    y_db += (size/2) * cos(angle);
		    x_db -= (length*size) * cos(angle);        /* Right  */
		    y_db -= (length*size) * sin(angle);
		    break;

	     case 4:                                           /* Middle */
		    x_db += (size/2) * cos(angle);             /* Left   */
		    y_db += (size/2) * sin(angle);
		    break;

	     case 5:                                           /* Middle */
		    x_db -= (length*size/2) * cos(angle);      /* Center */
		    y_db -= (length*size/2) * sin(angle);
		    break;

	     case 6:                                           /* Middle */
		    x_db -= (length*size) * cos(angle);        /* Right  */
		    y_db -= (length*size) * sin(angle);
		    break;

	     case 7:
		    x_db += (size/2) * sin(angle);             /* Top    */
		    y_db -= (size/2) * cos(angle);
		    x_db += (size/2) * cos(angle);             /* Left   */
		    y_db += (size/2) * sin(angle);
		    break;

	     case 8:
		    x_db += (size/2) * sin(angle);             /* Top    */
		    y_db -= (size/2) * cos(angle);
		    x_db -= (length*size/2) * cos(angle);      /* Center */
		    y_db -= (length*size/2) * sin(angle);
		    break;

	     case 9:
		    x_db += (size/2) * sin(angle);             /* Top    */
		    y_db -= (size/2) * cos(angle);
		    x_db -= (length*size) * cos(angle);        /* Right  */
		    y_db -= (length*size) * sin(angle);
		    break;
	    }



     for ( j=0 ; j<=length ; j++ )
	 {
	  symb_no     = 0 ;
	  symb_no     = text[text_index].string[j] ;
	  symb_factor = (float)size / font[font_no][symb_no].grid ;

	  if ( j != 0 )
	     {
	      previous_symb = text[text_index].string[j-1] ;

	      x_db += size * font[font_no][previous_symb].x_factor * cos(angle) ;
	      y_db += size * font[font_no][previous_symb].x_factor * sin(angle) ;
	     }


	  for ( jj=1 ; jj<=font[font_no][symb_no].stroke ; jj++ )
	      {
	       if ( x_db > x_min && x_db < x_max && y_db > y_min && y_db < y_max )
		{
		 switch (font[font_no][symb_no].mv_draw[jj])
		 {
		  case 0:     /*  Move  */

		    angle_sym = font[font_no][symb_no].angle[jj] + angle ;
		    x1_screen = x_db + symb_factor * font[font_no][symb_no].distance[jj] * cos(angle_sym);
		    y1_screen = y_db + symb_factor * font[font_no][symb_no].distance[jj] * sin(angle_sym);

		    fprintf(fp_o ,"\nPU,%d,%d;",x1_screen,y1_screen);

		    break ;

		  case 1:     /*  Draw  */

		    angle_sym = font[font_no][symb_no].angle[jj] + angle ;
		    x2_screen = x_db + symb_factor * font[font_no][symb_no].distance[jj] * cos(angle_sym);
		    y2_screen = y_db + symb_factor * font[font_no][symb_no].distance[jj] * sin(angle_sym);

		    fprintf(fp_o ,"PD%d,%d,%d,%d;",x1_screen,y1_screen,x2_screen,y2_screen);

		    x1_screen = x2_screen ;
		    y1_screen = y2_screen ;
		    break ;

		  default:    /* Do nothing */
		    break ;
		 }
		}
	      }
	 }
    }

}
