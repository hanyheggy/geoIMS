static char sqla_program_id[162] = 
{
 42,0,65,68,65,75,65,73,71,69,79,69,68,73,84,32,70,66,122,75,
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


#line 1 "geoedit.sqc"
/*------------------------------------------------------------------------*/
/*                geoINFO/6000  Edit Panel  ( geoedit.sqc)                */
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


#line 13 "geoedit.sqc"


/*------------------------------------------------------------------------*/
/*                           Functions Prototypes                         */
/*------------------------------------------------------------------------*/
void saveEditCB()      ;
void saveEditPicCB()   ;
void saveEditParmCB()  ;
void cancelEditCB()    ;
void cancelEditPicCB() ;
void cancelEditParmCB();

Widget create_label()  ;
Widget create_pbutton();
Widget create_tfield() ;

/*------------------------------------------------------------------------*/
/*                           Widget Definition                            */
/*------------------------------------------------------------------------*/
Widget  EditForm           ;
Widget  Edit_save_button   ;
Widget  Edit_cancel_button ;
Widget  Edit_separator     ;
Widget  Label[20]          ;
Widget  Field[20]          ;

/*------------------------------------------------------------------------*/
/*                   Global Variable Definition                           */
/*------------------------------------------------------------------------*/
char feat_code[21]       ;
char no_data_record[1]   ;



/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 46 "geoedit.sqc"

   long    feat_num1     ;

   char    status1 [3]   ;
   char    subid1  [13]  ;
   char    fdrnum1 [13]  ;
   char    subtype1[21]  ;
   long    kva1          ;

   char    gridid1  [13] ;
   char    mva      [5]  ;
   char    fdrtype1 [13] ;
   char    privolt1 [13] ;
   char    secvolt1 [13] ;
   long    length1       ;
   char    from     [13] ;
   char    to       [13] ;
   char    lmr1     [2]  ;
   char    lmr2     [2]  ;
   char    nearsub  [13] ;
   char    farsub   [13] ;

   char    name     [51] ;
   char    flow     [3]  ;
   long    width         ;
   long    length        ;
   long    weight        ;

   char    scale_range [6]     ;
   char    displayed   [1]     ;
   short   feat_color          ;
   short   feat_linetype       ;
   short   feat_linewidth      ;
   long    symb_num            ;
   long    symb_size           ;
   long    symb_angle          ;
   char    text_string [51]    ;
   long    text_font           ;
   long    text_size           ;
   long    text_angle          ;


/*
EXEC SQL END DECLARE SECTION;
*/

#line 87 "geoedit.sqc"



/*------------------------------------------------------------------------*/
/*                             editfeature()                              */
/*------------------------------------------------------------------------*/

void edit(Widget parent)
{
 XmString  xstr       ;
 Arg       args[20]   ;
 int       i          ;
 int       n          ;
 char      value [50] ;
 int       xWidget    ;
 int       yWidget    ;


 no_data_record[0] = 'N' ;

 feat_num1 = feat[selected_feat].num  ;
 strcpy (feat_code, feat[selected_feat].code) ;



 if ( strcmp (feat_code,"grid") == 0  &&  db_opened[0] == 'Y' )
    {
     
/*
EXEC SQL SELECT STATUS,GRID_ID,PRI_VOLT,SEC_VOLT,MVA
	      INTO   :status1,:gridid1,:privolt1,:secvolt1,:mva
	      FROM   GRID
	      WHERE  FEAT_NUM = :feat_num1 ;
*/

{
#line 117 "geoedit.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 117 "geoedit.sqc"
  sqlaaloc(2,1,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 117 "geoedit.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 117 "geoedit.sqc"
      sql_setdlist[0].sqldata = (void*)&feat_num1;
#line 117 "geoedit.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 117 "geoedit.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 117 "geoedit.sqc"
  sqlaaloc(3,5,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 117 "geoedit.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 3;
#line 117 "geoedit.sqc"
      sql_setdlist[0].sqldata = (void*)status1;
#line 117 "geoedit.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 117 "geoedit.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 13;
#line 117 "geoedit.sqc"
      sql_setdlist[1].sqldata = (void*)gridid1;
#line 117 "geoedit.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 117 "geoedit.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 13;
#line 117 "geoedit.sqc"
      sql_setdlist[2].sqldata = (void*)privolt1;
#line 117 "geoedit.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 117 "geoedit.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 13;
#line 117 "geoedit.sqc"
      sql_setdlist[3].sqldata = (void*)secvolt1;
#line 117 "geoedit.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 117 "geoedit.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 5;
#line 117 "geoedit.sqc"
      sql_setdlist[4].sqldata = (void*)mva;
#line 117 "geoedit.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 117 "geoedit.sqc"
      sqlasetdata(3,0,5,sql_setdlist,0L,0L);
    }
#line 117 "geoedit.sqc"
  sqlacall((unsigned short)24,1,2,3,0L);
#line 117 "geoedit.sqc"
  sqlastop(0L);
}

#line 117 "geoedit.sqc"


      // CHECKERR ("SELECT");

      if (SQLCODE != 0 )
         {
          switch (SQLCODE)   // NEW 30/03/2003
            {
             case 100:
               no_data_record[0] = 'Y' ;
               strcpy (status1  , "" );
               strcpy (gridid1  , "" );
               strcpy (privolt1 , "" );
               strcpy (secvolt1 , "" );
               strcpy (mva      , "" );
               break;

             default:
               fprintf(stderr,"ERROR : SQLCODE = %d",SQLCODE);
               draw_feature(selected_feat);
               // normal_cursor();
               draw_fun = EDIT ;
               return;
            }
         }

     /*------------------ Creat Form Dialog ---------------------*/
     sprintf (value,"EDIT  [ %s :  %d ]",feat_code,feat_num1);
     xstr = XmStringCreate(value,CS);
     n=0;
     XtSetArg(args[n] , XmNdialogTitle ,                       xstr);n++;
     XtSetArg(args[n] , XmNx           ,                          0);n++;
     XtSetArg(args[n] , XmNy           ,                          0);n++;
     XtSetArg(args[n] , XmNbackground  ,                lgray.pixel);n++;
     XtSetArg(args[n] , XmNdialogStyle , XmDIALOG_APPLICATION_MODAL);n++;

     EditForm = XmCreateFormDialog(parent,"EditForm", args,n);


     /*------------------  Create Labels ------------------------*/
     xWidget = 10 ;
     yWidget = 10 ;

     Label[0]=create_label(EditForm,"Status"        ,xWidget,yWidget,100,30,lgray.pixel); yWidget+=30 ;
     Label[1]=create_label(EditForm,"Gridstation ID",xWidget,yWidget,100,30,lgray.pixel); yWidget+=30 ;
     Label[2]=create_label(EditForm,"Primary Volt"  ,xWidget,yWidget,100,30,lgray.pixel); yWidget+=30 ;
     Label[3]=create_label(EditForm,"Secondary Volt",xWidget,yWidget,100,30,lgray.pixel); yWidget+=30 ;
     Label[4]=create_label(EditForm,"MAV"           ,xWidget,yWidget,100,30,lgray.pixel); yWidget+=30 ;


     /*-------------------- Create Fields -----------------------*/
     xWidget = 120 ;
     yWidget = 10  ;

     Field[0]=create_tfield(EditForm,status1 ,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;
     Field[1]=create_tfield(EditForm,gridid1 ,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;
     Field[2]=create_tfield(EditForm,privolt1,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;
     Field[3]=create_tfield(EditForm,secvolt1,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;
     Field[4]=create_tfield(EditForm,mva     ,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;


     /*------------------ add a separator --------------------------*/
     /*
     n=0;
     yWidget+=10 ;
     XtSetArg(args[n] , XmNy           ,     yWidget);n++;
     XtSetArg(args[n] , XmNbackground  , lgray.pixel);n++;
     Edit_separator =(Widget)XmCreateSeparator(EditForm,"Separator",args,n);
     XtManageChild(Edit_separator);
     -- OR --
     Edit_separator = (Widget)XmCreateSeparatorGadget(EditForm,"separator",((Arg  *)0),0);
     XtVaSetValues(Edit_separator ,XmNforeground,black.pixel,NULL);
     XtManageChild(Edit_separator);
     */

     /*-------------------- Create Buttons ----------------------*/

     yWidget+=10 ;
     Edit_save_button = create_pbutton (EditForm,"SAVE",10,yWidget,80,30,gray.pixel) ;
     XtAddCallback(Edit_save_button,XmNactivateCallback,saveEditCB,EditForm);

     Edit_cancel_button = create_pbutton (EditForm,"Cancel",200,yWidget,80,30,gray.pixel) ;
     XtAddCallback(Edit_cancel_button,XmNactivateCallback,cancelEditCB,EditForm);


     /*----------- Set Initial Focus & Default Button -----------*/

     XtSetArg(args[0], XmNinitialFocus , Field[0]);
     XtSetValues(EditForm,args,1);

     XtSetArg(args[0], XmNdefaultButton, Edit_save_button);
     XtSetValues(EditForm,args,1);

     /*------------------ Display Form Dialog --------------------*/

     XtManageChild(EditForm);
     XtRealizeWidget(EditForm);

     /*--------------------- Grab Form Dialog --------------------*/

     XtAddGrab(EditForm ,True,False );
    }
 else
 if ( strcmp (feat_code,"substation") == 0  &&  db_opened[0] == 'Y' )
    {
     
/*
EXEC SQL SELECT STATUS,SUB_ID,GRID_ID,FEEDER_NUM,TYPE,KVA,PRI_VOLT,SEC_VOLT
	      INTO   :status1,:subid1,:gridid1,:fdrnum1,:subtype1,:kva1,:privolt1,:secvolt1
	      FROM   DISTSTN
	      WHERE  FEAT_NUM = :feat_num1 ;
*/

{
#line 225 "geoedit.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 225 "geoedit.sqc"
  sqlaaloc(2,1,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 225 "geoedit.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 225 "geoedit.sqc"
      sql_setdlist[0].sqldata = (void*)&feat_num1;
#line 225 "geoedit.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 225 "geoedit.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 225 "geoedit.sqc"
  sqlaaloc(3,8,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[8];
#line 225 "geoedit.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 3;
#line 225 "geoedit.sqc"
      sql_setdlist[0].sqldata = (void*)status1;
#line 225 "geoedit.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 225 "geoedit.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 13;
#line 225 "geoedit.sqc"
      sql_setdlist[1].sqldata = (void*)subid1;
#line 225 "geoedit.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 225 "geoedit.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 13;
#line 225 "geoedit.sqc"
      sql_setdlist[2].sqldata = (void*)gridid1;
#line 225 "geoedit.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 225 "geoedit.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 13;
#line 225 "geoedit.sqc"
      sql_setdlist[3].sqldata = (void*)fdrnum1;
#line 225 "geoedit.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 225 "geoedit.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 21;
#line 225 "geoedit.sqc"
      sql_setdlist[4].sqldata = (void*)subtype1;
#line 225 "geoedit.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 225 "geoedit.sqc"
      sql_setdlist[5].sqltype = 496; sql_setdlist[5].sqllen = 4;
#line 225 "geoedit.sqc"
      sql_setdlist[5].sqldata = (void*)&kva1;
#line 225 "geoedit.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 225 "geoedit.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 13;
#line 225 "geoedit.sqc"
      sql_setdlist[6].sqldata = (void*)privolt1;
#line 225 "geoedit.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 225 "geoedit.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 13;
#line 225 "geoedit.sqc"
      sql_setdlist[7].sqldata = (void*)secvolt1;
#line 225 "geoedit.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 225 "geoedit.sqc"
      sqlasetdata(3,0,8,sql_setdlist,0L,0L);
    }
#line 225 "geoedit.sqc"
  sqlacall((unsigned short)24,2,2,3,0L);
#line 225 "geoedit.sqc"
  sqlastop(0L);
}

#line 225 "geoedit.sqc"


      // CHECKERR ("SELECT");

      if (SQLCODE == 100 )
         {
          no_data_record[0] = 'Y' ;

          strcpy (status1  , "" );
          strcpy (subid1   , "" );
          strcpy (gridid1  , "" );
          strcpy (fdrnum1  , "" );
          strcpy (subtype1 , "" );
          kva1 = 0 ;
          strcpy (privolt1 , "" );
          strcpy (secvolt1 , "" );
         }

     /*-------------------- FormDialog ------------------------*/
     sprintf (value,"EDIT  [ %s :  %d ]",feat_code,feat_num1);
     xstr = XmStringCreate(value,CS);
     n=0;
     XtSetArg(args[n] , XmNdialogTitle ,        xstr);n++;
     XtSetArg(args[n] , XmNx           ,           0);n++;
     XtSetArg(args[n] , XmNy           ,           0);n++;
     XtSetArg(args[n] , XmNbackground  , lgray.pixel);n++;

     EditForm = XmCreateFormDialog(parent,"EditForm", args,n);

     /*------------------  Create Labels ------------------------*/
     xWidget = 10 ;
     yWidget = 10 ;

     Label[0]=create_label(EditForm,"Status"         ,xWidget,yWidget,100,30,lgray.pixel); yWidget+=30 ;
     Label[1]=create_label(EditForm,"Substation id"  ,xWidget,yWidget,100,30,lgray.pixel); yWidget+=30 ;
     Label[2]=create_label(EditForm,"Grid id "       ,xWidget,yWidget,100,30,lgray.pixel); yWidget+=30 ;
     Label[3]=create_label(EditForm,"Feeder id "     ,xWidget,yWidget,100,30,lgray.pixel); yWidget+=30 ;
     Label[4]=create_label(EditForm,"Substation Type",xWidget,yWidget,100,30,lgray.pixel); yWidget+=30 ;
     Label[5]=create_label(EditForm,"KVA"            ,xWidget,yWidget,100,30,lgray.pixel); yWidget+=30 ;
     Label[6]=create_label(EditForm,"Primary Volt"   ,xWidget,yWidget,100,30,lgray.pixel); yWidget+=30 ;
     Label[7]=create_label(EditForm,"Secondary Volt" ,xWidget,yWidget,100,30,lgray.pixel); yWidget+=30 ;


     /*-------------------- Create Fields -----------------------*/
     xWidget = 120 ;
     yWidget = 10  ;

     Field[0]=create_tfield(EditForm,status1 ,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;
     Field[1]=create_tfield(EditForm,subid1  ,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;
     Field[2]=create_tfield(EditForm,gridid1 ,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;
     Field[3]=create_tfield(EditForm,fdrnum1 ,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;
     Field[4]=create_tfield(EditForm,subtype1,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;
              strcpy  (value,"");
              sprintf (value,"%d",kva1);
     Field[5]=create_tfield(EditForm,value   ,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;
     Field[6]=create_tfield(EditForm,privolt1,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;
     Field[7]=create_tfield(EditForm,secvolt1,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;



      /*-------------------- Create Buttons ----------------------*/

     yWidget+=10 ;
     Edit_save_button = create_pbutton (EditForm,"SAVE",10,yWidget,80,30,gray.pixel) ;
     XtAddCallback(Edit_save_button,XmNactivateCallback,saveEditCB,EditForm);

     Edit_cancel_button = create_pbutton (EditForm,"Cancel",200,yWidget,80,30,gray.pixel) ;
     XtAddCallback(Edit_cancel_button,XmNactivateCallback,cancelEditCB,EditForm);


     /*----------- Set Initial Focus & Default Button -----------*/

     XtSetArg(args[0], XmNinitialFocus , Field[0]);
     XtSetValues(EditForm,args,1);

     XtSetArg(args[0], XmNdefaultButton, Edit_save_button);
     XtSetValues(EditForm,args,1);

     /*------------------ Display Form Dialog -------------------*/

     XtManageChild(EditForm);
     XtRealizeWidget(EditForm);

     /*--------------------- Grab Form Dailog -------------------*/

     XtAddGrab(EditForm ,True,False );
    }
 else
 if ( strcmp (feat_code,"open_point") == 0  &&  db_opened[0] == 'Y' )
    {
     
/*
EXEC SQL SELECT STATUS,NEAR_SUB,FAR_SUB
	      INTO   :status1,:nearsub,:farsub
	      FROM   MVOPENPT
	      WHERE  FEAT_NUM = :feat_num1 ;
*/

{
#line 318 "geoedit.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 318 "geoedit.sqc"
  sqlaaloc(2,1,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 318 "geoedit.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 318 "geoedit.sqc"
      sql_setdlist[0].sqldata = (void*)&feat_num1;
#line 318 "geoedit.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 318 "geoedit.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 318 "geoedit.sqc"
  sqlaaloc(3,3,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 318 "geoedit.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 3;
#line 318 "geoedit.sqc"
      sql_setdlist[0].sqldata = (void*)status1;
#line 318 "geoedit.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 318 "geoedit.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 13;
#line 318 "geoedit.sqc"
      sql_setdlist[1].sqldata = (void*)nearsub;
#line 318 "geoedit.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 318 "geoedit.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 13;
#line 318 "geoedit.sqc"
      sql_setdlist[2].sqldata = (void*)farsub;
#line 318 "geoedit.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 318 "geoedit.sqc"
      sqlasetdata(3,0,3,sql_setdlist,0L,0L);
    }
#line 318 "geoedit.sqc"
  sqlacall((unsigned short)24,3,2,3,0L);
#line 318 "geoedit.sqc"
  sqlastop(0L);
}

#line 318 "geoedit.sqc"


      // CHECKERR ("SELECT");

      if (SQLCODE == 100 )
         {
          no_data_record[0] = 'Y' ;

          strcpy (status1  , "" );
          strcpy (nearsub  , "" );
          strcpy (farsub   , "" );
         }

     /*-------------------- FormDialog ------------------------*/
     sprintf (value,"EDIT  [ %s :  %d ]",feat_code,feat_num1);
     xstr = XmStringCreate(value,CS);
     n=0;
     XtSetArg(args[n] , XmNdialogTitle ,        xstr);n++;
     XtSetArg(args[n] , XmNx           ,           0);n++;
     XtSetArg(args[n] , XmNy           ,           0);n++;
     XtSetArg(args[n] , XmNbackground  , lgray.pixel);n++;

     EditForm = XmCreateFormDialog(parent,"EditForm", args,n);

     /*------------------  Create Labels ------------------------*/
     xWidget = 10 ;
     yWidget = 10 ;

     Label[0]=create_label(EditForm,"Status"         ,xWidget,yWidget,100,30,lgray.pixel); yWidget+=30 ;
     Label[1]=create_label(EditForm,"Near Substation",xWidget,yWidget,100,30,lgray.pixel); yWidget+=30 ;
     Label[2]=create_label(EditForm,"Far  Substation",xWidget,yWidget,100,30,lgray.pixel); yWidget+=30 ;


     /*-------------------- Create Fields -----------------------*/
     xWidget = 120 ;
     yWidget = 10  ;

     Field[0]=create_tfield(EditForm,status1 ,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;
     Field[1]=create_tfield(EditForm,nearsub ,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;
     Field[2]=create_tfield(EditForm,farsub  ,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;


      /*-------------------- Create Buttons ----------------------*/

     yWidget+=10 ;
     Edit_save_button = create_pbutton (EditForm,"SAVE",10,yWidget,80,30,gray.pixel) ;
     XtAddCallback(Edit_save_button,XmNactivateCallback,saveEditCB,EditForm);

     Edit_cancel_button = create_pbutton (EditForm,"Cancel",200,yWidget,80,30,gray.pixel) ;
     XtAddCallback(Edit_cancel_button,XmNactivateCallback,cancelEditCB,EditForm);


     /*----------- Set Initial Focus & Default Button -----------*/

     XtSetArg(args[0], XmNinitialFocus , Field[0]);
     XtSetValues(EditForm,args,1);

     XtSetArg(args[0], XmNdefaultButton, Edit_save_button);
     XtSetValues(EditForm,args,1);

     /*------------------ Display FormDialog --------------------*/

     XtManageChild(EditForm);
     XtRealizeWidget(EditForm);

     /*--------------------- Grab Form Dailog -------------------*/

     XtAddGrab(EditForm ,True,False );
    }
else
 if ( strcmp (feat_code,"mvfeeder") == 0 &&  db_opened[0] == 'Y' )
    {
     
/*
EXEC SQL SELECT STATUS,FEEDER_NUM,GRID_ID,UG_OH,PRI_VOLT,LENGTH,FROM_SUB,LMR1,TO_SUB,LMR2
	      INTO   :status1,:fdrnum1,:gridid1,:fdrtype1,:privolt1,:length1,:from,:lmr1,:to,:lmr2
	      FROM   MVFEEDER
	      WHERE  FEAT_NUM = :feat_num1 ;
*/

{
#line 393 "geoedit.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 393 "geoedit.sqc"
  sqlaaloc(2,1,7,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 393 "geoedit.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 393 "geoedit.sqc"
      sql_setdlist[0].sqldata = (void*)&feat_num1;
#line 393 "geoedit.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 393 "geoedit.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 393 "geoedit.sqc"
  sqlaaloc(3,10,8,0L);
    {
      struct sqla_setdata_list sql_setdlist[10];
#line 393 "geoedit.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 3;
#line 393 "geoedit.sqc"
      sql_setdlist[0].sqldata = (void*)status1;
#line 393 "geoedit.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 393 "geoedit.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 13;
#line 393 "geoedit.sqc"
      sql_setdlist[1].sqldata = (void*)fdrnum1;
#line 393 "geoedit.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 393 "geoedit.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 13;
#line 393 "geoedit.sqc"
      sql_setdlist[2].sqldata = (void*)gridid1;
#line 393 "geoedit.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 393 "geoedit.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 13;
#line 393 "geoedit.sqc"
      sql_setdlist[3].sqldata = (void*)fdrtype1;
#line 393 "geoedit.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 393 "geoedit.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 13;
#line 393 "geoedit.sqc"
      sql_setdlist[4].sqldata = (void*)privolt1;
#line 393 "geoedit.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 393 "geoedit.sqc"
      sql_setdlist[5].sqltype = 496; sql_setdlist[5].sqllen = 4;
#line 393 "geoedit.sqc"
      sql_setdlist[5].sqldata = (void*)&length1;
#line 393 "geoedit.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 393 "geoedit.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 13;
#line 393 "geoedit.sqc"
      sql_setdlist[6].sqldata = (void*)from;
#line 393 "geoedit.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 393 "geoedit.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 2;
#line 393 "geoedit.sqc"
      sql_setdlist[7].sqldata = (void*)lmr1;
#line 393 "geoedit.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 393 "geoedit.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 13;
#line 393 "geoedit.sqc"
      sql_setdlist[8].sqldata = (void*)to;
#line 393 "geoedit.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 393 "geoedit.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 2;
#line 393 "geoedit.sqc"
      sql_setdlist[9].sqldata = (void*)lmr2;
#line 393 "geoedit.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 393 "geoedit.sqc"
      sqlasetdata(3,0,10,sql_setdlist,0L,0L);
    }
#line 393 "geoedit.sqc"
  sqlacall((unsigned short)24,4,2,3,0L);
#line 393 "geoedit.sqc"
  sqlastop(0L);
}

#line 393 "geoedit.sqc"


      // CHECKERR ("SELECT");

      if (SQLCODE == 100 )
         {
          no_data_record[0] = 'Y' ;

          strcpy (status1  , "" );
          strcpy (fdrnum1  , "" );
          strcpy (gridid1  , "" );
          strcpy (fdrtype1 , "" );
          strcpy (privolt1 , "" );
          length1  = 0 ;
          strcpy (from     , "" );
          strcpy (lmr1     , "" );
          strcpy (to       , "" );
          strcpy (lmr2     , "" );
         }


     /*------------------ Creat Form Dialog ---------------------*/
     sprintf (value,"EDIT  [ %s :  %d ]",feat_code,feat_num1);
     xstr = XmStringCreate(value,CS);
     n=0;
     XtSetArg(args[n] , XmNdialogTitle ,                       xstr);n++;
     XtSetArg(args[n] , XmNx           ,                          0);n++;
     XtSetArg(args[n] , XmNy           ,                          0);n++;
     XtSetArg(args[n] , XmNbackground  ,                lgray.pixel);n++;
     XtSetArg(args[n] , XmNdialogStyle , XmDIALOG_APPLICATION_MODAL);n++;

     EditForm = XmCreateFormDialog(parent,"EditForm", args,n);


     /*------------------  Create Labels ------------------------*/
     xWidget = 10 ;
     yWidget = 10 ;

     Label[0]=create_label(EditForm,"Status"         ,xWidget,yWidget,100,30,lgray.pixel); yWidget+=30 ;
     Label[1]=create_label(EditForm,"Feeder id"      ,xWidget,yWidget,100,30,lgray.pixel); yWidget+=30 ;
     Label[2]=create_label(EditForm,"Grid id"        ,xWidget,yWidget,100,30,lgray.pixel); yWidget+=30 ;
     Label[3]=create_label(EditForm,"Feeder Type"    ,xWidget,yWidget,100,30,lgray.pixel); yWidget+=30 ;
     Label[4]=create_label(EditForm,"Primary Voltage",xWidget,yWidget,100,30,lgray.pixel); yWidget+=30 ;
     Label[5]=create_label(EditForm,"Length"         ,xWidget,yWidget,100,30,lgray.pixel); yWidget+=30 ;
     Label[6]=create_label(EditForm,"From S/S"       ,xWidget,yWidget,100,30,lgray.pixel); yWidget+=30 ;
     Label[7]=create_label(EditForm,"LMR1"           ,xWidget,yWidget,100,30,lgray.pixel); yWidget+=30 ;
     Label[8]=create_label(EditForm,"To S/S"         ,xWidget,yWidget,100,30,lgray.pixel); yWidget+=30 ;
     Label[9]=create_label(EditForm,"LMR2"           ,xWidget,yWidget,100,30,lgray.pixel); yWidget+=30 ;


     /*-------------------- Create Fields -----------------------*/
     xWidget = 120 ;
     yWidget = 10  ;

     Field[0]=create_tfield(EditForm,status1 ,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;
     Field[1]=create_tfield(EditForm,fdrnum1 ,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;
     Field[2]=create_tfield(EditForm,gridid1 ,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;
     Field[3]=create_tfield(EditForm,fdrtype1,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;
     Field[4]=create_tfield(EditForm,privolt1,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;
              strcpy  (value,"");
              sprintf (value,"%d",length1);
     Field[5]=create_tfield(EditForm,value   ,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;
     Field[6]=create_tfield(EditForm,from    ,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;
     Field[7]=create_tfield(EditForm,lmr1    ,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;
     Field[8]=create_tfield(EditForm,to      ,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;
     Field[9]=create_tfield(EditForm,lmr2    ,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;


      /*-------------------- Create Buttons ----------------------*/

     yWidget+=10 ;
     Edit_save_button = create_pbutton (EditForm,"SAVE",10,yWidget,80,30,gray.pixel) ;
     XtAddCallback(Edit_save_button,XmNactivateCallback,saveEditCB,EditForm);

     Edit_cancel_button = create_pbutton (EditForm,"Cancel",200,yWidget,80,30,gray.pixel) ;
     XtAddCallback(Edit_cancel_button,XmNactivateCallback,cancelEditCB,EditForm);


     /*----------- Set Initial Focus & Default Button -----------*/

     XtSetArg(args[0], XmNinitialFocus , Field[0]);
     XtSetValues(EditForm,args,1);

     XtSetArg(args[0], XmNdefaultButton, Edit_save_button);
     XtSetValues(EditForm,args,1);

     /*------------------ Display FormDialog --------------------*/

     XtManageChild(EditForm);
     XtRealizeWidget(EditForm);

     /*--------------------- Grab Form Dailog -------------------*/

     XtAddGrab(EditForm ,True,False );
    }
else
 if ( strcmp (feat_code,"street") == 0  &&  db_opened[0] == 'Y' )
    {
     
/*
EXEC SQL SELECT NAME, FLOW, WIDTH, LENGTH, WEIGHT
	      INTO   :name,:flow,:width,:length,:weight
	      FROM   STREET
	      WHERE  FEAT_NUM = :feat_num1 ;
*/

{
#line 494 "geoedit.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 494 "geoedit.sqc"
  sqlaaloc(2,1,9,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 494 "geoedit.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 494 "geoedit.sqc"
      sql_setdlist[0].sqldata = (void*)&feat_num1;
#line 494 "geoedit.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 494 "geoedit.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 494 "geoedit.sqc"
  sqlaaloc(3,5,10,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 494 "geoedit.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 51;
#line 494 "geoedit.sqc"
      sql_setdlist[0].sqldata = (void*)name;
#line 494 "geoedit.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 494 "geoedit.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 3;
#line 494 "geoedit.sqc"
      sql_setdlist[1].sqldata = (void*)flow;
#line 494 "geoedit.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 494 "geoedit.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 494 "geoedit.sqc"
      sql_setdlist[2].sqldata = (void*)&width;
#line 494 "geoedit.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 494 "geoedit.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 494 "geoedit.sqc"
      sql_setdlist[3].sqldata = (void*)&length;
#line 494 "geoedit.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 494 "geoedit.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 494 "geoedit.sqc"
      sql_setdlist[4].sqldata = (void*)&weight;
#line 494 "geoedit.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 494 "geoedit.sqc"
      sqlasetdata(3,0,5,sql_setdlist,0L,0L);
    }
#line 494 "geoedit.sqc"
  sqlacall((unsigned short)24,5,2,3,0L);
#line 494 "geoedit.sqc"
  sqlastop(0L);
}

#line 494 "geoedit.sqc"


     
/*
EXEC SQL SELECT WEIGHT
	      INTO   :weight
	      FROM   CONNECTIVITY
	      WHERE  ARC = :feat_num1 ;
*/

{
#line 499 "geoedit.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 499 "geoedit.sqc"
  sqlaaloc(2,1,11,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 499 "geoedit.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 499 "geoedit.sqc"
      sql_setdlist[0].sqldata = (void*)&feat_num1;
#line 499 "geoedit.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 499 "geoedit.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 499 "geoedit.sqc"
  sqlaaloc(3,1,12,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 499 "geoedit.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 499 "geoedit.sqc"
      sql_setdlist[0].sqldata = (void*)&weight;
#line 499 "geoedit.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 499 "geoedit.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 499 "geoedit.sqc"
  sqlacall((unsigned short)24,6,2,3,0L);
#line 499 "geoedit.sqc"
  sqlastop(0L);
}

#line 499 "geoedit.sqc"



     /*--------------------- FormDialog ---------------------------*/
     sprintf (value,"EDIT  [ %s :  %d ]",feat_code,feat_num1);
     xstr = XmStringCreate(value,CS);
     n=0;
     XtSetArg(args[n] , XmNdialogTitle ,        xstr);n++;
     XtSetArg(args[n] , XmNx           ,           0);n++;
     XtSetArg(args[n] , XmNy           ,           0);n++;
     XtSetArg(args[n] , XmNbackground  , lgray.pixel);n++;

     EditForm = XmCreateFormDialog(parent,"EditForm", args,n);


     /*------------------  Create Labels ------------------------*/
     xWidget = 10 ;
     yWidget = 10 ;

     Label[0]=create_label(EditForm,"Name"       ,xWidget,yWidget,100,30,lgray.pixel); yWidget+=30 ;
     Label[1]=create_label(EditForm,"Flow Grade" ,xWidget,yWidget,100,30,lgray.pixel); yWidget+=30 ;
     Label[2]=create_label(EditForm,"Width"      ,xWidget,yWidget,100,30,lgray.pixel); yWidget+=30 ;
     Label[3]=create_label(EditForm,"Length"     ,xWidget,yWidget,100,30,lgray.pixel); yWidget+=30 ;
     Label[4]=create_label(EditForm,"Net Weight" ,xWidget,yWidget,100,30,lgray.pixel); yWidget+=30 ;


     /*-------------------- Create Fields -----------------------*/
     xWidget = 120 ;
     yWidget = 10  ;

     Field[0]=create_tfield(EditForm,name  ,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;
     Field[1]=create_tfield(EditForm,flow  ,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;
              strcpy  (value,"");
              sprintf (value,"%d",width);
     Field[2]=create_tfield(EditForm,value ,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;
              strcpy  (value,"");
              sprintf (value,"%d",length);
     Field[3]=create_tfield(EditForm,value ,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;
              strcpy  (value,"");
              sprintf (value,"%d",weight);
     Field[4]=create_tfield(EditForm,value ,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;


      /*-------------------- Create Buttons ----------------------*/

     yWidget+=10 ;
     Edit_save_button = create_pbutton (EditForm,"SAVE",10,yWidget,80,30,gray.pixel) ;
     XtAddCallback(Edit_save_button,XmNactivateCallback,saveEditCB,EditForm);

     Edit_cancel_button = create_pbutton (EditForm,"Cancel",200,yWidget,80,30,gray.pixel) ;
     XtAddCallback(Edit_cancel_button,XmNactivateCallback,cancelEditCB,EditForm);


     /*----------- Set Initial Focus & Default Button -----------*/

     XtSetArg(args[0], XmNinitialFocus , Field[0]);
     XtSetValues(EditForm,args,1);

     XtSetArg(args[0], XmNdefaultButton, Edit_save_button);
     XtSetValues(EditForm,args,1);

     /*------------------ Display FormDialog --------------------*/

     XtManageChild(EditForm);
     XtRealizeWidget(EditForm);

     /*--------------------- Grab Form Dailog -------------------*/

     XtAddGrab(EditForm ,True,False );
    }
else
    {
     /*-------------------- FormDialog ------------------------*/
     sprintf (value,"EDIT  [ Feature has no BD Recored ]");
     xstr = XmStringCreate(value,CS);
     n=0;
     XtSetArg(args[n] , XmNdialogTitle ,        xstr);n++;
     XtSetArg(args[n] , XmNx           ,           0);n++;
     XtSetArg(args[n] , XmNy           ,           0);n++;
     // XtSetArg(args[n] , XmNwidth    ,         400);n++;  // Used only with BulletinBoardDialog
     // XtSetArg(args[n] , XmNheight   ,         500);n++;
     XtSetArg(args[n] , XmNbackground  , lgray.pixel);n++;

     // EditForm = XmCreateBulletinBoardDialog(parent,"EditForm", args,n);
     EditForm = XmCreateFormDialog(parent,"EditForm", args,n);


     /*------------------  Create Labels ------------------------*/
     xWidget = 10 ;
     yWidget = 10 ;

     Label[0]=create_label(EditForm,"Feature Number" ,xWidget,yWidget,100,30,lgray.pixel); yWidget+=30 ;
     Label[1]=create_label(EditForm,"Feature Code"   ,xWidget,yWidget,100,30,lgray.pixel); yWidget+=30 ;
     Label[2]=create_label(EditForm,"Feature Type"   ,xWidget,yWidget,100,30,lgray.pixel); yWidget+=30 ;
     Label[3]=create_label(EditForm,"Layer Number"   ,xWidget,yWidget,100,30,lgray.pixel); yWidget+=30 ;


     /*-------------------- Create Fields -----------------------*/
     xWidget = 120 ;
     yWidget = 10  ;

              strcpy  (value,"");
              sprintf (value,"%d",feat[selected_feat].num);
     Field[0]=create_tfield(EditForm,value                    ,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;
     Field[1]=create_tfield(EditForm,feat[selected_feat].code ,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;
              strcpy  (value,"");
              sprintf (value,"%d",feat[selected_feat].type);
     Field[2]=create_tfield(EditForm,value                    ,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;
              strcpy  (value,"");
              sprintf (value,"%d",feat[selected_feat].layer);
     Field[3]=create_tfield(EditForm,value                    ,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;


      /*-------------------- Create Buttons ----------------------*/

     yWidget+=10 ;

     Edit_cancel_button = create_pbutton (EditForm,"Cancel",100,yWidget,80,30,gray.pixel) ;
     XtAddCallback(Edit_cancel_button,XmNactivateCallback,cancelEditCB,EditForm);


     /*----------- Set Initial Focus & Default Button -----------*/

     XtSetArg(args[0], XmNinitialFocus , Field[0]);
     XtSetValues(EditForm,args,1);

     XtSetArg(args[0], XmNdefaultButton, Edit_cancel_button );
     XtSetValues(EditForm,args,1);

     /* NEW Hany Heggy */
     XtSetArg(args[0] , XmNwidth , xWidget+170 );
     XtSetValues(EditForm,args,1);

     /*
     XtSetArg(args[0] , XmNheight , yWidget+50 );
     XtSetValues(EditForm,args,1);
     */

     /*------------------ Display FormDialog --------------------*/

     XtManageChild(EditForm);
     XtRealizeWidget(EditForm);

     /*--------------------- Grab Form Dailog -------------------*/

     XtAddGrab(EditForm ,True,False );
    }

} /* Main Edit */

/*------------------------CALL BACKS ------------------------------*/
/*------------------------CALL BACKS ------------------------------*/
/*------------------------CALL BACKS ------------------------------*/
/*------------------------CALL BACKS ------------------------------*/


/*-----------------------------------------------------------------*/
/*                        cancelEditCB()                           */
/*-----------------------------------------------------------------*/
void cancelEditCB()
{
 XtUnmanageChild(EditForm);
 XtDestroyWidget(EditForm);

 draw_feature(selected_feat);
 // normal_cursor();
 draw_fun = EDIT ;
}
/*-----------------------------------------------------------------*/
/*                       cancelEditPicCB()                         */
/*-----------------------------------------------------------------*/
void cancelEditPicCB()
{
 draw_feature(selected_feat);
 // normal_cursor();
 draw_fun = EDITPIC ;
}
/*-----------------------------------------------------------------*/
/*                          saveEditCB()                           */
/*-----------------------------------------------------------------*/
void saveEditCB(Widget w,caddr_t client_data,ANYCBS *call_data)
{
 Arg       args[20]   ;
 char     *str        ;
 char     command[50] ;
 char     value[50]   ;


 XtSetArg(args[0],XmNvalue,command);
 XtGetValues(Field[0],args,1);



 if ( strcmp (feat_code,"grid") == 0 )
    {
     strcpy (status1 ,XmTextGetString(Field[0]));
     strcpy (gridid1 ,XmTextGetString(Field[1]));
     strcpy (privolt1,XmTextGetString(Field[2]));
     strcpy (secvolt1,XmTextGetString(Field[3]));
     strcpy (mva     ,XmTextGetString(Field[4]));

     if ( no_data_record[0] == 'Y' )
        {
         // Insert New Record
         
/*
EXEC SQL INSERT INTO GRID
	      VALUES (:feat_num1,
	              :status1  ,
		      :gridid1  ,
		      :privolt1 ,
		      :secvolt1 ,
		      :mva        );
*/

{
#line 709 "geoedit.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 709 "geoedit.sqc"
  sqlaaloc(2,6,13,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 709 "geoedit.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 709 "geoedit.sqc"
      sql_setdlist[0].sqldata = (void*)&feat_num1;
#line 709 "geoedit.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 709 "geoedit.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 3;
#line 709 "geoedit.sqc"
      sql_setdlist[1].sqldata = (void*)status1;
#line 709 "geoedit.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 709 "geoedit.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 13;
#line 709 "geoedit.sqc"
      sql_setdlist[2].sqldata = (void*)gridid1;
#line 709 "geoedit.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 709 "geoedit.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 13;
#line 709 "geoedit.sqc"
      sql_setdlist[3].sqldata = (void*)privolt1;
#line 709 "geoedit.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 709 "geoedit.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 13;
#line 709 "geoedit.sqc"
      sql_setdlist[4].sqldata = (void*)secvolt1;
#line 709 "geoedit.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 709 "geoedit.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 5;
#line 709 "geoedit.sqc"
      sql_setdlist[5].sqldata = (void*)mva;
#line 709 "geoedit.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 709 "geoedit.sqc"
      sqlasetdata(2,0,6,sql_setdlist,0L,0L);
    }
#line 709 "geoedit.sqc"
  sqlacall((unsigned short)24,7,2,0,0L);
#line 709 "geoedit.sqc"
  sqlastop(0L);
}

#line 709 "geoedit.sqc"


         
/*
EXEC SQL COMMIT WORK ;
*/

{
#line 711 "geoedit.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 711 "geoedit.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 711 "geoedit.sqc"
  sqlastop(0L);
}

#line 711 "geoedit.sqc"

        }
     else
        {
         // Update Exsisting Recored
         
/*
EXEC SQL UPDATE GRID
	       SET STATUS      = :status1  ,
		   GRID_ID     = :gridid1  ,
		   PRI_VOLT    = :privolt1 ,
		   SEC_VOLT    = :secvolt1 ,
		   MVA         = :mva
	    WHERE  FEAT_NUM    = :feat_num1 ;
*/

{
#line 722 "geoedit.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 722 "geoedit.sqc"
  sqlaaloc(2,6,14,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 722 "geoedit.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 3;
#line 722 "geoedit.sqc"
      sql_setdlist[0].sqldata = (void*)status1;
#line 722 "geoedit.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 722 "geoedit.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 13;
#line 722 "geoedit.sqc"
      sql_setdlist[1].sqldata = (void*)gridid1;
#line 722 "geoedit.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 722 "geoedit.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 13;
#line 722 "geoedit.sqc"
      sql_setdlist[2].sqldata = (void*)privolt1;
#line 722 "geoedit.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 722 "geoedit.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 13;
#line 722 "geoedit.sqc"
      sql_setdlist[3].sqldata = (void*)secvolt1;
#line 722 "geoedit.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 722 "geoedit.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 5;
#line 722 "geoedit.sqc"
      sql_setdlist[4].sqldata = (void*)mva;
#line 722 "geoedit.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 722 "geoedit.sqc"
      sql_setdlist[5].sqltype = 496; sql_setdlist[5].sqllen = 4;
#line 722 "geoedit.sqc"
      sql_setdlist[5].sqldata = (void*)&feat_num1;
#line 722 "geoedit.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 722 "geoedit.sqc"
      sqlasetdata(2,0,6,sql_setdlist,0L,0L);
    }
#line 722 "geoedit.sqc"
  sqlacall((unsigned short)24,8,2,0,0L);
#line 722 "geoedit.sqc"
  sqlastop(0L);
}

#line 722 "geoedit.sqc"


         
/*
EXEC SQL COMMIT WORK ;
*/

{
#line 724 "geoedit.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 724 "geoedit.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 724 "geoedit.sqc"
  sqlastop(0L);
}

#line 724 "geoedit.sqc"

         // CHECKERR ("UPDATE");
        }
    }
 else
 if ( strcmp (feat_code,"substation") == 0 )
    {
     strcpy (status1 ,XmTextGetString(Field[0]));
     strcpy (subid1  ,XmTextGetString(Field[1]));
     strcpy (gridid1 ,XmTextGetString(Field[2]));
     strcpy (fdrnum1 ,XmTextGetString(Field[3]));
     strcpy (subtype1,XmTextGetString(Field[4]));
     strcpy (value   ,XmTextGetString(Field[5]));  sscanf(value,"%d",&kva1);
     strcpy (privolt1,XmTextGetString(Field[6]));
     strcpy (secvolt1,XmTextGetString(Field[7]));

     if ( no_data_record[0] == 'Y' )
        {
         // Insert New Record
         
/*
EXEC SQL INSERT INTO DISTSTN
	      VALUES (:feat_num1,
	              :status1  ,
		      :subid1   ,
		      :gridid1  ,
		      :fdrnum1  ,
		      :subtype1 ,
		      :kva1     ,
		      :privolt1 ,
		      :secvolt1   );
*/

{
#line 752 "geoedit.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 752 "geoedit.sqc"
  sqlaaloc(2,9,15,0L);
    {
      struct sqla_setdata_list sql_setdlist[9];
#line 752 "geoedit.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 752 "geoedit.sqc"
      sql_setdlist[0].sqldata = (void*)&feat_num1;
#line 752 "geoedit.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 752 "geoedit.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 3;
#line 752 "geoedit.sqc"
      sql_setdlist[1].sqldata = (void*)status1;
#line 752 "geoedit.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 752 "geoedit.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 13;
#line 752 "geoedit.sqc"
      sql_setdlist[2].sqldata = (void*)subid1;
#line 752 "geoedit.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 752 "geoedit.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 13;
#line 752 "geoedit.sqc"
      sql_setdlist[3].sqldata = (void*)gridid1;
#line 752 "geoedit.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 752 "geoedit.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 13;
#line 752 "geoedit.sqc"
      sql_setdlist[4].sqldata = (void*)fdrnum1;
#line 752 "geoedit.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 752 "geoedit.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 21;
#line 752 "geoedit.sqc"
      sql_setdlist[5].sqldata = (void*)subtype1;
#line 752 "geoedit.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 752 "geoedit.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 752 "geoedit.sqc"
      sql_setdlist[6].sqldata = (void*)&kva1;
#line 752 "geoedit.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 752 "geoedit.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 13;
#line 752 "geoedit.sqc"
      sql_setdlist[7].sqldata = (void*)privolt1;
#line 752 "geoedit.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 752 "geoedit.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 13;
#line 752 "geoedit.sqc"
      sql_setdlist[8].sqldata = (void*)secvolt1;
#line 752 "geoedit.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 752 "geoedit.sqc"
      sqlasetdata(2,0,9,sql_setdlist,0L,0L);
    }
#line 752 "geoedit.sqc"
  sqlacall((unsigned short)24,9,2,0,0L);
#line 752 "geoedit.sqc"
  sqlastop(0L);
}

#line 752 "geoedit.sqc"


         
/*
EXEC SQL COMMIT WORK ;
*/

{
#line 754 "geoedit.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 754 "geoedit.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 754 "geoedit.sqc"
  sqlastop(0L);
}

#line 754 "geoedit.sqc"

        }
     else
        {
         // Update Exsisting Recored
         
/*
EXEC SQL UPDATE DISTSTN
	       SET STATUS      = :status1  ,
		   SUB_ID      = :subid1   ,
		   GRID_ID     = :gridid1  ,
		   FEEDER_NUM  = :fdrnum1  ,
		   TYPE        = :subtype1 ,
		   KVA         = :kva1     ,
		   PRI_VOLT    = :privolt1 ,
		   SEC_VOLT    = :secvolt1
	    WHERE  FEAT_NUM    = :feat_num1 ;
*/

{
#line 768 "geoedit.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 768 "geoedit.sqc"
  sqlaaloc(2,9,16,0L);
    {
      struct sqla_setdata_list sql_setdlist[9];
#line 768 "geoedit.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 3;
#line 768 "geoedit.sqc"
      sql_setdlist[0].sqldata = (void*)status1;
#line 768 "geoedit.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 768 "geoedit.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 13;
#line 768 "geoedit.sqc"
      sql_setdlist[1].sqldata = (void*)subid1;
#line 768 "geoedit.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 768 "geoedit.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 13;
#line 768 "geoedit.sqc"
      sql_setdlist[2].sqldata = (void*)gridid1;
#line 768 "geoedit.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 768 "geoedit.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 13;
#line 768 "geoedit.sqc"
      sql_setdlist[3].sqldata = (void*)fdrnum1;
#line 768 "geoedit.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 768 "geoedit.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 21;
#line 768 "geoedit.sqc"
      sql_setdlist[4].sqldata = (void*)subtype1;
#line 768 "geoedit.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 768 "geoedit.sqc"
      sql_setdlist[5].sqltype = 496; sql_setdlist[5].sqllen = 4;
#line 768 "geoedit.sqc"
      sql_setdlist[5].sqldata = (void*)&kva1;
#line 768 "geoedit.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 768 "geoedit.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 13;
#line 768 "geoedit.sqc"
      sql_setdlist[6].sqldata = (void*)privolt1;
#line 768 "geoedit.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 768 "geoedit.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 13;
#line 768 "geoedit.sqc"
      sql_setdlist[7].sqldata = (void*)secvolt1;
#line 768 "geoedit.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 768 "geoedit.sqc"
      sql_setdlist[8].sqltype = 496; sql_setdlist[8].sqllen = 4;
#line 768 "geoedit.sqc"
      sql_setdlist[8].sqldata = (void*)&feat_num1;
#line 768 "geoedit.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 768 "geoedit.sqc"
      sqlasetdata(2,0,9,sql_setdlist,0L,0L);
    }
#line 768 "geoedit.sqc"
  sqlacall((unsigned short)24,10,2,0,0L);
#line 768 "geoedit.sqc"
  sqlastop(0L);
}

#line 768 "geoedit.sqc"


         
/*
EXEC SQL COMMIT WORK ;
*/

{
#line 770 "geoedit.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 770 "geoedit.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 770 "geoedit.sqc"
  sqlastop(0L);
}

#line 770 "geoedit.sqc"

         // CHECKERR ("UPDATE");
        }
    }
 else
 if ( strcmp (feat_code,"open_point") == 0 )
    {
     strcpy (status1 ,XmTextGetString(Field[0]));
     strcpy (nearsub ,XmTextGetString(Field[1]));
     strcpy (farsub  ,XmTextGetString(Field[2]));

     if ( no_data_record[0] == 'Y' )
        {
         // Insert New Record
         
/*
EXEC SQL INSERT INTO MVOPENPT
	      VALUES (:feat_num1,
	              :status1  ,
		      :nearsub  ,
		      :farsub     );
*/

{
#line 788 "geoedit.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 788 "geoedit.sqc"
  sqlaaloc(2,4,17,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 788 "geoedit.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 788 "geoedit.sqc"
      sql_setdlist[0].sqldata = (void*)&feat_num1;
#line 788 "geoedit.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 788 "geoedit.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 3;
#line 788 "geoedit.sqc"
      sql_setdlist[1].sqldata = (void*)status1;
#line 788 "geoedit.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 788 "geoedit.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 13;
#line 788 "geoedit.sqc"
      sql_setdlist[2].sqldata = (void*)nearsub;
#line 788 "geoedit.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 788 "geoedit.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 13;
#line 788 "geoedit.sqc"
      sql_setdlist[3].sqldata = (void*)farsub;
#line 788 "geoedit.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 788 "geoedit.sqc"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 788 "geoedit.sqc"
  sqlacall((unsigned short)24,11,2,0,0L);
#line 788 "geoedit.sqc"
  sqlastop(0L);
}

#line 788 "geoedit.sqc"


         
/*
EXEC SQL COMMIT WORK ;
*/

{
#line 790 "geoedit.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 790 "geoedit.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 790 "geoedit.sqc"
  sqlastop(0L);
}

#line 790 "geoedit.sqc"

        }
     else
        {
         // Update Exsisting Recored
         
/*
EXEC SQL UPDATE MVOPENPT
	       SET STATUS      = :status1  ,
		   NEAR_SUB    = :nearsub  ,
		   FAR_SUB     = :farsub
	    WHERE  FEAT_NUM    = :feat_num1 ;
*/

{
#line 799 "geoedit.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 799 "geoedit.sqc"
  sqlaaloc(2,4,18,0L);
    {
      struct sqla_setdata_list sql_setdlist[4];
#line 799 "geoedit.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 3;
#line 799 "geoedit.sqc"
      sql_setdlist[0].sqldata = (void*)status1;
#line 799 "geoedit.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 799 "geoedit.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 13;
#line 799 "geoedit.sqc"
      sql_setdlist[1].sqldata = (void*)nearsub;
#line 799 "geoedit.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 799 "geoedit.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 13;
#line 799 "geoedit.sqc"
      sql_setdlist[2].sqldata = (void*)farsub;
#line 799 "geoedit.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 799 "geoedit.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 799 "geoedit.sqc"
      sql_setdlist[3].sqldata = (void*)&feat_num1;
#line 799 "geoedit.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 799 "geoedit.sqc"
      sqlasetdata(2,0,4,sql_setdlist,0L,0L);
    }
#line 799 "geoedit.sqc"
  sqlacall((unsigned short)24,12,2,0,0L);
#line 799 "geoedit.sqc"
  sqlastop(0L);
}

#line 799 "geoedit.sqc"


         
/*
EXEC SQL COMMIT WORK ;
*/

{
#line 801 "geoedit.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 801 "geoedit.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 801 "geoedit.sqc"
  sqlastop(0L);
}

#line 801 "geoedit.sqc"

         // CHECKERR ("UPDATE");
        }
    }
 else
 if ( strcmp (feat_code,"mvfeeder") == 0 )
    {
     strcpy (status1  ,XmTextGetString(Field[0]));
     strcpy (fdrnum1  ,XmTextGetString(Field[1]));
     strcpy (gridid1  ,XmTextGetString(Field[2]));
     strcpy (fdrtype1 ,XmTextGetString(Field[3]));
     strcpy (privolt1 ,XmTextGetString(Field[4]));
     strcpy (value    ,XmTextGetString(Field[5]));  sscanf(value,"%d",&length1);
     strcpy (from     ,XmTextGetString(Field[6]));
     strcpy (lmr1     ,XmTextGetString(Field[7]));
     strcpy (to       ,XmTextGetString(Field[8]));
     strcpy (lmr2     ,XmTextGetString(Field[9]));

     if ( no_data_record[0] == 'Y' )
        {
         // Insert New Record
         
/*
EXEC SQL INSERT INTO MVFEEDER
	      VALUES (:feat_num1 ,
	              :status1   ,
	              :fdrnum1   ,
		      :gridid1   ,
	              :fdrtype1  ,
		      :privolt1  ,
		      :length1   ,
		      :from      ,
		      :lmr1      ,
		      :to        ,
		      :lmr2       );
*/

{
#line 833 "geoedit.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 833 "geoedit.sqc"
  sqlaaloc(2,11,19,0L);
    {
      struct sqla_setdata_list sql_setdlist[11];
#line 833 "geoedit.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 833 "geoedit.sqc"
      sql_setdlist[0].sqldata = (void*)&feat_num1;
#line 833 "geoedit.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 833 "geoedit.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 3;
#line 833 "geoedit.sqc"
      sql_setdlist[1].sqldata = (void*)status1;
#line 833 "geoedit.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 833 "geoedit.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 13;
#line 833 "geoedit.sqc"
      sql_setdlist[2].sqldata = (void*)fdrnum1;
#line 833 "geoedit.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 833 "geoedit.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 13;
#line 833 "geoedit.sqc"
      sql_setdlist[3].sqldata = (void*)gridid1;
#line 833 "geoedit.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 833 "geoedit.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 13;
#line 833 "geoedit.sqc"
      sql_setdlist[4].sqldata = (void*)fdrtype1;
#line 833 "geoedit.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 833 "geoedit.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 13;
#line 833 "geoedit.sqc"
      sql_setdlist[5].sqldata = (void*)privolt1;
#line 833 "geoedit.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 833 "geoedit.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 833 "geoedit.sqc"
      sql_setdlist[6].sqldata = (void*)&length1;
#line 833 "geoedit.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 833 "geoedit.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 13;
#line 833 "geoedit.sqc"
      sql_setdlist[7].sqldata = (void*)from;
#line 833 "geoedit.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 833 "geoedit.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 2;
#line 833 "geoedit.sqc"
      sql_setdlist[8].sqldata = (void*)lmr1;
#line 833 "geoedit.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 833 "geoedit.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 13;
#line 833 "geoedit.sqc"
      sql_setdlist[9].sqldata = (void*)to;
#line 833 "geoedit.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 833 "geoedit.sqc"
      sql_setdlist[10].sqltype = 460; sql_setdlist[10].sqllen = 2;
#line 833 "geoedit.sqc"
      sql_setdlist[10].sqldata = (void*)lmr2;
#line 833 "geoedit.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 833 "geoedit.sqc"
      sqlasetdata(2,0,11,sql_setdlist,0L,0L);
    }
#line 833 "geoedit.sqc"
  sqlacall((unsigned short)24,13,2,0,0L);
#line 833 "geoedit.sqc"
  sqlastop(0L);
}

#line 833 "geoedit.sqc"


         
/*
EXEC SQL COMMIT WORK ;
*/

{
#line 835 "geoedit.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 835 "geoedit.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 835 "geoedit.sqc"
  sqlastop(0L);
}

#line 835 "geoedit.sqc"

        }
     else
        {
         // Update Exsisting Recored
         
/*
EXEC SQL UPDATE MVFEEDER
	      SET    STATUS      = :status1  ,
		     FEEDER_NUM  = :fdrnum1  ,
		     GRID_ID     = :gridid1  ,
		     UG_OH       = :fdrtype1 ,
		     PRI_VOLT    = :privolt1 ,
		     LENGTH      = :length1  ,
		     FROM_SUB    = :from     ,
		     LMR1        = :lmr1     ,
		     TO_SUB      = :to       ,
		     LMR2        = :lmr2
	      WHERE  FEAT_NUM    = :feat_num1 ;
*/

{
#line 851 "geoedit.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 851 "geoedit.sqc"
  sqlaaloc(2,11,20,0L);
    {
      struct sqla_setdata_list sql_setdlist[11];
#line 851 "geoedit.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 3;
#line 851 "geoedit.sqc"
      sql_setdlist[0].sqldata = (void*)status1;
#line 851 "geoedit.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 851 "geoedit.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 13;
#line 851 "geoedit.sqc"
      sql_setdlist[1].sqldata = (void*)fdrnum1;
#line 851 "geoedit.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 851 "geoedit.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 13;
#line 851 "geoedit.sqc"
      sql_setdlist[2].sqldata = (void*)gridid1;
#line 851 "geoedit.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 851 "geoedit.sqc"
      sql_setdlist[3].sqltype = 460; sql_setdlist[3].sqllen = 13;
#line 851 "geoedit.sqc"
      sql_setdlist[3].sqldata = (void*)fdrtype1;
#line 851 "geoedit.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 851 "geoedit.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 13;
#line 851 "geoedit.sqc"
      sql_setdlist[4].sqldata = (void*)privolt1;
#line 851 "geoedit.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 851 "geoedit.sqc"
      sql_setdlist[5].sqltype = 496; sql_setdlist[5].sqllen = 4;
#line 851 "geoedit.sqc"
      sql_setdlist[5].sqldata = (void*)&length1;
#line 851 "geoedit.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 851 "geoedit.sqc"
      sql_setdlist[6].sqltype = 460; sql_setdlist[6].sqllen = 13;
#line 851 "geoedit.sqc"
      sql_setdlist[6].sqldata = (void*)from;
#line 851 "geoedit.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 851 "geoedit.sqc"
      sql_setdlist[7].sqltype = 460; sql_setdlist[7].sqllen = 2;
#line 851 "geoedit.sqc"
      sql_setdlist[7].sqldata = (void*)lmr1;
#line 851 "geoedit.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 851 "geoedit.sqc"
      sql_setdlist[8].sqltype = 460; sql_setdlist[8].sqllen = 13;
#line 851 "geoedit.sqc"
      sql_setdlist[8].sqldata = (void*)to;
#line 851 "geoedit.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 851 "geoedit.sqc"
      sql_setdlist[9].sqltype = 460; sql_setdlist[9].sqllen = 2;
#line 851 "geoedit.sqc"
      sql_setdlist[9].sqldata = (void*)lmr2;
#line 851 "geoedit.sqc"
      sql_setdlist[9].sqlind = 0L;
#line 851 "geoedit.sqc"
      sql_setdlist[10].sqltype = 496; sql_setdlist[10].sqllen = 4;
#line 851 "geoedit.sqc"
      sql_setdlist[10].sqldata = (void*)&feat_num1;
#line 851 "geoedit.sqc"
      sql_setdlist[10].sqlind = 0L;
#line 851 "geoedit.sqc"
      sqlasetdata(2,0,11,sql_setdlist,0L,0L);
    }
#line 851 "geoedit.sqc"
  sqlacall((unsigned short)24,14,2,0,0L);
#line 851 "geoedit.sqc"
  sqlastop(0L);
}

#line 851 "geoedit.sqc"


         
/*
EXEC SQL COMMIT WORK ;
*/

{
#line 853 "geoedit.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 853 "geoedit.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 853 "geoedit.sqc"
  sqlastop(0L);
}

#line 853 "geoedit.sqc"

         // CHECKERR ("UPDATE");
        }
    }
else
 if ( strcmp (feat_code,"street") == 0 )
    {
     strcpy (name    ,XmTextGetString(Field[0]));
     strcpy (flow    ,XmTextGetString(Field[1]));
     strcpy (value   ,XmTextGetString(Field[2]));   sscanf (value,"%d",&width );
     strcpy (value   ,XmTextGetString(Field[3]));   sscanf (value,"%d",&length);
     strcpy (value   ,XmTextGetString(Field[4]));   sscanf (value,"%d",&weight);

     
/*
EXEC SQL UPDATE STREET
	      SET    NAME        = :name     ,
		     FLOW        = :flow     ,
		     WIDTH       = :width    ,
		     LENGTH      = :length   ,
		     WEIGHT      = :weight
	      WHERE  FEAT_NUM    = :feat_num1 ;
*/

{
#line 872 "geoedit.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 872 "geoedit.sqc"
  sqlaaloc(2,6,21,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 872 "geoedit.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 51;
#line 872 "geoedit.sqc"
      sql_setdlist[0].sqldata = (void*)name;
#line 872 "geoedit.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 872 "geoedit.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 3;
#line 872 "geoedit.sqc"
      sql_setdlist[1].sqldata = (void*)flow;
#line 872 "geoedit.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 872 "geoedit.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 872 "geoedit.sqc"
      sql_setdlist[2].sqldata = (void*)&width;
#line 872 "geoedit.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 872 "geoedit.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 872 "geoedit.sqc"
      sql_setdlist[3].sqldata = (void*)&length;
#line 872 "geoedit.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 872 "geoedit.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 872 "geoedit.sqc"
      sql_setdlist[4].sqldata = (void*)&weight;
#line 872 "geoedit.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 872 "geoedit.sqc"
      sql_setdlist[5].sqltype = 496; sql_setdlist[5].sqllen = 4;
#line 872 "geoedit.sqc"
      sql_setdlist[5].sqldata = (void*)&feat_num1;
#line 872 "geoedit.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 872 "geoedit.sqc"
      sqlasetdata(2,0,6,sql_setdlist,0L,0L);
    }
#line 872 "geoedit.sqc"
  sqlacall((unsigned short)24,15,2,0,0L);
#line 872 "geoedit.sqc"
  sqlastop(0L);
}

#line 872 "geoedit.sqc"


     
/*
EXEC SQL COMMIT WORK ;
*/

{
#line 874 "geoedit.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 874 "geoedit.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 874 "geoedit.sqc"
  sqlastop(0L);
}

#line 874 "geoedit.sqc"

     // CHECKERR ("UPDATE");

     
/*
EXEC SQL UPDATE CONNECTIVITY
	      SET    WEIGHT = :weight
	      WHERE  ARC    = :feat_num1 ;
*/

{
#line 879 "geoedit.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 879 "geoedit.sqc"
  sqlaaloc(2,2,22,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 879 "geoedit.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 879 "geoedit.sqc"
      sql_setdlist[0].sqldata = (void*)&weight;
#line 879 "geoedit.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 879 "geoedit.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 879 "geoedit.sqc"
      sql_setdlist[1].sqldata = (void*)&feat_num1;
#line 879 "geoedit.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 879 "geoedit.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 879 "geoedit.sqc"
  sqlacall((unsigned short)24,16,2,0,0L);
#line 879 "geoedit.sqc"
  sqlastop(0L);
}

#line 879 "geoedit.sqc"


     
/*
EXEC SQL COMMIT WORK ;
*/

{
#line 881 "geoedit.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 881 "geoedit.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 881 "geoedit.sqc"
  sqlastop(0L);
}

#line 881 "geoedit.sqc"

     // CHECKERR ("UPDATE");


     //////////////////
     /* Color Coding */
     //////////////////
     if ( strcmp(flow,"A") == 0 || strcmp(flow,"a") == 0 || strcmp(flow,"A ") == 0 || strcmp(flow,"a ") == 0 )
        {
         feat[selected_feat].color = green.pixel ;
         
/*
EXEC SQL UPDATE FEATURES
	          SET    COLOR    = 4
	          WHERE  FEAT_NUM = :feat_num1 ;
*/

{
#line 893 "geoedit.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 893 "geoedit.sqc"
  sqlaaloc(2,1,23,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 893 "geoedit.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 893 "geoedit.sqc"
      sql_setdlist[0].sqldata = (void*)&feat_num1;
#line 893 "geoedit.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 893 "geoedit.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 893 "geoedit.sqc"
  sqlacall((unsigned short)24,17,2,0,0L);
#line 893 "geoedit.sqc"
  sqlastop(0L);
}

#line 893 "geoedit.sqc"

         
/*
EXEC SQL COMMIT WORK ;
*/

{
#line 894 "geoedit.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 894 "geoedit.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 894 "geoedit.sqc"
  sqlastop(0L);
}

#line 894 "geoedit.sqc"

         // CHECKERR ("UPDATE");
        }
    else
     if ( strcmp(flow,"B") == 0 || strcmp(flow,"b") == 0 || strcmp(flow,"B ") == 0 || strcmp(flow,"b ") == 0)
        {
         feat[selected_feat].color = pink.pixel ;
         
/*
EXEC SQL UPDATE FEATURES
	          SET    COLOR    = 3
	          WHERE  FEAT_NUM = :feat_num1 ;
*/

{
#line 903 "geoedit.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 903 "geoedit.sqc"
  sqlaaloc(2,1,24,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 903 "geoedit.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 903 "geoedit.sqc"
      sql_setdlist[0].sqldata = (void*)&feat_num1;
#line 903 "geoedit.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 903 "geoedit.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 903 "geoedit.sqc"
  sqlacall((unsigned short)24,18,2,0,0L);
#line 903 "geoedit.sqc"
  sqlastop(0L);
}

#line 903 "geoedit.sqc"

         
/*
EXEC SQL COMMIT WORK ;
*/

{
#line 904 "geoedit.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 904 "geoedit.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 904 "geoedit.sqc"
  sqlastop(0L);
}

#line 904 "geoedit.sqc"

         // CHECKERR ("UPDATE");
        }
    else
     if ( strcmp(flow,"C") == 0 || strcmp(flow,"c") == 0 || strcmp(flow,"C ") == 0 || strcmp(flow,"c ") == 0)
        {
         feat[selected_feat].color = blue.pixel ;
         
/*
EXEC SQL UPDATE FEATURES
	          SET    COLOR    = 1
	          WHERE  FEAT_NUM = :feat_num1 ;
*/

{
#line 913 "geoedit.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 913 "geoedit.sqc"
  sqlaaloc(2,1,25,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 913 "geoedit.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 913 "geoedit.sqc"
      sql_setdlist[0].sqldata = (void*)&feat_num1;
#line 913 "geoedit.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 913 "geoedit.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 913 "geoedit.sqc"
  sqlacall((unsigned short)24,19,2,0,0L);
#line 913 "geoedit.sqc"
  sqlastop(0L);
}

#line 913 "geoedit.sqc"

         
/*
EXEC SQL COMMIT WORK ;
*/

{
#line 914 "geoedit.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 914 "geoedit.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 914 "geoedit.sqc"
  sqlastop(0L);
}

#line 914 "geoedit.sqc"

         // CHECKERR ("UPDATE");
        }
    else
     if ( strcmp(flow,"D") == 0 || strcmp(flow,"d") == 0 || strcmp(flow,"D ") == 0 || strcmp(flow,"d ") == 0)
        {
         feat[selected_feat].color = red.pixel ;
         
/*
EXEC SQL UPDATE FEATURES
	          SET    COLOR    = 2
	          WHERE  FEAT_NUM = :feat_num1 ;
*/

{
#line 923 "geoedit.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 923 "geoedit.sqc"
  sqlaaloc(2,1,26,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 923 "geoedit.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 923 "geoedit.sqc"
      sql_setdlist[0].sqldata = (void*)&feat_num1;
#line 923 "geoedit.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 923 "geoedit.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 923 "geoedit.sqc"
  sqlacall((unsigned short)24,20,2,0,0L);
#line 923 "geoedit.sqc"
  sqlastop(0L);
}

#line 923 "geoedit.sqc"

         
/*
EXEC SQL COMMIT WORK ;
*/

{
#line 924 "geoedit.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 924 "geoedit.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 924 "geoedit.sqc"
  sqlastop(0L);
}

#line 924 "geoedit.sqc"

         // CHECKERR ("UPDATE");

        }

     printf("ARC feat num = %d \n",feat_num1);

     need_draw_all = 1 ;
    }


 draw_feature(selected_feat);
 // normal_cursor();
 draw_fun = EDIT ;
}

/*------------------------------------------------------------------------*/
/*                        editfeaturePicture()                            */
/*------------------------------------------------------------------------*/
void edit_pic(Widget parent)
{
 XmString  xstr      ;
 Arg       args[20]  ;
 int       i , n , j ;
 char      value[50] ;
 int       xWidget   ;
 int       yWidget   ;


 // feat_array_index
 i = selected_feat ;

 feat_num1 = feat[selected_feat].num  ;
 strcpy (feat_code, feat[selected_feat].code) ;



 /*------------------ Creat Form Dialog ---------------------*/
 sprintf (value,"EDIT Picture [ %s :  %d ]",feat_code,feat_num1);
 xstr = XmStringCreate(value,CS);
 n=0;
 XtSetArg(args[n] , XmNdialogTitle ,                       xstr);n++;
 XtSetArg(args[n] , XmNx           ,                          0);n++;
 XtSetArg(args[n] , XmNy           ,                          0);n++;
 XtSetArg(args[n] , XmNbackground  ,                lgray.pixel);n++;
 XtSetArg(args[n] , XmNdialogStyle , XmDIALOG_APPLICATION_MODAL);n++;

 EditForm = XmCreateFormDialog(parent,"EditForm", args,n);


 /*------------------  Create Labels ------------------------*/
 j = 0        ;
 xWidget = 10 ;
 yWidget = 10 ;

 Label[j++]=create_label(EditForm,"Displayed"    ,xWidget,yWidget,100,30,lgray.pixel); yWidget+=30 ;
 Label[j++]=create_label(EditForm,"Scale Ranges" ,xWidget,yWidget,100,30,lgray.pixel); yWidget+=30 ;
 Label[j++]=create_label(EditForm,"Color"        ,xWidget,yWidget,100,30,lgray.pixel); yWidget+=30 ;
 Label[j++]=create_label(EditForm,"Line Type"    ,xWidget,yWidget,100,30,lgray.pixel); yWidget+=30 ;
 Label[j++]=create_label(EditForm,"Line Width"   ,xWidget,yWidget,100,30,lgray.pixel); yWidget+=30 ;

 if  ( feat[i].type == 1 && feat[i].symb_num != 0 )
     {
      Label[j++]=create_label(EditForm,"Symbol Number",xWidget,yWidget,100,30,lgray.pixel); yWidget+=30 ;
      Label[j++]=create_label(EditForm,"Symbol Size"  ,xWidget,yWidget,100,30,lgray.pixel); yWidget+=30 ;
      Label[j++]=create_label(EditForm,"Symbol Angle" ,xWidget,yWidget,100,30,lgray.pixel); yWidget+=30 ;
     }

 if  ( feat[i].has_text[0] == 'Y' )
     {
      Label[j++]=create_label(EditForm,"Text String"  ,xWidget,yWidget,100,30,lgray.pixel); yWidget+=30 ;
      Label[j++]=create_label(EditForm,"Text Font"    ,xWidget,yWidget,100,30,lgray.pixel); yWidget+=30 ;
      Label[j++]=create_label(EditForm,"Text Size"    ,xWidget,yWidget,100,30,lgray.pixel); yWidget+=30 ;
      Label[j++]=create_label(EditForm,"Text Angle"   ,xWidget,yWidget,100,30,lgray.pixel); yWidget+=30 ;
     }


 /*-------------------- Create Fields -----------------------*/
 j = 0         ;
 xWidget = 120 ;
 yWidget = 10  ;

 strcpy  (value,"");
 sprintf (value,"%c",feat[i].displayed[0]);
 Field[j++]=create_tfield(EditForm,value,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;

 strcpy (value,"");
 sprintf (value,"%c%c%c%c%c",feat[i].scale_range[0],feat[i].scale_range[1],feat[i].scale_range[2],feat[i].scale_range[3],feat[i].scale_range[4]);
 Field[j++]=create_tfield(EditForm,value,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;

 strcpy  (value,"");

      if (feat[i].color == blue.pixel  ) strcpy (value,"1" );
 else if (feat[i].color == red.pixel   ) strcpy (value,"2" );
 else if (feat[i].color == pink.pixel  ) strcpy (value,"3" );
 else if (feat[i].color == green.pixel ) strcpy (value,"4" );
 else if (feat[i].color == cyan.pixel  ) strcpy (value,"5" );
 else if (feat[i].color == yellow.pixel) strcpy (value,"6" );
 else if (feat[i].color == white.pixel ) strcpy (value,"7" );
 else if (feat[i].color == black.pixel ) strcpy (value,"8" );
 else if (feat[i].color == gray.pixel  ) strcpy (value,"9" );
 else if (feat[i].color == wheat.pixel ) strcpy (value,"10");
 else if (feat[i].color == brown.pixel ) strcpy (value,"11");
 else if (feat[i].color == orange.pixel) strcpy (value,"12");
 else if (feat[i].color == lgray.pixel ) strcpy (value,"13");

 Field[j++]=create_tfield(EditForm,value,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;

 strcpy  (value,"");
 sprintf (value,"%d",feat[i].linetype);
 Field[j++]=create_tfield(EditForm,value,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;

 strcpy  (value,"");
 sprintf (value,"%d",feat[i].linewidth);
 Field[j++]=create_tfield(EditForm,value,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;

 if  ( feat[i].type == 1 && feat[i].symb_num != 0 )
     {
      strcpy  (value,"");
      sprintf (value,"%d",feat[i].symb_num);
      Field[j++]=create_tfield(EditForm,value,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;

      strcpy  (value,"");
      sprintf (value,"%d",feat[i].symb_size);
      Field[j++]=create_tfield(EditForm,value,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;

      strcpy  (value,"");
      sprintf (value,"%d",feat[i].symb_angle);
      Field[j++]=create_tfield(EditForm,value,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;
     }

 if  ( feat[i].has_text[0] == 'Y' )
     {
      text_index = feat[i].text + 1 ;

      Field[j++]=create_tfield(EditForm,text[text_index].string,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;
               strcpy  (value,"");
               sprintf (value,"%d",text[text_index].font);
      Field[j++]=create_tfield(EditForm,value,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;
               strcpy  (value,"");
               sprintf (value,"%d",text[text_index].size);
      Field[j++]=create_tfield(EditForm,value,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;
               strcpy  (value,"");
               sprintf (value,"%d",(int)text[text_index].angle);
      Field[j++]=create_tfield(EditForm,value,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;
     }


 /*-------------------- Create Buttons ----------------------*/
 yWidget+=10 ;

 Edit_save_button = create_pbutton (EditForm,"SAVE",10,yWidget,80,30,gray.pixel) ;
 XtAddCallback(Edit_save_button,XmNactivateCallback,saveEditPicCB,EditForm);

 Edit_cancel_button = create_pbutton (EditForm,"Cancel",200,yWidget,80,30,gray.pixel) ;
 XtAddCallback(Edit_cancel_button,XmNactivateCallback,cancelEditPicCB,EditForm);


 /*----------- Set Initial Focus & Default Button -----------*/

 XtSetArg(args[0], XmNinitialFocus , Field[0]);
 XtSetValues(EditForm,args,1);

 XtSetArg(args[0], XmNdefaultButton, Edit_save_button);
 XtSetValues(EditForm,args,1);

 /*------------------ Display FormDialog --------------------*/

 XtManageChild(EditForm);

 /*--------------------- Grab Form Dailog -------------------*/

 XtAddGrab(EditForm ,True,False );

}

/*-----------------------------------------------------------------*/
/*                         saveEditPicCB()                         */
/*-----------------------------------------------------------------*/
void saveEditPicCB(Widget w,caddr_t client_data,ANYCBS *call_data)
{
 Arg      args[20]    ;
 char     *str        ;
 char     command[50] ;
 char     value[50]   ;
 int      j           ;


 i = selected_feat ;
 j = 0 ;

 XtSetArg(args[0],XmNvalue,command);
 XtGetValues(Field[0],args,1);


 strcpy (value ,XmTextGetString(Field[j++]));
 sscanf (value ,"%c",&feat[i].displayed[0]);
 displayed[0]=  feat[i].displayed[0] ;


 strcpy (value ,XmTextGetString(Field[j++]));
 feat[i].scale_range[0] = scale_range[0] = value[0] ;
 feat[i].scale_range[1] = scale_range[1] = value[1] ;
 feat[i].scale_range[2] = scale_range[2] = value[2] ;
 feat[i].scale_range[3] = scale_range[3] = value[3] ;
 feat[i].scale_range[4] = scale_range[4] = value[4] ;

 strcpy (value ,XmTextGetString(Field[j++]));
 sscanf (value ,"%d",&feat[i].color);
 feat_color = feat[i].color ;

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
	case 13: feat[i].color = lgray.pixel ;  break;

	default: feat[i].color = blue.pixel  ;  break;
       }


 strcpy (value ,XmTextGetString(Field[j++]));
 sscanf (value ,"%d",&feat[i].linetype);
 feat_linetype = feat[i].linetype ;

 strcpy (value ,XmTextGetString(Field[j++]));
 sscanf (value ,"%d",&feat[i].linewidth);
 feat_linewidth = feat[i].linewidth ;


 if ( feat[i].type == 1 && feat[i].symb_num != 0 )
    {
     strcpy (value ,XmTextGetString(Field[j++]));
     sscanf (value ,"%d",&feat[i].symb_num);
     symb_num = feat[i].symb_num ;

     strcpy (value ,XmTextGetString(Field[j++]));
     sscanf (value ,"%d",&feat[i].symb_size);
     symb_size = feat[i].symb_size ;

     strcpy (value ,XmTextGetString(Field[j++]));
     sscanf (value ,"%d",&feat[i].symb_angle);
     symb_angle = feat[i].symb_angle ;

     if ( db_opened[0] == 'Y' )
        {
         // Update Features Picture Recored
         feat_num1 = feat[selected_feat].num  ;

         
/*
EXEC SQL UPDATE FEATURES
                  SET displayed    = :displayed      ,
	   	      scale_range  = :scale_range    ,
	    	      color        = :feat_color     ,
		      line_type    = :feat_linetype  ,
		      line_width   = :feat_linewidth ,
		      symb_num     = :symb_num       ,
		      symb_size    = :symb_size      ,
		      symb_angle   = :symb_angle
	        WHERE FEAT_NUM     = :feat_num1 ;
*/

{
#line 1192 "geoedit.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1192 "geoedit.sqc"
  sqlaaloc(2,9,27,0L);
    {
      struct sqla_setdata_list sql_setdlist[9];
#line 1192 "geoedit.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 1;
#line 1192 "geoedit.sqc"
      sql_setdlist[0].sqldata = (void*)displayed;
#line 1192 "geoedit.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1192 "geoedit.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 6;
#line 1192 "geoedit.sqc"
      sql_setdlist[1].sqldata = (void*)scale_range;
#line 1192 "geoedit.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1192 "geoedit.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 1192 "geoedit.sqc"
      sql_setdlist[2].sqldata = (void*)&feat_color;
#line 1192 "geoedit.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1192 "geoedit.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 1192 "geoedit.sqc"
      sql_setdlist[3].sqldata = (void*)&feat_linetype;
#line 1192 "geoedit.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1192 "geoedit.sqc"
      sql_setdlist[4].sqltype = 500; sql_setdlist[4].sqllen = 2;
#line 1192 "geoedit.sqc"
      sql_setdlist[4].sqldata = (void*)&feat_linewidth;
#line 1192 "geoedit.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1192 "geoedit.sqc"
      sql_setdlist[5].sqltype = 496; sql_setdlist[5].sqllen = 4;
#line 1192 "geoedit.sqc"
      sql_setdlist[5].sqldata = (void*)&symb_num;
#line 1192 "geoedit.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 1192 "geoedit.sqc"
      sql_setdlist[6].sqltype = 496; sql_setdlist[6].sqllen = 4;
#line 1192 "geoedit.sqc"
      sql_setdlist[6].sqldata = (void*)&symb_size;
#line 1192 "geoedit.sqc"
      sql_setdlist[6].sqlind = 0L;
#line 1192 "geoedit.sqc"
      sql_setdlist[7].sqltype = 496; sql_setdlist[7].sqllen = 4;
#line 1192 "geoedit.sqc"
      sql_setdlist[7].sqldata = (void*)&symb_angle;
#line 1192 "geoedit.sqc"
      sql_setdlist[7].sqlind = 0L;
#line 1192 "geoedit.sqc"
      sql_setdlist[8].sqltype = 496; sql_setdlist[8].sqllen = 4;
#line 1192 "geoedit.sqc"
      sql_setdlist[8].sqldata = (void*)&feat_num1;
#line 1192 "geoedit.sqc"
      sql_setdlist[8].sqlind = 0L;
#line 1192 "geoedit.sqc"
      sqlasetdata(2,0,9,sql_setdlist,0L,0L);
    }
#line 1192 "geoedit.sqc"
  sqlacall((unsigned short)24,21,2,0,0L);
#line 1192 "geoedit.sqc"
  sqlastop(0L);
}

#line 1192 "geoedit.sqc"


         
/*
EXEC SQL COMMIT WORK ;
*/

{
#line 1194 "geoedit.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1194 "geoedit.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 1194 "geoedit.sqc"
  sqlastop(0L);
}

#line 1194 "geoedit.sqc"

         // // CHECKERR ("UPDATE");
        }
    }
 else
    {
    if ( db_opened[0] == 'Y' )
       {
        // Update Features Picture Recored
        feat_num1 = feat[selected_feat].num  ;

        
/*
EXEC SQL UPDATE FEATURES
                 SET displayed    = :displayed      ,
		     scale_range  = :scale_range    ,
		     color        = :feat_color     ,
		     line_type    = :feat_linetype  ,
		     line_width   = :feat_linewidth
	       WHERE FEAT_NUM     = :feat_num1 ;
*/

{
#line 1211 "geoedit.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1211 "geoedit.sqc"
  sqlaaloc(2,6,28,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 1211 "geoedit.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 1;
#line 1211 "geoedit.sqc"
      sql_setdlist[0].sqldata = (void*)displayed;
#line 1211 "geoedit.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1211 "geoedit.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 6;
#line 1211 "geoedit.sqc"
      sql_setdlist[1].sqldata = (void*)scale_range;
#line 1211 "geoedit.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1211 "geoedit.sqc"
      sql_setdlist[2].sqltype = 500; sql_setdlist[2].sqllen = 2;
#line 1211 "geoedit.sqc"
      sql_setdlist[2].sqldata = (void*)&feat_color;
#line 1211 "geoedit.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1211 "geoedit.sqc"
      sql_setdlist[3].sqltype = 500; sql_setdlist[3].sqllen = 2;
#line 1211 "geoedit.sqc"
      sql_setdlist[3].sqldata = (void*)&feat_linetype;
#line 1211 "geoedit.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1211 "geoedit.sqc"
      sql_setdlist[4].sqltype = 500; sql_setdlist[4].sqllen = 2;
#line 1211 "geoedit.sqc"
      sql_setdlist[4].sqldata = (void*)&feat_linewidth;
#line 1211 "geoedit.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1211 "geoedit.sqc"
      sql_setdlist[5].sqltype = 496; sql_setdlist[5].sqllen = 4;
#line 1211 "geoedit.sqc"
      sql_setdlist[5].sqldata = (void*)&feat_num1;
#line 1211 "geoedit.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 1211 "geoedit.sqc"
      sqlasetdata(2,0,6,sql_setdlist,0L,0L);
    }
#line 1211 "geoedit.sqc"
  sqlacall((unsigned short)24,22,2,0,0L);
#line 1211 "geoedit.sqc"
  sqlastop(0L);
}

#line 1211 "geoedit.sqc"


        
/*
EXEC SQL COMMIT WORK ;
*/

{
#line 1213 "geoedit.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1213 "geoedit.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 1213 "geoedit.sqc"
  sqlastop(0L);
}

#line 1213 "geoedit.sqc"

        // // CHECKERR ("UPDATE");
       }
    }


 if  ( feat[i].has_text[0] == 'Y' )
     {
      strcpy (text[text_index].string ,XmTextGetString(Field[j++]));
      strcpy (text_string , text[text_index].string );

      strcpy (value ,XmTextGetString(Field[j++]));
      sscanf (value ,"%d",&text[text_index].font);
      text_font = text[text_index].font ;

      strcpy (value ,XmTextGetString(Field[j++]));
      sscanf (value ,"%d",&text[text_index].size);
      text_size = text[text_index].size ;

      strcpy (value ,XmTextGetString(Field[j++]));
      sscanf (value ,"%f",&text[text_index].angle);
      text_angle = text[text_index].angle ;

      // Update size of Text feature if no symbol
      if ( feat[i].symb_num == 0 )
         {
          feat[i].symb_size = text_size ;
         }


      if ( db_opened[0] == 'Y' )
         {
          // Update Features Picture Recored
          feat_num1 = feat[selected_feat].num  ;

          
/*
EXEC SQL UPDATE TEXT
                   SET string       = :text_string ,
	  	       font         = :text_font   ,
	  	       size         = :text_size   ,
	  	       angle        = :text_angle
	         WHERE FEAT_NUM     = :feat_num1 ;
*/

{
#line 1253 "geoedit.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1253 "geoedit.sqc"
  sqlaaloc(2,5,29,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 1253 "geoedit.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 51;
#line 1253 "geoedit.sqc"
      sql_setdlist[0].sqldata = (void*)text_string;
#line 1253 "geoedit.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1253 "geoedit.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 1253 "geoedit.sqc"
      sql_setdlist[1].sqldata = (void*)&text_font;
#line 1253 "geoedit.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1253 "geoedit.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 1253 "geoedit.sqc"
      sql_setdlist[2].sqldata = (void*)&text_size;
#line 1253 "geoedit.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 1253 "geoedit.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 1253 "geoedit.sqc"
      sql_setdlist[3].sqldata = (void*)&text_angle;
#line 1253 "geoedit.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 1253 "geoedit.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 1253 "geoedit.sqc"
      sql_setdlist[4].sqldata = (void*)&feat_num1;
#line 1253 "geoedit.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 1253 "geoedit.sqc"
      sqlasetdata(2,0,5,sql_setdlist,0L,0L);
    }
#line 1253 "geoedit.sqc"
  sqlacall((unsigned short)24,23,2,0,0L);
#line 1253 "geoedit.sqc"
  sqlastop(0L);
}

#line 1253 "geoedit.sqc"

          
/*
EXEC SQL COMMIT WORK ;
*/

{
#line 1254 "geoedit.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1254 "geoedit.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 1254 "geoedit.sqc"
  sqlastop(0L);
}

#line 1254 "geoedit.sqc"
     // CHECKERR ("UPDATE");

          // Update size of Text feature if no symbol
          if ( feat[i].symb_num == 0 )
             {
              symb_size = text_size ;

              
/*
EXEC SQL UPDATE FEATURES
                       SET symb_size = :symb_size
	             WHERE FEAT_NUM  = :feat_num1 ;
*/

{
#line 1263 "geoedit.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1263 "geoedit.sqc"
  sqlaaloc(2,2,30,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 1263 "geoedit.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 1263 "geoedit.sqc"
      sql_setdlist[0].sqldata = (void*)&symb_size;
#line 1263 "geoedit.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 1263 "geoedit.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 1263 "geoedit.sqc"
      sql_setdlist[1].sqldata = (void*)&feat_num1;
#line 1263 "geoedit.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 1263 "geoedit.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 1263 "geoedit.sqc"
  sqlacall((unsigned short)24,24,2,0,0L);
#line 1263 "geoedit.sqc"
  sqlastop(0L);
}

#line 1263 "geoedit.sqc"

              
/*
EXEC SQL COMMIT WORK ;
*/

{
#line 1264 "geoedit.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 1264 "geoedit.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 1264 "geoedit.sqc"
  sqlastop(0L);
}

#line 1264 "geoedit.sqc"

             }

         }

     }



 draw_feature(selected_feat);
 // normal_cursor();
 draw_fun = EDITPIC ;
}
/*------------------------------------------------------------------------*/
/*                        edit System Parameters()                        */
/*------------------------------------------------------------------------*/
void edit_parm(Widget parent)
{
 XmString  xstr      ;
 Arg       args[20]  ;
 int       i , n , j ;
 char      value[50] ;
 int       xWidget   ;
 int       yWidget   ;


 /*------------------ Creat Form Dialog ---------------------*/

 xstr = XmStringCreate("EDIT System Parameters",CS);
 n=0;
 XtSetArg(args[n] , XmNdialogTitle ,                       xstr);n++;
 XtSetArg(args[n] , XmNx           ,                          0);n++;
 XtSetArg(args[n] , XmNy           ,                          0);n++;
 XtSetArg(args[n] , XmNbackground  ,                lgray.pixel);n++;
 XtSetArg(args[n] , XmNdialogStyle , XmDIALOG_APPLICATION_MODAL);n++;

 EditForm = XmCreateFormDialog(parent,"EditForm", args,n);


 /*------------------  Create Labels ------------------------*/
 j = 0        ;
 xWidget = 10 ;
 yWidget = 10 ;

 Label[j++]=create_label(EditForm,"Scale Range1"       ,xWidget,yWidget,150,30,lgray.pixel); yWidget+=30 ;
 Label[j++]=create_label(EditForm,"Scale Range2"       ,xWidget,yWidget,150,30,lgray.pixel); yWidget+=30 ;
 Label[j++]=create_label(EditForm,"Scale Range3"       ,xWidget,yWidget,150,30,lgray.pixel); yWidget+=30 ;
 Label[j++]=create_label(EditForm,"Scale Range4"       ,xWidget,yWidget,150,30,lgray.pixel); yWidget+=30 ;
 Label[j++]=create_label(EditForm,"Refresh After Draw" ,xWidget,yWidget,150,30,lgray.pixel); yWidget+=30 ;
 Label[j++]=create_label(EditForm,"Symbol Clip Buffer" ,xWidget,yWidget,150,30,lgray.pixel); yWidget+=30 ;
 Label[j++]=create_label(EditForm,"Line Clip Buffer"   ,xWidget,yWidget,150,30,lgray.pixel); yWidget+=30 ;
 Label[j++]=create_label(EditForm,"Queue Name"         ,xWidget,yWidget,150,30,lgray.pixel); yWidget+=30 ;
 Label[j++]=create_label(EditForm,"Import Path"        ,xWidget,yWidget,150,30,lgray.pixel); yWidget+=30 ;
 Label[j++]=create_label(EditForm,"Join Tolerance"     ,xWidget,yWidget,150,30,lgray.pixel); yWidget+=30 ;
 Label[j++]=create_label(EditForm,"DXF Import DBU"     ,xWidget,yWidget,150,30,lgray.pixel); yWidget+=30 ;


 /*-------------------- Create Fields -----------------------*/
 j = 0         ;
 xWidget = 170 ;
 yWidget = 10  ;


 strcpy  (value,"");
 sprintf (value,"%d",SC_RANGE1);
 Field[j++]=create_tfield(EditForm,value,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;

 strcpy  (value,"");
 sprintf (value,"%d",SC_RANGE2);
 Field[j++]=create_tfield(EditForm,value,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;

 strcpy  (value,"");
 sprintf (value,"%d",SC_RANGE3);
 Field[j++]=create_tfield(EditForm,value,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;

 strcpy  (value,"");
 sprintf (value,"%d",SC_RANGE4);
 Field[j++]=create_tfield(EditForm,value,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;

 strcpy  (value,"");
 sprintf (value,"%d",(int)REFRESH);
 Field[j++]=create_tfield(EditForm,value,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;

 strcpy  (value,"");
 sprintf (value,"%d",SYMBCLIPBUFFER);
 Field[j++]=create_tfield(EditForm,value,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;

 strcpy  (value,"");
 sprintf (value,"%d",LINECLIPBUFFER);
 Field[j++]=create_tfield(EditForm,value,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;

 strcpy  (value,queue_name);
 Field[j++]=create_tfield(EditForm,value,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;

 strcpy  (value,IMPORTPATH);
 Field[j++]=create_tfield(EditForm,value,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;

 strcpy  (value,"");
 sprintf (value,"%d",JOIN_TOLERANCE);
 Field[j++]=create_tfield(EditForm,value,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;

 strcpy  (value,"");
 sprintf (value,"%d  (1 MM/2 CM/3 DM/4 M/5 KM)",DXF_DB_UNIT);
 Field[j++]=create_tfield(EditForm,value,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=30 ;

 /*-------------------- Create Buttons ----------------------*/
 yWidget+=10 ;

 Edit_save_button = create_pbutton (EditForm,"SAVE",10,yWidget,80,30,gray.pixel) ;
 XtAddCallback(Edit_save_button,XmNactivateCallback,saveEditParmCB,EditForm);

 Edit_cancel_button = create_pbutton (EditForm,"Cancel",200,yWidget,80,30,gray.pixel) ;
 XtAddCallback(Edit_cancel_button,XmNactivateCallback,cancelEditParmCB,EditForm);


 /*----------- Set Initial Focus & Default Button -----------*/

 XtSetArg(args[0], XmNinitialFocus , Field[0]);
 XtSetValues(EditForm,args,1);

 XtSetArg(args[0], XmNdefaultButton, Edit_save_button);
 XtSetValues(EditForm,args,1);

 /*------------------ Display FormDialog --------------------*/

 XtManageChild(EditForm);

 /*--------------------- Grab Form Dailog -------------------*/

 XtAddGrab(EditForm ,True,False );

}

/*-----------------------------------------------------------------*/
/*                         saveEditParmCB()                        */
/*-----------------------------------------------------------------*/
void saveEditParmCB(Widget w,caddr_t client_data,ANYCBS *call_data)
{
 Arg      args[20]    ;
 char     *str        ;
 char     command[50] ;
 char     value[50]   ;
 int      j, ivalue   ;


 j = 0 ;

 strcpy (value ,XmTextGetString(Field[j++]));
 sscanf (value ,"%d",&SC_RANGE1);

 strcpy (value ,XmTextGetString(Field[j++]));
 sscanf (value ,"%d",&SC_RANGE2);

 strcpy (value ,XmTextGetString(Field[j++]));
 sscanf (value ,"%d",&SC_RANGE3);

 strcpy (value ,XmTextGetString(Field[j++]));
 sscanf (value ,"%d",&SC_RANGE4);


 strcpy (value ,XmTextGetString(Field[j++]));
 sscanf (value ,"%d",&ivalue);
 REFRESH = (float)ivalue ;

 strcpy (value ,XmTextGetString(Field[j++]));
 sscanf (value ,"%d",&SYMBCLIPBUFFER);

 strcpy (value ,XmTextGetString(Field[j++]));
 sscanf (value ,"%d",&LINECLIPBUFFER);

 strcpy (value,XmTextGetString(Field[j++]));
 strcpy (queue_name,value);

 strcpy (value,XmTextGetString(Field[j++]));
 strcpy (IMPORTPATH,value);

 strcpy (value ,XmTextGetString(Field[j++]));
 sscanf (value ,"%d",&JOIN_TOLERANCE);

 strcpy (value ,XmTextGetString(Field[j++]));
 sscanf (value ,"%d",&DXF_DB_UNIT);

 // normal_cursor();
}
/*-----------------------------------------------------------------*/
/*                       cancelEditParmCB()                        */
/*-----------------------------------------------------------------*/
void cancelEditParmCB()
{
 // normal_cursor();
}
/*--------------------------------------------------------------*/
/*                     Creat_label()                            */
/*--------------------------------------------------------------*/

Widget create_label (Widget parent,char *string,int x,int y,int w,int h,int color)
{
 Widget    label    ;
 XmString  xstr     ;
 Arg       args[20] ;
 int       n        ;

 xstr = XmStringCreate(string,CS);
 n=0;
 XtSetArg(args[n] , XmNlabelString ,  xstr);n++;
 XtSetArg(args[n] , XmNx           ,     x);n++;
 XtSetArg(args[n] , XmNy           ,     y);n++;
 XtSetArg(args[n] , XmNwidth       ,     w);n++;
 XtSetArg(args[n] , XmNheight      ,     h);n++;
 XtSetArg(args[n] , XmNbackground  , color);n++;

 label = XmCreateLabel(parent,"Label",args,n);
 XtManageChild(label);

 return (label);
}

/*--------------------------------------------------------------*/
/*                     Creat_tfield()                           */
/*--------------------------------------------------------------*/
Widget create_tfield (Widget parent,char *string,int x,int y,int w,int h,int fcolor,int bcolor)
{
 Widget    field     ;
 Arg       args[20]  ;
 int       n         ;

 n=0;
 XtSetArg(args[n] , XmNx           ,      x);n++;
 XtSetArg(args[n] , XmNy           ,      y);n++;
 XtSetArg(args[n] , XmNwidth       ,      w);n++;
 XtSetArg(args[n] , XmNheight      ,      h);n++;
 XtSetArg(args[n] , XmNvalue       , string);n++;
 XtSetArg(args[n] , XmNforeground  , fcolor);n++;
 XtSetArg(args[n] , XmNbackground  , bcolor);n++;

 field = XmCreateTextField(parent,"Field",args,n);
 XtManageChild(field);

 return (field);
}
/*--------------------------------------------------------------*/
/*                     Creat_pbutton()                          */
/*--------------------------------------------------------------*/
Widget create_pbutton (Widget parent,char *string,int x,int y,int w,int h,int bcolor)
{
 Widget    button   ;
 XmString  xstr     ;
 Arg       args[20] ;
 int       n        ;

 xstr = XmStringCreate(string,CS);
 n=0;
 XtSetArg(args[n] , XmNlabelString ,   xstr);n++;
 XtSetArg(args[n] , XmNx           ,      x);n++;
 XtSetArg(args[n] , XmNy           ,      y);n++;
 XtSetArg(args[n] , XmNwidth       ,      w);n++;
 XtSetArg(args[n] , XmNheight      ,      h);n++;
 XtSetArg(args[n] , XmNbackground  , bcolor);n++;

 button = XmCreatePushButton(parent,"Button",args,n);
 XtManageChild(button);

 return (button);
}
