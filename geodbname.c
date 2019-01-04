/*------------------------------------------------------------------------*/
/*                geoINFO/6000  Get DBname  ( geodbname.c )               */
/*------------------------------------------------------------------------*/

/*------------------------------------------------------------------------*/
/*                          geoINFO Include Files                         */
/*------------------------------------------------------------------------*/
#include "include/geoIMSextern.h"

/*------------------------------------------------------------------------*/
/*                           Functions Prototypes                         */
/*------------------------------------------------------------------------*/
void cancel_dbCB()     ;
void ok_dbCB()         ;

Widget create_label()  ;
Widget create_pbutton();
Widget create_tfield() ;

/*------------------------------------------------------------------------*/
/*                           Widget Definition                            */
/*------------------------------------------------------------------------*/
Widget  db_Dialog         ;
Widget  db_ok_button      ;
Widget  db_cancel_button  ;
Widget  Label[10]         ;
Widget  Field[10]         ;

/*------------------------------------------------------------------------*/
/*                   Global Variable Definition                           */
/*------------------------------------------------------------------------*/
char    retrieval_type [] ;


/*------------------------------------------------------------------------*/
/*                           get_db_name()                                */
/*------------------------------------------------------------------------*/
void get_db_name(Widget parent)
{
 XmString  xstr      ;
 Arg       args[10]  ;
 char      value[50] ;
 short     n         ;
 int       xWidget   ;
 int       yWidget   ;


 strcpy (retrieval_type,STR_PARM) ;


 if ( strcmp (retrieval_type,"ALL") == 0 || strcmp (retrieval_type,"CON") == 0 )
    {
     /*------------------ BulletnboardDialog ---------------------*/
     if (strcmp (retrieval_type,"ALL") == 0 )
        {
         xstr = XmStringCreate("DataBase Retrieve ALL",CS);
        }
     else
        {
         xstr = XmStringCreate("Connect to DataBase",CS);
        }

     n=0;
     XtSetArg(args[n] , XmNdialogTitle ,        xstr);n++;
     XtSetArg(args[n] , XmNx           ,           0);n++;
     XtSetArg(args[n] , XmNy           ,           0);n++;
     // XtSetArg(args[n] , XmNwidth       ,         400);n++;
     // XtSetArg(args[n] , XmNheight      ,         200);n++;
     XtSetArg(args[n] , XmNbackground  , lgray.pixel);n++;

     // db_Dialog = XmCreateBulletinBoardDialog(parent,"Dailog", args,n);
     db_Dialog = XmCreateFormDialog(parent,"Dailog", args,n);

     /*------------------  Create Labels ------------------------*/
     xWidget = 10 ;
     yWidget = 20 ;

     Label[0]=create_label(db_Dialog,"DataBase Name",xWidget,yWidget,100,30,lgray.pixel); yWidget+=40;
     Label[1]=create_label(db_Dialog,"Password"     ,xWidget,yWidget,100,30,lgray.pixel); yWidget+=40;

     /*-------------------- Create Fields -----------------------*/
     xWidget = 120 ;
     yWidget = 20  ;

     Field[0]=create_tfield(db_Dialog,DB_name ,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=40 ;
     Field[1]=create_tfield(db_Dialog,""      ,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=40 ;

     /*-------------------- Create Buttons ----------------------*/
     db_ok_button = create_pbutton (db_Dialog,"OK",10,yWidget,80,30,gray.pixel) ;
     XtAddCallback(db_ok_button,XmNactivateCallback,ok_dbCB,db_Dialog);

     db_cancel_button = create_pbutton (db_Dialog,"Cancel",230,yWidget,80,30,gray.pixel) ;
     XtAddCallback(db_cancel_button,XmNactivateCallback,cancel_dbCB,db_Dialog);

     /*----------- Set Initial Focus & Default Button -----------*/
     XtSetArg(args[0], XmNinitialFocus , Field[0]);
     XtSetValues(db_Dialog,args,1);

     XtSetArg(args[0], XmNdefaultButton, db_ok_button);
     XtSetValues(db_Dialog,args,1);

     /*------------------- Display Form Dailog ------------------*/
     XtManageChild(db_Dialog);

     /*--------------------- Grab Form Dailog -------------------*/
     XtRealizeWidget(db_Dialog);
     XtAddGrab(db_Dialog ,True,False );
    }
else
 if ( strcmp (retrieval_type,"AR") == 0 )
    {
     /*------------------ BulletnboardDialog ---------------------*/
     xstr = XmStringCreate("DataBase Area Retrieval",CS);
     n=0;
     XtSetArg(args[n] , XmNdialogTitle ,        xstr);n++;
     XtSetArg(args[n] , XmNx           ,           0);n++;
     XtSetArg(args[n] , XmNy           ,           0);n++;
     XtSetArg(args[n] , XmNbackground  , lgray.pixel);n++;

     db_Dialog = XmCreateFormDialog(parent,"Dailog", args,n);

     /*------------------  Create Labels ------------------------*/
     xWidget = 10 ;
     yWidget = 20 ;

     Label[0]=create_label(db_Dialog,"DataBase Name",xWidget,yWidget,100,30,lgray.pixel); yWidget+=40;
     Label[1]=create_label(db_Dialog,"Password"     ,xWidget,yWidget,100,30,lgray.pixel); yWidget+=40;
     Label[2]=create_label(db_Dialog,"X min"        ,xWidget,yWidget,100,30,lgray.pixel); yWidget+=40;
     Label[3]=create_label(db_Dialog,"Y min"        ,xWidget,yWidget,100,30,lgray.pixel); yWidget+=40;
     Label[4]=create_label(db_Dialog,"X max"        ,xWidget,yWidget,100,30,lgray.pixel); yWidget+=40;
     Label[5]=create_label(db_Dialog,"Y max"        ,xWidget,yWidget,100,30,lgray.pixel); yWidget+=40;

     /*-------------------- Create Fields -----------------------*/
     xWidget = 120 ;
     yWidget = 20  ;

     Field[0]=create_tfield(db_Dialog,DB_name ,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=40 ;
     Field[1]=create_tfield(db_Dialog,""      ,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=40 ;
              strcpy  (value,"");
              sprintf (value,"%d",AREA_XMIN);
     Field[2]=create_tfield(db_Dialog,value   ,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=40;
              strcpy  (value,"");
              sprintf (value,"%d",AREA_YMIN);
     Field[3]=create_tfield(db_Dialog,value   ,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=40 ;
              strcpy  (value,"");
              sprintf (value,"%d",AREA_XMAX);
     Field[4]=create_tfield(db_Dialog,value   ,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=40;
              strcpy  (value,"");
              sprintf (value,"%d",AREA_YMAX);
     Field[5]=create_tfield(db_Dialog,value   ,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=40 ;

     /*-------------------- Create Buttons ----------------------*/
     db_ok_button = create_pbutton (db_Dialog,"OK",10,yWidget,80,30,gray.pixel) ;
     XtAddCallback(db_ok_button,XmNactivateCallback,ok_dbCB,db_Dialog);

     db_cancel_button = create_pbutton (db_Dialog,"Cancel",230,yWidget,80,30,gray.pixel) ;
     XtAddCallback(db_cancel_button,XmNactivateCallback,cancel_dbCB,db_Dialog);

     /*----------- Set Initial Focus & Default Button -----------*/
     XtSetArg(args[0], XmNinitialFocus , Field[0]);
     XtSetValues(db_Dialog,args,1);

     XtSetArg(args[0], XmNdefaultButton, db_ok_button);
     XtSetValues(db_Dialog,args,1);

     /*------------------- Display Form Dailog ------------------*/
     XtManageChild(db_Dialog);

     /*--------------------- Grab Form Dailog -------------------*/
     XtRealizeWidget(db_Dialog);
     XtAddGrab(db_Dialog ,True,False );
    }
else
 if ( strcmp (retrieval_type,"NR") == 0 )
    {
     /*------------------ BulletnboardDialog ---------------------*/
     xstr = XmStringCreate("DataBase Network Retrieval",CS);
     n=0;
     XtSetArg(args[n] , XmNdialogTitle ,        xstr);n++;
     XtSetArg(args[n] , XmNx           ,           0);n++;
     XtSetArg(args[n] , XmNy           ,           0);n++;
     XtSetArg(args[n] , XmNbackground  , lgray.pixel);n++;

     db_Dialog = XmCreateFormDialog(parent,"Dailog", args,n);

     /*------------------  Create Labels ------------------------*/
     xWidget = 10 ;
     yWidget = 20 ;

     Label[0]=create_label(db_Dialog,"DataBase Name" ,xWidget,yWidget,100,30,lgray.pixel); yWidget+=40;
     Label[1]=create_label(db_Dialog,"Password"      ,xWidget,yWidget,100,30,lgray.pixel); yWidget+=40;
     Label[2]=create_label(db_Dialog,"Grid Name"     ,xWidget,yWidget,100,30,lgray.pixel); yWidget+=40;
     Label[3]=create_label(db_Dialog,"Feeder Name(s)",xWidget,yWidget,100,30,lgray.pixel); yWidget+=40;

     /*-------------------- Create Fields -----------------------*/
     xWidget = 120 ;
     yWidget = 20  ;

     Field[0]=create_tfield(db_Dialog,DB_name   ,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=40;
     Field[1]=create_tfield(db_Dialog,""        ,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=40;
     Field[2]=create_tfield(db_Dialog,GRID_NAME ,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=40;
     Field[3]=create_tfield(db_Dialog,"ALL"     ,xWidget,yWidget,150,30,black.pixel,white.pixel); yWidget+=40;

     /*-------------------- Create Buttons ----------------------*/
     db_ok_button = create_pbutton (db_Dialog,"OK",10,yWidget,80,30,gray.pixel) ;
     XtAddCallback(db_ok_button,XmNactivateCallback,ok_dbCB,db_Dialog);

     db_cancel_button = create_pbutton (db_Dialog,"Cancel",230,yWidget,80,30,gray.pixel) ;
     XtAddCallback(db_cancel_button,XmNactivateCallback,cancel_dbCB,db_Dialog);

     /*----------- Set Initial Focus & Default Button -----------*/
     XtSetArg(args[0], XmNinitialFocus , Field[0]);
     XtSetValues(db_Dialog,args,1);

     XtSetArg(args[0], XmNdefaultButton, db_ok_button);
     XtSetValues(db_Dialog,args,1);

     /*------------------- Display Form Dailog ------------------*/
     XtManageChild(db_Dialog);

     /*--------------------- Grab Form Dailog -------------------*/
     XtRealizeWidget(db_Dialog);
     XtAddGrab(db_Dialog ,True,False );
    }


} /* main Function */

/*------------------------CALL BACKS ------------------------------*/
/*------------------------CALL BACKS ------------------------------*/
/*------------------------CALL BACKS ------------------------------*/
/*------------------------CALL BACKS ------------------------------*/


/*--------------------------------------------------------------*/
/*                        cancel_dbCB()                         */
/*--------------------------------------------------------------*/
void cancel_dbCB()
{

 xstr = XmStringCreate(" INFO : Function Canceled",CS);
 XtSetArg(args[0], XmNlabelString, xstr);
 XtSetValues(output_label, args, 1);
 // normal_cursor();
 return ;

}
/*--------------------------------------------------------------*/
/*                          ok_dbCB()                           */
/*--------------------------------------------------------------*/
void ok_dbCB(Widget w,caddr_t client_data,ANYCBS *call_data)
{
 char  value [50]  ;


 if ( strcmp (retrieval_type,"ALL") == 0 )
    {
     strcpy (DB_name    , XmTextGetString(Field[0]));
     strcpy (DB_password, XmTextGetString(Field[1]));

     XSync(XtDisplay(w), True);
     XtUnmanageChild(db_Dialog);
     XSync(XtDisplay(w), False);

     retrieve_all() ;
     return ;
    }
else
 if ( strcmp (retrieval_type,"AR") == 0 )
    {
     strcpy (DB_name    , XmTextGetString(Field[0]));
     strcpy (DB_password, XmTextGetString(Field[1]));
     strcpy (value      , XmTextGetString(Field[2]));  sscanf (value,"%d", &AREA_XMIN);
     strcpy (value      , XmTextGetString(Field[3]));  sscanf (value,"%d", &AREA_YMIN);
     strcpy (value      , XmTextGetString(Field[4]));  sscanf (value,"%d", &AREA_XMAX);
     strcpy (value      , XmTextGetString(Field[5]));  sscanf (value,"%d", &AREA_YMAX);

     XSync(XtDisplay(w), True);
     XtUnmanageChild(db_Dialog);
     XSync(XtDisplay(w), False);

     area_retrieval() ;
     return ;
    }
else
 if ( strcmp (retrieval_type,"NR") == 0 )
    {
     strcpy (DB_name    , XmTextGetString(Field[0]));
     strcpy (DB_password, XmTextGetString(Field[1]));

     strcpy (GRID_NAME  , XmTextGetString(Field[2]));
     strcpy (FEEDER_NAME, XmTextGetString(Field[3]));

     XSync(XtDisplay(w), True);
     XtUnmanageChild(db_Dialog);
     XSync(XtDisplay(w), False);

     network_retrieval() ;
     return ;
    }
else
 if ( strcmp (retrieval_type,"CON") == 0 )
    {
     strcpy (DB_name    , XmTextGetString(Field[0]));
     strcpy (DB_password, XmTextGetString(Field[1]));

     XSync(XtDisplay(w), True);
     XtUnmanageChild(db_Dialog);
     XSync(XtDisplay(w), False);

     saveOkCB() ;
     return ;
    }





}
