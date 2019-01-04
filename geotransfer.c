/*------------------------------------------------------------------------*/
/*                geoINFO/6000  Map Transfer ( geotransfer.c )            */
/*------------------------------------------------------------------------*/

/*------------------------------------------------------------------------*/
/*                          geoINFO Include Files                         */
/*------------------------------------------------------------------------*/
#include "include/geoIMSextern.h"

/*------------------------------------------------------------------------*/
/*                           Functions Prototypes                         */
/*------------------------------------------------------------------------*/
void cancelTransferCB();
void okTransferCB();

/*------------------------------------------------------------------------*/
/*                           Widget Definition                            */
/*------------------------------------------------------------------------*/
Widget  TransferShell          ;
Widget  TransferForm           ;
Widget  Transfer_ok_button     ;
Widget  Transfer_cancel_button ;
Widget  Label[5]               ;
Widget  Field[5]               ;

/*------------------------------------------------------------------------*/
/*                   Global Variable Definition                           */
/*------------------------------------------------------------------------*/
XtAppContext  Transfer_context   ;
Display       *TransferDisplay   ;
XEvent        TransferEvent      ;

short         transfer_done = 0  ;


/*------------------------------------------------------------------------*/
/*                           map_transfer()                               */
/*------------------------------------------------------------------------*/

void map_transfer()
{
 int       argc = 0 ;   // Mandrek 8 use 0 & Redhat 6.2 use 1
 char      **argv   ;
 short     n        ;
 XmString  xstr     ;
 Arg       args[10] ;


 return_code = 0    ;   /* 0 normal, 1 cancel, 2 error */


 /*------ Make sure XtToolkitInitialize is only called once -----------*/
 if (ToolkitInitialized == 0)
    {
     XtToolkitInitialize()  ;
     ToolkitInitialized = 1 ;
    }

 /*------ create the application context ------------------------------*/
 Transfer_context = XtCreateApplicationContext();


 /*---------------------  Open Display --------------------------------*/
 TransferDisplay = XtOpenDisplay(Transfer_context,NULL,NULL,"TransferShell",NULL,0,&argc,argv);

 if (TransferDisplay == NULL)
    {
     fprintf(stderr,"Transfer : Can not open display\n");
     return ;
    }

 /*-------------------  Application Shell --------------------*/
 n = 0;
 XtSetArg(args[n] , XmNwidth       ,         400);n++;
 XtSetArg(args[n] , XmNheight      ,         200);n++;

 TransferShell=XtAppCreateShell(NULL,"TransferShell",applicationShellWidgetClass,TransferDisplay,args,n);

 /*----------------------- Form ------------------------------*/
 xstr = XmStringCreate("Map Transfer",CS);
 n=0;
 XtSetArg(args[n] , XmNdialogTitle ,        xstr);n++;
 XtSetArg(args[n] , XmNx           ,           0);n++;
 XtSetArg(args[n] , XmNy           ,           0);n++;
 XtSetArg(args[n] , XmNwidth       ,         400);n++;
 XtSetArg(args[n] , XmNheight      ,         200);n++;
 XtSetArg(args[n] , XmNbackground  , lgray.pixel);n++;

 TransferForm = XmCreateForm(TransferShell,"TransferForm", args,n);
 XtManageChild(TransferForm);

 /*---------------------- OK button --------------------------*/
 xstr = XmStringCreate("OK",CS);
 n=0;
 XtSetArg(args[n] , XmNlabelString ,       xstr);n++;
 XtSetArg(args[n] , XmNx           ,         70);n++;
 XtSetArg(args[n] , XmNy           ,        150);n++;
 XtSetArg(args[n] , XmNwidth       ,         80);n++;
 XtSetArg(args[n] , XmNheight      ,         30);n++;
 XtSetArg(args[n] , XmNbackground  , gray.pixel);n++;

 Transfer_ok_button = XmCreatePushButton(TransferForm,"Button",args,n);
 /*
 XtAddCallback(Transfer_ok_button,XmNactivateCallback,okTransferCB,TransferForm);
 */
 XtAddCallback(Transfer_ok_button,XmNactivateCallback,okTransferCB,NULL);
 XtManageChild(Transfer_ok_button);

 /*---------------------- Cancel button ----------------------*/
 xstr = XmStringCreate("Cancel",CS);
 n=0;
 XtSetArg(args[n] , XmNlabelString ,       xstr);n++;
 XtSetArg(args[n] , XmNx           ,        230);n++;
 XtSetArg(args[n] , XmNy           ,        150);n++;
 XtSetArg(args[n] , XmNwidth       ,         80);n++;
 XtSetArg(args[n] , XmNheight      ,         30);n++;
 XtSetArg(args[n] , XmNbackground  , gray.pixel);n++;

 Transfer_cancel_button = XmCreatePushButton(TransferForm,"Button",args,n);
 XtAddCallback(Transfer_cancel_button,XmNactivateCallback,cancelTransferCB,TransferForm);
 XtManageChild(Transfer_cancel_button);

 /*---------------------- Label[0]     ----------------------*/
 xstr = XmStringCreate("Shift in X direction",CS);
 n=0;
 XtSetArg(args[n] , XmNlabelString ,        xstr);n++;
 XtSetArg(args[n] , XmNx           ,          10);n++;
 XtSetArg(args[n] , XmNy           ,          30);n++;
 XtSetArg(args[n] , XmNwidth       ,         140);n++;
 XtSetArg(args[n] , XmNheight      ,          30);n++;
 XtSetArg(args[n] , XmNbackground  , lgray.pixel);n++;

 Label[0] = XmCreateLabel(TransferForm,"Label0",args,n);
 XtManageChild(Label[0]);

 /*---------------------- Field[0]     ----------------------*/
 n=0;
 XtSetArg(args[n] , XmNx           ,         160);n++;
 XtSetArg(args[n] , XmNy           ,          30);n++;
 XtSetArg(args[n] , XmNwidth       ,         150);n++;
 XtSetArg(args[n] , XmNheight      ,          30);n++;
 XtSetArg(args[n] , XmNvalue       ,          "");n++;
 XtSetArg(args[n] , XmNforeground  , black.pixel);n++;
 XtSetArg(args[n] , XmNbackground  , white.pixel);n++;

 Field[0] = XmCreateTextField(TransferForm,"Field0",args,n);
 XtManageChild(Field[0]);

 /*---------------------- Label[1]     ----------------------*/
 xstr = XmStringCreate("Shift in Y direction",CS);
 n=0;
 XtSetArg(args[n] , XmNlabelString ,        xstr);n++;
 XtSetArg(args[n] , XmNx           ,          10);n++;
 XtSetArg(args[n] , XmNy           ,          80);n++;
 XtSetArg(args[n] , XmNwidth       ,         140);n++;
 XtSetArg(args[n] , XmNheight      ,          30);n++;
 XtSetArg(args[n] , XmNbackground  , lgray.pixel);n++;

 Label[1] = XmCreateLabel(TransferForm,"Label1",args,n);
 XtManageChild(Label[1]);

 /*---------------------- Field[1]     ----------------------*/
 n=0;
 XtSetArg(args[n] , XmNx           ,         160);n++;
 XtSetArg(args[n] , XmNy           ,          80);n++;
 XtSetArg(args[n] , XmNwidth       ,         150);n++;
 XtSetArg(args[n] , XmNheight      ,          30);n++;
 XtSetArg(args[n] , XmNvalue       ,          "");n++;
 XtSetArg(args[n] , XmNforeground  , black.pixel);n++;
 XtSetArg(args[n] , XmNbackground  , white.pixel);n++;

 Field[1] = XmCreateTextField(TransferForm,"Field1",args,n);
 XtManageChild(Field[1]);


 /*--------- Set Initial Focus & Default Button ---------------*/

 XtSetArg(args[0], XmNinitialFocus, Field[0]);
 XtSetValues(TransferForm,args,1);

 XtSetArg(args[0], XmNdefaultButton, Transfer_ok_button);
 XtSetValues(TransferForm,args,1);


 /*------------------- Display the Interface ------------------*/

  XtRealizeWidget(TransferShell);


 /*--------- Check if any Events Pending ..        ------------*/
 /*--------- this will force display of the dialog ------------*/

  while (XtAppPending(Transfer_context))
	{
	 XtAppNextEvent(Transfer_context, &TransferEvent);
	 XtDispatchEvent(&TransferEvent);
	}

  transfer_done = 0 ;


  /*----------- running from the regular event loop -----------*/
  /*---- until close button callback sets transfer_done = 1 ---*/

  while (transfer_done == 0)
	{
	 XtAppNextEvent(Transfer_context, &TransferEvent);
	 XtDispatchEvent( &TransferEvent);
	}
  XtUnrealizeWidget(TransferShell);
  XtDestroyWidget(TransferShell);
  XSync(TransferDisplay, False);

}

/*------------------------CALL BACKS ------------------------------*/
/*------------------------CALL BACKS ------------------------------*/
/*------------------------CALL BACKS ------------------------------*/
/*------------------------CALL BACKS ------------------------------*/


/*-----------------------------------------------------------------*/
/*                        cancelTransferCB()                       */
/*-----------------------------------------------------------------*/

void cancelTransferCB()
{
 return_code = 1 ;   /* function canceled */
 transfer_done = 1 ;
}


/*-----------------------------------------------------------------*/
/*                          okTransferCB()                         */
/*-----------------------------------------------------------------*/

void okTransferCB(Widget w,caddr_t client_data,ANYCBS *call_data)
{
 long  x_shift = 0 ;
 long  y_shift = 0 ;
 char  value [50]  ;
 short rc1 = 0     ;
 short rc2 = 0     ;


 strcpy (value , XmTextGetString(Field[0]));
 rc1 = sscanf (value , "%d",&x_shift);

 strcpy (value , XmTextGetString(Field[1]));
 rc2 = sscanf (value , "%d",&y_shift);


 if ( rc1 == 1 && rc2 == 1 )
    {
     for ( i=1; i<=feat_count; i++ )
	 {
	  feat[i].xbase += x_shift ;
	  feat[i].ybase += y_shift ;
	  feat[i].xend  += x_shift ;
	  feat[i].yend  += y_shift ;

	  if ( feat[i].has_text[0] == 'Y' )
	     {
	      for(ii=1; ii<=feat[i].text_count; ii++ )
		 {
		  text_index = feat[i].text + ii ;
		  text[text_index].x += x_shift  ;
		  text[text_index].y += y_shift  ;
		 }
	     }

	  if ( feat[i].type == 2 )
	     {
	      for ( ii=1; ii<=feat[i].xy_count; ii++ )
		  {
		   xy_index = feat[i].xy + ii ;
		   x[xy_index] += x_shift     ;
		   y[xy_index] += y_shift     ;
		  }
	     }
	 }

     draw_all();
     // normal_cursor();
     display_scale();

     transfer_done = 1 ;
    }
 else
    {
     xstr = XmStringCreate(" ERROR : No values entered for X,Y",CS);
     XtSetArg(args[0], XmNlabelString, xstr);
     XtSetValues(output_label, args, 1);

     transfer_done = 1 ;
    }

}
