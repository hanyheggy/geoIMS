static char sqla_program_id[162] = 
{
 42,0,65,68,65,75,65,73,71,69,79,73,77,83,95,77,66,66,114,75,
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


#line 1 "geoIMS_main.sqc"
////////////////////////////////////////////////////////////////////////////////////////////////////
/*------------------------------------------------------------------------------------------------*/
/*                                     geoIMS Version 1.3                                         */
/*------------------------------------------------------------------------------------------------*/
////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                                                                                */
/*   Modules           :  geoIMS_main.sqc         Main program source code                        */
/*                        geoIMS_logger.c         System Logger                                   */
/*                        geoIMS_web_listener.c   Web-client Listener                             */
/*                        geoIMS_read_db.c        Read-write DB                                   */
/*                        geoIMS_network.sqc      Shortest Path for street Network                */
/*                                                                                                */
/*   Include Files     :  include/geoIMS.h        Main header file                                */
/*                        include/geoIMSextern.h  External variable header file                   */
/*                                                                                                */
/*   Directories       :  font/*.font             ALL font files                                  */
/*                        symbol/*.symbol         ALL Symbol sets                                 */
/*                        bitmap/*.xbm            Push Button Bitmap files                        */
/*                                                                                                */
/*   geoINFO source    :  geoIMS_trace.sqc        Electric Network tracing                        */
/*                        geomatch.sqc            Edge Matching                                   */
/*                        geoplot.c               Plotting                                        */
/*                        geodxfio.c              DXF import/export                               */
/*                        geodig.c                Digitizer Capture                               */
/*                                                                                                */
/*   X11-GUI Modules   :  geoedit.sqc             Feature Edit                                    */
/*                        geofsb.c                File Selection Box                              */
/*                        geodbname.c             Get Database name                               */
/*                        geolocate.c             locate point                                    */
/*                        geolayer.c              Layer Control                                   */
/*                                                                                                */
/*   Batch Modules     :  geoload.sqc             Load INF into  DB2                              */
/*                        dxf2inf.c               Convert DXF to INF                              */
/*                        inf2dxf.c               Convert INF to DXF                              */
/*                        match.c                 Edge Matching                                   */
/*                        geosld.sqc              SLD Module                                      */
/*   Notes :                                                                                      */
/*                                                                                                */
/*   1. change user profile to support large soft data segment to handle                          */
/*      up to 5,000,000 features & 25,000,000 xy_coord & 500,000 text                             */
/*      ( arround 600 MB data file )                                                              */
/*      AIX                                                                                       */
/*      e -t  /etc/security/limits                                                                */
/*            data = 262144    defaults                                                           */
/*            data = 462144    geoinfo users    ( check by : ulimit -a )                          */
/*                                                                                                */
/*------------------------------------------------------------------------------------------------*/
////////////////////////////////////////////////////////////////////////////////////////////////////


/*------------------------------------------------------------------------------------------------*/
/*                                    geoIMS Include Files                                        */
/*------------------------------------------------------------------------------------------------*/
#include "include/geoIMS.h"

/*------------------------------------------------------------------------------------------------*/
/*                                DB2 Embeded SQC Include Files                                   */
/*------------------------------------------------------------------------------------------------*/
#include <sqlda.h>
#include <sqlenv.h>
#include <sqlcodes.h>
#include "include/utilemb.h"

/*------------------------------------------------------------------------------------------------*/
/*                                    Embeded SQL Variables                                       */
/*------------------------------------------------------------------------------------------------*/
// #define CHECKERR(CE_STR) if(check_error(CE_STR,&sqlca)!=0) printf("Error");
//  EMB_SQL_CHECK( MSG_STR )


/*
EXEC SQL INCLUDE SQLCA         ;
*/

/* SQL Communication Area - SQLCA - structures and constants */
#include "sqlca.h"
struct sqlca sqlca;


#line 70 "geoIMS_main.sqc"


/*
EXEC SQL BEGIN DECLARE SECTION ;
*/

#line 71 "geoIMS_main.sqc"

   char    db_name   [31]      ;
   long    feat_num            ;
   char    feat_code [13]      ;
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
   long    area_xmin           ;
   long    area_xmax           ;
   long    area_ymin           ;
   long    area_ymax           ;
   char    status  [3]         ;
   char    subid   [13]        ;
   char    fdrnum  [13]        ;
   char    subtype [21]        ;
   long    kva                 ;
   long    number              ;
   long    conn_feat           ;
   long    conn_feat1          ;
   long    conn_feat2          ;
   long    conn_feat3          ;
   char    grid    [13]        ;
   char    feeder  [13]        ;
   char    code    [13]        ;
   char    code1   [13]        ;
   long    arc                 ;
   long    node1               ;
   long    node2               ;
   long    other               ;
   long    weight              ;
   long    direction           ;
   char    street_name [51]    ;

/*
EXEC SQL END DECLARE SECTION   ;
*/

#line 156 "geoIMS_main.sqc"



/*------------------------------------------------------------------------------------------------*/
/*                                    geoIMS Global Variables                                     */
/*------------------------------------------------------------------------------------------------*/
unsigned char  UTF_TEXT [100]    ;
int   k                 ;
int   found             ;
int   stack_count       ;
int   conn_stack [1000] ;

int   feat_1            ;
int   feat_2            ;

static  Display       *MainDisplay ;
static  XEvent        MainEvent    ;

static  short         done = 0     ;


void xor_draw_pix_symb(int symb_no,int x_screen,int y_screen, int color,double p_size,int p_angle) ;



////////////////////////////////////////////////////////////////////////////////////////////////////
/*------------------------------------------------------------------------------------------------*/
/*                                           main()                                               */
/*------------------------------------------------------------------------------------------------*/
////////////////////////////////////////////////////////////////////////////////////////////////////
main(int argc,char *argv[])
{
 /*----------------------------*/
 /*       Local Variables      */
 /*----------------------------*/
 pthread_t  system_logger_thread  ;   // System Logger Thread
 pthread_t  web_listener_thread   ;   // Web Lintener  Thread

 int        i                     ;   // Loop Counter
 int        rc                    ;   // Return Code
 time_t     current_time          ;   // Time string
 char       system_time[30]       ;

 char       module[] = {"main"}   ;


 /*-----------------------------------------------------------------------------------------*/
 /*                               1. Create System Logger Thread                            */
 /*-----------------------------------------------------------------------------------------*/
 /*
 rc = pthread_create (&system_logger_thread,NULL,(void*)system_logger,NULL);
 if ( rc != 0 )
    {
     fprintf(stderr,"[geoIMS] SEVERE ERROR : Failed to create system logger thread, geoIMS terminated\n");
     exit(-1) ;
    }
 */

 /*-----------------------------------------------------------------------------------------*/
 /*                                  2. Initialize geoIMS                                   */
 /*-----------------------------------------------------------------------------------------*/
{
 char PARM             [20]      ;  // Paramter Name
 char VALUE            [50]      ;  // Paramter Value

 char FONT_DIR         [50]      ;  // Font   Directory
 char SYMBOL_DIR       [50]      ;  // Symbol Directory

 char font_file_name   [25][100] ;  // Font   Files
 char symbol_file_name [10][100] ;  // Symbol Files
 char layer_file_name      [100] ;  // Layer  File

 int  DisplayHeight_mm           ;  // Display Height in MM
 int  DisplayHeight_pixel        ;  // Display height in Pixel
 int  MONITOR_SIZE               ;  // Monitor Size in inches

 int  maxx     = 0               ;
 int  grid     = 0               ;
 int  xstroke  = 0               ;
 int  ystroke  = 0               ;
 int  f        = 0               ;
 int  ff       = 0               ;

 fprintf (stdout,"\nINFO  : geoIMS initialization started ..\n" );

 /*---------------------------------------------------------------------*/
 /* 2.1 Initaize GLOBAL Variables                                       */
 /*---------------------------------------------------------------------*/
 db_opened[0]    = 'N'        ;  // Reset DB open flag
 trace_on [0]    = 'N'        ;  // Reset Trace Flag

 feat_count      = 0          ;  // Reset Total Number of Features
 lay_count       = 0          ;  // Reset Total Number of Layers
 xy_index        = 0          ;  // Reset xy_index
 text_index      = 0          ;  // Reset text_index

 x_ul_screen     = 0          ;  // Set Screen Limits (in Pixels)
 y_ul_screen     = 0          ;  // 500 x 500 Pixel
 x_br_screen     = 499        ;  // starting from 0 to 499
 y_br_screen     = 499        ;

 draw_fun        = NONE       ;  // Set Initial Draw function

 /*---------------------------------------------------------------------*/
 /* 2.2 Set Default Values to be over-written by geoIMS.ini             */
 /*---------------------------------------------------------------------*/
 DB_UNIT     = DM              ;  // Set Default DBU  to DM
 strcpy (DB_UNIT_NAME,"DM")    ;  // Set Default DBU  Name

 x_min = 5000000.0             ;  // Set Default DB Limits in DBU
 y_min = 5000000.0             ;  // gives scale 1:1000 with pixmap of
 x_max = 5002230.392209        ;  // 1000x1000 Pixel, 14" Monitor and
 y_max = 5002230.392209        ;  // X11 resolution 1024x768

 REFRESH        = 5000         ;  // Refresh Screen after drawing n feat
 cursor_size    = 8            ;  // Cursor Size in Pixles
 SYMBCLIPBUFFER = 50           ;  // Symbol Clip Buffer in DBU
 LINECLIPBUFFER = 100000       ;  // Line   Clip Buffer in DBU
 MONITOR_SIZE   = 14           ;  // Monitor Size in inches

 SC_RANGE1      = 2500         ;  // Scale Range Values
 SC_RANGE2      = 5000         ;
 SC_RANGE3      = 10000        ;
 SC_RANGE4      = 25000        ;

 // Set Default Print Queue
 strcpy ( queue_name , "hpgl" ) ;

 // Set Default Symbol Path
 strcpy ( SYMBOL_DIR           ,"symbol/"                    );
 strcpy ( symbol_file_name [1] ,"symbol/standard.symbol"     );

 // Set Default Font Path
 strcpy ( FONT_DIR           ,"font/"                        );
 strcpy ( font_file_name [1] ,"font/standard.font"           );
 strcpy ( font_file_name [2] ,"font/courier.font"            );
 strcpy ( font_file_name [3] ,"font/concept.font"            );
 strcpy ( font_file_name [4] ,"font/quick.font"              );
 strcpy ( font_file_name [5] ,"font/helvetic.font"           );
 strcpy ( font_file_name [6] ,"font/outline.font"            );
 strcpy ( font_file_name [7] ,"font/complex_italic1.font"    );
 strcpy ( font_file_name [8] ,"font/complex_italic2.font"    );
 strcpy ( font_file_name [9] ,"font/complex_roman1.font"     );
 strcpy ( font_file_name [10],"font/complex_roman2.font"     );
 strcpy ( font_file_name [11],"font/complex_script.font"     );
 strcpy ( font_file_name [12],"font/multiplex_3x_italic.font");
 strcpy ( font_file_name [13],"font/multiplex_2x_roman.font" );
 strcpy ( font_file_name [14],"font/multiplex_3x_roman.font" );
 strcpy ( font_file_name [15],"font/simplex_roman.font"      );
 strcpy ( font_file_name [16],"font/simplex_script.font"     );
 strcpy ( font_file_name [17],"font/gothic_english.font"     );
 strcpy ( font_file_name [18],"font/gothic_italia.font"      );
 strcpy ( font_file_name [19],"font/gfis.font"               );
 strcpy ( font_file_name [20],"font/gasfont.font"            );
 strcpy ( font_file_name [21],"font/arabic1.font"            );

 /*---------------------------------------------------------------------*/
 /* 2.3 Read Parameter file                                             */
 /*---------------------------------------------------------------------*/
 fp_i=fopen("geoIMS.ini","rt");
 if  ( fp_i== NULL )  // !fp_i
     {
      fprintf (stderr,"ERROR : Can't open parameter file [./geoIMS.ini], %s.\n",strerror(errno));
      fprintf (stderr,"INFO  : geoIMS terminated due to ERROR.\n\n");
      exit(1);
     }
 else
     {
      fprintf (stdout,"INFO  : Processing parameter file ..\n");
     }


 while ( fscanf(fp_i,"%s", PARM) != EOF )
       {
        fscanf(fp_i,"%s", VALUE );    // read  '='
        fscanf(fp_i,"%s", VALUE );    // read  'Value'


        if ( strcmp(PARM,"DATA_FILE") == 0 )
           {
            strcpy(sys.data_file,VALUE) ;
            continue;
           }
        else
        if ( strcmp(PARM,"LAYER_FILE") == 0 )
           {
            strcpy(layer_file_name,VALUE) ;
            continue;
           }
        else
        if ( strcmp(PARM,"WEB_IP") == 0 )
           {
            strcpy(sys.web_ip,VALUE) ;
            continue;
           }
        else
        if ( strcmp(PARM,"WEB_PORT") == 0 )
           {
            sys.web_port= atoi(VALUE) ;
            continue;
           }
        else
        if ( strcmp(PARM,"WEB_INCLUDE_FILE") == 0 )
           {
            strcpy(sys.web_include_file,VALUE) ;
            continue;
           }
        else
        if ( strcmp(PARM,"DB_UNIT") == 0 )
           {
                 if ( strcmp(VALUE,"MM") == 0 ) { DB_UNIT = MM ; strcpy (DB_UNIT_NAME,"MM"); }
            else if ( strcmp(VALUE,"CM") == 0 ) { DB_UNIT = CM ; strcpy (DB_UNIT_NAME,"CM"); }
            else if ( strcmp(VALUE,"DM") == 0 ) { DB_UNIT = DM ; strcpy (DB_UNIT_NAME,"DM"); }
            else if ( strcmp(VALUE,"M" ) == 0 ) { DB_UNIT = M  ; strcpy (DB_UNIT_NAME,"M" ); }
            else if ( strcmp(VALUE,"KM") == 0 ) { DB_UNIT = KM ; strcpy (DB_UNIT_NAME,"KM"); }
            else                                { DB_UNIT = DM ; strcpy (DB_UNIT_NAME,"DM"); }
            continue;
           }
        else
        if ( strcmp(PARM,"DXF_DB_UNIT") == 0 )
           {
                 if ( strcmp(VALUE,"MM") == 0 ) { DXF_DB_UNIT = MM ;  }
            else if ( strcmp(VALUE,"CM") == 0 ) { DXF_DB_UNIT = CM ;  }
            else if ( strcmp(VALUE,"DM") == 0 ) { DXF_DB_UNIT = DM ;  }
            else if ( strcmp(VALUE,"M" ) == 0 ) { DXF_DB_UNIT = M  ;  }
            else if ( strcmp(VALUE,"KM") == 0 ) { DXF_DB_UNIT = KM ;  }
            else                                { DXF_DB_UNIT = DM ;  }
            continue;
           }
        else
        if ( strcmp(PARM,"CURSOR_SIZE") == 0 )
           {
            cursor_size = atoi(VALUE) ;
            continue;
           }
        else
        if ( strcmp(PARM,"X_MIN") == 0 )
           {
            x_min = atof(VALUE) ;
            continue;
           }
        else
        if ( strcmp(PARM,"Y_MIN") == 0 )
           {
            y_min = atof(VALUE) ;
            continue;
           }
        else
        if ( strcmp(PARM,"X_MAX") == 0 )
           {
            x_max = atof(VALUE) ;
            continue;
           }
        else
        if ( strcmp(PARM,"Y_MAX") == 0 )
           {
            y_max = atof(VALUE) ;
            continue;
           }
        else
        if ( strcmp(PARM,"SC_RANGE1") == 0 )
           {
            SC_RANGE1 = atoi(VALUE) ;
            continue;
           }
        if ( strcmp(PARM,"SC_RANGE2") == 0 )
           {
            SC_RANGE2 = atoi(VALUE) ;
            continue;
           }
        if ( strcmp(PARM,"SC_RANGE3") == 0 )
           {
            SC_RANGE3 = atoi(VALUE) ;
            continue;
           }
        if ( strcmp(PARM,"SC_RANGE4") == 0 )
           {
            SC_RANGE4 = atoi(VALUE) ;
            continue;
           }
        else
        if ( strcmp(PARM,"REFRESH") == 0 )
           {
            REFRESH = atoi(VALUE) ;
            continue;
           }
        else
        if ( strcmp(PARM,"PRINT_QUEUE") == 0 )
           {
            strcpy (queue_name,VALUE) ;
            continue;
           }
        else
        if ( strcmp(PARM,"SYMB_CLIP_BUFFER") == 0 )
           {
            SYMBCLIPBUFFER = atoi(VALUE) ;
            continue;
           }
        else
        if ( strcmp(PARM,"LINE_CLIP_BUFFER") == 0 )
           {
            LINECLIPBUFFER = atoi(VALUE) ;
            continue;
           }
        else
        if ( strcmp(PARM,"JOIN_TOLERANCE") == 0 )
           {
            JOIN_TOLERANCE = atoi(VALUE) ;
            continue;
           }
        else
        if ( strcmp(PARM,"FONT_DIR") == 0 )
           {
            strcpy( FONT_DIR ,VALUE );
            strcat( FONT_DIR ,"/"   );
            continue;
           }
        else
        if ( strcmp(PARM,"FONT1") == 0 )
           {
            strcpy( font_file_name [1] ,FONT_DIR);
            strcat( font_file_name [1] ,VALUE   );
            continue;
           }
        else
        if ( strcmp (PARM, "FONT2" ) == 0 )
           {
            strcpy( font_file_name [2] ,FONT_DIR);
            strcat( font_file_name [2] ,VALUE   );
            continue;
           }
        else
        if ( strcmp (PARM, "FONT3" ) == 0 )
           {
            strcpy( font_file_name [3] ,FONT_DIR);
            strcat( font_file_name [3] ,VALUE   );
            continue;
           }
        else
        if ( strcmp (PARM, "FONT4" ) == 0 )
           {
            strcpy( font_file_name [4] ,FONT_DIR);
            strcat( font_file_name [4] ,VALUE   );
            continue;
           }
        else
        if ( strcmp (PARM, "FONT5" ) == 0 )
           {
            strcpy( font_file_name [5] ,FONT_DIR);
            strcat( font_file_name [5] ,VALUE   );
            continue;
           }
        else
        if ( strcmp (PARM, "FONT6" ) == 0 )
           {
            strcpy( font_file_name [6] ,FONT_DIR);
            strcat( font_file_name [6] ,VALUE   );
            continue;
           }
        else
        if ( strcmp (PARM, "FONT7" ) == 0 )
           {
            strcpy( font_file_name [7] ,FONT_DIR);
            strcat( font_file_name [7] ,VALUE   );
            continue;
           }
        else
        if ( strcmp (PARM, "FONT8" ) == 0 )
           {
            strcpy( font_file_name [8] ,FONT_DIR);
            strcat( font_file_name [8] ,VALUE   );
            continue;
           }
        else
        if ( strcmp (PARM, "FONT9" ) == 0 )
           {
            strcpy( font_file_name [9] ,FONT_DIR);
            strcat( font_file_name [9] ,VALUE   );
            continue;
           }
        else
        if ( strcmp (PARM, "FONT10" ) == 0 )
           {
            strcpy( font_file_name [10] ,FONT_DIR);
            strcat( font_file_name [10] ,VALUE   );
            continue;
           }
        else
        if ( strcmp (PARM, "FONT11" ) == 0 )
           {
            strcpy( font_file_name [11] ,FONT_DIR);
            strcat( font_file_name [11] ,VALUE   );
            continue;
           }
        else
        if ( strcmp (PARM, "FONT12" ) == 0 )
           {
            strcpy( font_file_name [12] ,FONT_DIR);
            strcat( font_file_name [12] ,VALUE   );
            continue;
           }
        else
        if ( strcmp (PARM, "FONT13" ) == 0 )
           {
            strcpy( font_file_name [13] ,FONT_DIR);
            strcat( font_file_name [13] ,VALUE   );
            continue;
           }
        else
        if ( strcmp (PARM, "FONT14" ) == 0 )
           {
            strcpy( font_file_name [14] ,FONT_DIR);
            strcat( font_file_name [14] ,VALUE   );
            continue;
           }
        else
        if ( strcmp (PARM, "FONT15" ) == 0 )
           {
            strcpy( font_file_name [15] ,FONT_DIR);
            strcat( font_file_name [15] ,VALUE   );
            continue;
           }
        else
        if ( strcmp (PARM, "FONT16" ) == 0 )
           {
            strcpy( font_file_name [16] ,FONT_DIR);
            strcat( font_file_name [16] ,VALUE   );
            continue;
           }
        else
        if ( strcmp (PARM, "FONT17" ) == 0 )
           {
            strcpy( font_file_name [17] ,FONT_DIR);
            strcat( font_file_name [17] ,VALUE   );
            continue;
           }
        else
        if ( strcmp (PARM, "FONT18" ) == 0 )
           {
            strcpy( font_file_name [18] ,FONT_DIR);
            strcat( font_file_name [18] ,VALUE   );
            continue;
           }
        else
        if ( strcmp (PARM, "FONT19" ) == 0 )
           {
            strcpy( font_file_name [19] ,FONT_DIR);
            strcat( font_file_name [19] ,VALUE   );
            continue;
           }
        else
        if ( strcmp (PARM, "FONT20" ) == 0 )
           {
            strcpy( font_file_name [20] ,FONT_DIR);
            strcat( font_file_name [20] ,VALUE   );
            continue;
           }
        else
        if ( strcmp (PARM, "FONT21" ) == 0 )
           {
            strcpy( font_file_name [21] ,FONT_DIR);
            strcat( font_file_name [21] ,VALUE   );
            continue;
           }
        else
        if ( strcmp (PARM, "FONT22" ) == 0 )
           {
            strcpy( font_file_name [22] ,FONT_DIR);
            strcat( font_file_name [22] ,VALUE   );
            continue;
           }
        else
        if ( strcmp (PARM, "FONT23" ) == 0 )
           {
            strcpy( font_file_name [23] ,FONT_DIR);
            strcat( font_file_name [23] ,VALUE   );
            continue;
           }
        else
        if ( strcmp (PARM, "FONT24" ) == 0 )
           {
            strcpy( font_file_name [24] ,FONT_DIR);
            strcat( font_file_name [24] ,VALUE   );
            continue;
           }
        else
        if ( strcmp(PARM,"SYMBOL_DIR") == 0 )
           {
            strcpy( SYMBOL_DIR ,VALUE );
            strcat( SYMBOL_DIR ,"/"   );
            continue;
           }
        else
        if ( strcmp(PARM,"SYMBOL1") == 0 )
           {
            strcpy( symbol_file_name [1] ,SYMBOL_DIR);
            strcat( symbol_file_name [1] ,VALUE     );
            continue;
           }
        else
        if ( strcmp (PARM, "MONITOR_SIZE" ) == 0 )
           {
            MONITOR_SIZE = atoi(VALUE) ;
            continue;
           }
        else
        if ( strcmp (PARM, "SESSION_TIMEOUT" ) == 0 )
           {
            sys.session_timeout = atoi(VALUE) ;
            continue;
           }
        else
           {
            printf("ERROR : Unknown Parameter, %s\n",PARM);
           }
      }
 fclose(fp_i);

 /*---------------------------------------------------------------------*/
 /* 2.4 Calculate Graphic Paramters                                     */
 /*---------------------------------------------------------------------*/
 DisplayHeight_pixel = 1024 ;  // = XDisplayHeight(MainDisplay,nScreen)
 DisplayHeight_mm    = 241  ;  // = XDisplayHeightMM(MainDisplay,nScreen)

 ONE_PIXEL = (y_max - y_min) / (y_br_screen - y_ul_screen) ;
 tolerance = cursor_size * ONE_PIXEL ;

 SCREEN_CM = (double)DisplayHeight_mm * (double)(y_br_screen+1) /(double)(DisplayHeight_pixel*10) ;

 switch(MONITOR_SIZE)
       {
        case 14:  SCREEN_CM *= (double)(14.0 / 17.0) ; break;
        case 15:  SCREEN_CM *= (double)(15.0 / 17.0) ; break;
        case 17:  SCREEN_CM *= (double)(17.0 / 17.0) ; break;
        case 19:  SCREEN_CM *= (double)(19.0 / 17.0) ; break;
        case 20:  SCREEN_CM *= (double)(20.0 / 17.0) ; break;
        case 21:  SCREEN_CM *= (double)(21.0 / 17.0) ; break;
        case 23:  SCREEN_CM *= (double)(23.0 / 17.0) ; break;
        default:  SCREEN_CM *= (double)(17.0 / 17.0) ;
                  fprintf(stderr,"WARNNING : Monitor size not defined, default set to 17 inch\n");
                  break;
       }

 y_diff = y_max - y_min ;
 switch (DB_UNIT)
        {
         case MM: scale = ( y_diff * .1   ) / SCREEN_CM ; break ;
         case CM: scale = ( y_diff * 1.   ) / SCREEN_CM ; break ;
         case DM: scale = ( y_diff * 10.  ) / SCREEN_CM ; break ;
         case  M: scale = ( y_diff * 100. ) / SCREEN_CM ; break ;
         case KM: scale = ( y_diff * 1000.) / SCREEN_CM ; break ;
         default: scale = ( y_diff * 100. ) / SCREEN_CM ;
                  fprintf(stderr,"ERROR : Data Base unit not defined, default set to Meter\n");
                  break ;
        }

 /*---------------------------------------------------------------------*/
 /* 2.5 Read Layer Name File                                            */
 /*---------------------------------------------------------------------*/
 fp_i=fopen(layer_file_name,"rt");
 if  ( fp_i== NULL )
     {
      fprintf (stderr,"ERROR : Can't open layer file  !\n");
      fprintf (stderr,"ERROR : geoIMS terminated ...  \n");
      exit(1);
     }
 else
     {
      printf ("INFO  : Processing layer file ..\n");
     }

 while ( fscanf(fp_i,"%d", &i) != EOF )
       {
        fscanf(fp_i,"%s", lay[i].name );
       }

 fclose(fp_i);

 /*---------------------------------------------------------------------*/
 /* 2.6 Read Symbol Set                                                 */
 /*---------------------------------------------------------------------*/
 fp_i=fopen(symbol_file_name[1],"rt");
 if  ( fp_i== NULL )
     {
      fprintf (stderr,"ERROR : Can't open symbol file !\n");
      fprintf (stderr,"ERROR : geoIMS terminated ...  \n");
      exit(1);
     }
 else
     {
      printf ("INFO  : Processing symbol file ..\n");
     }

 while ( fscanf(fp_i,"%s", &string) != EOF ) /* Symbol Name                */
       {
        fscanf(fp_i,"%d", &i             );  /* Symbol Number              */
        fscanf(fp_i,"%d", &symb[i].grid  );  /* Symbol Max Grid Coordinate */
        fscanf(fp_i,"%d", &symb[i].stroke);  /* Number of strokes          */

        for ( ii=1 ; ii<=symb[i].stroke ; ii++ )
            {
             fscanf(fp_i,"%d", &symb[i].mv_draw[ii]);
             fscanf(fp_i,"%d", &xstroke);
             fscanf(fp_i,"%d", &ystroke);

             /* Calculate Polar Coordinates */
             symb[i].angle[ii] = atan2(ystroke,xstroke) ;
             symb[i].distance[ii] = sqrt((xstroke*xstroke)+(ystroke*ystroke));
            }
       }
 fclose(fp_i);

 /*---------------------------------------------------------------------*/
 /* 2.7 Read Font Files                                                 */
 /*---------------------------------------------------------------------*/
 fprintf (stdout,"INFO  : Processing font files ..\n");
 for (f=1; f<22; f++)
     {
      fp_i=fopen(font_file_name[f],"rt");
      if  ( fp_i== NULL )
          {
           if (f==1)
              {
               fprintf (stderr,"ERROR : Can't open %s file !\n",font_file_name[f]);
               fprintf (stderr,"ERROR : geoIMS terminated ...\n");
               exit(1);
              }
           else
              {
               fprintf (stderr,"ERROR : Can't open %s file, font skipped !\n",font_file_name[f]);
               continue ;
              }
          }
      else
          {
           font_no = ++ff ;
          }

      while ( fscanf(fp_i,"%s", &string) != EOF )         /* Symbol Name                */
            {
             maxx = -1000 ;

             fscanf(fp_i,"%d", &i                      ); /* Symbol Number              */
             fscanf(fp_i,"%d", &font[font_no][i].grid  ); /* Symbol Max Grid Coordinate */
             fscanf(fp_i,"%d", &font[font_no][i].stroke); /* Number of strokes          */

             for ( ii=1 ; ii<=font[font_no][i].stroke ; ii++ )
                 {
                  fscanf(fp_i,"%d", &font[font_no][i].mv_draw[ii]);
                  fscanf(fp_i,"%d", &xstroke);
                  fscanf(fp_i,"%d", &ystroke);

                  /* Calculate Max xstroke */
                  if ( xstroke > maxx ) { maxx = xstroke ; }

                  /* Calculate Polar Coordinates */
                  font[font_no][i].angle[ii] = atan2(ystroke,xstroke) ;
                  font[font_no][i].distance[ii] = sqrt((xstroke*xstroke)+(ystroke*ystroke));
                 }

             grid = font[font_no][i].grid ;

             /*  Font Enhancement */
             if ( maxx > (grid/2)  &&  grid != 0 )
                {
                 font[font_no][i].x_factor = 1.0 + (float) (maxx - grid/2) / grid ;
                }
             else
             if ( grid != 0 )
                {
                 font[font_no][i].x_factor = 1.0 - (float) (grid/2 - maxx) / grid ;
                }
             else
                {
                 font[font_no][i].x_factor = 1.0 ;
                }
            }
      fclose(fp_i);
     }

 /*---------------------------------------------------------------------*/
 /* 2.8 Set ImageMagick Line types                                      */
 /*---------------------------------------------------------------------*/
 dash_array [1][0] = 1.0  ; // CONTINOUS LINE

 dash_array [2][0] = 5.0  ; // DASH LINE
 dash_array [2][1] = 5.0  ;

 dash_array [3][0] = 2.0  ; // DOT LINE
 dash_array [3][1] = 2.0  ;

 dash_array [4][0] = 10.0 ; //DASH_DOT LINE
 dash_array [4][1] = 2.0  ;
 dash_array [4][2] = 3.0  ;
 dash_array [4][3] = 2.0  ;

 dash_array [5][0] = 10.0 ; //DASH_DOT_DOT LINE
 dash_array [5][1] = 2.0  ;
 dash_array [5][2] = 3.0  ;
 dash_array [5][3] = 2.0  ;
 dash_array [5][4] = 3.0  ;
 dash_array [5][5] = 2.0  ;

 dash_array [6][0] = 1.0  ;
 dash_array [6][1] = 3.0  ;
 dash_array [6][2] = 1.0  ;
 dash_array [6][3] = 3.0  ;

 dash_array [7][0] = 1.0  ;
 dash_array [7][1] = 1.0  ;

 /*---------------------------------------------------------------------*/
 /* 2.9 Allocate ImageMagick Color Map                                  */
 /*---------------------------------------------------------------------*/
 for ( i=1 ; i<=14 ; i++ )
     {
      IMcolor [i] = NewPixelWand() ;
      switch (i)
        {
         case 1:
             if ( PixelSetColor(IMcolor[i],"blue") == MagickFalse )
                {
                 printf("ERROR :  allocating blue IMcolor");
                }
             break ;

         case 2:
             if ( PixelSetColor (IMcolor[i],"red") == MagickFalse )
                {
                 printf("ERROR :  allocating red IMcolor");
                }
             break ;

         case 3:
             if ( PixelSetColor (IMcolor[i],"pink") == MagickFalse )
                {
                 printf("ERROR :  allocating pink IMcolor");
                }
             break ;

         case 4:
             if ( PixelSetColor (IMcolor[i],"green") == MagickFalse )
                {
                 printf("ERROR :  allocating green IMcolor");
                }
             break ;

         case 5:
             if ( PixelSetColor (IMcolor[i],"cyan") == MagickFalse )
                {
                 printf("ERROR :  allocating cyan IMcolor");
                }
             break ;

         case 6:
             if ( PixelSetColor (IMcolor[i],"yellow") == MagickFalse )
                {
                 printf("ERROR :  allocating yellow IMcolor");
                }
             break ;

         case 7:
             if ( PixelSetColor (IMcolor[i],"white") == MagickFalse )
                {
                 printf("ERROR :  allocating white IMcolor");
                }
             break ;

         case 8:
             if ( PixelSetColor (IMcolor[i],"black") == MagickFalse )
                {
                 printf("ERROR :  allocating black IMcolor");
                }
             break ;

         case 9:
             if ( PixelSetColor (IMcolor[i],"gray") == MagickFalse )
                {
                 printf("ERROR :  allocating gray IMcolor");
                }
             break ;

         case 10:
             if ( PixelSetColor (IMcolor[i],"wheat") == MagickFalse )
                {
                 printf("ERROR :  allocating wheat IMcolor");
                }
             break ;

         case 11:
             if ( PixelSetColor (IMcolor[i],"brown") == MagickFalse )
                {
                 printf("ERROR :  allocating brown IMcolor");
                }
             break ;

         case 12:
             if ( PixelSetColor (IMcolor[i],"orange") == MagickFalse )
                {
                 printf("ERROR :  allocating orange IMcolor");
                }
             break ;

         case 13:
             if ( PixelSetColor (IMcolor[i],"light gray") == MagickFalse )
                {
                 printf("ERROR :  allocating light gray IMcolor");
                }
             break ;

         case 14:
             if ( PixelSetColor (IMcolor[i],"magenta") == MagickFalse )
                {
                 printf("ERROR :  allocating magenta IMcolor");
                }
             break ;
        }
     }

 fprintf (stdout,"INFO  : geoIMS initialization Compeleted\n\n");
}

 /*-----------------------------------------------------------------------------------------*/
 /*                                  3. Read Data File                                      */
 /*-----------------------------------------------------------------------------------------*/
 if ( strstr (sys.data_file,".infb") != NULL )
    {
     printf ("INFO  : geoIMS reading Binary INF File\n");
     infinbCB();
    }
 else
 if ( strstr (sys.data_file,".inf") != NULL )
    {
     printf ("INFO  : geoIMS reading Ascii INF File\n");
     infinaCB();
    }
 else
 if ( strstr (sys.data_file,".dxf") != NULL )
    {
     printf ("INFO  : geoIMS reading DXF File\n");
     strcpy (InputFile , sys.data_file);
     dxfin() ;
    }


 read_db (44,UTF_TEXT) ;
 utf8_2_arabic (UTF_TEXT,"OWN");

 /*-----------------------------------------------------------------------------------------*/
 /*                              4. Create geoIMS Web Listener                              */
 /*-----------------------------------------------------------------------------------------*/
 rc = pthread_create (&web_listener_thread,NULL,(void*)web_listener,NULL);
 if ( rc != 0 )
    {
     fprintf(stderr,"ERROR : Failed to create Web Listener Thread, geoIMS terminated\n");
     exit(-1) ;
    }
 else
    {
     fprintf(stdout,"INFO  : Web Listener Thread created successfully\n");
    }

 /*-----------------------------------------------------------------------------------------*/
 /*                                    5. Server Main Loop                                  */
 /*-----------------------------------------------------------------------------------------*/
 do
   {

    for ( i=1; i<200; i++ )
        {
         if ( session[i].status == 1 )
            {
             time (&current_time) ;
             sprintf(system_time,"%s",ctime(&current_time));
             system_time[24] = '\0' ;
             printf ("[%s] INFO  : Session[%d] will time-out in [%d] seconds ...\n",system_time,i,sys.session_timeout - (current_time - session[i].start_time) ) ;

             // Expire Session if timed-out
             if ( (current_time - session[i].start_time) > sys.session_timeout )
                {
                 strcpy (session[i].php_id,"") ;
                 session[i].status = 0 ;
                 fprintf(stdout,"[%s] INFO  : Session [%d] Expired ....\n",system_time,i) ;
                }
            }
        }

    time (&current_time) ;
    sprintf(system_time,"%s",ctime(&current_time));
    system_time[24] = '\0' ;
    fprintf(stdout,"[%s] INFO  : geoIMS Server running ...\n",system_time) ;

    system("/home/geoinfo/bin/ims_clean_maps");
    sleep(10) ;

    } while (1) ;

} // end of main ()

////////////////////////////////////////////////////////////////////////////////////////////////////
/*------------------------------------------------------------------------------------------------*/
/*                                      pan_left()                                                */
/*------------------------------------------------------------------------------------------------*/
////////////////////////////////////////////////////////////////////////////////////////////////////
void pan_left (char *image_file_name, int sid)
{
 /*----------------------------*/
 /*        Local Variables     */
 /*----------------------------*/
 double     x_diff                ;  // Pan working variable

 x_diff = session[sid].x_max - session[sid].x_min ;

 session[sid].x_min  = session[sid].x_min - .25 * x_diff ;
 session[sid].x_max  = session[sid].x_max - .25 * x_diff ;

 draw_all(image_file_name,sid)     ;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*------------------------------------------------------------------------------------------------*/
/*                                      pan_right()                                               */
/*------------------------------------------------------------------------------------------------*/
////////////////////////////////////////////////////////////////////////////////////////////////////
void pan_right (char *image_file_name, int sid)
{
 /*----------------------------*/
 /*        Local Variables     */
 /*----------------------------*/
 double     x_diff                ;  // Pan working variable

 x_diff = session[sid].x_max - session[sid].x_min ;

 session[sid].x_min  = session[sid].x_min + .25 * x_diff ;
 session[sid].x_max  = session[sid].x_max + .25 * x_diff ;

 draw_all(image_file_name,sid)     ;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                       pan_up()                                                 */
////////////////////////////////////////////////////////////////////////////////////////////////////
void pan_up (char *image_file_name, int sid)
{
 /*----------------------------*/
 /*        Local Variables     */
 /*----------------------------*/
 double     y_diff                ;  // Pan working variable

 y_diff = session[sid].y_max - session[sid].y_min ;

 session[sid].y_min  = session[sid].y_min + .25 * y_diff ;
 session[sid].y_max  = session[sid].y_max + .25 * y_diff ;

 draw_all(image_file_name,sid)  ;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                      pan_down()                                                */
////////////////////////////////////////////////////////////////////////////////////////////////////
void pan_down (char *image_file_name, int sid)
{
 /*----------------------------*/
 /*        Local Variables     */
 /*----------------------------*/
 double     y_diff                ;  // Pan working variable

 y_diff = session[sid].y_max - session[sid].y_min ;

 session[sid].y_min  = session[sid].y_min - .25 * y_diff ;
 session[sid].y_max  = session[sid].y_max - .25 * y_diff ;

 draw_all(image_file_name,sid)  ;
}
////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                         window()                                               */
////////////////////////////////////////////////////////////////////////////////////////////////////
void window (char *image_file_name,int x1_screen,int y1_screen,int x2_screen,int y2_screen,int sid)
{
 /*----------------------------*/
 /*        Local Variables     */
 /*----------------------------*/
 double     x_min,y_min           ; // Min x,y Limits of displayed Database
 double     x_max,y_max           ; // Max x,y Limits of displayed Database

 double     x1_db,y1_db           ; // Real world x-y coordinates
 double     x2_db,y2_db           ; // Real world x-y coordinates

 double     ONE_PIXEL             ; // Number of DB Unit per ONE Pixle
 double     x_diff,y_diff,xy_diff ; // Window working variable
 double     scale                 ; // Current Scale

 char       module[] = {"window"} ;


 // Copy Session xy Limit to Local Varibales
 x_min = session[sid].x_min ;
 y_min = session[sid].y_min ;
 x_max = session[sid].x_max ;
 y_max = session[sid].y_max ;


 // Calculate Realworld Cooridnate (DB Corrd.)
 y_diff    = y_max - y_min                        ;
 ONE_PIXEL = y_diff / (y_br_screen - y_ul_screen) ;

 x1_db = (x1_screen * ONE_PIXEL) + x_min ;
 y1_db = y_max - (y1_screen * ONE_PIXEL) ;

 x2_db = (x2_screen * ONE_PIXEL) + x_min ;
 y2_db = y_max - (y2_screen * ONE_PIXEL) ;


 ///////////////////------ CASE I ------/////////////////////
 if ( x1_db < x2_db && y1_db > y2_db )
    {
     x_min  = x1_db         ;
     y_min  = y2_db         ;
     x_max  = x2_db         ;
     y_max  = y1_db         ;
     x_diff = x_max - x_min ;
     y_diff = y_max - y_min ;

     if (x_diff > y_diff)
        {
         xy_diff = (x_diff - y_diff) / 2 ;
         y_min   = y_min - xy_diff       ;
         y_max   = y_max + xy_diff       ;
        }
   else  // if (y_diff > x_diff)
        {
         xy_diff = (y_diff - x_diff) / 2 ;
         x_min   = x_min - xy_diff       ;
         x_max   = x_max + xy_diff       ;
        }
    }

 ////////////////////----- CASE II ------//////////////////////
 if ( x1_db > x2_db && y1_db > y2_db )
    {
     x_min  = x2_db         ;
     y_min  = y2_db         ;
     x_max  = x1_db         ;
     y_max  = y1_db         ;
     x_diff = x_max - x_min ;
     y_diff = y_max - y_min ;

     if (x_diff > y_diff)
        {
         xy_diff = (x_diff - y_diff) / 2 ;
         y_min   = y_min - xy_diff       ;
         y_max   = y_max + xy_diff       ;
        }
    else // if (y_diff > x_diff)
        {
         xy_diff = (y_diff - x_diff) / 2 ;
         x_min   = x_min - xy_diff       ;
         x_max   = x_max + xy_diff       ;
        }
    }

 ////////////////////----- CASE III ------/////////////////////
 if ( x1_db < x2_db && y1_db < y2_db )
    {
     x_min  = x1_db ;
     y_min  = y1_db ;
     x_max  = x2_db ;
     y_max  = y2_db ;
     x_diff = x_max - x_min ;
     y_diff = y_max - y_min ;

     if (x_diff > y_diff)
        {
         xy_diff = (x_diff - y_diff) / 2 ;
         y_min   = y_min - xy_diff       ;
         y_max   = y_max + xy_diff       ;
        }
     else // if (y_diff > x_diff)
        {
         xy_diff = (y_diff - x_diff) / 2 ;
         x_min   = x_min - xy_diff       ;
         x_max   = x_max + xy_diff       ;
        }
    }
 ////////////////////----- CASE IV ------//////////////////////
 if ( x1_db > x2_db && y1_db < y2_db )
    {
     x_min  = x2_db ;
     y_min  = y1_db ;
     x_max  = x1_db ;
     y_max  = y2_db ;
     x_diff = x_max - x_min ;
     y_diff = y_max - y_min ;

     if (x_diff > y_diff)
        {
         xy_diff = (x_diff - y_diff) / 2 ;
         y_min   = y_min - xy_diff       ;
         y_max   = y_max + xy_diff       ;
        }
     else // if (y_diff > x_diff)
        {
         xy_diff = (y_diff - x_diff) / 2 ;
         x_min   = x_min - xy_diff       ;
         x_max   = x_max + xy_diff       ;
        }
    }


 //////////////-----  Calculate Current Scale -----///////////////
 y_diff = y_max - y_min ;
 switch (DB_UNIT)
        {
         case MM: scale = ( y_diff * .1   ) / SCREEN_CM ; break ;
         case CM: scale = ( y_diff * 1.   ) / SCREEN_CM ; break ;
         case DM: scale = ( y_diff * 10.  ) / SCREEN_CM ; break ;
         case  M: scale = ( y_diff * 100. ) / SCREEN_CM ; break ;
         case KM: scale = ( y_diff * 1000.) / SCREEN_CM ; break ;
         default: scale = ( y_diff * 100. ) / SCREEN_CM ;
                  fprintf(stderr,"[%s] ERROR : Data Base Unit not Defined\n",module);
                  break ;
        }

 // Check if (Current Scale >= 1) then we still can Zoom Window
 if ( scale >= 1 )
    {
     // Set New Window xy Limits
     session[sid].x_min = x_min ;
     session[sid].y_min = y_min ;
     session[sid].x_max = x_max ;
     session[sid].y_max = y_max ;
    }

 // Call draw_all
 draw_all(image_file_name,sid)  ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                      zoom_in()                                                 */
////////////////////////////////////////////////////////////////////////////////////////////////////
void zoom_in (char *image_file_name, int sid)
{
 /*----------------------------*/
 /*        Local Variables     */
 /*----------------------------*/
 double   x_diff                   ;  // Zoom in working variable
 double   y_diff                   ;  // Zoom in working variable
 double   scale                    ;  // Current Scale
 double   org_x_min                ;  // ORG Min x Limits of displayed Database
 double   org_y_min                ;  // ORG Min y Limits of displayed Database
 double   org_x_max                ;  // ORG Max x Limits of displayed Database
 double   org_y_max                ;  // ORG Max y Limits of displayed Database

 char     module[] = {"Zoom in"}   ;


 x_diff = session[sid].x_max - session[sid].x_min ;
 y_diff = session[sid].y_max - session[sid].y_min ;


 // Calculate Current Scale
 switch (DB_UNIT)
       {
        case MM: scale = ( y_diff * .1   ) / SCREEN_CM ; break ;
        case CM: scale = ( y_diff * 1.   ) / SCREEN_CM ; break ;
        case DM: scale = ( y_diff * 10.  ) / SCREEN_CM ; break ;
        case  M: scale = ( y_diff * 100. ) / SCREEN_CM ; break ;
        case KM: scale = ( y_diff * 1000.) / SCREEN_CM ; break ;
        default: scale = ( y_diff * 100. ) / SCREEN_CM ;
                 fprintf(stderr,"[%s] ERROR : Data Base unit not defined, assumed Meter\n",module);
                 break ;
       }

 // Check if (Current Scale >= 2) then we still can Zoom in
 if ( scale >= 2 )
    {
     // Assing new Zoom in xy Limits
     session[sid].x_min  = session[sid].x_min + .25 * x_diff ;
     session[sid].y_min  = session[sid].y_min + .25 * y_diff ;
     session[sid].x_max  = session[sid].x_max - .25 * x_diff ;
     session[sid].y_max  = session[sid].y_max - .25 * y_diff ;
    }

 draw_all (image_file_name, sid)  ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                          zoom_out()                                            */
////////////////////////////////////////////////////////////////////////////////////////////////////
void zoom_out (char *image_file_name, int sid)
{
 /*----------------------------*/
 /*        Local Variables     */
 /*----------------------------*/
 double    x_diff                ; // Zoom out working variable
 double    y_diff                ; // Zoom out working variable
 double    scale                 ; // Current Scale

 x_diff = session[sid].x_max - session[sid].x_min ;
 y_diff = session[sid].y_max - session[sid].y_min ;


 session[sid].x_min  = session[sid].x_min - .5 * x_diff ;
 session[sid].y_min  = session[sid].y_min - .5 * y_diff ;
 session[sid].x_max  = session[sid].x_max + .5 * x_diff ;
 session[sid].y_max  = session[sid].y_max + .5 * y_diff ;

 draw_all(image_file_name, sid)  ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                         draw_all()                                             */
////////////////////////////////////////////////////////////////////////////////////////////////////
void draw_all (char *image_file_name, int sid) // sid  --> Web_Client Session id
{
 /*-----------------------------------*/
 /*         Local Variables           */
 /*-----------------------------------*/
 MagickWand  *magick_wand                   ; // Session Magick Image   Object
 DrawingWand *draw_wand                     ; // Session Magick Drawing Object

 long        i,ii,j,jj                      ; // Loop Counters

 double      x_min,y_min                    ; // Session Min x,y Limits of displayed Database
 double      x_max,y_max                    ; // Session Max x,y Limits of displayed Database

 double      x_min1,x_min2,x_min3           ; // Session Min x Point/Line/Text Clipping Limits
 double      y_min1,y_min2,y_min3           ; // Session Min y Point/Line/Text Clipping Limits
 double      x_max1,x_max2,x_max3           ; // Session Max x Point/Line/Text Clipping Limits
 double      y_max1,y_max2,y_max3           ; // Session Max y Point/Line/Text Clipping Limits

 double      x1_clip,x2_clip                ; // Session x Clipping Limits
 double      y1_clip,y2_clip                ; // Session y Clipping Limits

 long        x_screen,x1_screen,x2_screen   ; // Session Equivlant x-y coord. on DrawingArea
 long        y_screen,y1_screen,y2_screen   ; // Session Equivlant x-y coord. on DrawingArea

 double      x_db,x1_db,x2_db               ; // Session Real world x-y coordinates
 double      y_db,y1_db,y2_db               ; // Session Real world x-y coordinates

 double      ONE_PIXEL                      ; // Session Number of DB Unit per ONE Pixle
 double      x_diff,y_diff,xy_diff          ; // Session Window / Zoom ALL  working variable
 double      scale                          ; // Session Current Scale
 int         sc_range                       ; // Session Current Scale Range

 double      tolerance                      ; // Session Correlation tolerance
 double      distance                       ; // Session Computed Distance
 double      radius                         ; // Session Computed Distance for Clipping

 double      symb_factor                    ; // Session Symbol Drawing Factor
 int         previous_symb                  ;

 long        x_base,y_base,x_end,y_end      ; // Session Feature x-y  enclosure box
 long        x_start_txt, y_start_txt       ; // Session Text Drawing Limits
 long        x_end_txt  , y_end_txt         ; // Session Text Drawing Limits
 long        text_buf                       ;

 char        module[] = {"draw_all"}        ; // Module Name


 /*------------------------------------------------------------------------*/
 /*                   Create ImageMagick Drawing Object                    */
 /*------------------------------------------------------------------------*/
 draw_wand = NewDrawingWand() ;  // Create DrawingWand Drawing Object

 /*------------------------------------------------------------------------*/
 /*       Get Session XY Limits & Calculate Feature Clipping Limits        */
 /*------------------------------------------------------------------------*/
 x_min  = session[sid].x_min     ;
 y_min  = session[sid].y_min     ;
 x_max  = session[sid].x_max     ;
 y_max  = session[sid].y_max     ;

 x_min1 = x_min - SYMBCLIPBUFFER ;  // Point Feature Clipping Limits
 y_min1 = y_min - SYMBCLIPBUFFER ;
 x_max1 = x_max + SYMBCLIPBUFFER ;
 y_max1 = y_max + SYMBCLIPBUFFER ;

 x_min2 = x_min - LINECLIPBUFFER ;  // Line Feature Clipping Limits
 y_min2 = y_min - LINECLIPBUFFER ;
 x_max2 = x_max + LINECLIPBUFFER ;
 y_max2 = y_max + LINECLIPBUFFER ;

 /*------------------------------------------------------------------------*/
 /*                     Calculate Drawing Paramters                        */
 /*------------------------------------------------------------------------*/
 y_diff    = y_max - y_min ;
 ONE_PIXEL = y_diff / (y_br_screen - y_ul_screen) ;

 switch (DB_UNIT)
      {
       case MM: scale = ( y_diff * .1   ) / SCREEN_CM ; break ;
       case CM: scale = ( y_diff * 1.   ) / SCREEN_CM ; break ;
       case DM: scale = ( y_diff * 10.  ) / SCREEN_CM ; break ;
       case  M: scale = ( y_diff * 100. ) / SCREEN_CM ; break ;
       case KM: scale = ( y_diff * 1000.) / SCREEN_CM ; break ;
       default: scale = ( y_diff * 100. ) / SCREEN_CM ;
                fprintf(stderr,"[%s] ERROR : Data Base Unit not Defined, default set to Meter\n",module);
                break ;
      }

      if ( scale > 0          &&  scale <= SC_RANGE1 ) sc_range = 0 ;
 else if ( scale > SC_RANGE1  &&  scale <= SC_RANGE2 ) sc_range = 1 ;
 else if ( scale > SC_RANGE2  &&  scale <= SC_RANGE3 ) sc_range = 2 ;
 else if ( scale > SC_RANGE3  &&  scale <= SC_RANGE4 ) sc_range = 3 ;
 else if ( scale > SC_RANGE4                         ) sc_range = 4 ;

 // printf("SCREEN_CM = [%f]\n",SCREEN_CM);
 // printf("scale     = [%f]\n",scale   );
 // printf("sc_range  = [%d]\n",sc_range);

 /*------------------------------------------------------------------------*/
 /*                              Main LOOP                                 */
 /*------------------------------------------------------------------------*/
 for (i=1; i<=feat_count; i++)
 {
 // if ( i == 9491 )
   //  {
    //  printf("Feature[%d] Color[%d] Ltype[%d] Lwidth[%d] \n",i,feat[i].color,feat[i].linetype,feat[i].linewidth);
   //  }

  switch (feat[i].type)
  {
   case 1:    /*---------- Draw type one -------------- */

    x_base = feat[i].xbase ;
    y_base = feat[i].ybase ;

    //  NEW Linux Only
    if (feat[i].has_text[0] == 'Y')
       {
        text_index = feat[i].text+1                           ;
           strcpy(text[text_index].string,UTF_TEXT)           ;  /////////// HANY HEGGY ARABIZATION ////////////

        font_no    = text[text_index].font                    ;
        size       = text[text_index].size                    ;
        angle      = (double)text[text_index].angle / DEG2RAD ;
        length     = strlen (text[text_index].string) - 1     ;

        x_start_txt = text[text_index].x  ;
        y_start_txt = text[text_index].y  ;
        text_buf = length * size    ;

        x_min3 = x_min - text_buf ;
        y_min3 = y_min - text_buf ;
        x_max3 = x_max + text_buf ;
        y_max3 = y_max + text_buf ;

        switch (text[text_index].just)
               {
                case 1: x_start_txt -= (size/2) * sin(angle);       /* Bottom */
                        y_start_txt -= (size/2) * cos(angle);
                        x_start_txt += (size/2) * cos(angle);       /* Left   */
                        y_start_txt -= (size/2) * sin(angle);
                        break;

                case 2: x_start_txt -= (size/2) * sin(angle);        /* Bottom */
                        y_start_txt -= (size/2) * cos(angle);
                        x_start_txt -= (length*size/2) * cos(angle); /* Center */
                        y_start_txt += (length*size/2) * sin(angle);
                        break;

                case 3: x_start_txt -= (size/2) * sin(angle);        /* Bottom */
                        y_start_txt -= (size/2) * cos(angle);
                        x_start_txt -= (length*size) * cos(angle);   /* Right  */
                        y_start_txt += (length*size) * sin(angle);
                        break;

                case 4: /* Middle */
                        x_start_txt += (size/2) * cos(angle);        /* Left   */
                        y_start_txt -= (size/2) * sin(angle);
                        break;

                case 5: /* Middle */
                        x_start_txt -= (length*size/2) * cos(angle); /* Center */
                        y_start_txt += (length*size/2) * sin(angle);
                        break;

                case 6: /* Middle */
                        x_start_txt -= (length*size) * cos(angle);   /* Right  */
                        y_start_txt += (length*size) * sin(angle);
                        break;

                case 7: x_start_txt += (size/2) * sin(angle);        /* Top  */
                        y_start_txt += (size/2) * cos(angle);
                        x_start_txt += (size/2) * cos(angle);        /* Left */
                        y_start_txt -= (size/2) * sin(angle);
                        break;

                case 8: x_start_txt += (size/2) * sin(angle);        /* Top    */
                        y_start_txt += (size/2) * cos(angle);
                        x_start_txt -= (length*size/2) * cos(angle); /* Center */
                        y_start_txt += (length*size/2) * sin(angle);
                        break;

                case 9: x_start_txt += (size/2) * sin(angle);        /* Top   */
                        y_start_txt += (size/2) * cos(angle);
                        x_start_txt -= (length*size) * cos(angle);   /* Right */
                        y_start_txt += (length*size) * sin(angle);
                        break;
              }

        x_end_txt = x_start_txt + length * size * cos(angle) ;
        y_end_txt = y_start_txt + length * size * sin(angle) ;

       }
     else
       {
        x_start_txt = 0 ;
        y_start_txt = 0 ;
        x_end_txt   = 0 ;
        y_end_txt   = 0 ;
       }


    /* BASE POINT CLIPPING & MIN SYMBOL SIZE = 1 &  Text Point Clipping */
    if ( ( feat[i].displayed[0] == 'Y'         ) &&
         ( feat[i].scale_range[sc_range] == 'Y') &&
         ( (feat[i].symb_size/ONE_PIXEL) >= 1  ) &&
         ( (x_base      >= x_min1 && x_base      <= x_max1 && y_base      >= y_min1 && y_base      <= y_max1) ||
           (x_start_txt >= x_min3 && x_start_txt <= x_max3 && y_start_txt >= y_min3 && y_start_txt <= y_max3) ||
           (x_end_txt   >= x_min3 && x_end_txt   <= x_max3 && y_end_txt   >= y_min3 && y_end_txt   <= y_max3) )
       )
     {
      DrawSetStrokeColor     ( draw_wand, IMcolor[feat[i].color] );  // set color
  //  DrawSetStrokeWidth     ( draw_wand, feat[i].linewidth      );  // set line width  HANY
  //  DrawSetStrokeWidth     ( draw_wand, 1  );
     if ( feat[i].linewidth >= 1 )
        {
         DrawSetStrokeWidth ( draw_wand, feat[i].linewidth );
        }
     else
        {
         printf("Feature[%d] TYPE [%d] Color[%d] Ltype[%d] Lwidth[%d] \n",i,feat[i].type,feat[i].color,feat[i].linetype,feat[i].linewidth);
         DrawSetStrokeWidth ( draw_wand, 1  );
        }


      switch (feat[i].linetype)                                      // set line type
             {
              case 1:
                DrawSetStrokeDashArray ( draw_wand, 0, dash_array[0] );
                break;

              default:
                DrawSetStrokeDashArray ( draw_wand, 2, dash_array[feat[i].linetype] );
                break;
             }

      /*....................*/
      /*  DRAW TEXT IF ANY  */
      /*....................*/
      if (feat[i].has_text[0] == 'Y')
         {
          for(ii=1; ii<=feat[i].text_count; ii++)
             {
              text_index = feat[i].text + ii                        ;
              font_no    = text[text_index].font                    ;
                strcpy(text[text_index].string,UTF_TEXT)              ;  /////////// HANY HEGGY ARABIZATION ////////////
                font_no    = 21                                       ;  /////////// HANY HEGGY ARABIZATION ////////////
              size       = text[text_index].size                    ;
              angle      = (double)text[text_index].angle / DEG2RAD ;
              length     = strlen (text[text_index].string) - 1     ;

              x_db       = text[text_index].x - x_min  ;
              y_db       = y_max - text[text_index].y  ;

              switch (text[text_index].just)
                     {
                      case 1: x_db -= (size/2) * sin(angle);       /* Bottom */
                              y_db -= (size/2) * cos(angle);
                              x_db += (size/2) * cos(angle);       /* Left   */
                              y_db -= (size/2) * sin(angle);
                              break;

                      case 2: x_db -= (size/2) * sin(angle);        /* Bottom */
                              y_db -= (size/2) * cos(angle);
                              x_db -= (length*size/2) * cos(angle); /* Center */
                              y_db += (length*size/2) * sin(angle);
                              break;

                      case 3: x_db -= (size/2) * sin(angle);        /* Bottom */
                              y_db -= (size/2) * cos(angle);
                              x_db -= (length*size) * cos(angle);   /* Right  */
                              y_db += (length*size) * sin(angle);
                              break;

                      case 4: /* Middle */
                              x_db += (size/2) * cos(angle);        /* Left   */
                              y_db -= (size/2) * sin(angle);
                              break;

                      case 5: /* Middle */
                              x_db -= (length*size/2) * cos(angle); /* Center */
                              y_db += (length*size/2) * sin(angle);
                              break;

                      case 6: /* Middle */
                              x_db -= (length*size) * cos(angle);   /* Right  */
                              y_db += (length*size) * sin(angle);
                              break;

                      case 7: x_db += (size/2) * sin(angle);        /* Top  */
                              y_db += (size/2) * cos(angle);
                              x_db += (size/2) * cos(angle);        /* Left */
                              y_db -= (size/2) * sin(angle);
                              break;

                      case 8: x_db += (size/2) * sin(angle);        /* Top    */
                              y_db += (size/2) * cos(angle);
                              x_db -= (length*size/2) * cos(angle); /* Center */
                              y_db += (length*size/2) * sin(angle);
                              break;

                      case 9: x_db += (size/2) * sin(angle);        /* Top   */
                              y_db += (size/2) * cos(angle);
                              x_db -= (length*size) * cos(angle);   /* Right */
                              y_db += (length*size) * sin(angle);
                              break;
                     }

              for (j=0; j<=length ; j++)
                  {
                   symb_no     = 0                                         ;
                   symb_no     = text[text_index].string[j]                ;
                   //if ( symb_no < 0 )  { symb_no += 256 ; }  /// Arabization
                   //else                { symb_no -= 1   ; }
                   symb_factor = (float)size / font[font_no][symb_no].grid ;

                   if ( j != 0 )
                      {
                       previous_symb = text[text_index].string[j-1]                      ;
                       //if ( previous_symb < 0 ) { previous_symb += 256 ; } /// Arabization
                       //else                     { previous_symb -= 1   ; }
                       x_db += size * font[font_no][previous_symb].x_factor * cos(angle) ;
                       y_db -= size * font[font_no][previous_symb].x_factor * sin(angle) ;
                      }

                     // Text Clipping on ONE Charcter Level
                     if ( (x_db+x_min) >= (x_min-size/2) && (x_db+x_min) <= (x_max+size/2) &&
                          (y_max-y_db) >= (y_min-size/2) && (y_max-y_db) <= (y_max+size/2) )
                      {
                       for ( jj=1; jj<=font[font_no][symb_no].stroke; jj++)
                           {
                            switch (font[font_no][symb_no].mv_draw[jj])
                             {
                              case 0:     /*  Move  */
                               angle_sym = font[font_no][symb_no].angle[jj] + angle ;
                               x1_screen = (x_db + symb_factor * font[font_no][symb_no].distance[jj] * cos(angle_sym))/ONE_PIXEL;
                               y1_screen = (y_db - symb_factor * font[font_no][symb_no].distance[jj] * sin(angle_sym))/ONE_PIXEL;
                               break ;

                              case 1:     /*  Draw  */
                               angle_sym = font[font_no][symb_no].angle[jj] + angle ;
                               x2_screen = (x_db + symb_factor * font[font_no][symb_no].distance[jj] * cos(angle_sym))/ONE_PIXEL;
                               y2_screen = (y_db - symb_factor * font[font_no][symb_no].distance[jj] * sin(angle_sym))/ONE_PIXEL;

                               DrawLine ( draw_wand,x1_screen,y1_screen,x2_screen,y2_screen );

                               x1_screen = x2_screen ;
                               y1_screen = y2_screen ;
                               break ;
                             }
                           }
                      }
                  }
             }
         }

      /*...............*/
      /*  DRAW SYMBOL  */
      /*...............*/

      symb_no     = feat[i].symb_num ;
      angle       = (double)feat[i].symb_angle / DEG2RAD ;
      symb_factor = (double)feat[i].symb_size  / symb[symb_no].grid ;

      for ( ii=1; ii<=symb[symb_no].stroke; ii++)
        {
         switch (symb[symb_no].mv_draw[ii])
          {
           case 0:     /*  Move  */

             angle_sym = symb[symb_no].angle[ii] + angle ;
             x1_screen = (x_base - x_min  + symb_factor * symb[symb_no].distance[ii] * cos(angle_sym)) / ONE_PIXEL ;
             y1_screen = (y_max  - y_base - symb_factor * symb[symb_no].distance[ii] * sin(angle_sym)) / ONE_PIXEL ;
             break ;

           case 1:     /*  Draw  */

             angle_sym = symb[symb_no].angle[ii] + angle ;
             x2_screen = (x_base - x_min  + symb_factor * symb[symb_no].distance[ii] * cos(angle_sym)) / ONE_PIXEL ;
             y2_screen = (y_max  - y_base - symb_factor * symb[symb_no].distance[ii] * sin(angle_sym)) / ONE_PIXEL ;

             DrawLine ( draw_wand,x1_screen,y1_screen,x2_screen,y2_screen );


             x1_screen = x2_screen ;
             y1_screen = y2_screen ;
             break ;
          }
       }

    }
    break ;


   case 2:    /*-------------- Draw type two --------------------*/

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

     DrawSetStrokeColor     ( draw_wand, IMcolor[feat[i].color]);
     if ( feat[i].linewidth >= 1 )
        {
         DrawSetStrokeWidth ( draw_wand, feat[i].linewidth );
        }
     else
        {
         printf("Feature[%d] TYPE [%d] Color[%d] Ltype[%d] Lwidth[%d] \n",i,feat[i].type,feat[i].color,feat[i].linetype,feat[i].linewidth);
         DrawSetStrokeWidth ( draw_wand, 1  );
        }

     switch (feat[i].linetype)
            {
             case 1:
               DrawSetStrokeDashArray ( draw_wand, 0, dash_array[0] );
               break;

             default:
               DrawSetStrokeDashArray ( draw_wand, 2, dash_array[feat[i].linetype] );
               break;
            }

     /*....................*/
     /*  DRAW TEXT IF ANY  */
     /*....................*/
     if (feat[i].has_text[0] == 'Y')
        {
         for(ii=1; ii<=feat[i].text_count; ii++)
            {
             text_index = feat[i].text + ii     ;
                strcpy(text[text_index].string,UTF_TEXT) ; /////////// HANY HEGGY ARABIZATION ////////////
             size       = text[text_index].size ;
             x_db       = text[text_index].x    ;
             y_db       = text[text_index].y    ;

             /*  TEXT CLIPPING  */
             if ( (x_db >= x_min1)&&(x_db <= x_max1) &&
                  (y_db >= y_min1)&&(y_db <= y_max1) &&
                  ((size/ONE_PIXEL) >= 1)  )
                {
                 font_no = text[text_index].font                    ;
                 angle   = (double)text[text_index].angle / DEG2RAD ;
                 length  = strlen (text[text_index].string) -1      ;

                 x_db   = text[text_index].x - x_min  ;
                 y_db   = y_max - text[text_index].y  ;

                 switch (text[text_index].just)
                        {
                         case 1: x_db -= (size/2) * sin(angle);       /* Bottom */
                                 y_db -= (size/2) * cos(angle);
                                 x_db += (size/2) * cos(angle);       /* Left   */
                                 y_db -= (size/2) * sin(angle);
                                 break;

                         case 2: x_db -= (size/2) * sin(angle);        /* Bottom */
                                 y_db -= (size/2) * cos(angle);
                                 x_db -= (length*size/2) * cos(angle); /* Center */
                                 y_db += (length*size/2) * sin(angle);
                                 break;

                         case 3: x_db -= (size/2) * sin(angle);        /* Bottom */
                                 y_db -= (size/2) * cos(angle);
                                 x_db -= (length*size) * cos(angle);   /* Right  */
                                 y_db += (length*size) * sin(angle);
                                 break;

                         case 4: /* Middle */
                                 x_db += (size/2) * cos(angle);        /* Left   */
                                 y_db -= (size/2) * sin(angle);
                                 break;

                         case 5: /* Middle */
                                 x_db -= (length*size/2) * cos(angle); /* Center */
                                 y_db += (length*size/2) * sin(angle);
                                 break;

                         case 6: /* Middle */
                                 x_db -= (length*size) * cos(angle);   /* Right  */
                                 y_db += (length*size) * sin(angle);
                                 break;

                         case 7: x_db += (size/2) * sin(angle);        /* Top  */
                                 y_db += (size/2) * cos(angle);
                                 x_db += (size/2) * cos(angle);        /* Left */
                                 y_db -= (size/2) * sin(angle);
                                 break;

                         case 8: x_db += (size/2) * sin(angle);        /* Top    */
                                 y_db += (size/2) * cos(angle);
                                 x_db -= (length*size/2) * cos(angle); /* Center */
                                 y_db += (length*size/2) * sin(angle);
                                 break;

                         case 9: x_db += (size/2) * sin(angle);        /* Top   */
                                 y_db += (size/2) * cos(angle);
                                 x_db -= (length*size) * cos(angle);   /* Right */
                                 y_db += (length*size) * sin(angle);
                                 break;
                        }

                 for ( j=0 ; j<=length ; j++ )
                     {
                      symb_no     = 0 ;
                      symb_no     = text[text_index].string[j]                ;
                      //if ( symb_no < 0 ) { symb_no += 256 ; }  /// Arabization
                      //else               { symb_no -= 1   ; }
                      symb_factor = (float)size / font[font_no][symb_no].grid ;

                      if ( j != 0 )
                         {
                          previous_symb = text[text_index].string[j-1] ;
                          //if ( previous_symb < 0 )  { previous_symb += 256 ; }  /// Arabization
                          // else                       { previous_symb -= 1   ; }
                          x_db += size * font[font_no][previous_symb].x_factor * cos(angle) ;
                          y_db -= size * font[font_no][previous_symb].x_factor * sin(angle) ;
                         }

                      for ( jj=1 ; jj<=font[font_no][symb_no].stroke ; jj++ )
                          {
                           switch (font[font_no][symb_no].mv_draw[jj])
                           {
                            case 0:     /*  Move  */

                              angle_sym = font[font_no][symb_no].angle[jj] + angle ;
                              x1_screen = (x_db + symb_factor * font[font_no][symb_no].distance[jj] * cos(angle_sym))/ONE_PIXEL;
                              y1_screen = (y_db - symb_factor * font[font_no][symb_no].distance[jj] * sin(angle_sym))/ONE_PIXEL;
                              break ;

                            case 1:     /*  Draw  */

                              angle_sym = font[font_no][symb_no].angle[jj] + angle ;
                              x2_screen = (x_db + symb_factor * font[font_no][symb_no].distance[jj] * cos(angle_sym))/ONE_PIXEL;
                              y2_screen = (y_db - symb_factor * font[font_no][symb_no].distance[jj] * sin(angle_sym))/ONE_PIXEL;

                              DrawLine ( draw_wand,x1_screen,y1_screen,x2_screen,y2_screen );

                              x1_screen = x2_screen ;
                              y1_screen = y2_screen ;
                              break ;
                           }
                          }
                     }
                }
            }
        }

     /*...........*/
     /* DRAW LINE */
     /*...........*/

     for ( ii=0 ; ii<=(feat[i].xy_count+1) ; ii++ )
         {
          switch (ii)
              {
               case 0:
                   x1_db = x_base ;
                   y1_db = y_base ;

                   x1_screen = (x1_db - x_min) / ONE_PIXEL ;
                   y1_screen = (y_max - y1_db) / ONE_PIXEL ;
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
                   x2_screen = (x2_db - x_min) / ONE_PIXEL ;
                   y2_screen = (y_max - y2_db) / ONE_PIXEL ;



                   if (( x1_db>=x_min && x1_db<=x_max && y1_db>=y_min && y1_db<=y_max ) &&
                       ( x2_db>=x_min && x2_db<=x_max && y2_db>=y_min && y2_db<=y_max ) )
                      {
                       DrawLine ( draw_wand,x1_screen,y1_screen,x2_screen,y2_screen );
                      }

              else if ( x1_db>=x_min && x1_db<=x_max && y1_db>=y_min && y1_db<=y_max )
                      {
                       if ( x1_db == x2_db )   /* VL Segment */
                          {
                           if ( y2_db > y1_db )
                              {
                               x2_screen = (x2_db - x_min) / ONE_PIXEL;
                               y2_screen = (y_max - y_max) / ONE_PIXEL;
                              }
                            else
                              {
                               x2_screen = (x2_db - x_min) / ONE_PIXEL ;
                               y2_screen = (y_max - y_min) / ONE_PIXEL ;
                              }
                           DrawLine ( draw_wand,x1_screen,y1_screen,x2_screen,y2_screen );
                           goto end ;
                          }

                       if ( y1_db == y2_db )    /* HZ Segment */
                          {
                           if ( x2_db > x1_db )
                              {
                               x2_screen = (x_max - x_min) / ONE_PIXEL ;
                               y2_screen = (y_max - y2_db) / ONE_PIXEL ;
                              }
                            else
                              {
                               x2_screen = (x_min - x_min) / ONE_PIXEL ;
                               y2_screen = (y_max - y2_db) / ONE_PIXEL ;
                              }
                           DrawLine ( draw_wand,x1_screen,y1_screen,x2_screen,y2_screen );
                           goto end ;
                          }

                       b = (y2_db - y1_db)/(x2_db - x1_db) ;
                       a = y1_db - (b * x1_db) ;

                       x_bot   = (y_min - a) / b ;
                       x_top   = (y_max - a) / b ;
                       y_left  = a + (b * x_min) ;
                       y_right = a + (b * x_max) ;

                       if ((x_bot>x_min && x_bot<x_max) &&
                          ((x_bot>x1_db && x_bot<x2_db) || (x_bot>x2_db && x_bot<x1_db)))
                          {
                           x2_screen = (x_bot - x_min) / ONE_PIXEL  ;
                           y2_screen = (y_max - y_min) / ONE_PIXEL ;
                           DrawLine ( draw_wand,x1_screen,y1_screen,x2_screen,y2_screen );
                          }
                  else if ((x_top>x_min && x_top<x_max) &&
                          ((x_top>x1_db && x_top<x2_db) || (x_top>x2_db && x_top<x1_db)))
                          {
                           x2_screen = (x_top - x_min) / ONE_PIXEL ;
                           y2_screen = (y_max - y_max) / ONE_PIXEL ;
                           DrawLine ( draw_wand,x1_screen,y1_screen,x2_screen,y2_screen );
                          }
                  else if ((y_left>y_min && y_left<y_max) &&
                          ((y_left>y1_db && y_left<y2_db) || (y_left>y2_db && y_left<y1_db)))
                          {
                           x2_screen = (x_min - x_min ) / ONE_PIXEL ;
                           y2_screen = (y_max - y_left) / ONE_PIXEL ;
                           DrawLine ( draw_wand,x1_screen,y1_screen,x2_screen,y2_screen );
                          }
                  else if ((y_right>y_min && y_right<y_max) &&
                          ((y_right>y1_db && y_right<y2_db) || (y_right>y2_db && y_right<y1_db)))
                          {
                           x2_screen = (x_max - x_min  ) / ONE_PIXEL ;
                           y2_screen = (y_max - y_right) / ONE_PIXEL ;
                           DrawLine ( draw_wand,x1_screen,y1_screen,x2_screen,y2_screen );
                          }
                      }

              else if ( x2_db>=x_min && x2_db<=x_max && y2_db>=y_min && y2_db<=y_max )
                      {

                       if ( x1_db == x2_db )   /* VL Segment */
                          {
                           if ( y1_db > y2_db )
                              {
                               x1_screen = (x1_db - x_min) / ONE_PIXEL ;
                               y1_screen = (y_max - y_max) / ONE_PIXEL ;
                              }
                            else
                              {
                               x1_screen = (x1_db - x_min) / ONE_PIXEL ;
                               y1_screen = (y_max - y_min) / ONE_PIXEL ;
                              }
                           DrawLine ( draw_wand,x1_screen,y1_screen,x2_screen,y2_screen );
                           goto end ;
                          }

                       if ( y1_db == y2_db )    /* HZ Segment */
                          {
                           if ( x1_db > x2_db )
                              {
                               x1_screen = (x_max - x_min) / ONE_PIXEL ;
                               y1_screen = (y_max - y1_db) / ONE_PIXEL ;
                              }
                            else
                              {
                               x1_screen = (x_min - x_min) / ONE_PIXEL ;
                               y1_screen = (y_max - y1_db) / ONE_PIXEL ;
                              }
                           DrawLine ( draw_wand,x1_screen,y1_screen,x2_screen,y2_screen );
                           goto end ;
                          }

                       b = (y2_db - y1_db)/(x2_db - x1_db) ;
                       a = y1_db - (b * x1_db) ;

                       x_bot   = (y_min - a) / b ;
                       x_top   = (y_max - a) / b ;
                       y_left  = a + (b * x_min) ;
                       y_right = a + (b * x_max) ;

                       if ((x_bot>x_min && x_bot<x_max) &&
                          ((x_bot>x1_db && x_bot<x2_db) || (x_bot>x2_db && x_bot<x1_db)))
                          {
                           x1_screen = (x_bot - x_min) / ONE_PIXEL ;
                           y1_screen = (y_max - y_min) / ONE_PIXEL ;
                           DrawLine ( draw_wand,x1_screen,y1_screen,x2_screen,y2_screen );
                          }
                  else if ((x_top>x_min && x_top<x_max) &&
                          ((x_top>x1_db && x_top<x2_db) || (x_top>x2_db && x_top<x1_db)))
                          {
                           x1_screen = (x_top - x_min) / ONE_PIXEL ;
                           y1_screen = (y_max - y_max) / ONE_PIXEL ;
                           DrawLine ( draw_wand,x1_screen,y1_screen,x2_screen,y2_screen );
                          }
                  else if ((y_left>y_min && y_left<y_max) &&
                          ((y_left>y1_db && y_left<y2_db) || (y_left>y2_db && y_left<y1_db)))
                          {
                           x1_screen = (x_min - x_min ) / ONE_PIXEL ;
                           y1_screen = (y_max - y_left) / ONE_PIXEL ;
                           DrawLine ( draw_wand,x1_screen,y1_screen,x2_screen,y2_screen );
                          }
                  else if ((y_right>y_min && y_right<y_max) &&
                          ((y_right>y1_db && y_right<y2_db) || (y_right>y2_db && y_right<y1_db)))
                          {
                           x1_screen = (x_max - x_min  ) / ONE_PIXEL ;
                           y1_screen = (y_max - y_right) / ONE_PIXEL ;
                           DrawLine ( draw_wand,x1_screen,y1_screen,x2_screen,y2_screen );
                          }
                      }
                  else
                      {
                       b = (y2_db - y1_db)/(x2_db - x1_db) ;
                       a = y1_db - (b * x1_db) ;

                       /* --------------------- CASE I ----------------------- */
                       if ((y1_db < y_min && y2_db > y_max) || (y2_db < y_min && y1_db > y_max))
                          {
                           if ( x2_db == x1_db && (x1_db > x_min && x1_db < x_max) )  /* VL Segment */
                              {                                       /* VL BUG solved 3/7/2002 */
                               x1_clip = x1_db ;  y1_clip = y_min ;
                               x2_clip = x2_db ;  y2_clip = y_max ;

                               x1_screen = (x1_clip - x_min) / ONE_PIXEL ;
                               y1_screen = (y_max - y1_clip) / ONE_PIXEL ;
                               x2_screen = (x2_clip - x_min) / ONE_PIXEL ;
                               y2_screen = (y_max - y2_clip) / ONE_PIXEL ;
                               DrawLine ( draw_wand,x1_screen,y1_screen,x2_screen,y2_screen );
                               goto end ;
                              }

                           x_bot = (y_min - a) / b ;
                           x_top = (y_max - a) / b ;

                           if (x_bot > x_min && x_bot < x_max)
                              {
                               x1_clip = x_bot ;
                               y1_clip = y_min ;
                              }
                           else
                              { goto next2 ; }

                           if (x_top  > x_min && x_top  < x_max)
                              {
                               x2_clip = x_top ;
                               y2_clip = y_max ;

                               x1_screen = (x1_clip - x_min) / ONE_PIXEL ;
                               y1_screen = (y_max - y1_clip) / ONE_PIXEL ;
                               x2_screen = (x2_clip - x_min) / ONE_PIXEL ;
                               y2_screen = (y_max - y2_clip) / ONE_PIXEL ;
                               DrawLine ( draw_wand,x1_screen,y1_screen,x2_screen,y2_screen );
                               goto end ;
                              }
                          }
                       next2:
                       /* --------------------- CASE II ---------------------- */
                       if ((x1_db < x_min && x2_db > x_max) || (x2_db < x_min && x1_db > x_max))
                          {
                           y_left  = a + (b * x_min) ;
                           y_right = a + (b * x_max) ;

                           if (y_left > y_min && y_left < y_max)
                              {
                               x1_clip = x_min  ;
                               y1_clip = y_left ;
                              }
                           else
                              { goto next3 ; }

                           if (y_right > y_min && y_right < y_max)
                              {
                               x2_clip = x_max   ;
                               y2_clip = y_right ;

                               x1_screen = (x1_clip - x_min) / ONE_PIXEL ;
                               y1_screen = (y_max - y1_clip) / ONE_PIXEL ;
                               x2_screen = (x2_clip - x_min) / ONE_PIXEL ;
                               y2_screen = (y_max - y2_clip) / ONE_PIXEL ;
                               DrawLine ( draw_wand,x1_screen,y1_screen,x2_screen,y2_screen );
                               goto end ;
                              }
                          }
                       next3:
                       /* --------------------- CASE III --------------------- */
                       if ((y1_db < y_min && x2_db > x_max) || (y2_db < y_min && x1_db > x_max))
                          {
                           x_bot   = (y_min - a) / b ;
                           y_right = a + (b * x_max) ;

                           if (x_bot > x_min && x_bot < x_max)
                              {
                               x1_clip = x_bot ;
                               y1_clip = y_min ;
                              }
                           else
                              { goto next4 ; }

                           if (y_right > y_min && y_right < y_max)
                              {
                               x2_clip = x_max   ;
                               y2_clip = y_right ;

                               x1_screen = (x1_clip - x_min) / ONE_PIXEL ;
                               y1_screen = (y_max - y1_clip) / ONE_PIXEL ;
                               x2_screen = (x2_clip - x_min) / ONE_PIXEL ;
                               y2_screen = (y_max - y2_clip) / ONE_PIXEL ;
                               DrawLine ( draw_wand,x1_screen,y1_screen,x2_screen,y2_screen );
                               goto end ;
                              }
                          }
                       next4:
                       /* --------------------- CASE IV ---------------------- */
                       if ((y1_db < y_min && x2_db < x_min) || (y2_db < y_min && x1_db < x_min))
                          {
                           x_bot  = (y_min - a) / b ;
                           y_left = a + (b * x_min) ;

                           if (x_bot > x_min && x_bot < x_max)
                              {
                               x1_clip = x_bot ;
                               y1_clip = y_min ;
                              }
                           else
                              { goto next5 ; }

                           if (y_left > y_min && y_left < y_max)
                              {
                               x2_clip = x_min   ;
                               y2_clip = y_left  ;

                               x1_screen = (x1_clip - x_min) / ONE_PIXEL ;
                               y1_screen = (y_max - y1_clip) / ONE_PIXEL ;
                               x2_screen = (x2_clip - x_min) / ONE_PIXEL ;
                               y2_screen = (y_max - y2_clip) / ONE_PIXEL ;
                               DrawLine ( draw_wand,x1_screen,y1_screen,x2_screen,y2_screen );
                               goto end ;
                              }
                          }
                       next5:
                       /* --------------------- CASE V ----------------------- */
                       if ((y2_db > y_max && x1_db > x_max) || (y1_db > y_max && x2_db > x_max))
                          {
                           x_top   = (y_max - a) / b ;
                           y_right = a + (b * x_max) ;

                           if (x_top  > x_min && x_top  < x_max)
                              {
                               x1_clip = x_top ;
                               y1_clip = y_max ;
                              }
                           else
                              { goto next6 ; }

                           if (y_right > y_min && y_right < y_max)
                              {
                               x2_clip = x_max   ;
                               y2_clip = y_right ;

                               x1_screen = (x1_clip - x_min) / ONE_PIXEL ;
                               y1_screen = (y_max - y1_clip) / ONE_PIXEL ;
                               x2_screen = (x2_clip - x_min) / ONE_PIXEL ;
                               y2_screen = (y_max - y2_clip) / ONE_PIXEL ;
                               DrawLine ( draw_wand,x1_screen,y1_screen,x2_screen,y2_screen );
                               goto end ;
                              }
                          }
                       next6:
                       /* --------------------- CASE VI ---------------------- */
                       if ((y2_db > y_max && x1_db < x_min) || (y1_db > y_max && x2_db < x_min))
                          {
                           x_top  = (y_max - a) / b ;
                           y_left = a + (b * x_min) ;

                           if (x_top  > x_min && x_top  < x_max)
                              {
                               x1_clip = x_top ;
                               y1_clip = y_max ;
                              }
                           else
                              { goto end ; }

                           if (y_left > y_min && y_left < y_max)
                              {
                               x2_clip = x_min   ;
                               y2_clip = y_left  ;

                               x1_screen = (x1_clip - x_min) / ONE_PIXEL ;
                               y1_screen = (y_max - y1_clip) / ONE_PIXEL ;
                               x2_screen = (x2_clip - x_min) / ONE_PIXEL ;
                               y2_screen = (y_max - y2_clip) / ONE_PIXEL ;

                               DrawLine ( draw_wand,x1_screen,y1_screen,x2_screen,y2_screen );
                               goto end ;
                              }
                          }

                       }

                    end:

                    x1_db = x[feat[i].xy+ii] ;
                    y1_db = y[feat[i].xy+ii] ;

                    x1_screen = x2_screen ;
                    y1_screen = y2_screen ;
                    break ;
              }
         }

    }
    break ;


   default:   /*---------------- Do nothing ----------------------*/
     break ;
  }

 }

 /*------------------------------------------------------------------------*/
 /*                  Create ImageMagick Image Object                       */
 /*------------------------------------------------------------------------*/
 magick_wand = NewMagickWand ();  // Create MagickWand  Image   Object

 MagickSetImageDepth ( magick_wand, 8  );
 if ( MagickNewImage ( magick_wand,  500, 500 , IMcolor[8]  ) != MagickTrue )
    {
     printf("[$s] ERROR : Cannot create 500x500 blank image \n",module);
     exit(-999) ;
    }

 /*------------------------------------------------------------------------*/
 /*            Copy draw_wand to magick_wand & save Image File             */
 /*------------------------------------------------------------------------*/
 MagickDrawImage ( magick_wand, draw_wand );

 MagickSetImageDepth ( magick_wand, 8  );
 if ( MagickWriteImage( magick_wand, image_file_name ) == MagickFalse )
    {
     printf ("ERROR : ImageMagick, Cannot write image file");
    }


 /*------------------------------------------------------------------------*/
 /*                  Destroy ImageMagick Image Objects                     */
 /*------------------------------------------------------------------------*/
 DestroyMagickWand ( magick_wand );
 DestroyDrawingWand( draw_wand  );

}

////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                        zoom_all()                                              */
////////////////////////////////////////////////////////////////////////////////////////////////////
void zoom_all ( char *image_file_name, int sid )
{
 /*-----------------------------------*/
 /*         Local Variables           */
 /*-----------------------------------*/
 MagickWand  *magick_wand                   ; // Session Magick Image   Object
 DrawingWand *draw_wand                     ; // Session Magick Drawing Object

 long        i,ii,j,jj                      ; // Loop Counters

 double      x_min,y_min                    ; // Session Min x,y Limits of displayed Database
 double      x_max,y_max                    ; // Session Max x,y Limits of displayed Database

 double      x_min1,x_min2,x_min3           ; // Session Min x Point/Line/Text Clipping Limits
 double      y_min1,y_min2,y_min3           ; // Session Min y Point/Line/Text Clipping Limits
 double      x_max1,x_max2,x_max3           ; // Session Max x Point/Line/Text Clipping Limits
 double      y_max1,y_max2,y_max3           ; // Session Max y Point/Line/Text Clipping Limits

 double      x1_clip,x2_clip                ; // Session x Clipping Limits
 double      y1_clip,y2_clip                ; // Session y Clipping Limits

 long        x_screen,x1_screen,x2_screen   ; // Session Equivlant x-y coord. on DrawingArea
 long        y_screen,y1_screen,y2_screen   ; // Session Equivlant x-y coord. on DrawingArea

 double      x_db,x1_db,x2_db               ; // Session Real world x-y coordinates
 double      y_db,y1_db,y2_db               ; // Session Real world x-y coordinates

 double      ONE_PIXEL                      ; // Session Number of DB Unit per ONE Pixle
 double      x_diff,y_diff,xy_diff          ; // Session Window / Zoom ALL  working variable
 double      scale                          ; // Session Current Scale
 int         sc_range                       ; // Session Current Scale Range

 double      tolerance                      ; // Session Correlation tolerance
 double      distance                       ; // Session Computed Distance
 double      radius                         ; // Session Computed Distance for Clipping

 double      symb_factor                    ; // Session Symbol Drawing Factor
 int         previous_symb                  ;

 long        x_base,y_base,x_end,y_end      ; // Session Feature x-y  enclosure box
 long        x_start_txt,y_start_txt        ; // Session Text Drawing Limits
 long        x_end_txt,y_end_txt            ; // Session Text Drawing Limits
 long        text_buf                       ; //

 long        text_index                     ; //
 int         size                           ; //

 long        x_min_all = 900000000          ; //
 long        y_min_all = 900000000          ; //
 long        x_max_all = 0                  ; //
 long        y_max_all = 0                  ; //

 char        module[]  = {"zoom_all"}       ; // Module Name


 /*------------------------------------------------------------------------*/
 /*                   Check if any feature found                           */
 /*------------------------------------------------------------------------*/
 if ( feat_count < 1 )
    {
     fprintf(stdout,"[%s] INFO : No features found ..\n",module);
     return ;
    }

 /*------------------------------------------------------------------------*/
 /*                   Create ImageMagick Drawing Object                    */
 /*------------------------------------------------------------------------*/
 draw_wand = NewDrawingWand();

 /*------------------------------------------------------------------------*/
 /*                     Calculate Min & Max Coordinates                    */
 /*------------------------------------------------------------------------*/
 for ( i=1; i<=feat_count; i++ )
 {
  if ( feat[i].displayed[0] == 'Y' )
     {

      if (feat[i].has_text[0] == 'Y')  /*---------- Exmain Text end_points IF ANY -----------------*/
         {
         for(ii=1; ii<=feat[i].text_count; ii++)
            {
             text_index = feat[i].text + ii     ;
             size       = text[text_index].size ;
             x_db       = text[text_index].x    ;   // DB Units
             y_db       = text[text_index].y    ;

             /*  TEXT SIZE CLIPPING  */
             if ( (size/ONE_PIXEL) >= 1  )
                {
                 length = strlen (text[text_index].string) -1  ;
                 angle  = (double)text[text_index].angle / DEG2RAD ;
                 switch (text[text_index].just)
                        {
                         case 1: x_db -= (size/2) * sin(angle);       /* Bottom */
                                 y_db += (size/2) * cos(angle);
                                 x_db += (size/2) * cos(angle);       /* Left   */
                                 y_db += (size/2) * sin(angle);
                                 break;
                         case 2: x_db -= (size/2) * sin(angle);        /* Bottom */
                                 y_db += (size/2) * cos(angle);
                                 x_db -= (length*size/2) * cos(angle); /* Center */
                                 y_db -= (length*size/2) * sin(angle);
                                 break;
                         case 3: x_db -= (size/2) * sin(angle);        /* Bottom */
                                 y_db += (size/2) * cos(angle);
                                 x_db -= (length*size) * cos(angle);   /* Right  */
                                 y_db -= (length*size) * sin(angle);
                                 break;
                         case 4: /* Middle */
                                 x_db += (size/2) * cos(angle);        /* Left   */
                                 y_db += (size/2) * sin(angle);
                                 break;
                         case 5: /* Middle */
                                 x_db -= (length*size/2) * cos(angle); /* Center */
                                 y_db -= (length*size/2) * sin(angle);
                                 break;
                         case 6: /* Middle */
                                 x_db -= (length*size) * cos(angle);   /* Right  */
                                 y_db -= (length*size) * sin(angle);
                                 break;
                         case 7: x_db += (size/2) * sin(angle);        /* Top  */
                                 y_db -= (size/2) * cos(angle);
                                 x_db += (size/2) * cos(angle);        /* Left */
                                 y_db += (size/2) * sin(angle);
                                 break;
                         case 8: x_db += (size/2) * sin(angle);        /* Top    */
                                 y_db -= (size/2) * cos(angle);
                                 x_db -= (length*size/2) * cos(angle); /* Center */
                                 y_db -= (length*size/2) * sin(angle);
                                 break;
                         case 9: x_db += (size/2) * sin(angle);        /* Top   */
                                 y_db -= (size/2) * cos(angle);
                                 x_db -= (length*size) * cos(angle);   /* Right */
                                 y_db -= (length*size) * sin(angle);
                                 break;
                        }

                 if (x_db < x_min_all)  x_min_all = x_db ;
                 if (y_db < y_min_all)  y_min_all = y_db ;
                 if (x_db > x_max_all)  x_max_all = x_db ;
                 if (y_db > y_max_all)  y_max_all = y_db ;

                 for (j=0; j<=length; j++)
                     {
                      symb_no     = 0 ;
                      symb_no     = text[text_index].string[j] ;
                      font_no     = text[text_index].font      ;
                      symb_factor = (float)size / font[font_no][symb_no].grid ;
                      if ( j != 0 )
                         {
                          previous_symb = text[text_index].string[j-1] ;
                          x_db += size * font[font_no][previous_symb].x_factor * cos(angle) ;
                          y_db += size * font[font_no][previous_symb].x_factor * sin(angle) ;
                         }
                      }

                 if (x_db < x_min_all)  x_min_all = x_db ;
                 if (y_db < y_min_all)  y_min_all = y_db ;
                 if (x_db > x_max_all)  x_max_all = x_db ;
                 if (y_db > y_max_all)  y_max_all = y_db ;
                }
            }
        }



      switch (feat[i].type)
           {
            case 1:    /*-------------- Exmain type one ------------------*/
             if (feat[i].xbase < x_min_all)  x_min_all = feat[i].xbase ;
             if (feat[i].ybase < y_min_all)  y_min_all = feat[i].ybase ;
             if (feat[i].xbase > x_max_all)  x_max_all = feat[i].xbase ;
             if (feat[i].ybase > y_max_all)  y_max_all = feat[i].ybase ;
             break ;

            case 2:    /*-------------- Exmain type two ------------------*/
             for ( ii=0; ii<=feat[i].xy_count; ii++ )
                 {
                  switch (ii)
                       {
                        case 0:
                         if (feat[i].xbase < x_min_all) x_min_all = feat[i].xbase ;
                         if (feat[i].ybase < y_min_all) y_min_all = feat[i].ybase ;
                         if (feat[i].xbase > x_max_all) x_max_all = feat[i].xbase ;
                         if (feat[i].ybase > y_max_all) y_max_all = feat[i].ybase ;
                         if (feat[i].xend  < x_min_all) x_min_all = feat[i].xend  ;  // Linux Bug fixing !!!!
                         if (feat[i].yend  < y_min_all) y_min_all = feat[i].yend  ;
                         if (feat[i].xend  > x_max_all) x_max_all = feat[i].xend  ;
                         if (feat[i].yend  > y_max_all) y_max_all = feat[i].yend  ;
                         break ;

                        default:
                         if (x[feat[i].xy+ii] < x_min_all) x_min_all = x[feat[i].xy+ii] ;
                         if (y[feat[i].xy+ii] < y_min_all) y_min_all = y[feat[i].xy+ii] ;

                         if (x[feat[i].xy+ii] > x_max_all) x_max_all = x[feat[i].xy+ii] ;
                         if (y[feat[i].xy+ii] > y_max_all) y_max_all = y[feat[i].xy+ii] ;
                         break ;
                       }
                 }
             break ;
           }
     }
 }


 x_min  = x_min_all ;
 y_min  = y_min_all ;
 x_max  = x_max_all ;
 y_max  = y_max_all ;

 /* check for xy_min & xy_max is the same point */
 if ( (x_min == x_max) && (y_min == y_max) )
    {
     scale = 500 ;
     switch (DB_UNIT)
          {
           case MM: y_diff = scale * ( SCREEN_CM / .1   ); break ;
           case CM: y_diff = scale * ( SCREEN_CM / 1    ); break ;
           case DM: y_diff = scale * ( SCREEN_CM / 10   ); break ;
           case  M: y_diff = scale * ( SCREEN_CM / 100  ); break ;
           case KM: y_diff = scale * ( SCREEN_CM / 1000 ); break ;
           default: y_diff = scale * ( SCREEN_CM / 100  );
                    fprintf(stderr,"ERROR : Data Base Unit not Defined\n");
                    break ;
          }
     x_center = ( x_max + x_min ) / 2  ;
     y_center = ( y_max + y_min ) / 2  ;

     x_min = x_center - ( y_diff / 2 ) ;
     y_min = y_center - ( y_diff / 2 ) ;
     x_max = x_center + ( y_diff / 2 ) ;
     y_max = y_center + ( y_diff / 2 ) ;
    }
 else
    {
     x_diff = x_max - x_min ;
     y_diff = y_max - y_min ;

     if (x_diff > y_diff)
        {
         xy_diff = (x_diff - y_diff) / 2 ;
         y_min   = y_min - xy_diff       ;
         y_max   = y_max + xy_diff       ;
        }

     if (y_diff > x_diff)
        {
         xy_diff = (y_diff - x_diff) / 2 ;
         x_min   = x_min - xy_diff       ;
         x_max   = x_max + xy_diff       ;
        }
    }

 /*------------------------------------------------------------------------*/
 /*                       Calculate Scale, ONE_PIXEL                       */
 /*------------------------------------------------------------------------*/
 y_diff = y_max - y_min ;
 ONE_PIXEL = (y_diff) / (y_br_screen - y_ul_screen) ;

 switch (DB_UNIT)
      {
       case MM: scale = ( y_diff * .1   ) / SCREEN_CM ; break ;
       case CM: scale = ( y_diff * 1.   ) / SCREEN_CM ; break ;
       case DM: scale = ( y_diff * 10.  ) / SCREEN_CM ; break ;
       case  M: scale = ( y_diff * 100. ) / SCREEN_CM ; break ;
       case KM: scale = ( y_diff * 1000.) / SCREEN_CM ; break ;
       default: scale = ( y_diff * 100. ) / SCREEN_CM ;
                fprintf(stderr,"[%d] ERROR : Data Base unit not defined, assumed Meter\n",module);
                break ;
      }

 /*------------------------------------------------------------------------*/
 /*                         Calculate Scale Range                          */
 /*------------------------------------------------------------------------*/
      if ( scale > 0          &&  scale <= SC_RANGE1 ) sc_range = 0 ;
 else if ( scale > SC_RANGE1  &&  scale <= SC_RANGE2 ) sc_range = 1 ;
 else if ( scale > SC_RANGE2  &&  scale <= SC_RANGE3 ) sc_range = 2 ;
 else if ( scale > SC_RANGE3  &&  scale <= SC_RANGE4 ) sc_range = 3 ;
 else if ( scale > SC_RANGE4                         ) sc_range = 4 ;


 /*------------------------------------------------------------------------*/
 /*      Main Loop to Draw ALL Displayed Features within Scale_range       */
 /*------------------------------------------------------------------------*/
 for ( i=1; i<=feat_count; i++ )
 {
  switch (feat[i].type)
  {
   case 1:    /*---------- Draw type one -------------- */
    if ( (feat[i].displayed[0] == 'Y'         ) &&
         (feat[i].scale_range[sc_range] == 'Y') &&
         ((feat[i].symb_size/ONE_PIXEL) >= 1  ) )
    {
     DrawSetStrokeColor ( draw_wand, IMcolor[feat[i].color] );  // set color
     DrawSetStrokeWidth ( draw_wand, feat[i].linewidth      );  // set line width
     switch (feat[i].linetype)                                  // set line type
            {
             case 1:
               DrawSetStrokeDashArray ( draw_wand, 0, dash_array[0] );
               break;

             default:
               DrawSetStrokeDashArray ( draw_wand, 2, dash_array[feat[i].linetype] );
               break;
            }

     x_base = feat[i].xbase ;
     y_base = feat[i].ybase ;

     if (feat[i].has_text[0] == 'Y')             /*  DRAW TEXT IF ANY  */
        {
         for(ii=1; ii<=feat[i].text_count; ii++)
            {
             text_index = feat[i].text + ii     ;
             size       = text[text_index].size ;
             font_no    = 21  ;                     /////////// ARABIZATION ///////////////////////
             x_db = text[text_index].x - x_min  ;
             y_db = y_max - text[text_index].y  ;

             /*  TEXT SIZE CLIPPING  */
             if ( (size/ONE_PIXEL) >= 1  )
                {
                 length = strlen (text[text_index].string) -1  ;
                 angle  = (double)text[text_index].angle / DEG2RAD ;

                 switch (text[text_index].just)
                        {
                         case 1: x_db -= (size/2) * sin(angle);       /* Bottom */
                                 y_db -= (size/2) * cos(angle);
                                 x_db += (size/2) * cos(angle);       /* Left   */
                                 y_db -= (size/2) * sin(angle);
                                 break;

                         case 2: x_db -= (size/2) * sin(angle);        /* Bottom */
                                 y_db -= (size/2) * cos(angle);
                                 x_db -= (length*size/2) * cos(angle); /* Center */
                                 y_db += (length*size/2) * sin(angle);
                                 break;

                         case 3: x_db -= (size/2) * sin(angle);        /* Bottom */
                                 y_db -= (size/2) * cos(angle);
                                 x_db -= (length*size) * cos(angle);   /* Right  */
                                 y_db += (length*size) * sin(angle);
                                 break;

                         case 4: /* Middle */
                                 x_db += (size/2) * cos(angle);        /* Left   */
                                 y_db -= (size/2) * sin(angle);
                                 break;

                         case 5: /* Middle */
                                 x_db -= (length*size/2) * cos(angle); /* Center */
                                 y_db += (length*size/2) * sin(angle);
                                 break;

                         case 6: /* Middle */
                                 x_db -= (length*size) * cos(angle);   /* Right  */
                                 y_db += (length*size) * sin(angle);
                                 break;

                         case 7: x_db += (size/2) * sin(angle);        /* Top  */
                                 y_db += (size/2) * cos(angle);
                                 x_db += (size/2) * cos(angle);        /* Left */
                                 y_db -= (size/2) * sin(angle);
                                 break;

                         case 8: x_db += (size/2) * sin(angle);        /* Top    */
                                 y_db += (size/2) * cos(angle);
                                 x_db -= (length*size/2) * cos(angle); /* Center */
                                 y_db += (length*size/2) * sin(angle);
                                 break;

                         case 9: x_db += (size/2) * sin(angle);        /* Top   */
                                 y_db += (size/2) * cos(angle);
                                 x_db -= (length*size) * cos(angle);   /* Right */
                                 y_db += (length*size) * sin(angle);
                                 break;
                        }


                 for (j=0; j<=length; j++)
                     {
                      symb_no     = 0 ;
                      symb_no     = text[text_index].string[j] ;
                      font_no     = text[text_index].font      ;
                      font_no    = 21 ; ////////////// ARABIZATION /////////////////
                      symb_factor = (float)size / font[font_no][symb_no].grid ;

                      if ( j != 0 )
                         {
                          previous_symb = text[text_index].string[j-1] ;
                          x_db += size * font[font_no][previous_symb].x_factor * cos(angle) ;
                          y_db -= size * font[font_no][previous_symb].x_factor * sin(angle) ;
                         }

                      for ( jj=1; jj<=font[font_no][symb_no].stroke; jj++)
                          {
                           switch (font[font_no][symb_no].mv_draw[jj])
                           {
                            case 0:     /*  Move  */

                              angle_sym = font[font_no][symb_no].angle[jj] + angle ;
                              x1_screen = (x_db + symb_factor * font[font_no][symb_no].distance[jj] * cos(angle_sym))/ONE_PIXEL;
                              y1_screen = (y_db - symb_factor * font[font_no][symb_no].distance[jj] * sin(angle_sym))/ONE_PIXEL;
                              break ;

                            case 1:     /*  Draw  */

                              angle_sym = font[font_no][symb_no].angle[jj] + angle ;
                              x2_screen = (x_db + symb_factor * font[font_no][symb_no].distance[jj] * cos(angle_sym))/ONE_PIXEL;
                              y2_screen = (y_db - symb_factor * font[font_no][symb_no].distance[jj] * sin(angle_sym))/ONE_PIXEL;

                              DrawLine ( draw_wand,x1_screen,y1_screen,x2_screen,y2_screen );

                              x1_screen = x2_screen ;
                              y1_screen = y2_screen ;
                              break ;
                           }
                          }
                     }
                }
            }
        }


     /*..............*/
     /* DRAW SYMBOL  */
     /*..............*/

     symb_no     = feat[i].symb_num   ;
     angle       = (float)feat[i].symb_angle / DEG2RAD ;
     symb_factor = (float)feat[i].symb_size  / symb[symb_no].grid ;

     for (ii=1; ii<=symb[symb_no].stroke; ii++)
       {
        switch (symb[symb_no].mv_draw[ii])
         {
          case 0:     /*  Move  */

            angle_sym = symb[symb_no].angle[ii] + angle ;
            x1_screen = (x_base - x_min  + symb_factor * symb[symb_no].distance[ii] * cos(angle_sym)) / ONE_PIXEL ;
            y1_screen = (y_max  - y_base - symb_factor * symb[symb_no].distance[ii] * sin(angle_sym)) / ONE_PIXEL ;
            break ;

          case 1:     /*  Draw  */

            angle_sym = symb[symb_no].angle[ii] + angle ;
            x2_screen = (x_base - x_min  + symb_factor * symb[symb_no].distance[ii] * cos(angle_sym)) / ONE_PIXEL ;
            y2_screen = (y_max  - y_base - symb_factor * symb[symb_no].distance[ii] * sin(angle_sym)) / ONE_PIXEL ;

            DrawLine ( draw_wand,x1_screen,y1_screen,x2_screen,y2_screen );

            x1_screen = x2_screen ;
            y1_screen = y2_screen ;
            break ;
         }
       }
    }
    break ;


   case 2:    /*-------------- Draw type two --------------------*/

    if (feat[i].displayed[0] == 'Y' && (feat[i].scale_range[sc_range] == 'Y'))
    {
     DrawSetStrokeColor ( draw_wand, IMcolor[feat[i].color] );  // set color
     DrawSetStrokeWidth ( draw_wand, feat[i].linewidth      );  // set line width
     switch (feat[i].linetype)                                  // set line type
            {
             case 1:
               DrawSetStrokeDashArray ( draw_wand, 0, dash_array[0] );
               break;

             default:
               DrawSetStrokeDashArray ( draw_wand, 2, dash_array[feat[i].linetype] );
               break;
            }


     if (feat[i].has_text[0] == 'Y')             /*  DRAW TEXT IF ANY  */
        {
         for(ii=1; ii<=feat[i].text_count; ii++)
            {
             text_index = feat[i].text + ii     ;
             size       = text[text_index].size ;

             x_db =text[text_index].x  ;
             y_db =text[text_index].y  ;

             /*  TEXT SIZE CLIPPING  */
             if ( (size/ONE_PIXEL) >= 1  )
                {
                 x_db =text[text_index].x - x_min  ;
                 y_db =y_max - text[text_index].y  ;

                 length = strlen (text[text_index].string) -1  ;
                 angle  = (double)text[text_index].angle / DEG2RAD ;

                 switch (text[text_index].just)
                        {
                         case 1: x_db -= (size/2) * sin(angle);       /* Bottom */
                                 y_db -= (size/2) * cos(angle);
                                 x_db += (size/2) * cos(angle);       /* Left   */
                                 y_db -= (size/2) * sin(angle);
                                 break;

                         case 2: x_db -= (size/2) * sin(angle);        /* Bottom */
                                 y_db -= (size/2) * cos(angle);
                                 x_db -= (length*size/2) * cos(angle); /* Center */
                                 y_db += (length*size/2) * sin(angle);
                                 break;

                         case 3: x_db -= (size/2) * sin(angle);        /* Bottom */
                                 y_db -= (size/2) * cos(angle);
                                 x_db -= (length*size) * cos(angle);   /* Right  */
                                 y_db += (length*size) * sin(angle);
                                 break;

                         case 4: /* Middle */
                                 x_db += (size/2) * cos(angle);        /* Left   */
                                 y_db -= (size/2) * sin(angle);
                                 break;

                         case 5: /* Middle */
                                 x_db -= (length*size/2) * cos(angle); /* Center */
                                 y_db += (length*size/2) * sin(angle);
                                 break;

                         case 6: /* Middle */
                                 x_db -= (length*size) * cos(angle);   /* Right  */
                                 y_db += (length*size) * sin(angle);
                                 break;

                         case 7: x_db += (size/2) * sin(angle);        /* Top  */
                                 y_db += (size/2) * cos(angle);
                                 x_db += (size/2) * cos(angle);        /* Left */
                                 y_db -= (size/2) * sin(angle);
                                 break;

                         case 8: x_db += (size/2) * sin(angle);        /* Top    */
                                 y_db += (size/2) * cos(angle);
                                 x_db -= (length*size/2) * cos(angle); /* Center */
                                 y_db += (length*size/2) * sin(angle);
                                 break;

                         case 9: x_db += (size/2) * sin(angle);        /* Top   */
                                 y_db += (size/2) * cos(angle);
                                 x_db -= (length*size) * cos(angle);   /* Right */
                                 y_db += (length*size) * sin(angle);
                                 break;
                        }


                 for (j=0; j<=length ; j++)
                     {
                      symb_no     = 0 ;
                      symb_no     = text[text_index].string[j] ;
                      font_no     = text[text_index].font      ;
                      symb_factor = (float)size / font[font_no][symb_no].grid ;

                      if ( j != 0 )
                         {
                          previous_symb = text[text_index].string[j-1] ;
                          x_db += size * font[font_no][previous_symb].x_factor * cos(angle) ;
                          y_db -= size * font[font_no][previous_symb].x_factor * sin(angle) ;
                         }

                      for ( jj=1; jj<=font[font_no][symb_no].stroke; jj++)
                          {
                           switch (font[font_no][symb_no].mv_draw[jj])
                           {
                            case 0:     /*  Move  */

                              angle_sym = font[font_no][symb_no].angle[jj] + angle ;
                              x1_screen = (x_db + symb_factor * font[font_no][symb_no].distance[jj] * cos(angle_sym))/ONE_PIXEL;
                              y1_screen = (y_db - symb_factor * font[font_no][symb_no].distance[jj] * sin(angle_sym))/ONE_PIXEL;
                              break ;

                            case 1:     /*  Draw  */

                              angle_sym = font[font_no][symb_no].angle[jj] + angle ;
                              x2_screen = (x_db + symb_factor * font[font_no][symb_no].distance[jj] * cos(angle_sym))/ONE_PIXEL;
                              y2_screen = (y_db - symb_factor * font[font_no][symb_no].distance[jj] * sin(angle_sym))/ONE_PIXEL;

                              DrawLine ( draw_wand,x1_screen,y1_screen,x2_screen,y2_screen );

                              x1_screen = x2_screen ;
                              y1_screen = y2_screen ;
                              break ;
                           }
                          }
                     }
                }
            }
        }


     /*............*/
     /* DRAW LINE  */
     /*............*/

     for ( ii=0 ; ii<=(feat[i].xy_count+1) ; ii++ )
         {
          switch (ii)
             {
              case 0:
                   x1_screen = (feat[i].xbase - x_min) / ONE_PIXEL ;
                   y1_screen = (y_max - feat[i].ybase) / ONE_PIXEL ;
                   break ;

              default:
                   if ( ii <= feat[i].xy_count )
                      {
                       x2_screen = (x[feat[i].xy+ii] - x_min) / ONE_PIXEL ;
                       y2_screen = (y_max - y[feat[i].xy+ii]) / ONE_PIXEL ;
                      }
                   else
                      {
                       x2_screen = (feat[i].xend - x_min) / ONE_PIXEL ;
                       y2_screen = (y_max - feat[i].yend) / ONE_PIXEL ;
                      }

                   DrawLine ( draw_wand,x1_screen,y1_screen,x2_screen,y2_screen );

                   x1_screen = x2_screen ;
                   y1_screen = y2_screen ;
                   break ;
             }
        }


    }
    break ;

   default:   /*---------------- Do nothing ----------------------*/
     break ;
  }
 }

 /*------------------------------------------------------------------------*/
 /*                  Create ImageMagick Image Object                       */
 /*------------------------------------------------------------------------*/
 magick_wand = NewMagickWand ();  // Create MagickWand  Image   Object

 if ( MagickNewImage (magick_wand,500,500,IMcolor[8]) != MagickTrue )
    {
     printf("[%s] ERROR : ImageMagick, Cannot create 500x500 blank image \n",module);
     exit(-999) ;
    }

 /*------------------------------------------------------------------------*/
 /*            Copy draw_wand to magick_wand & save Image File             */
 /*------------------------------------------------------------------------*/
 MagickDrawImage ( magick_wand, draw_wand );
 if ( MagickWriteImage( magick_wand, image_file_name ) == MagickFalse )
    {
     printf ("[%s] ERROR : ImageMagick, Cannot write image file",module);
    }

 /*------------------------------------------------------------------------*/
 /*                  Destroy ImageMagick Image Objects                     */
 /*------------------------------------------------------------------------*/
 DestroyMagickWand ( magick_wand );
 DestroyDrawingWand( draw_wand  );

 /*------------------------------------------------------------------------*/
 /*                  Set XY Limits in each client session                  */
 /*------------------------------------------------------------------------*/
 session[sid].x_min = x_min ;
 session[sid].y_min = y_min ;
 session[sid].x_max = x_max ;
 session[sid].y_max = y_max ;

}


////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                            newOkCB()                                           */
////////////////////////////////////////////////////////////////////////////////////////////////////
void newOkCB()
{
 char PARM[20]  ;
 char VALUE[20] ;

 XSynchronize(MainDisplay,1);
  cls_flag = 1 ;
  XClearWindow(MainDisplay,XtWindow(drawarea)) ;
  XFillRectangle(MainDisplay,Tile,Tilegc,0,0,499,499);
 XSynchronize(MainDisplay,0);

 XtVaSetValues( toplevel, XmNtitle, "geoIMS  [None]", NULL ) ;

 if ( db_opened[0] == 'Y' )
    {
     
/*
EXEC SQL CONNECT RESET;
*/

{
#line 3045 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 3045 "geoIMS_main.sqc"
  sqlacall((unsigned short)29,3,0,0,0L);
#line 3045 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 3045 "geoIMS_main.sqc"

     // CHECKERR ("CONNECT RESET");
    }

/*---------------------------------------------------------------------*/
/*                   Initaize GLOBAL Variables                         */
/*---------------------------------------------------------------------*/
 db_opened[0]    = 'N'        ;  /* Reset DB open flag                 */
 trace_on[0]     = 'N'        ;  /* Reset Trace Flag                   */

 feat_count      = 0          ;  /* Reset Total Number of Features     */
 lay_count       = 0          ;  /* Reset Total Number of Features     */
 xy_index        = 0          ;  /* Reset xy_index                     */
 text_index      = 0          ;  /* Reset text_index                   */

 draw_fun        = NONE       ;  /* Set Initial Draw function          */
 move_fun        = CROSSHAIR  ;  /* Set Initial Move function          */
 activateMenubar = 0          ;  /* Reset Menubar activation flag      */

 enable_leave    = 1          ;  /* Enter/Leave Flag                   */
 enable_enter    = 1          ;

/*---------------------------------------------------------------------*/
/*        Set Default Values to be over-written by geoIMS.ini        */
/*---------------------------------------------------------------------*/

 DB_UNIT     = DM             ;  /* Set Default DBU  to DM             */
 strcpy (DB_UNIT_NAME,"DM")   ;  /* Set Default DBU  name              */

 x_min = 5000000.0            ;  /* Set Default DB Limits in DBU       */
 y_min = 5000000.0            ;
 x_max = 5002230.392209       ;
 y_max = 5002230.392209       ;

/*---------------------------------------------------------------------*/
/*            Read New Workapce Settings from Paramter file            */
/*---------------------------------------------------------------------*/

 fp_i=fopen("geoIMS.ini","rt");
 if  ( fp_i== NULL )
     {
      fprintf (stderr,"INFO : Can't open parameter file, Use Default values !\n");
     }
 else
     {
      while ( fscanf(fp_i,"%s", PARM) != EOF )
            {
             fscanf(fp_i,"%s", VALUE );
             fscanf(fp_i,"%s", VALUE );

             if ( strcmp(PARM,"DB_UNIT") == 0 )
                {
                      if ( strcmp(VALUE,"MM") == 0 ) { DB_UNIT = MM ; strcpy (DB_UNIT_NAME,"MM"); }
                 else if ( strcmp(VALUE,"CM") == 0 ) { DB_UNIT = CM ; strcpy (DB_UNIT_NAME,"CM"); }
                 else if ( strcmp(VALUE,"DM") == 0 ) { DB_UNIT = DM ; strcpy (DB_UNIT_NAME,"DM"); }
                 else if ( strcmp(VALUE,"M" ) == 0 ) { DB_UNIT = M  ; strcpy (DB_UNIT_NAME,"M" ); }
                 else if ( strcmp(VALUE,"KM") == 0 ) { DB_UNIT = KM ; strcpy (DB_UNIT_NAME,"KM"); }
                 else                                { DB_UNIT = DM ; strcpy (DB_UNIT_NAME,"DM"); }
                }
             else
             if ( strcmp(PARM,"X_MIN") == 0 )
                {
                 x_min = atof(VALUE) ;
                }
             else
             if ( strcmp(PARM,"Y_MIN") == 0 )
                {
                 y_min = atof(VALUE) ;
                }
             else
             if ( strcmp(PARM,"X_MAX") == 0 )
                {
                 x_max = atof(VALUE) ;
                }
             else
             if ( strcmp(PARM,"Y_MAX") == 0 )
                {
                 y_max = atof(VALUE) ;
                }
            }
     }


 ONE_PIXEL = (y_max - y_min) / (y_br_screen - y_ul_screen) ;
 tolerance = cursor_size * ONE_PIXEL ;

 // normal_cursor();
 display_scale();

 xstr = XmStringCreate("X-Y Coordinates",CS);
 XtSetArg(args[0], XmNlabelString, xstr);
 XtSetValues(xy_label,args,1);

 xstr = XmStringCreate(" geoIMS  Ready.",CS);
 XtSetArg(args[0], XmNlabelString , xstr);
 XtSetValues(output_label,args,1);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                        retrieve_all()                                          */
////////////////////////////////////////////////////////////////////////////////////////////////////
void retrieve_all()
{
 char command[50] ;


 strcpy ( db_name , DB_name ) ;

 if ( db_opened[0] == 'Y' )
    {
     
/*
EXEC SQL CONNECT RESET;
*/

{
#line 3155 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 3155 "geoIMS_main.sqc"
  sqlacall((unsigned short)29,3,0,0,0L);
#line 3155 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 3155 "geoIMS_main.sqc"

     // CHECKERR ("CONNECT RESET");
     db_opened[0] = 'N' ;
    }

 printf("INFO  : Connecting to Database [ %s ] ..\n",db_name);

 
/*
EXEC SQL CONNECT TO :db_name   ;
*/

{
#line 3162 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 3162 "geoIMS_main.sqc"
  sqlaaloc(2,1,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 3162 "geoIMS_main.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 31;
#line 3162 "geoIMS_main.sqc"
      sql_setdlist[0].sqldata = (void*)db_name;
#line 3162 "geoIMS_main.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 3162 "geoIMS_main.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 3162 "geoIMS_main.sqc"
  sqlacall((unsigned short)29,4,2,0,0L);
#line 3162 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 3162 "geoIMS_main.sqc"
  /* CHECKERR ("CONNECT TO geoinfo"); */


 if ( SQLCODE == -1013  || SQLCODE == -1001 || strcmp(db_name,"") == 0 )
    {
     sprintf (Message, "'%s', Database not found" ,db_name);
     xstr  = XmStringCreate("ERROR",CS);
     xstr1 = XmStringCreate(Message,CS);

     n=0;
     XtSetArg(args[n] , XmNdialogTitle   ,        xstr);n++;
     XtSetArg(args[n] , XmNmessageString ,       xstr1);n++;
     // XtSetArg(args[n] , XmNwidth         ,         300);n++;
     // XtSetArg(args[n] , XmNheight        ,         130);n++;
     XtSetArg(args[n] , XmNborderColor   , white.pixel);n++;
     XtSetArg(args[n] , XmNforeground    , black.pixel);n++;
     XtSetArg(args[n] , XmNbackground    , lgray.pixel);n++;

     PD = XmCreateErrorDialog(MainForm,"PD",args,n);
     XtManageChild(PD);

     // normal_cursor();
     return ;
    }

 if ( SQLCODE == -1032 )
    {
     xstr  = XmStringCreate("ERROR",CS);
     xstr1 = XmStringCreate("Database Engine is not started",CS);

     n=0;
     XtSetArg(args[n] , XmNdialogTitle   ,        xstr);n++;
     XtSetArg(args[n] , XmNmessageString ,       xstr1);n++;
     // XtSetArg(args[n] , XmNwidth         ,         300);n++;
     // XtSetArg(args[n] , XmNheight        ,         130);n++;
     XtSetArg(args[n] , XmNborderColor   , white.pixel);n++;
     XtSetArg(args[n] , XmNforeground    , black.pixel);n++;
     XtSetArg(args[n] , XmNbackground    , lgray.pixel);n++;

     PD = XmCreateErrorDialog(MainForm,"PD",args,n);
     XtManageChild(PD);

     // normal_cursor();
     return ;
    }

 XSynchronize(MainDisplay,1);
  cls_flag = 1 ;
  XClearWindow(MainDisplay,XtWindow(drawarea));
  XFillRectangle(MainDisplay,Tile,Tilegc,0,0,499,499);
 XSynchronize(MainDisplay,0);

 printf("INFO  : Retrieving from Database ...\n");

 
/*
EXEC SQL DECLARE ALL1 CURSOR FOR
          SELECT  feat_num,
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
          FROM    features
          FOR     READ ONLY;
*/

#line 3240 "geoIMS_main.sqc"

 // CHECKERR ("DECLARE CURSOR");

 
/*
EXEC SQL DECLARE ALL2 CURSOR FOR
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

#line 3257 "geoIMS_main.sqc"

 // CHECKERR ("DECLARE CURSOR");

 
/*
EXEC SQL DECLARE ALL3 CURSOR FOR
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

#line 3270 "geoIMS_main.sqc"

 // CHECKERR ("DECLARE CURSOR");


 
/*
EXEC SQL OPEN ALL1 ;
*/

{
#line 3274 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 3274 "geoIMS_main.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 3274 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 3274 "geoIMS_main.sqc"
     /* CHECKERR ("OPEN CURSOR"); */


 ///////////////////////////////
 /* Used for workspace Load   */
 ///////////////////////////////
 i = 0              ;     /* Reset i Counter                 */
 xy_index   = 0     ;     /* Reset xy_index                  */
 text_index = 0     ;     /* Reset text_index                */
 feat_count = 0     ;     /* Reset Total Number of Features  */
 lay_count  = 0     ;     /* Reset Total Number of Layers    */

 trace_on[0] = 'N'  ;     /* Reset Trace Flag                */


 do {
     
/*
EXEC SQL FETCH ALL1 INTO :feat_num,
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
                              :text_count  ;
*/

{
#line 3311 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 3311 "geoIMS_main.sqc"
  sqlaaloc(3,22,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[22];
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[0].sqldata = (void*)&feat_num;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 13;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[1].sqldata = (void*)feat_code;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[2].sqldata = (void*)&type;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[3].sqldata = (void*)&layer;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[4].sqldata = (void*)&network;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 6;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[5].sqldata = (void*)scale_range;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 2;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[6].sqldata = (void*)rdisplayed;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 2;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[7].sqldata = (void*)rselectable;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 2;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[8].sqldata = (void*)rhas_attrib;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 2;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[9].sqldata = (void*)rhas_text;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[10].sqltype = 500; sql_setdlist[10].sqllen = 2;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[10].sqldata = (void*)&feat_color;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[11].sqltype = 500; sql_setdlist[11].sqllen = 2;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[11].sqldata = (void*)&feat_linetype;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[12].sqltype = 500; sql_setdlist[12].sqllen = 2;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[12].sqldata = (void*)&feat_linewidth;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[13].sqltype = 496; sql_setdlist[13].sqllen = 4;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[13].sqldata = (void*)&x_base;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[14].sqltype = 496; sql_setdlist[14].sqllen = 4;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[14].sqldata = (void*)&y_base;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[15].sqltype = 496; sql_setdlist[15].sqllen = 4;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[15].sqldata = (void*)&x_end;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[16].sqltype = 496; sql_setdlist[16].sqllen = 4;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[16].sqldata = (void*)&y_end;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[17].sqltype = 496; sql_setdlist[17].sqllen = 4;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[17].sqldata = (void*)&xy_count;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[18].sqltype = 496; sql_setdlist[18].sqllen = 4;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[18].sqldata = (void*)&symb_num;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[19].sqltype = 496; sql_setdlist[19].sqllen = 4;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[19].sqldata = (void*)&symb_size;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[20].sqltype = 496; sql_setdlist[20].sqllen = 4;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[20].sqldata = (void*)&symb_angle;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[21].sqltype = 496; sql_setdlist[21].sqllen = 4;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[21].sqldata = (void*)&text_count;
#line 3311 "geoIMS_main.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 3311 "geoIMS_main.sqc"
      sqlasetdata(3,0,22,sql_setdlist,0L,0L);
    }
#line 3311 "geoIMS_main.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 3311 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 3311 "geoIMS_main.sqc"


     if (SQLCODE != 0)
        {
         switch (SQLCODE)
              {
               case 100:     /* End of Rows */
               break;

               case -818:    /* DB need bind */
                 
/*
EXEC SQL CONNECT RESET;
*/

{
#line 3321 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 3321 "geoIMS_main.sqc"
  sqlacall((unsigned short)29,3,0,0,0L);
#line 3321 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 3321 "geoIMS_main.sqc"

                 strcpy (command, "./geoDBbind ");
                 strcat (command, db_name    );
                 strcat (command, " "        );
                 system (command) ;
                 retrieve_all();
               break ;

               default:      /* Any Other Error */
                 fprintf(stderr,"ERROR : Reading from Features table, SQLCODE = [%d]\n",SQLCODE);
               break;
              }

         /* if (SQLCODE != 100)
            {
             fprintf(stderr,"ERROR : Reading from Features [SQLCODE] = %d\n",SQLCODE);
            }   */

         break ;
        }

     feat[++i].num         = feat_num       ;
     sscanf (feat_code,"%s",&feat[i].code)  ; /* use sscanf to Trim DB2 trailing spaces */
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


     if  ( feat[i].xy_count > 0 )
         {
          
/*
EXEC SQL OPEN ALL2 ;
*/

{
#line 3369 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 3369 "geoIMS_main.sqc"
  sqlaaloc(2,1,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 3369 "geoIMS_main.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 3369 "geoIMS_main.sqc"
      sql_setdlist[0].sqldata = (void*)&feat_num;
#line 3369 "geoIMS_main.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 3369 "geoIMS_main.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 3369 "geoIMS_main.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 3369 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 3369 "geoIMS_main.sqc"


          feat[i].xy = xy_index ;
          j = 0 ;

          for (iii=1; iii<=(feat[i].xy_count/10); iii++)
              {
               
/*
EXEC SQL FETCH ALL2 INTO :seq ,
                                        :x_1 ,:y_1,
                                        :x_2 ,:y_2,
                                        :x_3 ,:y_3,
                                        :x_4 ,:y_4,
                                        :x_5 ,:y_5,
                                        :x_6 ,:y_6,
                                        :x_7 ,:y_7,
                                        :x_8 ,:y_8,
                                        :x_9 ,:y_9,
                                        :x_10,:y_10  ;
*/

{
#line 3386 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 3386 "geoIMS_main.sqc"
  sqlaaloc(3,21,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[21];
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[0].sqldata = (void*)&seq;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[1].sqldata = (void*)&x_1;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[2].sqldata = (void*)&y_1;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[3].sqldata = (void*)&x_2;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[4].sqldata = (void*)&y_2;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[5].sqltype = 496; sql_setdlist[5].sqllen = 4;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[5].sqldata = (void*)&x_3;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[6].sqldata = (void*)&y_3;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[7].sqltype = 496; sql_setdlist[7].sqllen = 4;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[7].sqldata = (void*)&x_4;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[8].sqltype = 496; sql_setdlist[8].sqllen = 4;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[8].sqldata = (void*)&y_4;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[9].sqltype = 496; sql_setdlist[9].sqllen = 4;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[9].sqldata = (void*)&x_5;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[10].sqltype = 496; sql_setdlist[10].sqllen = 4;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[10].sqldata = (void*)&y_5;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[11].sqltype = 496; sql_setdlist[11].sqllen = 4;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[11].sqldata = (void*)&x_6;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[12].sqltype = 496; sql_setdlist[12].sqllen = 4;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[12].sqldata = (void*)&y_6;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[13].sqltype = 496; sql_setdlist[13].sqllen = 4;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[13].sqldata = (void*)&x_7;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[14].sqltype = 496; sql_setdlist[14].sqllen = 4;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[14].sqldata = (void*)&y_7;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[15].sqltype = 496; sql_setdlist[15].sqllen = 4;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[15].sqldata = (void*)&x_8;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[16].sqltype = 496; sql_setdlist[16].sqllen = 4;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[16].sqldata = (void*)&y_8;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[17].sqltype = 496; sql_setdlist[17].sqllen = 4;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[17].sqldata = (void*)&x_9;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[18].sqltype = 496; sql_setdlist[18].sqllen = 4;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[18].sqldata = (void*)&y_9;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[19].sqltype = 496; sql_setdlist[19].sqllen = 4;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[19].sqldata = (void*)&x_10;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[20].sqltype = 496; sql_setdlist[20].sqllen = 4;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[20].sqldata = (void*)&y_10;
#line 3386 "geoIMS_main.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 3386 "geoIMS_main.sqc"
      sqlasetdata(3,0,21,sql_setdlist,0L,0L);
    }
#line 3386 "geoIMS_main.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 3386 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 3386 "geoIMS_main.sqc"

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
EXEC SQL FETCH ALL2 INTO :seq ,
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
#line 3417 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 3417 "geoIMS_main.sqc"
  sqlaaloc(3,21,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[21];
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[0].sqldata = (void*)&seq;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[1].sqldata = (void*)&x_1;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[2].sqldata = (void*)&y_1;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[3].sqldata = (void*)&x_2;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[4].sqldata = (void*)&y_2;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[5].sqltype = 496; sql_setdlist[5].sqllen = 4;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[5].sqldata = (void*)&x_3;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[6].sqldata = (void*)&y_3;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[7].sqltype = 496; sql_setdlist[7].sqllen = 4;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[7].sqldata = (void*)&x_4;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[8].sqltype = 496; sql_setdlist[8].sqllen = 4;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[8].sqldata = (void*)&y_4;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[9].sqltype = 496; sql_setdlist[9].sqllen = 4;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[9].sqldata = (void*)&x_5;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[10].sqltype = 496; sql_setdlist[10].sqllen = 4;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[10].sqldata = (void*)&y_5;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[11].sqltype = 496; sql_setdlist[11].sqllen = 4;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[11].sqldata = (void*)&x_6;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[12].sqltype = 496; sql_setdlist[12].sqllen = 4;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[12].sqldata = (void*)&y_6;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[13].sqltype = 496; sql_setdlist[13].sqllen = 4;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[13].sqldata = (void*)&x_7;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[14].sqltype = 496; sql_setdlist[14].sqllen = 4;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[14].sqldata = (void*)&y_7;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[15].sqltype = 496; sql_setdlist[15].sqllen = 4;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[15].sqldata = (void*)&x_8;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[16].sqltype = 496; sql_setdlist[16].sqllen = 4;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[16].sqldata = (void*)&y_8;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[17].sqltype = 496; sql_setdlist[17].sqllen = 4;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[17].sqldata = (void*)&x_9;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[18].sqltype = 496; sql_setdlist[18].sqllen = 4;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[18].sqldata = (void*)&y_9;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[19].sqltype = 496; sql_setdlist[19].sqllen = 4;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[19].sqldata = (void*)&x_10;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[20].sqltype = 496; sql_setdlist[20].sqllen = 4;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[20].sqldata = (void*)&y_10;
#line 3417 "geoIMS_main.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 3417 "geoIMS_main.sqc"
      sqlasetdata(3,0,21,sql_setdlist,0L,0L);
    }
#line 3417 "geoIMS_main.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 3417 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 3417 "geoIMS_main.sqc"

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
EXEC SQL CLOSE ALL2 ;
*/

{
#line 3434 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 3434 "geoIMS_main.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 3434 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 3434 "geoIMS_main.sqc"

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
EXEC SQL OPEN ALL3 ;
*/

{
#line 3447 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 3447 "geoIMS_main.sqc"
  sqlaaloc(2,1,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 3447 "geoIMS_main.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 3447 "geoIMS_main.sqc"
      sql_setdlist[0].sqldata = (void*)&feat_num;
#line 3447 "geoIMS_main.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 3447 "geoIMS_main.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 3447 "geoIMS_main.sqc"
  sqlacall((unsigned short)26,3,2,0,0L);
#line 3447 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 3447 "geoIMS_main.sqc"


          feat[i].text = text_index ;

          for (iii=1; iii<=feat[i].text_count; iii++)
              {
               
/*
EXEC SQL FETCH ALL3 INTO :text_x      ,
                                        :text_y      ,
                                        :text_size   ,
                                        :text_angle  ,
                                        :text_just   ,
                                        :text_font   ,
                                        :textstring   ;
*/

{
#line 3459 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 3459 "geoIMS_main.sqc"
  sqlaaloc(3,7,7,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 3459 "geoIMS_main.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 3459 "geoIMS_main.sqc"
      sql_setdlist[0].sqldata = (void*)&text_x;
#line 3459 "geoIMS_main.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 3459 "geoIMS_main.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 3459 "geoIMS_main.sqc"
      sql_setdlist[1].sqldata = (void*)&text_y;
#line 3459 "geoIMS_main.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 3459 "geoIMS_main.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 3459 "geoIMS_main.sqc"
      sql_setdlist[2].sqldata = (void*)&text_size;
#line 3459 "geoIMS_main.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 3459 "geoIMS_main.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 3459 "geoIMS_main.sqc"
      sql_setdlist[3].sqldata = (void*)&text_angle;
#line 3459 "geoIMS_main.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 3459 "geoIMS_main.sqc"
      sql_setdlist[4].sqltype = 500; sql_setdlist[4].sqllen = 2;
#line 3459 "geoIMS_main.sqc"
      sql_setdlist[4].sqldata = (void*)&text_just;
#line 3459 "geoIMS_main.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 3459 "geoIMS_main.sqc"
      sql_setdlist[5].sqltype = 500; sql_setdlist[5].sqllen = 2;
#line 3459 "geoIMS_main.sqc"
      sql_setdlist[5].sqldata = (void*)&text_font;
#line 3459 "geoIMS_main.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 3459 "geoIMS_main.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 51;
#line 3459 "geoIMS_main.sqc"
      sql_setdlist[6].sqldata = (void*)textstring;
#line 3459 "geoIMS_main.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 3459 "geoIMS_main.sqc"
      sqlasetdata(3,0,7,sql_setdlist,0L,0L);
    }
#line 3459 "geoIMS_main.sqc"
  sqlacall((unsigned short)25,3,0,3,0L);
#line 3459 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 3459 "geoIMS_main.sqc"

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
EXEC SQL CLOSE ALL3 ;
*/

{
#line 3477 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 3477 "geoIMS_main.sqc"
  sqlacall((unsigned short)20,3,0,0,0L);
#line 3477 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 3477 "geoIMS_main.sqc"

         }

/*
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
*/

      } while ( 1 );

 
/*
EXEC SQL CLOSE ALL1 ;
*/

{
#line 3502 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 3502 "geoIMS_main.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 3502 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 3502 "geoIMS_main.sqc"


 feat_count = i          ;  // Linux  Fixing geoIMS bug !!!!
 xy_LAST    = xy_index   ;
 text_LAST  = text_index ;

 db_opened[0] = 'Y' ;
 update_layer()     ;
 display_scale()    ;
 // zoom_all("test.png")           ;
 // normal_cursor()    ;


 sprintf (Message, "geoIMS  [ Database : %s ]",db_name);
 XtVaSetValues( toplevel, XmNtitle, Message, NULL ) ;

 xstr = XmStringCreate(" INFO : Function Completed ",CS);
 XtSetArg(args[0], XmNlabelString , xstr);
 XtSetValues(output_label,args,1);


/* Orginal
 sprintf (Message," INFO : Function Completed, [ Feature Count : %d ]",feat_count);
 xstr = XmStringCreate(Message,CS);
 XtSetArg(args[0], XmNlabelString , xstr);
 XtSetValues(output_label,args,1);
*/
}
/*------------------------------------------------------------------------*/
/*                         area_retrievalCB()                             */
/*------------------------------------------------------------------------*/
void area_retrievalCB()
{
 activateMenubar = 1  ;
 // wait_cursor();

 strcpy(STR_PARM,"AR");   /*  LINUX  */
 get_db_name(MainForm);
}
/*------------------------------------------------------------------------*/
/*                         area_retrieval()                             */
/*------------------------------------------------------------------------*/
void area_retrieval()
{

 strcpy ( db_name , DB_name ) ;

 if ( db_opened[0] == 'Y' )
    {
     
/*
EXEC SQL CONNECT RESET;
*/

{
#line 3551 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 3551 "geoIMS_main.sqc"
  sqlacall((unsigned short)29,3,0,0,0L);
#line 3551 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 3551 "geoIMS_main.sqc"

     // CHECKERR ("CONNECT RESET");
     db_opened[0] = 'N' ;
    }


 printf("INFO  : Connecting to Database [ %s ] ..\n",db_name);

 
/*
EXEC SQL CONNECT TO :db_name   ;
*/

{
#line 3559 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 3559 "geoIMS_main.sqc"
  sqlaaloc(2,1,8,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 3559 "geoIMS_main.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 31;
#line 3559 "geoIMS_main.sqc"
      sql_setdlist[0].sqldata = (void*)db_name;
#line 3559 "geoIMS_main.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 3559 "geoIMS_main.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 3559 "geoIMS_main.sqc"
  sqlacall((unsigned short)29,4,2,0,0L);
#line 3559 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 3559 "geoIMS_main.sqc"
   /* CHECKERR ("CONNECT TO geoinfo"); */


  if ( SQLCODE == -1013  || SQLCODE == -1001 || strcmp(db_name,"") == 0 )
    {
     sprintf (Message, "'%s', Database not found" ,db_name);
     xstr  = XmStringCreate("ERROR",CS);
     xstr1 = XmStringCreate(Message,CS);
     n=0;
     XtSetArg(args[n] , XmNdialogTitle   ,        xstr);n++;
     XtSetArg(args[n] , XmNmessageString ,       xstr1);n++;
     XtSetArg(args[n] , XmNwidth         ,         300);n++;
     XtSetArg(args[n] , XmNheight        ,         130);n++;
     XtSetArg(args[n] , XmNborderColor   , white.pixel);n++;
     XtSetArg(args[n] , XmNforeground    , black.pixel);n++;
     XtSetArg(args[n] , XmNbackground    , lgray.pixel);n++;
     PD = XmCreateErrorDialog(MainForm,"PD",args,n);
     XtManageChild(PD);

     // normal_cursor();
     return ;
    }

 if ( SQLCODE == -1032 )
    {
     xstr  = XmStringCreate("ERROR",CS);
     xstr1 = XmStringCreate("Database Engine is not started",CS);
     n=0;
     XtSetArg(args[n] , XmNdialogTitle   ,        xstr);n++;
     XtSetArg(args[n] , XmNmessageString ,       xstr1);n++;
     XtSetArg(args[n] , XmNwidth         ,         300);n++;
     XtSetArg(args[n] , XmNheight        ,         130);n++;
     XtSetArg(args[n] , XmNborderColor   , white.pixel);n++;
     XtSetArg(args[n] , XmNforeground    , black.pixel);n++;
     XtSetArg(args[n] , XmNbackground    , lgray.pixel);n++;
     PD = XmCreateErrorDialog(MainForm,"PD",args,n);
     XtManageChild(PD);

     // normal_cursor();
     return ;
    }

 XSynchronize(MainDisplay,1);
  cls_flag = 1 ;
  XClearWindow(MainDisplay,XtWindow(drawarea));
  XFillRectangle(MainDisplay,Tile,Tilegc,0,0,499,499);
 XSynchronize(MainDisplay,0);

 printf("INFO  : Retrieving from Database ...\n");

 area_xmin = AREA_XMIN  ;
 area_xmax = AREA_XMAX  ;
 area_ymin = AREA_YMIN  ;
 area_ymax = AREA_YMAX  ;

 
/*
EXEC SQL DECLARE AR1 CURSOR FOR
          SELECT  feat_num,
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
          FROM    features
          WHERE   ((x_base between :area_xmin and :area_xmax AND y_base between :area_ymin and :area_ymax )
                    OR
                   (x_end  between :area_xmin and :area_xmax AND y_end  between :area_ymin and :area_ymax ))
          FOR     READ ONLY;
*/

#line 3641 "geoIMS_main.sqc"
           /*      AND  layer <> 2 */
                //   AND  layer = 1

 // CHECKERR ("DECLARE CURSOR");

 
/*
EXEC SQL DECLARE AR2 CURSOR FOR
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

#line 3660 "geoIMS_main.sqc"

 // CHECKERR ("DECLARE CURSOR");

 
/*
EXEC SQL DECLARE AR3 CURSOR FOR
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

#line 3673 "geoIMS_main.sqc"

 // CHECKERR ("DECLARE CURSOR");


 
/*
EXEC SQL OPEN AR1 ;
*/

{
#line 3677 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 3677 "geoIMS_main.sqc"
  sqlaaloc(2,8,9,0L);
    {
      struct sqla_setdata_list sql_setdlist[8];
#line 3677 "geoIMS_main.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 3677 "geoIMS_main.sqc"
      sql_setdlist[0].sqldata = (void*)&area_xmin;
#line 3677 "geoIMS_main.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 3677 "geoIMS_main.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 3677 "geoIMS_main.sqc"
      sql_setdlist[1].sqldata = (void*)&area_xmax;
#line 3677 "geoIMS_main.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 3677 "geoIMS_main.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 3677 "geoIMS_main.sqc"
      sql_setdlist[2].sqldata = (void*)&area_ymin;
#line 3677 "geoIMS_main.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 3677 "geoIMS_main.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 3677 "geoIMS_main.sqc"
      sql_setdlist[3].sqldata = (void*)&area_ymax;
#line 3677 "geoIMS_main.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 3677 "geoIMS_main.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 3677 "geoIMS_main.sqc"
      sql_setdlist[4].sqldata = (void*)&area_xmin;
#line 3677 "geoIMS_main.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 3677 "geoIMS_main.sqc"
      sql_setdlist[5].sqltype = 496; sql_setdlist[5].sqllen = 4;
#line 3677 "geoIMS_main.sqc"
      sql_setdlist[5].sqldata = (void*)&area_xmax;
#line 3677 "geoIMS_main.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 3677 "geoIMS_main.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 3677 "geoIMS_main.sqc"
      sql_setdlist[6].sqldata = (void*)&area_ymin;
#line 3677 "geoIMS_main.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 3677 "geoIMS_main.sqc"
      sql_setdlist[7].sqltype = 496; sql_setdlist[7].sqllen = 4;
#line 3677 "geoIMS_main.sqc"
      sql_setdlist[7].sqldata = (void*)&area_ymax;
#line 3677 "geoIMS_main.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 3677 "geoIMS_main.sqc"
      sqlasetdata(2,0,8,sql_setdlist,0L,0L);
    }
#line 3677 "geoIMS_main.sqc"
  sqlacall((unsigned short)26,4,2,0,0L);
#line 3677 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 3677 "geoIMS_main.sqc"
     /* CHECKERR ("OPEN CURSOR"); */

 i = 0             ;     /* Used for workspace Load   */
 xy_index   = 0    ;
 text_index = 0    ;
 feat_count = 0    ;     /* Reset Total Number of Features  */
 lay_count  = 0    ;     /* Reset Total Number of Layers    */
 trace_on[0] = 'N' ;     /* Reset Trace Flag                */


 do {
     
/*
EXEC SQL FETCH AR1 INTO :feat_num,
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
                             :text_count  ;
*/

{
#line 3709 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 3709 "geoIMS_main.sqc"
  sqlaaloc(3,22,10,0L);
    {
      struct sqla_setdata_list sql_setdlist[22];
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[0].sqldata = (void*)&feat_num;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 13;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[1].sqldata = (void*)feat_code;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[2].sqldata = (void*)&type;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[3].sqldata = (void*)&layer;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[4].sqldata = (void*)&network;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 6;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[5].sqldata = (void*)scale_range;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 2;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[6].sqldata = (void*)rdisplayed;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 2;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[7].sqldata = (void*)rselectable;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 2;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[8].sqldata = (void*)rhas_attrib;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 2;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[9].sqldata = (void*)rhas_text;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[10].sqltype = 500; sql_setdlist[10].sqllen = 2;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[10].sqldata = (void*)&feat_color;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[11].sqltype = 500; sql_setdlist[11].sqllen = 2;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[11].sqldata = (void*)&feat_linetype;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[12].sqltype = 500; sql_setdlist[12].sqllen = 2;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[12].sqldata = (void*)&feat_linewidth;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[13].sqltype = 496; sql_setdlist[13].sqllen = 4;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[13].sqldata = (void*)&x_base;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[14].sqltype = 496; sql_setdlist[14].sqllen = 4;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[14].sqldata = (void*)&y_base;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[15].sqltype = 496; sql_setdlist[15].sqllen = 4;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[15].sqldata = (void*)&x_end;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[16].sqltype = 496; sql_setdlist[16].sqllen = 4;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[16].sqldata = (void*)&y_end;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[17].sqltype = 496; sql_setdlist[17].sqllen = 4;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[17].sqldata = (void*)&xy_count;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[18].sqltype = 496; sql_setdlist[18].sqllen = 4;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[18].sqldata = (void*)&symb_num;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[19].sqltype = 496; sql_setdlist[19].sqllen = 4;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[19].sqldata = (void*)&symb_size;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[20].sqltype = 496; sql_setdlist[20].sqllen = 4;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[20].sqldata = (void*)&symb_angle;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[21].sqltype = 496; sql_setdlist[21].sqllen = 4;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[21].sqldata = (void*)&text_count;
#line 3709 "geoIMS_main.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 3709 "geoIMS_main.sqc"
      sqlasetdata(3,0,22,sql_setdlist,0L,0L);
    }
#line 3709 "geoIMS_main.sqc"
  sqlacall((unsigned short)25,4,0,3,0L);
#line 3709 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 3709 "geoIMS_main.sqc"


     if (SQLCODE != 0)
        {
         if (SQLCODE != 100)
            {
             fprintf(stderr,"ERROR : Reading from Features [SQLCODE] = %d\n",SQLCODE);
            }
         break ;
        }

     feat[++i].num         = feat_num       ;
     sscanf (feat_code,"%s",&feat[i].code)  ; /* use sscanf to Trim DB2 trailing spaces */
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


     if  ( feat[i].xy_count > 0 )
         {
          
/*
EXEC SQL OPEN AR2;
*/

{
#line 3747 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 3747 "geoIMS_main.sqc"
  sqlaaloc(2,1,11,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 3747 "geoIMS_main.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 3747 "geoIMS_main.sqc"
      sql_setdlist[0].sqldata = (void*)&feat_num;
#line 3747 "geoIMS_main.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 3747 "geoIMS_main.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 3747 "geoIMS_main.sqc"
  sqlacall((unsigned short)26,5,2,0,0L);
#line 3747 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 3747 "geoIMS_main.sqc"
    /* CHECKERR ("OPEN CURSOR"); */

          feat[i].xy = xy_index ;
          j = 0 ;

          for (iii=1; iii<=(feat[i].xy_count/10); iii++)
              {
               
/*
EXEC SQL FETCH AR2 INTO :seq ,
                                       :x_1 ,:y_1,
                                       :x_2 ,:y_2,
                                       :x_3 ,:y_3,
                                       :x_4 ,:y_4,
                                       :x_5 ,:y_5,
                                       :x_6 ,:y_6,
                                       :x_7 ,:y_7,
                                       :x_8 ,:y_8,
                                       :x_9 ,:y_9,
                                       :x_10,:y_10  ;
*/

{
#line 3764 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 3764 "geoIMS_main.sqc"
  sqlaaloc(3,21,12,0L);
    {
      struct sqla_setdata_list sql_setdlist[21];
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[0].sqldata = (void*)&seq;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[1].sqldata = (void*)&x_1;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[2].sqldata = (void*)&y_1;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[3].sqldata = (void*)&x_2;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[4].sqldata = (void*)&y_2;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[5].sqltype = 496; sql_setdlist[5].sqllen = 4;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[5].sqldata = (void*)&x_3;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[6].sqldata = (void*)&y_3;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[7].sqltype = 496; sql_setdlist[7].sqllen = 4;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[7].sqldata = (void*)&x_4;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[8].sqltype = 496; sql_setdlist[8].sqllen = 4;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[8].sqldata = (void*)&y_4;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[9].sqltype = 496; sql_setdlist[9].sqllen = 4;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[9].sqldata = (void*)&x_5;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[10].sqltype = 496; sql_setdlist[10].sqllen = 4;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[10].sqldata = (void*)&y_5;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[11].sqltype = 496; sql_setdlist[11].sqllen = 4;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[11].sqldata = (void*)&x_6;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[12].sqltype = 496; sql_setdlist[12].sqllen = 4;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[12].sqldata = (void*)&y_6;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[13].sqltype = 496; sql_setdlist[13].sqllen = 4;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[13].sqldata = (void*)&x_7;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[14].sqltype = 496; sql_setdlist[14].sqllen = 4;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[14].sqldata = (void*)&y_7;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[15].sqltype = 496; sql_setdlist[15].sqllen = 4;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[15].sqldata = (void*)&x_8;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[16].sqltype = 496; sql_setdlist[16].sqllen = 4;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[16].sqldata = (void*)&y_8;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[17].sqltype = 496; sql_setdlist[17].sqllen = 4;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[17].sqldata = (void*)&x_9;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[18].sqltype = 496; sql_setdlist[18].sqllen = 4;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[18].sqldata = (void*)&y_9;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[19].sqltype = 496; sql_setdlist[19].sqllen = 4;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[19].sqldata = (void*)&x_10;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[20].sqltype = 496; sql_setdlist[20].sqllen = 4;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[20].sqldata = (void*)&y_10;
#line 3764 "geoIMS_main.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 3764 "geoIMS_main.sqc"
      sqlasetdata(3,0,21,sql_setdlist,0L,0L);
    }
#line 3764 "geoIMS_main.sqc"
  sqlacall((unsigned short)25,5,0,3,0L);
#line 3764 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 3764 "geoIMS_main.sqc"

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
EXEC SQL FETCH AR2 INTO :seq ,
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
#line 3795 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 3795 "geoIMS_main.sqc"
  sqlaaloc(3,21,13,0L);
    {
      struct sqla_setdata_list sql_setdlist[21];
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[0].sqldata = (void*)&seq;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[1].sqldata = (void*)&x_1;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[2].sqldata = (void*)&y_1;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[3].sqldata = (void*)&x_2;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[4].sqldata = (void*)&y_2;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[5].sqltype = 496; sql_setdlist[5].sqllen = 4;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[5].sqldata = (void*)&x_3;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[6].sqldata = (void*)&y_3;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[7].sqltype = 496; sql_setdlist[7].sqllen = 4;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[7].sqldata = (void*)&x_4;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[8].sqltype = 496; sql_setdlist[8].sqllen = 4;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[8].sqldata = (void*)&y_4;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[9].sqltype = 496; sql_setdlist[9].sqllen = 4;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[9].sqldata = (void*)&x_5;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[10].sqltype = 496; sql_setdlist[10].sqllen = 4;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[10].sqldata = (void*)&y_5;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[11].sqltype = 496; sql_setdlist[11].sqllen = 4;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[11].sqldata = (void*)&x_6;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[12].sqltype = 496; sql_setdlist[12].sqllen = 4;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[12].sqldata = (void*)&y_6;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[13].sqltype = 496; sql_setdlist[13].sqllen = 4;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[13].sqldata = (void*)&x_7;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[14].sqltype = 496; sql_setdlist[14].sqllen = 4;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[14].sqldata = (void*)&y_7;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[15].sqltype = 496; sql_setdlist[15].sqllen = 4;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[15].sqldata = (void*)&x_8;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[16].sqltype = 496; sql_setdlist[16].sqllen = 4;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[16].sqldata = (void*)&y_8;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[17].sqltype = 496; sql_setdlist[17].sqllen = 4;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[17].sqldata = (void*)&x_9;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[18].sqltype = 496; sql_setdlist[18].sqllen = 4;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[18].sqldata = (void*)&y_9;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[19].sqltype = 496; sql_setdlist[19].sqllen = 4;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[19].sqldata = (void*)&x_10;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[20].sqltype = 496; sql_setdlist[20].sqllen = 4;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[20].sqldata = (void*)&y_10;
#line 3795 "geoIMS_main.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 3795 "geoIMS_main.sqc"
      sqlasetdata(3,0,21,sql_setdlist,0L,0L);
    }
#line 3795 "geoIMS_main.sqc"
  sqlacall((unsigned short)25,5,0,3,0L);
#line 3795 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 3795 "geoIMS_main.sqc"

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
EXEC SQL CLOSE AR2;
*/

{
#line 3812 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 3812 "geoIMS_main.sqc"
  sqlacall((unsigned short)20,5,0,0,0L);
#line 3812 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 3812 "geoIMS_main.sqc"
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
EXEC SQL OPEN AR3 ;
*/

{
#line 3825 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 3825 "geoIMS_main.sqc"
  sqlaaloc(2,1,14,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 3825 "geoIMS_main.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 3825 "geoIMS_main.sqc"
      sql_setdlist[0].sqldata = (void*)&feat_num;
#line 3825 "geoIMS_main.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 3825 "geoIMS_main.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 3825 "geoIMS_main.sqc"
  sqlacall((unsigned short)26,6,2,0,0L);
#line 3825 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 3825 "geoIMS_main.sqc"
    /* CHECKERR ("OPEN CURSOR"); */

          feat[i].text = text_index ;

          for (iii=1; iii<=feat[i].text_count; iii++)
              {
               
/*
EXEC SQL FETCH AR3 INTO :text_x      ,
                                       :text_y      ,
                                       :text_size   ,
                                       :text_angle  ,
                                       :text_just   ,
                                       :text_font   ,
                                       :textstring   ;
*/

{
#line 3837 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 3837 "geoIMS_main.sqc"
  sqlaaloc(3,7,15,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 3837 "geoIMS_main.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 3837 "geoIMS_main.sqc"
      sql_setdlist[0].sqldata = (void*)&text_x;
#line 3837 "geoIMS_main.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 3837 "geoIMS_main.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 3837 "geoIMS_main.sqc"
      sql_setdlist[1].sqldata = (void*)&text_y;
#line 3837 "geoIMS_main.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 3837 "geoIMS_main.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 3837 "geoIMS_main.sqc"
      sql_setdlist[2].sqldata = (void*)&text_size;
#line 3837 "geoIMS_main.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 3837 "geoIMS_main.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 3837 "geoIMS_main.sqc"
      sql_setdlist[3].sqldata = (void*)&text_angle;
#line 3837 "geoIMS_main.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 3837 "geoIMS_main.sqc"
      sql_setdlist[4].sqltype = 500; sql_setdlist[4].sqllen = 2;
#line 3837 "geoIMS_main.sqc"
      sql_setdlist[4].sqldata = (void*)&text_just;
#line 3837 "geoIMS_main.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 3837 "geoIMS_main.sqc"
      sql_setdlist[5].sqltype = 500; sql_setdlist[5].sqllen = 2;
#line 3837 "geoIMS_main.sqc"
      sql_setdlist[5].sqldata = (void*)&text_font;
#line 3837 "geoIMS_main.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 3837 "geoIMS_main.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 51;
#line 3837 "geoIMS_main.sqc"
      sql_setdlist[6].sqldata = (void*)textstring;
#line 3837 "geoIMS_main.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 3837 "geoIMS_main.sqc"
      sqlasetdata(3,0,7,sql_setdlist,0L,0L);
    }
#line 3837 "geoIMS_main.sqc"
  sqlacall((unsigned short)25,6,0,3,0L);
#line 3837 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 3837 "geoIMS_main.sqc"



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
EXEC SQL CLOSE AR3 ;
*/

{
#line 3857 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 3857 "geoIMS_main.sqc"
  sqlacall((unsigned short)20,6,0,0,0L);
#line 3857 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 3857 "geoIMS_main.sqc"
     /* CHECKERR ("CLOSE CURSOR"); */
         }

/*
     switch(feat[i].color)
           {
            case 1:  feat[i].color = blue.pixel  ; break;
            case 2:  feat[i].color = red.pixel   ; break;
            case 3:  feat[i].color = pink.pixel  ; break;
            case 4:  feat[i].color = green.pixel ; break;
            case 5:  feat[i].color = cyan.pixel  ; break;
            case 6:  feat[i].color = yellow.pixel; break;
            case 7:  feat[i].color = white.pixel ; break;
            case 8:  feat[i].color = black.pixel ; break;
            case 9:  feat[i].color = gray.pixel  ; break;
            case 10: feat[i].color = wheat.pixel ; break;
            case 11: feat[i].color = brown.pixel ; break;
            case 12: feat[i].color = orange.pixel; break;

            default: feat[i].color = brown.pixel ;  break;
           }
*/

 /*
     if ( feat[i].xy_count > 0 )
        {
         for ( j=1 ; j<=feat[i].xy_count ; j++ )
             {
              if(( x[feat[i].xy+j] < 5200000  || x[feat[i].xy+j] > 5210000 ) ||
                 ( y[feat[i].xy+j] < 23752500 || y[feat[i].xy+j] > 23760000))
                {
                 xy_index   = xy_index   - feat[i].xy_count   ;
                 text_index = text_index - feat[i].text_count ;
                 i-- ;
                 break ;
                }
              }
        }
    else
        {
         if(( feat[i].xbase < 5200000 || feat[i].xbase > 5210000 || feat[i].ybase < 23752500 || feat[i].ybase > 23760000 )
              &&
            ( feat[i].xend  < 5200000 || feat[i].xend  > 5210000 || feat[i].yend  < 23752500 || feat[i].yend  > 23760000 ))
            {
             xy_index   = xy_index   - feat[i].xy_count   ;
             text_index = text_index - feat[i].text_count ;
             i-- ;
            }
        }
 */


      } while ( 1 );


 
/*
EXEC SQL CLOSE AR1 ;
*/

{
#line 3912 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 3912 "geoIMS_main.sqc"
  sqlacall((unsigned short)20,4,0,0,0L);
#line 3912 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 3912 "geoIMS_main.sqc"
    /* CHECKERR ("CLOSE CURSOR"); */


 if ( i == 0 )
     feat_count = i     ;
 else
     feat_count = i     ;   // Linux fixing geoIMS bug !!

 xy_LAST    = xy_index   ;
 text_LAST  = text_index ;

 db_opened[0] = 'Y' ;
 update_layer()     ;
 display_scale()    ;
 // zoom_all("test.png")           ;
 // normal_cursor()    ;

 sprintf (Message, "geoIMS  [ Database : %s ]",db_name);
 XtVaSetValues( toplevel, XmNtitle, Message, NULL ) ;

 xstr = XmStringCreate(" INFO : Function Completed ",CS);
 XtSetArg(args[0], XmNlabelString , xstr);
 XtSetValues(output_label,args,1);


/* Original
 sprintf (Message," INFO : Function Completed, [ Feature Count : %d ]",feat_count);
 xstr = XmStringCreate(Message,CS);
 XtSetArg(args[0], XmNlabelString , xstr);
 XtSetValues(output_label,args,1);
*/
}
/*------------------------------------------------------------------------*/
/*                       network_retrievalCB()                            */
/*------------------------------------------------------------------------*/

void network_retrievalCB()
{
 activateMenubar = 1  ;
 // wait_cursor();

 strcpy(STR_PARM,"NR");   /*  LINUX  */
 get_db_name(MainForm);
}
/*------------------------------------------------------------------------*/
/*                       network_retrieval()                              */
/*------------------------------------------------------------------------*/
void network_retrieval()
{
 strcpy ( db_name , DB_name ) ;

 if ( db_opened[0] == 'Y' )
    {
     
/*
EXEC SQL CONNECT RESET;
*/

{
#line 3965 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 3965 "geoIMS_main.sqc"
  sqlacall((unsigned short)29,3,0,0,0L);
#line 3965 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 3965 "geoIMS_main.sqc"

     // CHECKERR ("CONNECT RESET");
     db_opened[0] = 'N' ;
    }

 printf("INFO  : Connecting to Database [ %s ] ..\n",db_name);

 
/*
EXEC SQL CONNECT TO :db_name   ;
*/

{
#line 3972 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 3972 "geoIMS_main.sqc"
  sqlaaloc(2,1,16,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 3972 "geoIMS_main.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 31;
#line 3972 "geoIMS_main.sqc"
      sql_setdlist[0].sqldata = (void*)db_name;
#line 3972 "geoIMS_main.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 3972 "geoIMS_main.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 3972 "geoIMS_main.sqc"
  sqlacall((unsigned short)29,4,2,0,0L);
#line 3972 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 3972 "geoIMS_main.sqc"
   /* CHECKERR ("CONNECT TO geoinfo"); */


  if ( SQLCODE == -1013  || SQLCODE == -1001 || strcmp(db_name,"") == 0 )
    {
     sprintf (Message, "'%s', Database not found" ,db_name);
     xstr  = XmStringCreate("ERROR",CS);
     xstr1 = XmStringCreate(Message,CS);
     n=0;
     XtSetArg(args[n] , XmNdialogTitle   ,        xstr);n++;
     XtSetArg(args[n] , XmNmessageString ,       xstr1);n++;
     XtSetArg(args[n] , XmNwidth         ,         300);n++;
     XtSetArg(args[n] , XmNheight        ,         130);n++;
     XtSetArg(args[n] , XmNborderColor   , white.pixel);n++;
     XtSetArg(args[n] , XmNforeground    , black.pixel);n++;
     XtSetArg(args[n] , XmNbackground    , lgray.pixel);n++;
     PD = XmCreateErrorDialog(MainForm,"PD",args,n);
     XtManageChild(PD);

     // normal_cursor();
     return ;
    }

 if ( SQLCODE == -1032 )
    {
     xstr  = XmStringCreate("ERROR",CS);
     xstr1 = XmStringCreate("Database Engine is not started",CS);
     n=0;
     XtSetArg(args[n] , XmNdialogTitle   ,        xstr);n++;
     XtSetArg(args[n] , XmNmessageString ,       xstr1);n++;
     XtSetArg(args[n] , XmNwidth         ,         300);n++;
     XtSetArg(args[n] , XmNheight        ,         130);n++;
     XtSetArg(args[n] , XmNborderColor   , white.pixel);n++;
     XtSetArg(args[n] , XmNforeground    , black.pixel);n++;
     XtSetArg(args[n] , XmNbackground    , lgray.pixel);n++;
     PD = XmCreateErrorDialog(MainForm,"PD",args,n);
     XtManageChild(PD);

     // normal_cursor();
     return ;
    }

 XSynchronize(MainDisplay,1);
  cls_flag = 1 ;
  XClearWindow(MainDisplay,XtWindow(drawarea));
  XFillRectangle(MainDisplay,Tile,Tilegc,0,0,499,499);
 XSynchronize(MainDisplay,0);

 printf("INFO  : Retrieving from Database ...\n");

 i = 1           ;
 conn_count  = 0 ;
 stack_count = 0 ;

 strcpy(grid  ,GRID_NAME  );                  /* Get Grid feat_num      */
 strcpy(feeder,FEEDER_NAME);                  /* Get Grid feat_num      */

 
/*
EXEC SQL SELECT feat_num
          INTO   :number
          FROM   grid
          WHERE  grid_id = :grid    ;
*/

{
#line 4032 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 4032 "geoIMS_main.sqc"
  sqlaaloc(2,1,17,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 4032 "geoIMS_main.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 13;
#line 4032 "geoIMS_main.sqc"
      sql_setdlist[0].sqldata = (void*)grid;
#line 4032 "geoIMS_main.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 4032 "geoIMS_main.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 4032 "geoIMS_main.sqc"
  sqlaaloc(3,1,18,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 4032 "geoIMS_main.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 4032 "geoIMS_main.sqc"
      sql_setdlist[0].sqldata = (void*)&number;
#line 4032 "geoIMS_main.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 4032 "geoIMS_main.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 4032 "geoIMS_main.sqc"
  sqlacall((unsigned short)24,7,2,3,0L);
#line 4032 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 4032 "geoIMS_main.sqc"


 
/*
EXEC SQL DECLARE NR1 CURSOR FOR              /- Get Feeder's feat_num  -/
          SELECT  ARC                         /- Connected to GRID      -/
          FROM    connectivity
          WHERE   S_NODE  = :number
          FOR     READ ONLY ;
*/

#line 4038 "geoIMS_main.sqc"



 
/*
EXEC SQL OPEN  NR1 ;
*/

{
#line 4041 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 4041 "geoIMS_main.sqc"
  sqlaaloc(2,1,19,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 4041 "geoIMS_main.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 4041 "geoIMS_main.sqc"
      sql_setdlist[0].sqldata = (void*)&number;
#line 4041 "geoIMS_main.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 4041 "geoIMS_main.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 4041 "geoIMS_main.sqc"
  sqlacall((unsigned short)26,8,2,0,0L);
#line 4041 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 4041 "geoIMS_main.sqc"

 do {
     
/*
EXEC SQL FETCH NR1  INTO :conn_feat ;
*/

{
#line 4043 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 4043 "geoIMS_main.sqc"
  sqlaaloc(3,1,20,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 4043 "geoIMS_main.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 4043 "geoIMS_main.sqc"
      sql_setdlist[0].sqldata = (void*)&conn_feat;
#line 4043 "geoIMS_main.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 4043 "geoIMS_main.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 4043 "geoIMS_main.sqc"
  sqlacall((unsigned short)25,8,0,3,0L);
#line 4043 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 4043 "geoIMS_main.sqc"

     if (SQLCODE != 0) break ;
     conn_stack[++stack_count] = conn_feat ;
    } while(1);
 
/*
EXEC SQL CLOSE NR1 ;
*/

{
#line 4047 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 4047 "geoIMS_main.sqc"
  sqlacall((unsigned short)20,8,0,0,0L);
#line 4047 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 4047 "geoIMS_main.sqc"




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
#line 4057 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 4057 "geoIMS_main.sqc"
  sqlaaloc(2,1,21,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 4057 "geoIMS_main.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 4057 "geoIMS_main.sqc"
      sql_setdlist[0].sqldata = (void*)&number;
#line 4057 "geoIMS_main.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 4057 "geoIMS_main.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 4057 "geoIMS_main.sqc"
  sqlaaloc(3,1,22,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 4057 "geoIMS_main.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 13;
#line 4057 "geoIMS_main.sqc"
      sql_setdlist[0].sqldata = (void*)code1;
#line 4057 "geoIMS_main.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 4057 "geoIMS_main.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 4057 "geoIMS_main.sqc"
  sqlacall((unsigned short)24,9,2,3,0L);
#line 4057 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 4057 "geoIMS_main.sqc"

      sscanf (code1,"%s",code) ;


      if ( strcmp(feeder,"all") == 0  || strcmp(feeder,"ALL") == 0 )
         {
          append_net(number,"grid") ;
         }
      else
      if ( strcmp (code,feeder) == 0 )
         {
          trace_net(number,"grid") ;
         }
     }

 
/*
EXEC SQL DECLARE  NR2  CURSOR FOR
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

#line 4086 "geoIMS_main.sqc"

 // CHECKERR ("DECLARE CURSOR");


 
/*
EXEC SQL DECLARE NR3 CURSOR FOR
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

#line 4100 "geoIMS_main.sqc"

 // CHECKERR ("DECLARE CURSOR");


 i = 0              ;     /* Used for workspace Load         */
 xy_index   = 0     ;
 text_index = 0     ;
 feat_count = 0     ;     /* Reset Total Number of Features  */
 lay_count  = 0     ;     /* Reset Total Number of Layers    */
 trace_on[0] = 'N'  ;     /* Reset Trace Flag                */


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
#line 4160 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 4160 "geoIMS_main.sqc"
  sqlaaloc(2,1,23,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[0].sqldata = (void*)&number;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 4160 "geoIMS_main.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 4160 "geoIMS_main.sqc"
  sqlaaloc(3,22,24,0L);
    {
      struct sqla_setdata_list sql_setdlist[22];
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[0].sqldata = (void*)&feat_num;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 13;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[1].sqldata = (void*)feat_code;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[2].sqldata = (void*)&type;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[3].sqldata = (void*)&layer;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[4].sqldata = (void*)&network;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 6;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[5].sqldata = (void*)scale_range;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 2;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[6].sqldata = (void*)rdisplayed;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 2;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[7].sqldata = (void*)rselectable;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 2;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[8].sqldata = (void*)rhas_attrib;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 2;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[9].sqldata = (void*)rhas_text;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[10].sqltype = 500; sql_setdlist[10].sqllen = 2;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[10].sqldata = (void*)&feat_color;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[11].sqltype = 500; sql_setdlist[11].sqllen = 2;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[11].sqldata = (void*)&feat_linetype;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[12].sqltype = 500; sql_setdlist[12].sqllen = 2;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[12].sqldata = (void*)&feat_linewidth;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[13].sqltype = 496; sql_setdlist[13].sqllen = 4;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[13].sqldata = (void*)&x_base;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[14].sqltype = 496; sql_setdlist[14].sqllen = 4;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[14].sqldata = (void*)&y_base;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[15].sqltype = 496; sql_setdlist[15].sqllen = 4;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[15].sqldata = (void*)&x_end;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[16].sqltype = 496; sql_setdlist[16].sqllen = 4;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[16].sqldata = (void*)&y_end;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[17].sqltype = 496; sql_setdlist[17].sqllen = 4;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[17].sqldata = (void*)&xy_count;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[18].sqltype = 496; sql_setdlist[18].sqllen = 4;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[18].sqldata = (void*)&symb_num;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[19].sqltype = 496; sql_setdlist[19].sqllen = 4;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[19].sqldata = (void*)&symb_size;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[20].sqltype = 496; sql_setdlist[20].sqllen = 4;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[20].sqldata = (void*)&symb_angle;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[21].sqltype = 496; sql_setdlist[21].sqllen = 4;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[21].sqldata = (void*)&text_count;
#line 4160 "geoIMS_main.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 4160 "geoIMS_main.sqc"
      sqlasetdata(3,0,22,sql_setdlist,0L,0L);
    }
#line 4160 "geoIMS_main.sqc"
  sqlacall((unsigned short)24,12,2,3,0L);
#line 4160 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 4160 "geoIMS_main.sqc"


      if (SQLCODE != 0)
         {
         if (SQLCODE != 100)
            {
             fprintf(stderr,"ERROR : Reading from Features SQLCODE = %d\n",SQLCODE);
            }
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
EXEC SQL OPEN NR2 ;
*/

{
#line 4198 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 4198 "geoIMS_main.sqc"
  sqlaaloc(2,1,25,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 4198 "geoIMS_main.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 4198 "geoIMS_main.sqc"
      sql_setdlist[0].sqldata = (void*)&feat_num;
#line 4198 "geoIMS_main.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 4198 "geoIMS_main.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 4198 "geoIMS_main.sqc"
  sqlacall((unsigned short)26,10,2,0,0L);
#line 4198 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 4198 "geoIMS_main.sqc"


          feat[i].xy = xy_index ;
          j = 0 ;

          for (iii=1; iii<=(feat[i].xy_count/10); iii++)
              {
               
/*
EXEC SQL FETCH NR2 INTO :seq ,:x_1,:y_1,:x_2,:y_2,:x_3,:y_3,
                                             :x_4,:y_4,:x_5,:y_5,:x_6,:y_6,
                                             :x_7,:y_7,:x_8,:y_8,:x_9,:y_9,:x_10,:y_10;
*/

{
#line 4207 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 4207 "geoIMS_main.sqc"
  sqlaaloc(3,21,26,0L);
    {
      struct sqla_setdata_list sql_setdlist[21];
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[0].sqldata = (void*)&seq;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[1].sqldata = (void*)&x_1;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[2].sqldata = (void*)&y_1;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[3].sqldata = (void*)&x_2;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[4].sqldata = (void*)&y_2;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[5].sqltype = 496; sql_setdlist[5].sqllen = 4;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[5].sqldata = (void*)&x_3;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[6].sqldata = (void*)&y_3;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[7].sqltype = 496; sql_setdlist[7].sqllen = 4;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[7].sqldata = (void*)&x_4;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[8].sqltype = 496; sql_setdlist[8].sqllen = 4;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[8].sqldata = (void*)&y_4;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[9].sqltype = 496; sql_setdlist[9].sqllen = 4;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[9].sqldata = (void*)&x_5;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[10].sqltype = 496; sql_setdlist[10].sqllen = 4;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[10].sqldata = (void*)&y_5;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[11].sqltype = 496; sql_setdlist[11].sqllen = 4;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[11].sqldata = (void*)&x_6;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[12].sqltype = 496; sql_setdlist[12].sqllen = 4;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[12].sqldata = (void*)&y_6;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[13].sqltype = 496; sql_setdlist[13].sqllen = 4;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[13].sqldata = (void*)&x_7;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[14].sqltype = 496; sql_setdlist[14].sqllen = 4;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[14].sqldata = (void*)&y_7;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[15].sqltype = 496; sql_setdlist[15].sqllen = 4;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[15].sqldata = (void*)&x_8;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[16].sqltype = 496; sql_setdlist[16].sqllen = 4;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[16].sqldata = (void*)&y_8;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[17].sqltype = 496; sql_setdlist[17].sqllen = 4;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[17].sqldata = (void*)&x_9;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[18].sqltype = 496; sql_setdlist[18].sqllen = 4;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[18].sqldata = (void*)&y_9;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[19].sqltype = 496; sql_setdlist[19].sqllen = 4;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[19].sqldata = (void*)&x_10;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[20].sqltype = 496; sql_setdlist[20].sqllen = 4;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[20].sqldata = (void*)&y_10;
#line 4207 "geoIMS_main.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 4207 "geoIMS_main.sqc"
      sqlasetdata(3,0,21,sql_setdlist,0L,0L);
    }
#line 4207 "geoIMS_main.sqc"
  sqlacall((unsigned short)25,10,0,3,0L);
#line 4207 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 4207 "geoIMS_main.sqc"


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
EXEC SQL FETCH NR2 INTO :seq ,
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
#line 4239 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 4239 "geoIMS_main.sqc"
  sqlaaloc(3,21,27,0L);
    {
      struct sqla_setdata_list sql_setdlist[21];
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[0].sqldata = (void*)&seq;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[1].sqldata = (void*)&x_1;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[2].sqldata = (void*)&y_1;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[3].sqldata = (void*)&x_2;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[4].sqldata = (void*)&y_2;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[5].sqltype = 496; sql_setdlist[5].sqllen = 4;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[5].sqldata = (void*)&x_3;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[6].sqldata = (void*)&y_3;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[7].sqltype = 496; sql_setdlist[7].sqllen = 4;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[7].sqldata = (void*)&x_4;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[8].sqltype = 496; sql_setdlist[8].sqllen = 4;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[8].sqldata = (void*)&y_4;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[9].sqltype = 496; sql_setdlist[9].sqllen = 4;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[9].sqldata = (void*)&x_5;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[10].sqltype = 496; sql_setdlist[10].sqllen = 4;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[10].sqldata = (void*)&y_5;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[11].sqltype = 496; sql_setdlist[11].sqllen = 4;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[11].sqldata = (void*)&x_6;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[12].sqltype = 496; sql_setdlist[12].sqllen = 4;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[12].sqldata = (void*)&y_6;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[13].sqltype = 496; sql_setdlist[13].sqllen = 4;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[13].sqldata = (void*)&x_7;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[14].sqltype = 496; sql_setdlist[14].sqllen = 4;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[14].sqldata = (void*)&y_7;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[15].sqltype = 496; sql_setdlist[15].sqllen = 4;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[15].sqldata = (void*)&x_8;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[16].sqltype = 496; sql_setdlist[16].sqllen = 4;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[16].sqldata = (void*)&y_8;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[17].sqltype = 496; sql_setdlist[17].sqllen = 4;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[17].sqldata = (void*)&x_9;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[18].sqltype = 496; sql_setdlist[18].sqllen = 4;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[18].sqldata = (void*)&y_9;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[19].sqltype = 496; sql_setdlist[19].sqllen = 4;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[19].sqldata = (void*)&x_10;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[20].sqltype = 496; sql_setdlist[20].sqllen = 4;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[20].sqldata = (void*)&y_10;
#line 4239 "geoIMS_main.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 4239 "geoIMS_main.sqc"
      sqlasetdata(3,0,21,sql_setdlist,0L,0L);
    }
#line 4239 "geoIMS_main.sqc"
  sqlacall((unsigned short)25,10,0,3,0L);
#line 4239 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 4239 "geoIMS_main.sqc"

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
EXEC SQL CLOSE NR2 ;
*/

{
#line 4256 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 4256 "geoIMS_main.sqc"
  sqlacall((unsigned short)20,10,0,0,0L);
#line 4256 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 4256 "geoIMS_main.sqc"
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
EXEC SQL OPEN NR3 ;
*/

{
#line 4269 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 4269 "geoIMS_main.sqc"
  sqlaaloc(2,1,28,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 4269 "geoIMS_main.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 4269 "geoIMS_main.sqc"
      sql_setdlist[0].sqldata = (void*)&feat_num;
#line 4269 "geoIMS_main.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 4269 "geoIMS_main.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 4269 "geoIMS_main.sqc"
  sqlacall((unsigned short)26,11,2,0,0L);
#line 4269 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 4269 "geoIMS_main.sqc"
    /* CHECKERR ("OPEN CURSOR"); */

          feat[i].text = text_index ;

          for (iii=1; iii<=feat[i].text_count; iii++)
              {
               
/*
EXEC SQL FETCH NR3 INTO :text_x      ,
                                       :text_y      ,
                                       :text_size   ,
                                       :text_angle  ,
                                       :text_just   ,
                                       :text_font   ,
                                       :textstring   ;
*/

{
#line 4281 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 4281 "geoIMS_main.sqc"
  sqlaaloc(3,7,29,0L);
    {
      struct sqla_setdata_list sql_setdlist[7];
#line 4281 "geoIMS_main.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 4281 "geoIMS_main.sqc"
      sql_setdlist[0].sqldata = (void*)&text_x;
#line 4281 "geoIMS_main.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 4281 "geoIMS_main.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 4281 "geoIMS_main.sqc"
      sql_setdlist[1].sqldata = (void*)&text_y;
#line 4281 "geoIMS_main.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 4281 "geoIMS_main.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 4281 "geoIMS_main.sqc"
      sql_setdlist[2].sqldata = (void*)&text_size;
#line 4281 "geoIMS_main.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 4281 "geoIMS_main.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 4281 "geoIMS_main.sqc"
      sql_setdlist[3].sqldata = (void*)&text_angle;
#line 4281 "geoIMS_main.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 4281 "geoIMS_main.sqc"
      sql_setdlist[4].sqltype = 500; sql_setdlist[4].sqllen = 2;
#line 4281 "geoIMS_main.sqc"
      sql_setdlist[4].sqldata = (void*)&text_just;
#line 4281 "geoIMS_main.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 4281 "geoIMS_main.sqc"
      sql_setdlist[5].sqltype = 500; sql_setdlist[5].sqllen = 2;
#line 4281 "geoIMS_main.sqc"
      sql_setdlist[5].sqldata = (void*)&text_font;
#line 4281 "geoIMS_main.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 4281 "geoIMS_main.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 51;
#line 4281 "geoIMS_main.sqc"
      sql_setdlist[6].sqldata = (void*)textstring;
#line 4281 "geoIMS_main.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 4281 "geoIMS_main.sqc"
      sqlasetdata(3,0,7,sql_setdlist,0L,0L);
    }
#line 4281 "geoIMS_main.sqc"
  sqlacall((unsigned short)25,11,0,3,0L);
#line 4281 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 4281 "geoIMS_main.sqc"

               if (SQLCODE == 0)
                  {
                   text[feat[i].text+iii].x     = text_x     ;
                   text[feat[i].text+iii].y     = text_y     ;
                   text[feat[i].text+iii].size  = text_size  ;
                   text[feat[i].text+iii].angle = text_angle ;
                   text[feat[i].text+iii].just  = text_just  ;
                   text[feat[i].text+iii].font  = text_font  ;
                   strcpy(text[feat[i].text+iii].string,textstring);
                   // printf("text[%d] %s \n",feat[i].num, text[feat[i].text+iii].string);
                  }
                else
                  {
                   break ;
                  }
              }

          text_index = text_index + feat[i].text_count ;
          
/*
EXEC SQL CLOSE NR3 ;
*/

{
#line 4300 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 4300 "geoIMS_main.sqc"
  sqlacall((unsigned short)20,11,0,0,0L);
#line 4300 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 4300 "geoIMS_main.sqc"
     /* CHECKERR ("CLOSE CURSOR"); */
         }

/*
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
*/

     }  /* End of Ret. LOOP */


 feat_count = i          ;
 xy_LAST    = xy_index   ;
 text_LAST  = text_index ;

 db_opened[0] = 'Y' ;
 update_layer()     ;
 display_scale()    ;
 // zoom_all("test.png")           ;
 // normal_cursor()    ;

 sprintf (Message, "geoIMS  [ Database : %s ]",db_name);
 XtVaSetValues( toplevel, XmNtitle, Message, NULL ) ;

 xstr = XmStringCreate(" INFO : Function Completed ",CS);
 XtSetArg(args[0], XmNlabelString , xstr);
 XtSetValues(output_label,args,1);

/* ORIGINAL
 sprintf (Message," INFO : Function Completed, [ Feature Count : %d ]",feat_count);
 xstr = XmStringCreate(Message,CS);
 XtSetArg(args[0], XmNlabelString , xstr);
 XtSetValues(output_label,args,1);
*/
}
/*------------------------------------------------------------------------*/
/*                              savedbCB()                                */
/*------------------------------------------------------------------------*/
void savedbCB()
{
 activateMenubar = 1 ;
 // wait_cursor();

 if ( db_opened[0] == 'Y' )
    {
     xstr  = XmStringCreate("Save workspace into DB Confirmation",CS);
     xstr1 = XmStringCreate("Are you sure ",CS);

     n=0;
     XtSetArg(args[n] , XmNdialogTitle   ,        xstr);n++;
     XtSetArg(args[n] , XmNmessageString ,       xstr1);n++;
     XtSetArg(args[n] , XmNwidth         ,         300);n++;
     XtSetArg(args[n] , XmNheight        ,         130);n++;
     XtSetArg(args[n] , XmNborderColor   , white.pixel);n++;
     XtSetArg(args[n] , XmNforeground    , black.pixel);n++;
     XtSetArg(args[n] , XmNbackground    , lgray.pixel);n++;

     PD = XmCreateQuestionDialog(MainForm,"PD",args,n);
     XtAddCallback(PD,XmNokCallback,saveOkCB,MainForm);
     XtAddCallback(PD,XmNcancelCallback,saveCancelCB,MainForm);
     XtManageChild(PD);

     /* keep the user on this dialog until it is accepted or canceled */
     XtAddGrab( PD,True,False );
    }
 else
 if ( db_opened[0] == 'N' )
    {
     strcpy(STR_PARM,"CON");          // get_db_name("ALL");    AIX
     get_db_name(MainForm);
    }

}
/*------------------------------------------------------------------------*/
/*                          saveCancelCB()                                */
/*------------------------------------------------------------------------*/
void saveCancelCB()
{
 // normal_cursor();
}
/*------------------------------------------------------------------------*/
/*                              saveOkCB()                                */
/*------------------------------------------------------------------------*/
void saveOkCB()
{

 if ( db_opened[0] == 'N' )
    {
     strcpy ( db_name , DB_name ) ;

     printf("INFO  : Connecting to Database [ %s ] ..\n",db_name);
     
/*
EXEC SQL CONNECT TO :db_name   ;
*/

{
#line 4406 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 4406 "geoIMS_main.sqc"
  sqlaaloc(2,1,30,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 4406 "geoIMS_main.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 31;
#line 4406 "geoIMS_main.sqc"
      sql_setdlist[0].sqldata = (void*)db_name;
#line 4406 "geoIMS_main.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 4406 "geoIMS_main.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 4406 "geoIMS_main.sqc"
  sqlacall((unsigned short)29,4,2,0,0L);
#line 4406 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 4406 "geoIMS_main.sqc"
  /* CHECKERR ("CONNECT TO geoinfo"); */

     if ( SQLCODE == -1013  || SQLCODE == -1001 || strcmp(db_name,"") == 0 )
        {
         sprintf (Message, "'%s', Database not found" ,db_name);
         xstr  = XmStringCreate("ERROR",CS);
         xstr1 = XmStringCreate(Message,CS);
         n=0;
         XtSetArg(args[n] , XmNdialogTitle   ,        xstr);n++;
         XtSetArg(args[n] , XmNmessageString ,       xstr1);n++;
         XtSetArg(args[n] , XmNwidth         ,         300);n++;
         XtSetArg(args[n] , XmNheight        ,         130);n++;
         XtSetArg(args[n] , XmNborderColor   , white.pixel);n++;
         XtSetArg(args[n] , XmNforeground    , black.pixel);n++;
         XtSetArg(args[n] , XmNbackground    , lgray.pixel);n++;
         PD = XmCreateErrorDialog(MainForm,"PD",args,n);
         XtManageChild(PD);

         // normal_cursor();
         return ;
        }

     if ( SQLCODE == -1032 )
        {
         xstr  = XmStringCreate("ERROR",CS);
         xstr1 = XmStringCreate("Database Engine is not started",CS);
         n=0;
         XtSetArg(args[n] , XmNdialogTitle   ,        xstr);n++;
         XtSetArg(args[n] , XmNmessageString ,       xstr1);n++;
         XtSetArg(args[n] , XmNwidth         ,         300);n++;
         XtSetArg(args[n] , XmNheight        ,         130);n++;
         XtSetArg(args[n] , XmNborderColor   , white.pixel);n++;
         XtSetArg(args[n] , XmNforeground    , black.pixel);n++;
         XtSetArg(args[n] , XmNbackground    , lgray.pixel);n++;
         PD = XmCreateErrorDialog(MainForm,"PD",args,n);
         XtManageChild(PD);

         // normal_cursor();
         return ;
        }
    }


            // LAST_FEAT_NUM
            //  DBASE
 
/*
EXEC SQL SELECT MAX(FEAT_NUM)
          INTO   :feat_num
          FROM   FEATURES;
*/

{
#line 4453 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 4453 "geoIMS_main.sqc"
  sqlaaloc(3,1,31,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 4453 "geoIMS_main.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 4453 "geoIMS_main.sqc"
      sql_setdlist[0].sqldata = (void*)&feat_num;
#line 4453 "geoIMS_main.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 4453 "geoIMS_main.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 4453 "geoIMS_main.sqc"
  sqlacall((unsigned short)24,13,0,3,0L);
#line 4453 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 4453 "geoIMS_main.sqc"


 printf("INFO  : Save workspace into Database ...\n");

 for ( i=1; i<=feat_count ; i++ )
     {
      if ( feat[i].selectble[0] == 'I' )  // Feature are imported inf/infb/dxf OR Added with no db_connection
         {
          feat_num++ ;
          feat[i].selectble[0] = 'Y' ;

          feat[i].num   = feat_num                 ;
          strcpy (feat_code,feat[i].code)          ;
          type          = feat[i].type             ;
          layer         = feat[i].layer            ;
          network       = feat[i].network          ;

          scale_range[0]= feat[i].scale_range[0]   ;
          scale_range[1]= feat[i].scale_range[1]   ;
          scale_range[2]= feat[i].scale_range[2]   ;
          scale_range[3]= feat[i].scale_range[3]   ;
          scale_range[4]= feat[i].scale_range[4]   ;
          displayed  [0]= feat[i].displayed  [0]   ;
          selectable [0]= feat[i].selectble  [0]   ;
          has_attrib [0]= feat[i].has_attrib [0]   ;
          has_text   [0]= feat[i].has_text   [0]   ;
          feat_linetype = feat[i].linetype         ;
          feat_linewidth= feat[i].linewidth        ;

          x_min_feat    = feat[i].xmin             ;
          y_min_feat    = feat[i].ymin             ;
          x_max_feat    = feat[i].xmax             ;
          y_max_feat    = feat[i].ymax             ;
          x_base        = feat[i].xbase            ;
          y_base        = feat[i].ybase            ;
          x_end         = feat[i].xend             ;
          y_end         = feat[i].yend             ;
          xy_count      = feat[i].xy_count         ;
          text_count    = feat[i].text_count       ;

               if (feat[i].color == blue.pixel  )  feat_color = 1  ;
          else if (feat[i].color == red.pixel   )  feat_color = 2  ;
          else if (feat[i].color == pink.pixel  )  feat_color = 3  ;
          else if (feat[i].color == green.pixel )  feat_color = 4  ;
          else if (feat[i].color == cyan.pixel  )  feat_color = 5  ;
          else if (feat[i].color == yellow.pixel)  feat_color = 6  ;
          else if (feat[i].color == white.pixel )  feat_color = 7  ;
          else if (feat[i].color == black.pixel )  feat_color = 8  ;
          else if (feat[i].color == gray.pixel  )  feat_color = 9  ;
          else if (feat[i].color == wheat.pixel )  feat_color = 10 ;
          else if (feat[i].color == brown.pixel )  feat_color = 11 ;
          else if (feat[i].color == orange.pixel)  feat_color = 12 ;


          if  ( feat[i].type == 1 )
              {
               symb_num   = feat[i].symb_num   ;
               symb_size  = feat[i].symb_size  ;
               symb_angle = feat[i].symb_angle ;
              }


          
/*
EXEC SQL INSERT INTO geoinfo.features
                    VALUES (:feat_num       ,
                            :feat_code      ,
                            :type           ,
                            :layer          ,
                            :network        ,
                            :scale_range    ,
                            :displayed      ,
                            :selectable     ,
                            :has_attrib     ,
                            :has_text       ,
                            :feat_color     ,
                            :feat_linetype  ,
                            :feat_linewidth ,
                            :x_min_feat     ,
                            :y_min_feat     ,
                            :x_max_feat     ,
                            :y_max_feat     ,
                            :x_base         ,
                            :y_base         ,
                            :x_end          ,
                            :y_end          ,
                            :xy_count       ,
                            :symb_num       ,
                            :symb_size      ,
                            :symb_angle     ,
                            :text_count );
*/

{
#line 4541 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 4541 "geoIMS_main.sqc"
  sqlaaloc(2,26,32,0L);
    {
      struct sqla_setdata_list sql_setdlist[26];
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[0].sqldata = (void*)&feat_num;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 13;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[1].sqldata = (void*)feat_code;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[2].sqldata = (void*)&type;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[3].sqldata = (void*)&layer;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[4].sqldata = (void*)&network;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 6;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[5].sqldata = (void*)scale_range;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 1;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[6].sqldata = (void*)displayed;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 1;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[7].sqldata = (void*)selectable;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 1;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[8].sqldata = (void*)has_attrib;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 1;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[9].sqldata = (void*)has_text;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[10].sqltype = 500; sql_setdlist[10].sqllen = 2;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[10].sqldata = (void*)&feat_color;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[11].sqltype = 500; sql_setdlist[11].sqllen = 2;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[11].sqldata = (void*)&feat_linetype;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[12].sqltype = 500; sql_setdlist[12].sqllen = 2;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[12].sqldata = (void*)&feat_linewidth;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[13].sqltype = 496; sql_setdlist[13].sqllen = 4;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[13].sqldata = (void*)&x_min_feat;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[14].sqltype = 496; sql_setdlist[14].sqllen = 4;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[14].sqldata = (void*)&y_min_feat;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[15].sqltype = 496; sql_setdlist[15].sqllen = 4;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[15].sqldata = (void*)&x_max_feat;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[16].sqltype = 496; sql_setdlist[16].sqllen = 4;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[16].sqldata = (void*)&y_max_feat;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[17].sqltype = 496; sql_setdlist[17].sqllen = 4;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[17].sqldata = (void*)&x_base;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[18].sqltype = 496; sql_setdlist[18].sqllen = 4;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[18].sqldata = (void*)&y_base;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[19].sqltype = 496; sql_setdlist[19].sqllen = 4;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[19].sqldata = (void*)&x_end;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[20].sqltype = 496; sql_setdlist[20].sqllen = 4;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[20].sqldata = (void*)&y_end;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[21].sqltype = 496; sql_setdlist[21].sqllen = 4;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[21].sqldata = (void*)&xy_count;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[22].sqltype = 496; sql_setdlist[22].sqllen = 4;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[22].sqldata = (void*)&symb_num;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[23].sqltype = 496; sql_setdlist[23].sqllen = 4;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[23].sqldata = (void*)&symb_size;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[24].sqltype = 496; sql_setdlist[24].sqllen = 4;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[24].sqldata = (void*)&symb_angle;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[25].sqltype = 496; sql_setdlist[25].sqllen = 4;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[25].sqldata = (void*)&text_count;
#line 4541 "geoIMS_main.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 4541 "geoIMS_main.sqc"
      sqlasetdata(2,0,26,sql_setdlist,0L,0L);
    }
#line 4541 "geoIMS_main.sqc"
  sqlacall((unsigned short)24,14,2,0,0L);
#line 4541 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 4541 "geoIMS_main.sqc"


          // CHECKERR ("INSERT INTO");


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
#line 4581 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 4581 "geoIMS_main.sqc"
  sqlaaloc(2,22,33,0L);
    {
      struct sqla_setdata_list sql_setdlist[22];
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[0].sqldata = (void*)&feat_num;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[1].sqldata = (void*)&seq;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[2].sqldata = (void*)&x_1;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[3].sqldata = (void*)&y_1;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[4].sqldata = (void*)&x_2;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[5].sqltype = 496; sql_setdlist[5].sqllen = 4;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[5].sqldata = (void*)&y_2;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[6].sqldata = (void*)&x_3;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[7].sqltype = 496; sql_setdlist[7].sqllen = 4;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[7].sqldata = (void*)&y_3;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[8].sqltype = 496; sql_setdlist[8].sqllen = 4;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[8].sqldata = (void*)&x_4;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[9].sqltype = 496; sql_setdlist[9].sqllen = 4;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[9].sqldata = (void*)&y_4;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[10].sqltype = 496; sql_setdlist[10].sqllen = 4;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[10].sqldata = (void*)&x_5;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[11].sqltype = 496; sql_setdlist[11].sqllen = 4;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[11].sqldata = (void*)&y_5;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[12].sqltype = 496; sql_setdlist[12].sqllen = 4;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[12].sqldata = (void*)&x_6;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[13].sqltype = 496; sql_setdlist[13].sqllen = 4;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[13].sqldata = (void*)&y_6;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[14].sqltype = 496; sql_setdlist[14].sqllen = 4;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[14].sqldata = (void*)&x_7;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[15].sqltype = 496; sql_setdlist[15].sqllen = 4;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[15].sqldata = (void*)&y_7;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[16].sqltype = 496; sql_setdlist[16].sqllen = 4;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[16].sqldata = (void*)&x_8;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[17].sqltype = 496; sql_setdlist[17].sqllen = 4;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[17].sqldata = (void*)&y_8;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[18].sqltype = 496; sql_setdlist[18].sqllen = 4;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[18].sqldata = (void*)&x_9;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[19].sqltype = 496; sql_setdlist[19].sqllen = 4;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[19].sqldata = (void*)&y_9;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[20].sqltype = 496; sql_setdlist[20].sqllen = 4;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[20].sqldata = (void*)&x_10;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[21].sqltype = 496; sql_setdlist[21].sqllen = 4;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[21].sqldata = (void*)&y_10;
#line 4581 "geoIMS_main.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 4581 "geoIMS_main.sqc"
      sqlasetdata(2,0,22,sql_setdlist,0L,0L);
    }
#line 4581 "geoIMS_main.sqc"
  sqlacall((unsigned short)24,15,2,0,0L);
#line 4581 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 4581 "geoIMS_main.sqc"


                // CHECKERR ("INSERT INTO");
               }
         }


      if  ( feat[i].has_text[0] == 'Y' )
          {
           for ( ii=1 ; ii<=feat[i].text_count ; ii++ )
               {
                text_x      = text[feat[i].text+ii].x              ;
                text_y      = text[feat[i].text+ii].y              ;
                text_size   = text[feat[i].text+ii].size           ;
                text_angle  = text[feat[i].text+ii].angle          ;
                text_just   = text[feat[i].text+ii].just           ;
                text_font   = text[feat[i].text+ii].font           ;
                strcpy(textstring,text[feat[i].text+ii].string) ;

                
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
#line 4608 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 4608 "geoIMS_main.sqc"
  sqlaaloc(2,8,34,0L);
    {
      struct sqla_setdata_list sql_setdlist[8];
#line 4608 "geoIMS_main.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 4608 "geoIMS_main.sqc"
      sql_setdlist[0].sqldata = (void*)&feat_num;
#line 4608 "geoIMS_main.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 4608 "geoIMS_main.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 4608 "geoIMS_main.sqc"
      sql_setdlist[1].sqldata = (void*)&text_x;
#line 4608 "geoIMS_main.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 4608 "geoIMS_main.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 4608 "geoIMS_main.sqc"
      sql_setdlist[2].sqldata = (void*)&text_y;
#line 4608 "geoIMS_main.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 4608 "geoIMS_main.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 4608 "geoIMS_main.sqc"
      sql_setdlist[3].sqldata = (void*)&text_size;
#line 4608 "geoIMS_main.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 4608 "geoIMS_main.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 4608 "geoIMS_main.sqc"
      sql_setdlist[4].sqldata = (void*)&text_angle;
#line 4608 "geoIMS_main.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 4608 "geoIMS_main.sqc"
      sql_setdlist[5].sqltype = 500; sql_setdlist[5].sqllen = 2;
#line 4608 "geoIMS_main.sqc"
      sql_setdlist[5].sqldata = (void*)&text_just;
#line 4608 "geoIMS_main.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 4608 "geoIMS_main.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 4608 "geoIMS_main.sqc"
      sql_setdlist[6].sqldata = (void*)&text_font;
#line 4608 "geoIMS_main.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 4608 "geoIMS_main.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 51;
#line 4608 "geoIMS_main.sqc"
      sql_setdlist[7].sqldata = (void*)textstring;
#line 4608 "geoIMS_main.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 4608 "geoIMS_main.sqc"
      sqlasetdata(2,0,8,sql_setdlist,0L,0L);
    }
#line 4608 "geoIMS_main.sqc"
  sqlacall((unsigned short)24,16,2,0,0L);
#line 4608 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 4608 "geoIMS_main.sqc"


                // CHECKERR ("INSERT INTO");
              }
         }


   /* if ( __s trcmp(feat[i].code ,"DISTSTN") == 0 )
         {
          strcmp  (status ,"IS") ;
          sprintf (subid,"C %d",feat_num );
          kva = 1000 ;

          EXEC SQL INSERT INTO geoinfo.diststn
                   VALUES (:feat_num ,
                           :status   ,
                           :subid    ,
                           :fdrnum   ,
                           :subtype  ,
                           :kva        );

          // CHECKERR ("INSERT INTO");
         }
    */

       } /* end if */

     } /* main loop */


 
/*
EXEC SQL UPDATE DBASE
          SET    LAST_FEAT_NUM = :feat_num
          WHERE  DB_NAME       = :db_name ;
*/

{
#line 4640 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 4640 "geoIMS_main.sqc"
  sqlaaloc(2,2,35,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 4640 "geoIMS_main.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 4640 "geoIMS_main.sqc"
      sql_setdlist[0].sqldata = (void*)&feat_num;
#line 4640 "geoIMS_main.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 4640 "geoIMS_main.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 31;
#line 4640 "geoIMS_main.sqc"
      sql_setdlist[1].sqldata = (void*)db_name;
#line 4640 "geoIMS_main.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 4640 "geoIMS_main.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 4640 "geoIMS_main.sqc"
  sqlacall((unsigned short)24,17,2,0,0L);
#line 4640 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 4640 "geoIMS_main.sqc"


 
/*
EXEC SQL COMMIT WORK ;
*/

{
#line 4642 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 4642 "geoIMS_main.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 4642 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 4642 "geoIMS_main.sqc"


 // normal_cursor();

 sprintf (Message, "geoIMS  [ Database : %s ]",db_name);
 XtVaSetValues( toplevel, XmNtitle, Message, NULL ) ;

 xstr = XmStringCreate(" INFO : Save workspace into Database Function Completed",CS);
 XtSetArg(args[0], XmNlabelString ,  xstr);
 XtSetValues(output_label,args,1);
}
/*------------------------------------------------------------------------*/
/*                             createdbCB()                               */
/*------------------------------------------------------------------------*/
void createdbCB()
{
 activateMenubar = 1 ;
 // wait_cursor();


 system ("geoDBcreate xx");

 system ("geoDBbind   xx");


 // normal_cursor();

 sprintf (Message, "geoIMS  [ Database : %s ]",db_name);
 XtVaSetValues( toplevel, XmNtitle, Message, NULL ) ;

 xstr = XmStringCreate(" INFO : Database created successfully",CS);
 XtSetArg(args[0], XmNlabelString ,  xstr);
 XtSetValues(output_label,args,1);
}
/*------------------------------------------------------------------------*/
/*                              dropdbCB()                                */
/*------------------------------------------------------------------------*/
void dropdbCB()
{
 activateMenubar = 1 ;
 // wait_cursor();


 system("db2 drop database xx");


 // normal_cursor();

 sprintf (Message, "geoIMS  [ Database : %s ]",db_name);
 XtVaSetValues( toplevel, XmNtitle, Message, NULL ) ;

 xstr = XmStringCreate(" INFO : Database created successfully",CS);
 XtSetArg(args[0], XmNlabelString ,  xstr);
 XtSetValues(output_label,args,1);
}
/*------------------------------------------------------------------------*/
/*                           insert_feature()                             */
/*------------------------------------------------------------------------*/
void insert_feature(long arrary_index)
{

 printf("INFO  : Insert Feature into Database ...\n");


 // For New DB which have no Features
 feat_num = 0 ;

 // Get Last_Feat_Num from DBASE
 
/*
EXEC SQL SELECT MAX(FEAT_NUM)
          INTO   :feat_num
          FROM   FEATURES ;
*/

{
#line 4712 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 4712 "geoIMS_main.sqc"
  sqlaaloc(3,1,36,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 4712 "geoIMS_main.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 4712 "geoIMS_main.sqc"
      sql_setdlist[0].sqldata = (void*)&feat_num;
#line 4712 "geoIMS_main.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 4712 "geoIMS_main.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 4712 "geoIMS_main.sqc"
  sqlacall((unsigned short)24,18,0,3,0L);
#line 4712 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 4712 "geoIMS_main.sqc"


 feat_num++       ;
 i = arrary_index ;


 feat[i].num   = feat_num                 ;
 strcpy (feat_code,feat[i].code)          ;
 type          = feat[i].type             ;
 layer         = feat[i].layer            ;
 network       = feat[i].network          ;

 scale_range[0]= feat[i].scale_range[0]   ;
 scale_range[1]= feat[i].scale_range[1]   ;
 scale_range[2]= feat[i].scale_range[2]   ;
 scale_range[3]= feat[i].scale_range[3]   ;
 scale_range[4]= feat[i].scale_range[4]   ;
 displayed  [0]= feat[i].displayed  [0]   ;
 selectable [0]= feat[i].selectble  [0]   ;
 has_attrib [0]= feat[i].has_attrib [0]   ;
 has_text   [0]= feat[i].has_text   [0]   ;
 feat_linetype = feat[i].linetype         ;
 feat_linewidth= feat[i].linewidth        ;

 x_min_feat    = feat[i].xmin             ;
 y_min_feat    = feat[i].ymin             ;
 x_max_feat    = feat[i].xmax             ;
 y_max_feat    = feat[i].ymax             ;
 x_base        = feat[i].xbase            ;
 y_base        = feat[i].ybase            ;
 x_end         = feat[i].xend             ;
 y_end         = feat[i].yend             ;
 xy_count      = feat[i].xy_count         ;
 text_count    = feat[i].text_count       ;

       if (feat[i].color == blue.pixel  )  feat_color = 1  ;
  else if (feat[i].color == red.pixel   )  feat_color = 2  ;
  else if (feat[i].color == pink.pixel  )  feat_color = 3  ;
  else if (feat[i].color == green.pixel )  feat_color = 4  ;
  else if (feat[i].color == cyan.pixel  )  feat_color = 5  ;
  else if (feat[i].color == yellow.pixel)  feat_color = 6  ;
  else if (feat[i].color == white.pixel )  feat_color = 7  ;
  else if (feat[i].color == black.pixel )  feat_color = 8  ;
  else if (feat[i].color == gray.pixel  )  feat_color = 9  ;
  else if (feat[i].color == wheat.pixel )  feat_color = 10 ;
  else if (feat[i].color == brown.pixel )  feat_color = 11 ;
  else if (feat[i].color == orange.pixel)  feat_color = 12 ;
  else if (feat[i].color == lgray.pixel )  feat_color = 13 ;


  if  ( feat[i].type == 1 )
      {
       symb_num   = feat[i].symb_num   ;
       symb_size  = feat[i].symb_size  ;
       symb_angle = feat[i].symb_angle ;
      }


 
/*
EXEC SQL INSERT INTO geoinfo.features
          VALUES (:feat_num       ,
                  :feat_code      ,
                  :type           ,
                  :layer          ,
                  :network        ,
                  :scale_range    ,
                  :displayed      ,
                  :selectable     ,
                  :has_attrib     ,
                  :has_text       ,
                  :feat_color     ,
                  :feat_linetype  ,
                  :feat_linewidth ,
                  :x_min_feat     ,
                  :y_min_feat     ,
                  :x_max_feat     ,
                  :y_max_feat     ,
                  :x_base         ,
                  :y_base         ,
                  :x_end          ,
                  :y_end          ,
                  :xy_count       ,
                  :symb_num       ,
                  :symb_size      ,
                  :symb_angle     ,
                  :text_count );
*/

{
#line 4796 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 4796 "geoIMS_main.sqc"
  sqlaaloc(2,26,37,0L);
    {
      struct sqla_setdata_list sql_setdlist[26];
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[0].sqldata = (void*)&feat_num;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 13;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[1].sqldata = (void*)feat_code;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[2].sqldata = (void*)&type;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[3].sqldata = (void*)&layer;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[4].sqldata = (void*)&network;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 6;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[5].sqldata = (void*)scale_range;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 1;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[6].sqldata = (void*)displayed;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 1;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[7].sqldata = (void*)selectable;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 1;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[8].sqldata = (void*)has_attrib;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 1;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[9].sqldata = (void*)has_text;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[10].sqltype = 500; sql_setdlist[10].sqllen = 2;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[10].sqldata = (void*)&feat_color;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[11].sqltype = 500; sql_setdlist[11].sqllen = 2;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[11].sqldata = (void*)&feat_linetype;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[12].sqltype = 500; sql_setdlist[12].sqllen = 2;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[12].sqldata = (void*)&feat_linewidth;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[13].sqltype = 496; sql_setdlist[13].sqllen = 4;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[13].sqldata = (void*)&x_min_feat;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[14].sqltype = 496; sql_setdlist[14].sqllen = 4;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[14].sqldata = (void*)&y_min_feat;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[15].sqltype = 496; sql_setdlist[15].sqllen = 4;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[15].sqldata = (void*)&x_max_feat;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[16].sqltype = 496; sql_setdlist[16].sqllen = 4;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[16].sqldata = (void*)&y_max_feat;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[17].sqltype = 496; sql_setdlist[17].sqllen = 4;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[17].sqldata = (void*)&x_base;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[18].sqltype = 496; sql_setdlist[18].sqllen = 4;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[18].sqldata = (void*)&y_base;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[19].sqltype = 496; sql_setdlist[19].sqllen = 4;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[19].sqldata = (void*)&x_end;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[20].sqltype = 496; sql_setdlist[20].sqllen = 4;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[20].sqldata = (void*)&y_end;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[21].sqltype = 496; sql_setdlist[21].sqllen = 4;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[21].sqldata = (void*)&xy_count;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[22].sqltype = 496; sql_setdlist[22].sqllen = 4;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[22].sqldata = (void*)&symb_num;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[22].sqlind = 0L;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[23].sqltype = 496; sql_setdlist[23].sqllen = 4;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[23].sqldata = (void*)&symb_size;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[23].sqlind = 0L;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[24].sqltype = 496; sql_setdlist[24].sqllen = 4;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[24].sqldata = (void*)&symb_angle;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[24].sqlind = 0L;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[25].sqltype = 496; sql_setdlist[25].sqllen = 4;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[25].sqldata = (void*)&text_count;
#line 4796 "geoIMS_main.sqc"
      sql_setdlist[25].sqlind = 0L;
#line 4796 "geoIMS_main.sqc"
      sqlasetdata(2,0,26,sql_setdlist,0L,0L);
    }
#line 4796 "geoIMS_main.sqc"
  sqlacall((unsigned short)24,19,2,0,0L);
#line 4796 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 4796 "geoIMS_main.sqc"


 // CHECKERR ("INSERT INTO");


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
#line 4837 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 4837 "geoIMS_main.sqc"
  sqlaaloc(2,22,38,0L);
    {
      struct sqla_setdata_list sql_setdlist[22];
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[0].sqldata = (void*)&feat_num;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[1].sqldata = (void*)&seq;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[2].sqldata = (void*)&x_1;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[3].sqldata = (void*)&y_1;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[4].sqldata = (void*)&x_2;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[5].sqltype = 496; sql_setdlist[5].sqllen = 4;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[5].sqldata = (void*)&y_2;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[6].sqldata = (void*)&x_3;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[7].sqltype = 496; sql_setdlist[7].sqllen = 4;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[7].sqldata = (void*)&y_3;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[8].sqltype = 496; sql_setdlist[8].sqllen = 4;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[8].sqldata = (void*)&x_4;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[9].sqltype = 496; sql_setdlist[9].sqllen = 4;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[9].sqldata = (void*)&y_4;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[10].sqltype = 496; sql_setdlist[10].sqllen = 4;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[10].sqldata = (void*)&x_5;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[11].sqltype = 496; sql_setdlist[11].sqllen = 4;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[11].sqldata = (void*)&y_5;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[12].sqltype = 496; sql_setdlist[12].sqllen = 4;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[12].sqldata = (void*)&x_6;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[13].sqltype = 496; sql_setdlist[13].sqllen = 4;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[13].sqldata = (void*)&y_6;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[14].sqltype = 496; sql_setdlist[14].sqllen = 4;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[14].sqldata = (void*)&x_7;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[15].sqltype = 496; sql_setdlist[15].sqllen = 4;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[15].sqldata = (void*)&y_7;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[16].sqltype = 496; sql_setdlist[16].sqllen = 4;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[16].sqldata = (void*)&x_8;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[17].sqltype = 496; sql_setdlist[17].sqllen = 4;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[17].sqldata = (void*)&y_8;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[18].sqltype = 496; sql_setdlist[18].sqllen = 4;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[18].sqldata = (void*)&x_9;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[19].sqltype = 496; sql_setdlist[19].sqllen = 4;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[19].sqldata = (void*)&y_9;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[20].sqltype = 496; sql_setdlist[20].sqllen = 4;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[20].sqldata = (void*)&x_10;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[21].sqltype = 496; sql_setdlist[21].sqllen = 4;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[21].sqldata = (void*)&y_10;
#line 4837 "geoIMS_main.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 4837 "geoIMS_main.sqc"
      sqlasetdata(2,0,22,sql_setdlist,0L,0L);
    }
#line 4837 "geoIMS_main.sqc"
  sqlacall((unsigned short)24,20,2,0,0L);
#line 4837 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 4837 "geoIMS_main.sqc"


           // CHECKERR ("INSERT INTO");
          }
    }


 if ( feat[i].has_text[0] == 'Y' )
    {
     for ( ii=1 ; ii<=feat[i].text_count ; ii++ )
         {
          text_x      = text[feat[i].text+ii].x           ;
          text_y      = text[feat[i].text+ii].y           ;
          text_size   = text[feat[i].text+ii].size        ;
          text_angle  = text[feat[i].text+ii].angle       ;
          text_just   = text[feat[i].text+ii].just        ;
          text_font   = text[feat[i].text+ii].font        ;
          strcpy(textstring,text[feat[i].text+ii].string) ;

          
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
#line 4864 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 4864 "geoIMS_main.sqc"
  sqlaaloc(2,8,39,0L);
    {
      struct sqla_setdata_list sql_setdlist[8];
#line 4864 "geoIMS_main.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 4864 "geoIMS_main.sqc"
      sql_setdlist[0].sqldata = (void*)&feat_num;
#line 4864 "geoIMS_main.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 4864 "geoIMS_main.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 4864 "geoIMS_main.sqc"
      sql_setdlist[1].sqldata = (void*)&text_x;
#line 4864 "geoIMS_main.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 4864 "geoIMS_main.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 4864 "geoIMS_main.sqc"
      sql_setdlist[2].sqldata = (void*)&text_y;
#line 4864 "geoIMS_main.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 4864 "geoIMS_main.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 4864 "geoIMS_main.sqc"
      sql_setdlist[3].sqldata = (void*)&text_size;
#line 4864 "geoIMS_main.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 4864 "geoIMS_main.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 4864 "geoIMS_main.sqc"
      sql_setdlist[4].sqldata = (void*)&text_angle;
#line 4864 "geoIMS_main.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 4864 "geoIMS_main.sqc"
      sql_setdlist[5].sqltype = 500; sql_setdlist[5].sqllen = 2;
#line 4864 "geoIMS_main.sqc"
      sql_setdlist[5].sqldata = (void*)&text_just;
#line 4864 "geoIMS_main.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 4864 "geoIMS_main.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 4864 "geoIMS_main.sqc"
      sql_setdlist[6].sqldata = (void*)&text_font;
#line 4864 "geoIMS_main.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 4864 "geoIMS_main.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 51;
#line 4864 "geoIMS_main.sqc"
      sql_setdlist[7].sqldata = (void*)textstring;
#line 4864 "geoIMS_main.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 4864 "geoIMS_main.sqc"
      sqlasetdata(2,0,8,sql_setdlist,0L,0L);
    }
#line 4864 "geoIMS_main.sqc"
  sqlacall((unsigned short)24,21,2,0,0L);
#line 4864 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 4864 "geoIMS_main.sqc"


          // CHECKERR ("INSERT INTO");
         }
    }


 
/*
EXEC SQL UPDATE DBASE
          SET    LAST_FEAT_NUM = :feat_num
          WHERE  DB_NAME       = :db_name ;
*/

{
#line 4873 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 4873 "geoIMS_main.sqc"
  sqlaaloc(2,2,40,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 4873 "geoIMS_main.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 4873 "geoIMS_main.sqc"
      sql_setdlist[0].sqldata = (void*)&feat_num;
#line 4873 "geoIMS_main.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 4873 "geoIMS_main.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 31;
#line 4873 "geoIMS_main.sqc"
      sql_setdlist[1].sqldata = (void*)db_name;
#line 4873 "geoIMS_main.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 4873 "geoIMS_main.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 4873 "geoIMS_main.sqc"
  sqlacall((unsigned short)24,22,2,0,0L);
#line 4873 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 4873 "geoIMS_main.sqc"


 
/*
EXEC SQL COMMIT WORK ;
*/

{
#line 4875 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 4875 "geoIMS_main.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 4875 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 4875 "geoIMS_main.sqc"



 
/*
EXEC SQL INSERT INTO geoinfo.node
          VALUES (:feat_num ,
                  :node1   );
*/

{
#line 4880 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 4880 "geoIMS_main.sqc"
  sqlaaloc(2,2,41,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 4880 "geoIMS_main.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 4880 "geoIMS_main.sqc"
      sql_setdlist[0].sqldata = (void*)&feat_num;
#line 4880 "geoIMS_main.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 4880 "geoIMS_main.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 4880 "geoIMS_main.sqc"
      sql_setdlist[1].sqldata = (void*)&node1;
#line 4880 "geoIMS_main.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 4880 "geoIMS_main.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 4880 "geoIMS_main.sqc"
  sqlacall((unsigned short)24,23,2,0,0L);
#line 4880 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 4880 "geoIMS_main.sqc"


 // CHECKERR ("INSERT INTO");
 
/*
EXEC SQL COMMIT WORK ;
*/

{
#line 4883 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 4883 "geoIMS_main.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 4883 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 4883 "geoIMS_main.sqc"


}
/*------------------------------------------------------------------------*/
/*                           insert_text()                                */
/*------------------------------------------------------------------------*/
void insert_text(long arrary_index)
{

 printf("INFO  : Insert Text into Database ...\n");


 i = arrary_index ;

 feat_num    = feat[i].num         ;
 has_text[0] = feat[i].has_text[0] ;
 text_count  = feat[i].text_count  ;


 
/*
EXEC SQL UPDATE  FEATURES
          SET     HAS_TEXT   = :has_text  ,
                  TEXT_COUNT = :text_count
          WHERE   FEAT_NUM   = :feat_num  ;
*/

{
#line 4905 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 4905 "geoIMS_main.sqc"
  sqlaaloc(2,3,42,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 4905 "geoIMS_main.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 1;
#line 4905 "geoIMS_main.sqc"
      sql_setdlist[0].sqldata = (void*)has_text;
#line 4905 "geoIMS_main.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 4905 "geoIMS_main.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 4905 "geoIMS_main.sqc"
      sql_setdlist[1].sqldata = (void*)&text_count;
#line 4905 "geoIMS_main.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 4905 "geoIMS_main.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 4905 "geoIMS_main.sqc"
      sql_setdlist[2].sqldata = (void*)&feat_num;
#line 4905 "geoIMS_main.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 4905 "geoIMS_main.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 4905 "geoIMS_main.sqc"
  sqlacall((unsigned short)24,24,2,0,0L);
#line 4905 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 4905 "geoIMS_main.sqc"


 // CHECKERR ("UPDATE");


 if ( feat[i].has_text[0] == 'Y' )
    {
     for ( ii=1 ; ii<=feat[i].text_count ; ii++ )
         {
          text_x      = text[feat[i].text+ii].x           ;
          text_y      = text[feat[i].text+ii].y           ;
          text_size   = text[feat[i].text+ii].size        ;
          text_angle  = text[feat[i].text+ii].angle       ;
          text_just   = text[feat[i].text+ii].just        ;
          text_font   = text[feat[i].text+ii].font        ;
          strcpy(textstring,text[feat[i].text+ii].string) ;

          
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
#line 4930 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 4930 "geoIMS_main.sqc"
  sqlaaloc(2,8,43,0L);
    {
      struct sqla_setdata_list sql_setdlist[8];
#line 4930 "geoIMS_main.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 4930 "geoIMS_main.sqc"
      sql_setdlist[0].sqldata = (void*)&feat_num;
#line 4930 "geoIMS_main.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 4930 "geoIMS_main.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 4930 "geoIMS_main.sqc"
      sql_setdlist[1].sqldata = (void*)&text_x;
#line 4930 "geoIMS_main.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 4930 "geoIMS_main.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 4930 "geoIMS_main.sqc"
      sql_setdlist[2].sqldata = (void*)&text_y;
#line 4930 "geoIMS_main.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 4930 "geoIMS_main.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 4930 "geoIMS_main.sqc"
      sql_setdlist[3].sqldata = (void*)&text_size;
#line 4930 "geoIMS_main.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 4930 "geoIMS_main.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 4930 "geoIMS_main.sqc"
      sql_setdlist[4].sqldata = (void*)&text_angle;
#line 4930 "geoIMS_main.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 4930 "geoIMS_main.sqc"
      sql_setdlist[5].sqltype = 500; sql_setdlist[5].sqllen = 2;
#line 4930 "geoIMS_main.sqc"
      sql_setdlist[5].sqldata = (void*)&text_just;
#line 4930 "geoIMS_main.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 4930 "geoIMS_main.sqc"
      sql_setdlist[6].sqltype = 500; sql_setdlist[6].sqllen = 2;
#line 4930 "geoIMS_main.sqc"
      sql_setdlist[6].sqldata = (void*)&text_font;
#line 4930 "geoIMS_main.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 4930 "geoIMS_main.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 51;
#line 4930 "geoIMS_main.sqc"
      sql_setdlist[7].sqldata = (void*)textstring;
#line 4930 "geoIMS_main.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 4930 "geoIMS_main.sqc"
      sqlasetdata(2,0,8,sql_setdlist,0L,0L);
    }
#line 4930 "geoIMS_main.sqc"
  sqlacall((unsigned short)24,25,2,0,0L);
#line 4930 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 4930 "geoIMS_main.sqc"

          // CHECKERR ("INSERT INTO");
          /*
          printf("i          %d     \n",i          );
          printf("feat_num   %d     \n",feat_num   );
          printf("text_x     %d     \n",text_x     );
          printf("text_y     %d     \n",text_y     );
          printf("text_size  %d     \n",text_size  );
          printf("text_angle %d     \n",text_angle );
          printf("text_just  %d     \n",text_just  );
          printf("text_font  %d     \n",text_font  );
          printf("text_string [%s]  \n",textstring );
          */
         }
    }


 
/*
EXEC SQL COMMIT WORK ;
*/

{
#line 4947 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 4947 "geoIMS_main.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 4947 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 4947 "geoIMS_main.sqc"

}
/*------------------------------------------------------------------------*/
/*                              infinbCB()                                */
/*------------------------------------------------------------------------*/
void infinbCB()
{
 fp_i = fopen (sys.data_file,"rb");
 if  ( fp_i == NULL )
     {
      fprintf(stderr,"ERROR : Can't open input file [%s] !\n",sys.data_file);
      return ;
     }
 else
     {
      fprintf (stdout,"INFO  : Processing input file ..\n");
     }

 fread (&DB_UNIT_NAME , sizeof(DB_UNIT_NAME) , 1 , fp_i);
 fread (&x_min        , sizeof(x_min)        , 1 , fp_i);
 fread (&y_min        , sizeof(y_min)        , 1 , fp_i);
 fread (&x_max        , sizeof(x_max)        , 1 , fp_i);
 fread (&y_max        , sizeof(y_max)        , 1 , fp_i);

      if ( strcmp(DB_UNIT_NAME,"MM") == 0 ) DB_UNIT = 1 ;
 else if ( strcmp(DB_UNIT_NAME,"CM") == 0 ) DB_UNIT = 2 ;
 else if ( strcmp(DB_UNIT_NAME,"DM") == 0 ) DB_UNIT = 3 ;
 else if ( strcmp(DB_UNIT_NAME,"M" ) == 0 ) DB_UNIT = 4 ;
 else if ( strcmp(DB_UNIT_NAME,"KM") == 0 ) DB_UNIT = 5 ;

 /*
 Used for workspace Load
 i = 0 ; xy_index = 0 ; text_index = 0 ;
 */

 i          = feat_count ;   /* Used for workspace Merege */
 xy_index   = xy_LAST    ;
 text_index = text_LAST  ;


 while( fread (&feat[++i],sizeof(feat[i]),1,fp_i) == 1 )
      {
       feat[i].selectble[0] = 'I' ;    // I for Imported Record

       if ( feat[i].xy_count > 0 )
          {
           feat[i].xy = xy_index ;
           for ( ii=1 ; ii<=feat[i].xy_count ; ii++ )
               {
                fread (&x[xy_index+ii],sizeof(&x[0]),1,fp_i);
                fread (&y[xy_index+ii],sizeof(&y[0]),1,fp_i);
               }
           xy_index = xy_index + feat[i].xy_count ;
          }

       if ( feat[i].has_text[0] == 'Y' )
          {
           feat[i].text = text_index ;
           for ( ii=1 ; ii<=feat[i].text_count ; ii++ )
               {
                fread (&text[feat[i].text+ii],sizeof(text[0]),1,fp_i);
               }
           text_index = text_index + feat[i].text_count ;
          }

      } /* main loop */

 fclose(fp_i);

 feat_count = i - 1      ;
 xy_LAST    = xy_index   ;
 text_LAST  = text_index ;

 update_layer();

 fprintf (stdout,"INFO  : Feature Count    = [%d]\n",feat_count);
 fprintf (stdout,"INFO  : LAST xy Index    = [%d]\n",xy_LAST   );
 fprintf (stdout,"INFO  : LAST text Index  = [%d]\n",text_LAST );
 fprintf (stdout,"INFO  : Import Binary file [%s] Completed\n\n",sys.data_file);
}
/*------------------------------------------------------------------------*/
/*                              infoutbCB()                               */
/*------------------------------------------------------------------------*/
void infoutbCB()
{
 activateMenubar = 1 ;
 // wait_cursor()       ;
 move_fun = NONE     ;

 xstr  = XmStringCreate("Output file name",CS);
 xstr1 = XmStringCreate("aa",CS);
 n=0;
 XtSetArg(args[n] , XmNdialogTitle ,        xstr);n++;
 XtSetArg(args[n] , XmNtitle       ,       xstr1);n++;
 XtSetArg(args[n] , XmNwidth       ,         300);n++;
 XtSetArg(args[n] , XmNheight      ,         130);n++;
 XtSetArg(args[n] , XmNborderColor , white.pixel);n++;
 XtSetArg(args[n] , XmNforeground  , black.pixel);n++;
 XtSetArg(args[n] , XmNbackground  , lgray.pixel);n++;

 PD = XmCreatePromptDialog(MainForm,"PD",args,n);
 XtAddCallback(PD,XmNokCallback,infoutbOKCB,MainForm);
 XtAddCallback(PD,XmNcancelCallback,infoutbCancelCB,MainForm);
 XtManageChild(PD);

 /* keep the user on this dialog until it is accepted or canceled */
 XtAddGrab( PD,True,False );
}
/*------------------------------------------------------------------------*/
/*                             infoutbOKCB()                              */
/*------------------------------------------------------------------------*/
void infoutbOKCB(Widget w, caddr_t client_data, FSBCBS *call_data)
{
 int   xcolor ;
 char  *str   ;

 XmStringGetLtoR(call_data->value ,CS ,&str);
 strcpy(OutputFile,str);
 strcat(OutputFile,".infb");

 fp_o = fopen (OutputFile,"wb");

 if  ( fp_o == NULL )
     {
      fprintf (stderr,"ERROR : Can't open output file  !\n");
      // normal_cursor();
      return ;
     }

 printf ("INFO  : Processing output file ..\n");

      if ( DB_UNIT == 1 ) strcpy (DB_UNIT_NAME , "MM") ;
 else if ( DB_UNIT == 2 ) strcpy (DB_UNIT_NAME , "CM") ;
 else if ( DB_UNIT == 3 ) strcpy (DB_UNIT_NAME , "DM") ;
 else if ( DB_UNIT == 4 ) strcpy (DB_UNIT_NAME , "M" ) ;
 else if ( DB_UNIT == 5 ) strcpy (DB_UNIT_NAME , "KM") ;


 fwrite (&DB_UNIT_NAME , sizeof(DB_UNIT_NAME) , 1 , fp_o) ;
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
      else       /* default color */         { xcolor=white.pixel ; feat[i].color = 7  ;}

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

 fclose(fp_o);
 // normal_cursor();

 xstr = XmStringCreate(" INFO : Export Binary inf Function Completed",CS);
 XtSetArg(args[0], XmNlabelString ,  xstr);
 XtSetValues(output_label,args,1);
}
/*------------------------------------------------------------------------*/
/*                        infoubCancelCB()                                */
/*------------------------------------------------------------------------*/
void infoutbCancelCB(Widget w, caddr_t client_data, FSBCBS *call_data)
{
 // normal_cursor();
}
/*------------------------------------------------------------------------*/
/*                              infinaCB()                                */
/*------------------------------------------------------------------------*/
void infinaCB()
{

 fp_i = fopen (sys.data_file,"rt");
 if  ( fp_i == NULL )
     {
      fprintf(stderr,"ERROR : Can't open input file [%s] !\n",sys.data_file);
      return ;
     }
 else
     {
      fprintf (stdout,"INFO  : Processing input file ..\n");
     }


 fscanf(fp_i,"%s", &DB_UNIT_NAME) ;

      if ( strcmp(DB_UNIT_NAME,"MM") == 0 ) DB_UNIT = 1;
 else if ( strcmp(DB_UNIT_NAME,"CM") == 0 ) DB_UNIT = 2;
 else if ( strcmp(DB_UNIT_NAME,"DM") == 0 ) DB_UNIT = 3;
 else if ( strcmp(DB_UNIT_NAME,"M" ) == 0 ) DB_UNIT = 4;
 else if ( strcmp(DB_UNIT_NAME,"KM") == 0 ) DB_UNIT = 5;

 fscanf(fp_i,"%lf %lf %lf %lf ", &x_min, &y_min, &x_max, &y_max) ;


 i          = feat_count ;  /* Used for workspace Merege */
 xy_index   = xy_LAST    ;
 text_index = text_LAST  ;


 while( fscanf(fp_i,"\n %d", &feat[++i].num) == 1 )
      {
       fscanf(fp_i,"%s %d %d %d %s %s %s %s %s %d %d %d %d %d %d %d %d"
                   ,&feat[i].code
                   ,&feat[i].type
                   ,&feat[i].layer
                   ,&feat[i].network
                   ,&feat[i].scale_range
                   ,&feat[i].displayed
                   ,&feat[i].selectble
                   ,&feat[i].has_attrib
                   ,&feat[i].has_text
                   ,&feat[i].color
                   ,&feat[i].linetype
                   ,&feat[i].linewidth
                   ,&feat[i].xbase
                   ,&feat[i].ybase
                   ,&feat[i].xend
                   ,&feat[i].yend
                   ,&feat[i].xy_count );

       feat[i].selectble[0] = 'I' ;   // I  for imported Record

       if  ( feat[i].xy_count > 0 )
           {
             feat[i].xy = xy_index ;
             for ( ii=1 ; ii<=feat[i].xy_count ; ii++ )
                 {
                  fscanf(fp_i,"%d %d", &x[ii+xy_index], &y[ii+xy_index] ) ;
                 }
             xy_index = xy_index + feat[i].xy_count ;
            }

   else if  ( feat[i].type == 1 )
            {
             fscanf(fp_i,"%d %d %d",&feat[i].symb_num,&feat[i].symb_size,&feat[i].symb_angle);
            }


      if  ( feat[i].has_text[0] == 'Y' )
          {
           fscanf(fp_i,"%d", &feat[i].text_count ) ;

           feat[i].text = text_index ;

           for (ii=1 ; ii<=feat[i].text_count ; ii++)
               {
                fscanf(fp_i,"%d",   &text[feat[i].text+ii].x      ) ;
                fscanf(fp_i,"%d",   &text[feat[i].text+ii].y      ) ;
                fscanf(fp_i,"%d",   &text[feat[i].text+ii].size   ) ;
                fscanf(fp_i,"%f",   &text[feat[i].text+ii].angle  ) ;
                fscanf(fp_i,"%d",   &text[feat[i].text+ii].just   ) ;
                fscanf(fp_i,"%d",   &text[feat[i].text+ii].font   ) ;

             /* fscanf(fp_i,"%50s", &text[feat[i].text+ii].string ) ;  */
                fgets (text[feat[i].text+ii].string, 2  , fp_i );
                fgets (text[feat[i].text+ii].string, 51 , fp_i );

                // Delete TEXT Trilling spaces
                for (j=48 ; j>=1 ; j--)   // Text_string [0] -> [48], [49]='\0'
                    {
                     if ( text[feat[i].text+ii].string[j] != ' ' )
                        {
                         text[feat[i].text+ii].string[j+1] = '\0' ;
                         // printf("\n String length = %d \n",j+1 );
                         break;
                        }
                    }
               }
           text_index = text_index + feat[i].text_count ;
          }

      } /* main loop */

 fclose(fp_i);

 feat_count = i - 1      ;
 xy_LAST    = xy_index   ;
 text_LAST  = text_index ;

 update_layer();

 fprintf (stdout,"INFO  : Feature Count    = [%d]\n",feat_count);
 fprintf (stdout,"INFO  : LAST xy Index    = [%d]\n",xy_LAST   );
 fprintf (stdout,"INFO  : LAST text Index  = [%d]\n",text_LAST );
 fprintf (stdout,"INFO  : Import Ascii file [%s] Completed\n\n",sys.data_file);
}
/*------------------------------------------------------------------------*/
/*                             infoutaCB()                                */
/*------------------------------------------------------------------------*/
void infoutaCB()
{
 activateMenubar = 1 ;
 // wait_cursor()       ;
 move_fun = NONE     ;

 xstr  = XmStringCreate("Output file name",CS);
 xstr1 = XmStringCreate("aa",CS);
 n=0;
 XtSetArg(args[n] , XmNdialogTitle ,        xstr);n++;
// XtSetArg(args[n] , XmNtitle       ,       xstr1);n++;
 XtSetArg(args[n] , XmNwidth       ,         300);n++;
 XtSetArg(args[n] , XmNheight      ,         130);n++;
 XtSetArg(args[n] , XmNborderColor , white.pixel);n++;
 XtSetArg(args[n] , XmNforeground  , black.pixel);n++;
 XtSetArg(args[n] , XmNbackground  , lgray.pixel);n++;

 PD = XmCreatePromptDialog(MainForm,"PD",args,n);
 XtAddCallback(PD,XmNokCallback,infoutaOKCB,MainForm);
 XtAddCallback(PD,XmNcancelCallback,infoutaCancelCB,MainForm);
 XtManageChild(PD);

 /* keep the user on this dialog until it is accepted or canceled */
 XtAddGrab( PD,True,False );
}
/*------------------------------------------------------------------------*/
/*                            infoutaOKCB()                               */
/*------------------------------------------------------------------------*/
void infoutaOKCB(Widget w, caddr_t client_data, FSBCBS *call_data)
{
 char  *str   ;

 XmStringGetLtoR(call_data->value ,CS ,&str);
 strcpy(OutputFile,str);
 strcat(OutputFile,".inf");

 fp_o = fopen (OutputFile,"wt");
 if  ( fp_o == NULL )
     {
      fprintf (stderr,"ERROR : Can't open output file  !\n");
      // normal_cursor();
      return ;
     }

 printf ("INFO  : Processing output file ..\n");

      if ( DB_UNIT == 1 ) strcpy (DB_UNIT_NAME , "MM") ;
 else if ( DB_UNIT == 2 ) strcpy (DB_UNIT_NAME , "CM") ;
 else if ( DB_UNIT == 3 ) strcpy (DB_UNIT_NAME , "DM") ;
 else if ( DB_UNIT == 4 ) strcpy (DB_UNIT_NAME , "M" ) ;
 else if ( DB_UNIT == 5 ) strcpy (DB_UNIT_NAME , "KM") ;

 fprintf(fp_o ,"%2s", &DB_UNIT_NAME) ;
 fprintf(fp_o ,"\n%d %d %d %d ",(int)x_min,(int)y_min,(int)x_max,(int)y_max) ;


 for ( i=1 ; i <= feat_count ; i++ )
     {
      if ( feat[i].has_text[0] != 'Y' )  feat[i].has_text[0] = 'N';

      fprintf(fp_o ,"\n%-6d ",feat[i].num           ) ;
      fprintf(fp_o ,"%-12s ", feat[i].code          ) ;  /* - for left justfied  */
      fprintf(fp_o ,"%-2d ",  feat[i].type          ) ;
      fprintf(fp_o ,"%-2d ",  feat[i].layer         ) ;
      fprintf(fp_o ,"%-2d ",  feat[i].network       ) ;
      fprintf(fp_o ,"%c" ,    feat[i].scale_range[0]) ;
      fprintf(fp_o ,"%c" ,    feat[i].scale_range[1]) ;
      fprintf(fp_o ,"%c" ,    feat[i].scale_range[2]) ;
      fprintf(fp_o ,"%c" ,    feat[i].scale_range[3]) ;
      fprintf(fp_o ,"%c ",    feat[i].scale_range[4]) ;
      fprintf(fp_o ,"%c ",    feat[i].displayed[0]  ) ;
      fprintf(fp_o ,"%c ",    feat[i].selectble[0]  ) ;
      fprintf(fp_o ,"%c ",    feat[i].has_attrib[0] ) ;
      fprintf(fp_o ,"%c ",    feat[i].has_text[0]   ) ;

           if (feat[i].color == blue.pixel  )  fprintf(fp_o ,"1  ") ;
      else if (feat[i].color == red.pixel   )  fprintf(fp_o ,"2  ") ;
      else if (feat[i].color == pink.pixel  )  fprintf(fp_o ,"3  ") ;
      else if (feat[i].color == green.pixel )  fprintf(fp_o ,"4  ") ;
      else if (feat[i].color == cyan.pixel  )  fprintf(fp_o ,"5  ") ;
      else if (feat[i].color == yellow.pixel)  fprintf(fp_o ,"6  ") ;
      else if (feat[i].color == white.pixel )  fprintf(fp_o ,"7  ") ;
      else if (feat[i].color == black.pixel )  fprintf(fp_o ,"8  ") ;
      else if (feat[i].color == gray.pixel  )  fprintf(fp_o ,"9  ") ;
      else if (feat[i].color == wheat.pixel )  fprintf(fp_o ,"10 ") ;
      else if (feat[i].color == brown.pixel )  fprintf(fp_o ,"11 ") ;
      else if (feat[i].color == orange.pixel)  fprintf(fp_o ,"12 ") ;
      else if (feat[i].color == lgray.pixel )  fprintf(fp_o ,"13 ") ;
      else     /* default color */             fprintf(fp_o ,"7  ") ;

      fprintf(fp_o ,"%-2d ",  feat[i].linetype   );
      fprintf(fp_o ,"%-2d ",  feat[i].linewidth  );
      fprintf(fp_o ,"%-10d ", feat[i].xbase      ) ;
      fprintf(fp_o ,"%-10d ", feat[i].ybase      ) ;
      fprintf(fp_o ,"%-10d ", feat[i].xend       ) ;
      fprintf(fp_o ,"%-10d ", feat[i].yend       ) ;
      fprintf(fp_o ,"%-4d ",  feat[i].xy_count   ) ;

      if  ( feat[i].xy_count > 0 )
          {
           for ( ii=1 ; ii<=feat[i].xy_count ; ii++ )
               {
                fprintf(fp_o ,"%-10d ", x[feat[i].xy+ii] ) ;
                fprintf(fp_o ,"%-10d ", y[feat[i].xy+ii] ) ;
               }
          }
  else if ( feat[i].type == 1 )
          {
           fprintf(fp_o,"%-3d ", feat[i].symb_num  ) ;
           fprintf(fp_o,"%-3d ", feat[i].symb_size ) ;
           fprintf(fp_o,"%-3d ", feat[i].symb_angle) ;
          }

      if  ( feat[i].has_text[0] == 'Y' )
          {
           fprintf(fp_o,"%d ", feat[i].text_count ) ;

           for (ii=1 ; ii<=feat[i].text_count ; ii++)
               {
                fprintf(fp_o,"%d ",  text[feat[i].text+ii].x     ) ;
                fprintf(fp_o,"%d ",  text[feat[i].text+ii].y     ) ;
                fprintf(fp_o,"%d ",  text[feat[i].text+ii].size  ) ;
                fprintf(fp_o,"%f ",  text[feat[i].text+ii].angle ) ;
                fprintf(fp_o,"%d ",  text[feat[i].text+ii].just  ) ;
                fprintf(fp_o,"%d ",  text[feat[i].text+ii].font  ) ;
                fprintf(fp_o,"%-50s",text[feat[i].text+ii].string) ;
               }
          }

     } /* main loop */

 fclose(fp_o);
 // normal_cursor();

 xstr = XmStringCreate(" INFO : Export Ascii inf Function Completed",CS);
 XtSetArg(args[0], XmNlabelString ,  xstr);
 XtSetValues(output_label,args,1);
}
/*------------------------------------------------------------------------*/
/*                        infouaCancelCB()                                */
/*------------------------------------------------------------------------*/
void infoutaCancelCB(Widget w, caddr_t client_data, FSBCBS *call_data)
{
 // normal_cursor();
}

/*------------------------------------------------------------------------*/
/*                          CenterpointCB()                               */
/*------------------------------------------------------------------------*/
void centerpointCB()
{
 activateMenubar = 1  ;
 // normal_cursor()      ;  /* cross hair enter/leave bug */

 draw_fun = CPOINT    ;
 move_fun = CROSSHAIR ;
 point_counter = 1    ;

 xstr = XmStringCreate(" CENTER POINT : Select New Center point",CS);
 XtSetArg(args[0], XmNlabelString, xstr);
 XtSetValues(output_label,args,1);
}
/*------------------------------------------------------------------------*/
/*                           addpointCB()                                 */
/*------------------------------------------------------------------------*/
void addpointCB()
{
 activateMenubar = 1  ;
 draw_fun = ADDPOINT  ;
 last_fun = ADDPOINT  ;
 move_fun = CROSSHAIR ;

 strcpy (add.code,"point_feat");
 add.type       = 1            ;
 add.layer      = 1            ;
 add.network    = 1            ;
 add.color      = yellow.pixel ;
 add.linetype   = 1            ;
 add.linewidth  = 1            ;
 add.symb_num   = 6            ;
 add.symb_size  = 30           ;
 add.symb_angle = 0            ;
 add.text_count = 1            ;

 point_counter = 1 ;
}
/*------------------------------------------------------------------------*/
/*                            addtextCB()                                 */
/*------------------------------------------------------------------------*/
void addtextCB()
{
 activateMenubar = 1 ;

 feat_count++ ;
 text_index = text_LAST ;
 feat[feat_count].text = text_index++ ;

 xstr = XmStringCreate("Enter text ",CS);
 n=0;
 XtSetArg(args[n], XmNdialogTitle , xstr);n++;
 XtSetArg(args[n], XmNwidth       ,  300);n++;
 XtSetArg(args[n], XmNheight      ,  130);n++;
 PD = XmCreatePromptDialog(MainForm,"PD",args,n);
 XtAddCallback(PD,XmNokCallback,textCB,MainForm);
 XtManageChild(PD);

 XtAddGrab( PD,True,False );

 draw_fun = ADDTEXT   ;
 last_fun = ADDTEXT   ;
 move_fun = CROSSHAIR ;
 point_counter = 1    ;
}
/*------------------------------------------------------------------------*/
/*                          addtext2fCB()                                 */
/*------------------------------------------------------------------------*/
void addtext2fCB()
{
 activateMenubar = 1  ;
 draw_fun = ADDTEXT2F ;
 last_fun = ADDTEXT2F ;
 move_fun = CROSSHAIR ;
 point_counter = 1    ;
}
/*------------------------------------------------------------------------*/
/*                           addnodeCB()                                  */
/*------------------------------------------------------------------------*/
void addnodeCB()
{
 activateMenubar = 1  ;
 draw_fun = ADDNODE   ;
 move_fun = CROSSHAIR ;
 point_counter = 1    ;
}
/*------------------------------------------------------------------------*/
/*                           addaccdentCB()                               */
/*------------------------------------------------------------------------*/
void addaccdentCB()
{
 activateMenubar = 1   ;
 draw_fun = ADDACCDENT ;
 move_fun = CROSSHAIR  ;
 point_counter = 1     ;
}
/*------------------------------------------------------------------------*/
/*                             addarcCB()                                 */
/*------------------------------------------------------------------------*/
void addarcCB()
{
 activateMenubar = 1  ;
 draw_fun = ADDARC    ;
 move_fun = CROSSHAIR ;
 point_counter = 1    ;
}
/*------------------------------------------------------------------------*/
/*                            addlineCB()                                 */
/*------------------------------------------------------------------------*/
void addlineCB()
{
 activateMenubar = 1  ;
 draw_fun = ADDLINE   ;
 last_fun = ADDLINE   ;
 move_fun = CROSSHAIR ;

 strcpy (add.code,"line_feat") ;
 add.type       = 2            ;
 add.layer      = 1            ;
 add.network    = 0            ;
 add.color      = yellow.pixel ;
 add.linetype   = 2            ;
 add.linewidth  = 2            ;

 point_counter = 1 ;
}
/*------------------------------------------------------------------------*/
/*                           addpolygonCB()                               */
/*------------------------------------------------------------------------*/
void addpolygonCB()
{
 activateMenubar = 1   ;
 draw_fun = ADDPOLYGON ;
 move_fun = CROSSHAIR  ;
 point_counter = 1     ;
}
/*------------------------------------------------------------------------*/
/*                           add_gridCB()                                 */
/*------------------------------------------------------------------------*/
void add_gridCB()
{
 activateMenubar = 1  ;
 draw_fun = ADDPOINT  ;
 move_fun = CROSSHAIR ;

 strcpy (add.code , "grid" )  ;
 add.type       = 1           ;
 add.layer      = 1           ;
 add.network    = 1           ;
 add.color      = white.pixel ;
 add.linetype   = 1           ;
 add.linewidth  = 2           ;
 add.symb_num   = 1           ;
 add.symb_size  = 50          ;
 add.symb_angle = 0           ;
 add.text_count = 1           ;

 point_counter = 1 ;
}
/*------------------------------------------------------------------------*/
/*                           add_substnCB()                               */
/*------------------------------------------------------------------------*/
void add_substnCB()
{
 activateMenubar = 1  ;
 draw_fun = ADDPOINT  ;
 move_fun = CROSSHAIR ;

 strcpy (add.code , "substation" ) ;
 add.type       = 1           ;
 add.layer      = 1           ;
 add.network    = 1           ;
 add.color      = white.pixel ;
 add.linetype   = 1           ;
 add.linewidth  = 2           ;
 add.symb_num   = 2           ;
 add.symb_size  = 30          ;
 add.symb_angle = 0           ;
 add.text_count = 1           ;

 point_counter = 1 ;
}
/*------------------------------------------------------------------------*/
/*                           add_op_ptCB()                                */
/*------------------------------------------------------------------------*/
void add_op_ptCB()
{
 activateMenubar = 1  ;
 draw_fun = ADDOPPT   ;
 move_fun = CROSSHAIR ;

 strcpy (add.code , "open_point") ;
 add.type       = 1           ;
 add.layer      = 1           ;
 add.network    = 1           ;
 add.color      = white.pixel ;
 add.linetype   = 1           ;
 add.linewidth  = 2           ;
 add.symb_num   = 3           ;
 add.symb_size  = 40          ;
 add.symb_angle = 0           ;
 add.text_count = 0           ;

 point_counter = 1 ;
}
/*------------------------------------------------------------------------*/
/*                          get_xy_point()                                */
/*------------------------------------------------------------------------*/
void get_xy_point()
{
 activateMenubar = 1  ;

 point.xscreen   = 0  ;
 point.yscreen   = 0  ;
 point.xdb       = 0  ;
 point.xdb       = 0  ;

 draw_fun = GETXYPT   ;
 move_fun = CROSSHAIR ;

 // XtAddGrab( MainForm,True,False );
}
/*------------------------------------------------------------------------*/
/*                           add_mv_fdrCB()                               */
/*------------------------------------------------------------------------*/
void add_mv_fdrCB()
{
 activateMenubar = 1  ;
 draw_fun = ADDLINE   ;
 move_fun = CROSSHAIR ;

 strcpy (add.code,"mvfeeder")  ;
 add.type       = 2            ;
 add.layer      = 1            ;
 add.network    = 1            ;
 add.color      = red.pixel    ;
 add.linetype   = 1            ;
 add.linewidth  = 3            ;

 point_counter = 1    ;
}
/*------------------------------------------------------------------------*/
/*                                sldCB()                                 */
/*------------------------------------------------------------------------*/
void sldCB()
{
 activateMenubar = 1 ;

 if ( db_opened[0] != 'Y' )
    {
     xstr  = XmStringCreate("INFO",CS);
     xstr1 = XmStringCreate("No Database Connection found, Function Canceled",CS);

     n=0;
     XtSetArg(args[n] , XmNdialogTitle   ,        xstr);n++;
     XtSetArg(args[n] , XmNmessageString ,       xstr1);n++;
     XtSetArg(args[n] , XmNborderColor   , white.pixel);n++;
     XtSetArg(args[n] , XmNforeground    , black.pixel);n++;
     XtSetArg(args[n] , XmNbackground    , lgray.pixel);n++;

     PD = XmCreateErrorDialog(MainForm,"PD",args,n);
     XtManageChild(PD);

     // normal_cursor();
     return ;
    }

 // wait_cursor() ;


 // Set Display OFF for Old SLD (in SLD layer if any)
 for (i=1 ; i<=feat_count ; i++)
     {
      if (feat[i].layer == 34 && feat[i].selectble[0] == 'I') // SLD Layer and Imported Record
         {
          feat[i].displayed[0]   = 'N' ;
          feat[i].scale_range[0] = 'N' ;
          feat[i].scale_range[1] = 'N' ;
          feat[i].scale_range[2] = 'N' ;
          feat[i].scale_range[3] = 'N' ;
          feat[i].scale_range[4] = 'N' ;
         }
    }


 xstr = XmStringCreate("SLD, enter Grid name, Feeder Number",CS);
 n=0;
 XtSetArg(args[n], XmNdialogTitle  , xstr);n++;
 XtSetArg(args[n] , XmNwidth       ,  300);n++;
 XtSetArg(args[n] , XmNheight      ,  130);n++;
 PD = XmCreatePromptDialog(MainForm,"PD",args,n);
 XtAddCallback(PD,XmNokCallback,runsldCB,MainForm);
 XtManageChild(PD);

 /* keep the user on this dialog until it is accepted or canceled */
 XtAddGrab( PD,True,False );
}
/*------------------------------------------------------------------------*/
/*                             runsldCB()                                 */
/*------------------------------------------------------------------------*/
void runsldCB(Widget w, caddr_t client_data, FSBCBS *call_data)
{
 char *str        ;
 char command[50] ;


 XmStringGetLtoR(call_data->value ,CS ,&str);

 strcpy (command, "./geosld ");
 strcat (command, db_name    );
 strcat (command, " "        );
 strcat (command, str        );

 system (command) ;
 // infinbCB() ;
 // zoom_all("test.png")   ;

 strcpy(InputFile,"./sld.infb");
 fp_i = fopen (InputFile,"rb");
 if  ( fp_i == NULL )
     {
      xstr = XmStringCreate(" ERROR : Can't open input file  !",CS);
      XtSetArg(args[0], XmNlabelString, xstr);
      XtSetValues(output_label, args, 1);
      // normal_cursor();
      return ;
     }

 printf ("INFO  : Processing input file ..\n");

 XSynchronize(MainDisplay,1);
  cls_flag = 1 ;
  XClearWindow(MainDisplay,XtWindow(drawarea));
  XFillRectangle(MainDisplay,Tile,Tilegc,0,0,499,499);
 XSynchronize(MainDisplay,0);


 fread (&DB_UNIT_NAME , sizeof(DB_UNIT_NAME) , 1 , fp_i);
 fread (&x_min        , sizeof(x_min)        , 1 , fp_i);
 fread (&y_min        , sizeof(y_min)        , 1 , fp_i);
 fread (&x_max        , sizeof(x_max)        , 1 , fp_i);
 fread (&y_max        , sizeof(y_max)        , 1 , fp_i);


      if ( strcmp(DB_UNIT_NAME,"MM") == 0 ) DB_UNIT = 1 ;
 else if ( strcmp(DB_UNIT_NAME,"CM") == 0 ) DB_UNIT = 2 ;
 else if ( strcmp(DB_UNIT_NAME,"DM") == 0 ) DB_UNIT = 3 ;
 else if ( strcmp(DB_UNIT_NAME,"M" ) == 0 ) DB_UNIT = 4 ;
 else if ( strcmp(DB_UNIT_NAME,"KM") == 0 ) DB_UNIT = 5 ;

 /*
 Used for workspace Load
 i = 0 ; xy_index = 0 ; text_index = 0 ;
 */

 i          = feat_count ;   /* Used for workspace Merege */
 xy_index   = xy_LAST    ;
 text_index = text_LAST  ;


 while( fread (&feat[++i],sizeof(feat[i]),1,fp_i) == 1 )
      {
       feat[i].selectble[0] = 'I' ;    // I for Imported Record

       if ( feat[i].xy_count > 0 )
          {
           feat[i].xy = xy_index ;
           for ( ii=1 ; ii<=feat[i].xy_count ; ii++ )
               {
                fread (&x[xy_index+ii],sizeof(&x[0]),1,fp_i);
                fread (&y[xy_index+ii],sizeof(&y[0]),1,fp_i);
               }
           xy_index = xy_index + feat[i].xy_count ;
          }

       if ( feat[i].has_text[0] == 'Y' )
          {
           feat[i].text = text_index ;
           for ( ii=1 ; ii<=feat[i].text_count ; ii++ )
               {
                fread (&text[feat[i].text+ii],sizeof(text[0]),1,fp_i);
               }
           text_index = text_index + feat[i].text_count ;
          }
/*
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
*/
      } /* main loop */


 fclose(fp_i);

 feat_count = i - 1      ;
 xy_LAST    = xy_index   ;
 text_LAST  = text_index ;


 update_layer();
 display_scale();
//  draw_all();
 // normal_cursor();

 xstr = XmStringCreate(" INFO : SLD Function Completed ",CS);
 XtSetArg(args[0], XmNlabelString ,  xstr);
 XtSetValues(output_label,args,1);
}
/*------------------------------------------------------------------------*/
/*                              dxfinCB()                                 */
/*------------------------------------------------------------------------*/
void dxfinCB()
{
 activateMenubar = 1 ;

 // wait_cursor()   ;

 fsb("dxf","Import DXF File");

 if ( return_code == 1 )     /*   Canceled   */
    {
     xstr = XmStringCreate(" INFO : Function Canceled",CS);
     XtSetArg(args[0], XmNlabelString, xstr);
     XtSetValues(output_label, args, 1);
     // normal_cursor();
     return ;
    }

 dxfin()         ;
 // normal_cursor() ;

 xstr = XmStringCreate(" INFO : Import DXF Function Completed ",CS);
 XtSetArg(args[0], XmNlabelString ,  xstr);
 XtSetValues(output_label,args,1);
}
/*------------------------------------------------------------------------*/
/*                              dxfoutCB()                                */
/*------------------------------------------------------------------------*/
void dxfoutCB()
{
 activateMenubar = 1 ;

 // wait_cursor()   ;
 dxfout()        ;
 // normal_cursor() ;

 xstr = XmStringCreate(" INFO : Export DXF Function Completed ",CS);
 XtSetArg(args[0], XmNlabelString ,  xstr);
 XtSetValues(output_label,args,1);
}
/*------------------------------------------------------------------------*/
/*                              bitmapCB()                                */
/*------------------------------------------------------------------------*/
void bitmapCB()
{
 activateMenubar = 1 ;

 // wait_cursor()   ;
 export_bitmap() ;
 // normal_cursor() ;

 xstr = XmStringCreate(" INFO : Export BITMAP Function Completed ",CS);
 XtSetArg(args[0], XmNlabelString ,  xstr);
 XtSetValues(output_label,args,1);
}
/*------------------------------------------------------------------------*/
/*                           edgematchCB()                                */
/*------------------------------------------------------------------------*/
void edgematchCB()
{
 activateMenubar = 1 ;

 // wait_cursor()   ;
 match_all(JOIN_TOLERANCE)   ; /* match tolerance */
 // normal_cursor() ;

 xstr = XmStringCreate(" INFO : Edge Matching Function Completed ",CS);
 XtSetArg(args[0], XmNlabelString ,  xstr);
 XtSetValues(output_label,args,1);
}
/*------------------------------------------------------------------------*/
/*                              scaleCB()                                 */
/*------------------------------------------------------------------------*/
void scaleCB()
{
 activateMenubar = 1 ;
 // wait_cursor()       ;
 move_fun = NONE     ;

 xstr  = XmStringCreate("Set Scale",CS);
 xstr1 = XmStringCreate("aa",CS);
 n=0;
 XtSetArg(args[n] , XmNdialogTitle ,        xstr);n++;
 XtSetArg(args[n] , XmNtitle       ,       xstr1);n++;
 XtSetArg(args[n] , XmNwidth       ,         300);n++;
 XtSetArg(args[n] , XmNheight      ,         130);n++;
 XtSetArg(args[n] , XmNborderColor , white.pixel);n++;
 XtSetArg(args[n] , XmNforeground  , black.pixel);n++;
 XtSetArg(args[n] , XmNbackground  , lgray.pixel);n++;

 PD = XmCreatePromptDialog(MainForm,"PD",args,n);
 XtAddCallback(PD,XmNokCallback,scaleOkCB,MainForm);
 XtAddCallback(PD,XmNcancelCallback,scaleCancelCB,MainForm);
 XtManageChild(PD);

 /* keep the user on this dialog until it is accepted or canceled */
 XtAddGrab( PD,True,False );
}
/*------------------------------------------------------------------------*/
/*                            scaleOkCB()                                 */
/*------------------------------------------------------------------------*/
void scaleOkCB(Widget w, caddr_t client_data, FSBCBS *call_data)
{
 char     *str;

 XmStringGetLtoR(call_data->value ,CS ,&str);
 scale = atoi(str) ;

 if ( scale > 0 )
    {
     switch (DB_UNIT)
          {
           case MM: y_diff = scale * ( SCREEN_CM / .1   ); break ;
           case CM: y_diff = scale * ( SCREEN_CM / 1.   ); break ;
           case DM: y_diff = scale * ( SCREEN_CM / 10.  ); break ;
           case  M: y_diff = scale * ( SCREEN_CM / 100. ); break ;
           case KM: y_diff = scale * ( SCREEN_CM / 1000.); break ;
           default: y_diff = scale * ( SCREEN_CM / 100. );
                    fprintf(stderr,"ERROR : Data Base Unit not Defined\n");
                    break ;
          }

     x_center = ( x_max + x_min ) / 2  ;
     y_center = ( y_max + y_min ) / 2  ;

     x_min = x_center - ( y_diff / 2 ) ;
     y_min = y_center - ( y_diff / 2 ) ;
     x_max = x_center + ( y_diff / 2 ) ;
     y_max = y_center + ( y_diff / 2 ) ;

//     draw_all();
     // normal_cursor();
     display_scale();
    }
 else
    {
     xstr = XmStringCreate(" ERROR : Invalid Scale value ..",CS);
     XtSetArg(args[0], XmNlabelString, xstr);
     XtSetValues(output_label,args,1);
     // normal_cursor();
    }
}
/*------------------------------------------------------------------------*/
/*                         scaleCancelCB()                                */
/*------------------------------------------------------------------------*/
void scaleCancelCB(Widget w, caddr_t client_data, FSBCBS *call_data)
{
 // normal_cursor();
}
/*------------------------------------------------------------------------*/
/*                              findCB()                                  */
/*------------------------------------------------------------------------*/
void findCB()
{
 activateMenubar = 1 ;
 // wait_cursor()       ;
 move_fun = NONE     ;

 xstr  = XmStringCreate("Find Feature by feat_num",CS);
 xstr1 = XmStringCreate("aa",CS);
 n=0;
 XtSetArg(args[n] , XmNdialogTitle ,        xstr);n++;
 XtSetArg(args[n] , XmNtitle       ,       xstr1);n++;
 XtSetArg(args[n] , XmNwidth       ,         300);n++;
 XtSetArg(args[n] , XmNheight      ,         130);n++;
 XtSetArg(args[n] , XmNborderColor , white.pixel);n++;
 XtSetArg(args[n] , XmNforeground  , black.pixel);n++;
 XtSetArg(args[n] , XmNbackground  , lgray.pixel);n++;

 PD = XmCreatePromptDialog(MainForm,"PD",args,n);
 XtAddCallback(PD,XmNokCallback,findOkCB,MainForm);
 XtAddCallback(PD,XmNcancelCallback,findCancelCB,MainForm);
 XtManageChild(PD);

 /* keep the user on this dialog until it is accepted or canceled */
 XtAddGrab( PD,True,False );
}
/*------------------------------------------------------------------------*/
/*                            findOkCB()                                  */
/*------------------------------------------------------------------------*/
void findOkCB(Widget w, caddr_t client_data, FSBCBS *call_data)
{
 char     *str;

 XmStringGetLtoR(call_data->value ,CS ,&str);
 scale = atoi(str) ;

 if ( scale > 0 )
    {

//     draw_all();
     // normal_cursor();
     display_scale();
    }
 else
    {
     xstr = XmStringCreate(" ERROR : Invalid Feature Number ..",CS);
     XtSetArg(args[0], XmNlabelString, xstr);
     XtSetValues(output_label,args,1);
     // normal_cursor();
    }
}
/*------------------------------------------------------------------------*/
/*                          findCancelCB()                                */
/*------------------------------------------------------------------------*/
void findCancelCB(Widget w, caddr_t client_data, FSBCBS *call_data)
{
 // normal_cursor();
}
/*------------------------------------------------------------------------*/
/*                              textCB()                                  */
/*------------------------------------------------------------------------*/
void textCB(Widget w, caddr_t client_data, FSBCBS *call_data)
{
 char     *str;

 XmStringGetLtoR(call_data->value ,CS ,&str);
 strcpy (text[text_index].string,str);
// move_fun = CROSSHAIR ;

 XSynchronize(MainDisplay,1);
  /* Change Cursor to Pixmap Null Shape */
  XDefineCursor (MainDisplay,XtWindow(drawarea),pixCursor);
  /* Change Move_function to CrossHair  */
  move_fun = CROSSHAIR ;
  enable_leave = 1 ;
  enable_enter = 1 ;
 XSynchronize(MainDisplay,0);

}
/*------------------------------------------------------------------------*/
/*                              editCB()                                  */
/*------------------------------------------------------------------------*/
void editCB()
{
 activateMenubar = 1  ;
 // normal_cursor()      ;  /* cross hair enter/leave bug */

 draw_fun = EDIT      ;
 move_fun = CROSSHAIR ;

 xstr = XmStringCreate(" EDIT : Correlate on Feature",CS);
 XtSetArg(args[0], XmNlabelString ,  xstr);
 XtSetValues(output_label,args,1);
}
/*------------------------------------------------------------------------*/
/*                          editpictureCB()                               */
/*------------------------------------------------------------------------*/
void editpictureCB()
{
 activateMenubar = 1  ;
 // normal_cursor()      ;  /* cross hair enter/leave bug */

 draw_fun = EDITPIC   ;
 last_fun = EDITPIC   ;
 move_fun = CROSSHAIR ;

 xstr = XmStringCreate(" EDIT : Correlate on Feature",CS);
 XtSetArg(args[0], XmNlabelString ,  xstr);
 XtSetValues(output_label,args,1);
}
/*------------------------------------------------------------------------*/
/*                          editparmCB()                               */
/*------------------------------------------------------------------------*/
void edit_parmCB()
{
 activateMenubar = 1 ;
 // wait_cursor()       ;  /* cross hair enter/leave bug */
 move_fun = NONE     ;

 edit_parm(MainForm)    ;
}
/*------------------------------------------------------------------------*/
/*                           distanceCB()                                 */
/*------------------------------------------------------------------------*/
void distanceCB()
{
 draw_fun = DISTANCE  ;
 move_fun = CROSSHAIR ;

 point_counter = 1    ;

 xstr = XmStringCreate(" DISTANCE : Select 2 points",CS);
 XtSetArg(args[0], XmNlabelString ,  xstr);
 XtSetValues(output_label,args,1);
}
/*------------------------------------------------------------------------*/
/*                              whereCB()                                 */
/*------------------------------------------------------------------------*/
void whereCB()
{
 draw_fun = WHERE     ;
 move_fun = CROSSHAIR ;

 xstr = XmStringCreate(" WHERE : Point to a Location",CS);
 XtSetArg(args[0], XmNlabelString ,  xstr);
 XtSetValues(output_label,args,1);
}
/*------------------------------------------------------------------------*/
/*                          double_curCB()                                */
/*------------------------------------------------------------------------*/
void double_curCB()
{
 if (cursor_size <= 32)
    {
     cursor_size = cursor_size * 2 ;
     tolerance = cursor_size * ONE_PIXEL ;
    }
}
/*------------------------------------------------------------------------*/
/*                           half_curCB()                                 */
/*------------------------------------------------------------------------*/
void half_curCB()
{
 if (cursor_size >= 8)
    {
     cursor_size = cursor_size / 2 ;
     tolerance = cursor_size * ONE_PIXEL ;
    }
}
/*------------------------------------------------------------------------*/
/*                             plotCB()                                   */
/*------------------------------------------------------------------------*/
void plotCB()
{
 double        LONG   ;
 double        LAT    ;
 double        X      ;
 double        Y      ;
 int           ZONE   ;


 X    = 636500.8 ;
 Y    = 812465.4 ;

 LONG  = fromETM ((636500.8), (812465.4), 1);
 printf ("\n LONG = %lf \n",LONG );

 LAT   = fromETM ((636500.8), (812465.4), 2);
 printf ("\n LAT = %lf \n",LAT );



 LONG = 31.0  ;
 LAT  = 30.0  ;

 X    = toUTM(LONG,LAT,1 );
 printf ("\n X = %lf \n",X );

 Y    = toUTM(LONG,LAT,2);
 printf ("\n Y = %lf \n",Y  );

 ZONE = (int) toUTM(LONG,LAT,3);
 printf ("\n ZONE = %d \n",ZONE);




 return ;





 activateMenubar = 1  ;
 // wait_cursor()        ;


 /* plot()               ; */
 cls_flag = 1         ;
 move_fun = CROSSHAIR ;
 // normal_cursor()      ;
 return ;

/*
 draw_fun = PLOTWINDOW ;
 move_fun = CROSSHAIR  ;
 point_counter = 1     ;
*/



 // wait_cursor()        ;
 createGL()           ;
 cls_flag = 1         ;
 move_fun = CROSSHAIR ;
 point_counter = 1    ;
 // normal_cursor()      ;


 xstr = XmStringCreate(" PLOT : Select PLOT Window",CS);
 XtSetArg(args[0], XmNlabelString, xstr);
 XtSetValues(output_label,args,1);
}
/*------------------------------------------------------------------------*/
/*                             createGL()                                */
/*------------------------------------------------------------------------*/
void createGL()
{
 fp_o = fopen ("geoIMS.gl","wt");
 if  ( fp_o == NULL )
     {
      fprintf (stderr,"ERROR : Can't open PLOT file  !\n");
      // normal_cursor () ;
      return ;
     }

 printf ("INFO  : Processing PLOT file ..\n");

 x_min1 = x_min_plot - SYMBCLIPBUFFER/2 ;
 y_min1 = y_min_plot - SYMBCLIPBUFFER/2 ;
 x_max1 = x_max_plot + SYMBCLIPBUFFER/2 ;
 y_max1 = y_max_plot + SYMBCLIPBUFFER/2 ;

 x_min2 = x_min_plot - LINECLIPBUFFER ;
 y_min2 = y_min_plot - LINECLIPBUFFER ;
 x_max2 = x_max_plot + LINECLIPBUFFER ;
 y_max2 = y_max_plot + LINECLIPBUFFER ;

 y_diff = y_max_plot - y_min_plot ;
 switch (DB_UNIT)
      {
       case MM: scale = ( y_diff * .1   ) / SCREEN_CM ; break ;
       case CM: scale = ( y_diff * 1.   ) / SCREEN_CM ; break ;
       case DM: scale = ( y_diff * 10.  ) / SCREEN_CM ; break ;
       case  M: scale = ( y_diff * 100. ) / SCREEN_CM ; break ;
       case KM: scale = ( y_diff * 1000.) / SCREEN_CM ; break ;
       default: scale = ( y_diff * 100. ) / SCREEN_CM ;
                fprintf(stderr,"ERROR : Data Base Unit not Defined\n");
                break ;
      }


      if ( scale > 0          &&  scale <= SC_RANGE1 ) sc_range = 0 ;
 else if ( scale > SC_RANGE1  &&  scale <= SC_RANGE2 ) sc_range = 1 ;
 else if ( scale > SC_RANGE2  &&  scale <= SC_RANGE3 ) sc_range = 2 ;
 else if ( scale > SC_RANGE3  &&  scale <= SC_RANGE4 ) sc_range = 3 ;
 else if ( scale > SC_RANGE4                         ) sc_range = 4 ;



 fprintf(fp_o ,"IN;");
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

/* Grid PLOT  48,103  */

x1_db = x_min_plot ;
for ( i=1 ; i<=23 ; i++ )
    {
     x1_db = x1_db + (x_max_plot - x_min_plot)/24 ;
     fprintf(fp_o ,"\nPU%d,%d;",(int)x_min_plot,(int)y_min_plot);
     fprintf(fp_o ,"PD%d,%d,%d,%d;",(int)x1_db,(int)y_min_plot,(int)x1_db,(int)y_max_plot);
    }

y1_db = y_min_plot ;
for ( i=1 ; i<=55  ; i++ )
    {
     y1_db = y1_db + (y_max_plot - y_min_plot)/56   ;
     fprintf(fp_o ,"\nPU%d,%d;",(int)x_min_plot,(int)y_min_plot);
     fprintf(fp_o ,"PD%d,%d,%d,%d;",(int)x_min_plot,(int)y1_db,(int)x_max_plot,(int)y1_db);
    }





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
         ((feat[i].symb_size/ONE_PIXEL) >= 1    ) &&
         (x_base >= x_min1)&&(x_base <= x_max1) &&
         (y_base >= y_min1)&&(y_base <= y_max1) )
       {
        if (feat[i].has_text[0] == 'Y')             /* PLOT TEXT IF ANY */
           {
            for(ii=0; ii<feat[i].text_count; ii++)
               {
                text_index = feat[i].text + ii ;
                plot_text(text_index);
               }
           }

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
         ((x_end>x_min2)&&(x_end<x_max2)&&(y_end>y_min2)&&(y_end<y_max2))) )
    {

    for ( ii=0 ; ii<=(feat[i].xy_count+1) ; ii++ )
        {
         switch (ii)
             {
              case 0:
                   SP_flag = 0  ;
                   x1_db = feat[i].xbase ;
                   y1_db = feat[i].ybase ;
                   break ;

              default:
                   if ( ii <= feat[i].xy_count)
                      {
                       x2_db = x[feat[i].xy+ii] ;
                       y2_db = y[feat[i].xy+ii] ;
                      }
                   else
                      {
                       x2_db = x_end ;
                       y2_db = y_end ;
                      }

                  if (( x1_db>x_min_plot && x1_db<x_max_plot && y1_db>y_min_plot && y1_db<y_max_plot ) &&
                      ( x2_db>x_min_plot && x2_db<x_max_plot && y2_db>y_min_plot && y2_db<y_max_plot ))
                     {
                      if (SP_flag == 0) { fprintf(fp_o,"\nSP%d;",color); SP_flag =1; }
                      fprintf(fp_o ,"\nPU,%d,%d;",(int)x1_db,(int)y1_db);
                      fprintf(fp_o ,"PD%d,%d,%d,%d;",(int)x1_db,(int)y1_db,(int)x2_db,(int)y2_db);
                     }

             else if ( x1_db>x_min_plot && x1_db<x_max_plot && y1_db>y_min_plot && y1_db<y_max_plot )
                     {
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

             else if ( x2_db>x_min_plot && x2_db<x_max_plot && y2_db>y_min_plot && y2_db<y_max_plot )
                     {
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
                          if ((x2_db - x1_db) == 0)
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
 fclose(fp_o);
}
/*------------------------------------------------------------------------*/
/*                         layerConrolCB()                                */
/*------------------------------------------------------------------------*/
void layercontrolCB()
{
 activateMenubar = 1 ;
 // wait_cursor()       ;
 move_fun = NONE     ;

 layer_control(MainForm) ;

}
/*------------------------------------------------------------------------*/
/*                             deleteCB()                                 */
/*------------------------------------------------------------------------*/
void deleteCB()
{
 activateMenubar = 1  ;
 // normal_cursor()      ;  /* cross hair enter/leave bug */

 draw_fun = DELETE    ;
 move_fun = CROSSHAIR ;

 xstr = XmStringCreate(" DELETE : Correlate on Feature",CS);
 XtSetArg(args[0], XmNlabelString ,  xstr);
 XtSetValues(output_label,args,1);
}
/*------------------------------------------------------------------------*/
/*                         networktraceCB()                               */
/*------------------------------------------------------------------------*/
void networktraceCB()
{
 activateMenubar = 1  ;

 if ( db_opened[0] != 'Y' )
    {
     xstr  = XmStringCreate("INFO",CS);
     xstr1 = XmStringCreate("No Database Connection found, Function Canceled",CS);

     n=0;
     XtSetArg(args[n] , XmNdialogTitle   ,        xstr);n++;
     XtSetArg(args[n] , XmNmessageString ,       xstr1);n++;
     //XtSetArg(args[n] , XmNwidth         ,         350);n++;
     //XtSetArg(args[n] , XmNheight        ,         130);n++;
     XtSetArg(args[n] , XmNborderColor   , white.pixel);n++;
     XtSetArg(args[n] , XmNforeground    , black.pixel);n++;
     XtSetArg(args[n] , XmNbackground    , lgray.pixel);n++;

     PD = XmCreateErrorDialog(MainForm,"PD",args,n);
     XtManageChild(PD);

     // normal_cursor();
     return ;
    }

 // normal_cursor()      ;  /* cross hair enter/leave bug */
 draw_fun = TRACE     ;
 move_fun = CROSSHAIR ;

 xstr = XmStringCreate(" TRACE : Correlate on Feature",CS);
 XtSetArg(args[0], XmNlabelString ,  xstr);
 XtSetValues(output_label,args,1);
}
/*------------------------------------------------------------------------*/
/*                         traceadjcentCB()                               */
/*------------------------------------------------------------------------*/
void traceadjcentCB()
{
 activateMenubar = 1  ;

 if ( db_opened[0] != 'Y' )
    {
     xstr  = XmStringCreate("INFO",CS);
     xstr1 = XmStringCreate("No Database Connection found, Function Canceled",CS);

     n=0;
     XtSetArg(args[n] , XmNdialogTitle   ,        xstr);n++;
     XtSetArg(args[n] , XmNmessageString ,       xstr1);n++;
     //XtSetArg(args[n] , XmNwidth         ,         350);n++;
     //XtSetArg(args[n] , XmNheight        ,         130);n++;
     XtSetArg(args[n] , XmNborderColor   , white.pixel);n++;
     XtSetArg(args[n] , XmNforeground    , black.pixel);n++;
     XtSetArg(args[n] , XmNbackground    , lgray.pixel);n++;

     PD = XmCreateErrorDialog(MainForm,"PD",args,n);
     XtManageChild(PD);

     // normal_cursor();
     return ;
    }

 // normal_cursor()      ;  /* cross hair enter/leave bug */
 draw_fun = TRACEADJ  ;
 move_fun = CROSSHAIR ;

 xstr = XmStringCreate(" TRACE ADJCENT : Correlate on Feature",CS);
 XtSetArg(args[0], XmNlabelString ,  xstr);
 XtSetValues(output_label,args,1);
}
/*------------------------------------------------------------------------*/
/*                         resettraceCB()                                 */
/*------------------------------------------------------------------------*/
void resettraceCB()
{
 activateMenubar = 1 ;
 // wait_cursor()       ;
 move_fun = NONE     ;


 if ( trace_on[0] == 'Y' )   /* Reset Trace only if Trace was ON */
    {
     for (i=1; i<=feat_count; i++)
         {
          feat[i].linetype = org_linetype[i] ;

          for (j=1; j<=conn_count; j++)
              {
               if (feat[i].num == conn_list[j] )
                  {
                   feat[i].linetype = org_linetype[i] ;
                  }
              }
         }
//     draw_all () ;
    }

 // normal_cursor() ;
}
/*------------------------------------------------------------------------*/
/*                              moveCB()                                  */
/*------------------------------------------------------------------------*/
void moveCB()
{
 activateMenubar = 1  ;
 // normal_cursor()      ;  /* cross hair enter/leave bug */

 draw_fun = MOVE      ;
 last_fun = MOVE      ;
 move_fun = CROSSHAIR ;
 point_counter = 1    ;

 xstr = XmStringCreate(" MOVE : Correlate on Feature",CS);
 XtSetArg(args[0], XmNlabelString ,  xstr);
 XtSetValues(output_label,args,1);
}
/*------------------------------------------------------------------------*/
/*                              splitCB()                                 */
/*------------------------------------------------------------------------*/
void splitCB()
{
 activateMenubar = 1  ;
 // normal_cursor()      ;  /* cross hair enter/leave bug */

 draw_fun = SPLIT     ;
 last_fun = SPLIT     ;
 move_fun = CROSSHAIR ;

 xstr = XmStringCreate(" SPLIT : Correlate on Feature",CS);
 XtSetArg(args[0], XmNlabelString ,  xstr);
 XtSetValues(output_label,args,1);
}
/*------------------------------------------------------------------------*/
/*                              joinCB()                                  */
/*------------------------------------------------------------------------*/
void joinCB()
{
 activateMenubar = 1  ;
 // normal_cursor()      ;  /* cross hair enter/leave bug */

 draw_fun = JOIN      ;
 move_fun = CROSSHAIR ;
 point_counter = 1    ;

 xstr = XmStringCreate(" JOIN : Correlate on Features to be joined",CS);
 XtSetArg(args[0], XmNlabelString ,  xstr);
 XtSetValues(output_label,args,1);
}
/*------------------------------------------------------------------------*/
/*                             locateCB()                                 */
/*------------------------------------------------------------------------*/
void locateCB()
{
 activateMenubar = 1 ;
 // wait_cursor()       ;
 move_fun = NONE     ;

 locate_point () ;

 // normal_cursor() ;
}
/*------------------------------------------------------------------------*/
/*                           transferCB()                                 */
/*------------------------------------------------------------------------*/
void transferCB()
{
 activateMenubar = 1 ;
 // wait_cursor()       ;
 move_fun = NONE     ;

 map_transfer()      ;

 // normal_cursor() ;
}
/*------------------------------------------------------------------------*/
/*                         projectionCB()                                 */
/*------------------------------------------------------------------------*/
void projectionCB()
{
 activateMenubar = 1 ;
 // wait_cursor()       ;
 move_fun = NONE     ;

 map_projection()    ;

 // normal_cursor() ;
}
/*------------------------------------------------------------------------*/
/*                             shortestpathCB()                           */
/*------------------------------------------------------------------------*/
void shortestpathCB()
{
 activateMenubar = 1 ;

 if ( db_opened[0] != 'Y' )
    {
     xstr  = XmStringCreate("INFO",CS);
     xstr1 = XmStringCreate("No Database Connection found, Function Canceled",CS);

     n=0;
     XtSetArg(args[n] , XmNdialogTitle   ,        xstr);n++;
     XtSetArg(args[n] , XmNmessageString ,       xstr1);n++;
     //XtSetArg(args[n] , XmNwidth         ,         350);n++;
     //XtSetArg(args[n] , XmNheight        ,         130);n++;
     XtSetArg(args[n] , XmNborderColor   , white.pixel);n++;
     XtSetArg(args[n] , XmNforeground    , black.pixel);n++;
     XtSetArg(args[n] , XmNbackground    , lgray.pixel);n++;

     PD = XmCreateErrorDialog(MainForm,"PD",args,n);
     XtManageChild(PD);

     // normal_cursor();
     return ;
    }

 draw_fun = SHORTPATH ;
 move_fun = CROSSHAIR ;

 node1         = 0    ;
 node2         = 0    ;
 point_counter = 1    ;

 xstr = XmStringCreate(" SHORTEST PATH : Select 2 points",CS);
 XtSetArg(args[0], XmNlabelString ,  xstr);
 XtSetValues(output_label,args,1);
}
/*------------------------------------------------------------------------*/
/*                             findstreetCB()                             */
/*------------------------------------------------------------------------*/
void findstreetCB()
{
 activateMenubar = 1 ;

 if ( db_opened[0] != 'Y' )
    {
     xstr  = XmStringCreate("INFO",CS);
     xstr1 = XmStringCreate("No Database Connection found, Function Canceled",CS);

     n=0;
     XtSetArg(args[n] , XmNdialogTitle   ,        xstr);n++;
     XtSetArg(args[n] , XmNmessageString ,       xstr1);n++;
     XtSetArg(args[n] , XmNborderColor   , white.pixel);n++;
     XtSetArg(args[n] , XmNforeground    , black.pixel);n++;
     XtSetArg(args[n] , XmNbackground    , lgray.pixel);n++;

     PD = XmCreateErrorDialog(MainForm,"PD",args,n);
     XtManageChild(PD);

     // normal_cursor();
     return ;
    }


 // wait_cursor()    ;
 move_fun = NONE  ;

 xstr  = XmStringCreate("Find Street",CS);
 xstr1 = XmStringCreate("aa",CS);
 n=0;
 XtSetArg(args[n] , XmNdialogTitle ,        xstr);n++;
 XtSetArg(args[n] , XmNtitle       ,       xstr1);n++;
 XtSetArg(args[n] , XmNwidth       ,         300);n++;
 XtSetArg(args[n] , XmNheight      ,         130);n++;
 XtSetArg(args[n] , XmNborderColor , white.pixel);n++;
 XtSetArg(args[n] , XmNforeground  , black.pixel);n++;
 XtSetArg(args[n] , XmNbackground  , lgray.pixel);n++;

 PD = XmCreatePromptDialog(MainForm,"PD",args,n);
 XtAddCallback(PD,XmNokCallback,findstreetOkCB,MainForm);
 XtAddCallback(PD,XmNcancelCallback,findstreetCancelCB,MainForm);
 XtManageChild(PD);

 /* keep the user on this dialog until it is accepted or canceled */
 XtAddGrab( PD,True,False );
}
/*------------------------------------------------------------------------*/
/*                         findstreetOkCB()                               */
/*------------------------------------------------------------------------*/
void findstreetOkCB(Widget w, caddr_t client_data, FSBCBS *call_data)
{
 char  *str                  ;
 int   street_stack[1000]    ;
 long  x_min_all = 900000000 ;
 long  y_min_all = 900000000 ;
 long  x_max_all = 0         ;
 long  y_max_all = 0         ;
 int   previous_symb         ;


 stack_count = 0 ;


 XmStringGetLtoR(call_data->value ,CS ,&str);

 strcpy(street_name, str);
 strcat(street_name, "%");
 printf("street name : %s \n", street_name);


 
/*
EXEC SQL DECLARE Find1  CURSOR FOR
          SELECT  FEAT_NUM
          FROM    STREET
          WHERE   NAME LIKE :street_name
          FOR     READ ONLY ;
*/

#line 7014 "geoIMS_main.sqc"


 
/*
EXEC SQL OPEN  Find1    ;
*/

{
#line 7016 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 7016 "geoIMS_main.sqc"
  sqlaaloc(2,1,44,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 7016 "geoIMS_main.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 51;
#line 7016 "geoIMS_main.sqc"
      sql_setdlist[0].sqldata = (void*)street_name;
#line 7016 "geoIMS_main.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 7016 "geoIMS_main.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 7016 "geoIMS_main.sqc"
  sqlacall((unsigned short)26,26,2,0,0L);
#line 7016 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 7016 "geoIMS_main.sqc"

 // CHECKERR ("OPEN CURSOR");



 do {
     
/*
EXEC SQL FETCH Find1 INTO :feat_num ;
*/

{
#line 7022 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 7022 "geoIMS_main.sqc"
  sqlaaloc(3,1,45,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 7022 "geoIMS_main.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 7022 "geoIMS_main.sqc"
      sql_setdlist[0].sqldata = (void*)&feat_num;
#line 7022 "geoIMS_main.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 7022 "geoIMS_main.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 7022 "geoIMS_main.sqc"
  sqlacall((unsigned short)25,26,0,3,0L);
#line 7022 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 7022 "geoIMS_main.sqc"

     if ( SQLCODE != 0    ) break    ;

     for (i=1 ; i<= feat_count ; i++)
         {
          if ( feat[i].num == feat_num )
             {
              street_stack[++stack_count] = i ;
              printf("feat num = %d \n",i);
             }
         }

    } while(1);

 
/*
EXEC SQL CLOSE Find1 ;
*/

{
#line 7036 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 7036 "geoIMS_main.sqc"
  sqlacall((unsigned short)20,26,0,0,0L);
#line 7036 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 7036 "geoIMS_main.sqc"



 /*...................................*/
 /*  Calculate Min & Max Coordinates  */
 /*...................................*/

 for ( i=1; i<=stack_count; i++ )
 {
  switch (feat[street_stack[i]].type)
  {
   case 1:    /*-------------- Exmain type one ------------------*/

    if (feat[street_stack[i]].xbase < x_min_all)  x_min_all = feat[street_stack[i]].xbase ;
    if (feat[street_stack[i]].ybase < y_min_all)  y_min_all = feat[street_stack[i]].ybase ;

    if (feat[street_stack[i]].xbase > x_max_all)  x_max_all = feat[street_stack[i]].xbase ;
    if (feat[street_stack[i]].ybase > y_max_all)  y_max_all = feat[street_stack[i]].ybase ;
    break ;

   case 2:    /*-------------- Exmain type two ------------------*/

    for ( ii=0; ii<=feat[street_stack[i]].xy_count; ii++ )
        {
         switch (ii)
             {
              case 0:
                 if (feat[street_stack[i]].xbase < x_min_all) x_min_all = feat[street_stack[i]].xbase ;
                 if (feat[street_stack[i]].ybase < y_min_all) y_min_all = feat[street_stack[i]].ybase ;
                 if (feat[street_stack[i]].xbase > x_max_all) x_max_all = feat[street_stack[i]].xbase ;
                 if (feat[street_stack[i]].ybase > y_max_all) y_max_all = feat[street_stack[i]].ybase ;

                 if (feat[street_stack[i]].xend < x_min_all)  x_min_all = feat[street_stack[i]].xend  ;  // Linux Bug fixing !!!!
                 if (feat[street_stack[i]].yend < y_min_all)  y_min_all = feat[street_stack[i]].yend  ;
                 if (feat[street_stack[i]].xend > x_max_all)  x_max_all = feat[street_stack[i]].xend  ;
                 if (feat[street_stack[i]].yend > y_max_all)  y_max_all = feat[street_stack[i]].yend  ;
                 break ;

              default:
                 if (x[feat[street_stack[i]].xy+ii] < x_min_all) x_min_all = x[feat[street_stack[i]].xy+ii] ;
                 if (y[feat[street_stack[i]].xy+ii] < y_min_all) y_min_all = y[feat[street_stack[i]].xy+ii] ;

                 if (x[feat[street_stack[i]].xy+ii] > x_max_all) x_max_all = x[feat[street_stack[i]].xy+ii] ;
                 if (y[feat[street_stack[i]].xy+ii] > y_max_all) y_max_all = y[feat[street_stack[i]].xy+ii] ;
                 break ;
             }
        }
    break ;
  }
 }

 x_min  = x_min_all ;
 y_min  = y_min_all ;
 x_max  = x_max_all ;
 y_max  = y_max_all ;



 /* ------------------------------------------- */
 /* check for xy_min & xy_max is the same point */
 /* ------------------------------------------- */

 if ( (x_min == x_max) && (y_min == y_max) )
    {
     scale = 500 ;
     switch (DB_UNIT)
          {
           case MM: y_diff = scale * ( SCREEN_CM / .1   ); break ;
           case CM: y_diff = scale * ( SCREEN_CM / 1    ); break ;
           case DM: y_diff = scale * ( SCREEN_CM / 10   ); break ;
           case  M: y_diff = scale * ( SCREEN_CM / 100  ); break ;
           case KM: y_diff = scale * ( SCREEN_CM / 1000 ); break ;
           default: y_diff = scale * ( SCREEN_CM / 100  );
                    fprintf(stderr,"ERROR : Data Base Unit not Defined\n");
                    break ;
          }
     x_center = ( x_max + x_min ) / 2  ;
     y_center = ( y_max + y_min ) / 2  ;

     x_min = x_center - ( y_diff / 2 ) ;
     y_min = y_center - ( y_diff / 2 ) ;
     x_max = x_center + ( y_diff / 2 ) ;
     y_max = y_center + ( y_diff / 2 ) ;
    }
 else
    {
     x_diff = x_max - x_min ;
     y_diff = y_max - y_min ;

     if (x_diff > y_diff)
        {
         xy_diff = (x_diff - y_diff) / 2 ;
         y_min   = y_min - xy_diff       ;
         y_max   = y_max + xy_diff       ;
        }

     if (y_diff > x_diff)
        {
         xy_diff = (y_diff - x_diff) / 2 ;
         x_min   = x_min - xy_diff       ;
         x_max   = x_max + xy_diff       ;
        }
    }


 /*.................................*/
 /*  Calculate Scale , Scale_range  */
 /*.................................*/
 ONE_PIXEL = (y_max - y_min) / (y_br_screen - y_ul_screen) ;
 tolerance = cursor_size * ONE_PIXEL ;

 y_diff = y_max - y_min ;
 switch (DB_UNIT)
      {
       case MM: scale = ( y_diff * .1   ) / SCREEN_CM ; break ;
       case CM: scale = ( y_diff * 1.   ) / SCREEN_CM ; break ;
       case DM: scale = ( y_diff * 10.  ) / SCREEN_CM ; break ;
       case  M: scale = ( y_diff * 100. ) / SCREEN_CM ; break ;
       case KM: scale = ( y_diff * 1000.) / SCREEN_CM ; break ;
       default: scale = ( y_diff * 100. ) / SCREEN_CM ;
                fprintf(stderr,"ERROR : Data Base Unit not Defined\n");
                break ;
      }


// draw_all();

 // Draw streets in Highlight Lines

 k = 0 ;
 for ( i=1; i<=stack_count; i++ )
     {
      printf("i = %d   street_stack[i] = %d  \n",i,street_stack[i]);
      highlight_feature (street_stack[i]);
     }

 // normal_cursor();
 display_scale();
}
/*------------------------------------------------------------------------*/
/*                             Bld_s_ConnectivityCB()                     */
/*------------------------------------------------------------------------*/
void bld_s_connectivityCB()
{
 activateMenubar = 1 ;

 if ( db_opened[0] != 'Y' )
    {
     xstr  = XmStringCreate("INFO",CS);
     xstr1 = XmStringCreate("No Database Connection found, Function Canceled",CS);

     n=0;
     XtSetArg(args[n] , XmNdialogTitle   ,        xstr);n++;
     XtSetArg(args[n] , XmNmessageString ,       xstr1);n++;
     XtSetArg(args[n] , XmNborderColor   , white.pixel);n++;
     XtSetArg(args[n] , XmNforeground    , black.pixel);n++;
     XtSetArg(args[n] , XmNbackground    , lgray.pixel);n++;

     PD = XmCreateErrorDialog(MainForm,"PD",args,n);
     XtManageChild(PD);

     // normal_cursor();
     return ;
    }

 draw_fun = BLD_STREET_CONN ;
 move_fun = CROSSHAIR ;

 node1         = 0     ;
 node2         = 0     ;
 point_counter = 1     ;

 xstr = XmStringCreate(" Build Connectivity : Select Arc, then 2 Nodes",CS);
 XtSetArg(args[0], XmNlabelString ,  xstr);
 XtSetValues(output_label,args,1);
}
/*------------------------------------------------------------------------*/
/*                           Bld_e_ConnectivityCB()                       */
/*------------------------------------------------------------------------*/
void bld_e_connectivityCB()
{
 activateMenubar = 1 ;

 if ( db_opened[0] != 'Y' )
    {
     xstr  = XmStringCreate("INFO",CS);
     xstr1 = XmStringCreate("No Database Connection found, Function Canceled",CS);

     n=0;
     XtSetArg(args[n] , XmNdialogTitle   ,        xstr);n++;
     XtSetArg(args[n] , XmNmessageString ,       xstr1);n++;
     //XtSetArg(args[n] , XmNwidth         ,         350);n++;
     //XtSetArg(args[n] , XmNheight        ,         130);n++;
     XtSetArg(args[n] , XmNborderColor   , white.pixel);n++;
     XtSetArg(args[n] , XmNforeground    , black.pixel);n++;
     XtSetArg(args[n] , XmNbackground    , lgray.pixel);n++;

     PD = XmCreateErrorDialog(MainForm,"PD",args,n);
     XtManageChild(PD);

     // normal_cursor();
     return ;
    }


 draw_fun = BLD_ELECTRIC_CONN ;
 move_fun = CROSSHAIR ;

 node1         = 0     ;
 node2         = 0     ;
 point_counter = 1     ;

 xstr = XmStringCreate(" Build Connectivity : Select Feeder, then 2 Substations",CS);
 XtSetArg(args[0], XmNlabelString ,  xstr);
 XtSetValues(output_label,args,1);
}
/*------------------------------------------------------------------------*/
/*                         scaleCancelCB()                                */
/*------------------------------------------------------------------------*/
void findstreetCancelCB(Widget w, caddr_t client_data, FSBCBS *call_data)
{
 // normal_cursor();
}
/*------------------------------------------------------------------------*/
/*                                 endCB()                                */
/*------------------------------------------------------------------------*/
void endCB()
{
 activateMenubar = 1 ;
 // wait_cursor()       ;
 move_fun = NONE     ;

 xstr  = XmStringCreate("End session Confirmation",CS);
 xstr1 = XmStringCreate("Are you sure ",CS);

 n=0;
 XtSetArg(args[n] , XmNdialogTitle   ,        xstr);n++;
 XtSetArg(args[n] , XmNmessageString ,       xstr1);n++;
 XtSetArg(args[n] , XmNwidth         ,         300);n++;
 XtSetArg(args[n] , XmNheight        ,         130);n++;
 XtSetArg(args[n] , XmNborderColor   , white.pixel);n++;
 XtSetArg(args[n] , XmNforeground    , black.pixel);n++;
 XtSetArg(args[n] , XmNbackground    , lgray.pixel);n++;

 PD = XmCreateQuestionDialog(MainForm,"PD",args,n);
 XtAddCallback(PD,XmNokCallback,endOkCB,MainForm);
 XtAddCallback(PD,XmNcancelCallback,endCancelCB,MainForm);
 XtManageChild(PD);

 /* keep the user on this dialog until it is accepted or canceled */
 XtAddGrab( PD,True,False );
}
/*------------------------------------------------------------------------*/
/*                               endOKCB()                                */
/*------------------------------------------------------------------------*/
void endOkCB()
{
 if ( db_opened[0] == 'Y' )
    {
     
/*
EXEC SQL CONNECT RESET;
*/

{
#line 7295 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 7295 "geoIMS_main.sqc"
  sqlacall((unsigned short)29,3,0,0,0L);
#line 7295 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 7295 "geoIMS_main.sqc"

     // CHECKERR ("CONNECT RESET");
    }

 done = 1 ;
}
/*------------------------------------------------------------------------*/
/*                          endCancelCB()                                 */
/*------------------------------------------------------------------------*/
void endCancelCB()
{
 // normal_cursor();
}
/*------------------------------------------------------------------------*/
/*                          button_moveCB()   Not Used !!                 */
/*------------------------------------------------------------------------*/
/* void button_moveCB(Widget w, Data *data, XEvent *event) */
void button_moveCB(Widget w, XtPointer Data, XEvent *event)
{
/*
 data->x1=event->xbutton.x ;
 data->y1=event->xbutton.y ;
 data->x2=event->xbutton.x ;
 data->y2=event->xbutton.y ;
*/
 switch(event->xmotion.state)
  {
   case Button1MotionMask:
     /*
     data->x2 = event->xbutton.x ;
    data->y2 = event->xbutton.y ;
    XDrawLine(MainDisplay,XtWindow(w),copy_gc,data->x1,data->y1,data->x2,data->y2);
    XDrawPoint(MainDisplay,XtWindow(w),copy_gc,data->x2,data->y2);
    data->x1 = data->x2 ;
    data->y1 = data->y2 ;
    */
    break ;

  case Button3MotionMask:
    /*
    XDrawLine(MainDisplay,XtWindow(w),copy_gc,data->x1,data->y1,data->x2,data->y2);
    data->x2 = event->xbutton.x ;
    data->y2 = event->xbutton.y ;
    XDrawLine(MainDisplay,XtWindow(w),copy_gc,data->x1,data->y1,data->x2,data->y2);
    */
    break ;

  case Button2MotionMask:
    /* XClearWindow(MainDisplay,XtWindow(w)) ; */
    break ;
  }
}

/*------------------------------------------------------------------------*/
/*                               zwin()                                   */
/*------------------------------------------------------------------------*/
void zwin ()
{

 draw_fun = WINDOW    ;
 move_fun = CROSSHAIR ;
 point_counter = 1    ;

 xstr = XmStringCreate(" WINDOW : Select 2 points",CS);
 XtSetArg(args[0], XmNlabelString, xstr);
 XtSetValues(output_label,args,1);
}


/*------------------------------------------------------------------------*/
/*                             draw_symb()                                */
/*------------------------------------------------------------------------*/
void draw_symb(symb_no,x_base,y_base,color,size,angle1)
{

 XSetForeground(MainDisplay,copy_gc,color);

 symb_factor = (float)size / symb[symb_no].grid ;
 angle  = (float)angle1 / DEG2RAD ;

 for ( ii=1; ii<=symb[symb_no].stroke; ii++)
   {
    switch (symb[symb_no].mv_draw[ii])
     {
      case 0:     /*  Move  */

        angle_sym = symb[symb_no].angle[ii] + angle ;
        x1_screen = (x_base - x_min  + symb_factor * symb[symb_no].distance[ii] * cos(angle_sym)) / ONE_PIXEL ;
        y1_screen = (y_max  - y_base - symb_factor * symb[symb_no].distance[ii] * sin(angle_sym)) / ONE_PIXEL ;

        break ;

      case 1:     /*  Draw  */

        angle_sym = symb[symb_no].angle[ii] + angle ;
        x2_screen = (x_base - x_min  + symb_factor * symb[symb_no].distance[ii] * cos(angle_sym)) / ONE_PIXEL ;
        y2_screen = (y_max  - y_base - symb_factor * symb[symb_no].distance[ii] * sin(angle_sym)) / ONE_PIXEL ;

        XDrawLine(MainDisplay,XtWindow(drawarea),copy_gc,x1_screen,y1_screen,x2_screen,y2_screen);
        XDrawLine(MainDisplay,Tile,copy_gc,x1_screen,y1_screen,x2_screen,y2_screen);

        x1_screen = x2_screen ;
        y1_screen = y2_screen ;

        break ;

      default:    /* Do nothing */
        break ;
     }
  }
}
/*------------------------------------------------------------------------*/
/*                          draw_pix_symb()                               */
/*------------------------------------------------------------------------*/
void draw_pix_symb(int symb_no,int x_screen,int y_screen, int color,double p_size,int p_angle)
{
 long x1_screen , y1_screen ;
 long x2_screen , y2_screen ;


 XSetForeground(MainDisplay,copy_gc,color);

 symb_factor = (float)p_size / symb[symb_no].grid ;
 angle  = (float)p_angle / DEG2RAD ;

 for ( ii=1; ii<=symb[symb_no].stroke; ii++)
     {
      switch (symb[symb_no].mv_draw[ii])
      {
       case 0:     /*  Move  */

        angle_sym = symb[symb_no].angle[ii] + angle ;
        x1_screen = x_screen + symb_factor * symb[symb_no].distance[ii] * cos(angle_sym) / ONE_PIXEL ;
        y1_screen = y_screen - symb_factor * symb[symb_no].distance[ii] * sin(angle_sym) / ONE_PIXEL ;
        break ;

       case 1:     /*  Draw  */

        angle_sym = symb[symb_no].angle[ii] + angle ;
        x2_screen = x_screen + symb_factor * symb[symb_no].distance[ii] * cos(angle_sym) / ONE_PIXEL ;
        y2_screen = y_screen - symb_factor * symb[symb_no].distance[ii] * sin(angle_sym) / ONE_PIXEL ;

        XDrawLine(MainDisplay,XtWindow(drawarea),copy_gc,x1_screen,y1_screen,x2_screen,y2_screen);
        XDrawLine(MainDisplay,Tile,copy_gc,x1_screen,y1_screen,x2_screen,y2_screen);

        x1_screen = x2_screen ;
        y1_screen = y2_screen ;
        break ;

       default:    /* Do nothing */
        break ;
     }
  }
//  cls_flag = 1 ;
//  XCopyArea(MainDisplay,Tile,XtWindow(drawarea),Tilegc,0,0,999,999,0,0);
}
/*------------------------------------------------------------------------*/
/*                        xor_draw_pix_symb()                             */
/*------------------------------------------------------------------------*/
void xor_draw_pix_symb(int symb_no,int x_screen,int y_screen, int color,double p_size,int p_angle)
{
 long x1_screen , y1_screen ;
 long x2_screen , y2_screen ;


 // XSetForeground(MainDisplay,xor_gc,color);

 symb_factor = (float)p_size / symb[symb_no].grid ;
 angle  = (float)p_angle / DEG2RAD ;

 for ( ii=1; ii<=symb[symb_no].stroke; ii++)
     {
      switch (symb[symb_no].mv_draw[ii])
      {
       case 0:     /*  Move  */

        angle_sym = symb[symb_no].angle[ii] + angle ;
        x1_screen = x_screen + symb_factor * symb[symb_no].distance[ii] * cos(angle_sym) / ONE_PIXEL ;
        y1_screen = y_screen - symb_factor * symb[symb_no].distance[ii] * sin(angle_sym) / ONE_PIXEL ;
        break ;

       case 1:     /*  Draw  */

        angle_sym = symb[symb_no].angle[ii] + angle ;
        x2_screen = x_screen + symb_factor * symb[symb_no].distance[ii] * cos(angle_sym) / ONE_PIXEL ;
        y2_screen = y_screen - symb_factor * symb[symb_no].distance[ii] * sin(angle_sym) / ONE_PIXEL ;

        XDrawLine(MainDisplay,XtWindow(drawarea),xor_gc,x1_screen,y1_screen,x2_screen,y2_screen);
        XDrawLine(MainDisplay,Tile,xor_gc,x1_screen,y1_screen,x2_screen,y2_screen);

        x1_screen = x2_screen ;
        y1_screen = y2_screen ;
        break ;

       default:    /* Do nothing */
        break ;
     }
  }
}
/*------------------------------------------------------------------------*/
/*                             draw_text()                                */
/*------------------------------------------------------------------------*/
void draw_text(x_screen,y_screen,color,size,text_index,angle1)
{
 int    i  ;
 int    ii ;
 int    length ;
 int    previous_symb ;
 double x_db ;
 double y_db ;

 XSetForeground(MainDisplay,copy_gc,color);

 x_db =text[text_index].x - x_min  ;
 y_db =y_max - text[text_index].y  ;

 font_no = text[text_index].font                    ;
 length  = strlen (text[text_index].string) -1      ;
 angle   = (double)text[text_index].angle / DEG2RAD ;


 switch (text[text_index].just)
        {
         case 1:
                /* Bottom */
                x_db -= (size/2) * sin(angle);
                y_db -= (size/2) * cos(angle);

                /* Left */
                x_db += (size/2) * cos(angle);
                y_db -= (size/2) * sin(angle);
                break;

         case 2:
                /* Bottom */
                x_db -= (size/2) * sin(angle);
                y_db -= (size/2) * cos(angle);

                /* Center */
                x_db -= (length*size/2) * cos(angle);
                y_db += (length*size/2) * sin(angle);
                break;

         case 3:
                /* Bottom */
                x_db -= (size/2) * sin(angle);
                y_db -= (size/2) * cos(angle);

                /* Right  */
                x_db -= (length*size) * cos(angle);
                y_db += (length*size) * sin(angle);
                break;

         case 4:
                /* Middle */
                /* Left   */
                x_db += (size/2) * cos(angle);
                y_db -= (size/2) * sin(angle);
                break;

         case 5:
                /* Middle */

                /* Center */
                x_db -= (length*size/2) * cos(angle);
                y_db += (length*size/2) * sin(angle);
                break;

         case 6:
                /* Middle */

                /* Right  */
                x_db -= (length*size) * cos(angle);
                y_db += (length*size) * sin(angle);
                break;

         case 7:
                /* Top */
                x_db += (size/2) * sin(angle);
                y_db += (size/2) * cos(angle);

                /* Left */
                x_db += (size/2) * cos(angle);
                y_db -= (size/2) * sin(angle);
                break;

         case 8:
                /* Top */
                x_db += (size/2) * sin(angle);
                y_db += (size/2) * cos(angle);

                /* Center */
                x_db -= (length*size/2) * cos(angle);
                y_db += (length*size/2) * sin(angle);
                break;

         case 9:
                /* Top */
                x_db += (size/2) * sin(angle);
                y_db += (size/2) * cos(angle);

                /* Right  */
                x_db -= (length*size) * cos(angle);
                y_db += (length*size) * sin(angle);
                break;
        }



 for (i=0; i<=length ; i++)
 {
  symb_no     = 0 ;
  // symb_no     = text[text_index].string[i]  ;
  symb_no     = 135 ; // hany heggy testing arabic letters
  symb_factor = (float)size / font[font_no][symb_no].grid ;

 printf("\n font number [%d]  symb_no [%d] \n",font_no,symb_no);

  if ( i != 0 )
     {
      previous_symb = text[text_index].string[i-1] ;
      x_db += size * font[font_no][previous_symb].x_factor * cos(angle) ;
      y_db -= size * font[font_no][previous_symb].x_factor * sin(angle) ;

      /* x_db += size * cos(angle) ;
         y_db -= size * sin(angle) ; */
     }


  for ( ii=1; ii<=font[font_no][symb_no].stroke; ii++)
    {
     switch (font[font_no][symb_no].mv_draw[ii])
     {
      case 0:     /*  Move  */

        angle_sym = font[font_no][symb_no].angle[ii] + angle ;
        x1_screen = (x_db + symb_factor * font[font_no][symb_no].distance[ii] * cos(angle_sym))/ONE_PIXEL;
        y1_screen = (y_db - symb_factor * font[font_no][symb_no].distance[ii] * sin(angle_sym))/ONE_PIXEL;
        break ;

      case 1:     /*  Draw  */

        angle_sym = font[font_no][symb_no].angle[ii] + angle ;
        x2_screen = (x_db + symb_factor * font[font_no][symb_no].distance[ii] * cos(angle_sym))/ONE_PIXEL;
        y2_screen = (y_db - symb_factor * font[font_no][symb_no].distance[ii] * sin(angle_sym))/ONE_PIXEL;

        XDrawLine(MainDisplay,XtWindow(drawarea),copy_gc,x1_screen,y1_screen,x2_screen,y2_screen);
        XDrawLine(MainDisplay,Tile,copy_gc,x1_screen,y1_screen,x2_screen,y2_screen);

        x1_screen = x2_screen ;
        y1_screen = y2_screen ;
        break ;

      default:    /* Do nothing */
        break ;
     }
    }
  }
}
/*------------------------------------------------------------------------*/
/*                             draw_text_mask()                           */
/*------------------------------------------------------------------------*/
void draw_text_mask(x_screen,y_screen,color,size,text_index,angle1)
{
 int    i  ;
 int    ii ;
 int    length ;
 int    previous_symb ;
 double x_db ;
 double y_db ;

 XSetForeground(MainDisplay,xor_gc,color);

 x_db =text[text_index].x - x_min  ;
 y_db =y_max - text[text_index].y  ;

 font_no = text[text_index].font                    ;
 length  = strlen (text[text_index].string) -1      ;
 angle   = (double)text[text_index].angle / DEG2RAD ;


 switch (text[text_index].just)
        {
         case 1:
                /* Bottom */
                x_db -= (size/2) * sin(angle);
                y_db -= (size/2) * cos(angle);

                /* Left */
                x_db += (size/2) * cos(angle);
                y_db -= (size/2) * sin(angle);
                break;

         case 2:
                /* Bottom */
                x_db -= (size/2) * sin(angle);
                y_db -= (size/2) * cos(angle);

                /* Center */
                x_db -= (length*size/2) * cos(angle);
                y_db += (length*size/2) * sin(angle);
                break;

         case 3:
                /* Bottom */
                x_db -= (size/2) * sin(angle);
                y_db -= (size/2) * cos(angle);

                /* Right  */
                x_db -= (length*size) * cos(angle);
                y_db += (length*size) * sin(angle);
                break;

         case 4:
                /* Middle */
                /* Left   */
                x_db += (size/2) * cos(angle);
                y_db -= (size/2) * sin(angle);
                break;

         case 5:
                /* Middle */

                /* Center */
                x_db -= (length*size/2) * cos(angle);
                y_db += (length*size/2) * sin(angle);
                break;

         case 6:
                /* Middle */

                /* Right  */
                x_db -= (length*size) * cos(angle);
                y_db += (length*size) * sin(angle);
                break;

         case 7:
                /* Top */
                x_db += (size/2) * sin(angle);
                y_db += (size/2) * cos(angle);

                /* Left */
                x_db += (size/2) * cos(angle);
                y_db -= (size/2) * sin(angle);
                break;

         case 8:
                /* Top */
                x_db += (size/2) * sin(angle);
                y_db += (size/2) * cos(angle);

                /* Center */
                x_db -= (length*size/2) * cos(angle);
                y_db += (length*size/2) * sin(angle);
                break;

         case 9:
                /* Top */
                x_db += (size/2) * sin(angle);
                y_db += (size/2) * cos(angle);

                /* Right  */
                x_db -= (length*size) * cos(angle);
                y_db += (length*size) * sin(angle);
                break;
        }



 for (i=0; i<=length ; i++)
 {
  symb_no     = 0 ;
  symb_no     = text[text_index].string[i] ;
  symb_factor = (float)size / font[font_no][symb_no].grid ;

  if ( i != 0 )
     {
      previous_symb = text[text_index].string[i-1] ;
      x_db += size * font[font_no][previous_symb].x_factor * cos(angle) ;
      y_db -= size * font[font_no][previous_symb].x_factor * sin(angle) ;

      /* x_db += size * cos(angle) ;
         y_db -= size * sin(angle) ; */
     }


  for ( ii=1; ii<=font[font_no][symb_no].stroke; ii++)
    {
     switch (font[font_no][symb_no].mv_draw[ii])
     {
      case 0:     /*  Move  */

        angle_sym = font[font_no][symb_no].angle[ii] + angle ;
        x1_screen = (x_db + symb_factor * font[font_no][symb_no].distance[ii] * cos(angle_sym))/ONE_PIXEL;
        y1_screen = (y_db - symb_factor * font[font_no][symb_no].distance[ii] * sin(angle_sym))/ONE_PIXEL;
        break ;

      case 1:     /*  Draw  */

        angle_sym = font[font_no][symb_no].angle[ii] + angle ;
        x2_screen = (x_db + symb_factor * font[font_no][symb_no].distance[ii] * cos(angle_sym))/ONE_PIXEL;
        y2_screen = (y_db - symb_factor * font[font_no][symb_no].distance[ii] * sin(angle_sym))/ONE_PIXEL;

        XDrawLine(MainDisplay,XtWindow(drawarea),xor_gc,x1_screen,y1_screen,x2_screen,y2_screen);
        XDrawLine(MainDisplay,Tile              ,xor_gc,x1_screen,y1_screen,x2_screen,y2_screen);

        x1_screen = x2_screen ;
        y1_screen = y2_screen ;
        break ;

      default:    /* Do nothing */
        break ;
     }
    }
  }
}
/*------------------------------------------------------------------------*/
/*                             draw_line()                                */
/*------------------------------------------------------------------------*/
void draw_line(int feat_parm, int color_parm)
{
 int i,ii, color ;

 i     = feat_parm  ;
 color = color_parm ;

 x_base = feat[i].xbase ;
 y_base = feat[i].ybase ;
 x_end  = feat[i].xend  ;
 y_end  = feat[i].yend  ;

 XSetForeground(MainDisplay,copy_gc, color);

 for ( ii=0 ; ii<=(feat[i].xy_count+1) ; ii++ )
     {
      switch (ii)
         {
          case 0:
               x1_db = x_base ;
               y1_db = y_base ;

               x1_screen = (x1_db - x_min) / ONE_PIXEL ;
               y1_screen = (y_max - y1_db) / ONE_PIXEL ;
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

               x2_screen = (x2_db - x_min) / ONE_PIXEL ;
               y2_screen = (y_max - y2_db) / ONE_PIXEL ;


               if (( x1_db>=x_min && x1_db<=x_max && y1_db>=y_min && y1_db<=y_max ) &&
                   ( x2_db>=x_min && x2_db<=x_max && y2_db>=y_min && y2_db<=y_max ) )
                  {
                   XDrawLine(MainDisplay,XtWindow(drawarea),copy_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                   XDrawLine(MainDisplay,Tile              ,copy_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                  }

          else if ( x1_db>=x_min && x1_db<=x_max && y1_db>=y_min && y1_db<=y_max )
                  {
                   if ( x1_db == x2_db )   /* VL Segment */
                      {
                       if ( y2_db > y1_db )
                          {
                           x2_screen = (x2_db - x_min) / ONE_PIXEL;
                           y2_screen = (y_max - y_max) / ONE_PIXEL;
                          }
                        else
                          {
                           x2_screen = (x2_db - x_min) / ONE_PIXEL ;
                           y2_screen = (y_max - y_min) / ONE_PIXEL ;
                          }
                       XDrawLine(MainDisplay,XtWindow(drawarea),copy_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                       XDrawLine(MainDisplay,Tile,copy_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                       goto end ;
                      }

                   if ( y1_db == y2_db )    /* HZ Segment */
                      {
                       if ( x2_db > x1_db )
                          {
                           x2_screen = (x_max - x_min) / ONE_PIXEL ;
                           y2_screen = (y_max - y2_db) / ONE_PIXEL ;
                          }
                        else
                          {
                           x2_screen = (x_min - x_min) / ONE_PIXEL ;
                           y2_screen = (y_max - y2_db) / ONE_PIXEL ;
                          }
                       XDrawLine(MainDisplay,XtWindow(drawarea),copy_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                       XDrawLine(MainDisplay,Tile,copy_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                       goto end ;
                      }

                   b = (y2_db - y1_db)/(x2_db - x1_db) ;
                   a = y1_db - (b * x1_db) ;

                   x_bot   = (y_min - a) / b ;
                   x_top   = (y_max - a) / b ;
                   y_left  = a + (b * x_min) ;
                   y_right = a + (b * x_max) ;

                   if ((x_bot>x_min && x_bot<x_max) &&
                      ((x_bot>x1_db && x_bot<x2_db) || (x_bot>x2_db && x_bot<x1_db)))
                      {
                       x2_screen = (x_bot - x_min) / ONE_PIXEL  ;
                       y2_screen = (y_max - y_min) / ONE_PIXEL ;
                       XDrawLine(MainDisplay,XtWindow(drawarea),copy_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                       XDrawLine(MainDisplay,Tile,copy_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                      }
              else if ((x_top>x_min && x_top<x_max) &&
                      ((x_top>x1_db && x_top<x2_db) || (x_top>x2_db && x_top<x1_db)))
                      {
                       x2_screen = (x_top - x_min) / ONE_PIXEL ;
                       y2_screen = (y_max - y_max) / ONE_PIXEL ;
                       XDrawLine(MainDisplay,XtWindow(drawarea),copy_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                       XDrawLine(MainDisplay,Tile,copy_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                      }
              else if ((y_left>y_min && y_left<y_max) &&
                      ((y_left>y1_db && y_left<y2_db) || (y_left>y2_db && y_left<y1_db)))
                      {
                       x2_screen = (x_min - x_min ) / ONE_PIXEL ;
                       y2_screen = (y_max - y_left) / ONE_PIXEL ;
                       XDrawLine(MainDisplay,XtWindow(drawarea),copy_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                       XDrawLine(MainDisplay,Tile,copy_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                      }
              else if ((y_right>y_min && y_right<y_max) &&
                      ((y_right>y1_db && y_right<y2_db) || (y_right>y2_db && y_right<y1_db)))
                      {
                       x2_screen = (x_max - x_min  ) / ONE_PIXEL ;
                       y2_screen = (y_max - y_right) / ONE_PIXEL ;
                       XDrawLine(MainDisplay,XtWindow(drawarea),copy_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                       XDrawLine(MainDisplay,Tile,copy_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                      }
                  }

          else if ( x2_db>=x_min && x2_db<=x_max && y2_db>=y_min && y2_db<=y_max )
                  {
                   if ( x1_db == x2_db )   /* VL Segment */
                      {
                       if ( y1_db > y2_db )
                          {
                           x1_screen = (x1_db - x_min) / ONE_PIXEL ;
                           y1_screen = (y_max - y_max) / ONE_PIXEL ;
                          }
                        else
                          {
                           x1_screen = (x1_db - x_min) / ONE_PIXEL ;
                           y1_screen = (y_max - y_min) / ONE_PIXEL ;
                          }
                       XDrawLine(MainDisplay,XtWindow(drawarea),copy_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                       XDrawLine(MainDisplay,Tile,copy_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                       goto end ;
                      }

                   if ( y1_db == y2_db )    /* HZ Segment */
                      {
                       if ( x1_db > x2_db )
                          {
                           x1_screen = (x_max - x_min) / ONE_PIXEL ;
                           y1_screen = (y_max - y1_db) / ONE_PIXEL ;
                          }
                        else
                          {
                           x1_screen = (x_min - x_min) / ONE_PIXEL ;
                           y1_screen = (y_max - y1_db) / ONE_PIXEL ;
                          }
                       XDrawLine(MainDisplay,XtWindow(drawarea),copy_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                       XDrawLine(MainDisplay,Tile,copy_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                       goto end ;
                      }

                   b = (y2_db - y1_db)/(x2_db - x1_db) ;
                   a = y1_db - (b * x1_db) ;

                   x_bot   = (y_min - a) / b ;
                   x_top   = (y_max - a) / b ;
                   y_left  = a + (b * x_min) ;
                   y_right = a + (b * x_max) ;

                   if ((x_bot>x_min && x_bot<x_max) &&
                      ((x_bot>x1_db && x_bot<x2_db) || (x_bot>x2_db && x_bot<x1_db)))
                      {
                       x1_screen = (x_bot - x_min) / ONE_PIXEL ;
                       y1_screen = (y_max - y_min) / ONE_PIXEL ;
                       XDrawLine(MainDisplay,XtWindow(drawarea),copy_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                       XDrawLine(MainDisplay,Tile,copy_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                      }
              else if ((x_top>x_min && x_top<x_max) &&
                      ((x_top>x1_db && x_top<x2_db) || (x_top>x2_db && x_top<x1_db)))
                      {
                       x1_screen = (x_top - x_min) / ONE_PIXEL ;
                       y1_screen = (y_max - y_max) / ONE_PIXEL ;
                       XDrawLine(MainDisplay,XtWindow(drawarea),copy_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                       XDrawLine(MainDisplay,Tile,copy_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                      }
              else if ((y_left>y_min && y_left<y_max) &&
                      ((y_left>y1_db && y_left<y2_db) || (y_left>y2_db && y_left<y1_db)))
                      {
                       x1_screen = (x_min - x_min ) / ONE_PIXEL ;
                       y1_screen = (y_max - y_left) / ONE_PIXEL ;
                       XDrawLine(MainDisplay,XtWindow(drawarea),copy_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                       XDrawLine(MainDisplay,Tile,copy_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                      }
              else if ((y_right>y_min && y_right<y_max) &&
                      ((y_right>y1_db && y_right<y2_db) || (y_right>y2_db && y_right<y1_db)))
                      {
                       x1_screen = (x_max - x_min  ) / ONE_PIXEL ;
                       y1_screen = (y_max - y_right) / ONE_PIXEL ;
                       XDrawLine(MainDisplay,XtWindow(drawarea),copy_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                       XDrawLine(MainDisplay,Tile,copy_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                      }
                  }
              else
                  {
                   b = (y2_db - y1_db)/(x2_db - x1_db) ;
                   a = y1_db - (b * x1_db) ;

                   /* --------------------- CASE I ----------------------- */
                   if ((y1_db < y_min && y2_db > y_max) || (y2_db < y_min && y1_db > y_max))
                      {
                       if ( x2_db == x1_db )  /* VL Segment */
                          {
                           x1_clip = x1_db ;  y1_clip = y_min ;
                           x2_clip = x2_db ;  y2_clip = y_max ;

                           x1_screen = (x1_clip - x_min) / ONE_PIXEL ;
                           y1_screen = (y_max - y1_clip) / ONE_PIXEL ;
                           x2_screen = (x2_clip - x_min) / ONE_PIXEL ;
                           y2_screen = (y_max - y2_clip) / ONE_PIXEL ;
                           XDrawLine(MainDisplay,XtWindow(drawarea),copy_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                           XDrawLine(MainDisplay,Tile,copy_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                           goto end ;
                          }

                       x_bot = (y_min - a) / b ;
                       x_top = (y_max - a) / b ;

                       if (x_bot > x_min && x_bot < x_max)
                          {
                           x1_clip = x_bot ;
                           y1_clip = y_min ;
                          }
                       else
                          { goto next2 ; }

                       if (x_top  > x_min && x_top  < x_max)
                          {
                           x2_clip = x_top ;
                           y2_clip = y_max ;

                           x1_screen = (x1_clip - x_min) / ONE_PIXEL ;
                           y1_screen = (y_max - y1_clip) / ONE_PIXEL ;
                           x2_screen = (x2_clip - x_min) / ONE_PIXEL ;
                           y2_screen = (y_max - y2_clip) / ONE_PIXEL ;
                           XDrawLine(MainDisplay,XtWindow(drawarea),copy_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                           XDrawLine(MainDisplay,Tile,copy_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                           goto end ;
                          }
                      }
                   next2:
                   /* --------------------- CASE II ---------------------- */
                   if ((x1_db < x_min && x2_db > x_max) || (x2_db < x_min && x1_db > x_max))
                      {
                       y_left  = a + (b * x_min) ;
                       y_right = a + (b * x_max) ;

                       if (y_left > y_min && y_left < y_max)
                          {
                           x1_clip = x_min  ;
                           y1_clip = y_left ;
                          }
                       else
                          { goto next3 ; }

                       if (y_right > y_min && y_right < y_max)
                          {
                           x2_clip = x_max   ;
                           y2_clip = y_right ;

                           x1_screen = (x1_clip - x_min) / ONE_PIXEL ;
                           y1_screen = (y_max - y1_clip) / ONE_PIXEL ;
                           x2_screen = (x2_clip - x_min) / ONE_PIXEL ;
                           y2_screen = (y_max - y2_clip) / ONE_PIXEL ;
                           XDrawLine(MainDisplay,XtWindow(drawarea),copy_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                           XDrawLine(MainDisplay,Tile,copy_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                           goto end ;
                          }
                      }
                   next3:
                   /* --------------------- CASE III --------------------- */
                   if ((y1_db < y_min && x2_db > x_max) || (y2_db < y_min && x1_db > x_max))
                      {
                       x_bot   = (y_min - a) / b ;
                       y_right = a + (b * x_max) ;

                       if (x_bot > x_min && x_bot < x_max)
                          {
                           x1_clip = x_bot ;
                           y1_clip = y_min ;
                          }
                       else
                          { goto next4 ; }

                       if (y_right > y_min && y_right < y_max)
                          {
                           x2_clip = x_max   ;
                           y2_clip = y_right ;

                           x1_screen = (x1_clip - x_min) / ONE_PIXEL ;
                           y1_screen = (y_max - y1_clip) / ONE_PIXEL ;
                           x2_screen = (x2_clip - x_min) / ONE_PIXEL ;
                           y2_screen = (y_max - y2_clip) / ONE_PIXEL ;
                           XDrawLine(MainDisplay,XtWindow(drawarea),copy_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                           XDrawLine(MainDisplay,Tile,copy_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                           goto end ;
                          }
                      }
                   next4:
                   /* --------------------- CASE IV ---------------------- */
                   if ((y1_db < y_min && x2_db < x_min) || (y2_db < y_min && x1_db < x_min))
                      {
                       x_bot  = (y_min - a) / b ;
                       y_left = a + (b * x_min) ;

                       if (x_bot > x_min && x_bot < x_max)
                          {
                           x1_clip = x_bot ;
                           y1_clip = y_min ;
                          }
                       else
                          { goto next5 ; }

                       if (y_left > y_min && y_left < y_max)
                          {
                           x2_clip = x_min   ;
                           y2_clip = y_left  ;

                           x1_screen = (x1_clip - x_min) / ONE_PIXEL ;
                           y1_screen = (y_max - y1_clip) / ONE_PIXEL ;
                           x2_screen = (x2_clip - x_min) / ONE_PIXEL ;
                           y2_screen = (y_max - y2_clip) / ONE_PIXEL ;
                           XDrawLine(MainDisplay,XtWindow(drawarea),copy_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                           XDrawLine(MainDisplay,Tile,copy_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                           goto end ;
                          }
                      }
                   next5:
                   /* --------------------- CASE V ----------------------- */
                   if ((y2_db > y_max && x1_db > x_max) || (y1_db > y_max && x2_db > x_max))
                      {
                       x_top   = (y_max - a) / b ;
                       y_right = a + (b * x_max) ;

                       if (x_top  > x_min && x_top  < x_max)
                          {
                           x1_clip = x_top ;
                           y1_clip = y_max ;
                          }
                       else
                          { goto next6 ; }

                       if (y_right > y_min && y_right < y_max)
                          {
                           x2_clip = x_max   ;
                           y2_clip = y_right ;

                           x1_screen = (x1_clip - x_min) / ONE_PIXEL ;
                           y1_screen = (y_max - y1_clip) / ONE_PIXEL ;
                           x2_screen = (x2_clip - x_min) / ONE_PIXEL ;
                           y2_screen = (y_max - y2_clip) / ONE_PIXEL ;
                           XDrawLine(MainDisplay,XtWindow(drawarea),copy_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                           XDrawLine(MainDisplay,Tile,copy_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                           goto end ;
                          }
                      }
                   next6:
                   /* --------------------- CASE VI ---------------------- */
                   if ((y2_db > y_max && x1_db < x_min) || (y1_db > y_max && x2_db < x_min))
                      {
                       x_top  = (y_max - a) / b ;
                       y_left = a + (b * x_min) ;

                       if (x_top  > x_min && x_top  < x_max)
                          {
                           x1_clip = x_top ;
                           y1_clip = y_max ;
                          }
                       else
                          { goto end ; }

                       if (y_left > y_min && y_left < y_max)
                          {
                           x2_clip = x_min   ;
                           y2_clip = y_left  ;

                           x1_screen = (x1_clip - x_min) / ONE_PIXEL ;
                           y1_screen = (y_max - y1_clip) / ONE_PIXEL ;
                           x2_screen = (x2_clip - x_min) / ONE_PIXEL ;
                           y2_screen = (y_max - y2_clip) / ONE_PIXEL ;
                           XDrawLine(MainDisplay,XtWindow(drawarea),copy_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                           XDrawLine(MainDisplay,Tile,copy_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                           goto end ;
                          }
                      }

                  }

                end:

                x1_db = x[feat[i].xy+ii] ;
                y1_db = y[feat[i].xy+ii] ;

                x1_screen = x2_screen ;
                y1_screen = y2_screen ;
                break ;
         }
     }

}
/*------------------------------------------------------------------------*/
/*                          update_layer()                                */
/*------------------------------------------------------------------------*/
void update_layer()
{
 int  found    ;
 int  layer_id ;

 /* Check for New Layer & Update Layer List (after Importing Data OR Adding Features) */
 for ( i=1 ; i<=feat_count ; i++ )
     {
      found = 0 ;

      for ( j=1 ; j<=lay_count ; j++ )
          {
           if ( lay[j].id == feat[i].layer )
              {
               found = 1 ;
              }
          }

      if ( found == 0 )
         {
          lay_count++ ;
          lay[lay_count].id   = feat[i].layer ;
          lay[lay_count].displayed[0] = 'Y'   ;
         }
     }


 /* Numerically sort layers assending */
 for ( i=1 ; i<=lay_count ; i++ )
     {
      for ( j=1 ; j<lay_count ; j++ )
          {
           if ( lay[j].id > lay[j+1].id )
              {
               layer_id    = lay[j].id   ;
               lay[j].id   = lay[j+1].id ;
               lay[j+1].id = layer_id    ;
              }
          }
     }


 /* Change Feature displayed Status according to layer visibility (New Linux) */
  for ( i=1 ; i<=feat_count ; i++ )
     {
      for ( j=1 ; j<=lay_count ; j++ )
          {
           if (( feat[i].layer == lay[j].id ) &&
               ( feat[i].displayed[0] != lay[j].displayed[0] ))
               {
                feat[i].displayed[0] = lay[j].displayed[0] ;
                break ;
               }
          }
     }

}
/*------------------------------------------------------------------------*/
/*                           display_scale()                              */
/*------------------------------------------------------------------------*/
void display_scale()     /* BUG */
{
 y_diff = y_max - y_min ;


 switch (DB_UNIT)
      {
       case MM: scale = ( y_diff * .1   )  / SCREEN_CM ; break ;
       case CM: scale = ( y_diff * 1.   ) / SCREEN_CM ; break ;
       case DM: scale = ( y_diff * 10.  ) / SCREEN_CM ; break ;
       case  M: scale = ( y_diff * 100. ) / SCREEN_CM ; break ;
       case KM: scale = ( y_diff * 1000.) / SCREEN_CM ; break ;
       default: scale = ( y_diff * 100. ) / SCREEN_CM ;
                fprintf(stderr,"ERROR : Data Base Unit not Defined\n");
                break ;
      }


 sprintf (scale_ch, "SCALE : 1 / %.0f",scale);
 xstr = XmStringCreate(scale_ch,CS);
 XtSetArg(args[0], XmNlabelString, xstr);
 XtSetValues(scale_label,args,1);
}
/*------------------------------------------------------------------------*/
/*                           snap_to_feat()                               */
/*------------------------------------------------------------------------*/
void snap_to_feature(char *snap_feat)
{
 double min_distance ;


 min_distance  = 9999999 ;


 for ( i=1; i<=feat_count; i++ )
 {

 switch (feat[i].type)
  {
   case 1:    /*-------------- Exmain type one --------------------*/

    x_base = feat[i].xbase ;
    y_base = feat[i].ybase ;

    /* Dsiplayed feat && same feat_code as requested */
    if ( (feat[i].displayed[0] == 'Y') && (strcmp(feat[i].code,snap_feat) == 0) )
       {
        x_diff   = abs  ( x_mouse - feat[i].xbase ) ;
        y_diff   = abs  ( y_mouse - feat[i].ybase ) ;
        distance = sqrt ((x_diff * x_diff) + (y_diff * y_diff)) ;

        if (distance <= min_distance)
           {
            selected_feat = i        ;
            min_distance  = distance ;
            search_status = FOUND    ;
           }
       }

    break ;
  }
 }
}
/*------------------------------------------------------------------------*/
/*                           feat_search()                                */
/*------------------------------------------------------------------------*/
void feat_search()
{
 x_min1 = x_min - SYMBCLIPBUFFER ;
 y_min1 = y_min - SYMBCLIPBUFFER ;
 x_max1 = x_max + SYMBCLIPBUFFER ;
 y_max1 = y_max + SYMBCLIPBUFFER ;

 x_min2 = x_min - LINECLIPBUFFER ;
 y_min2 = y_min - LINECLIPBUFFER ;
 x_max2 = x_max + LINECLIPBUFFER ;
 y_max2 = y_max + LINECLIPBUFFER ;


 for ( i=1; i<=feat_count; i++ )
 {

 switch (feat[i].type)
  {
   case 1:    /*-------------- Exmain type one --------------------*/

    x_base = feat[i].xbase ;
    y_base = feat[i].ybase ;

    /* BASE POINT CLIPPING & MIN SYMBOL SIZE = 1 */
    if ( (feat[i].displayed[0] == 'Y'         ) &&
         (feat[i].scale_range[sc_range] == 'Y') &&
         (x_base >= x_min1)&&(x_base <= x_max1) &&
         (y_base >= y_min1)&&(y_base <= y_max1) &&
         ((feat[i].symb_size/ONE_PIXEL) >= 1) )
       {
        x_diff   = abs  ( x_mouse - feat[i].xbase ) ;
        y_diff   = abs  ( y_mouse - feat[i].ybase ) ;
        distance = sqrt ((x_diff * x_diff) + (y_diff * y_diff)) ;

        if (distance <= tolerance )
           {
            selected_feat = i     ;
            search_status = FOUND ;
            return ;
           }


        /*  Correlate on TEXT if ANY */
        if (feat[i].has_text[0] == 'Y')
           {
            for(ii=1; ii<=feat[i].text_count; ii++)
               {
                text_index = feat[i].text + ii     ;
                size       = text[text_index].size ;
                angle      = (double)text[text_index].angle / DEG2RAD ;
                length     = strlen (text[text_index].string) - 1     ;

                x1_db      = text[text_index].x ;
                y1_db      = text[text_index].y ;
                x2_db      = x1_db + length * size * cos(angle) ;
                y2_db      = y1_db + length * size * sin(angle) ;

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

                /* IF Mouse inside TEXT Enclosure Box, Try to Correlate */
                if ((x_mouse>x_small)&&(x_mouse<x_big)&&(y_mouse>y_small)&&(y_mouse<y_big))
                   {
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
                       {
                        b = (y2_db - y1_db)/(x2_db - x1_db) ;
                        angle = atan (b);

                        a        = y1_db - (b * x1_db) ;
                        x_line   = ( y_mouse - a ) / b ;
                        x_diff   = abs ( x_line - x_mouse ) ;
                        distance = abs ( x_diff * sin(angle) ) ;
                       }

                    if (distance <= tolerance )
                       {
                        selected_feat = i     ;
                        search_status = FOUND ;
                        return ;
                       }
                   }
               }
           } /* end of TEXT Correlation */

       }
    break ;

   case 2:    /*-------------- Exmain type two --------------------*/

    x_base = feat[i].xbase ;
    y_base = feat[i].ybase ;
    x_end  = feat[i].xend  ;
    y_end  = feat[i].yend  ;

    /* END POINTS CLIPPING */
    if ( (feat[i].displayed[0] == 'Y'         ) &&
         (feat[i].scale_range[sc_range] == 'Y') &&
         (((x_base>x_min2)&&(x_base<x_max2)&&(y_base>y_min2)&&(y_base<y_max2)) ||
         ((x_end>x_min2)&&(x_end<x_max2)&&(y_end>y_min2)&&(y_end<y_max2))) )
       {
        for ( ii=0 ; ii<=(feat[i].xy_count+1) ; ii++ )
            {
             switch (ii)
                {
                 case 0:
                      x1_db = x_base ;
                      y1_db = y_base ;
                      break ;

                 default:
                      if ( ii <= feat[i].xy_count)
                         {
                          x2_db = x[feat[i].xy+ii] ;
                          y2_db = y[feat[i].xy+ii] ;
                         }
                      else
                         {
                          x2_db = x_end ;
                          y2_db = y_end ;
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
                          if ( y1_db == y2_db )  /* hz segment */
                             {
                              distance = abs (y_mouse - y1_db) ;
                             }

                     else if ( x1_db == x2_db )  /* vl segment */
                             {
                              distance = abs (x_mouse - x1_db) ;
                             }
                         else
                             {
                              angle = atan2 ((y2_db - y1_db),(x2_db - x1_db));
                              b = tan (angle) ;

                              a        = y1_db - (b * x1_db) ;
                              x_line   = ( y_mouse - a ) / b ;
                              x_diff   = abs ( x_line - x_mouse ) ;
                              distance = abs ( x_diff * sin(angle) ) ;
                             }

                          if ( distance <= tolerance )
                             {
                              selected_feat = i     ;
                              search_status = FOUND ;
                              return ;
                             }
                         }

                      x1_db = x2_db ;
                      y1_db = y2_db ;
                      break ;
                }
            }


        /*  Correlate on TEXT if ANY */
        if (feat[i].has_text[0] == 'Y')
           {
            for(ii=1; ii<=feat[i].text_count; ii++)
               {
                text_index = feat[i].text + ii     ;
                size       = text[text_index].size ;
                angle      = (double)text[text_index].angle / DEG2RAD ;
                length     = strlen (text[text_index].string) - 1     ;

                x1_db      = text[text_index].x ;
                y1_db      = text[text_index].y ;
                x2_db      = x1_db + length * size * cos(angle) ;
                y2_db      = y1_db + length * size * sin(angle) ;

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

                /* IF Mouse inside TEXT Enclosure Box, Try to Correlate */
                if ((x_mouse>x_small)&&(x_mouse<x_big)&&(y_mouse>y_small)&&(y_mouse<y_big))
                   {
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
                       {
                        b = (y2_db - y1_db)/(x2_db - x1_db) ;
                        angle = atan (b);

                        a        = y1_db - (b * x1_db) ;
                        x_line   = ( y_mouse - a ) / b ;
                        x_diff   = abs ( x_line - x_mouse ) ;
                        distance = abs ( x_diff * sin(angle) ) ;
                       }

                    if (distance <= tolerance )
                       {
                        selected_feat = i     ;
                        search_status = FOUND ;
                        return ;
                       }
                   }
               }
           } /* end of TEXT Correlation */


       }

    break ;
  }
 } /* main loop */

}
/*------------------------------------------------------------------------*/
/*                           edit_feature()                               */
/*------------------------------------------------------------------------*/
void edit_feature()
{
 edit () ;
}
/*------------------------------------------------------------------------*/
/*                        highlight_feature()                             */
/*------------------------------------------------------------------------*/
void highlight_feature (int selected_feat_parm)
{
 int i  ;
 int ii ;

 i = selected_feat_parm ;


 if (feat[i].type == 1)
    {
     XSynchronize(MainDisplay,1);

     set_line_attr (feat[i].linetype,feat[i].linewidth);

     draw_symb(feat[i].symb_num,
               feat[i].xbase,
               feat[i].ybase,
               magenta.pixel,
               feat[i].symb_size,
               feat[i].symb_angle);


     if (feat[i].has_text[0] == 'Y')
        {
         for(ii=1; ii<=feat[i].text_count; ii++)
            {
             text_index = feat[i].text + ii ;
             x_screen  = (text[text_index].x - x_min ) / ONE_PIXEL ;
             y_screen  = (y_max  - text[text_index].y) / ONE_PIXEL ;
             draw_text(x_screen,y_screen,magenta.pixel,text[text_index].size,text_index,text[text_index].angle);
            }
        }

    }
 else
 if (feat[i].type == 2)
    {
     XSynchronize(MainDisplay,1);

     set_line_attr (feat[i].linetype,(feat[i].linewidth)); /* linewidth+1 */

     draw_line(i,magenta.pixel) ;


     if (feat[i].has_text[0] == 'Y')
        {
         for(ii=1; ii<=feat[i].text_count; ii++)
            {
             text_index = feat[i].text + ii ;
             x_screen  = (text[text_index].x - x_min ) / ONE_PIXEL ;
             y_screen  = (y_max  - text[text_index].y) / ONE_PIXEL ;
             draw_text(x_screen,y_screen,magenta.pixel,text[text_index].size,text_index,text[text_index].angle);
            }
        }
    }

 XSynchronize(MainDisplay,0);
}
/*------------------------------------------------------------------------*/
/*                             draw_feature()                             */
/*------------------------------------------------------------------------*/
void draw_feature (int selected_feat_parm)
{
 int i  ;
 int ii ;

 i = selected_feat_parm ;


 if (feat[i].type == 1)
    {
     XSynchronize(MainDisplay,1);

     set_line_attr (feat[i].linetype,feat[i].linewidth);

     draw_symb(feat[i].symb_num,
               feat[i].xbase,
               feat[i].ybase,
               feat[i].color,
               feat[i].symb_size,
               feat[i].symb_angle);


     if (feat[i].has_text[0] == 'Y')
        {
         for(ii=1; ii<=feat[i].text_count; ii++)
            {
             text_index = feat[i].text + ii ;
             x_screen  = (text[text_index].x - x_min ) / ONE_PIXEL ;
             y_screen  = (y_max  - text[text_index].y) / ONE_PIXEL ;
             draw_text(x_screen,y_screen,feat[i].color,text[text_index].size,text_index,text[text_index].angle);
            }
        }

    }
 else
 if (feat[i].type == 2)
    {
     XSynchronize(MainDisplay,1);

     set_line_attr (feat[i].linetype,feat[i].linewidth);

     draw_line(i,feat[i].color) ;

     if (feat[i].has_text[0] == 'Y')
        {
         for(ii=1; ii<=feat[i].text_count; ii++)
            {
             text_index = feat[i].text + ii ;
             x_screen  = (text[text_index].x - x_min ) / ONE_PIXEL ;
             y_screen  = (y_max  - text[text_index].y) / ONE_PIXEL ;
             draw_text(x_screen,y_screen,feat[i].color,text[text_index].size,text_index,text[text_index].angle);
            }
        }
    }

 XSynchronize(MainDisplay,0);


 if ( need_draw_all == 1 )  /* Used with street color coding only */
    {
     // draw_all(image_file_name) ;
     // normal_cursor();
    }

}
/*------------------------------------------------------------------------*/
/*                             erase_feature()                            */
/*------------------------------------------------------------------------*/
void erase_feature (int selected_feat_parm)
{
 int i  ;
 int ii ;

 i = selected_feat_parm ;


 if (feat[i].type == 1)
    {
     XSynchronize(MainDisplay,1);

     set_line_attr (feat[i].linetype,feat[i].linewidth);

     draw_symb(feat[i].symb_num,
               feat[i].xbase,
               feat[i].ybase,
               black.pixel,
               feat[i].symb_size,
               feat[i].symb_angle);


     if (feat[i].has_text[0] == 'Y')
        {
         for(ii=1; ii<=feat[i].text_count; ii++)
            {
             text_index = feat[i].text + ii ;
             x_screen  = (text[text_index].x - x_min ) / ONE_PIXEL ;
             y_screen  = (y_max  - text[text_index].y) / ONE_PIXEL ;
             draw_text(x_screen,y_screen,black.pixel,text[text_index].size,text_index,text[text_index].angle);
            }
        }

    }
 else
 if (feat[i].type == 2)
    {
     XSynchronize(MainDisplay,1);

     set_line_attr (feat[i].linetype,feat[i].linewidth);

     draw_line(i,black.pixel);


     if (feat[i].has_text[0] == 'Y')
        {
         for(ii=1; ii<=feat[i].text_count; ii++)
            {
             text_index = feat[i].text + ii ;
             x_screen  = (text[text_index].x - x_min ) / ONE_PIXEL ;
             y_screen  = (y_max  - text[text_index].y) / ONE_PIXEL ;
             draw_text(x_screen,y_screen,black.pixel,text[text_index].size,text_index,text[text_index].angle);
            }
        }
    }

 XSynchronize(MainDisplay,0);

}
/*------------------------------------------------------------------------*/
/*                           draw_feature_mask()                          */
/*------------------------------------------------------------------------*/
void draw_feature_mask (int selected_feat_parm, int x_parm, int y_parm )
{
 int i   ;
 int ii  ;
 int xx1 ;
 int yy1 ;
 int xx2 ;
 int yy2 ;


 i = selected_feat_parm ;

 /* Draw Text Mask if Any */
 if (feat[i].has_text[0] == 'Y')
    {

     for(ii=1; ii<=feat[i].text_count; ii++)
        {
         text_index = feat[i].text + ii ;
         {
          int     j             ;
          int     jj            ;
          int     length        ;
          int     previous_symb ;
          double  x_db          ;
          double  y_db          ;
          double  size          ;

          switch (feat[i].type)
            {
             case 1:
             default:
               x_db = x_parm + (text[text_index].x - feat[i].xbase) / ONE_PIXEL ;
               y_db = y_parm - (text[text_index].y - feat[i].ybase) / ONE_PIXEL ;
               break;

            case 2:
              x_db = x_parm + (text[text_index].x - x_old) / ONE_PIXEL ;
              y_db = y_parm - (text[text_index].y - y_old) / ONE_PIXEL ;
              break;
            }

          font_no = text[text_index].font                    ;
          length  = strlen (text[text_index].string) -1      ;
          angle   = (double)text[text_index].angle / DEG2RAD ;
          size    = text[text_index].size / ONE_PIXEL        ;

          switch (text[text_index].just)
                 {
                  case 1:
                        x_db -= (size/2) * sin(angle);         /* Bottom */
                        y_db -= (size/2) * cos(angle);
                        x_db += (size/2) * cos(angle);         /* Left   */
                        y_db -= (size/2) * sin(angle);
                        break;

                  case 2:
                        x_db -= (size/2) * sin(angle);         /* Bottom */
                        y_db -= (size/2) * cos(angle);
                        x_db -= (length*size/2) * cos(angle);  /* Center */
                        y_db += (length*size/2) * sin(angle);
                        break;

                  case 3:
                        x_db -= (size/2) * sin(angle);         /* Bottom */
                        y_db -= (size/2) * cos(angle);
                        x_db -= (length*size) * cos(angle);    /* Right  */
                        y_db += (length*size) * sin(angle);
                        break;

                  case 4:
                                                               /* Middle */
                        x_db += (size/2) * cos(angle);         /* Left   */
                        y_db -= (size/2) * sin(angle);
                        break;

                  case 5:
                                                               /* Middle */
                        x_db -= (length*size/2) * cos(angle);  /* Center */
                        y_db += (length*size/2) * sin(angle);
                        break;

                  case 6:
                        /* Middle */
                        /* Right  */
                        x_db -= (length*size) * cos(angle);
                        y_db += (length*size) * sin(angle);
                        break;

                  case 7:
                        /* Top */
                        x_db += (size/2) * sin(angle);
                        y_db += (size/2) * cos(angle);
                        /* Left */
                        x_db += (size/2) * cos(angle);
                        y_db -= (size/2) * sin(angle);
                        break;

                  case 8:
                        /* Top */
                        x_db += (size/2) * sin(angle);
                        y_db += (size/2) * cos(angle);
                        /* Center */
                        x_db -= (length*size/2) * cos(angle);
                        y_db += (length*size/2) * sin(angle);
                        break;

                  case 9:
                        /* Top */
                        x_db += (size/2) * sin(angle);
                        y_db += (size/2) * cos(angle);
                        /* Right  */
                        x_db -= (length*size) * cos(angle);
                        y_db += (length*size) * sin(angle);
                        break;
                  }


          for (j=0; j<=length ; j++)
              {
               symb_no     = 0 ;
               symb_no     = text[text_index].string[j] ;
               symb_factor = (double) size / (double) font[font_no][symb_no].grid ;

               if ( j != 0 )
                  {
                   previous_symb = text[text_index].string[j-1] ;
                   x_db += size * font[font_no][previous_symb].x_factor * cos(angle) ;
                   y_db -= size * font[font_no][previous_symb].x_factor * sin(angle) ;
                   /* x_db += size * cos(angle) ;
                      y_db -= size * sin(angle) ; */
                  }


               for ( jj=1; jj<=font[font_no][symb_no].stroke; jj++)
                   {
                    switch (font[font_no][symb_no].mv_draw[jj])
                     {
                      case 0:     /*  Move  */

                        angle_sym = font[font_no][symb_no].angle[jj] + angle ;
                        xx1 = x_db + symb_factor * font[font_no][symb_no].distance[jj] * cos(angle_sym);
                        yy1 = y_db - symb_factor * font[font_no][symb_no].distance[jj] * sin(angle_sym);
                        break ;

                      case 1:     /*  Draw  */

                        angle_sym = font[font_no][symb_no].angle[jj] + angle ;
                        xx2 = x_db + symb_factor * font[font_no][symb_no].distance[jj] * cos(angle_sym);
                        yy2 = y_db - symb_factor * font[font_no][symb_no].distance[jj] * sin(angle_sym);

                        XDrawLine(MainDisplay,XtWindow(drawarea),xor_gc,xx1,yy1,xx2,yy2);
                        XDrawLine(MainDisplay,Tile              ,xor_gc,xx1,yy1,xx2,yy2);

                        xx1 = xx2 ;
                        yy1 = yy2 ;
                        break ;

                      default:    /* Do nothing */
                        break ;
                     }
                }
             }

         }
      }
    } /* end of Text Mask */



 if (feat[i].type == 1)
    {
     /* Draw Symbol */
     x_base      = x_parm ;
     y_base      = y_parm ;

     symb_no     = feat[i].symb_num ;
     symb_factor = (float)feat[i].symb_size  / symb[symb_no].grid ;
     angle       = (float)feat[i].symb_angle / DEG2RAD            ;

     for ( ii=1; ii<=symb[symb_no].stroke; ii++)
         {
          switch (symb[symb_no].mv_draw[ii])
           {
            case 0:     /*  Move  */
             angle_sym = symb[symb_no].angle[ii] + angle ;
             xx1 = (x_base) + ( symb_factor * symb[symb_no].distance[ii] * cos(angle_sym)) / ONE_PIXEL ;
             yy1 = (y_base) - ( symb_factor * symb[symb_no].distance[ii] * sin(angle_sym)) / ONE_PIXEL ;
             break ;

            case 1:     /*  Draw  */
             angle_sym = symb[symb_no].angle[ii] + angle ;
             xx2 = (x_base) + (symb_factor * symb[symb_no].distance[ii] * cos(angle_sym)) / ONE_PIXEL ;
             yy2 = (y_base) - (symb_factor * symb[symb_no].distance[ii] * sin(angle_sym)) / ONE_PIXEL ;
             XDrawLine(MainDisplay,XtWindow(drawarea),xor_gc,xx1,yy1,xx2,yy2);
             XDrawLine(MainDisplay,Tile              ,xor_gc,xx1,yy1,xx2,yy2);
             xx1 = xx2 ;
             yy1 = yy2 ;
             break ;
            }
         }
    }/* End of Point feature Mask */

 else
 if (feat[i].type == 2)
    {
     x_parm = x_parm * ONE_PIXEL + x_min ;
     y_parm = y_max - y_parm * ONE_PIXEL ;


     x_base = x_parm + (feat[i].xbase - x_old) ;
     y_base = y_parm + (feat[i].ybase - y_old) ;
     x_end  = x_parm + (feat[i].xend  - x_old) ;
     y_end  = y_parm + (feat[i].yend  - y_old) ;

     {
      long    j          ;
      long    jj         ;
      long    x_screen   ;
      long    y_screen   ;
      long    x1_screen  ;
      long    y1_screen  ;
      long    x2_screen  ;
      long    y2_screen  ;
      double  x1_db      ;
      double  y1_db      ;
      double  x2_db      ;
      double  y2_db      ;


      for ( jj=0 ; jj<=(feat[i].xy_count+1) ; jj++ )
        {
         switch (jj)
          {
          case 0:
               x1_db = x_base ;
               y1_db = y_base ;

               x1_screen = (x1_db - x_min) / ONE_PIXEL ;
               y1_screen = (y_max - y1_db) / ONE_PIXEL ;
               break ;

          default:
               if ( jj <= feat[i].xy_count )
                  {
                   x2_db = x_parm + (x[feat[i].xy+jj] - x_old);
                   y2_db = y_parm + (y[feat[i].xy+jj] - y_old);
                  }
               else
                  {
                   x2_db = x_end ;
                   y2_db = y_end ;
                  }

               x2_screen = (x2_db - x_min) / ONE_PIXEL ;
               y2_screen = (y_max - y2_db) / ONE_PIXEL ;


               if (( x1_db>=x_min && x1_db<=x_max && y1_db>=y_min && y1_db<=y_max ) &&
                   ( x2_db>=x_min && x2_db<=x_max && y2_db>=y_min && y2_db<=y_max ) )
                  {
                   XDrawLine(MainDisplay,XtWindow(drawarea),xor_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                   XDrawLine(MainDisplay,Tile,xor_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                  }

          else if ( x1_db>=x_min && x1_db<=x_max && y1_db>=y_min && y1_db<=y_max )
                  {
                   if ( x1_db == x2_db )   /* VL Segment */
                      {
                       if ( y2_db > y1_db )
                          {
                           x2_screen = (x2_db - x_min) / ONE_PIXEL;
                           y2_screen = (y_max - y_max) / ONE_PIXEL;
                          }
                        else
                          {
                           x2_screen = (x2_db - x_min) / ONE_PIXEL ;
                           y2_screen = (y_max - y_min) / ONE_PIXEL ;
                          }
                       XDrawLine(MainDisplay,XtWindow(drawarea),xor_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                       XDrawLine(MainDisplay,Tile,xor_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                       goto end ;
                      }

                   if ( y1_db == y2_db )    /* HZ Segment */
                      {
                       if ( x2_db > x1_db )
                          {
                           x2_screen = (x_max - x_min) / ONE_PIXEL ;
                           y2_screen = (y_max - y2_db) / ONE_PIXEL ;
                          }
                        else
                          {
                           x2_screen = (x_min - x_min) / ONE_PIXEL ;
                           y2_screen = (y_max - y2_db) / ONE_PIXEL ;
                          }
                       XDrawLine(MainDisplay,XtWindow(drawarea),xor_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                       XDrawLine(MainDisplay,Tile,xor_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                       goto end ;
                      }

                   b = (y2_db - y1_db)/(x2_db - x1_db) ;
                   a = y1_db - (b * x1_db) ;

                   x_bot   = (y_min - a) / b ;
                   x_top   = (y_max - a) / b ;
                   y_left  = a + (b * x_min) ;
                   y_right = a + (b * x_max) ;

                   if ((x_bot>x_min && x_bot<x_max) &&
                      ((x_bot>x1_db && x_bot<x2_db) || (x_bot>x2_db && x_bot<x1_db)))
                      {
                       x2_screen = (x_bot - x_min) / ONE_PIXEL  ;
                       y2_screen = (y_max - y_min) / ONE_PIXEL ;
                       XDrawLine(MainDisplay,XtWindow(drawarea),xor_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                       XDrawLine(MainDisplay,Tile,xor_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                      }
              else if ((x_top>x_min && x_top<x_max) &&
                      ((x_top>x1_db && x_top<x2_db) || (x_top>x2_db && x_top<x1_db)))
                      {
                       x2_screen = (x_top - x_min) / ONE_PIXEL ;
                       y2_screen = (y_max - y_max) / ONE_PIXEL ;
                       XDrawLine(MainDisplay,XtWindow(drawarea),xor_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                       XDrawLine(MainDisplay,Tile,xor_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                      }
              else if ((y_left>y_min && y_left<y_max) &&
                      ((y_left>y1_db && y_left<y2_db) || (y_left>y2_db && y_left<y1_db)))
                      {
                       x2_screen = (x_min - x_min ) / ONE_PIXEL ;
                       y2_screen = (y_max - y_left) / ONE_PIXEL ;
                       XDrawLine(MainDisplay,XtWindow(drawarea),xor_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                       XDrawLine(MainDisplay,Tile,xor_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                      }
              else if ((y_right>y_min && y_right<y_max) &&
                      ((y_right>y1_db && y_right<y2_db) || (y_right>y2_db && y_right<y1_db)))
                      {
                       x2_screen = (x_max - x_min  ) / ONE_PIXEL ;
                       y2_screen = (y_max - y_right) / ONE_PIXEL ;
                       XDrawLine(MainDisplay,XtWindow(drawarea),xor_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                       XDrawLine(MainDisplay,Tile,xor_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                      }
                  }

          else if ( x2_db>=x_min && x2_db<=x_max && y2_db>=y_min && y2_db<=y_max )
                  {
                   if ( x1_db == x2_db )   /* VL Segment */
                      {
                       if ( y1_db > y2_db )
                          {
                           x1_screen = (x1_db - x_min) / ONE_PIXEL ;
                           y1_screen = (y_max - y_max) / ONE_PIXEL ;
                          }
                        else
                          {
                           x1_screen = (x1_db - x_min) / ONE_PIXEL ;
                           y1_screen = (y_max - y_min) / ONE_PIXEL ;
                          }
                       XDrawLine(MainDisplay,XtWindow(drawarea),xor_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                       XDrawLine(MainDisplay,Tile,xor_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                       goto end ;
                      }

                   if ( y1_db == y2_db )    /* HZ Segment */
                      {
                       if ( x1_db > x2_db )
                          {
                           x1_screen = (x_max - x_min) / ONE_PIXEL ;
                           y1_screen = (y_max - y1_db) / ONE_PIXEL ;
                          }
                        else
                          {
                           x1_screen = (x_min - x_min) / ONE_PIXEL ;
                           y1_screen = (y_max - y1_db) / ONE_PIXEL ;
                          }
                       XDrawLine(MainDisplay,XtWindow(drawarea),xor_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                       XDrawLine(MainDisplay,Tile,xor_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                       goto end ;
                      }

                   b = (y2_db - y1_db)/(x2_db - x1_db) ;
                   a = y1_db - (b * x1_db) ;

                   x_bot   = (y_min - a) / b ;
                   x_top   = (y_max - a) / b ;
                   y_left  = a + (b * x_min) ;
                   y_right = a + (b * x_max) ;

                   if ((x_bot>x_min && x_bot<x_max) &&
                      ((x_bot>x1_db && x_bot<x2_db) || (x_bot>x2_db && x_bot<x1_db)))
                      {
                       x1_screen = (x_bot - x_min) / ONE_PIXEL ;
                       y1_screen = (y_max - y_min) / ONE_PIXEL ;
                       XDrawLine(MainDisplay,XtWindow(drawarea),xor_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                       XDrawLine(MainDisplay,Tile,xor_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                      }
              else if ((x_top>x_min && x_top<x_max) &&
                      ((x_top>x1_db && x_top<x2_db) || (x_top>x2_db && x_top<x1_db)))
                      {
                       x1_screen = (x_top - x_min) / ONE_PIXEL ;
                       y1_screen = (y_max - y_max) / ONE_PIXEL ;
                       XDrawLine(MainDisplay,XtWindow(drawarea),xor_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                       XDrawLine(MainDisplay,Tile,xor_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                      }
              else if ((y_left>y_min && y_left<y_max) &&
                      ((y_left>y1_db && y_left<y2_db) || (y_left>y2_db && y_left<y1_db)))
                      {
                       x1_screen = (x_min - x_min ) / ONE_PIXEL ;
                       y1_screen = (y_max - y_left) / ONE_PIXEL ;
                       XDrawLine(MainDisplay,XtWindow(drawarea),xor_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                       XDrawLine(MainDisplay,Tile,xor_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                      }
              else if ((y_right>y_min && y_right<y_max) &&
                      ((y_right>y1_db && y_right<y2_db) || (y_right>y2_db && y_right<y1_db)))
                      {
                       x1_screen = (x_max - x_min  ) / ONE_PIXEL ;
                       y1_screen = (y_max - y_right) / ONE_PIXEL ;
                       XDrawLine(MainDisplay,XtWindow(drawarea),xor_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                       XDrawLine(MainDisplay,Tile,xor_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                      }
                  }
              else
                  {
                   b = (y2_db - y1_db)/(x2_db - x1_db) ;
                   a = y1_db - (b * x1_db) ;

                   /* --------------------- CASE I ----------------------- */
                   if ((y1_db < y_min && y2_db > y_max) || (y2_db < y_min && y1_db > y_max))
                      {
                       if ( x2_db == x1_db )  /* VL Segment */
                          {
                           x1_clip = x1_db ;  y1_clip = y_min ;
                           x2_clip = x2_db ;  y2_clip = y_max ;

                           x1_screen = (x1_clip - x_min) / ONE_PIXEL ;
                           y1_screen = (y_max - y1_clip) / ONE_PIXEL ;
                           x2_screen = (x2_clip - x_min) / ONE_PIXEL ;
                           y2_screen = (y_max - y2_clip) / ONE_PIXEL ;
                           XDrawLine(MainDisplay,XtWindow(drawarea),xor_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                           XDrawLine(MainDisplay,Tile              ,xor_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                           goto end ;
                          }

                       x_bot = (y_min - a) / b ;
                       x_top = (y_max - a) / b ;

                       if (x_bot > x_min && x_bot < x_max)
                          {
                           x1_clip = x_bot ;
                           y1_clip = y_min ;
                          }
                       else
                          { goto next2 ; }

                       if (x_top  > x_min && x_top  < x_max)
                          {
                           x2_clip = x_top ;
                           y2_clip = y_max ;

                           x1_screen = (x1_clip - x_min) / ONE_PIXEL ;
                           y1_screen = (y_max - y1_clip) / ONE_PIXEL ;
                           x2_screen = (x2_clip - x_min) / ONE_PIXEL ;
                           y2_screen = (y_max - y2_clip) / ONE_PIXEL ;
                           XDrawLine(MainDisplay,XtWindow(drawarea),xor_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                           XDrawLine(MainDisplay,Tile,xor_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                           goto end ;
                          }
                      }
                   next2:
                   /* --------------------- CASE II ---------------------- */
                   if ((x1_db < x_min && x2_db > x_max) || (x2_db < x_min && x1_db > x_max))
                      {
                       y_left  = a + (b * x_min) ;
                       y_right = a + (b * x_max) ;

                       if (y_left > y_min && y_left < y_max)
                          {
                           x1_clip = x_min  ;
                           y1_clip = y_left ;
                          }
                       else
                          { goto next3 ; }

                       if (y_right > y_min && y_right < y_max)
                          {
                           x2_clip = x_max   ;
                           y2_clip = y_right ;

                           x1_screen = (x1_clip - x_min) / ONE_PIXEL ;
                           y1_screen = (y_max - y1_clip) / ONE_PIXEL ;
                           x2_screen = (x2_clip - x_min) / ONE_PIXEL ;
                           y2_screen = (y_max - y2_clip) / ONE_PIXEL ;
                           XDrawLine(MainDisplay,XtWindow(drawarea),xor_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                           XDrawLine(MainDisplay,Tile,xor_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                           goto end ;
                          }
                      }
                   next3:
                   /* --------------------- CASE III --------------------- */
                   if ((y1_db < y_min && x2_db > x_max) || (y2_db < y_min && x1_db > x_max))
                      {
                       x_bot   = (y_min - a) / b ;
                       y_right = a + (b * x_max) ;

                       if (x_bot > x_min && x_bot < x_max)
                          {
                           x1_clip = x_bot ;
                           y1_clip = y_min ;
                          }
                       else
                          { goto next4 ; }

                       if (y_right > y_min && y_right < y_max)
                          {
                           x2_clip = x_max   ;
                           y2_clip = y_right ;

                           x1_screen = (x1_clip - x_min) / ONE_PIXEL ;
                           y1_screen = (y_max - y1_clip) / ONE_PIXEL ;
                           x2_screen = (x2_clip - x_min) / ONE_PIXEL ;
                           y2_screen = (y_max - y2_clip) / ONE_PIXEL ;
                           XDrawLine(MainDisplay,XtWindow(drawarea),xor_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                           XDrawLine(MainDisplay,Tile,xor_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                           goto end ;
                          }
                      }
                   next4:
                   /* --------------------- CASE IV ---------------------- */
                   if ((y1_db < y_min && x2_db < x_min) || (y2_db < y_min && x1_db < x_min))
                      {
                       x_bot  = (y_min - a) / b ;
                       y_left = a + (b * x_min) ;

                       if (x_bot > x_min && x_bot < x_max)
                          {
                           x1_clip = x_bot ;
                           y1_clip = y_min ;
                          }
                       else
                          { goto next5 ; }

                       if (y_left > y_min && y_left < y_max)
                          {
                           x2_clip = x_min   ;
                           y2_clip = y_left  ;

                           x1_screen = (x1_clip - x_min) / ONE_PIXEL ;
                           y1_screen = (y_max - y1_clip) / ONE_PIXEL ;
                           x2_screen = (x2_clip - x_min) / ONE_PIXEL ;
                           y2_screen = (y_max - y2_clip) / ONE_PIXEL ;
                           XDrawLine(MainDisplay,XtWindow(drawarea),xor_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                           XDrawLine(MainDisplay,Tile,xor_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                           goto end ;
                          }
                      }
                   next5:
                   /* --------------------- CASE V ----------------------- */
                   if ((y2_db > y_max && x1_db > x_max) || (y1_db > y_max && x2_db > x_max))
                      {
                       x_top   = (y_max - a) / b ;
                       y_right = a + (b * x_max) ;

                       if (x_top  > x_min && x_top  < x_max)
                          {
                           x1_clip = x_top ;
                           y1_clip = y_max ;
                          }
                       else
                          { goto next6 ; }

                       if (y_right > y_min && y_right < y_max)
                          {
                           x2_clip = x_max   ;
                           y2_clip = y_right ;

                           x1_screen = (x1_clip - x_min) / ONE_PIXEL ;
                           y1_screen = (y_max - y1_clip) / ONE_PIXEL ;
                           x2_screen = (x2_clip - x_min) / ONE_PIXEL ;
                           y2_screen = (y_max - y2_clip) / ONE_PIXEL ;
                           XDrawLine(MainDisplay,XtWindow(drawarea),xor_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                           XDrawLine(MainDisplay,Tile,xor_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                           goto end ;
                          }
                      }
                   next6:
                   /* --------------------- CASE VI ---------------------- */
                   if ((y2_db > y_max && x1_db < x_min) || (y1_db > y_max && x2_db < x_min))
                      {
                       x_top  = (y_max - a) / b ;
                       y_left = a + (b * x_min) ;

                       if (x_top  > x_min && x_top  < x_max)
                          {
                           x1_clip = x_top ;
                           y1_clip = y_max ;
                          }
                       else
                          { goto end ; }

                       if (y_left > y_min && y_left < y_max)
                          {
                           x2_clip = x_min   ;
                           y2_clip = y_left  ;

                           x1_screen = (x1_clip - x_min) / ONE_PIXEL ;
                           y1_screen = (y_max - y1_clip) / ONE_PIXEL ;
                           x2_screen = (x2_clip - x_min) / ONE_PIXEL ;
                           y2_screen = (y_max - y2_clip) / ONE_PIXEL ;
                           XDrawLine(MainDisplay,XtWindow(drawarea),xor_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                           XDrawLine(MainDisplay,Tile,xor_gc,x1_screen,y1_screen,x2_screen,y2_screen);
                           goto end ;
                          }
                      }

                  }

                end:

                x1_db = x_parm + (x[feat[i].xy+jj] - x_old);
                y1_db = y_parm + (y[feat[i].xy+jj] - y_old);

                x1_screen = x2_screen ;
                y1_screen = y2_screen ;
                break ;
         }
     }

    }

    }/* End of Line Feature Mask */
}
/*------------------------------------------------------------------------*/
/*                          set_line_attr()                               */
/*------------------------------------------------------------------------*/
void set_line_attr(int parm_type, int parm_width)
{
 switch( parm_type )
       {
        case 1:
        default:
          XSetLineAttributes (MainDisplay,copy_gc,parm_width,LineSolid,CapButt,JoinMiter);
          break;

        case 2:
          XSetDashes         (MainDisplay,copy_gc,nDashOffset,cDashList2,sizeof(cDashList2)/sizeof(char));
          XSetLineAttributes (MainDisplay,copy_gc,parm_width,LineOnOffDash,CapButt,JoinMiter);
          break;

        case 3:
          XSetDashes         (MainDisplay,copy_gc,nDashOffset,cDashList3,sizeof(cDashList3)/sizeof(char));
          XSetLineAttributes (MainDisplay,copy_gc,parm_width,LineOnOffDash,CapButt,JoinMiter);
          break;

        case 4:
          XSetDashes         (MainDisplay,copy_gc,nDashOffset,cDashList4,sizeof(cDashList4)/sizeof(char));
          XSetLineAttributes (MainDisplay,copy_gc,parm_width,LineOnOffDash,CapButt,JoinMiter);
          break;

        case 5:
          XSetDashes         (MainDisplay,copy_gc,nDashOffset,cDashList5,sizeof(cDashList5)/sizeof(char));
          XSetLineAttributes (MainDisplay,copy_gc,parm_width,LineOnOffDash,CapButt,JoinMiter);
          break;

        case 6:
          XSetDashes         (MainDisplay,copy_gc,nDashOffset,cDashList6,sizeof(cDashList6)/sizeof(char));
          XSetLineAttributes (MainDisplay,copy_gc,parm_width,LineOnOffDash,CapButt,JoinMiter);
          break;

        case 7:
          XSetDashes         (MainDisplay,copy_gc,nDashOffset,cDashList7,sizeof(cDashList7)/sizeof(char));
          XSetLineAttributes (MainDisplay,copy_gc,parm_width,LineOnOffDash,CapButt,JoinMiter);
          break;

        case 8:
          XSetDashes         (MainDisplay,copy_gc,nDashOffset,cDashList8,sizeof(cDashList8)/sizeof(char));
          XSetLineAttributes (MainDisplay,copy_gc,parm_width,LineOnOffDash,CapButt,JoinMiter);
          break;

        case 9:
          XSetDashes         (MainDisplay,copy_gc,nDashOffset,cDashList9,sizeof(cDashList9)/sizeof(char));
          XSetLineAttributes (MainDisplay,copy_gc,parm_width,LineOnOffDash,CapButt,JoinMiter);
          break;

        case 10:
          XSetDashes         (MainDisplay,copy_gc,nDashOffset,cDashList10,sizeof(cDashList10)/sizeof(char));
          XSetLineAttributes (MainDisplay,copy_gc,parm_width,LineOnOffDash,CapButt,JoinMiter);
          break;
       }
}
/*------------------------------------------------------------------------*/
/*                             set_color()                                */
/*------------------------------------------------------------------------*/
void set_color(int parm_color)
{
  // XSetForeground (MainDisplay,copy_gc,parm_color);
}
/*------------------------------------------------------------------------*/
/*                         export_bitmap()                                */
/*------------------------------------------------------------------------*/
void export_bitmap()
{
 char          str[40];
 unsigned int  width  ;
 unsigned int  height ;
 int           x_hot  ;
 int           y_hot  ;
 int           ret    ;
 unsigned long val    ;


 /*
 x_hot  = 1  ;
 y_hot  = 1  ;
  val = XGetPixel( (XImage *) Tile , x_hot, y_hot);
 printf("return code = %d \n",val);
 printf("return code = %d \n",val);
  return ;
 */


 strcpy(str,"image.bit") ;
 width  = 1000 ;
 height = 1000 ;
 x_hot  = -1  ;
 y_hot  = -1  ;


 XWriteBitmapFile(MainDisplay,str,Tile,width,height,x_hot,y_hot);

 printf("INFO : Workspace exported to BitMap File [%s] \n",str);

}
/* -------------------------------------------------------------------*/
/*                         move_feature()                             */
/* -------------------------------------------------------------------*/
void move_feature(int selected_feat_parm,double x_old_parm,double y_old_parm,double x_new_parm,double y_new_parm)
{
 int i ;

 i       = selected_feat_parm ;
 x_mouse = x_old_parm         ;
 y_mouse = y_old_parm         ;
 x_new   = x_new_parm         ;
 y_new   = y_new_parm         ;


 if ( feat[i].type == 1 )
    {
     x_old = feat[i].xbase ;
     y_old = feat[i].ybase ;

     feat[i].xbase  += (x_new - x_old) ;
     feat[i].ybase  += (y_new - y_old) ;
     if ( db_opened[0] == 'Y' )
        {
         // Update Feature X_BASE, Y_BASE
         feat_num = feat[i].num   ;
         x_base   = feat[i].xbase ;
         y_base   = feat[i].ybase ;

         
/*
EXEC SQL UPDATE FEATURES
                  SET X_BASE = :x_base ,
                      Y_BASE = :y_base
                  WHERE FEAT_NUM = :feat_num ;
*/

{
#line 9607 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 9607 "geoIMS_main.sqc"
  sqlaaloc(2,3,46,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 9607 "geoIMS_main.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 9607 "geoIMS_main.sqc"
      sql_setdlist[0].sqldata = (void*)&x_base;
#line 9607 "geoIMS_main.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 9607 "geoIMS_main.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 9607 "geoIMS_main.sqc"
      sql_setdlist[1].sqldata = (void*)&y_base;
#line 9607 "geoIMS_main.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 9607 "geoIMS_main.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 9607 "geoIMS_main.sqc"
      sql_setdlist[2].sqldata = (void*)&feat_num;
#line 9607 "geoIMS_main.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 9607 "geoIMS_main.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 9607 "geoIMS_main.sqc"
  sqlacall((unsigned short)24,27,2,0,0L);
#line 9607 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 9607 "geoIMS_main.sqc"

         
/*
EXEC SQL COMMIT WORK ;
*/

{
#line 9608 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 9608 "geoIMS_main.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 9608 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 9608 "geoIMS_main.sqc"
       //  CHECKERR ("UPDATE");
        }


     if (feat[i].has_text[0] == 'Y')
        {
         for(ii=1; ii<=feat[i].text_count; ii++)
            {
             text_index = feat[i].text + ii ;
             text[text_index].x += (x_new - x_old) ;
             text[text_index].y += (y_new - y_old) ;

             if ( db_opened[0] == 'Y' )
                {
                 // Update Feature TEXT X,Y
                 feat_num = feat[i].num        ;
                 x_base   = text[text_index].x ;
                 y_base   = text[text_index].y ;

                 
/*
EXEC SQL UPDATE TEXT
                          SET X1 = :x_base ,
                              Y1 = :y_base
                          WHERE FEAT_NUM = :feat_num ;
*/

{
#line 9630 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 9630 "geoIMS_main.sqc"
  sqlaaloc(2,3,47,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 9630 "geoIMS_main.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 9630 "geoIMS_main.sqc"
      sql_setdlist[0].sqldata = (void*)&x_base;
#line 9630 "geoIMS_main.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 9630 "geoIMS_main.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 9630 "geoIMS_main.sqc"
      sql_setdlist[1].sqldata = (void*)&y_base;
#line 9630 "geoIMS_main.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 9630 "geoIMS_main.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 9630 "geoIMS_main.sqc"
      sql_setdlist[2].sqldata = (void*)&feat_num;
#line 9630 "geoIMS_main.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 9630 "geoIMS_main.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 9630 "geoIMS_main.sqc"
  sqlacall((unsigned short)24,28,2,0,0L);
#line 9630 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 9630 "geoIMS_main.sqc"

                 
/*
EXEC SQL COMMIT WORK ;
*/

{
#line 9631 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 9631 "geoIMS_main.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 9631 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 9631 "geoIMS_main.sqc"
      //  CHECKERR ("UPDATE");
                }
            }
        }

     return ;

    }
 else

 if ( feat[i].type == 2 )
    {
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
                    if ( y1_db == y2_db )  /* hz segment */
                       { distance = abs (y_mouse - y1_db) ; }
                    else
                    if ( x1_db == x2_db )  /* vl segment */
                       { distance = abs (x_mouse - x1_db) ; }
                    else
                       {
                        angle = atan2 ((y2_db - y1_db),(x2_db - x1_db));
                        b = tan (angle) ;

                        a        = y1_db - (b * x1_db) ;
                        x_line   = ( y_mouse - a ) / b ;
                        x_diff   = abs ( x_line - x_mouse )    ;
                        distance = abs ( x_diff * sin(angle) ) ;
                       }

                    if ( distance <= tolerance )
                       {
                        x_old = x_mouse - distance * sin(angle) ;
                        y_old = y_mouse + distance * cos(angle) ;


                        /* Update feature Coordinate */
                        feat[i].xbase  += (x_new - x_old) ;
                        feat[i].ybase  += (y_new - y_old) ;
                        feat[i].xend   += (x_new - x_old) ;
                        feat[i].yend   += (y_new - y_old) ;

                        if ( db_opened[0] == 'Y' )
                           {
                            // Update Feature XY_BASE, XY_END
                            feat_num = feat[i].num   ;
                            x_base   = feat[i].xbase ;
                            y_base   = feat[i].ybase ;
                            x_end    = feat[i].xend  ;
                            y_end    = feat[i].yend  ;

                            
/*
EXEC SQL UPDATE FEATURES
                                     SET X_BASE = :x_base ,
                                         Y_BASE = :y_base ,
                                         X_END  = :x_end  ,
                                         Y_END  = :y_end
                                     WHERE FEAT_NUM = :feat_num ;
*/

{
#line 9733 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 9733 "geoIMS_main.sqc"
  sqlaaloc(2,5,48,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 9733 "geoIMS_main.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 9733 "geoIMS_main.sqc"
      sql_setdlist[0].sqldata = (void*)&x_base;
#line 9733 "geoIMS_main.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 9733 "geoIMS_main.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 9733 "geoIMS_main.sqc"
      sql_setdlist[1].sqldata = (void*)&y_base;
#line 9733 "geoIMS_main.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 9733 "geoIMS_main.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 9733 "geoIMS_main.sqc"
      sql_setdlist[2].sqldata = (void*)&x_end;
#line 9733 "geoIMS_main.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 9733 "geoIMS_main.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 9733 "geoIMS_main.sqc"
      sql_setdlist[3].sqldata = (void*)&y_end;
#line 9733 "geoIMS_main.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 9733 "geoIMS_main.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 9733 "geoIMS_main.sqc"
      sql_setdlist[4].sqldata = (void*)&feat_num;
#line 9733 "geoIMS_main.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 9733 "geoIMS_main.sqc"
      sqlasetdata(2,0,5,sql_setdlist,0L,0L);
    }
#line 9733 "geoIMS_main.sqc"
  sqlacall((unsigned short)24,29,2,0,0L);
#line 9733 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 9733 "geoIMS_main.sqc"

                            
/*
EXEC SQL COMMIT WORK ;
*/

{
#line 9734 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 9734 "geoIMS_main.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 9734 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 9734 "geoIMS_main.sqc"
       //  CHECKERR ("UPDATE");
                           }

                        for ( j=1; j<=feat[i].xy_count; j++ )
                            {
                             x[feat[i].xy+j] += (x_new - x_old);
                             y[feat[i].xy+j] += (y_new - y_old);
                            }

                        if ( db_opened[0] == 'Y' && feat[i].xy_count > 0 )
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
EXEC SQL UPDATE coordinates
                                           SET  X_1  = :x_1 , Y_1  = :y_1 ,
                                                X_2  = :x_2 , Y_2  = :y_2 ,
                                                X_3  = :x_3 , Y_3  = :y_3 ,
                                                X_4  = :x_4 , Y_4  = :y_4 ,
                                                X_5  = :x_5 , Y_5  = :y_5 ,
                                                X_6  = :x_6 , Y_6  = :y_6 ,
                                                X_7  = :x_7 , Y_7  = :y_7 ,
                                                X_8  = :x_8 , Y_8  = :y_8 ,
                                                X_9  = :x_9 , Y_9  = :y_9 ,
                                                X_10 = :x_10, Y_10 = :y_10
                                           WHERE FEAT_NUM = :feat_num  AND SEQ = :seq ;
*/

{
#line 9777 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 9777 "geoIMS_main.sqc"
  sqlaaloc(2,22,49,0L);
    {
      struct sqla_setdata_list sql_setdlist[22];
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[0].sqldata = (void*)&x_1;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[1].sqldata = (void*)&y_1;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[2].sqldata = (void*)&x_2;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[3].sqldata = (void*)&y_2;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[4].sqldata = (void*)&x_3;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[5].sqltype = 496; sql_setdlist[5].sqllen = 4;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[5].sqldata = (void*)&y_3;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[6].sqldata = (void*)&x_4;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[7].sqltype = 496; sql_setdlist[7].sqllen = 4;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[7].sqldata = (void*)&y_4;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[8].sqltype = 496; sql_setdlist[8].sqllen = 4;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[8].sqldata = (void*)&x_5;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[9].sqltype = 496; sql_setdlist[9].sqllen = 4;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[9].sqldata = (void*)&y_5;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[10].sqltype = 496; sql_setdlist[10].sqllen = 4;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[10].sqldata = (void*)&x_6;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[11].sqltype = 496; sql_setdlist[11].sqllen = 4;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[11].sqldata = (void*)&y_6;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[11].sqlind = 0L;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[12].sqltype = 496; sql_setdlist[12].sqllen = 4;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[12].sqldata = (void*)&x_7;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[12].sqlind = 0L;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[13].sqltype = 496; sql_setdlist[13].sqllen = 4;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[13].sqldata = (void*)&y_7;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[13].sqlind = 0L;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[14].sqltype = 496; sql_setdlist[14].sqllen = 4;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[14].sqldata = (void*)&x_8;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[14].sqlind = 0L;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[15].sqltype = 496; sql_setdlist[15].sqllen = 4;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[15].sqldata = (void*)&y_8;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[15].sqlind = 0L;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[16].sqltype = 496; sql_setdlist[16].sqllen = 4;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[16].sqldata = (void*)&x_9;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[16].sqlind = 0L;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[17].sqltype = 496; sql_setdlist[17].sqllen = 4;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[17].sqldata = (void*)&y_9;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[17].sqlind = 0L;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[18].sqltype = 496; sql_setdlist[18].sqllen = 4;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[18].sqldata = (void*)&x_10;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[18].sqlind = 0L;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[19].sqltype = 496; sql_setdlist[19].sqllen = 4;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[19].sqldata = (void*)&y_10;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[19].sqlind = 0L;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[20].sqltype = 496; sql_setdlist[20].sqllen = 4;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[20].sqldata = (void*)&feat_num;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[20].sqlind = 0L;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[21].sqltype = 496; sql_setdlist[21].sqllen = 4;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[21].sqldata = (void*)&seq;
#line 9777 "geoIMS_main.sqc"
      sql_setdlist[21].sqlind = 0L;
#line 9777 "geoIMS_main.sqc"
      sqlasetdata(2,0,22,sql_setdlist,0L,0L);
    }
#line 9777 "geoIMS_main.sqc"
  sqlacall((unsigned short)24,30,2,0,0L);
#line 9777 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 9777 "geoIMS_main.sqc"
  // CHECKERR ("INSERT INTO");
                                 }
                           }

                        if (feat[i].has_text[0] == 'Y')
                           {
                            for(ii=1; ii<=feat[i].text_count; ii++)
                               {
                                text_index = feat[i].text + ii ;
                                text[text_index].x += (x_new - x_old) ;
                                text[text_index].y += (y_new - y_old) ;

                                if ( db_opened[0] == 'Y' )
                                   {
                                    // Update Feature TEXT X,Y
                                    feat_num = feat[i].num        ;
                                    x_base   = text[text_index].x ;
                                    y_base   = text[text_index].y ;

                                    
/*
EXEC SQL UPDATE TEXT
                                             SET X1 = :x_base ,
                                                 Y1 = :y_base
                                             WHERE FEAT_NUM = :feat_num ;
*/

{
#line 9799 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 9799 "geoIMS_main.sqc"
  sqlaaloc(2,3,50,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 9799 "geoIMS_main.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 9799 "geoIMS_main.sqc"
      sql_setdlist[0].sqldata = (void*)&x_base;
#line 9799 "geoIMS_main.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 9799 "geoIMS_main.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 9799 "geoIMS_main.sqc"
      sql_setdlist[1].sqldata = (void*)&y_base;
#line 9799 "geoIMS_main.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 9799 "geoIMS_main.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 9799 "geoIMS_main.sqc"
      sql_setdlist[2].sqldata = (void*)&feat_num;
#line 9799 "geoIMS_main.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 9799 "geoIMS_main.sqc"
      sqlasetdata(2,0,3,sql_setdlist,0L,0L);
    }
#line 9799 "geoIMS_main.sqc"
  sqlacall((unsigned short)24,31,2,0,0L);
#line 9799 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 9799 "geoIMS_main.sqc"

                                    
/*
EXEC SQL COMMIT WORK ;
*/

{
#line 9800 "geoIMS_main.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 9800 "geoIMS_main.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 9800 "geoIMS_main.sqc"
  sqlastop(0L);
}

#line 9800 "geoIMS_main.sqc"
      //  CHECKERR ("UPDATE");
                                   }
                               }

                           }

                        return ;
                       }
                   }

                x1_db = x2_db ;
                y1_db = y2_db ;
                break ;
            }
    } /* Type 2 loop */
 }

}

/*------------------------------------------------------------------------*/
/*---------- CALL BACKS ----- CALL BACKS ----- CALL BACKS ----------------*/
/*----------- CALL BACKS ----- CALL BACKS ----- CALL BACKS ---------------*/
/*------------ CALL BACKS ----- CALL BACKS ----- CALL BACKS --------------*/
/*------------- CALL BACKS ----- CALL BACKS ----- CALL BACKS -------------*/
/*-------------- CALL BACKS ----- CALL BACKS ----- CALL BACKS ------------*/
/*--------------- CALL BACKS ----- CALL BACKS ----- CALL BACKS -----------*/
/*------------------------------------------------------------------------*/


/*------------------------------------------------------------------------*/
/*                            mouse_downCB()                              */
/*------------------------------------------------------------------------*/
/*
void mouse_downCB(Widget w, XtPointer Data, XEvent *event)
{

 switch (draw_fun)
   {
    case GETXYPT:                   //  Get xy point

        point.xscreen = event->xbutton.x ;
        point.yscreen = event->xbutton.y ;

        point.xdb = (x_screen * ONE_PIXEL) + x_min ;
        point.ydb = y_max - (y_screen * ONE_PIXEL) ;

    break ;


    case WINDOW:                    //   2 pt window

      switch (point_counter)
       {
        case 1:
             x_min1 = x_min ; // Temprarley Save original xy coord.
             y_min1 = y_min ;
             x_max1 = x_max ;
             y_max1 = y_max ;

             x1_screen = event->xbutton.x ;
             y1_screen = event->xbutton.y ;
             x1_db = (x1_screen * ONE_PIXEL) + x_min ;
             y1_db = y_max - (y1_screen * ONE_PIXEL) ;

             XSetForeground(MainDisplay,xor_gc,gray.pixel);

             // Erase Cross Hair
             XDrawLine(MainDisplay,XtWindow(w),xor_gc,0,y_last,499,y_last);
             XDrawLine(MainDisplay,XtWindow(w),xor_gc,x_last,0,x_last,499);

             // Erase Correlation Window
             XDrawLine(MainDisplay,XtWindow(w),xor_gc,x_last+cursor_size,y_last,x_last,y_last+cursor_size);
             XDrawLine(MainDisplay,XtWindow(w),xor_gc,x_last+cursor_size,y_last,x_last,y_last-cursor_size);
             XDrawLine(MainDisplay,XtWindow(w),xor_gc,x_last-cursor_size,y_last,x_last,y_last+cursor_size);
             XDrawLine(MainDisplay,XtWindow(w),xor_gc,x_last-cursor_size,y_last,x_last,y_last-cursor_size);

             move_fun = RUBBERBOX ;
             point_counter++ ;
             break ;

        case 2:
             x2_screen = event->xbutton.x ;
             y2_screen = event->xbutton.y ;
             x2_db = (x2_screen * ONE_PIXEL) + x_min ;
             y2_db = y_max - (y2_screen * ONE_PIXEL) ;

            //----------------------- CASE I ---------------------------
             if ( x1_db < x2_db && y1_db > y2_db )
                { x_min  = x1_db ;
                  y_min  = y2_db ;
                  x_max  = x2_db ;
                  y_max  = y1_db ;
                  x_diff = x_max - x_min ;
                  y_diff = y_max - y_min ;

                  if (x_diff > y_diff) { xy_diff = (x_diff - y_diff) / 2 ;
                                         y_min   = y_min - xy_diff       ;
                                         y_max   = y_max + xy_diff       ; }

                  if (y_diff > x_diff) { xy_diff = (y_diff - x_diff) / 2 ;
                                         x_min   = x_min - xy_diff       ;
                                         x_max   = x_max + xy_diff       ; }
                }
            //----------------------- CASE II --------------------------
             if ( x1_db > x2_db && y1_db > y2_db )
                { x_min  = x2_db ;
                  y_min  = y2_db ;
                  x_max  = x1_db ;
                  y_max  = y1_db ;
                  x_diff = x_max - x_min ;
                  y_diff = y_max - y_min ;

                  if (x_diff > y_diff) { xy_diff = (x_diff - y_diff) / 2 ;
                                         y_min   = y_min - xy_diff       ;
                                         y_max   = y_max + xy_diff       ; }

                  if (y_diff > x_diff) { xy_diff = (y_diff - x_diff) / 2 ;
                                         x_min   = x_min - xy_diff       ;
                                         x_max   = x_max + xy_diff       ; }
                }
            //----------------------- CASE III -------------------------
             if ( x1_db < x2_db && y1_db < y2_db )
                { x_min  = x1_db ;
                  y_min  = y1_db ;
                  x_max  = x2_db ;
                  y_max  = y2_db ;
                  x_diff = x_max - x_min ;
                  y_diff = y_max - y_min ;

                  if (x_diff > y_diff) { xy_diff = (x_diff - y_diff) / 2 ;
                                         y_min   = y_min - xy_diff       ;
                                         y_max   = y_max + xy_diff       ; }

                  if (y_diff > x_diff) { xy_diff = (y_diff - x_diff) / 2 ;
                                         x_min   = x_min - xy_diff       ;
                                         x_max   = x_max + xy_diff       ; }
                }
            //----------------------- CASE IV  -------------------------
             if ( x1_db > x2_db && y1_db < y2_db )
                { x_min  = x2_db ;
                  y_min  = y1_db ;
                  x_max  = x1_db ;
                  y_max  = y2_db ;
                  x_diff = x_max - x_min ;
                  y_diff = y_max - y_min ;

                  if (x_diff > y_diff) { xy_diff = (x_diff - y_diff) / 2 ;
                                         y_min   = y_min - xy_diff       ;
                                         y_max   = y_max + xy_diff       ; }

                  if (y_diff > x_diff) { xy_diff = (y_diff - x_diff) / 2 ;
                                         x_min   = x_min - xy_diff       ;
                                         x_max   = x_max + xy_diff       ; }
                }

             // wait_cursor()          ;

             y_diff = y_max - y_min ;
             switch (DB_UNIT)
                  {
                   case MM: scale = ( y_diff * .1   ) / SCREEN_CM ; break ;
                   case CM: scale = ( y_diff * 1.   ) / SCREEN_CM ; break ;
                   case DM: scale = ( y_diff * 10.  ) / SCREEN_CM ; break ;
                   case  M: scale = ( y_diff * 100. ) / SCREEN_CM ; break ;
                   case KM: scale = ( y_diff * 1000.) / SCREEN_CM ; break ;
                   default: scale = ( y_diff * 100. ) / SCREEN_CM ;
                            fprintf(stderr,"ERROR : Data Base Unit not Defined\n");
                            break ;
                  }

             if ( scale >= 1 )
                {
                 draw_all()      ;
                 display_scale() ;
                }
             else
                {
                 cls_flag = 1   ;

                 x_min = x_min1 ; // Restore xy coord. before Window
                 y_min = y_min1 ;
                 x_max = x_max1 ;
                 y_max = y_max1 ;

                 xstr = XmStringCreate(" INFO : Selected Window results in Zero Scale ..",CS);
                 XtSetArg(args[0], XmNlabelString , xstr);
                 XtSetValues(output_label,args,1);
                }

             move_fun = CROSSHAIR ;
             // normal_cursor()      ;

             point_counter = 1    ;
             draw_fun = WINDOW    ;
             break ;
       }
    break ;


    case CPOINT:                   //  Set New Screen Center Point

        x_screen = event->xbutton.x ;
        y_screen = event->xbutton.y ;

        x_db = (x_screen * ONE_PIXEL) + x_min ;
        y_db = y_max - (y_screen * ONE_PIXEL) ;

        x_diff = x_max - x_min ;
        y_diff = y_max - y_min ;

        x_min = x_db - x_diff /2 ;
        y_min = y_db - y_diff /2 ;
        x_max = x_db + x_diff /2 ;
        y_max = y_db + y_diff /2 ;

        // wait_cursor();
        draw_all()      ;
        // normal_cursor()      ;
    break ;


    case ADDPOINT:               //  Add point feature

      switch (point_counter)
       {
        case 1:
             feat_count++ ;
             text_index = text_LAST ;

             x_screen = x1_screen = event->xbutton.x ;
             y_screen = y1_screen = event->xbutton.y ;

             x1_db = (x_screen * ONE_PIXEL) + x_min ;
             y1_db = y_max - (y_screen * ONE_PIXEL) ;

             feat[feat_count].num = feat[feat_count-1].num + 1 ;
             strcpy (feat[feat_count].code , add.code )        ;

             feat[feat_count].type          = add.type       ;
             feat[feat_count].layer         = add.layer      ;
             feat[feat_count].network       = add.network    ;
             feat[feat_count].scale_range[0]= 'Y'            ;
             feat[feat_count].scale_range[1]= 'Y'            ;
             feat[feat_count].scale_range[2]= 'Y'            ;
             feat[feat_count].scale_range[3]= 'Y'            ;
             feat[feat_count].scale_range[4]= 'Y'            ;
             feat[feat_count].displayed[0]  = 'Y'            ;
             feat[feat_count].selectble[0]  = 'Y'            ;
             feat[feat_count].has_attrib[0] = 'Y'            ;
             feat[feat_count].has_text[0]   = 'Y'            ;
             feat[feat_count].color         = add.color      ;
             feat[feat_count].linetype      = add.linetype   ;
             feat[feat_count].linewidth     = add.linewidth  ;
             feat[feat_count].xbase         = x1_db          ;
             feat[feat_count].ybase         = y1_db          ;
             feat[feat_count].xy_count      = 0              ;
             feat[feat_count].symb_num      = add.symb_num   ;
             feat[feat_count].symb_size     = add.symb_size  ;
             feat[feat_count].symb_angle    = add.symb_angle ;
             feat[feat_count].text_count    = add.text_count ;
             feat[feat_count].text          = text_index++   ;

             set_color     (feat[feat_count].color);
             set_line_attr (feat[feat_count].linetype,feat[feat_count].linewidth);

             cls_flag = 2 ;
             move_fun = ROTATESYMB ;
             point_counter++ ;
             break ;


        case 2:
             draw_pix_symb(feat[feat_count].symb_num,x_screen,y_screen,feat[feat_count].color,
                           (float)feat[feat_count].symb_size,feat[feat_count].symb_angle);

             if ( add.text_count != 0 )
                {
                 // wait_cursor();
                 xstr = XmStringCreate("Text attached to Point Feature",CS);
                 n=0;
                 XtSetArg(args[n], XmNdialogTitle  , xstr);n++;
                 XtSetArg(args[n] , XmNwidth       ,  300);n++;
                 XtSetArg(args[n] , XmNheight      ,  130);n++;
                 PD = XmCreatePromptDialog(MainForm,"PD",args,n);
                 XtAddCallback(PD,XmNokCallback,textCB,MainForm);
                 XtManageChild(PD);

                 XtAddGrab( PD,True,False );
                }
             else
                {
                 if ( db_opened[0] == 'Y' )
                    {

                     insert_feature(feat_count);
                    }
                 else
                    {
                     feat[feat_count].selectble[0]  = 'I' ;
                     printf ("WARNING : This feature will not be added to Database ! \n");
                    }

                 move_fun  = CROSSHAIR ;
                 draw_fun  = NONE ;
                 update_layer() ;
                 break ;
                }

             point_counter++ ;
             break ;

        case 3:
             x_screen  = x1_screen = event->xbutton.x ;
             y_screen  = y1_screen = event->xbutton.y ;
             x1_db = (x_screen * ONE_PIXEL) + x_min ;
             y1_db = y_max - (y_screen * ONE_PIXEL) ;

             text[text_index].x    = x1_db ;
             text[text_index].y    = y1_db ;
             text[text_index].size = 30    ;
             text[text_index].just = 1     ;
             text[text_index].font = 2     ;

             move_fun = RUBBERPAN ;
             point_counter++ ;
             break ;

        case 4:
             // Delete the rubber-pan line
             XDrawLine(MainDisplay,XtWindow(w),xor_gc,x1_screen,y1_screen,x2_screen,y2_screen);

             x2_db = (event->xbutton.x * ONE_PIXEL) + x_min ;
             y2_db = y_max - (event->xbutton.y * ONE_PIXEL) ;

             text[text_index].angle = atan2((y2_db-y1_db),(x2_db-x1_db)) * DEG2RAD ;

             set_color     (feat[feat_count].color);
             set_line_attr (feat[feat_count].linetype,feat[feat_count].linewidth);

             draw_text(x_screen,y_screen,feat[feat_count].color,text[text_index].size,
                      text_index,text[text_index].angle);

             text_LAST = text_LAST + 1 ;

             if ( db_opened[0] == 'Y' )
                {
                 insert_feature(feat_count);
                }
             else
                {
                 printf ("WARNING : This feature will not be added to Database ! \n");
                }

             move_fun  = CROSSHAIR ;
             draw_fun  = NONE ;
             update_layer() ;
             break ;
       }
      break ;


    case ADDOPPT:               //  Add open point feature

      search_status = NOTFOUND ;
      distance      = 99999999 ;

      x_mouse = (event->xbutton.x * ONE_PIXEL) + x_min ;
      y_mouse = y_max - (event->xbutton.y * ONE_PIXEL) ;

      feat_search();

      if ( search_status == NOTFOUND )
         {
          xstr = XmStringCreate(" INFO : Cannot correlate on mvfeeder, Please retry !",CS);
          XtSetArg(args[0],XmNlabelString,xstr);
          XtSetValues(output_label,args,1);
          // normal_cursor();
         }
     else
         {
          switch (point_counter)
           {
            case 1:
             if ( strcmp(feat[selected_feat].code,"mvfeeder") == 0 )
                {
                 highlight_feature (selected_feat);
                 point_counter++ ;
                }
              else
                {
                 xstr = XmStringCreate(" INFO : Cannot correlate on mvfeeder, Please retry !",CS);
                 XtSetArg(args[0],XmNlabelString,xstr);
                 XtSetValues(output_label,args,1);
                 // normal_cursor();
                }
             break ;

            case 2:
             // wait_cursor();

             feat_count++ ;
             text_index = text_LAST ;

             x_screen = event->xbutton.x ;
             y_screen = event->xbutton.y ;

             x1_db = (x_screen * ONE_PIXEL) + x_min ;
             y1_db = y_max - (y_screen * ONE_PIXEL) ;

             feat[feat_count].num = feat[feat_count-1].num + 1 ;
             strcpy (feat[feat_count].code , add.code )        ;

             feat[feat_count].type          = add.type       ;
             feat[feat_count].layer         = add.layer      ;
             feat[feat_count].network       = add.network    ;
             feat[feat_count].scale_range[0]= 'Y'            ;
             feat[feat_count].scale_range[1]= 'Y'            ;
             feat[feat_count].scale_range[2]= 'Y'            ;
             feat[feat_count].scale_range[3]= 'Y'            ;
             feat[feat_count].scale_range[4]= 'Y'            ;
             feat[feat_count].displayed[0]  = 'Y'            ;
             feat[feat_count].selectble[0]  = 'Y'            ;
             feat[feat_count].has_attrib[0] = 'Y'            ;
             feat[feat_count].has_text[0]   = 'Y'            ;
             feat[feat_count].color         = add.color      ;
             feat[feat_count].linetype      = add.linetype   ;
             feat[feat_count].linewidth     = add.linewidth  ;
             feat[feat_count].xbase         = x1_db          ;
             feat[feat_count].ybase         = y1_db          ;
             feat[feat_count].xy_count      = 0              ;
             feat[feat_count].symb_num      = add.symb_num   ;
             feat[feat_count].symb_size     = add.symb_size  ;
             feat[feat_count].symb_angle    = add.symb_angle ;
             feat[feat_count].text_count    = add.text_count ;
             feat[feat_count].text          = text_index++   ;

             set_color     (feat[feat_count].color);
             set_line_attr (feat[feat_count].linetype,feat[feat_count].linewidth);

             draw_pix_symb(feat[feat_count].symb_num,x_screen,y_screen,feat[feat_count].color,
                    (float)feat[feat_count].symb_size,feat[feat_count].symb_angle);

             if ( db_opened[0] == 'Y' )
                {
                 insert_feature(feat_count);

                 arc   = feat[selected_feat].num ;
                 node2 = feat[feat_count].num    ;

                 EXEC SQL SELECT  E_NODE
                          INTO    :other
                          FROM    connectivity
                          Where   ARC = :arc ;

                 EXEC SQL UPDATE CONNECTIVITY
                          SET    E_NODE = :node2 ,
                                 OTHER  = :other
                          WHERE  ARC    = :arc ;

                 // CHECKERR ("UPDATE");
                 EXEC SQL COMMIT WORK ;

                 printf ("ARC   = %d\n",arc   );
                 printf ("e_node = %d\n",node2);
                 printf ("other  = %d\n",other);
                }
             else
                {
                 feat[feat_count].selectble[0]  = 'I' ;
                 printf ("WARNING : This feature will not be added to Database ! \n");
                }

             move_fun  = CROSSHAIR ;
             draw_fun  = NONE ;
             cls_flag  = 1 ;
             // normal_cursor();
             update_layer() ;
             break ;
            }
         }

      break ;



    case ADDTEXT:               //  Add Text feature

      switch (point_counter)
       {
        case 1:
             x_screen = x1_screen = event->xbutton.x ;
             y_screen = y1_screen = event->xbutton.y ;

             x1_db = (x_screen * ONE_PIXEL) + x_min ;
             y1_db = y_max - (y_screen * ONE_PIXEL) ;

             feat[feat_count].num = feat[feat_count-1].num + 1 ;
             strcpy (feat[feat_count].code ,"text")         ;
             feat[feat_count].type          = 1             ;
             feat[feat_count].layer         = 33            ;
             feat[feat_count].network       = 0             ;
             feat[feat_count].scale_range[0]= 'Y'           ;
             feat[feat_count].scale_range[1]= 'Y'           ;
             feat[feat_count].scale_range[2]= 'Y'           ;
             feat[feat_count].scale_range[3]= 'Y'           ;
             feat[feat_count].scale_range[4]= 'Y'           ;
             feat[feat_count].displayed[0]  = 'Y'           ;
             feat[feat_count].selectble[0]  = 'Y'           ;
             feat[feat_count].has_attrib[0] = 'Y'           ;
             feat[feat_count].has_text[0]   = 'Y'           ;
             feat[feat_count].color         = white.pixel   ;
             feat[feat_count].linetype      = 1             ;
             feat[feat_count].linewidth     = 2             ;
             feat[feat_count].xbase         = x1_db         ;
             feat[feat_count].ybase         = y1_db         ;
             feat[feat_count].xy_count      = 0             ;
             feat[feat_count].symb_num      = 0             ;
             feat[feat_count].symb_size     = 30            ;
             feat[feat_count].symb_angle    = 0             ;
             feat[feat_count].text_count    = 1             ;

             text[text_index].x    = x1_db ;
             text[text_index].y    = y1_db ;
             text[text_index].size = 30    ;
             text[text_index].just = 1     ;
             text[text_index].font = 2     ;

             move_fun = RUBBERPAN ;
             point_counter++ ;
             break ;

        case 2:
             // Delete the rubber-pan line
             XDrawLine(MainDisplay,XtWindow(w),xor_gc,x1_screen,y1_screen,x2_screen,y2_screen);

             x2_db = (event->xbutton.x * ONE_PIXEL) + x_min ;
             y2_db = y_max - (event->xbutton.y * ONE_PIXEL) ;

             text[text_index].angle = atan2((y2_db-y1_db),(x2_db-x1_db)) * DEG2RAD ;

             set_color     (feat[feat_count].color);
             set_line_attr (feat[feat_count].linetype,feat[feat_count].linewidth);

             draw_text(x_screen,y_screen,feat[feat_count].color,text[text_index].size,
                      text_index,text[text_index].angle);

             text_LAST = text_LAST + 1 ;

             if ( db_opened[0] == 'Y' )
                {
                 insert_feature(feat_count);
                }
             else
                {
                 feat[feat_count].selectble[0]  = 'I' ;
                 printf ("WARNING : This feature will not be added to Database ! \n");
                }

             move_fun  = CROSSHAIR ;
             draw_fun  = NONE ;
             update_layer() ;
             break ;
       }
      break ;



    case ADDTEXT2F:               //  Add Text to Exsisting Feature

      switch (point_counter)
       {
        case 1:
          distance = 99999999 ;

          x_mouse = (event->xbutton.x * ONE_PIXEL) + x_min ;
          y_mouse = y_max - (event->xbutton.y * ONE_PIXEL) ;

          feat_search();

          if ( search_status == NOTFOUND )
             {
              xstr  = XmStringCreate("INFO",CS);
              xstr1 = XmStringCreate("Cannot correlate, Please retry !",CS);
              n=0;
              XtSetArg(args[n] , XmNdialogTitle   ,        xstr);n++;
              XtSetArg(args[n] , XmNmessageString ,       xstr1);n++;
              XtSetArg(args[n] , XmNborderColor   , white.pixel);n++;
              XtSetArg(args[n] , XmNforeground    , black.pixel);n++;
              XtSetArg(args[n] , XmNbackground    , lgray.pixel);n++;

              PD = XmCreateErrorDialog(MainForm,"PD",args,n);
              XtManageChild(PD);

              cls_flag = 0   ;
              // normal_cursor();
             }
          else
             {
              highlight_feature (selected_feat);
              // wait_cursor() ;

              if (feat[selected_feat].has_text[0] == 'Y')
                 {
                  int old_text_index ;

                  old_text_index = feat[selected_feat].text ;
                  text_index = text_LAST ;

                  feat[selected_feat].text = text_index++ ;

                  for (i=1; i<= feat[selected_feat].text_count ; i++)
                      {
                       text[text_index].x     = text[old_text_index+i].x     ;
                       text[text_index].y     = text[old_text_index+i].y     ;
                       text[text_index].size  = text[old_text_index+i].size  ;
                       text[text_index].just  = text[old_text_index+i].just  ;
                       text[text_index].font  = text[old_text_index+i].font  ;
                       text[text_index].angle = text[old_text_index+i].angle ;
                       strcpy(text[text_index].string,text[old_text_index+i].string);

                       text_index++ ;
                      }

                  feat[selected_feat].text_count++  ;
                 }
              else
                 {
                  text_index = text_LAST ;

                  feat[selected_feat].has_text[0] = 'Y'          ;
                  feat[selected_feat].text        = text_index++ ;
                  feat[selected_feat].text_count  = 1            ;
                 }

              point_counter++ ;

              xstr = XmStringCreate("Enter Attached Text",CS);
              n=0;
              XtSetArg(args[n], XmNdialogTitle , xstr);n++;
              XtSetArg(args[n], XmNwidth       ,  300);n++;
              XtSetArg(args[n], XmNheight      ,  130);n++;
              PD = XmCreatePromptDialog(MainForm,"PD",args,n);
              XtAddCallback(PD,XmNokCallback,textCB,MainForm);
              XtManageChild(PD);

              XtAddGrab( PD,True,False );
             }
          break ;

        case 2:
          x_screen = x1_screen = event->xbutton.x ;
          y_screen = y1_screen = event->xbutton.y ;

          x1_db = (x_screen * ONE_PIXEL) + x_min ;
          y1_db = y_max - (y_screen * ONE_PIXEL) ;

          text[text_index].x    = x1_db ;
          text[text_index].y    = y1_db ;
          text[text_index].size = 30    ;
          text[text_index].just = 1     ;
          text[text_index].font = 2     ;

          move_fun = RUBBERPAN ;
          point_counter++ ;
          break ;

        case 3:
          x2_db = (event->xbutton.x * ONE_PIXEL) + x_min ;
          y2_db = y_max - (event->xbutton.y * ONE_PIXEL) ;

          text[text_index].angle = atan2((y2_db-y1_db),(x2_db-x1_db)) * DEG2RAD ;

          set_color     (feat[selected_feat].color);
          set_line_attr (feat[selected_feat].linetype,feat[selected_feat].linewidth);

          draw_text(x_screen,y_screen,feat[selected_feat].color,text[text_index].size,text_index,text[text_index].angle);

          text_LAST = text_LAST + feat[selected_feat].text_count ;  //+1

          if ( db_opened[0] == 'Y' )
             {
              insert_text (selected_feat);
             }
          else
             {
              printf ("WARNING : This Modification will not be saved to Database ! \n");
             }

          move_fun  = CROSSHAIR ;
          draw_fun  = NONE ;
          update_layer() ;
          // normal_cursor();
          break ;
       }
      break ;


    case ADDNODE:               //  Add NODE point feature

      switch (point_counter)
       {
        case 1:
             feat_count++ ;
             text_index   = text_LAST ;

             x_screen = event->xbutton.x ;
             y_screen = event->xbutton.y ;

             x1_db = (x_screen * ONE_PIXEL) + x_min ;
             y1_db = y_max - (y_screen * ONE_PIXEL) ;

             feat[feat_count].num = feat[feat_count-1].num + 1 ;
             strcpy (feat[feat_count].code ,"node")         ;

             feat[feat_count].type          = 1             ;
             feat[feat_count].layer         = 31            ;
             feat[feat_count].network       = 0             ;
             feat[feat_count].scale_range[0]= 'Y'           ;
             feat[feat_count].scale_range[1]= 'Y'           ;
             feat[feat_count].scale_range[2]= 'Y'           ;
             feat[feat_count].scale_range[3]= 'Y'           ;
             feat[feat_count].scale_range[4]= 'Y'           ;
             feat[feat_count].displayed[0]  = 'Y'           ;
             feat[feat_count].selectble[0]  = 'Y'           ;
             feat[feat_count].has_attrib[0] = 'Y'           ;
             feat[feat_count].has_text[0]   = 'Y'           ;
             feat[feat_count].color         = yellow.pixel  ;
             feat[feat_count].linetype      = 1             ;
             feat[feat_count].linewidth     = 2             ;
             feat[feat_count].xbase         = x1_db         ;
             feat[feat_count].ybase         = y1_db         ;
             feat[feat_count].xy_count      = 0             ;
             feat[feat_count].symb_num      = 6             ;
             feat[feat_count].symb_size     = 50            ;
             feat[feat_count].symb_angle    = 0             ;
             feat[feat_count].text_count    = 1             ;
             feat[feat_count].text          = text_index++  ;

             set_color     (feat[feat_count].color);
             set_line_attr (feat[feat_count].linetype,feat[feat_count].linewidth);

             draw_pix_symb(feat[feat_count].symb_num,x_screen,y_screen,feat[feat_count].color,
                    (float)feat[feat_count].symb_size,feat[feat_count].symb_angle);


             if ( db_opened[0] == 'Y' )
                {
                 EXEC SQL SELECT MAX(NODE_NUM)
                 INTO   :node1
                 FROM   NODE ;

                 node1++ ;
                 sprintf (text[text_index].string,"%d",node1);
                }
             else
                {
                 xstr = XmStringCreate("Text attached to Point Feature",CS);
                 n=0;
                 XtSetArg(args[n], XmNdialogTitle  , xstr);n++;
                 XtSetArg(args[n] , XmNwidth       ,  300);n++;
                 XtSetArg(args[n] , XmNheight      ,  130);n++;
                 PD = XmCreatePromptDialog(MainForm,"PD",args,n);
                 XtAddCallback(PD,XmNokCallback,textCB,MainForm);
                 XtManageChild(PD);
                }

             point_counter++ ;
             break ;

        case 2:
             x_screen  = x1_screen = event->xbutton.x ;
             y_screen  = y1_screen = event->xbutton.y ;
             x1_db = (x_screen * ONE_PIXEL) + x_min ;
             y1_db = y_max - (y_screen * ONE_PIXEL) ;

             text[text_index].x    = x1_db ;
             text[text_index].y    = y1_db ;
             text[text_index].size = 50    ;
             text[text_index].just = 1     ;
             text[text_index].font = 2     ;

             move_fun = RUBBERPAN ;
             point_counter++ ;
             break ;

        case 3:
             x2_db = (event->xbutton.x * ONE_PIXEL) + x_min ;
             y2_db = y_max - (event->xbutton.y * ONE_PIXEL) ;

             text[text_index].angle = atan2((y2_db-y1_db),(x2_db-x1_db)) * DEG2RAD ;

             set_color     (feat[feat_count].color);
             set_line_attr (feat[feat_count].linetype,feat[feat_count].linewidth);

             draw_text(x_screen,y_screen,feat[feat_count].color,text[text_index].size,
                      text_index,text[text_index].angle);

             text_LAST = text_LAST + 1 ;

             if ( db_opened[0] == 'Y' )
                {
                 insert_feature(feat_count);
                }
             else
                {
                 feat[feat_count].selectble[0]  = 'I' ;
                 printf ("WARNING : This feature will not be added to Database ! \n");
                }

             move_fun  = CROSSHAIR ;
             draw_fun  = NONE ;
             update_layer() ;
             break ;
       }
      break ;


    case ADDACCDENT:               //  Add ACCDENT point feature

      switch (point_counter)
       {
        case 1:
             feat_count++ ;
             text_index   = text_LAST ;

             x_screen = event->xbutton.x ;
             y_screen = event->xbutton.y ;

             x1_db = (x_screen * ONE_PIXEL) + x_min ;
             y1_db = y_max - (y_screen * ONE_PIXEL) ;

             feat[feat_count].num = feat[feat_count-1].num + 1 ;
             strcpy (feat[feat_count].code ,"Accdent")         ;

             feat[feat_count].type          = 1             ;
             feat[feat_count].layer         = 31            ;
             feat[feat_count].network       = 0             ;
             feat[feat_count].scale_range[0]= 'Y'           ;
             feat[feat_count].scale_range[1]= 'Y'           ;
             feat[feat_count].scale_range[2]= 'Y'           ;
             feat[feat_count].scale_range[3]= 'Y'           ;
             feat[feat_count].scale_range[4]= 'Y'           ;
             feat[feat_count].displayed[0]  = 'Y'           ;
             feat[feat_count].selectble[0]  = 'Y'           ;
             feat[feat_count].has_attrib[0] = 'Y'           ;
             feat[feat_count].has_text[0]   = 'Y'           ;
             feat[feat_count].color         = orange.pixel  ;
             feat[feat_count].linetype      = 1             ;
             feat[feat_count].linewidth     = 2             ;
             feat[feat_count].xbase         = x1_db         ;
             feat[feat_count].ybase         = y1_db         ;
             feat[feat_count].xy_count      = 0             ;
             feat[feat_count].symb_num      = 12            ;
             feat[feat_count].symb_size     = 50            ;
             feat[feat_count].symb_angle    = 0             ;
             feat[feat_count].text_count    = 1             ;
             feat[feat_count].text          = text_index++  ;

             set_color     (feat[feat_count].color);
             set_line_attr (feat[feat_count].linetype,feat[feat_count].linewidth);

             draw_pix_symb(feat[feat_count].symb_num,x_screen,y_screen,feat[feat_count].color,
                    (float)feat[feat_count].symb_size,feat[feat_count].symb_angle);

             xstr = XmStringCreate("Text attached to Point Feature",CS);
             n=0;
             XtSetArg(args[n], XmNdialogTitle  , xstr);n++;
             XtSetArg(args[n] , XmNwidth       ,  300);n++;
             XtSetArg(args[n] , XmNheight      ,  130);n++;
             PD = XmCreatePromptDialog(MainForm,"PD",args,n);
             XtAddCallback(PD,XmNokCallback,textCB,MainForm);
             XtManageChild(PD);

             point_counter++ ;
             break ;

        case 2:
             x_screen  = x1_screen = event->xbutton.x ;
             y_screen  = y1_screen = event->xbutton.y ;
             x1_db = (x_screen * ONE_PIXEL) + x_min ;
             y1_db = y_max - (y_screen * ONE_PIXEL) ;

             text[text_index].x    = x1_db ;
             text[text_index].y    = y1_db ;
             text[text_index].size = 50    ;
             text[text_index].just = 1     ;
             text[text_index].font = 2     ;

             move_fun = RUBBERPAN ;
             point_counter++ ;
             break ;

        case 3:
             x2_db = (event->xbutton.x * ONE_PIXEL) + x_min ;
             y2_db = y_max - (event->xbutton.y * ONE_PIXEL) ;

             text[text_index].angle = atan2((y2_db-y1_db),(x2_db-x1_db)) * DEG2RAD ;

             set_color     (feat[feat_count].color);
             set_line_attr (feat[feat_count].linetype,feat[feat_count].linewidth);

             draw_text(x_screen,y_screen,feat[feat_count].color,text[text_index].size,
                      text_index,text[text_index].angle);

             text_LAST = text_LAST + 1 ;
             move_fun  = CROSSHAIR ;
             draw_fun  = NONE ;
             update_layer() ;
             break ;
       }
      break ;


    case ADDLINE:                //  Add line feature

      switch (point_counter)
       {
        case 1:
             feat_count++ ;
             xy_index  = xy_LAST          ;
             x1_screen = event->xbutton.x ;
             y1_screen = event->xbutton.y ;
             x1_db = (x1_screen * ONE_PIXEL) + x_min ;
             y1_db = y_max - (y1_screen * ONE_PIXEL) ;

             feat[feat_count].num  = feat[feat_count-1].num + 1 ;
             strcpy (feat[feat_count].code ,add.code)           ;
             feat[feat_count].type          = add.type          ;
             feat[feat_count].layer         = add.layer         ;
             feat[feat_count].network       = add.network       ;
             feat[feat_count].scale_range[0]= 'Y'               ;
             feat[feat_count].scale_range[1]= 'Y'               ;
             feat[feat_count].scale_range[2]= 'Y'               ;
             feat[feat_count].scale_range[3]= 'Y'               ;
             feat[feat_count].scale_range[4]= 'Y'               ;
             feat[feat_count].displayed[0]  = 'Y'               ;
             feat[feat_count].selectble[0]  = 'Y'               ;
             feat[feat_count].has_attrib[0] = 'Y'               ;
             feat[feat_count].has_text[0]   = 'N'               ;
             feat[feat_count].color         = add.color         ;
             feat[feat_count].linetype      = add.linetype      ;
             feat[feat_count].linewidth     = add.linewidth     ;
             feat[feat_count].xbase         = x1_db             ;
             feat[feat_count].ybase         = y1_db             ;
             feat[feat_count].xy            = xy_index          ;
             feat[feat_count].text_count    = 0                 ;

             move_fun = RUBBERPAN ;
             point_counter++ ;
             break ;

        default:
             // Delete the rubber-pan line
             XDrawLine(MainDisplay,XtWindow(w),xor_gc,x1_screen,y1_screen,x2_screen,y2_screen);

             ii = point_counter - 1 ;
             x2_screen = event->xbutton.x ;
             y2_screen = event->xbutton.y ;
             x2_db = (x2_screen * ONE_PIXEL) + x_min ;
             y2_db = y_max - (y2_screen * ONE_PIXEL) ;

             x[xy_index+ii] = x2_db ;
             y[xy_index+ii] = y2_db ;

             set_color     (feat[feat_count].color);
             set_line_attr (feat[feat_count].linetype,feat[feat_count].linewidth);

             XDrawLine(MainDisplay,XtWindow(drawarea),copy_gc,x1_screen,y1_screen,x2_screen,y2_screen);
             XDrawLine(MainDisplay,Tile,copy_gc,x1_screen,y1_screen,x2_screen,y2_screen);

             x1_screen = x2_screen ;
             y1_screen = y2_screen ;


             if ( event->xbutton.button == 3 ) // (see /usr/lpp/X11/include/X11/Xlib.h line 614)
                {
                 move_fun = CROSSHAIR ;
                 draw_fun = NONE      ;

                 feat[feat_count].xend = x[xy_index + ii] ;
                 feat[feat_count].yend = y[xy_index + ii] ;
                 ii--;

                 feat[feat_count].xy_count = ii ;
                 xy_LAST = xy_LAST + ii ;

                 if ( db_opened[0] == 'Y' )
                    {
                     insert_feature(feat_count);
                    }
                 else
                    {
                     feat[feat_count].selectble[0]  = 'I' ;
                     printf ("WARNING : This feature will not be added to Database ! \n");
                    }

                 update_layer() ;
                 break ;
                }

             point_counter++ ;
             break ;

       }

      break ;


    case ADDPOLYGON:  //---------- Add polygon feature ------------
      break ;



    case ADDARC:                //  Add ARC line feature

      switch (point_counter)
       {
        case 1:
             feat_count++ ;
             xy_index  = xy_LAST          ;
             x1_screen = event->xbutton.x ;
             y1_screen = event->xbutton.y ;
             x1_db = (x1_screen * ONE_PIXEL) + x_min ;
             y1_db = y_max - (y1_screen * ONE_PIXEL) ;

             feat[feat_count].num  = feat[feat_count-1].num + 1 ;
             strcpy (feat[feat_count].code ,"street" )          ;
             feat[feat_count].type          = 2                 ;
             feat[feat_count].layer         = 31                ;
             feat[feat_count].network       = 1                 ;
             feat[feat_count].scale_range[0]= 'Y'               ;
             feat[feat_count].scale_range[1]= 'Y'               ;
             feat[feat_count].scale_range[2]= 'Y'               ;
             feat[feat_count].scale_range[3]= 'Y'               ;
             feat[feat_count].scale_range[4]= 'Y'               ;
             feat[feat_count].displayed[0]  = 'Y'               ;
             feat[feat_count].selectble[0]  = 'Y'               ;
             feat[feat_count].has_attrib[0] = 'Y'               ;
             feat[feat_count].has_text[0]   = 'N'               ;
             feat[feat_count].color         = pink.pixel        ;
             feat[feat_count].linetype      = 1                 ;
             feat[feat_count].linewidth     = 3                 ;
             feat[feat_count].xbase         = x1_db             ;
             feat[feat_count].ybase         = y1_db             ;
             feat[feat_count].xy            = xy_index          ;

             move_fun = RUBBERPAN ;
             point_counter++ ;
             break ;

        default:
             ii = point_counter - 1 ;
             x2_screen = event->xbutton.x ;
             y2_screen = event->xbutton.y ;
             x2_db = (x2_screen * ONE_PIXEL) + x_min ;
             y2_db = y_max - (y2_screen * ONE_PIXEL) ;

             x[xy_index+ii] = x2_db ;
             y[xy_index+ii] = y2_db ;

             set_color     (feat[feat_count].color);
             set_line_attr (feat[feat_count].linetype,feat[feat_count].linewidth);

             XDrawLine(MainDisplay,XtWindow(drawarea),copy_gc,x1_screen,y1_screen,x2_screen,y2_screen);
             XDrawLine(MainDisplay,Tile,copy_gc,x1_screen,y1_screen,x2_screen,y2_screen);

             x1_screen = x2_screen ;
             y1_screen = y2_screen ;


             if ( event->xbutton.button == 3 ) // (see /usr/lpp/X11/include/X11/Xlib.h line 614)
                {
                 move_fun = CROSSHAIR ;
                 draw_fun = NONE      ;

                 feat[feat_count].xend = x[xy_index + ii] ;
                 feat[feat_count].yend = y[xy_index + ii] ;
                 ii--;

                 feat[feat_count].xy_count = ii ;
                 xy_LAST = xy_LAST + ii ;

                 if ( db_opened[0] == 'Y' )
                    {
                     insert_feature(feat_count);
                    }
                 else
                    {
                     feat[feat_count].selectble[0]  = 'I' ;
                     printf ("WARNING : This feature will not be added to Database ! \n");
                    }

                 update_layer() ;
                 break ;
                }

             point_counter++ ;
             break ;
       }

      break ;


    case EDIT:        //-------------- Edit feature Attribute ---------------

      search_status = NOTFOUND ;
      distance      = 99999999 ;
      need_draw_all = 0        ;

      x_mouse = (event->xbutton.x * ONE_PIXEL) + x_min ;
      y_mouse = y_max - (event->xbutton.y * ONE_PIXEL) ;

      // wait_cursor();
      feat_search();

      if ( search_status == NOTFOUND )
         {
          xstr  = XmStringCreate("INFO",CS);
          xstr1 = XmStringCreate("Cannot correlate, Please retry !",CS);
          n=0;
          XtSetArg(args[n] , XmNdialogTitle   ,        xstr);n++;
          XtSetArg(args[n] , XmNmessageString ,       xstr1);n++;
          XtSetArg(args[n] , XmNborderColor   , white.pixel);n++;
          XtSetArg(args[n] , XmNforeground    , black.pixel);n++;
          XtSetArg(args[n] , XmNbackground    , lgray.pixel);n++;

          PD = XmCreateErrorDialog(MainForm,"PD",args,n);
          XtManageChild(PD);

          cls_flag = 1   ;
          // normal_cursor();
         }
     else
         {
          cls_flag = 1 ;
          highlight_feature (selected_feat);
          edit (MainForm);
         }

      draw_fun = EDIT ;
      break ;



    case EDITPIC:        //-------------- Edit feature Picture ---------------

      search_status = NOTFOUND ;
      distance      = 99999999 ;
      need_draw_all = 0        ;

      x_mouse = (event->xbutton.x * ONE_PIXEL) + x_min ;
      y_mouse = y_max - (event->xbutton.y * ONE_PIXEL) ;

      // wait_cursor();
      feat_search();

      if ( search_status == NOTFOUND )
         {
          xstr  = XmStringCreate("INFO",CS);
          xstr1 = XmStringCreate("Cannot correlate, Please retry !",CS);
          n=0;
          XtSetArg(args[n] , XmNdialogTitle   ,        xstr);n++;
          XtSetArg(args[n] , XmNmessageString ,       xstr1);n++;
          XtSetArg(args[n] , XmNborderColor   , white.pixel);n++;
          XtSetArg(args[n] , XmNforeground    , black.pixel);n++;
          XtSetArg(args[n] , XmNbackground    , lgray.pixel);n++;

          PD = XmCreateErrorDialog(MainForm,"PD",args,n);
          XtManageChild(PD);

          cls_flag = 1 ;
          // normal_cursor();
         }
     else
         {
          cls_flag = 1 ;
          highlight_feature (selected_feat);
          edit_pic (MainForm);
         }

      draw_fun = EDITPIC ;
      break ;



    case DISTANCE:  //------------ Calculate Distance -----------

      switch (point_counter)
       {
        case 1:
             x1_screen = event->xbutton.x ;
             y1_screen = event->xbutton.y ;

             XSetLineAttributes(MainDisplay,copy_gc,1,LineSolid,CapButt,JoinMiter);
             draw_pix_symb(25,x1_screen,y1_screen,cyan.pixel,(float)(12*ONE_PIXEL),0);

             x1_db = (x1_screen * ONE_PIXEL) + x_min ;
             y1_db = y_max - (y1_screen * ONE_PIXEL) ;
             point_counter++ ;
             move_fun = RUBBERPAN ;
             break ;

        default:
             x2_screen = event->xbutton.x ;
             y2_screen = event->xbutton.y ;

             XSetLineAttributes(MainDisplay,copy_gc,1,LineSolid,CapButt,JoinMiter);
             draw_pix_symb(25,x2_screen,y2_screen,cyan.pixel,(float)(12*ONE_PIXEL),0);
             // Draw line between 2 points at pixmap for screen refresh
             set_color(gray.pixel);
             XDrawLine(MainDisplay,Tile,copy_gc,x1_screen,y1_screen,x2_screen,y2_screen);

             x2_db = (x2_screen * ONE_PIXEL) + x_min ;
             y2_db = y_max - (y2_screen * ONE_PIXEL) ;

             x_diff = x2_db - x1_db ;
             y_diff = y2_db - y1_db ;

             distance = sqrt ( (x_diff * x_diff) + (y_diff * y_diff) ) ;

             sprintf (Message, " Distance = %.2f   %s",distance,DB_UNIT_NAME);

             xstr = XmStringCreate(Message,CS);
             XtSetArg(args[0], XmNlabelString ,  xstr);
             XtSetValues(output_label,args,1);
             point_counter = 1 ;
             move_fun = CROSSHAIR ;
             break ;
       }
      break ;

    case SHORTPATH:  //------------ Get Shortest Path Nodes ----------

      search_status = NOTFOUND ;
      distance      = 99999999 ;

      printf("\n\n\n short path function   \n\n\n");

      x_mouse = (event->xbutton.x * ONE_PIXEL) + x_min ;
      y_mouse = y_max - (event->xbutton.y * ONE_PIXEL) ;

      // feat_search();
      snap_to_feature("node");

      if ( search_status == NOTFOUND )
         {
          xstr  = XmStringCreate("INFO",CS);
          xstr1 = XmStringCreate("Cannot correlate, Please retry !",CS);
          n=0;
          XtSetArg(args[n] , XmNdialogTitle   ,        xstr);n++;
          XtSetArg(args[n] , XmNmessageString ,       xstr1);n++;
          XtSetArg(args[n] , XmNborderColor   , white.pixel);n++;
          XtSetArg(args[n] , XmNforeground    , black.pixel);n++;
          XtSetArg(args[n] , XmNbackground    , lgray.pixel);n++;

          PD = XmCreateErrorDialog(MainForm,"PD",args,n);
          XtManageChild(PD);

          cls_flag = 0   ;
          // normal_cursor();
         }
     else
         {
          if ( strcmp (feat[selected_feat].code,"node") == 0 )
             {
              highlight_feature (selected_feat);

              switch (point_counter)
                {
                 case 1:
                   // printf ("1st node feat num %d\n",feat[selected_feat].num );

                   feat_num = feat[selected_feat].num ;
                   EXEC SQL SELECT NODE_NUM
                   INTO   :node1
                   FROM   NODE
                   WHERE  FEAT_NUM = :feat_num ;

                   point_counter++ ;
                   break ;

                 default:
                   // printf ("2nd node feat num %d\n",feat[selected_feat].num );

                   feat_num = feat[selected_feat].num ;
                   EXEC SQL SELECT NODE_NUM
                   INTO   :node2
                   FROM   NODE
                   WHERE  FEAT_NUM = :feat_num ;


                   // printf("node1 = %d\n",node1);
                   // printf("node2 = %d\n",node2);

                   // wait_cursor();
                   cls_flag = 1 ;
                   if ( node1 == node2 )
                      {
                       xstr = XmStringCreate(" INFO : Error origin = dest, Please retry !",CS);
                       XtSetArg(args[0],XmNlabelString,xstr);
                       XtSetValues(output_label,args,1);
                       cls_flag = 1 ;
                       point_counter = 1 ;
                       draw_fun = SHORTPATH ;
                       // normal_cursor();
                      }
                   else
                      {
                       shortest_path( node1 , node2 );
                       point_counter = 1 ;
                       draw_fun = SHORTPATH ;
                       // normal_cursor();
                      }
                   break ;
                }
             }
         }
      break ;



    case BLD_STREET_CONN:  //------------ Build Connectivity betw ARC & Nodes ----------

      search_status = NOTFOUND ;
      distance      = 99999999 ;

      x_mouse = (event->xbutton.x * ONE_PIXEL) + x_min ;
      y_mouse = y_max - (event->xbutton.y * ONE_PIXEL) ;

      feat_search();

      if ( search_status == NOTFOUND )
         {
          xstr  = XmStringCreate("INFO",CS);
          xstr1 = XmStringCreate("Cannot correlate, Please retry !",CS);
          n=0;
          XtSetArg(args[n] , XmNdialogTitle   ,        xstr);n++;
          XtSetArg(args[n] , XmNmessageString ,       xstr1);n++;
          XtSetArg(args[n] , XmNborderColor   , white.pixel);n++;
          XtSetArg(args[n] , XmNforeground    , black.pixel);n++;
          XtSetArg(args[n] , XmNbackground    , lgray.pixel);n++;

          PD = XmCreateErrorDialog(MainForm,"PD",args,n);
          XtManageChild(PD);

          cls_flag = 0   ;
          // normal_cursor();
         }
     else
         {
          if ( strcmp(feat[selected_feat].code,"street") == 0 || strcmp(feat[selected_feat].code,"node") == 0 )
             {
              highlight_feature (selected_feat);

              switch (point_counter)
                {
                 case 1:
                   printf ("ARC feat num %d\n",feat[selected_feat].num );
                   arc       = feat[selected_feat].num ;
                   weight    = 30 ;
                   direction = 1  ;

                   point_counter++ ;
                   break ;

                 case 2:
                   printf ("1st Node feat num %d\n",feat[selected_feat].num );

                   feat_num = feat[selected_feat].num ;
                   EXEC SQL SELECT NODE_NUM
                   INTO   :node1
                   FROM   NODE
                   WHERE  FEAT_NUM = :feat_num ;

                   point_counter++ ;
                   break ;

                 default:
                   printf ("2nd Node feat num %d\n",feat[selected_feat].num );

                   feat_num = feat[selected_feat].num ;
                   EXEC SQL SELECT NODE_NUM
                   INTO   :node2
                   FROM   NODE
                   WHERE  FEAT_NUM = :feat_num ;

                   printf("node1 = %d\n",node1);
                   printf("node2 = %d\n",node2);

                   // wait_cursor();
                   cls_flag = 1 ;
                   if ( node1 == node2 )
                      {
                       xstr = XmStringCreate(" INFO : Error Arc have same Node, Please retry !",CS);
                       XtSetArg(args[0],XmNlabelString,xstr);
                       XtSetValues(output_label,args,1);
                       cls_flag = 1 ;
                       point_counter = 1 ;
                       // normal_cursor();
                      }
                   else
                      {
                       EXEC SQL INSERT INTO geoinfo.connectivity ( S_NODE, ARC, E_NODE, WEIGHT, DIRECTION )
                            VALUES (:node1  ,
                                    :arc    ,
                                    :node2  ,
                                    :weight ,
                                    :direction);

                       // CHECKERR ("INSERT INTO");
                       EXEC SQL COMMIT WORK ;

                       point_counter = 1 ;
                       // normal_cursor();
                      }
                   break ;
                }
             }
         }
      break ;

    case BLD_ELECTRIC_CONN:  //---------- Build Electric Connectivity betw ARC & Nodes ----------

      search_status = NOTFOUND ;
      distance      = 99999999 ;

      x_mouse = (event->xbutton.x * ONE_PIXEL) + x_min ;
      y_mouse = y_max - (event->xbutton.y * ONE_PIXEL) ;

      feat_search();

      if ( search_status == NOTFOUND )
         {
          xstr  = XmStringCreate("INFO",CS);
          xstr1 = XmStringCreate("Cannot correlate, Please retry !",CS);
          n=0;
          XtSetArg(args[n] , XmNdialogTitle   ,        xstr);n++;
          XtSetArg(args[n] , XmNmessageString ,       xstr1);n++;
          XtSetArg(args[n] , XmNborderColor   , white.pixel);n++;
          XtSetArg(args[n] , XmNforeground    , black.pixel);n++;
          XtSetArg(args[n] , XmNbackground    , lgray.pixel);n++;

          PD = XmCreateErrorDialog(MainForm,"PD",args,n);
          XtManageChild(PD);

          cls_flag = 0   ;
          // normal_cursor();
         }
     else
         {
          if ( strcmp(feat[selected_feat].code,"mvfeeder")   == 0  ||
               strcmp(feat[selected_feat].code,"substation") == 0  ||
               strcmp(feat[selected_feat].code,"grid")       == 0 )
             {
              highlight_feature (selected_feat);

              switch (point_counter)
                {
                 case 1:
                   arc = feat[selected_feat].num ;
                   point_counter++ ;
                   break ;

                 case 2:
                   node1 = feat[selected_feat].num ;
                   point_counter++ ;
                   break ;

                 default:
                   node2 = feat[selected_feat].num ;

                   printf("INFO : FEAT_NUM OF Start Node [%d]\n",node1);
                   printf("INFO : FEAT_NUM OF ARC        [%d]\n",arc  );
                   printf("INFO : FEAT_NUM OF End Node   [%d]\n",node2);

                   // wait_cursor();
                   cls_flag = 1 ;
                   if ( node1 == node2 )
                      {
                       xstr = XmStringCreate(" INFO : Error Arc have same Node, Please retry !",CS);
                       XtSetArg(args[0],XmNlabelString,xstr);
                       XtSetValues(output_label,args,1);
                       cls_flag = 1 ;
                       point_counter = 1 ;
                       // normal_cursor();
                      }
                   else
                      {
                       EXEC SQL INSERT INTO geoinfo.connectivity ( S_NODE, ARC, E_NODE )
                            VALUES (:node1, :arc, :node2 );

                       // CHECKERR ("INSERT INTO");
                       EXEC SQL COMMIT WORK ;

                       point_counter = 1 ;
                       // normal_cursor();
                      }
                   break ;
                }
             }
         }
      break ;


    case JOIN:  //--------------------- Join 2 Features ------------------------------

      search_status = NOTFOUND ;
      distance      = 99999999 ;

      x_mouse = (event->xbutton.x * ONE_PIXEL) + x_min ;
      y_mouse = y_max - (event->xbutton.y * ONE_PIXEL) ;

      feat_search();

      if ( search_status == NOTFOUND )
         {
          xstr = XmStringCreate(" ERROR : Cannot correlate, Please retry !",CS);
          XtSetArg(args[0],XmNlabelString,xstr);
          XtSetValues(output_label,args,1);
          cls_flag = 0    ;
          draw_fun = JOIN ;
         }
     else
         {
          if ( feat[selected_feat].type != 2 )
             {
              highlight_feature (selected_feat);

              xstr = XmStringCreate(" ERROR : Join apply only on line features, Please retry !",CS);
              XtSetArg(args[0],XmNlabelString,xstr);
              XtSetValues(output_label,args,1);
              cls_flag = 0    ;
              draw_fun = JOIN ;
              printf("feat_1 %d \n",feat_1);
              printf("feat_2 %d \n",feat_2);
              printf("point counter  %d \n",point_counter);
             }
          else
             {
              highlight_feature (selected_feat);

              switch (point_counter)
                {
                 case 1:
                   feat_1 = selected_feat ;
                   point_counter++ ;
                   break ;


                 default:
                   // wait_cursor();
                   cls_flag = 1 ;
                   feat_2 = selected_feat ;

                   if ( feat_1 == feat_2 )
                      {
                       xstr = XmStringCreate(" ERROR : Cannot join same Feature !",CS);
                       XtSetArg(args[0],XmNlabelString,xstr);
                       XtSetValues(output_label,args,1);
                       cls_flag = 1      ;
                       // normal_cursor()   ;
                       point_counter = 1 ;
                       draw_fun = JOIN   ;
                      }
                   else
                      {
                       join_feature(feat_1, feat_2, JOIN_TOLERANCE);

                       draw_all();
                       // normal_cursor();
                       point_counter = 1 ;
                       draw_fun = JOIN   ;
                      }
                   break ;
                }
             }
         }
      break ;


    case SPLIT:  //--------------------- Split Feature -------------------------------

      search_status = NOTFOUND ;
      distance      = 99999999 ;

      x_mouse = (event->xbutton.x * ONE_PIXEL) + x_min ;
      y_mouse = y_max - (event->xbutton.y * ONE_PIXEL) ;

      feat_search();

      if ( search_status == NOTFOUND )
         {
          xstr = XmStringCreate(" ERROR : Cannot correlate, Please retry !",CS);
          XtSetArg(args[0],XmNlabelString,xstr);
          XtSetValues(output_label,args,1);
          cls_flag = 0     ;
          draw_fun = SPLIT ;
         }
     else
         {
          if ( feat[selected_feat].type != 2 )
             {
              highlight_feature (selected_feat);

              xstr = XmStringCreate(" ERROR : Split apply only on line features, Please retry !",CS);
              XtSetArg(args[0],XmNlabelString,xstr);
              XtSetValues(output_label,args,1);
              cls_flag = 0     ;
              draw_fun = SPLIT ;
             }
          else
             {

              highlight_feature (selected_feat);
              // // wait_cursor();
              // cls_flag = 1 ;

              x_mouse = (event->xbutton.x * ONE_PIXEL) + x_min ;
              y_mouse = y_max - (event->xbutton.y * ONE_PIXEL) ;

              split_feature(selected_feat,x_mouse,y_mouse);

              draw_all();
              // normal_cursor();
              point_counter = 1 ;
              draw_fun = SPLIT  ;
             }
         }
      break ;

    case MOVE:  //--------------------- Move Feature -------------------------------

      search_status = NOTFOUND ;
      distance      = 99999999 ;

      switch (point_counter)
             {
              case 1:
                  x_mouse = (event->xbutton.x * ONE_PIXEL) + x_min ;
                  y_mouse = y_max - (event->xbutton.y * ONE_PIXEL) ;

                  feat_search();

                  if ( search_status == NOTFOUND )
                     {
                      xstr = XmStringCreate(" ERROR : Cannot correlate, Please retry !",CS);
                      XtSetArg(args[0],XmNlabelString,xstr);
                      XtSetValues(output_label,args,1);
                      cls_flag = 0    ;
                      draw_fun = MOVE ;
                      break ;
                     }

                  cls_flag = 2 ;         // remove cross-hair , but donot draw feature
                  move_fun = FEATMASK ;

                  x_old = (event->xbutton.x * ONE_PIXEL) + x_min ;
                  y_old = y_max - (event->xbutton.y * ONE_PIXEL) ;
                  point_counter++ ;
                  break ;

              default:
                  x_new = (event->xbutton.x * ONE_PIXEL) + x_min ;
                  y_new = y_max - (event->xbutton.y * ONE_PIXEL) ;

                  draw_feature_mask(selected_feat,x_last,y_last);
                  erase_feature(selected_feat);

                  move_feature(selected_feat,x_old,y_old,x_new,y_new);
                  draw_feature(selected_feat);

                  // normal_cursor();
                  point_counter = 1 ;
                  draw_fun = MOVE   ;
                  break ;
             }
      break ;


    case WHERE:         //----------- Display Coordinates ------------

      x_screen = event->xbutton.x ;
      y_screen = event->xbutton.y ;
      x1_db = (x_screen * ONE_PIXEL) + x_min ;
      y1_db = y_max - (y_screen * ONE_PIXEL) ;

      XSetLineAttributes(MainDisplay,copy_gc,1,LineSolid,CapButt,JoinMiter);
      draw_pix_symb(25,x_screen,y_screen,cyan.pixel,(float)(12*ONE_PIXEL),0);

      sprintf (Message," Point Coordinates :  X = %d   Y = %d   %s",(int)x1_db,(int)y1_db,DB_UNIT_NAME);

      xstr = XmStringCreate(Message,CS);
      XtSetArg(args[0], XmNlabelString ,  xstr);
      XtSetValues(output_label,args,1);

      break ;


    case DELETE:        //------------- Delete feature ---------------

      search_status = NOTFOUND ;
      distance      = 99999999 ;

      x_mouse = (event->xbutton.x * ONE_PIXEL) + x_min ;
      y_mouse = y_max - (event->xbutton.y * ONE_PIXEL) ;

      // wait_cursor();
      feat_search();

      if ( search_status == NOTFOUND )
         {
          xstr  = XmStringCreate("INFO",CS);
          xstr1 = XmStringCreate("Cannot correlate, Please retry !",CS);
          n=0;
          XtSetArg(args[n] , XmNdialogTitle   ,        xstr);n++;
          XtSetArg(args[n] , XmNmessageString ,       xstr1);n++;
          XtSetArg(args[n] , XmNborderColor   , white.pixel);n++;
          XtSetArg(args[n] , XmNforeground    , black.pixel);n++;
          XtSetArg(args[n] , XmNbackground    , lgray.pixel);n++;
          PD = XmCreateErrorDialog(MainForm,"PD",args,n);
          XtManageChild(PD);

          cls_flag = 1 ;
          // normal_cursor();
         }
     else
         {
          feat_num = feat[selected_feat].num ;

          if (feat[selected_feat].type == 1)
             {
              cls_flag = 1 ;
              XSynchronize(MainDisplay,1);

              set_line_attr (feat[selected_feat].linetype,feat[selected_feat].linewidth);

              draw_symb(feat[selected_feat].symb_num,
                        feat[selected_feat].xbase,
                        feat[selected_feat].ybase,
                        black.pixel,
                        feat[selected_feat].symb_size,
                        feat[selected_feat].symb_angle);

              if (feat[selected_feat].has_text[0] == 'Y')
                 {
                  for(ii=1; ii<=feat[selected_feat].text_count; ii++)
                     {
                      text_index = feat[selected_feat].text + ii ;
                      x_screen  = (text[text_index].x - x_min ) / ONE_PIXEL ;
                      y_screen  = (y_max  - text[text_index].y) / ONE_PIXEL ;
                      draw_text(x_screen,y_screen,black.pixel,text[text_index].size,text_index,text[text_index].angle);
                     }
                 }

              feat[selected_feat].num            = feat[feat_count].num           ;
              strcpy ( feat[selected_feat].code, feat[feat_count].code )          ;
              feat[selected_feat].type           = feat[feat_count].type          ;
              feat[selected_feat].layer          = feat[feat_count].layer         ;
              feat[selected_feat].network        = feat[feat_count].network       ;
              feat[selected_feat].scale_range[0] = feat[feat_count].scale_range[0];
              feat[selected_feat].scale_range[1] = feat[feat_count].scale_range[1];
              feat[selected_feat].scale_range[2] = feat[feat_count].scale_range[2];
              feat[selected_feat].scale_range[3] = feat[feat_count].scale_range[3];
              feat[selected_feat].scale_range[4] = feat[feat_count].scale_range[4];
              feat[selected_feat].displayed[0]   = feat[feat_count].displayed[0]  ;
              feat[selected_feat].selectble[0]   = feat[feat_count].selectble[0]  ;
              feat[selected_feat].has_attrib[0]  = feat[feat_count].has_attrib[0] ;
              feat[selected_feat].has_text[0]    = feat[feat_count].has_text[0]   ;
              feat[selected_feat].color          = feat[feat_count].color         ;
              feat[selected_feat].linetype       = feat[feat_count].linetype      ;
              feat[selected_feat].linewidth      = feat[feat_count].linewidth     ;
              feat[selected_feat].xbase          = feat[feat_count].xbase         ;
              feat[selected_feat].ybase          = feat[feat_count].ybase         ;
              feat[selected_feat].xend           = feat[feat_count].xend          ;
              feat[selected_feat].yend           = feat[feat_count].yend          ;
              feat[selected_feat].xy_count       = feat[feat_count].xy_count      ;
              feat[selected_feat].symb_num       = feat[feat_count].symb_num      ;
              feat[selected_feat].symb_size      = feat[feat_count].symb_size     ;
              feat[selected_feat].symb_angle     = feat[feat_count].symb_angle    ;
              feat[selected_feat].text_count     = feat[feat_count].text_count    ;
              feat[selected_feat].xy             = feat[feat_count].xy            ;
              feat[selected_feat].text           = feat[feat_count].text          ;

              feat_count-- ;

              if ( db_opened[0] == 'Y' )
                 {
                  EXEC SQL  delete from features where FEAT_NUM = :feat_num ;
                  EXEC SQL  COMMIT WORK ;
                 }
              XSynchronize(MainDisplay,0);
              // normal_cursor();
             }

          if (feat[selected_feat].type == 2)
             {
              cls_flag = 1 ;
              XSynchronize(MainDisplay,1);

              set_line_attr (feat[selected_feat].linetype,feat[selected_feat].linewidth);

              draw_line(selected_feat,black.pixel)   ;
              if (feat[selected_feat].has_text[0] == 'Y')
                 {
                  for(ii=1; ii<=feat[selected_feat].text_count; ii++)
                     {
                      text_index = feat[selected_feat].text + ii ;
                      x_screen  = (text[text_index].x - x_min ) / ONE_PIXEL ;
                      y_screen  = (y_max  - text[text_index].y) / ONE_PIXEL ;
                      draw_text(x_screen,y_screen,black.pixel,text[text_index].size,text_index,text[text_index].angle);
                     }
                 }


              feat[selected_feat].num            = feat[feat_count].num           ;
              strcpy ( feat[selected_feat].code, feat[feat_count].code )          ;
              feat[selected_feat].type           = feat[feat_count].type          ;
              feat[selected_feat].layer          = feat[feat_count].layer         ;
              feat[selected_feat].network        = feat[feat_count].network       ;
              feat[selected_feat].scale_range[0] = feat[feat_count].scale_range[0];
              feat[selected_feat].scale_range[1] = feat[feat_count].scale_range[1];
              feat[selected_feat].scale_range[2] = feat[feat_count].scale_range[2];
              feat[selected_feat].scale_range[3] = feat[feat_count].scale_range[3];
              feat[selected_feat].scale_range[4] = feat[feat_count].scale_range[4];
              feat[selected_feat].displayed[0]   = feat[feat_count].displayed[0]  ;
              feat[selected_feat].selectble[0]   = feat[feat_count].selectble[0]  ;
              feat[selected_feat].has_attrib[0]  = feat[feat_count].has_attrib[0] ;
              feat[selected_feat].has_text[0]    = feat[feat_count].has_text[0]   ;
              feat[selected_feat].color          = feat[feat_count].color         ;
              feat[selected_feat].linetype       = feat[feat_count].linetype      ;
              feat[selected_feat].linewidth      = feat[feat_count].linewidth     ;
              feat[selected_feat].xbase          = feat[feat_count].xbase         ;
              feat[selected_feat].ybase          = feat[feat_count].ybase         ;
              feat[selected_feat].xend           = feat[feat_count].xend          ;
              feat[selected_feat].yend           = feat[feat_count].yend          ;
              feat[selected_feat].xy_count       = feat[feat_count].xy_count      ;
              feat[selected_feat].symb_num       = feat[feat_count].symb_num      ;
              feat[selected_feat].symb_size      = feat[feat_count].symb_size     ;
              feat[selected_feat].symb_angle     = feat[feat_count].symb_angle    ;
              feat[selected_feat].text_count     = feat[feat_count].text_count    ;
              feat[selected_feat].xy             = feat[feat_count].xy            ;
              feat[selected_feat].text           = feat[feat_count].text          ;

              feat_count-- ;

              if ( db_opened[0] == 'Y' )
                 {
                  EXEC SQL  delete from features where FEAT_NUM = :feat_num ;
                  EXEC SQL  COMMIT WORK ;
                 }
              XSynchronize(MainDisplay,0);
              // normal_cursor();
             }
         }

      draw_fun = DELETE ;
      break ;


    case TRACE:       //-------------- Network Trace ---------------

      search_status = NOTFOUND ;
      distance      = 99999999 ;

      x_mouse = (event->xbutton.x * ONE_PIXEL) + x_min ;
      y_mouse = y_max - (event->xbutton.y * ONE_PIXEL) ;

      // wait_cursor();
      feat_search();

      if ( search_status == NOTFOUND )
         {
          xstr  = XmStringCreate("INFO",CS);
          xstr1 = XmStringCreate("Cannot correlate, Please retry !",CS);
          n=0;
          XtSetArg(args[n] , XmNdialogTitle   ,        xstr);n++;
          XtSetArg(args[n] , XmNmessageString ,       xstr1);n++;
          XtSetArg(args[n] , XmNborderColor   , white.pixel);n++;
          XtSetArg(args[n] , XmNforeground    , black.pixel);n++;
          XtSetArg(args[n] , XmNbackground    , lgray.pixel);n++;

          PD = XmCreateErrorDialog(MainForm,"PD",args,n);
          XtManageChild(PD);

          cls_flag = 1   ;
          // normal_cursor();
         }
     else
         {
          // IF TRACE ON Rest Trace
          if ( trace_on[0] == 'Y' )
             {
              for (i=1; i<=feat_count; i++)
                  {
                   feat[i].linetype = org_linetype[i] ;
                   for (j=1; j<=conn_count; j++)
                       {
                        if (feat[i].num == conn_list[j] )
                           { feat[i].linetype = org_linetype[i] ; }
                       }
                  }
              trace_on[0] = 'N' ;
             }

          trace_net(feat[selected_feat].num,"grid") ;

          for (i=1; i<=feat_count; i++)
              {
               org_linetype[i]  = feat[i].linetype ;
               // Dash Line Type For non-connected Features
               feat[i].linetype = 2  ;

               for (j=1; j<=conn_count; j++)
                   {
                    if (feat[i].num == conn_list[j] )
                       {
                        // Solid Line Type For connected Features
                        feat[i].linetype = 1  ;
                       }
                   }
              }

          trace_on[0] = 'Y' ;
          draw_all ();
          // normal_cursor();
         }

      draw_fun = TRACE ;
      break ;

    case TRACEADJ:       //-------------- Trace  ADJCENT ---------------

      search_status = NOTFOUND ;
      distance      = 99999999 ;

      x_mouse = (event->xbutton.x * ONE_PIXEL) + x_min ;
      y_mouse = y_max - (event->xbutton.y * ONE_PIXEL) ;

      // wait_cursor();
      feat_search();

      if ( search_status == NOTFOUND )
         {
          xstr  = XmStringCreate("INFO",CS);
          xstr1 = XmStringCreate("Cannot correlate, Please retry !",CS);
          n=0;
          XtSetArg(args[n] , XmNdialogTitle   ,        xstr);n++;
          XtSetArg(args[n] , XmNmessageString ,       xstr1);n++;
          XtSetArg(args[n] , XmNborderColor   , white.pixel);n++;
          XtSetArg(args[n] , XmNforeground    , black.pixel);n++;
          XtSetArg(args[n] , XmNbackground    , lgray.pixel);n++;

          PD = XmCreateErrorDialog(MainForm,"PD",args,n);
          XtManageChild(PD);

          cls_flag = 1 ;
          // normal_cursor();
         }
     else
         {
          // IF TRACE ON Rest Trace
          if ( trace_on[0] == 'Y' )
             {
              for (i=1; i<=feat_count; i++)
                  {
                   feat[i].linetype = org_linetype[i] ;
                   for (j=1; j<=conn_count; j++)
                       {
                        if (feat[i].num == conn_list[j] )
                           { feat[i].linetype = org_linetype[i] ; }
                       }
                  }
              trace_on[0] = 'N' ;
             }

          trace_net(feat[selected_feat].num,"substation") ;

          for (i=1; i<=feat_count; i++)
              {
               org_linetype[i]  = feat[i].linetype ;
               // Dash Line Type For non-connected Features
               feat[i].linetype = 2  ;

               for (j=1; j<=conn_count; j++)
                   {
                    if (feat[i].num == conn_list[j] )
                       {
                        // Solid Line Type For connected Features
                        feat[i].linetype = 1  ;
                       }
                   }
              }

          trace_on[0] = 'Y' ;
          draw_all ();
          // normal_cursor();
         }

      draw_fun = TRACEADJ ;
      break ;


    case PLOTWINDOW:                //  2 pt plot window

      switch (point_counter)
       {
        case 1:
             x1_screen = event->xbutton.x ;
             y1_screen = event->xbutton.y ;
             x1_db = (x1_screen * ONE_PIXEL) + x_min ;
             y1_db = y_max - (y1_screen * ONE_PIXEL) ;

             XSetForeground(MainDisplay,xor_gc,gray.pixel);

             // Erase Cross Hair
             XDrawLine(MainDisplay,XtWindow(w),xor_gc,0,y_last,499,y_last);
             XDrawLine(MainDisplay,XtWindow(w),xor_gc,x_last,0,x_last,499);

             // Erase Correlation Window
             XDrawLine(MainDisplay,XtWindow(w),xor_gc,x_last+cursor_size,y_last,x_last,y_last+cursor_size);
             XDrawLine(MainDisplay,XtWindow(w),xor_gc,x_last+cursor_size,y_last,x_last,y_last-cursor_size);
             XDrawLine(MainDisplay,XtWindow(w),xor_gc,x_last-cursor_size,y_last,x_last,y_last+cursor_size);
             XDrawLine(MainDisplay,XtWindow(w),xor_gc,x_last-cursor_size,y_last,x_last,y_last-cursor_size);

             move_fun = RUBBERBOX ;
             point_counter++ ;
             break ;

        case 2:
             x2_screen = event->xbutton.x ;
             y2_screen = event->xbutton.y ;
             x2_db = (x2_screen * ONE_PIXEL) + x_min ;
             y2_db = y_max - (y2_screen * ONE_PIXEL) ;

            //----------------------- CASE I ---------------------------
             if ( x1_db < x2_db && y1_db > y2_db )
                { x_min_plot  = x1_db ;
                  y_min_plot  = y2_db ;
                  x_max_plot  = x2_db ;
                  y_max_plot  = y1_db ;
                }
            //----------------------- CASE II --------------------------
             if ( x1_db > x2_db && y1_db > y2_db )
                { x_min_plot  = x2_db ;
                  y_min_plot  = y2_db ;
                  x_max_plot  = x1_db ;
                  y_max_plot  = y1_db ;
                }
            //----------------------- CASE III -------------------------
             if ( x1_db < x2_db && y1_db < y2_db )
                { x_min_plot  = x1_db ;
                  y_min_plot  = y1_db ;
                  x_max_plot  = x2_db ;
                  y_max_plot  = y2_db ;
                }
            //----------------------- CASE IV  -------------------------
             if ( x1_db > x2_db && y1_db < y2_db )
                { x_min_plot  = x2_db ;
                  y_min_plot  = y1_db ;
                  x_max_plot  = x1_db ;
                  y_max_plot  = y2_db ;
                }

             // wait_cursor()        ;
             createGL()           ;
             cls_flag = 1         ;
             move_fun = CROSSHAIR ;
             point_counter = 1    ;
             // normal_cursor()      ;
             break ;

        default:
             break ;
       }
    break ;



    default:  //  Recall Last Function  OR  DO Nothing
     if ( event->xbutton.button == 3 )  // (see /usr/lpp/X11/include/X11/Xlib.h line 614)
        {
         switch (last_fun)
                {
                 case ADDPOINT:
                      addpointCB();
                      break;

                 case ADDLINE:
                      addlineCB();
                      break;

                 case ADDTEXT:
                      addtextCB();
                      break;

                 case ADDTEXT2F:
                      addtext2fCB();
                      break;

                 case EDITPIC:
                      editpictureCB();
                      break;

                 case MOVE:
                      moveCB();
                      break;

                 case SPLIT:
                      splitCB();
                      break;
                }
        }
     else
        {
         // normal_cursor();
        }
      break ;
   }
}

*/


/*------------------------------------------------------------------------*/
/*                            mouse_moveCB()                              */
/*------------------------------------------------------------------------*/
/*
void mouse_moveCB(Widget w, XtPointer Data, XEvent *event)
{

 XSetForeground(MainDisplay,xor_gc,gray.pixel);

 switch (move_fun)
   {

    case CROSSHAIR:          // Crosshair pointer with correlation Window

      if (cls_flag == 0)     // Drawing Area not cleared
         {
          // Cross Hair
          XDrawLine(MainDisplay,XtWindow(w),xor_gc,0,y_last,499,y_last);
          XDrawLine(MainDisplay,XtWindow(w),xor_gc,x_last,0,x_last,499);

          // Correlation Window
          XDrawLine(MainDisplay,XtWindow(w),xor_gc,x_last+cursor_size,y_last,x_last,y_last+cursor_size);
          XDrawLine(MainDisplay,XtWindow(w),xor_gc,x_last+cursor_size,y_last,x_last,y_last-cursor_size);
          XDrawLine(MainDisplay,XtWindow(w),xor_gc,x_last-cursor_size,y_last,x_last,y_last+cursor_size);
          XDrawLine(MainDisplay,XtWindow(w),xor_gc,x_last-cursor_size,y_last,x_last,y_last-cursor_size);
         }

      x2_screen = event->xbutton.x ;
      y2_screen = event->xbutton.y ;

      // Cross Hair
      XDrawLine(MainDisplay,XtWindow(w),xor_gc,0,y2_screen,499,y2_screen);
      XDrawLine(MainDisplay,XtWindow(w),xor_gc,x2_screen,0,x2_screen,499);

      // Correlation Window
      XDrawLine(MainDisplay,XtWindow(w),xor_gc,x2_screen+cursor_size,y2_screen,x2_screen,y2_screen+cursor_size);
      XDrawLine(MainDisplay,XtWindow(w),xor_gc,x2_screen+cursor_size,y2_screen,x2_screen,y2_screen-cursor_size);
      XDrawLine(MainDisplay,XtWindow(w),xor_gc,x2_screen-cursor_size,y2_screen,x2_screen,y2_screen+cursor_size);
      XDrawLine(MainDisplay,XtWindow(w),xor_gc,x2_screen-cursor_size,y2_screen,x2_screen,y2_screen-cursor_size);

      cls_flag = 0 ;
      x_last = x2_screen ;
      y_last = y2_screen ;
      break ;

    case RUBBERBOX:                  //  Window rubber box

      if (cls_flag == 0)             // Drawing Area not cleared
         {
          // Rubber Box
          XDrawLine(MainDisplay,XtWindow(w),xor_gc,x1_screen,y1_screen,x_last,y1_screen);
          XDrawLine(MainDisplay,XtWindow(w),xor_gc,x1_screen,y1_screen,x1_screen,y_last);
          XDrawLine(MainDisplay,XtWindow(w),xor_gc,x_last,y_last,x_last,y1_screen);
          XDrawLine(MainDisplay,XtWindow(w),xor_gc,x_last,y_last,x1_screen,y_last);
         }

      x2_screen = event->xbutton.x ;
      y2_screen = event->xbutton.y ;

      XDrawLine(MainDisplay,XtWindow(w),xor_gc,x1_screen,y1_screen,x2_screen,y1_screen);
      XDrawLine(MainDisplay,XtWindow(w),xor_gc,x1_screen,y1_screen,x1_screen,y2_screen);
      XDrawLine(MainDisplay,XtWindow(w),xor_gc,x2_screen,y2_screen,x2_screen,y1_screen);
      XDrawLine(MainDisplay,XtWindow(w),xor_gc,x2_screen,y2_screen,x1_screen,y2_screen);

      cls_flag = 0 ;
      x_last = x2_screen ;
      y_last = y2_screen ;
      break ;


    case RUBBERPAN:                  //  Add rubber Pan

      if (cls_flag == 0)             // Drawing Area not cleared
         {
          // Cross Hair
          XDrawLine(MainDisplay,XtWindow(w),xor_gc,0,y_last,499,y_last);
          XDrawLine(MainDisplay,XtWindow(w),xor_gc,x_last,0,x_last,499);

          // Correlation Window
          XDrawLine(MainDisplay,XtWindow(w),xor_gc,x_last+cursor_size,y_last,x_last,y_last+cursor_size);
          XDrawLine(MainDisplay,XtWindow(w),xor_gc,x_last+cursor_size,y_last,x_last,y_last-cursor_size);
          XDrawLine(MainDisplay,XtWindow(w),xor_gc,x_last-cursor_size,y_last,x_last,y_last+cursor_size);
          XDrawLine(MainDisplay,XtWindow(w),xor_gc,x_last-cursor_size,y_last,x_last,y_last-cursor_size);

          // Rubber Pan
          XDrawLine(MainDisplay,XtWindow(w),xor_gc,x1_screen,y1_screen,x_last,y_last);


          // DISPLAY DISTANCE ON MOVE
          x1_db = (x1_screen * ONE_PIXEL) + x_min ;
          y1_db = y_max - (y1_screen * ONE_PIXEL) ;
          x2_db = (event->xbutton.x * ONE_PIXEL) + x_min ;
          y2_db = y_max - (event->xbutton.y * ONE_PIXEL) ;

          x_diff = x2_db - x1_db ;
          y_diff = y2_db - y1_db ;
          distance = sqrt ( (x_diff * x_diff) + (y_diff * y_diff) ) ;

          sprintf (Message, " Distance = %.2f   %s",distance,DB_UNIT_NAME);
          xstr = XmStringCreate(Message,CS);
          XtSetArg(args[0], XmNlabelString ,  xstr);
          XtSetValues(output_label,args,1);
         }

      x2_screen = event->xbutton.x ;
      y2_screen = event->xbutton.y ;

      // Cross Hair
      XDrawLine(MainDisplay,XtWindow(w),xor_gc,0,y2_screen,499,y2_screen);
      XDrawLine(MainDisplay,XtWindow(w),xor_gc,x2_screen,0,x2_screen,499);

      // Correlation Window
      XDrawLine(MainDisplay,XtWindow(w),xor_gc,x2_screen+cursor_size,y2_screen,x2_screen,y2_screen+cursor_size);
      XDrawLine(MainDisplay,XtWindow(w),xor_gc,x2_screen+cursor_size,y2_screen,x2_screen,y2_screen-cursor_size);
      XDrawLine(MainDisplay,XtWindow(w),xor_gc,x2_screen-cursor_size,y2_screen,x2_screen,y2_screen+cursor_size);
      XDrawLine(MainDisplay,XtWindow(w),xor_gc,x2_screen-cursor_size,y2_screen,x2_screen,y2_screen-cursor_size);

      // Rubber Pan
      XDrawLine(MainDisplay,XtWindow(w),xor_gc,x1_screen,y1_screen,x2_screen,y2_screen);

      cls_flag = 0 ;
      x_last = x2_screen ;
      y_last = y2_screen ;
      break ;


    case ROTATESYMB:                 //  Rotate Symbol While Moving

      if (cls_flag == 0)             // Drawing Area not cleared
         {
          // Cross Hair
          XDrawLine(MainDisplay,XtWindow(w),xor_gc,0,y_last,499,y_last);
          XDrawLine(MainDisplay,XtWindow(w),xor_gc,x_last,0,x_last,499);

          // Correlation Window
          XDrawLine(MainDisplay,XtWindow(w),xor_gc,x_last+cursor_size,y_last,x_last,y_last+cursor_size);
          XDrawLine(MainDisplay,XtWindow(w),xor_gc,x_last+cursor_size,y_last,x_last,y_last-cursor_size);
          XDrawLine(MainDisplay,XtWindow(w),xor_gc,x_last-cursor_size,y_last,x_last,y_last+cursor_size);
          XDrawLine(MainDisplay,XtWindow(w),xor_gc,x_last-cursor_size,y_last,x_last,y_last-cursor_size);

          // Rubber Pan
          XDrawLine(MainDisplay,XtWindow(w),xor_gc,x1_screen,y1_screen,x2_screen,y2_screen);

          // Symbol with angle
          x1_db = (x1_screen * ONE_PIXEL) + x_min ;
          y1_db = y_max - (y1_screen * ONE_PIXEL) ;
          x2_db = (x_last * ONE_PIXEL) + x_min ;
          y2_db = y_max - (y_last * ONE_PIXEL) ;

          feat[feat_count].symb_angle = atan2((y2_db-y1_db),(x2_db-x1_db)) * DEG2RAD ;
          xor_draw_pix_symb(feat[feat_count].symb_num,x_screen,y_screen,feat[feat_count].color,
                           (float)feat[feat_count].symb_size,feat[feat_count].symb_angle);
         }
      else
      if (cls_flag == 2)             // Drawing Area not cleared
         {
          // Cross Hair
          XDrawLine(MainDisplay,XtWindow(w),xor_gc,0,y_last,499,y_last);
          XDrawLine(MainDisplay,XtWindow(w),xor_gc,x_last,0,x_last,499);

          // Correlation Window
          XDrawLine(MainDisplay,XtWindow(w),xor_gc,x_last+cursor_size,y_last,x_last,y_last+cursor_size);
          XDrawLine(MainDisplay,XtWindow(w),xor_gc,x_last+cursor_size,y_last,x_last,y_last-cursor_size);
          XDrawLine(MainDisplay,XtWindow(w),xor_gc,x_last-cursor_size,y_last,x_last,y_last+cursor_size);
          XDrawLine(MainDisplay,XtWindow(w),xor_gc,x_last-cursor_size,y_last,x_last,y_last-cursor_size);

          // Rubber Pan
          XDrawLine(MainDisplay,XtWindow(w),xor_gc,x1_screen,y1_screen,x2_screen,y2_screen);

         }


      x2_screen = event->xbutton.x ;
      y2_screen = event->xbutton.y ;

      // Cross Hair
      XDrawLine(MainDisplay,XtWindow(w),xor_gc,0,y2_screen,499,y2_screen);
      XDrawLine(MainDisplay,XtWindow(w),xor_gc,x2_screen,0,x2_screen,499);

      // Correlation Window
      XDrawLine(MainDisplay,XtWindow(w),xor_gc,x2_screen+cursor_size,y2_screen,x2_screen,y2_screen+cursor_size);
      XDrawLine(MainDisplay,XtWindow(w),xor_gc,x2_screen+cursor_size,y2_screen,x2_screen,y2_screen-cursor_size);
      XDrawLine(MainDisplay,XtWindow(w),xor_gc,x2_screen-cursor_size,y2_screen,x2_screen,y2_screen+cursor_size);
      XDrawLine(MainDisplay,XtWindow(w),xor_gc,x2_screen-cursor_size,y2_screen,x2_screen,y2_screen-cursor_size);

      // Rubber Pan
      XDrawLine(MainDisplay,XtWindow(w),xor_gc,x1_screen,y1_screen,x2_screen,y2_screen);

      // Symbol with angle
      x1_db = (x1_screen * ONE_PIXEL) + x_min ;
      y1_db = y_max - (y1_screen * ONE_PIXEL) ;
      x2_db = (x2_screen * ONE_PIXEL) + x_min ;
      y2_db = y_max - (y2_screen * ONE_PIXEL) ;
      feat[feat_count].symb_angle = atan2((y2_db-y1_db),(x2_db-x1_db)) * DEG2RAD ;
      xor_draw_pix_symb(feat[feat_count].symb_num,x_screen,y_screen,feat[feat_count].color,
                       (float)feat[feat_count].symb_size,feat[feat_count].symb_angle);


      cls_flag = 0 ;
      x_last = x2_screen ;
      y_last = y2_screen ;
      break ;



    case FEATMASK:                  //  Moving feature mask

      if (cls_flag == 0)             // Drawing Area not cleared , XOR both cross-hair & feature
         {
          // Cross Hair
          XDrawLine(MainDisplay,XtWindow(w),xor_gc,0,y_last,979,y_last);
          XDrawLine(MainDisplay,XtWindow(w),xor_gc,x_last,0,x_last,979);

          // Correlation Window
          XDrawLine(MainDisplay,XtWindow(w),xor_gc,x_last+cursor_size,y_last,x_last,y_last+cursor_size);
          XDrawLine(MainDisplay,XtWindow(w),xor_gc,x_last+cursor_size,y_last,x_last,y_last-cursor_size);
          XDrawLine(MainDisplay,XtWindow(w),xor_gc,x_last-cursor_size,y_last,x_last,y_last+cursor_size);
          XDrawLine(MainDisplay,XtWindow(w),xor_gc,x_last-cursor_size,y_last,x_last,y_last-cursor_size);

          // Feature Mask
          draw_feature_mask(selected_feat,x_last,y_last);
         }
      else
      if (cls_flag == 2)             // Drawing Area not cleared , XOR crosshair only
         {
          // Cross Hair
          XDrawLine(MainDisplay,XtWindow(w),xor_gc,0,y_last,979,y_last);
          XDrawLine(MainDisplay,XtWindow(w),xor_gc,x_last,0,x_last,979);

          // Correlation Window
          XDrawLine(MainDisplay,XtWindow(w),xor_gc,x_last+cursor_size,y_last,x_last,y_last+cursor_size);
          XDrawLine(MainDisplay,XtWindow(w),xor_gc,x_last+cursor_size,y_last,x_last,y_last-cursor_size);
          XDrawLine(MainDisplay,XtWindow(w),xor_gc,x_last-cursor_size,y_last,x_last,y_last+cursor_size);
          XDrawLine(MainDisplay,XtWindow(w),xor_gc,x_last-cursor_size,y_last,x_last,y_last-cursor_size);
         }


      x2_screen = event->xbutton.x ;
      y2_screen = event->xbutton.y ;

      // Cross Hair
      XDrawLine(MainDisplay,XtWindow(w),xor_gc,0,y2_screen,979,y2_screen);
      XDrawLine(MainDisplay,XtWindow(w),xor_gc,x2_screen,0,x2_screen,979);

      // Correlation Window
      XDrawLine(MainDisplay,XtWindow(w),xor_gc,x2_screen+cursor_size,y2_screen,x2_screen,y2_screen+cursor_size);
      XDrawLine(MainDisplay,XtWindow(w),xor_gc,x2_screen+cursor_size,y2_screen,x2_screen,y2_screen-cursor_size);
      XDrawLine(MainDisplay,XtWindow(w),xor_gc,x2_screen-cursor_size,y2_screen,x2_screen,y2_screen+cursor_size);
      XDrawLine(MainDisplay,XtWindow(w),xor_gc,x2_screen-cursor_size,y2_screen,x2_screen,y2_screen-cursor_size);

      // Feature Mask
      draw_feature_mask(selected_feat,(int)x2_screen,(int)y2_screen);

      cls_flag = 0 ;
      x_last = x2_screen ;
      y_last = y2_screen ;
      break ;
   }


 // Dsiplay Mouse XY_Coordinates

 x_mouse = (event->xbutton.x * ONE_PIXEL) + x_min ;
 y_mouse = y_max - (event->xbutton.y * ONE_PIXEL) ;

 // x_mouse = event->xbutton.x ;  // the Left most pixel bug (pixel N# 0)
 // y_mouse = event->xbutton.y ;  // the Top  most pixel bug (pixel N# 0)

 sprintf (scale_ch,"X = %.1f   Y = %.1f",x_mouse,y_mouse);
 xstr = XmStringCreate(scale_ch,CS);
 XtSetArg(args[0], XmNlabelString, xstr);
 XtSetValues(xy_label,args,1);
}

*/

