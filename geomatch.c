static char sqla_program_id[162] = 
{
 42,0,65,68,65,75,65,73,71,69,79,77,65,84,67,72,55,65,83,89,
 79,67,75,86,48,49,49,49,49,32,50,32,8,0,71,69,79,73,78,70,
 79,32,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0
};

#include "sqladef.h"

static struct sqla_runtime_info sqla_rtinfo = 
{{'S','Q','L','A','R','T','I','N'}, sizeof(wchar_t), 0, {' ',' ',' ',' '}};


#line 1 "geomatch.sqc"
/*------------------------------------------------------------------------*/
/*               geoINFO/6000  Edge Matching ( geomatch.sqc)              */
/*------------------------------------------------------------------------*/

/*------------------------------------------------------------------------*/
/*                          geoINFO Include Files                         */
/*------------------------------------------------------------------------*/
#include "include/geoIMSextern.h"

/*------------------------------------------------------------------------------------------------*/
/*                                DB2 Embeded SQC Include Files                                   */
/*------------------------------------------------------------------------------------------------*/
#include <sqlda.h>
#include <sqlenv.h>
#include <sqlcodes.h>
#include "include/utilemb.h"

/*------------------------------------------------------------------------*/
/*                           Functions Prototypes                         */
/*------------------------------------------------------------------------*/
void join_text_and_update_DB();

/*------------------------------------------------------------------------------------------------*/
/*                                    Embeded SQL Variables                                       */
/*------------------------------------------------------------------------------------------------*/
// #define  CHECKERR(CE_STR)  if(check_error (CE_STR,&sqlca) != 0) printf("error");


/*
EXEC SQL INCLUDE SQLCA;
*/

/* SQL Communication Area - SQLCA - structures and constants */
#include "sqlca.h"
struct sqlca sqlca;


#line 28 "geomatch.sqc"



/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 30 "geomatch.sqc"

   long    feat_num            ;
   long    x_base              ;
   long    y_base              ;
   long    x_end               ;
   long    y_end               ;
   long    xy_count            ;
   long    text_count          ;
   long    seq                 ;
   long    x_1                 ;
   long    y_1                 ;
   long    x_2                 ;
   long    y_2                 ;
   long    x_3                 ;
   long    y_3                 ;
   long    x_4                 ;
   long    y_4                 ;
   long    x_5                 ;
   long    y_5                 ;
   long    x_6                 ;
   long    y_6                 ;
   long    x_7                 ;
   long    y_7                 ;
   long    x_8                 ;
   long    y_8                 ;
   long    x_9                 ;
   long    y_9                 ;
   long    x_10                ;
   long    y_10                ;
   long    text_x              ;
   long    text_y              ;
   long    text_size           ;
   long    text_angle          ;
   short   text_just           ;
   short   text_font           ;
   char    textstring [51]     ;

/*
EXEC SQL END DECLARE SECTION;
*/

#line 66 "geomatch.sqc"



 char   MATCH [1]   ;

 int    f_num1      ;
 int    x_base1     ;
 int    y_base1     ;
 int    x_end1      ;
 int    y_end1      ;
 int    xy_index1   ;
 int    xy_count1   ;
 int    text_index1 ;
 int    text_count1 ;

 int    f_num2      ;
 int    x_base2     ;
 int    y_base2     ;
 int    x_end2      ;
 int    y_end2      ;
 int    xy_index2   ;
 int    xy_count2   ;
 int    text_index2 ;
 int    text_count2 ;

 int    distance1   ;
 int    distance2   ;
 int    distance3   ;
 int    distance4   ;


/* -------------------------------------------------------------------*/
/*                         match_all()                                */
/* -------------------------------------------------------------------*/
match_all(int match_tolerance )
{

 /*-------------------------------------------------------------*/
 /*                   Match_Adjecent_Features                   */
 /*-------------------------------------------------------------*/

 Match_Adjecent :

 MATCH[0] = 'N';

 for ( i=1 ; i<=feat_count ; i++ )
     {

     if ( feat[i].type == 2 )
	{

	 for ( ii=1 ; ii <= feat_count ; ii++ )
	     {
	      if (( ii != i ) && ( strcmp(feat[ii].code,feat[i].code) == 0 ))
		 {
		  f_num1    = feat[i].num                        ;
		  x_base1   = feat[i].xbase                      ;
		  y_base1   = feat[i].ybase                      ;
		  xy_index1 = feat[i].xy                         ;
		  xy_count1 = feat[i].xy_count                   ;
		  x_end1    = feat[i].xend                       ;
		  y_end1    = feat[i].yend                       ;

		  f_num2    = feat[ii].num                       ;
		  x_base2   = feat[ii].xbase                     ;
		  y_base2   = feat[ii].ybase                     ;
		  xy_index2 = feat[ii].xy                        ;
		  xy_count2 = feat[ii].xy_count                  ;
		  x_end2    = feat[ii].xend                      ;
		  y_end2    = feat[ii].yend                      ;


		  /*---------------------------------------------*/
		  /*            CASE I  (base1=base2)            */
		  /*---------------------------------------------*/

		  if ( x_base1 == x_base2 && y_base1 == y_base2 )
		     {
		      MATCH[0]   = 'Y'      ;
		      jj         = 0        ;
		      xy_index   = xy_LAST  ;


		      feat[i].xbase = x_end1 ;
		      feat[i].ybase = y_end1 ;

		      for ( j=xy_count1 ; j>=1 ; j-- )
			  {
			   jj++;
			   x[xy_index+jj] = x[xy_index1+j];
			   y[xy_index+jj] = y[xy_index1+j];
			  }

		      jj++;
		      x[xy_index+jj] = x_base1 ;
		      y[xy_index+jj] = y_base1 ;

		      for ( j=1 ; j<=xy_count2 ; j++ )
			  {
			   jj++;
			   x[xy_index+jj] = x[xy_index2+j];
			   y[xy_index+jj] = y[xy_index2+j];
			  }

		      feat[i].xend = x_end2 ;
		      feat[i].yend = y_end2 ;


		      feat[i].xy       = xy_index ;
		      feat[i].xy_count = jj       ;
		      xy_LAST          = xy_LAST + feat[i].xy_count ;


		      feat[ii].num            = feat[feat_count].num           ;
		      strcpy ( feat[ii].code, feat[feat_count].code )        ;
		      feat[ii].type           = feat[feat_count].type          ;
		      feat[ii].layer          = feat[feat_count].layer         ;
		      feat[ii].network        = feat[feat_count].network       ;
		      feat[ii].scale_range[0] = feat[feat_count].scale_range[0];
		      feat[ii].scale_range[1] = feat[feat_count].scale_range[1];
		      feat[ii].scale_range[2] = feat[feat_count].scale_range[2];
		      feat[ii].scale_range[3] = feat[feat_count].scale_range[3];
		      feat[ii].scale_range[4] = feat[feat_count].scale_range[4];
		      feat[ii].displayed[0]   = feat[feat_count].displayed[0]  ;
		      feat[ii].selectble[0]   = feat[feat_count].selectble[0]  ;
		      feat[ii].has_attrib[0]  = feat[feat_count].has_attrib[0] ;
		      feat[ii].has_text[0]    = feat[feat_count].has_text[0]   ;
		      feat[ii].color          = feat[feat_count].color         ;
		      feat[ii].linetype       = feat[feat_count].linetype      ;
		      feat[ii].linewidth      = feat[feat_count].linewidth     ;
		      feat[ii].xbase          = feat[feat_count].xbase         ;
		      feat[ii].ybase          = feat[feat_count].ybase         ;
		      feat[ii].xend           = feat[feat_count].xend          ;
		      feat[ii].yend           = feat[feat_count].yend          ;
		      feat[ii].xy_count       = feat[feat_count].xy_count      ;
		      feat[ii].symb_num       = feat[feat_count].symb_num      ;
		      feat[ii].symb_size      = feat[feat_count].symb_size     ;
		      feat[ii].symb_angle     = feat[feat_count].symb_angle    ;
		      feat[ii].text_count     = feat[feat_count].text_count    ;
		      feat[ii].xy             = feat[feat_count].xy            ;
		      feat[ii].text           = feat[feat_count].text          ;

		      feat_count-- ;
		     }

		  /*---------------------------------------------*/
		  /*            CASE II  (base1=end2)            */
		  /*---------------------------------------------*/

	     else if ( x_base1 == x_end2  && y_base1 == y_end2 )
		     {
		      MATCH[0]   = 'Y'      ;
		      jj         = 0        ;
		      xy_index   = xy_LAST  ;


		      feat[i].xbase = x_end1 ;
		      feat[i].ybase = y_end1 ;

		      for ( j=xy_count1 ; j>=1 ; j-- )
			  {
			   jj++;
			   x[xy_index+jj] = x[xy_index1+j];
			   y[xy_index+jj] = y[xy_index1+j];
			  }

		      jj++;
		      x[xy_index+jj] = x_base1 ;
		      y[xy_index+jj] = y_base1 ;

		      for ( j=xy_count2 ; j>=1 ; j-- )
			  {
			   jj++;
			   x[xy_index+jj] = x[xy_index2+j];
			   y[xy_index+jj] = y[xy_index2+j];
			  }

		      feat[i].xend = x_base2 ;
		      feat[i].yend = y_base2 ;


		      feat[i].xy       = xy_index ;
		      feat[i].xy_count = jj       ;
		      xy_LAST          = xy_LAST + feat[i].xy_count ;

		      feat[ii].num            = feat[feat_count].num           ;
		      strcpy ( feat[ii].code, feat[feat_count].code )        ;
		      feat[ii].type           = feat[feat_count].type          ;
		      feat[ii].layer          = feat[feat_count].layer         ;
		      feat[ii].network        = feat[feat_count].network       ;
		      feat[ii].scale_range[0] = feat[feat_count].scale_range[0];
		      feat[ii].scale_range[1] = feat[feat_count].scale_range[1];
		      feat[ii].scale_range[2] = feat[feat_count].scale_range[2];
		      feat[ii].scale_range[3] = feat[feat_count].scale_range[3];
		      feat[ii].scale_range[4] = feat[feat_count].scale_range[4];
		      feat[ii].displayed[0]   = feat[feat_count].displayed[0]  ;
		      feat[ii].selectble[0]   = feat[feat_count].selectble[0]  ;
		      feat[ii].has_attrib[0]  = feat[feat_count].has_attrib[0] ;
		      feat[ii].has_text[0]    = feat[feat_count].has_text[0]   ;
		      feat[ii].color          = feat[feat_count].color         ;
		      feat[ii].linetype       = feat[feat_count].linetype      ;
		      feat[ii].linewidth      = feat[feat_count].linewidth     ;
		      feat[ii].xbase          = feat[feat_count].xbase         ;
		      feat[ii].ybase          = feat[feat_count].ybase         ;
		      feat[ii].xend           = feat[feat_count].xend          ;
		      feat[ii].yend           = feat[feat_count].yend          ;
		      feat[ii].xy_count       = feat[feat_count].xy_count      ;
		      feat[ii].symb_num       = feat[feat_count].symb_num      ;
		      feat[ii].symb_size      = feat[feat_count].symb_size     ;
		      feat[ii].symb_angle     = feat[feat_count].symb_angle    ;
		      feat[ii].text_count     = feat[feat_count].text_count    ;
		      feat[ii].xy             = feat[feat_count].xy            ;
		      feat[ii].text           = feat[feat_count].text          ;

		      feat_count-- ;
		     }

		  /*---------------------------------------------*/
		  /*            CASE III  (end1=base2)           */
		  /*---------------------------------------------*/

	     else if ( x_end1 == x_base2 && y_end1 == y_base2 )
		     {
		      MATCH[0]  = 'Y'       ;
		      jj         = 0        ;
		      xy_index   = xy_LAST  ;


		      feat[i].xbase = x_base1 ;
		      feat[i].ybase = y_base1 ;

		      for ( j=1 ; j<=xy_count1 ; j++ )
			  {
			   jj++;
			   x[xy_index+jj] = x[xy_index1+j];
			   y[xy_index+jj] = y[xy_index1+j];
			  }

		      jj++;
		      x[xy_index+jj] = x_end1 ;
		      y[xy_index+jj] = y_end1 ;

		      for ( j=1 ; j<=xy_count2 ; j++ )
			  {
			   jj++;
			   x[xy_index+jj] = x[xy_index2+j];
			   y[xy_index+jj] = y[xy_index2+j];
			  }

		      feat[i].xend = x_end2 ;
		      feat[i].yend = y_end2 ;


		      feat[i].xy       = xy_index ;
		      feat[i].xy_count = jj       ;
		      xy_LAST          = xy_LAST + feat[i].xy_count ;

		      feat[ii].num            = feat[feat_count].num           ;
		      strcpy ( feat[ii].code, feat[feat_count].code )        ;
		      feat[ii].type           = feat[feat_count].type          ;
		      feat[ii].layer          = feat[feat_count].layer         ;
		      feat[ii].network        = feat[feat_count].network       ;
		      feat[ii].scale_range[0] = feat[feat_count].scale_range[0];
		      feat[ii].scale_range[1] = feat[feat_count].scale_range[1];
		      feat[ii].scale_range[2] = feat[feat_count].scale_range[2];
		      feat[ii].scale_range[3] = feat[feat_count].scale_range[3];
		      feat[ii].scale_range[4] = feat[feat_count].scale_range[4];
		      feat[ii].displayed[0]   = feat[feat_count].displayed[0]  ;
		      feat[ii].selectble[0]   = feat[feat_count].selectble[0]  ;
		      feat[ii].has_attrib[0]  = feat[feat_count].has_attrib[0] ;
		      feat[ii].has_text[0]    = feat[feat_count].has_text[0]   ;
		      feat[ii].color          = feat[feat_count].color         ;
		      feat[ii].linetype       = feat[feat_count].linetype      ;
		      feat[ii].linewidth      = feat[feat_count].linewidth     ;
		      feat[ii].xbase          = feat[feat_count].xbase         ;
		      feat[ii].ybase          = feat[feat_count].ybase         ;
		      feat[ii].xend           = feat[feat_count].xend          ;
		      feat[ii].yend           = feat[feat_count].yend          ;
		      feat[ii].xy_count       = feat[feat_count].xy_count      ;
		      feat[ii].symb_num       = feat[feat_count].symb_num      ;
		      feat[ii].symb_size      = feat[feat_count].symb_size     ;
		      feat[ii].symb_angle     = feat[feat_count].symb_angle    ;
		      feat[ii].text_count     = feat[feat_count].text_count    ;
		      feat[ii].xy             = feat[feat_count].xy            ;
		      feat[ii].text           = feat[feat_count].text          ;

		      feat_count-- ;
		     }

		  /*---------------------------------------------*/
		  /*            CASE IV  (end1=end2)             */
		  /*---------------------------------------------*/

	     else if ( x_end1 == x_end2  && y_end1 == y_end2 )
		     {
		      MATCH[0]   = 'Y'      ;
		      jj         = 0        ;
		      xy_index   = xy_LAST  ;


		      feat[i].xbase = x_base1 ;
		      feat[i].ybase = y_base1 ;

		      for ( j=1 ; j<=xy_count1 ; j++ )
			  {
			   jj++;
			   x[xy_index+jj] = x[xy_index1+j];
			   y[xy_index+jj] = y[xy_index1+j];
			  }

		      jj++;
		      x[xy_index+jj] = x_end1 ;
		      y[xy_index+jj] = y_end1 ;

		      for ( j=xy_count2 ; j>=1 ; j-- )
			  {
			   jj++;
			   x[xy_index+jj] = x[xy_index2+j];
			   y[xy_index+jj] = y[xy_index2+j];
			  }

		      feat[i].xend = x_base2 ;
		      feat[i].yend = y_base2 ;


		      feat[i].xy       = xy_index ;
		      feat[i].xy_count = jj       ;
		      xy_LAST          = xy_LAST + feat[i].xy_count ;

		      feat[ii].num            = feat[feat_count].num           ;
		      strcpy ( feat[ii].code, feat[feat_count].code )        ;
		      feat[ii].type           = feat[feat_count].type          ;
		      feat[ii].layer          = feat[feat_count].layer         ;
		      feat[ii].network        = feat[feat_count].network       ;
		      feat[ii].scale_range[0] = feat[feat_count].scale_range[0];
		      feat[ii].scale_range[1] = feat[feat_count].scale_range[1];
		      feat[ii].scale_range[2] = feat[feat_count].scale_range[2];
		      feat[ii].scale_range[3] = feat[feat_count].scale_range[3];
		      feat[ii].scale_range[4] = feat[feat_count].scale_range[4];
		      feat[ii].displayed[0]   = feat[feat_count].displayed[0]  ;
		      feat[ii].selectble[0]   = feat[feat_count].selectble[0]  ;
		      feat[ii].has_attrib[0]  = feat[feat_count].has_attrib[0] ;
		      feat[ii].has_text[0]    = feat[feat_count].has_text[0]   ;
		      feat[ii].color          = feat[feat_count].color         ;
		      feat[ii].linetype       = feat[feat_count].linetype      ;
		      feat[ii].linewidth      = feat[feat_count].linewidth     ;
		      feat[ii].xbase          = feat[feat_count].xbase         ;
		      feat[ii].ybase          = feat[feat_count].ybase         ;
		      feat[ii].xend           = feat[feat_count].xend          ;
		      feat[ii].yend           = feat[feat_count].yend          ;
		      feat[ii].xy_count       = feat[feat_count].xy_count      ;
		      feat[ii].symb_num       = feat[feat_count].symb_num      ;
		      feat[ii].symb_size      = feat[feat_count].symb_size     ;
		      feat[ii].symb_angle     = feat[feat_count].symb_angle    ;
		      feat[ii].text_count     = feat[feat_count].text_count    ;
		      feat[ii].xy             = feat[feat_count].xy            ;
		      feat[ii].text           = feat[feat_count].text          ;

		      feat_count-- ;
		     }

		 }
	     }
	}

     }  /* end of for loop */

  if ( MATCH[0] == 'Y' ) goto Match_Adjecent ;



 /*-------------------------------------------------------------*/
 /*             Match_Features_within_Tolerance                 */
 /*-------------------------------------------------------------*/

 Match_Tolerance :

 MATCH[0] = 'N';

 for ( i=1 ; i<=feat_count ; i++ )
     {

     if ( feat[i].type == 2 )
	{

	 for ( ii=1 ; ii <= feat_count ; ii++ )
	     {
	      if (( ii != i ) && ( strcmp(feat[ii].code,feat[i].code) == 0 ))
		 {
		  f_num1    = feat[i].num                        ;
		  x_base1   = feat[i].xbase                      ;
		  y_base1   = feat[i].ybase                      ;
		  xy_index1 = feat[i].xy                         ;
		  xy_count1 = feat[i].xy_count                   ;
		  x_end1    = feat[i].xend                       ;
		  y_end1    = feat[i].yend                       ;

		  f_num2    = feat[ii].num                       ;
		  x_base2   = feat[ii].xbase                     ;
		  y_base2   = feat[ii].ybase                     ;
		  xy_index2 = feat[ii].xy                        ;
		  xy_count2 = feat[ii].xy_count                  ;
		  x_end2    = feat[ii].xend                      ;
		  y_end2    = feat[ii].yend                      ;

		  x_diff    = abs  ( x_base1 - x_base2 );
		  y_diff    = abs  ( y_base1 - y_base2 );
		  distance1 = sqrt ((x_diff*x_diff)+(y_diff*y_diff));

		  x_diff    = abs  ( x_base1 - x_end2  );
		  y_diff    = abs  ( y_base1 - y_end2  );
		  distance2 = sqrt ((x_diff*x_diff)+(y_diff*y_diff));

		  x_diff    = abs  ( x_end1  - x_base2 );
		  y_diff    = abs  ( y_end1  - y_base2 );
		  distance3 = sqrt ((x_diff*x_diff)+(y_diff*y_diff));

		  x_diff    = abs  ( x_end1  - x_end2  );
		  y_diff    = abs  ( y_end1  - y_end2  );
		  distance4 = sqrt ((x_diff*x_diff)+(y_diff*y_diff));


		  /*---------------------------------------------*/
		  /*            CASE I  (base1-base2)            */
		  /*---------------------------------------------*/

		  if ( distance1 <= match_tolerance )
		     {
		      MATCH[0]   = 'Y'      ;
		      jj         = 0        ;
		      xy_index   = xy_LAST  ;

		      feat[i].xbase = x_end1 ;
		      feat[i].ybase = y_end1 ;

		      for ( j=xy_count1 ; j>=1 ; j-- )
			  {
			   jj++;
			   x[xy_index+jj] = x[xy_index1+j];
			   y[xy_index+jj] = y[xy_index1+j];
			  }

		      jj++;
		      x[xy_index+jj] = ( x_base1 + x_base2 ) / 2 ;
		      y[xy_index+jj] = ( y_base1 + y_base2 ) / 2 ;

		      for ( j=1 ; j<=xy_count2 ; j++ )
			  {
			   jj++;
			   x[xy_index+jj] = x[xy_index2+j];
			   y[xy_index+jj] = y[xy_index2+j];
			  }

		      feat[i].xend = x_end2 ;
		      feat[i].yend = y_end2 ;

		      feat[i].xy       = xy_index ;
		      feat[i].xy_count = jj       ;
		      xy_LAST          = xy_LAST + feat[i].xy_count ;

		      feat[ii].num            = feat[feat_count].num           ;
		      strcpy ( feat[ii].code, feat[feat_count].code )        ;
		      feat[ii].type           = feat[feat_count].type          ;
		      feat[ii].layer          = feat[feat_count].layer         ;
		      feat[ii].network        = feat[feat_count].network       ;
		      feat[ii].scale_range[0] = feat[feat_count].scale_range[0];
		      feat[ii].scale_range[1] = feat[feat_count].scale_range[1];
		      feat[ii].scale_range[2] = feat[feat_count].scale_range[2];
		      feat[ii].scale_range[3] = feat[feat_count].scale_range[3];
		      feat[ii].scale_range[4] = feat[feat_count].scale_range[4];
		      feat[ii].displayed[0]   = feat[feat_count].displayed[0]  ;
		      feat[ii].selectble[0]   = feat[feat_count].selectble[0]  ;
		      feat[ii].has_attrib[0]  = feat[feat_count].has_attrib[0] ;
		      feat[ii].has_text[0]    = feat[feat_count].has_text[0]   ;
		      feat[ii].color          = feat[feat_count].color         ;
		      feat[ii].linetype       = feat[feat_count].linetype      ;
		      feat[ii].linewidth      = feat[feat_count].linewidth     ;
		      feat[ii].xbase          = feat[feat_count].xbase         ;
		      feat[ii].ybase          = feat[feat_count].ybase         ;
		      feat[ii].xend           = feat[feat_count].xend          ;
		      feat[ii].yend           = feat[feat_count].yend          ;
		      feat[ii].xy_count       = feat[feat_count].xy_count      ;
		      feat[ii].symb_num       = feat[feat_count].symb_num      ;
		      feat[ii].symb_size      = feat[feat_count].symb_size     ;
		      feat[ii].symb_angle     = feat[feat_count].symb_angle    ;
		      feat[ii].text_count     = feat[feat_count].text_count    ;
		      feat[ii].xy             = feat[feat_count].xy            ;
		      feat[ii].text           = feat[feat_count].text          ;

		      feat_count-- ;
		     }

		  /*---------------------------------------------*/
		  /*            CASE II  (base1-end2)            */
		  /*---------------------------------------------*/

	     else if ( distance2 <= match_tolerance )
		     {
		      MATCH[0]  = 'Y'       ;
		      jj         = 0        ;
		      xy_index   = xy_LAST  ;

		      feat[i].xbase = x_end1 ;
		      feat[i].ybase = y_end1 ;

		      for ( j=xy_count1 ; j>=1 ; j-- )
			  {
			   jj++;
			   x[xy_index+jj] = x[xy_index1+j];
			   y[xy_index+jj] = y[xy_index1+j];
			  }

		      jj++;
		      x[xy_index+jj] = ( x_base1 + x_end2 ) / 2 ;
		      y[xy_index+jj] = ( y_base1 + y_end2 ) / 2 ;

		      for ( j=xy_count2 ; j>=1 ; j-- )
			  {
			   jj++;
			   x[xy_index+jj] = x[xy_index2+j];
			   y[xy_index+jj] = y[xy_index2+j];
			  }

		      feat[i].xend = x_base2 ;
		      feat[i].yend = y_base2 ;

		      feat[i].xy       = xy_index ;
		      feat[i].xy_count = jj       ;
		      xy_LAST          = xy_LAST + feat[i].xy_count ;

		      feat[ii].num            = feat[feat_count].num           ;
		      strcpy ( feat[ii].code, feat[feat_count].code )        ;
		      feat[ii].type           = feat[feat_count].type          ;
		      feat[ii].layer          = feat[feat_count].layer         ;
		      feat[ii].network        = feat[feat_count].network       ;
		      feat[ii].scale_range[0] = feat[feat_count].scale_range[0];
		      feat[ii].scale_range[1] = feat[feat_count].scale_range[1];
		      feat[ii].scale_range[2] = feat[feat_count].scale_range[2];
		      feat[ii].scale_range[3] = feat[feat_count].scale_range[3];
		      feat[ii].scale_range[4] = feat[feat_count].scale_range[4];
		      feat[ii].displayed[0]   = feat[feat_count].displayed[0]  ;
		      feat[ii].selectble[0]   = feat[feat_count].selectble[0]  ;
		      feat[ii].has_attrib[0]  = feat[feat_count].has_attrib[0] ;
		      feat[ii].has_text[0]    = feat[feat_count].has_text[0]   ;
		      feat[ii].color          = feat[feat_count].color         ;
		      feat[ii].linetype       = feat[feat_count].linetype      ;
		      feat[ii].linewidth      = feat[feat_count].linewidth     ;
		      feat[ii].xbase          = feat[feat_count].xbase         ;
		      feat[ii].ybase          = feat[feat_count].ybase         ;
		      feat[ii].xend           = feat[feat_count].xend          ;
		      feat[ii].yend           = feat[feat_count].yend          ;
		      feat[ii].xy_count       = feat[feat_count].xy_count      ;
		      feat[ii].symb_num       = feat[feat_count].symb_num      ;
		      feat[ii].symb_size      = feat[feat_count].symb_size     ;
		      feat[ii].symb_angle     = feat[feat_count].symb_angle    ;
		      feat[ii].text_count     = feat[feat_count].text_count    ;
		      feat[ii].xy             = feat[feat_count].xy            ;
		      feat[ii].text           = feat[feat_count].text          ;

		      feat_count-- ;
		     }

		  /*---------------------------------------------*/
		  /*            CASE III  (end1-base2)           */
		  /*---------------------------------------------*/

	     else if ( distance3 <= match_tolerance )
		     {
		      MATCH[0]   = 'Y'      ;
		      jj         = 0        ;
		      xy_index   = xy_LAST  ;

		      feat[i].xbase = x_base1 ;
		      feat[i].ybase = y_base1 ;

		      for ( j=1 ; j<=xy_count1 ; j++ )
			  {
			   jj++;
			   x[xy_index+jj] = x[xy_index1+j];
			   y[xy_index+jj] = y[xy_index1+j];
			  }

		      jj++;
		      x[xy_index+jj] = ( x_end1 + x_base2 ) / 2 ;
		      y[xy_index+jj] = ( y_end1 + y_base2 ) / 2 ;


		      for ( j=1 ; j<=xy_count2 ; j++ )
			  {
			   jj++;
			   x[xy_index+jj] = x[xy_index2+j];
			   y[xy_index+jj] = y[xy_index2+j];
			  }

		      feat[i].xend = x_end2 ;
		      feat[i].yend = y_end2 ;

		      feat[i].xy       = xy_index ;
		      feat[i].xy_count = jj       ;
		      xy_LAST          = xy_LAST + feat[i].xy_count ;

		      feat[ii].num            = feat[feat_count].num           ;
		      strcpy ( feat[ii].code, feat[feat_count].code )        ;
		      feat[ii].type           = feat[feat_count].type          ;
		      feat[ii].layer          = feat[feat_count].layer         ;
		      feat[ii].network        = feat[feat_count].network       ;
		      feat[ii].scale_range[0] = feat[feat_count].scale_range[0];
		      feat[ii].scale_range[1] = feat[feat_count].scale_range[1];
		      feat[ii].scale_range[2] = feat[feat_count].scale_range[2];
		      feat[ii].scale_range[3] = feat[feat_count].scale_range[3];
		      feat[ii].scale_range[4] = feat[feat_count].scale_range[4];
		      feat[ii].displayed[0]   = feat[feat_count].displayed[0]  ;
		      feat[ii].selectble[0]   = feat[feat_count].selectble[0]  ;
		      feat[ii].has_attrib[0]  = feat[feat_count].has_attrib[0] ;
		      feat[ii].has_text[0]    = feat[feat_count].has_text[0]   ;
		      feat[ii].color          = feat[feat_count].color         ;
		      feat[ii].linetype       = feat[feat_count].linetype      ;
		      feat[ii].linewidth      = feat[feat_count].linewidth     ;
		      feat[ii].xbase          = feat[feat_count].xbase         ;
		      feat[ii].ybase          = feat[feat_count].ybase         ;
		      feat[ii].xend           = feat[feat_count].xend          ;
		      feat[ii].yend           = feat[feat_count].yend          ;
		      feat[ii].xy_count       = feat[feat_count].xy_count      ;
		      feat[ii].symb_num       = feat[feat_count].symb_num      ;
		      feat[ii].symb_size      = feat[feat_count].symb_size     ;
		      feat[ii].symb_angle     = feat[feat_count].symb_angle    ;
		      feat[ii].text_count     = feat[feat_count].text_count    ;
		      feat[ii].xy             = feat[feat_count].xy            ;
		      feat[ii].text           = feat[feat_count].text          ;

		      feat_count-- ;
		     }

		  /*---------------------------------------------*/
		  /*            CASE IV  (end1-end2)             */
		  /*---------------------------------------------*/

	     else if ( distance4 <= match_tolerance )
		     {
		      MATCH[0]   = 'Y'      ;
		      jj         = 0        ;
		      xy_index   = xy_LAST  ;

		      feat[i].xbase = x_base1 ;
		      feat[i].ybase = y_base1 ;

		      for ( j=1 ; j<=xy_count1 ; j++ )
			  {
			   jj++;
			   x[xy_index+jj] = x[xy_index1+j];
			   y[xy_index+jj] = y[xy_index1+j];
			  }

		      jj++;
		      x[xy_index+jj] = ( x_end1 + x_end2 ) / 2 ;
		      y[xy_index+jj] = ( y_end1 + y_end2 ) / 2 ;

		      for ( j=xy_count2 ; j>=1 ; j-- )
			  {
			   jj++;
			   x[xy_index+jj] = x[xy_index2+j];
			   y[xy_index+jj] = y[xy_index2+j];
			  }

		      feat[i].xend = x_base2 ;
		      feat[i].yend = y_base2 ;


		      feat[i].xy       = xy_index ;
		      feat[i].xy_count = jj       ;
		      xy_LAST          = xy_LAST + feat[i].xy_count ;

		      feat[ii].num            = feat[feat_count].num           ;
		      strcpy ( feat[ii].code, feat[feat_count].code )        ;
		      feat[ii].type           = feat[feat_count].type          ;
		      feat[ii].layer          = feat[feat_count].layer         ;
		      feat[ii].network        = feat[feat_count].network       ;
		      feat[ii].scale_range[0] = feat[feat_count].scale_range[0];
		      feat[ii].scale_range[1] = feat[feat_count].scale_range[1];
		      feat[ii].scale_range[2] = feat[feat_count].scale_range[2];
		      feat[ii].scale_range[3] = feat[feat_count].scale_range[3];
		      feat[ii].scale_range[4] = feat[feat_count].scale_range[4];
		      feat[ii].displayed[0]   = feat[feat_count].displayed[0]  ;
		      feat[ii].selectble[0]   = feat[feat_count].selectble[0]  ;
		      feat[ii].has_attrib[0]  = feat[feat_count].has_attrib[0] ;
		      feat[ii].has_text[0]    = feat[feat_count].has_text[0]   ;
		      feat[ii].color          = feat[feat_count].color         ;
		      feat[ii].linetype       = feat[feat_count].linetype      ;
		      feat[ii].linewidth      = feat[feat_count].linewidth     ;
		      feat[ii].xbase          = feat[feat_count].xbase         ;
		      feat[ii].ybase          = feat[feat_count].ybase         ;
		      feat[ii].xend           = feat[feat_count].xend          ;
		      feat[ii].yend           = feat[feat_count].yend          ;
		      feat[ii].xy_count       = feat[feat_count].xy_count      ;
		      feat[ii].symb_num       = feat[feat_count].symb_num      ;
		      feat[ii].symb_size      = feat[feat_count].symb_size     ;
		      feat[ii].symb_angle     = feat[feat_count].symb_angle    ;
		      feat[ii].text_count     = feat[feat_count].text_count    ;
		      feat[ii].xy             = feat[feat_count].xy            ;
		      feat[ii].text           = feat[feat_count].text          ;

		      feat_count-- ;
		     }

		 }
	     }
	}

     }  /* end of for loop */

  if ( MATCH[0] == 'Y' ) goto Match_Tolerance ;


 return ;

}
/* -------------------------------------------------------------------*/
/*                        join_feature()                              */
/* -------------------------------------------------------------------*/

join_feature(int feat_1,int feat_2, int match_tolerance)
{
 long i  ;
 long ii ;


 Match_Tolerance :

 MATCH[0] = 'N';

 i  = feat_1 ;
 ii = feat_2 ;

 if ( strcmp(feat[i].code,feat[ii].code) == 0 )
    {
      f_num1      = feat[i].num            ;
      x_base1     = feat[i].xbase          ;
      y_base1     = feat[i].ybase          ;
      xy_index1   = feat[i].xy             ;
      xy_count1   = feat[i].xy_count       ;
      text_index1 = feat[i].text           ;
      text_count1 = feat[i].text_count     ;
      x_end1      = feat[i].xend           ;
      y_end1      = feat[i].yend           ;

      f_num2      = feat[ii].num           ;
      x_base2     = feat[ii].xbase         ;
      y_base2     = feat[ii].ybase         ;
      xy_index2   = feat[ii].xy            ;
      xy_count2   = feat[ii].xy_count      ;
      text_index2 = feat[ii].text          ;
      text_count2 = feat[ii].text_count    ;
      x_end2      = feat[ii].xend          ;
      y_end2      = feat[ii].yend          ;

      x_diff    = abs  ( x_base1 - x_base2 );
      y_diff    = abs  ( y_base1 - y_base2 );
      distance1 = sqrt ((x_diff*x_diff)+(y_diff*y_diff));

      x_diff    = abs  ( x_base1 - x_end2  );
      y_diff    = abs  ( y_base1 - y_end2  );
      distance2 = sqrt ((x_diff*x_diff)+(y_diff*y_diff));

      x_diff    = abs  ( x_end1  - x_base2 );
      y_diff    = abs  ( y_end1  - y_base2 );
      distance3 = sqrt ((x_diff*x_diff)+(y_diff*y_diff));

      x_diff    = abs  ( x_end1  - x_end2  );
      y_diff    = abs  ( y_end1  - y_end2  );
      distance4 = sqrt ((x_diff*x_diff)+(y_diff*y_diff));


      /*-----------------------------------------------------------*/
      /*            CASE I  (base1-base2)                          */
      /*-----------------------------------------------------------*/
      if ( distance1 <= match_tolerance )
         {
          MATCH[0]   = 'Y'      ;
          jj         = 0        ;
          xy_index   = xy_LAST  ;

          feat[i].xbase = x_end1 ;
          feat[i].ybase = y_end1 ;

          for ( j=xy_count1 ; j>=1 ; j-- )
	      {
	       jj++;
               x[xy_index+jj] = x[xy_index1+j];
	       y[xy_index+jj] = y[xy_index1+j];
	      }

          jj++;
          x[xy_index+jj] = ( x_base1 + x_base2 ) / 2 ;
          y[xy_index+jj] = ( y_base1 + y_base2 ) / 2 ;

          for ( j=1 ; j<=xy_count2 ; j++ )
	      {
	       jj++;
	       x[xy_index+jj] = x[xy_index2+j];
	       y[xy_index+jj] = y[xy_index2+j];
	      }

          feat[i].xend = x_end2 ;
          feat[i].yend = y_end2 ;

          feat[i].xy       = xy_index ;
          feat[i].xy_count = jj       ;
          xy_LAST          = xy_LAST + feat[i].xy_count ;

          //------------------------------------------
          // TEXT Join  & Delete feat_2 (from DB too)
          //------------------------------------------
          join_text_and_update_DB(i,ii) ;

         }

      /*-----------------------------------------------------------*/
      /*            CASE II  (base1-end2)                          */
      /*-----------------------------------------------------------*/
      else
      if ( distance2 <= match_tolerance )
         {
	  MATCH[0]  = 'Y'       ;
	  jj         = 0        ;
	  xy_index   = xy_LAST  ;

	  feat[i].xbase = x_end1 ;
	  feat[i].ybase = y_end1 ;

	  for ( j=xy_count1 ; j>=1 ; j-- )
	      {
	       jj++;
	       x[xy_index+jj] = x[xy_index1+j];
	       y[xy_index+jj] = y[xy_index1+j];
	      }

	  jj++;
	  x[xy_index+jj] = ( x_base1 + x_end2 ) / 2 ;
	  y[xy_index+jj] = ( y_base1 + y_end2 ) / 2 ;

	  for ( j=xy_count2 ; j>=1 ; j-- )
	      {
	       jj++;
	       x[xy_index+jj] = x[xy_index2+j];
	       y[xy_index+jj] = y[xy_index2+j];
	      }

  	  feat[i].xend = x_base2 ;
	  feat[i].yend = y_base2 ;

	  feat[i].xy       = xy_index ;
	  feat[i].xy_count = jj       ;
	  xy_LAST          = xy_LAST + feat[i].xy_count ;

          //------------------------------------------
          // TEXT Join  & Delete feat_2 (from DB too)
          //------------------------------------------
          join_text_and_update_DB(i,ii) ;

         }

      /*-----------------------------------------------------------*/
      /*            CASE III  (end1-base2)                         */
      /*-----------------------------------------------------------*/
      else
      if ( distance3 <= match_tolerance )
	 {
	  MATCH[0]   = 'Y'      ;
	  jj         = 0        ;
	  xy_index   = xy_LAST  ;

          feat[i].xbase = x_base1 ;
          feat[i].ybase = y_base1 ;

	  for ( j=1 ; j<=xy_count1 ; j++ )
	      {
	       jj++;
	       x[xy_index+jj] = x[xy_index1+j];
	       y[xy_index+jj] = y[xy_index1+j];
	      }

 	  jj++;
	  x[xy_index+jj] = ( x_end1 + x_base2 ) / 2 ;
	  y[xy_index+jj] = ( y_end1 + y_base2 ) / 2 ;


	  for ( j=1 ; j<=xy_count2 ; j++ )
	      {
	       jj++;
	       x[xy_index+jj] = x[xy_index2+j];
	       y[xy_index+jj] = y[xy_index2+j];
	      }

   	  feat[i].xend = x_end2 ;
	  feat[i].yend = y_end2 ;

	  feat[i].xy       = xy_index ;
	  feat[i].xy_count = jj       ;
	  xy_LAST          = xy_LAST + feat[i].xy_count ;

          //------------------------------------------
          // TEXT Join  & Delete feat_2 (from DB too)
          //------------------------------------------
          join_text_and_update_DB(i,ii) ;

	 }

      /*-----------------------------------------------------------*/
      /*            CASE IV  (end1-end2)                           */
      /*-----------------------------------------------------------*/
      else
      if ( distance4 <= match_tolerance )
	 {
	  MATCH[0]   = 'Y'      ;
	  jj         = 0        ;
	  xy_index   = xy_LAST  ;

          feat[i].xbase = x_base1 ;
	  feat[i].ybase = y_base1 ;

          for ( j=1 ; j<=xy_count1 ; j++ )
	      {
	       jj++;
	       x[xy_index+jj] = x[xy_index1+j];
	       y[xy_index+jj] = y[xy_index1+j];
	      }

	  jj++;
	  x[xy_index+jj] = ( x_end1 + x_end2 ) / 2 ;
	  y[xy_index+jj] = ( y_end1 + y_end2 ) / 2 ;

          for ( j=xy_count2 ; j>=1 ; j-- )
	      {
	       jj++;
	       x[xy_index+jj] = x[xy_index2+j];
	       y[xy_index+jj] = y[xy_index2+j];
	      }

          feat[i].xend = x_base2 ;
	  feat[i].yend = y_base2 ;

	  feat[i].xy       = xy_index ;
	  feat[i].xy_count = jj       ;
	  xy_LAST          = xy_LAST + feat[i].xy_count ;

          //------------------------------------------
          // TEXT Join  & Delete feat_2 (from DB too)
          //------------------------------------------
          join_text_and_update_DB(i,ii) ;

	 }


     }  /* end of for loop */


  if ( MATCH[0] == 'N' )
     {
      printf("\n ERROR : join not done !");
     }

}
/* -------------------------------------------------------------------*/
/*                  join_text_and_update_DB()                         */
/* -------------------------------------------------------------------*/
void join_text_and_update_DB(int feat_1, int feat_2)
{
 int i              ;
 int ii             ;
 int j              ;
 int old_text_index ;


 i  = feat_1 ;
 ii = feat_2 ;


 //-------------------------------
 // Join Text in Memorey
 //-------------------------------
 if (feat[i].has_text[0] == 'Y' && feat[ii].has_text[0] == 'Y')
    {
     old_text_index = feat[i].text ;
     text_index     = text_LAST    ;
     feat[i].text   = text_index++ ;

     for (j=1; j<= feat[i].text_count ; j++)
         {
          text[text_index].x     = text[old_text_index+j].x     ;
          text[text_index].y     = text[old_text_index+j].y     ;
	  text[text_index].size  = text[old_text_index+j].size  ;
	  text[text_index].just  = text[old_text_index+j].just  ;
	  text[text_index].font  = text[old_text_index+j].font  ;
          text[text_index].angle = text[old_text_index+j].angle ;
          strcpy(text[text_index].string,text[old_text_index+j].string);
          text_index++ ;
         }

     old_text_index = feat[ii].text ;
     for (j=1; j<= feat[ii].text_count ; j++)
         {
          text[text_index].x     = text[old_text_index+j].x     ;
          text[text_index].y     = text[old_text_index+j].y     ;
	  text[text_index].size  = text[old_text_index+j].size  ;
	  text[text_index].just  = text[old_text_index+j].just  ;
	  text[text_index].font  = text[old_text_index+j].font  ;
          text[text_index].angle = text[old_text_index+j].angle ;
          strcpy(text[text_index].string,text[old_text_index+j].string);
          text_index++ ;
         }

     feat[i].text_count = text_count1 + text_count2      ;
     text_LAST          = text_LAST + feat[i].text_count ;

    }
 else
 if (feat[i].has_text[0] == 'N' && feat[ii].has_text[0] == 'Y')
    {
     feat[i].text        = feat[ii].text ;
     feat[i].text_count  = feat[ii].text_count ;
     feat[i].has_text[0] = 'Y' ;
    }


 //----------------------------------------------
 // Update feat_1 in DB (Features, Coordinates )
 //----------------------------------------------
 if ( db_opened[0] == 'Y' )
    {
     // Update Features (XY_base, XY_end, XY_count)
     feat_num   = feat[i].num        ;
     x_base     = feat[i].xbase      ;
     y_base     = feat[i].ybase      ;
     x_end      = feat[i].xend       ;
     y_end      = feat[i].yend       ;
     xy_count   = feat[i].xy_count   ;
     text_count = feat[i].text_count ;

     printf("feat_num   = %d\n",feat_num);
     printf("x_base     = %d\n",x_base);
     printf("y_base     = %d\n",y_base);
     printf("x_end      = %d\n",x_end);
     printf("y_end      = %d\n",y_end);
     printf("xy_count   = %d\n",xy_count);
     printf("text_count = %d\n",text_count);

     
/*
EXEC SQL UPDATE FEATURES
              SET X_BASE     = :x_base   ,
	          Y_BASE     = :y_base   ,
	          X_END      = :x_end    ,
	          Y_END      = :y_end    ,
	          XY_COUNT   = :xy_count ,
	          TEXT_COUNT = :text_count
	      WHERE FEAT_NUM = :feat_num ;
*/

{
#line 1119 "geomatch.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1119 "geomatch.sqc"
  sqlaaloc(2,7,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 1119 "geomatch.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 1119 "geomatch.sqc"
      sql_setdlist[0].sqldata = (void*)&x_base;
#line 1119 "geomatch.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1119 "geomatch.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 1119 "geomatch.sqc"
      sql_setdlist[1].sqldata = (void*)&y_base;
#line 1119 "geomatch.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1119 "geomatch.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 1119 "geomatch.sqc"
      sql_setdlist[2].sqldata = (void*)&x_end;
#line 1119 "geomatch.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1119 "geomatch.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 1119 "geomatch.sqc"
      sql_setdlist[3].sqldata = (void*)&y_end;
#line 1119 "geomatch.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1119 "geomatch.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 1119 "geomatch.sqc"
      sql_setdlist[4].sqldata = (void*)&xy_count;
#line 1119 "geomatch.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1119 "geomatch.sqc"
      sql_setdlist[5].sqltype = 496; sql_setdlist[5].sqllen = 4;
#line 1119 "geomatch.sqc"
      sql_setdlist[5].sqldata = (void*)&text_count;
#line 1119 "geomatch.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 1119 "geomatch.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 1119 "geomatch.sqc"
      sql_setdlist[6].sqldata = (void*)&feat_num;
#line 1119 "geomatch.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 1119 "geomatch.sqc"
      sqlasetdata(2,0,7,sql_setdlist,NULL,0L);
    }
#line 1119 "geomatch.sqc"
  sqlacall((unsigned short)24,1,2,0,0L);
#line 1119 "geomatch.sqc"
  sqlastop(0L);
}

#line 1119 "geomatch.sqc"

     
/*
EXEC SQL COMMIT WORK ;
*/

{
#line 1120 "geomatch.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1120 "geomatch.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 1120 "geomatch.sqc"
  sqlastop(0L);
}

#line 1120 "geomatch.sqc"
      //  CHECKERR ("UPDATE");


     // Delete OLD XY from Coordinates
     
/*
EXEC SQL  delete from COORDINATES where FEAT_NUM = :feat_num ;
*/

{
#line 1124 "geomatch.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1124 "geomatch.sqc"
  sqlaaloc(2,1,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 1124 "geomatch.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 1124 "geomatch.sqc"
      sql_setdlist[0].sqldata = (void*)&feat_num;
#line 1124 "geomatch.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1124 "geomatch.sqc"
      sqlasetdata(2,0,1,sql_setdlist,NULL,0L);
    }
#line 1124 "geomatch.sqc"
  sqlacall((unsigned short)24,2,2,0,0L);
#line 1124 "geomatch.sqc"
  sqlastop(0L);
}

#line 1124 "geomatch.sqc"

     
/*
EXEC SQL  COMMIT WORK ;
*/

{
#line 1125 "geomatch.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1125 "geomatch.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 1125 "geomatch.sqc"
  sqlastop(0L);
}

#line 1125 "geomatch.sqc"


     // Insert New XY into Coordinates (IF Any)
     if ( feat[i].xy_count > 0 )
        {
	 j   = 0 ;
	 seq = 0 ;

	 while( j < feat[i].xy_count )
	      {
		x_1 = x_2 = x_3 = x_4 = x_5 = x_6 = x_7 = x_8 = x_9 = x_10 = 0 ;
		y_1 = y_2 = y_3 = y_4 = y_5 = y_6 = y_7 = y_8 = y_9 = y_10 = 0 ;

		seq++ ;

                j++; if ( j <= feat[i].xy_count ) {x_1 =x[feat[i].xy+j]; y_1 =y[feat[i].xy+j];}
		j++; if ( j <= feat[i].xy_count ) {x_2 =x[feat[i].xy+j]; y_2 =y[feat[i].xy+j];}
		j++; if ( j <= feat[i].xy_count ) {x_3 =x[feat[i].xy+j]; y_3 =y[feat[i].xy+j];}
		j++; if ( j <= feat[i].xy_count ) {x_4 =x[feat[i].xy+j]; y_4 =y[feat[i].xy+j];}
		j++; if ( j <= feat[i].xy_count ) {x_5 =x[feat[i].xy+j]; y_5 =y[feat[i].xy+j];}
		j++; if ( j <= feat[i].xy_count ) {x_6 =x[feat[i].xy+j]; y_6 =y[feat[i].xy+j];}
		j++; if ( j <= feat[i].xy_count ) {x_7 =x[feat[i].xy+j]; y_7 =y[feat[i].xy+j];}
		j++; if ( j <= feat[i].xy_count ) {x_8 =x[feat[i].xy+j]; y_8 =y[feat[i].xy+j];}
		j++; if ( j <= feat[i].xy_count ) {x_9 =x[feat[i].xy+j]; y_9 =y[feat[i].xy+j];}
		j++; if ( j <= feat[i].xy_count ) {x_10=x[feat[i].xy+j]; y_10=y[feat[i].xy+j];}

		
/*
EXEC SQL INSERT INTO geoinfo.coordinates
			 VALUES (:feat_num ,
				 :seq ,
				 :x_1 , : y_1 ,
				 :x_2 , : y_2 ,
				 :x_3 , : y_3 ,
				 :x_4 , : y_4 ,
				 :x_5 , : y_5 ,
				 :x_6 , : y_6 ,
				 :x_7 , : y_7 ,
				 :x_8 , : y_8 ,
				 :x_9 , : y_9 ,
				 :x_10, : y_10  );
*/

{
#line 1163 "geomatch.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1163 "geomatch.sqc"
  sqlaaloc(2,22,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[22];
#line 1163 "geomatch.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 1163 "geomatch.sqc"
      sql_setdlist[0].sqldata = (void*)&feat_num;
#line 1163 "geomatch.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1163 "geomatch.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 1163 "geomatch.sqc"
      sql_setdlist[1].sqldata = (void*)&seq;
#line 1163 "geomatch.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1163 "geomatch.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 1163 "geomatch.sqc"
      sql_setdlist[2].sqldata = (void*)&x_1;
#line 1163 "geomatch.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1163 "geomatch.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 1163 "geomatch.sqc"
      sql_setdlist[3].sqldata = (void*)&y_1;
#line 1163 "geomatch.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1163 "geomatch.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 1163 "geomatch.sqc"
      sql_setdlist[4].sqldata = (void*)&x_2;
#line 1163 "geomatch.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1163 "geomatch.sqc"
      sql_setdlist[5].sqltype = 496; sql_setdlist[5].sqllen = 4;
#line 1163 "geomatch.sqc"
      sql_setdlist[5].sqldata = (void*)&y_2;
#line 1163 "geomatch.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 1163 "geomatch.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 1163 "geomatch.sqc"
      sql_setdlist[6].sqldata = (void*)&x_3;
#line 1163 "geomatch.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 1163 "geomatch.sqc"
      sql_setdlist[7].sqltype = 496; sql_setdlist[7].sqllen = 4;
#line 1163 "geomatch.sqc"
      sql_setdlist[7].sqldata = (void*)&y_3;
#line 1163 "geomatch.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 1163 "geomatch.sqc"
      sql_setdlist[8].sqltype = 496; sql_setdlist[8].sqllen = 4;
#line 1163 "geomatch.sqc"
      sql_setdlist[8].sqldata = (void*)&x_4;
#line 1163 "geomatch.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 1163 "geomatch.sqc"
      sql_setdlist[9].sqltype = 496; sql_setdlist[9].sqllen = 4;
#line 1163 "geomatch.sqc"
      sql_setdlist[9].sqldata = (void*)&y_4;
#line 1163 "geomatch.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 1163 "geomatch.sqc"
      sql_setdlist[10].sqltype = 496; sql_setdlist[10].sqllen = 4;
#line 1163 "geomatch.sqc"
      sql_setdlist[10].sqldata = (void*)&x_5;
#line 1163 "geomatch.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 1163 "geomatch.sqc"
      sql_setdlist[11].sqltype = 496; sql_setdlist[11].sqllen = 4;
#line 1163 "geomatch.sqc"
      sql_setdlist[11].sqldata = (void*)&y_5;
#line 1163 "geomatch.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 1163 "geomatch.sqc"
      sql_setdlist[12].sqltype = 496; sql_setdlist[12].sqllen = 4;
#line 1163 "geomatch.sqc"
      sql_setdlist[12].sqldata = (void*)&x_6;
#line 1163 "geomatch.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 1163 "geomatch.sqc"
      sql_setdlist[13].sqltype = 496; sql_setdlist[13].sqllen = 4;
#line 1163 "geomatch.sqc"
      sql_setdlist[13].sqldata = (void*)&y_6;
#line 1163 "geomatch.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 1163 "geomatch.sqc"
      sql_setdlist[14].sqltype = 496; sql_setdlist[14].sqllen = 4;
#line 1163 "geomatch.sqc"
      sql_setdlist[14].sqldata = (void*)&x_7;
#line 1163 "geomatch.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 1163 "geomatch.sqc"
      sql_setdlist[15].sqltype = 496; sql_setdlist[15].sqllen = 4;
#line 1163 "geomatch.sqc"
      sql_setdlist[15].sqldata = (void*)&y_7;
#line 1163 "geomatch.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 1163 "geomatch.sqc"
      sql_setdlist[16].sqltype = 496; sql_setdlist[16].sqllen = 4;
#line 1163 "geomatch.sqc"
      sql_setdlist[16].sqldata = (void*)&x_8;
#line 1163 "geomatch.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 1163 "geomatch.sqc"
      sql_setdlist[17].sqltype = 496; sql_setdlist[17].sqllen = 4;
#line 1163 "geomatch.sqc"
      sql_setdlist[17].sqldata = (void*)&y_8;
#line 1163 "geomatch.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 1163 "geomatch.sqc"
      sql_setdlist[18].sqltype = 496; sql_setdlist[18].sqllen = 4;
#line 1163 "geomatch.sqc"
      sql_setdlist[18].sqldata = (void*)&x_9;
#line 1163 "geomatch.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 1163 "geomatch.sqc"
      sql_setdlist[19].sqltype = 496; sql_setdlist[19].sqllen = 4;
#line 1163 "geomatch.sqc"
      sql_setdlist[19].sqldata = (void*)&y_9;
#line 1163 "geomatch.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 1163 "geomatch.sqc"
      sql_setdlist[20].sqltype = 496; sql_setdlist[20].sqllen = 4;
#line 1163 "geomatch.sqc"
      sql_setdlist[20].sqldata = (void*)&x_10;
#line 1163 "geomatch.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 1163 "geomatch.sqc"
      sql_setdlist[21].sqltype = 496; sql_setdlist[21].sqllen = 4;
#line 1163 "geomatch.sqc"
      sql_setdlist[21].sqldata = (void*)&y_10;
#line 1163 "geomatch.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 1163 "geomatch.sqc"
      sqlasetdata(2,0,22,sql_setdlist,NULL,0L);
    }
#line 1163 "geomatch.sqc"
  sqlacall((unsigned short)24,3,2,0,0L);
#line 1163 "geomatch.sqc"
  sqlastop(0L);
}

#line 1163 "geomatch.sqc"


		// CHECKERR ("INSERT INTO");
	       }
	 }

    } /* end of update feat_1 in DBASE */


 //------------------------------------------------------
 // Delete feat_2 from DB  & Memorey
 //------------------------------------------------------
 if ( db_opened[0] == 'Y' )
    {
     // Delete feat_2 from DB (Features, Coordinates, Text)
     feat_num =  feat[ii].num ;
     
/*
EXEC SQL  delete from features where FEAT_NUM = :feat_num ;
*/

{
#line 1179 "geomatch.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1179 "geomatch.sqc"
  sqlaaloc(2,1,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 1179 "geomatch.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 1179 "geomatch.sqc"
      sql_setdlist[0].sqldata = (void*)&feat_num;
#line 1179 "geomatch.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1179 "geomatch.sqc"
      sqlasetdata(2,0,1,sql_setdlist,NULL,0L);
    }
#line 1179 "geomatch.sqc"
  sqlacall((unsigned short)24,4,2,0,0L);
#line 1179 "geomatch.sqc"
  sqlastop(0L);
}

#line 1179 "geomatch.sqc"

     
/*
EXEC SQL  COMMIT WORK ;
*/

{
#line 1180 "geomatch.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1180 "geomatch.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 1180 "geomatch.sqc"
  sqlastop(0L);
}

#line 1180 "geomatch.sqc"

    }

 // Delete feat_2 from Memorey (Move last feature in place of feat_2)
 feat[ii].num            = feat[feat_count].num           ;
 strcpy ( feat[ii].code, feat[feat_count].code )          ;
 feat[ii].type           = feat[feat_count].type          ;
 feat[ii].layer          = feat[feat_count].layer         ;
 feat[ii].network        = feat[feat_count].network       ;
 feat[ii].scale_range[0] = feat[feat_count].scale_range[0];
 feat[ii].scale_range[1] = feat[feat_count].scale_range[1];
 feat[ii].scale_range[2] = feat[feat_count].scale_range[2];
 feat[ii].scale_range[3] = feat[feat_count].scale_range[3];
 feat[ii].scale_range[4] = feat[feat_count].scale_range[4];
 feat[ii].displayed[0]   = feat[feat_count].displayed[0]  ;
 feat[ii].selectble[0]   = feat[feat_count].selectble[0]  ;
 feat[ii].has_attrib[0]  = feat[feat_count].has_attrib[0] ;
 feat[ii].has_text[0]    = feat[feat_count].has_text[0]   ;
 feat[ii].color          = feat[feat_count].color         ;
 feat[ii].linetype       = feat[feat_count].linetype      ;
 feat[ii].linewidth      = feat[feat_count].linewidth     ;
 feat[ii].xbase          = feat[feat_count].xbase         ;
 feat[ii].ybase          = feat[feat_count].ybase         ;
 feat[ii].xend           = feat[feat_count].xend          ;
 feat[ii].yend           = feat[feat_count].yend          ;
 feat[ii].xy_count       = feat[feat_count].xy_count      ;
 feat[ii].symb_num       = feat[feat_count].symb_num      ;
 feat[ii].symb_size      = feat[feat_count].symb_size     ;
 feat[ii].symb_angle     = feat[feat_count].symb_angle    ;
 feat[ii].text_count     = feat[feat_count].text_count    ;
 feat[ii].xy             = feat[feat_count].xy            ;
 feat[ii].text           = feat[feat_count].text          ;
 feat_count-- ;


 //----------------------------
 // Update feat_1 in DB (TEXT)
 //----------------------------
 if ( db_opened[0] == 'Y' )
    {
     // Delete OLD Text from TEXT  for feat_1
     feat_num =  feat[i].num ;
     
/*
EXEC SQL  delete from TEXT where FEAT_NUM = :feat_num ;
*/

{
#line 1222 "geomatch.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1222 "geomatch.sqc"
  sqlaaloc(2,1,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 1222 "geomatch.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 1222 "geomatch.sqc"
      sql_setdlist[0].sqldata = (void*)&feat_num;
#line 1222 "geomatch.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1222 "geomatch.sqc"
      sqlasetdata(2,0,1,sql_setdlist,NULL,0L);
    }
#line 1222 "geomatch.sqc"
  sqlacall((unsigned short)24,5,2,0,0L);
#line 1222 "geomatch.sqc"
  sqlastop(0L);
}

#line 1222 "geomatch.sqc"

     
/*
EXEC SQL  COMMIT WORK ;
*/

{
#line 1223 "geomatch.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1223 "geomatch.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 1223 "geomatch.sqc"
  sqlastop(0L);
}

#line 1223 "geomatch.sqc"


     // Insert New Text into TEXT for feat_1
     if  ( feat[i].has_text[0] == 'Y' )
	 {
	   for ( j=1 ; j<=feat[i].text_count ; j++ )
	       {
		text_x      = text[feat[i].text+j].x              ;
		text_y      = text[feat[i].text+j].y              ;
		text_size   = text[feat[i].text+j].size           ;
		text_angle  = text[feat[i].text+j].angle          ;
		text_just   = text[feat[i].text+j].just           ;
		text_font   = text[feat[i].text+j].font           ;
		strcpy(textstring,text[feat[i].text+j].string) ;

		
/*
EXEC SQL INSERT INTO geoinfo.text
			 VALUES (:feat_num   ,
				 :text_x     ,
				 :text_y     ,
				 :text_size  ,
				 :text_angle ,
				 :text_just  ,
				 :text_font  ,
				 :textstring );
*/

{
#line 1246 "geomatch.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1246 "geomatch.sqc"
  sqlaaloc(2,8,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[8];
#line 1246 "geomatch.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 1246 "geomatch.sqc"
      sql_setdlist[0].sqldata = (void*)&feat_num;
#line 1246 "geomatch.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1246 "geomatch.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 1246 "geomatch.sqc"
      sql_setdlist[1].sqldata = (void*)&text_x;
#line 1246 "geomatch.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1246 "geomatch.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 1246 "geomatch.sqc"
      sql_setdlist[2].sqldata = (void*)&text_y;
#line 1246 "geomatch.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1246 "geomatch.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 1246 "geomatch.sqc"
      sql_setdlist[3].sqldata = (void*)&text_size;
#line 1246 "geomatch.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1246 "geomatch.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 1246 "geomatch.sqc"
      sql_setdlist[4].sqldata = (void*)&text_angle;
#line 1246 "geomatch.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1246 "geomatch.sqc"
      sql_setdlist[5].sqltype = 500; sql_setdlist[5].sqllen = 2;
#line 1246 "geomatch.sqc"
      sql_setdlist[5].sqldata = (void*)&text_just;
#line 1246 "geomatch.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 1246 "geomatch.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 1246 "geomatch.sqc"
      sql_setdlist[6].sqldata = (void*)&text_font;
#line 1246 "geomatch.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 1246 "geomatch.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 51;
#line 1246 "geomatch.sqc"
      sql_setdlist[7].sqldata = (void*)textstring;
#line 1246 "geomatch.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 1246 "geomatch.sqc"
      sqlasetdata(2,0,8,sql_setdlist,NULL,0L);
    }
#line 1246 "geomatch.sqc"
  sqlacall((unsigned short)24,6,2,0,0L);
#line 1246 "geomatch.sqc"
  sqlastop(0L);
}

#line 1246 "geomatch.sqc"


		// CHECKERR ("INSERT INTO");
	      }
	 }

    }

}
/* -------------------------------------------------------------------*/
/*                       split_feature()                              */
/* -------------------------------------------------------------------*/
split_feature(int feat_parm, double x_parm , double y_parm)
{
 int    i          ;
 int    ii         ;
 int    iii        ;
 double x_line     ;
 double y_line     ;
 double x_mouse    ;
 double y_mouse    ;
 double x_adjusted ;
 double y_adjusted ;


 i       = feat_parm ;
 x_mouse = x_parm    ;
 y_mouse = y_parm    ;


 for ( ii=0 ; ii<=(feat[i].xy_count+1) ; ii++ )
     {
      switch (ii)
             {
	      case 0:
  	        x1_db = feat[i].xbase ;
		y1_db = feat[i].ybase ;
		break ;

	      default:
		if ( ii <= feat[i].xy_count )
		   {
		    x2_db = x [feat[i].xy+ii] ;
		    y2_db = y [feat[i].xy+ii] ;
		   }
		else
		   {
		    x2_db = feat[i].xend ;
		    y2_db = feat[i].yend ;
		   }

		/* Calculate Enclosure Box Min-Max Values */
		if ( x1_db < x2_db )
		   {
		    x_small = x1_db - tolerance ;
		    x_big   = x2_db + tolerance ;
		   }
		else
		   {
		    x_small = x2_db - tolerance ;
		    x_big   = x1_db + tolerance ;
		   }

		if ( y1_db < y2_db )
		   {
		    y_small = y1_db - tolerance ;
		    y_big   = y2_db + tolerance ;
		   }
	        else
		   {
		    y_small = y2_db - tolerance ;
		    y_big   = y1_db + tolerance ;
		   }


		/* IF Mouse inside segment Enclosure Box, Try to Correlate */
		if ((x_mouse>x_small)&&(x_mouse<x_big)&&(y_mouse>y_small)&&(y_mouse<y_big))
		   {
		    // Cal. Prependicular Distance between Mouse and line segment
		    if ( y1_db == y2_db )  /* hz segment */
		       {
		        distance = abs (y_mouse - y1_db) ;
		       }
		    else
		    if ( x1_db == x2_db )  /* vl segment */
		       {
		        distance = abs (x_mouse - x1_db) ;
		       }
		    else
		       {                   /* segment with angle */
		        angle    = atan2 ((y2_db - y1_db),(x2_db - x1_db));
		        b        = tan (angle) ;

		        a        = y1_db - (b * x1_db) ;
		        x_line   = ( y_mouse - a ) / b ;
		        x_diff   = abs ( x_line - x_mouse )    ;
		        distance = abs ( x_diff * sin(angle) ) ;
                       }



		    if ( distance <= tolerance )
		       {
		        /* cal. xy coord of Adjuseted point */
		        if ( y1_db == y2_db )
		           {
		            x_adjusted = x_mouse ;
		            y_adjusted = y1_db   ;
		           }
		        else
		        if ( x1_db == x2_db )
		           {
		            x_adjusted = x1_db   ;
		            y_adjusted = y_mouse ;
		           }
		        else
		           {
		            x_adjusted = ( y_mouse - a ) / b ;
		            y_adjusted = ( x_mouse * b ) + a ;

    	                    if ( x_adjusted < x_mouse )
    	                       { x_adjusted = x_mouse - abs (distance * sin(angle)) ; }
       	                    else
    	                       { x_adjusted = x_mouse + abs (distance * sin(angle)) ; }

    	                    if ( y_adjusted < y_mouse )
    	                       { y_adjusted = y_mouse - abs (distance * cos(angle)) ; }
                            else
                               { y_adjusted = y_mouse + abs (distance * cos(angle)) ; }
                           }


    	                /* Create 2nd feature */
    	                feat_count++ ;
	                xy_index = xy_LAST ;

	                feat[feat_count].num  = feat[feat_count-1].num + 1         ;
	                strcpy ( feat[feat_count].code , feat[i].code )            ;
	                feat[feat_count].type          = feat[i].type              ;
	                feat[feat_count].layer         = feat[i].layer             ;
	                feat[feat_count].network       = feat[i].network           ;
	                feat[feat_count].scale_range[0]= feat[i].scale_range[0]    ;
	                feat[feat_count].scale_range[1]= feat[i].scale_range[1]    ;
	                feat[feat_count].scale_range[2]= feat[i].scale_range[2]    ;
	                feat[feat_count].scale_range[3]= feat[i].scale_range[3]    ;
	                feat[feat_count].scale_range[4]= feat[i].scale_range[4]    ;
	                feat[feat_count].displayed[0]  = feat[i].displayed[0]      ;
	                feat[feat_count].selectble[0]  = feat[i].selectble[0]      ;
	                feat[feat_count].has_attrib[0] = feat[i].has_attrib[0]     ;
	                feat[feat_count].has_text[0]   = feat[i].has_text[0]       ;
	                feat[feat_count].color         = feat[i].color             ;
	                feat[feat_count].linetype      = feat[i].linetype          ;
	                feat[feat_count].linewidth     = feat[i].linewidth         ;
	                feat[feat_count].xbase         = x_adjusted                ;
	                feat[feat_count].ybase         = y_adjusted                ;
	                feat[feat_count].xy            = xy_index                  ;
                        feat[feat_count].xend          = feat[i].xend              ;
                        feat[feat_count].yend          = feat[i].yend              ;
                        feat[feat_count].xy_count      = feat[i].xy_count - ii + 1 ;

                        iii = ii ;
                        j   = 0  ;
	                for ( j=1; j<=feat[feat_count].xy_count; j++ )
	                    {
                             x[xy_index+j] = x[feat[i].xy+iii];
	                     y[xy_index+j] = y[feat[i].xy+iii];
	                     iii++ ;
	                    }
                        xy_LAST = xy_LAST + j ;


    	                /* Modify 1st feature */
                        feat[i].xend     = x_adjusted ;
                        feat[i].yend     = y_adjusted ;
                        feat[i].xy_count = ii - 1 ;

                        highlight_feature (feat_count);
  		        return ;
  		       }
                   }

	        x1_db = x2_db ;
	        y1_db = y2_db ;
	        break ;
            }
    } /* Main loop */

}
