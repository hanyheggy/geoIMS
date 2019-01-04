static char sqla_program_id[162] = 
{
 42,0,65,68,65,75,65,73,71,69,79,84,82,65,67,69,122,65,52,75,
 79,101,66,87,48,49,49,49,49,32,50,32,8,0,71,69,79,73,78,70,
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


static const short sqlIsLiteral   = SQL_IS_LITERAL;
static const short sqlIsInputHvar = SQL_IS_INPUT_HVAR;


#line 1 "geotrace.sqc"
/*------------------------------------------------------------------------*/
/*              geoINFO/6000  Trace Network ( geotrace.sqc )              */
/*------------------------------------------------------------------------*/

/*------------------------------------------------------------------------*/
/*                          Standard Include Files                        */
/*------------------------------------------------------------------------*/
#include "include/geoIMSextern.h"

#include <sqlenv.h>
#include <sqlda.h>

// #define  CHECKERR(CE_STR)  if(check_error (CE_STR,&sqlca) != 0) printf("error");

/*
EXEC SQL INCLUDE SQLCA;
*/

/* SQL Communication Area - SQLCA - structures and constants */
#include "sqlca.h"
struct sqlca sqlca;


#line 14 "geotrace.sqc"


/*------------------------------------------------------------------------*/
/*                           Functions Prototypes                         */
/*------------------------------------------------------------------------*/
void get_connected_nan();


/*------------------------------------------------------------------------*/
/*                   Global Variable Definition                           */
/*------------------------------------------------------------------------*/

int   k                  ;
int   found              ;
int   stack_count        ;
int   conn_stack [10000] ;



/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 32 "geotrace.sqc"

   long    number              ;
   long    conn_feat           ;
   long    conn_feat1          ;
   long    conn_feat2          ;
   long    conn_feat3          ;
   long    weight              ;
   char    grid    [13]        ;
   char    code    [13]        ;
   char    code1   [13]        ;

   long    feat_num            ;
   char    feat_code[13]       ;
   long    type                ;
   long    layer               ;
   long    network             ;
   char    scale_range [6]     ;
   char    displayed   [1]     ;
   char    selectable  [1]     ;
   char    has_attrib  [1]     ;
   char    has_text    [1]     ;
   char    rdisplayed  [2]     ;
   char    rselectable [2]     ;
   char    rhas_attrib [2]     ;
   char    rhas_text   [2]     ;
   short   feat_color          ;
   short   feat_linetype       ;
   short   feat_linewidth      ;
   long    x_min_feat          ;
   long    y_min_feat          ;
   long    x_max_feat          ;
   long    y_max_feat          ;
   long    x_base              ;
   long    y_base              ;
   long    x_end               ;
   long    y_end               ;
   long    xy_count            ;
   long    symb_num            ;
   long    symb_size           ;
   long    symb_angle          ;
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

#line 101 "geotrace.sqc"



/*------------------------------------------------------------------------*/
/*                              trace_net()                               */
/*------------------------------------------------------------------------*/

void trace_net(long start_feat, char *term_feat)
{
 i = 1           ;
 conn_count  = 0 ;
 stack_count = 0 ;


 conn_stack[++stack_count] = start_feat ;

 while ( i <= stack_count )
       {
	found = 0 ;

	for ( j=1 ; j <= conn_count ; j++ )
	    {
	     if ( conn_stack[i] == conn_list[j] )  { found = 1 ; break ; }
	    }

	if ( found == 0 )
	   {
	    conn_list[++conn_count] = conn_stack[i] ;
	
	    get_connected_nan(conn_stack[i],term_feat);
	   }

	i++;
       }

 /*
 printf ("\n conn_count  = %d",conn_count  );
 for ( i=1 ; i<= conn_count ; i++ )
     { printf ("\n feat[%d] = %d",i,conn_list[i] ); }  */

}
/*---------------------------------------------------------------------------*/
/*                            append_net()                                   */
/*---------------------------------------------------------------------------*/

void append_net(long start_feat, char *term_feat)
{
 i = 1 ;

 conn_stack[++stack_count] = start_feat ;

 while ( i <= stack_count )
       {
	found = 0 ;

	for ( j=1 ; j <= conn_count ; j++ )
	    {
	     if ( conn_stack[i] == conn_list[j] )  { found = 1 ; break ; }
	    }

	if ( found == 0 )
	   {
	    conn_list[++conn_count] = conn_stack[i] ;
	    get_connected_nan(conn_stack[i],term_feat);
	   }

	i++;
       }

}
/*------------------------------------------------------------------------*/
/*                        get_connected_nan()                             */
/*------------------------------------------------------------------------*/

void get_connected_nan(int feat_num,char *term_feat)
{

 
/*
EXEC SQL DECLARE nan1  CURSOR FOR
	  SELECT  S_NODE ,
		  ARC    ,
		  E_NODE
	  FROM    CONNECTIVITY
	  WHERE   S_NODE = :number  OR  E_NODE = :number
	  FOR     READ ONLY ;
*/

#line 184 "geotrace.sqc"



 number = feat_num ;

 
/*
EXEC SQL SELECT FEAT_CODE , TYPE
	  INTO   :code1    , :type
	  FROM   FEATURES
	  WHERE  FEAT_NUM = :number  ;
*/

{
#line 192 "geotrace.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 192 "geotrace.sqc"
  sqlaaloc(2,1,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 192 "geotrace.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 192 "geotrace.sqc"
      sql_setdlist[0].sqldata = (void*)&number;
#line 192 "geotrace.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 192 "geotrace.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 192 "geotrace.sqc"
  sqlaaloc(3,2,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 192 "geotrace.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 13;
#line 192 "geotrace.sqc"
      sql_setdlist[0].sqldata = (void*)code1;
#line 192 "geotrace.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 192 "geotrace.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 192 "geotrace.sqc"
      sql_setdlist[1].sqldata = (void*)&type;
#line 192 "geotrace.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 192 "geotrace.sqc"
      sqlasetdata(3,0,2,sql_setdlist,0L,0L);
    }
#line 192 "geotrace.sqc"
  sqlacall((unsigned short)24,2,2,3,0L);
#line 192 "geotrace.sqc"
  sqlastop(0L);
}

#line 192 "geotrace.sqc"


 sscanf (code1,"%s",code) ;

 if (SQLCODE != 0)
    {
     printf("\nERROR : get_connected_nan [SQLCODE] = %d\n",SQLCODE);
     return;
    }


 if ( (type == 1) && (strcmp(code,term_feat) != 0) )
    {
     
/*
EXEC SQL OPEN  nan1 ;
*/

{
#line 205 "geotrace.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 205 "geotrace.sqc"
  sqlaaloc(2,2,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 205 "geotrace.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 205 "geotrace.sqc"
      sql_setdlist[0].sqldata = (void*)&number;
#line 205 "geotrace.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 205 "geotrace.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 205 "geotrace.sqc"
      sql_setdlist[1].sqldata = (void*)&number;
#line 205 "geotrace.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 205 "geotrace.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 205 "geotrace.sqc"
  sqlacall((unsigned short)26,1,2,0,0L);
#line 205 "geotrace.sqc"
  sqlastop(0L);
}

#line 205 "geotrace.sqc"
     /* CHECKERR ("OPEN CURSOR"); */

     do {
	 
/*
EXEC SQL FETCH nan1 INTO :conn_feat1, :conn_feat2, :conn_feat3 ;
*/

{
#line 208 "geotrace.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 208 "geotrace.sqc"
  sqlaaloc(3,3,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 208 "geotrace.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 208 "geotrace.sqc"
      sql_setdlist[0].sqldata = (void*)&conn_feat1;
#line 208 "geotrace.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 208 "geotrace.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 208 "geotrace.sqc"
      sql_setdlist[1].sqldata = (void*)&conn_feat2;
#line 208 "geotrace.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 208 "geotrace.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 208 "geotrace.sqc"
      sql_setdlist[2].sqldata = (void*)&conn_feat3;
#line 208 "geotrace.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 208 "geotrace.sqc"
      sqlasetdata(3,0,3,sql_setdlist,0L,0L);
    }
#line 208 "geotrace.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 208 "geotrace.sqc"
  sqlastop(0L);
}

#line 208 "geotrace.sqc"


	 if (SQLCODE != 0) break ;
	 conn_stack[++stack_count] = conn_feat1 ;
	 conn_stack[++stack_count] = conn_feat2 ;
	 conn_stack[++stack_count] = conn_feat3 ;
	 /*
	 printf ("\n CONN ROW %d %d %d",conn_feat1,conn_feat2,conn_feat3);
	 */
	} while(1);
     
/*
EXEC SQL CLOSE nan1  ;
*/

{
#line 218 "geotrace.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 218 "geotrace.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 218 "geotrace.sqc"
  sqlastop(0L);
}

#line 218 "geotrace.sqc"

    }
else
 if ( (type == 2) && (strcmp(code,term_feat) != 0) )
    {
     
/*
EXEC SQL SELECT S_NODE      , E_NODE
	      INTO   :conn_feat1 , :conn_feat3
	      FROM   CONNECTIVITY
	      WHERE  ARC = :number ;
*/

{
#line 226 "geotrace.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 226 "geotrace.sqc"
  sqlaaloc(2,1,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 226 "geotrace.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 226 "geotrace.sqc"
      sql_setdlist[0].sqldata = (void*)&number;
#line 226 "geotrace.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 226 "geotrace.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 226 "geotrace.sqc"
  sqlaaloc(3,2,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 226 "geotrace.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 226 "geotrace.sqc"
      sql_setdlist[0].sqldata = (void*)&conn_feat1;
#line 226 "geotrace.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 226 "geotrace.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 226 "geotrace.sqc"
      sql_setdlist[1].sqldata = (void*)&conn_feat3;
#line 226 "geotrace.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 226 "geotrace.sqc"
      sqlasetdata(3,0,2,sql_setdlist,0L,0L);
    }
#line 226 "geotrace.sqc"
  sqlacall((unsigned short)24,3,2,3,0L);
#line 226 "geotrace.sqc"
  sqlastop(0L);
}

#line 226 "geotrace.sqc"


     if (SQLCODE != 0) return ;
     conn_stack[++stack_count] = conn_feat1 ;
     conn_stack[++stack_count] = conn_feat3 ;
     /*
     printf ("\n CONN ROW %d %d %d",conn_feat1,number,conn_feat3);
     */
    }

 return ;
}
/*------------------------------------------------------------------------*/
/*                          network_ret()                                 */
/*------------------------------------------------------------------------*/

void network_ret(char *grid,char *feeder)
{
 i = 1           ;
 conn_count  = 0 ;
 stack_count = 0 ;


 strcpy(code,grid);                           /* Get Grid feat_num     */
 
/*
EXEC SQL SELECT feat_num
	  INTO   :number
	  FROM   grid
	  WHERE  grid_id = :grid    ;
*/

{
#line 253 "geotrace.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 253 "geotrace.sqc"
  sqlaaloc(2,1,7,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 253 "geotrace.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 13;
#line 253 "geotrace.sqc"
      sql_setdlist[0].sqldata = (void*)grid;
#line 253 "geotrace.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 253 "geotrace.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 253 "geotrace.sqc"
  sqlaaloc(3,1,8,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 253 "geotrace.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 253 "geotrace.sqc"
      sql_setdlist[0].sqldata = (void*)&number;
#line 253 "geotrace.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 253 "geotrace.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 253 "geotrace.sqc"
  sqlacall((unsigned short)24,4,2,3,0L);
#line 253 "geotrace.sqc"
  sqlastop(0L);
}

#line 253 "geotrace.sqc"


 
/*
EXEC SQL DECLARE t9 CURSOR FOR               /- Get Feeder's feat_num  -/
	  SELECT  ARC                         /- Connected to GRID      -/
	  FROM    connectivity
	  WHERE   S_NODE  = :number
	  FOR     READ ONLY ;
*/

#line 259 "geotrace.sqc"


 
/*
EXEC SQL OPEN  t9 ;
*/

{
#line 261 "geotrace.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 261 "geotrace.sqc"
  sqlaaloc(2,1,9,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 261 "geotrace.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 261 "geotrace.sqc"
      sql_setdlist[0].sqldata = (void*)&number;
#line 261 "geotrace.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 261 "geotrace.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 261 "geotrace.sqc"
  sqlacall((unsigned short)26,5,2,0,0L);
#line 261 "geotrace.sqc"
  sqlastop(0L);
}

#line 261 "geotrace.sqc"

 do {
     
/*
EXEC SQL FETCH t9  INTO :conn_feat ;
*/

{
#line 263 "geotrace.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 263 "geotrace.sqc"
  sqlaaloc(3,1,10,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 263 "geotrace.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 263 "geotrace.sqc"
      sql_setdlist[0].sqldata = (void*)&conn_feat;
#line 263 "geotrace.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 263 "geotrace.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 263 "geotrace.sqc"
  sqlacall((unsigned short)25,5,0,3,0L);
#line 263 "geotrace.sqc"
  sqlastop(0L);
}

#line 263 "geotrace.sqc"

     if (SQLCODE != 0) break ;
     conn_stack[++stack_count] = conn_feat ;
    } while(1);
 
/*
EXEC SQL CLOSE t9 ;
*/

{
#line 267 "geotrace.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 267 "geotrace.sqc"
  sqlacall((unsigned short)20,5,0,0,0L);
#line 267 "geotrace.sqc"
  sqlastop(0L);
}

#line 267 "geotrace.sqc"




 for ( i=1 ; i<=stack_count ; i++ )
     {
      number = conn_stack[i] ;
      
/*
EXEC SQL SELECT FEEDER_NUM
	       INTO   :code1
	       FROM   MVFEEDER
	       WHERE  FEAT_NUM = :number ;
*/

{
#line 277 "geotrace.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 277 "geotrace.sqc"
  sqlaaloc(2,1,11,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 277 "geotrace.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 277 "geotrace.sqc"
      sql_setdlist[0].sqldata = (void*)&number;
#line 277 "geotrace.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 277 "geotrace.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 277 "geotrace.sqc"
  sqlaaloc(3,1,12,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 277 "geotrace.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 13;
#line 277 "geotrace.sqc"
      sql_setdlist[0].sqldata = (void*)code1;
#line 277 "geotrace.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 277 "geotrace.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 277 "geotrace.sqc"
  sqlacall((unsigned short)24,6,2,3,0L);
#line 277 "geotrace.sqc"
  sqlastop(0L);
}

#line 277 "geotrace.sqc"

      sscanf (code1,"%s",code) ;

      /*  one feeder
      trace_net(number,"GRIDSTN") ; // one grid //
      */
      if ( strcmp (code,feeder) == 0)
	 {
	  /* printf("\nFEEDER feat_num %d",number); */
	  trace_net(number,"GRIDSTN") ;
	 }
     }


 printf("\nINFO  : Retreiving from Database ...");

 
/*
EXEC SQL DECLARE  NR_COORD  CURSOR FOR
	  SELECT   seq,
		   x_1 , y_1,
		   x_2 , y_2,
		   x_3 , y_3,
		   x_4 , y_4,
		   x_5 , y_5,
		   x_6 , y_6,
		   x_7 , y_7,
		   x_8 , y_8,
		   x_9 , y_9,
		   x_10, y_10
	  FROM     coordinates
	  WHERE    feat_num = :feat_num
	  FOR      READ ONLY;
*/

#line 307 "geotrace.sqc"

 // CHECKERR ("DECLARE CURSOR");

 
/*
EXEC SQL DECLARE TEXT CURSOR FOR
	  SELECT   x1     ,
		   y1     ,
		   size   ,
		   angle  ,
		   just   ,
		   font   ,
		   string
	  FROM     text
	  WHERE    feat_num = :feat_num
	  FOR      READ ONLY;
*/

#line 320 "geotrace.sqc"

 // CHECKERR ("DECLARE CURSOR");


 i = 0          ;
 xy_index   = 0 ;
 text_index = 0 ;

 for ( k=1 ; k<=conn_count ; k++ )
     {
      number = conn_list[k] ;
      
/*
EXEC SQL SELECT  feat_num,
		       feat_code,
		       type,
		       layer,
		       network,
		       scale_range,
		       displayed,
		       selectable,
		       has_attrib,
		       has_text,
		       color,
		       line_type,
		       line_width,
		       x_base,
		       y_base,
		       x_end,
		       y_end,
		       xy_count,
		       symb_num,
		       symb_size,
		       symb_angle,
		       text_count
	       INTO    :feat_num,
		       :feat_code,
		       :type,
		       :layer,
		       :network,
		       :scale_range,
		       :rdisplayed,
		       :rselectable,
		       :rhas_attrib,
		       :rhas_text,
		       :feat_color,
		       :feat_linetype,
		       :feat_linewidth,
		       :x_base,
		       :y_base,
		       :x_end,
		       :y_end,
		       :xy_count,
		       :symb_num,
		       :symb_size,
		       :symb_angle,
		       :text_count
	       FROM    features
	       WHERE   feat_num = :number ;
*/

{
#line 376 "geotrace.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 376 "geotrace.sqc"
  sqlaaloc(2,1,13,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 376 "geotrace.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 376 "geotrace.sqc"
      sql_setdlist[0].sqldata = (void*)&number;
#line 376 "geotrace.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 376 "geotrace.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 376 "geotrace.sqc"
  sqlaaloc(3,22,14,0L);
    {
      struct sqla_setdata_list sql_setdlist[22];
#line 376 "geotrace.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 376 "geotrace.sqc"
      sql_setdlist[0].sqldata = (void*)&feat_num;
#line 376 "geotrace.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 376 "geotrace.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 13;
#line 376 "geotrace.sqc"
      sql_setdlist[1].sqldata = (void*)feat_code;
#line 376 "geotrace.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 376 "geotrace.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 376 "geotrace.sqc"
      sql_setdlist[2].sqldata = (void*)&type;
#line 376 "geotrace.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 376 "geotrace.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 376 "geotrace.sqc"
      sql_setdlist[3].sqldata = (void*)&layer;
#line 376 "geotrace.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 376 "geotrace.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 376 "geotrace.sqc"
      sql_setdlist[4].sqldata = (void*)&network;
#line 376 "geotrace.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 376 "geotrace.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 6;
#line 376 "geotrace.sqc"
      sql_setdlist[5].sqldata = (void*)scale_range;
#line 376 "geotrace.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 376 "geotrace.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 2;
#line 376 "geotrace.sqc"
      sql_setdlist[6].sqldata = (void*)rdisplayed;
#line 376 "geotrace.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 376 "geotrace.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 2;
#line 376 "geotrace.sqc"
      sql_setdlist[7].sqldata = (void*)rselectable;
#line 376 "geotrace.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 376 "geotrace.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 2;
#line 376 "geotrace.sqc"
      sql_setdlist[8].sqldata = (void*)rhas_attrib;
#line 376 "geotrace.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 376 "geotrace.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 2;
#line 376 "geotrace.sqc"
      sql_setdlist[9].sqldata = (void*)rhas_text;
#line 376 "geotrace.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 376 "geotrace.sqc"
      sql_setdlist[10].sqltype = 500; sql_setdlist[10].sqllen = 2;
#line 376 "geotrace.sqc"
      sql_setdlist[10].sqldata = (void*)&feat_color;
#line 376 "geotrace.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 376 "geotrace.sqc"
      sql_setdlist[11].sqltype = 500; sql_setdlist[11].sqllen = 2;
#line 376 "geotrace.sqc"
      sql_setdlist[11].sqldata = (void*)&feat_linetype;
#line 376 "geotrace.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 376 "geotrace.sqc"
      sql_setdlist[12].sqltype = 500; sql_setdlist[12].sqllen = 2;
#line 376 "geotrace.sqc"
      sql_setdlist[12].sqldata = (void*)&feat_linewidth;
#line 376 "geotrace.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 376 "geotrace.sqc"
      sql_setdlist[13].sqltype = 496; sql_setdlist[13].sqllen = 4;
#line 376 "geotrace.sqc"
      sql_setdlist[13].sqldata = (void*)&x_base;
#line 376 "geotrace.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 376 "geotrace.sqc"
      sql_setdlist[14].sqltype = 496; sql_setdlist[14].sqllen = 4;
#line 376 "geotrace.sqc"
      sql_setdlist[14].sqldata = (void*)&y_base;
#line 376 "geotrace.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 376 "geotrace.sqc"
      sql_setdlist[15].sqltype = 496; sql_setdlist[15].sqllen = 4;
#line 376 "geotrace.sqc"
      sql_setdlist[15].sqldata = (void*)&x_end;
#line 376 "geotrace.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 376 "geotrace.sqc"
      sql_setdlist[16].sqltype = 496; sql_setdlist[16].sqllen = 4;
#line 376 "geotrace.sqc"
      sql_setdlist[16].sqldata = (void*)&y_end;
#line 376 "geotrace.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 376 "geotrace.sqc"
      sql_setdlist[17].sqltype = 496; sql_setdlist[17].sqllen = 4;
#line 376 "geotrace.sqc"
      sql_setdlist[17].sqldata = (void*)&xy_count;
#line 376 "geotrace.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 376 "geotrace.sqc"
      sql_setdlist[18].sqltype = 496; sql_setdlist[18].sqllen = 4;
#line 376 "geotrace.sqc"
      sql_setdlist[18].sqldata = (void*)&symb_num;
#line 376 "geotrace.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 376 "geotrace.sqc"
      sql_setdlist[19].sqltype = 496; sql_setdlist[19].sqllen = 4;
#line 376 "geotrace.sqc"
      sql_setdlist[19].sqldata = (void*)&symb_size;
#line 376 "geotrace.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 376 "geotrace.sqc"
      sql_setdlist[20].sqltype = 496; sql_setdlist[20].sqllen = 4;
#line 376 "geotrace.sqc"
      sql_setdlist[20].sqldata = (void*)&symb_angle;
#line 376 "geotrace.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 376 "geotrace.sqc"
      sql_setdlist[21].sqltype = 496; sql_setdlist[21].sqllen = 4;
#line 376 "geotrace.sqc"
      sql_setdlist[21].sqldata = (void*)&text_count;
#line 376 "geotrace.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 376 "geotrace.sqc"
      sqlasetdata(3,0,22,sql_setdlist,0L,0L);
    }
#line 376 "geotrace.sqc"
  sqlacall((unsigned short)24,9,2,3,0L);
#line 376 "geotrace.sqc"
  sqlastop(0L);
}

#line 376 "geotrace.sqc"


      if (SQLCODE != 0)
	 {
	  printf("\nNETWORK RET : ERROR Reading from Features SQLCODE = %d\n",SQLCODE);
	  break;
	 }

      feat[++i].num         = feat_num       ;
      sscanf (feat_code,"%s",&feat[i].code)  ; /* Trim DB2trailing spaces      */
      feat[i].type          = type           ;
      feat[i].layer         = layer          ;
      feat[i].network       = network        ;
      feat[i].scale_range[0]= scale_range[0] ;
      feat[i].scale_range[1]= scale_range[1] ;
      feat[i].scale_range[2]= scale_range[2] ;
      feat[i].scale_range[3]= scale_range[3] ;
      feat[i].scale_range[4]= scale_range[4] ;
      feat[i].displayed[0]  = rdisplayed[0]  ;
      feat[i].selectble[0]  = rselectable[0] ;
      feat[i].has_attrib[0] = rhas_attrib[0] ;
      feat[i].has_text[0]   = rhas_text[0]   ;
      feat[i].color         = feat_color     ;
      feat[i].linetype      = feat_linetype  ;
      feat[i].linewidth     = feat_linewidth ;
      feat[i].xbase         = x_base         ;
      feat[i].ybase         = y_base         ;
      feat[i].xend          = x_end          ;
      feat[i].yend          = y_end          ;
      feat[i].xy_count      = xy_count       ;
      feat[i].text_count    = text_count     ;


      if ( feat[i].xy_count > 0 )
	 {
	  
/*
EXEC SQL OPEN NR_COORD ;
*/

{
#line 411 "geotrace.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 411 "geotrace.sqc"
  sqlaaloc(2,1,15,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 411 "geotrace.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 411 "geotrace.sqc"
      sql_setdlist[0].sqldata = (void*)&feat_num;
#line 411 "geotrace.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 411 "geotrace.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 411 "geotrace.sqc"
  sqlacall((unsigned short)26,7,2,0,0L);
#line 411 "geotrace.sqc"
  sqlastop(0L);
}

#line 411 "geotrace.sqc"


	  feat[i].xy = xy_index ;
	  j = 0 ;

	  for (iii=1; iii<=(feat[i].xy_count/10); iii++)
	      {
	       
/*
EXEC SQL FETCH NR_COORD INTO  :seq ,:x_1 ,:y_1,:x_2 ,:y_2,:x_3 ,:y_3,
					     :x_4 ,:y_4,:x_5 ,:y_5,:x_6 ,:y_6,
					     :x_7 ,:y_7,:x_8 ,:y_8,:x_9 ,:y_9,:x_10,:y_10;
*/

{
#line 420 "geotrace.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 420 "geotrace.sqc"
  sqlaaloc(3,21,16,0L);
    {
      struct sqla_setdata_list sql_setdlist[21];
#line 420 "geotrace.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 420 "geotrace.sqc"
      sql_setdlist[0].sqldata = (void*)&seq;
#line 420 "geotrace.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 420 "geotrace.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 420 "geotrace.sqc"
      sql_setdlist[1].sqldata = (void*)&x_1;
#line 420 "geotrace.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 420 "geotrace.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 420 "geotrace.sqc"
      sql_setdlist[2].sqldata = (void*)&y_1;
#line 420 "geotrace.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 420 "geotrace.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 420 "geotrace.sqc"
      sql_setdlist[3].sqldata = (void*)&x_2;
#line 420 "geotrace.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 420 "geotrace.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 420 "geotrace.sqc"
      sql_setdlist[4].sqldata = (void*)&y_2;
#line 420 "geotrace.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 420 "geotrace.sqc"
      sql_setdlist[5].sqltype = 496; sql_setdlist[5].sqllen = 4;
#line 420 "geotrace.sqc"
      sql_setdlist[5].sqldata = (void*)&x_3;
#line 420 "geotrace.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 420 "geotrace.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 420 "geotrace.sqc"
      sql_setdlist[6].sqldata = (void*)&y_3;
#line 420 "geotrace.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 420 "geotrace.sqc"
      sql_setdlist[7].sqltype = 496; sql_setdlist[7].sqllen = 4;
#line 420 "geotrace.sqc"
      sql_setdlist[7].sqldata = (void*)&x_4;
#line 420 "geotrace.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 420 "geotrace.sqc"
      sql_setdlist[8].sqltype = 496; sql_setdlist[8].sqllen = 4;
#line 420 "geotrace.sqc"
      sql_setdlist[8].sqldata = (void*)&y_4;
#line 420 "geotrace.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 420 "geotrace.sqc"
      sql_setdlist[9].sqltype = 496; sql_setdlist[9].sqllen = 4;
#line 420 "geotrace.sqc"
      sql_setdlist[9].sqldata = (void*)&x_5;
#line 420 "geotrace.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 420 "geotrace.sqc"
      sql_setdlist[10].sqltype = 496; sql_setdlist[10].sqllen = 4;
#line 420 "geotrace.sqc"
      sql_setdlist[10].sqldata = (void*)&y_5;
#line 420 "geotrace.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 420 "geotrace.sqc"
      sql_setdlist[11].sqltype = 496; sql_setdlist[11].sqllen = 4;
#line 420 "geotrace.sqc"
      sql_setdlist[11].sqldata = (void*)&x_6;
#line 420 "geotrace.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 420 "geotrace.sqc"
      sql_setdlist[12].sqltype = 496; sql_setdlist[12].sqllen = 4;
#line 420 "geotrace.sqc"
      sql_setdlist[12].sqldata = (void*)&y_6;
#line 420 "geotrace.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 420 "geotrace.sqc"
      sql_setdlist[13].sqltype = 496; sql_setdlist[13].sqllen = 4;
#line 420 "geotrace.sqc"
      sql_setdlist[13].sqldata = (void*)&x_7;
#line 420 "geotrace.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 420 "geotrace.sqc"
      sql_setdlist[14].sqltype = 496; sql_setdlist[14].sqllen = 4;
#line 420 "geotrace.sqc"
      sql_setdlist[14].sqldata = (void*)&y_7;
#line 420 "geotrace.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 420 "geotrace.sqc"
      sql_setdlist[15].sqltype = 496; sql_setdlist[15].sqllen = 4;
#line 420 "geotrace.sqc"
      sql_setdlist[15].sqldata = (void*)&x_8;
#line 420 "geotrace.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 420 "geotrace.sqc"
      sql_setdlist[16].sqltype = 496; sql_setdlist[16].sqllen = 4;
#line 420 "geotrace.sqc"
      sql_setdlist[16].sqldata = (void*)&y_8;
#line 420 "geotrace.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 420 "geotrace.sqc"
      sql_setdlist[17].sqltype = 496; sql_setdlist[17].sqllen = 4;
#line 420 "geotrace.sqc"
      sql_setdlist[17].sqldata = (void*)&x_9;
#line 420 "geotrace.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 420 "geotrace.sqc"
      sql_setdlist[18].sqltype = 496; sql_setdlist[18].sqllen = 4;
#line 420 "geotrace.sqc"
      sql_setdlist[18].sqldata = (void*)&y_9;
#line 420 "geotrace.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 420 "geotrace.sqc"
      sql_setdlist[19].sqltype = 496; sql_setdlist[19].sqllen = 4;
#line 420 "geotrace.sqc"
      sql_setdlist[19].sqldata = (void*)&x_10;
#line 420 "geotrace.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 420 "geotrace.sqc"
      sql_setdlist[20].sqltype = 496; sql_setdlist[20].sqllen = 4;
#line 420 "geotrace.sqc"
      sql_setdlist[20].sqldata = (void*)&y_10;
#line 420 "geotrace.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 420 "geotrace.sqc"
      sqlasetdata(3,0,21,sql_setdlist,0L,0L);
    }
#line 420 "geotrace.sqc"
  sqlacall((unsigned short)25,7,0,3,0L);
#line 420 "geotrace.sqc"
  sqlastop(0L);
}

#line 420 "geotrace.sqc"


	       if (SQLCODE == 0)
		  {
		   x[xy_index + ++j]=x_1 ; y[xy_index+j]=y_1 ;
		   x[xy_index + ++j]=x_2 ; y[xy_index+j]=y_2 ;
		   x[xy_index + ++j]=x_3 ; y[xy_index+j]=y_3 ;
		   x[xy_index + ++j]=x_4 ; y[xy_index+j]=y_4 ;
		   x[xy_index + ++j]=x_5 ; y[xy_index+j]=y_5 ;
		   x[xy_index + ++j]=x_6 ; y[xy_index+j]=y_6 ;
		   x[xy_index + ++j]=x_7 ; y[xy_index+j]=y_7 ;
		   x[xy_index + ++j]=x_8 ; y[xy_index+j]=y_8 ;
		   x[xy_index + ++j]=x_9 ; y[xy_index+j]=y_9 ;
		   x[xy_index + ++j]=x_10; y[xy_index+j]=y_10;
		  }
		else
		  {
		   break ;
		  }
	      }

	  /* Get Last COORDINTE  ROW  */
	  
/*
EXEC SQL FETCH NR_COORD INTO  :seq ,
				  :x_1 ,:y_1,
				  :x_2 ,:y_2,
				  :x_3 ,:y_3,
				  :x_4 ,:y_4,
				  :x_5 ,:y_5,
				  :x_6 ,:y_6,
				  :x_7 ,:y_7,
				  :x_8 ,:y_8,
				  :x_9 ,:y_9,
				  :x_10,:y_10   ;
*/

{
#line 452 "geotrace.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 452 "geotrace.sqc"
  sqlaaloc(3,21,17,0L);
    {
      struct sqla_setdata_list sql_setdlist[21];
#line 452 "geotrace.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 452 "geotrace.sqc"
      sql_setdlist[0].sqldata = (void*)&seq;
#line 452 "geotrace.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 452 "geotrace.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 452 "geotrace.sqc"
      sql_setdlist[1].sqldata = (void*)&x_1;
#line 452 "geotrace.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 452 "geotrace.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 452 "geotrace.sqc"
      sql_setdlist[2].sqldata = (void*)&y_1;
#line 452 "geotrace.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 452 "geotrace.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 452 "geotrace.sqc"
      sql_setdlist[3].sqldata = (void*)&x_2;
#line 452 "geotrace.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 452 "geotrace.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 452 "geotrace.sqc"
      sql_setdlist[4].sqldata = (void*)&y_2;
#line 452 "geotrace.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 452 "geotrace.sqc"
      sql_setdlist[5].sqltype = 496; sql_setdlist[5].sqllen = 4;
#line 452 "geotrace.sqc"
      sql_setdlist[5].sqldata = (void*)&x_3;
#line 452 "geotrace.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 452 "geotrace.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 452 "geotrace.sqc"
      sql_setdlist[6].sqldata = (void*)&y_3;
#line 452 "geotrace.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 452 "geotrace.sqc"
      sql_setdlist[7].sqltype = 496; sql_setdlist[7].sqllen = 4;
#line 452 "geotrace.sqc"
      sql_setdlist[7].sqldata = (void*)&x_4;
#line 452 "geotrace.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 452 "geotrace.sqc"
      sql_setdlist[8].sqltype = 496; sql_setdlist[8].sqllen = 4;
#line 452 "geotrace.sqc"
      sql_setdlist[8].sqldata = (void*)&y_4;
#line 452 "geotrace.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 452 "geotrace.sqc"
      sql_setdlist[9].sqltype = 496; sql_setdlist[9].sqllen = 4;
#line 452 "geotrace.sqc"
      sql_setdlist[9].sqldata = (void*)&x_5;
#line 452 "geotrace.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 452 "geotrace.sqc"
      sql_setdlist[10].sqltype = 496; sql_setdlist[10].sqllen = 4;
#line 452 "geotrace.sqc"
      sql_setdlist[10].sqldata = (void*)&y_5;
#line 452 "geotrace.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 452 "geotrace.sqc"
      sql_setdlist[11].sqltype = 496; sql_setdlist[11].sqllen = 4;
#line 452 "geotrace.sqc"
      sql_setdlist[11].sqldata = (void*)&x_6;
#line 452 "geotrace.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 452 "geotrace.sqc"
      sql_setdlist[12].sqltype = 496; sql_setdlist[12].sqllen = 4;
#line 452 "geotrace.sqc"
      sql_setdlist[12].sqldata = (void*)&y_6;
#line 452 "geotrace.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 452 "geotrace.sqc"
      sql_setdlist[13].sqltype = 496; sql_setdlist[13].sqllen = 4;
#line 452 "geotrace.sqc"
      sql_setdlist[13].sqldata = (void*)&x_7;
#line 452 "geotrace.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 452 "geotrace.sqc"
      sql_setdlist[14].sqltype = 496; sql_setdlist[14].sqllen = 4;
#line 452 "geotrace.sqc"
      sql_setdlist[14].sqldata = (void*)&y_7;
#line 452 "geotrace.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 452 "geotrace.sqc"
      sql_setdlist[15].sqltype = 496; sql_setdlist[15].sqllen = 4;
#line 452 "geotrace.sqc"
      sql_setdlist[15].sqldata = (void*)&x_8;
#line 452 "geotrace.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 452 "geotrace.sqc"
      sql_setdlist[16].sqltype = 496; sql_setdlist[16].sqllen = 4;
#line 452 "geotrace.sqc"
      sql_setdlist[16].sqldata = (void*)&y_8;
#line 452 "geotrace.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 452 "geotrace.sqc"
      sql_setdlist[17].sqltype = 496; sql_setdlist[17].sqllen = 4;
#line 452 "geotrace.sqc"
      sql_setdlist[17].sqldata = (void*)&x_9;
#line 452 "geotrace.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 452 "geotrace.sqc"
      sql_setdlist[18].sqltype = 496; sql_setdlist[18].sqllen = 4;
#line 452 "geotrace.sqc"
      sql_setdlist[18].sqldata = (void*)&y_9;
#line 452 "geotrace.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 452 "geotrace.sqc"
      sql_setdlist[19].sqltype = 496; sql_setdlist[19].sqllen = 4;
#line 452 "geotrace.sqc"
      sql_setdlist[19].sqldata = (void*)&x_10;
#line 452 "geotrace.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 452 "geotrace.sqc"
      sql_setdlist[20].sqltype = 496; sql_setdlist[20].sqllen = 4;
#line 452 "geotrace.sqc"
      sql_setdlist[20].sqldata = (void*)&y_10;
#line 452 "geotrace.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 452 "geotrace.sqc"
      sqlasetdata(3,0,21,sql_setdlist,0L,0L);
    }
#line 452 "geotrace.sqc"
  sqlacall((unsigned short)25,7,0,3,0L);
#line 452 "geotrace.sqc"
  sqlastop(0L);
}

#line 452 "geotrace.sqc"

	  if (SQLCODE == 0)
	     {
	      j++; if ( j <= feat[i].xy_count ) { x[xy_index+j]=x_1 ; y[xy_index+j]=y_1 ;}
	      j++; if ( j <= feat[i].xy_count ) { x[xy_index+j]=x_2 ; y[xy_index+j]=y_2 ;}
	      j++; if ( j <= feat[i].xy_count ) { x[xy_index+j]=x_3 ; y[xy_index+j]=y_3 ;}
	      j++; if ( j <= feat[i].xy_count ) { x[xy_index+j]=x_4 ; y[xy_index+j]=y_4 ;}
	      j++; if ( j <= feat[i].xy_count ) { x[xy_index+j]=x_5 ; y[xy_index+j]=y_5 ;}
	      j++; if ( j <= feat[i].xy_count ) { x[xy_index+j]=x_6 ; y[xy_index+j]=y_6 ;}
	      j++; if ( j <= feat[i].xy_count ) { x[xy_index+j]=x_7 ; y[xy_index+j]=y_7 ;}
	      j++; if ( j <= feat[i].xy_count ) { x[xy_index+j]=x_8 ; y[xy_index+j]=y_8 ;}
	      j++; if ( j <= feat[i].xy_count ) { x[xy_index+j]=x_9 ; y[xy_index+j]=y_9 ;}
	      j++; if ( j <= feat[i].xy_count ) { x[xy_index+j]=x_10; y[xy_index+j]=y_10;}
	     }

	  xy_index = xy_index + feat[i].xy_count ;

	  
/*
EXEC SQL CLOSE NR_COORD;
*/

{
#line 469 "geotrace.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 469 "geotrace.sqc"
  sqlacall((unsigned short)20,7,0,0,0L);
#line 469 "geotrace.sqc"
  sqlastop(0L);
}

#line 469 "geotrace.sqc"
     /* CHECKERR ("CLOSE CURSOR"); */
	 }

 else if ( feat[i].type == 1 )
	 {
	  feat[i].symb_num   = symb_num    ;
	  feat[i].symb_size  = symb_size   ;
	  feat[i].symb_angle = symb_angle  ;
	 }


     if  ( feat[i].has_text[0] == 'Y' )
	 {
	  
/*
EXEC SQL OPEN TEXT;
*/

{
#line 482 "geotrace.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 482 "geotrace.sqc"
  sqlaaloc(2,1,18,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 482 "geotrace.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 482 "geotrace.sqc"
      sql_setdlist[0].sqldata = (void*)&feat_num;
#line 482 "geotrace.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 482 "geotrace.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 482 "geotrace.sqc"
  sqlacall((unsigned short)26,8,2,0,0L);
#line 482 "geotrace.sqc"
  sqlastop(0L);
}

#line 482 "geotrace.sqc"
    /* CHECKERR ("OPEN CURSOR"); */

	  feat[i].text = text_index ;

	  for (iii=1; iii<=feat[i].text_count; iii++)
	      {
	       
/*
EXEC SQL FETCH TEXT INTO :text_x      ,
				        :text_y      ,
				        :text_size   ,
				        :text_angle  ,
				        :text_just   ,
				        :text_font   ,
				        :textstring   ;
*/

{
#line 494 "geotrace.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 494 "geotrace.sqc"
  sqlaaloc(3,7,19,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 494 "geotrace.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 494 "geotrace.sqc"
      sql_setdlist[0].sqldata = (void*)&text_x;
#line 494 "geotrace.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 494 "geotrace.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 494 "geotrace.sqc"
      sql_setdlist[1].sqldata = (void*)&text_y;
#line 494 "geotrace.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 494 "geotrace.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 494 "geotrace.sqc"
      sql_setdlist[2].sqldata = (void*)&text_size;
#line 494 "geotrace.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 494 "geotrace.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 494 "geotrace.sqc"
      sql_setdlist[3].sqldata = (void*)&text_angle;
#line 494 "geotrace.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 494 "geotrace.sqc"
      sql_setdlist[4].sqltype = 500; sql_setdlist[4].sqllen = 2;
#line 494 "geotrace.sqc"
      sql_setdlist[4].sqldata = (void*)&text_just;
#line 494 "geotrace.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 494 "geotrace.sqc"
      sql_setdlist[5].sqltype = 500; sql_setdlist[5].sqllen = 2;
#line 494 "geotrace.sqc"
      sql_setdlist[5].sqldata = (void*)&text_font;
#line 494 "geotrace.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 494 "geotrace.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 51;
#line 494 "geotrace.sqc"
      sql_setdlist[6].sqldata = (void*)textstring;
#line 494 "geotrace.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 494 "geotrace.sqc"
      sqlasetdata(3,0,7,sql_setdlist,0L,0L);
    }
#line 494 "geotrace.sqc"
  sqlacall((unsigned short)25,8,0,3,0L);
#line 494 "geotrace.sqc"
  sqlastop(0L);
}

#line 494 "geotrace.sqc"

	       if (SQLCODE == 0)
		  {
		   text[feat[i].text+iii].x     = text_x     ;
		   text[feat[i].text+iii].y     = text_y     ;
		   text[feat[i].text+iii].size  = text_size  ;
		   text[feat[i].text+iii].angle = text_angle ;
		   text[feat[i].text+iii].just  = text_just  ;
		   text[feat[i].text+iii].font  = text_font  ;
		   strcpy(text[feat[i].text+iii].string,textstring);
		  }
		else
		  {
		   break ;
		  }
	      }

	  text_index = text_index + feat[i].text_count ;
	  
/*
EXEC SQL CLOSE TEXT;
*/

{
#line 512 "geotrace.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 512 "geotrace.sqc"
  sqlacall((unsigned short)20,8,0,0,0L);
#line 512 "geotrace.sqc"
  sqlastop(0L);
}

#line 512 "geotrace.sqc"
     /* CHECKERR ("CLOSE CURSOR"); */
	 }

     switch(feat[i].color)
	   {
	    case 1:  feat[i].color = blue.pixel  ;  break;
	    case 2:  feat[i].color = red.pixel   ;  break;
	    case 3:  feat[i].color = pink.pixel  ;  break;
	    case 4:  feat[i].color = green.pixel ;  break;
	    case 5:  feat[i].color = cyan.pixel  ;  break;
	    case 6:  feat[i].color = yellow.pixel;  break;
	    case 7:  feat[i].color = white.pixel ;  break;
	    case 8:  feat[i].color = black.pixel ;  break;
	    case 9:  feat[i].color = gray.pixel  ;  break;
	    case 10: feat[i].color = wheat.pixel ;  break;
	    case 11: feat[i].color = brown.pixel ;  break;
	    case 12: feat[i].color = orange.pixel;  break;

	    default: feat[i].color = brown.pixel ;  break;
	   }


     }  /* End of Ret. LOOP */


 printf("\n End of Retreival Process ...\n");

 feat_count = i          ;
 xy_LAST    = xy_index   ;
 text_LAST  = text_index ;

 printf ("\nINFO  : Feature Count   = [%d]",feat_count);
 printf ("\nINFO  : LAST xy Index   = [%d]",xy_LAST   );
 printf ("\nINFO  : LAST text Index = [%d]",text_LAST );
 printf ("\n");

 db_opened[0] = 'Y' ;
 update_layer()     ;
 display_scale()    ;
 zoom_all("test.png")           ;
 // normal_cursor()    ;
}
