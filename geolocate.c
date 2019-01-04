/*------------------------------------------------------------------------*/
/*                geoINFO/6000  Locate Point ( geolocate.c )              */
/*------------------------------------------------------------------------*/

/*------------------------------------------------------------------------*/
/*                          geoINFO Include Files                         */
/*------------------------------------------------------------------------*/
#include "include/geoIMSextern.h"

/*------------------------------------------------------------------------*/
/*                           Functions Prototypes                         */
/*------------------------------------------------------------------------*/
void cancelLocateCB();
void okLocateCB();

/*------------------------------------------------------------------------*/
/*                           Widget Definition                            */
/*------------------------------------------------------------------------*/
Widget  LocateShell          ;
Widget  LocateForm           ;
Widget  Locate_ok_button     ;
Widget  Locate_cancel_button ;
Widget  Label[10]            ;
Widget  Field[10]            ;

/*------------------------------------------------------------------------*/
/*                   Global Variable Definition                           */
/*------------------------------------------------------------------------*/
XtAppContext  Locate_context     ;
Display       *LocateDisplay     ;
XEvent        LocateEvent        ;

short         locate_done = 0    ;

/*------------------------------------------------------------------------*/
/*                           locate_point()                               */
/*------------------------------------------------------------------------*/

void locate_point()
{
 int       argc = 0 ;   // RedHat 6.2 use 1 & Mandrek 8 use 0
 char      **argv   ;
 short     n        ;
 XmString  xstr     ;
 Arg       args[10] ;


 return_code = 0      ;   /* 0 normal, 1 cancel, 2 error */


 /*------ Make sure XtToolkitInitialize is only called once -----------*/
 if (ToolkitInitialized == 0)
    {
     XtToolkitInitialize() ;
     ToolkitInitialized = 1;
    }

 /*------ create the application context ------------------------------*/
 Locate_context = XtCreateApplicationContext();


 /*---------------------  Open Display --------------------------------*/

 LocateDisplay = XtOpenDisplay(Locate_context,NULL,NULL,"LocateShell",NULL,0,&argc,argv);

 if (LocateDisplay == NULL)
    {
     fprintf(stderr,"Locate : Can not open display\n");
     return ;
    }

 /*-------------------  Application Shell --------------------*/
 n = 0;
 XtSetArg(args[n] , XmNwidth       ,         400);n++;
 XtSetArg(args[n] , XmNheight      ,         200);n++;

 LocateShell=XtAppCreateShell(NULL,"LocateShell",applicationShellWidgetClass,LocateDisplay,args,n);

 /*----------------------- Form ------------------------------*/
 xstr = XmStringCreate("Locate Point",CS);
 n=0;
 XtSetArg(args[n] , XmNdialogTitle ,        xstr);n++;
 XtSetArg(args[n] , XmNx           ,           0);n++;
 XtSetArg(args[n] , XmNy           ,           0);n++;
 XtSetArg(args[n] , XmNwidth       ,         400);n++;
 XtSetArg(args[n] , XmNheight      ,         200);n++;
 XtSetArg(args[n] , XmNbackground  , lgray.pixel);n++;

 LocateForm = XmCreateForm(LocateShell,"LocateForm",args,n);
 XtManageChild(LocateForm);

 /*---------------------- OK button --------------------------*/
 xstr = XmStringCreate("OK",CS);
 n=0;
 XtSetArg(args[n] , XmNlabelString ,       xstr);n++;
 XtSetArg(args[n] , XmNx           ,         70);n++;
 XtSetArg(args[n] , XmNy           ,        150);n++;
 XtSetArg(args[n] , XmNwidth       ,         80);n++;
 XtSetArg(args[n] , XmNheight      ,         30);n++;
 XtSetArg(args[n] , XmNbackground  , gray.pixel);n++;

 Locate_ok_button = XmCreatePushButton(LocateForm,"Button",args,n);
 XtAddCallback(Locate_ok_button,XmNactivateCallback,okLocateCB,LocateForm);
 XtManageChild(Locate_ok_button);

 /*---------------------- Cancel button ----------------------*/
 xstr = XmStringCreate("Cancel",CS);
 n=0;
 XtSetArg(args[n] , XmNlabelString ,       xstr);n++;
 XtSetArg(args[n] , XmNx           ,        230);n++;
 XtSetArg(args[n] , XmNy           ,        150);n++;
 XtSetArg(args[n] , XmNwidth       ,         80);n++;
 XtSetArg(args[n] , XmNheight      ,         30);n++;
 XtSetArg(args[n] , XmNbackground  , gray.pixel);n++;

 Locate_cancel_button = XmCreatePushButton(LocateForm,"Button",args,n);
 XtAddCallback(Locate_cancel_button,XmNactivateCallback,cancelLocateCB,LocateForm);
 XtManageChild(Locate_cancel_button);

 /*---------------------- Label[0]     ----------------------*/
 xstr = XmStringCreate("X Coordinate",CS);
 n=0;
 XtSetArg(args[n] , XmNlabelString ,        xstr);n++;
 XtSetArg(args[n] , XmNx           ,          10);n++;
 XtSetArg(args[n] , XmNy           ,          30);n++;
 XtSetArg(args[n] , XmNwidth       ,         100);n++;
 XtSetArg(args[n] , XmNheight      ,          30);n++;
 XtSetArg(args[n] , XmNbackground  , lgray.pixel);n++;

 Label[0] = XmCreateLabel(LocateForm,"Label0",args,n);
 XtManageChild(Label[0]);

 /*---------------------- Field[0]     ----------------------*/
 n=0;
 XtSetArg(args[n] , XmNx           ,         120);n++;
 XtSetArg(args[n] , XmNy           ,          30);n++;
 XtSetArg(args[n] , XmNwidth       ,         150);n++;
 XtSetArg(args[n] , XmNheight      ,          30);n++;
 XtSetArg(args[n] , XmNvalue       ,          "");n++;
 XtSetArg(args[n] , XmNforeground  , black.pixel);n++;
 XtSetArg(args[n] , XmNbackground  , white.pixel);n++;

 Field[0] = XmCreateTextField(LocateForm,"Field0",args,n);
 XtManageChild(Field[0]);

 /*---------------------- Label[1]     ----------------------*/
 xstr = XmStringCreate("Y Coordinate",CS);
 n=0;
 XtSetArg(args[n] , XmNlabelString ,        xstr);n++;
 XtSetArg(args[n] , XmNx           ,          10);n++;
 XtSetArg(args[n] , XmNy           ,          80);n++;
 XtSetArg(args[n] , XmNwidth       ,         100);n++;
 XtSetArg(args[n] , XmNheight      ,          30);n++;
 XtSetArg(args[n] , XmNbackground  , lgray.pixel);n++;

 Label[1] = XmCreateLabel(LocateForm,"Label1",args,n);
 XtManageChild(Label[1]);

 /*---------------------- Field[1]     ----------------------*/
 n=0;
 XtSetArg(args[n] , XmNx           ,         120);n++;
 XtSetArg(args[n] , XmNy           ,          80);n++;
 XtSetArg(args[n] , XmNwidth       ,         150);n++;
 XtSetArg(args[n] , XmNheight      ,          30);n++;
 XtSetArg(args[n] , XmNvalue       ,          "");n++;
 XtSetArg(args[n] , XmNforeground  , black.pixel);n++;
 XtSetArg(args[n] , XmNbackground  , white.pixel);n++;

 Field[1] = XmCreateTextField(LocateForm,"Field1",args,n);
 XtManageChild(Field[1]);


 /*--------- Set Initial Focus & Default Button ---------------*/

 XtSetArg(args[0], XmNinitialFocus, Field[0]);
 XtSetValues(LocateForm,args,1);

 XtSetArg(args[0], XmNdefaultButton, Locate_ok_button);
 XtSetValues(LocateForm,args,1);


 /*------------------- Display the Interface ------------------*/

  XtRealizeWidget(LocateShell);


 /*--------- Check if any Events Pending ..        ------------*/
 /*--------- this will force display of the dialog ------------*/

  while (XtAppPending(Locate_context))
	{
	 XtAppNextEvent(Locate_context, &LocateEvent);
	 XtDispatchEvent(&LocateEvent);
	}

  locate_done = 0 ;


  /*----------- running from the regular event loop -----------*/
  /*----- until close button callback sets locate_done = 1 ----*/

  while (locate_done == 0)
	{
	 XtAppNextEvent(Locate_context, &LocateEvent);
	 XtDispatchEvent( &LocateEvent);
	}
  XtUnrealizeWidget(LocateShell);
  XtDestroyWidget(LocateShell);
  XSync(LocateDisplay, False);

}

/*------------------------CALL BACKS ------------------------------*/
/*------------------------CALL BACKS ------------------------------*/
/*------------------------CALL BACKS ------------------------------*/
/*------------------------CALL BACKS ------------------------------*/


/*-----------------------------------------------------------------*/
/*                        cancelLocateCB()                         */
/*-----------------------------------------------------------------*/

void cancelLocateCB()
{
 return_code = 1 ;   /* function canceled */
 locate_done = 1 ;
}


/*-----------------------------------------------------------------*/
/*                          okLocateCB()                           */
/*-----------------------------------------------------------------*/

void okLocateCB(Widget w,caddr_t client_data,ANYCBS *call_data)
{
 long  x = 0     ;
 long  y = 0     ;
 char  value[50] ;
 short rc1 = 0   ;
 short rc2 = 0   ;

 strcpy (value , XmTextGetString(Field[0]));
 rc1 = sscanf (value , "%d",&x);

 strcpy (value , XmTextGetString(Field[1]));
 rc2 = sscanf (value , "%d",&y);

 if ( rc1 == 1 && rc2 == 1 )
    {
     x_diff = x_max - x_min ;
     y_diff = y_max - y_min ;

     x_min = x - ( x_diff / 2 ) ;
     y_min = y - ( y_diff / 2 ) ;
     x_max = x + ( x_diff / 2 ) ;
     y_max = y + ( y_diff / 2 ) ;

     x_screen = (x - x_min) / ONE_PIXEL ;
     y_screen = (y_max - y) / ONE_PIXEL ;

     draw_all();
     draw_pix_symb(25,x_screen,y_screen,cyan.pixel,(float)(12*ONE_PIXEL),0);

     // normal_cursor();
     display_scale();

     locate_done = 1 ;
    }
 else
    {
     xstr = XmStringCreate(" ERROR : No values entered for X,Y",CS);
     XtSetArg(args[0], XmNlabelString, xstr);
     XtSetValues(output_label, args, 1);

     locate_done = 1 ;
    }

}
