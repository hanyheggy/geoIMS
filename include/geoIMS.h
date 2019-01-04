/*------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*/
/*                    Header File  ( geoIMS.h )                           */
/*------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*/

/*------------------------------------------------------------------------*/
/*                          Standard Include Files                        */
/*------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <math.h>
#include <errno.h>

/*------------------------------------------------------------------------*/
/*                          Arabic Include Files                          */
/*------------------------------------------------------------------------*/
/* AIX 3.2.4
#include <sys/lc_layout.h>
#include <locale.h>
#include <sys/FP.h>  */

/*------------------------------------------------------------------------*/
/*                      Clinet/Server Include Files                       */
/*------------------------------------------------------------------------*/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>

/*------------------------------------------------------------------------*/
/*                      ImageMagick Include Files                         */
/*------------------------------------------------------------------------*/
#include <wand/magick_wand.h>
#include <magick/api.h>

/*------------------------------------------------------------------------*/
/*                          X Include Files                               */
/*------------------------------------------------------------------------*/
#include <Xm/Xm.h>            /*  Motif Files 2.1      */
#include <Xm/MainW.h>
#include <Xm/PushB.h>
#include <Xm/Label.h>
#include <Xm/Text.h>
#include <Xm/List.h>
#include <Xm/BulletinB.h>
#include <Xm/Form.h>
#include <Xm/DrawingA.h>
#include <Xm/MessageB.h>
#include <Xm/ScrolledW.h>
#include <Xm/Scale.h>
#include <Xm/RowColumn.h>
#include <Xm/CascadeB.h>
#include <Xm/TextF.h>         /*  FieldText     new   */
#include <Xm/SelectioB.h>     /*  PromptDialog  new   */
#include <Xm/ToggleB.h>       /*  Toggle Button new   */
#include <Xm/ScrolledW.h>     /*  Scrolled Window     */

#include <X11/Intrinsic.h>    /*  X11 Files           */
#include <X11/cursorfont.h>   /*  Cursor Font         */
#include <X11/keysymdef.h>
#include <X11/keysym.h>

#include <X11/Xlib.h>         /*  Enhanced X-windows  */
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/X.h>
#include <X11/Xlibint.h>

/*  #include <X11/AIX.h>
    #include <X11/AIXlib.h> LINUX  */

#include <Xm/MwmUtil.h>       /* Mwm include file     */

#include "geocursor.bit"

/*------------------------------------------------------------------------*/
/*                         X Defined Constants                            */
/*------------------------------------------------------------------------*/
#define CS          XmSTRING_DEFAULT_CHARSET
#define FSBCBS      XmFileSelectionBoxCallbackStruct
#define ANYCBS      XmAnyCallbackStruct
#define DEG2RAD     57.29578

/*------------------------------------------------------------------------*/
/*                     geoIMS Defined Constants                           */
/*------------------------------------------------------------------------*/
#define MM                   1    // Data Base Unit
#define CM                   2
#define DM                   3
#define M                    4
#define KM                   5

#define NONE                 0    // Mouse down
#define WINDOW               1
#define ADDPOINT             2
#define ADDTEXT              3
#define ADDTEXT2F            4
#define ADDLINE              5
#define ADDPOLYGON           6
#define ADDNODE              7
#define ADDARC               8
#define ADDACCDENT           9
#define ADDOPPT              10
#define EDIT                 11
#define EDITPIC              12
#define DISTANCE             13
#define WHERE                14
#define CPOINT               15
#define CHANGECOLOR          16
#define PLOTWINDOW           17
#define DELETE               18
#define MOVE                 19
#define SPLIT                20
#define JOIN                 21
#define TRACE                22
#define TRACEADJ             23
#define SHORTPATH            24
#define BLD_STREET_CONN      25
#define BLD_ELECTRIC_CONN    26
#define GETXYPT              27


#define CROSSHAIR   1       /* Mouse move        */
#define RUBBERBOX   2
#define RUBBERPAN   3
#define FEATMASK    4
#define ROTATESYMB  5

#define FOUND       1       /* Search edit       */
#define NOTFOUND    0

/* User Defined Line Types */
int            nDashOffset   = 0             ;
unsigned char  cDashList2[]  = {5,5}         ;
unsigned char  cDashList3[]  = {2,2}         ;
unsigned char  cDashList4[]  = {10,2,3,2}    ;
unsigned char  cDashList5[]  = {10,2,3,2,3,2};
unsigned char  cDashList6[]  = {10,2,3,2}    ;
unsigned char  cDashList7[]  = {10,2,3,2}    ;
unsigned char  cDashList8[]  = {9,2,9,2}     ;
unsigned char  cDashList9[]  = {1,3,1,3}     ;
unsigned char  cDashList10[] = {1,1}         ;


/*------------------------------------------------------------------------*/
/*                          Function Prototypes                           */
/*------------------------------------------------------------------------*/
void  newCB()               ;   /* Call_Back Functions */
void  newOkCB()             ;
void  newCancelCB()         ;
void  retrieve_allCB()      ;
void  retrieve_all()        ;
void  area_retrievalCB()    ;
void  area_retrieval()      ;
void  network_retrievalCB() ;
void  network_retrieval()   ;
void  savedbCB()            ;
void  saveOkCB()            ;
void  saveCancelCB()        ;
void  createdbCB()          ;
void  dropdbCB()            ;
void  drawCB()              ;
void  zwinCB()              ;
void  zinCB()               ;
void  zoutCB()              ;
void  zallCB()              ;
void  centerpointCB()       ;
void  addlineCB()           ;
void  addpointCB()          ;
void  addtextCB()           ;
void  addtext2fCB()         ;
void  addnodeCB()           ;
void  addarcCB()            ;
void  addaccdentCB()        ;
void  addpolygonCB()        ;
void  mouse_downCB()        ;
void  mouse_moveCB()        ;
void  button_moveCB()       ;
void  refreshCB()           ;
void  leaveCB()             ;
void  enterCB()             ;
void  infinbCB()            ;
void  infoutbCB()           ;
void  infoutbOKCB()         ;
void  infoutbCancelCB()     ;
void  infinaCB()            ;
void  infoutaCB()           ;
void  infoutaOKCB()         ;
void  infoutaCancelCB()     ;
void  dxfinCB()             ;
void  dxfoutCB()            ;
void  dxfoutOKCB()          ;
void  dxfoutCancelCB()      ;
void  scaleCB()             ;
void  scaleOkCB()           ;
void  scaleCancelCB()       ;
void  db_nameCB()           ;
void  textCB()              ;
void  editCB()              ;
void  editpictureCB()       ;
void  distanceCB()          ;
void  whereCB()             ;
void  double_curCB()        ;
void  half_curCB()          ;
void  plotCB()              ;
void  layercontrolCB()      ;
void  panleftCB()           ;
void  panrightCB()          ;
void  panupCB()             ;
void  pandownCB()           ;
void  deleteCB()            ;
void  splitCB()             ;
void  joinCB()              ;
void  moveCB()              ;
void  findCB()              ;
void  findOkCB()            ;
void  findCancelCB()        ;
void  edgematchCB()         ;
void  locateCB()            ;
void  endCB()               ;
void  endOkCB()             ;
void  endCancelCB()         ;
void  transferCB()          ;
void  projectionCB()        ;
void  edit_parmCB()         ;
void  bitmapCB()            ;

void  colorstreet()         ;  /* Street Network CallBacks   */
void  shortestpathCB()      ;
void  findstreetCB()        ;
void  findstreetOkCB()      ;
void  findstreetCancelCB()  ;
void  bld_s_connectivityCB();

void  add_gridCB()          ;  /* Electric Network CallBacks */
void  add_substnCB()        ;
void  add_op_ptCB()         ;
void  add_mv_fdrCB()        ;
void  bld_e_connectivityCB();
void  networktraceCB()      ;
void  traceadjcentCB()      ;
void  resettraceCB()        ;
void  sldCB()               ;
void  runsldCB()            ;



void  initialize()          ;   /* Non Call_Back Functions */
void  opendb()              ;
void  draw_all()            ;
void  draw_symb()           ;
void  draw_pix_symb()       ;
void  draw_text()           ;
void  plot_symb()           ;
void  plot_text()           ;
void  draw_line()           ;
void  window()              ;
void  display_scale()       ;
void  update_layer()        ;
void  feat_search()         ;
void  snap_to_feature()     ;
void  edit_feature()        ;
void  insert_feature()      ;
void  insert_text()         ;
void  join_feature()        ;
void  split_feature()       ;
void  move_feature()        ;
void  highlight_feature()   ;
void  draw_feature()        ;
void  draw_feature_mask()   ;
void  erase_feature()       ;
void  normal_cursor()       ;
void  wait_cursor()         ;
void  createGL()            ;
void  dxfin()               ;
void  dxfout()              ;
void  match_all()           ;
void  map_transfer()        ;
void  map_projection()      ;
void  get_xy_point()        ;
void  set_line_attr()       ;
void  set_color()           ;
void  edit_parm()           ;

void  fsb()                 ;   /* Motif Functions         */
void  edit()                ;
void  edit_pic()            ;
void  plot_fit_to_paper()   ;
void  plot_using_temp()     ;
void  plot_using_window()   ;
void  scalepanel()          ;
void  set_scale()           ;
void  layer_control()       ;

void  OpendbSubMenu()       ;   /* Pull Down Sub-menus */
void  ImportSubMenu()       ;
void  ExportSubMenu()       ;
void  PlotSubMenu()         ;
void  ElectricSubMenu()     ;
void  StreetSubMenu()       ;

void  trace_net()           ;
void  shortest_path()       ;
void  export_bitmap()       ;



void * web_listener()       ;
void * system_logger()      ;

/*------------------------------------------------------------------------*/
/*                          Definend Widgets                              */
/*------------------------------------------------------------------------*/
Widget  toplevel            ;
Widget  MainWindow          ;
Widget  MainForm            ;
Widget  drawarea            ;
Widget  scrolledwindow      ;

Widget  opendb_button       ;
Widget  savedb_button       ;
Widget  draw_button         ;
Widget  zwin_button         ;
Widget  zin_button          ;
Widget  zout_button         ;
Widget  zall_button         ;
Widget  addline_button      ;
Widget  addpoint_button     ;
Widget  addpolygon_button   ;
Widget  scale_button        ;
Widget  edit_button         ;
Widget  distance_button     ;
Widget  where_button        ;
Widget  half_cur_button     ;
Widget  double_cur_button   ;
Widget  plot_button         ;
Widget  panleft_button      ;
Widget  panright_button     ;
Widget  panup_button        ;
Widget  pandown_button      ;

Widget  scale_label         ;
Widget  xy_label            ;
Widget  output_label        ;
Widget  label               ;

Widget  PD                  ;
Widget  ScaleFrom           ;
Widget  ok_button           ;
Widget  cancel_button       ;

Widget MenuBar = 0          ;
Widget CreateTheMenuBar()   ;


/* LINUX */
Widget CreatePushButton( Widget   Parent,
                         String   Name,
                         char     *labelString,
                         char     mnemonic,
                         XmString acceleratorText,
                         String   accelerator       ) ;

Widget CreateCascadeButton( Widget   Parent,
                            String   Name,
                            Widget   subMenuId,
                            char     *labelString,
                            char     mnemonic      )  ;


/*------------------------------------------------------------------------*/
/*                       X Windows Global Variables                       */
/*------------------------------------------------------------------------*/
GC           copy_gc     ;     /*  Copy   graphic context     */
GC           xor_gc      ;     /*  XOR    graphic context     */
GC           Tilegc      ;     /*  Pixmap graphic context     */
XGCValues    val         ;     /*  graphic context values     */

XEvent       event       ;     /*  Event variable             */
Arg          args[20]    ;     /*  Widget Resource values     */
XmString     xstr        ;     /*  XString                    */
XmString     xstr1       ;     /*  XString                    */
XmString     xstr2       ;     /*  XString                    */

Colormap     cmap        ;     /*  Color Map                  */
XColor       dummy       ;     /*  Dummy   Color              */
XColor       blue        ;     /*  geoINFO Color # 1          */
XColor       red         ;     /*  geoINFO Color # 2          */
XColor       pink        ;     /*  geoINFO Color # 3          */
XColor       green       ;     /*  geoINFO Color # 4          */
XColor       cyan        ;     /*  geoINFO Color # 5          */
XColor       yellow      ;     /*  geoINFO Color # 6          */
XColor       white       ;     /*  geoINFO Color # 7          */
XColor       black       ;     /*  geoINFO Color # 8          */
XColor       gray        ;     /*  geoINFO Color # 9          */
XColor       wheat       ;     /*  geoINFO Color # 10         */
XColor       brown       ;     /*  geoINFO Color # 11         */
XColor       orange      ;     /*  geoINFO Color # 12         */
XColor       lgray       ;     /*  geoINFO Color # 13         */
XColor       magenta     ;     /*  geoINFO Color # 14         */

Cursor       myCursor    ;     /*  Normal Cursor              */
Cursor       pixCursor   ;     /*  Pixmap Cursor              */

Pixmap       Tile        ;     /*  Pixmap Drawing Area        */
Pixmap       mapCursor   ;     /*  Pixmap Cursor              */
Pixmap       buttonpix   ;     /*  Pixmap Cursor              */
int          nDepth      ;     /*  Pixmap Depth               */
int          nScreen     ;     /*  Pixmap Screen              */

short ToolkitInitialized ;     /*  Toolkit Initialzation Flag */

/*------------------------------------------------------------------------*/
/*                     ImageMagick Global Variables                       */
/*------------------------------------------------------------------------*/
PixelWand     *IMcolor[256]      ;
double         dash_array[20][10] ;


/*------------------------------------------------------------------------*/
/*                        geoINFO Global Variables                        */
/*------------------------------------------------------------------------*/
typedef struct
  {
   long   num                   ;
   char   code[13]              ;
   int    type                  ;
   int    layer                 ;
   int    network               ;
   char   scale_range [5]       ;
   char   displayed   [1]       ;
   char   selectble   [1]       ;
   char   has_attrib  [1]       ;
   char   has_text    [1]       ;
   int    color                 ;
   int    linetype              ;
   int    linewidth             ;
   long   xmin                  ;
   long   ymin                  ;
   long   xmax                  ;
   long   ymax                  ;
   long   xbase                 ;
   long   ybase                 ;
   long   xend                  ;
   long   yend                  ;
   int    xy_count              ;
   int    symb_num              ;
   int    symb_size             ;
   int    symb_angle            ;
   int    text_count            ;
   int    xy                    ;  // xy_start_after_index
   int    text                  ;  // text_start_after_index
  } Features ;

typedef struct
  {
   int    id                    ;
   char   name      [21]        ;
   char   desc      [51]        ;
   char   displayed [1]         ;
  } Layers  ;

typedef struct
  {
   int    x                     ;
   int    y                     ;
   int    size                  ;
   float  angle                 ;
   int    just                  ;
   int    font                  ;
   unsigned char   string[51]   ;
  } Text ;

typedef struct
  {
   int    stroke                ;
   int    grid                  ;
   int    mv_draw [200]         ;
   double angle   [200]         ;
   double distance[200]         ;
   float  x_factor              ;
  } Symbols ;

typedef struct
  {
   int    code                  ;
   char   value   [81]          ;
   char   text    [81]          ;
   char   layer   [21]          ;
   char   font    [41]          ;
   char   linetype[21]          ;
   int    hz_just               ;
   int    vl_just               ;
   int    pline_flag            ;
   int    color                 ;
   float  x1,y1,z1              ;
   float  x2,y2,z2              ;
   int    i_value               ;
   float  f_value               ;
  } DXF ;

typedef struct
  {
   int    xscreen               ;  // 1
   int    yscreen               ;  // 2
   int    xdb                   ;  // 3
   int    ydb                   ;  // 4
  } POINT ;

typedef struct
  {
   int    status                ;  // 1  Empty/Inuse Flag
   char   php_id[50]            ;  // 2  PHP Session String
   double x_min                 ;  // 3  Min x Limits of displayed Database
   double y_min                 ;  // 4  Min y Limits of displayed Database
   double x_max                 ;  // 5  Max x Limits of displayed Database
   double y_max                 ;  // 6  Max y Limits of displayed Database
   int    start_time            ;  // 7  Session start time in seconds (HH*3600+MM*60+SS)
  } SESSION ;

typedef struct
  {
   int    status                ;  // 1  SYSTEM Current status
   int    stop                  ;  // 2  SYSTEM Stop Flag
   char   web_ip          [21]  ;  // 3  SYSTEM Web Listen IP
   int    web_port              ;  // 4  SYSTEM Web Port
   char   web_include_file[100] ;  // 5  SYSTEM Web Connection include file (full path name)
   char   data_file       [100] ;  // 6  SYSTEM Binary Data file (full path name)
   char   dsn_name        [21]  ;  // 7  SYSTEM DB Server Source ODBC DSN name
   char   dsn_user        [21]  ;  // 8  SYSTEM DB Server Source ODBC DSN user
   char   dsn_pwd         [21]  ;  // 9  SYSTEM DB Server Source ODBC DSN password
   int    char_bind_len         ;  // 10 SYSTEM Character Column Bind lenght
   int    int_bind_len          ;  // 11 SYSTEM Integer   Column Bind lenght
   int    sleep_time            ;  // 12 SYSTEM System Sleep time in seconds
   int    log_level             ;  // 13 SYSTEM System Log Level 1,2,3,4
   int    logger_status         ;  // 14 SYSTEM System Logger Status
   int    end_logger_thread     ;  // 15 SYSTEM System Logger stop falg
   int    session_timeout       ;  // 16 SYSTEM Session Time-out in minutes
   char   sql            [1000] ;  // 17 SYSTEM SQL working variable
  } SYS ;

typedef struct
  {
   short  status                ;  // 1  Log status  0 -> free 1 -> inuse
   int    service_id            ;  // 2  Service id which send the log message
   char   timein        [21]    ;  // 3  Timestamp for log message
   char   type          [21]    ;  // 4  Type      of  log message  WARNNING,INFO,ERROR,SEVERE ERROR
   char   module        [31]    ;  // 5  Module    which generate log message
   char   message       [1000]  ;  // 6  Message   to be written to log
  } LOG ;




SYS       sys                   ;  // Running SYSTEM configuration    structure
LOG       log_queue [5001]      ;  // SYSTEM  Logger queue            structure

Features  feat[2000000]         ; // Main Drawing data  1,000,000   ( feat[] -> Dynamic Array )
Features  add                   ; // Add feature variable
Layers    lay[255]              ; // Layer Defenition
Text      text[200000]          ; // Text Drawing data
Symbols   symb[1000]            ; // Symbol set data
Symbols   font[25][255]         ; // Text font set data
DXF       dxf                   ; // DXF format data
POINT     point                 ; // XY Point from Mouse down
SESSION   session[200]          ;

long      x[12000000]           ; // Default 5000000
long      y[12000000]           ; // Default 5000000
long      xy_index              ; // xy_start of feature
long      xy_LAST               ; // LAST xy index

long      SYMBCLIPBUFFER        ; // Symb Clip Buffer in DBU (default 50)
long      LINECLIPBUFFER        ; // Line Clip Buffer in DBU (def. 10000)

double    x_ul_screen           ; // DrawArea Upper_Left   x Limits Pixle
double    y_ul_screen           ; // DrawArea Upper_Left   y Limits Pixle
double    x_br_screen           ; // DrawArea Bottom_Right x Limits Pixle
double    y_br_screen           ; // DrawArea Bottom_Right y Limits Pixle



double    x_min                 ; // Min x Limits of displayed Database
double    y_min                 ; // Min y Limits of displayed Database
double    x_max                 ; // Max x Limits of displayed Database
double    y_max                 ; // Max y Limits of displayed Database
double    x_min1                ; // Min x Symbol Clipping Limits
double    y_min1                ; // Min y Symbol Clipping Limits
double    x_max1                ; // Max x Symbol Clipping Limits
double    y_max1                ; // Max y Symbol Clipping Limits
double    x_min2                ; // Min x Line Clipping Limits
double    y_min2                ; // Min y Line Clipping Limits
double    x_max2                ; // Max x Line Clipping Limits
double    y_max2                ; // Max y Line Clipping Limits
double    x_min3                ; // Min x Line Clipping Limits text
double    y_min3                ; // Min y Line Clipping Limits text
double    x_max3                ; // Max x Line Clipping Limits text
double    y_max3                ; // Max y Line Clipping Limits text

double    x_db                  ; // Real world x-y coordinates
double    y_db                  ; // Real world x-y coordinates
double    x1_db                 ; // Real world x-y coordinates
double    y1_db                 ; // Real world x-y coordinates
double    x2_db                 ; // Real world x-y coordinates
double    y2_db                 ; // Real world x-y coordinates

double    x1_clip               ; // Min x Clipping Limits
double    y1_clip               ; // Min y Clipping Limits
double    x2_clip               ; // Max x Clipping Limits
double    y2_clip               ; // Max y Clipping Limits

double    x_bot                 ; // Line  Clipping Limits
double    x_top                 ; // Line  Clipping Limits
double    y_left                ; // Line  Clipping Limits
double    y_right               ; // Line  Clipping Limits

long      x_screen              ; // Equivlant x-y coord. on DrawingArea
long      y_screen              ; // Equivlant x-y coord. on DrawingArea
long      x1_screen             ; // Equivlant x-y coord. on DrawingArea
long      y1_screen             ; // Equivlant x-y coord. on DrawingArea
long      x2_screen             ; // Equivlant x-y coord. on DrawingArea
long      y2_screen             ; // Equivlant x-y coord. on DrawingArea

double    ONE_PIXEL             ; // Number of DB Unit per ONE Pixel
double    x_diff                ; // Window / Zoom ALL  working variable
double    y_diff                ; // Window / Zoom ALL  working variable
double    xy_diff               ; // Window / Zoom ALL  working variable
double    scale                 ; // Current Scale
double    tolerance             ; // Correlation tolerance
double    distance              ; // Computed Distance
double    radius                ; // Computed Distance for Clipping
double    symb_factor           ; // Symbol Drawing Factor
double    SCREEN_CM             ; // Drawing area Size in CM

double    x_center              ; // Center x Coord of displayed Database
double    y_center              ; // Center y Coord of displayed Database

double    x_min_plot            ; // Min x PLOT Window Limits
double    y_min_plot            ; // Min y PLOT Window Limits
double    x_max_plot            ; // Max x PLOT Window Limits
double    y_max_plot            ; // Max y PLOT Window Limits

double    x_old                 ; // Move feat
double    y_old                 ; //
double    x_new                 ; //
double    y_new                 ; //

long      x_last                ; // Mouse_move last x
long      y_last                ; // Mouse_move last y

long      x_base                ; //
long      y_base                ; //
long      x_end                 ; //
long      y_end                 ; //

double    x_mouse               ; // Mouse move coord to Display XY
double    y_mouse               ; // Mouse move coord to Display XY

int       DB_UNIT               ; // DB unit of workspace default DM
char      DB_UNIT_NAME [10]     ; // DB unit Name of workspace
int       draw_fun              ; // (1)window, (2)add point, (3)add line
int       last_fun              ; // (1)window, (2)add point, (3)add line
int       move_fun              ; // (1) crosshair , (2) rubber box
int       search_status         ; // Feature search status
char      scale_ch [40]         ; // Current Scale in Character form
char      Message  [40]         ; // System Message Line

long      feat_count            ; // Total Number of features
long      lay_count             ; // Total Number of layers
long      selected_feat         ; // Feature Number to be EDIT
int       point_counter         ; //
int       cursor_size           ; // Cursor Size in Pixles
int       color                 ; //
int       size                  ; //
int       symb_no               ; //
int       font_no               ; //
int       cls_flag              ; // clear screen flag
int       rc                    ; // DXF read return code

FILE      *fp_i                 ; // Input  file pointer
FILE      *fp_o                 ; // Output file pointer
FILE      *fopen()              ; //
char      InputFile  [51]       ; // Input  file name
char      OutputFile [51]       ; // Output file name

int       n                     ; // X args counter
long      i , ii , iii          ; // LOOP Counters
long      j , jj                ; // LOOP Counters

double    a,b,angle             ; // Line Correlation paramters
double    x_line,y_line         ; // Line Correlation paramters
double    x_small               ; // Enclosure Box x_small
double    y_small               ; // Enclosure Box y_small
double    x_big                 ; // Enclosure Box x_big
double    y_big                 ; // Enclosure Box y_big

double    angle_sym             ; // Line Correlation paramters
char      string[61]            ; // Text Drawing String
char      dummyT [51]           ; // Text Drawing String

long      text_index            ;
long      text_LAST             ;
long      length                ;

int       conn_count            ;
int       conn_list  [1000]     ;
/*
short     org_color  [1000]     ;
*/
short     org_linetype [100000] ;

char      db_opened    [1]      ;
char      DB_name      [21]     ;
char      DB_password  [21]     ;
long      AREA_XMIN             ;
long      AREA_XMAX             ;
long      AREA_YMIN             ;
long      AREA_YMAX             ;
char      GRID_NAME    [21]     ;
char      FEEDER_NAME  [200]    ;
char      trace_on     [1]      ;


short     return_code           ; // fun call 0 normal, 1 cancel, 2 error
int       sc_range              ;

short     num                   ;
short     den                   ;
short     threshold             ;
short     SP_flag               ;
short     activateMenubar       ;
short     enable_leave          ;
short     enable_enter          ;

char      STR_PARM   [51]       ; // Charcter Pramter  LINUX
int       need_draw_all         ;
char      queue_name[20]        ; // Print Queue Name
char      IMPORTPATH[50]        ; // DATA Import Path

long      SC_RANGE1             ;
long      SC_RANGE2             ;
long      SC_RANGE3             ;
long      SC_RANGE4             ;
float     REFRESH               ;
short     DXF_DB_UNIT           ; // IMPORTED DXF DB unit
short     JOIN_TOLERANCE        ; // Edge Matching & Join Tolerance in DBU


