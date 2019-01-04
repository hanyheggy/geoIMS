/*------------------------------------------------------------------------*/
/*             geoINFO/6000  file_selection_box  ( geofsb.c )             */
/*------------------------------------------------------------------------*/

/*------------------------------------------------------------------------*/
/*                          geoINFO Include Files                         */
/*------------------------------------------------------------------------*/
#include "include/geoIMSextern.h"

/*------------------------------------------------------------------------*/
/*                           Functions Prototypes                         */
/*------------------------------------------------------------------------*/
void cancelCB();
void okCB    ();

/*------------------------------------------------------------------------*/
/*                           Widget Definition                            */
/*------------------------------------------------------------------------*/
Widget  AppShell     ;
Widget  fsbox        ;

/*------------------------------------------------------------------------*/
/*                   Global Variable Definition                           */
/*------------------------------------------------------------------------*/
XtAppContext    app_context        ;
Display         *myDisplay         ;
XEvent          myEvent            ;
short           fsb_done = 0       ;
static  char    dirmask[70]        ;
static  char    current_ftype[10]  ;

/*------------------------------------------------------------------------*/
/*                                fsb()                                   */
/*------------------------------------------------------------------------*/

void fsb(char ftype[10],char FSBlabel[30])
{
 int       argc = 1     ;
 char      **argv       ;
 short     n            ;
 XmString  xstr         ;
 XmString  xstr1        ;
 XmString  xstr2        ;
 XmString  xstr3        ;
 XmString  xstr4        ;
 Arg       args[10]     ;
 int       saved_argc   ;
 char      **saved_argv ;


 return_code = 0          ;    /* 0 normal, 1 cancel, 2 error */

 /*
 if ((strcmp (dirmask,"") == 0) || (strcmp (ftype,current_ftype) != 0))
    {
 */
     strcpy (dirmask , IMPORTPATH);  /* Full Path name for Data Import Dir */
     strcat (dirmask , "/*." );      /* any file end with of the following */
     strcat (dirmask , ftype );      /* inf or infb or dxf                 */
  /*
     }
  */

 strcpy ( current_ftype , ftype );   /* Save Current ftype                 */



 /*---- Make sure XtToolkitInitialize is only called once ----*/

 if (ToolkitInitialized == 0)
    {
     XtToolkitInitialize() ;
     ToolkitInitialized = 1;
    }

 /*------ create the application context ---------------------*/

 app_context = XtCreateApplicationContext();

 /*  create duplicate argc and argv, XtOpenDisplay
  *  changes argc and argv.  But if we change argc and argv,
  *  XtAppCreateShell down below causes errors
  */
 saved_argc = argc;
 saved_argv = (char **)XtMalloc(argc * sizeof(char *));
 bcopy(argv, saved_argv, argc * sizeof(char *));

 /*---------------------  Open Display -----------------------*/

 myDisplay = XtOpenDisplay(app_context,NULL,NULL,"AppShell",NULL,0,&argc,argv);
 if (myDisplay == NULL)
    {
     fprintf(stderr,"FSB : Can not open display\n");
     return_code = 2 ;
     return ;
    }

 /*-------------------  Application Shell --------------------*/

 n = 0;
 XtSetArg(args[n],XtNargc        , saved_argc );n++;
 XtSetArg(args[n],XtNargv        , saved_argv );n++;

 AppShell = XtAppCreateShell(NULL,"AppShell",applicationShellWidgetClass,myDisplay,args,n);


 /*------------------- File Selection Box --------------------*/

 xstr1 = XmStringCreate("Current Directory",CS);
 xstr2 = XmStringCreate("Files"            ,CS);
 xstr3 = XmStringCreate("Selected File"    ,CS);
 xstr4 = XmStringCreate(dirmask            ,CS);

 xstr = XmStringCreate(FSBlabel,CS);
 n=0;
 XtSetArg(args[n],XmNdialogTitle         , xstr        );n++;
 XtSetArg(args[n],XmNwidth               , 300         );n++;
 XtSetArg(args[n],XmNheight              , 370         );n++;
 XtSetArg(args[n],XmNmustMatch           , True        );n++;
 XtSetArg(args[n],XmNautoUnmanage        , False       );n++;
 XtSetArg(args[n],XmNnoResize            , False       );n++;
/* XtSetArg(args[n],XmNnoResize            ,True        );n++; */
 XtSetArg(args[n],XmNfilterLabelString   , xstr1       );n++;
 XtSetArg(args[n],XmNlistLabelString     , xstr2       );n++;
 XtSetArg(args[n],XmNselectionLabelString, xstr3       );n++;
 XtSetArg(args[n],XmNdirMask             , xstr4       );n++;
 XtSetArg(args[n],XmNforeground          , black.pixel );n++;
 XtSetArg(args[n],XmNbackground          , lgray.pixel );n++;

 fsbox = (Widget)XmCreateFileSelectionBox(AppShell,"FSB",args,n);
 XtAddCallback(fsbox ,XmNokCallback    ,okCB    ,NULL);
 XtAddCallback(fsbox ,XmNcancelCallback,cancelCB,NULL);
 XtManageChild(fsbox);


 /*-------- Display the Interface & Set MWM Functions --------*/

 XtRealizeWidget(AppShell);
 XtVaSetValues(AppShell,XmNmwmFunctions
		       ,(MWM_FUNC_MOVE|MWM_FUNC_MINIMIZE),NULL);


/*-----------    Check if any Events Pending..      ----------*/
/*----------- This will Force Display of the Dialog ----------*/

 while (XtAppPending(app_context))
       {
	XtAppNextEvent(app_context, &myEvent);
	XtDispatchEvent(&myEvent);
       }

 fsb_done = 0 ;

/*------------  Running From Regular Event Loop --------------*/

 /* Close button Callback sets fsb_done = 1 */
 while (fsb_done == 0)
       {
        XtAppNextEvent(app_context, &myEvent);
	XtDispatchEvent( &myEvent);
       }


 XtUnrealizeWidget(AppShell);
 XtDestroyWidget(AppShell);
 XSync(myDisplay, False);
}

/*------------------------CALL BACKS ------------------------------*/
/*------------------------CALL BACKS ------------------------------*/
/*------------------------CALL BACKS ------------------------------*/
/*------------------------CALL BACKS ------------------------------*/


/*-----------------------------------------------------------------*/
/*                        cancelCB()                               */
/*-----------------------------------------------------------------*/
void cancelCB(Widget w, caddr_t client_data, caddr_t call_data)
{
 return_code = 1 ;
 fsb_done = 1 ;
}

/*-----------------------------------------------------------------*/
/*                           okCB()                                */
/*-----------------------------------------------------------------*/
void okCB(Widget w, caddr_t client_data, FSBCBS *call_data)
{
 char      *str             ;
 XmString  xstr             ;
 Arg       args[2]          ;
 char      *updated_dirmask ;


 /* Get Input File Name */

 XmStringGetLtoR(call_data->value ,CS ,&str);
 strcpy ( InputFile , str );


 /* Save Updated dirmask */


 XtSetArg(args[0],XmNdirMask,&xstr);
 XtGetValues(fsbox,args,1);

 XmStringGetLtoR(xstr ,CS , &updated_dirmask);
/* LINUX   strcpy ( dirmask , updated_dirmask ); */


 fsb_done = 1 ;

}

