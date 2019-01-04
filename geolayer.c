/*------------------------------------------------------------------------*/
/*                geoINFO/6000  Layer Control ( geolayer.c )              */
/*------------------------------------------------------------------------*/

/*------------------------------------------------------------------------*/
/*                          geoINFO Include Files                         */
/*------------------------------------------------------------------------*/
#include "include/geoIMSextern.h"

/*------------------------------------------------------------------------*/
/*                           Defined Constants                            */
/*------------------------------------------------------------------------*/
#define   LAYER_NAME_LEN         21
#define   MAX_LAYERS             256

/*------------------------------------------------------------------------*/
/*                           Functions Prototypes                         */
/*------------------------------------------------------------------------*/
void  okLayerCB()            ;
void  cancelLayerCB()        ;
void  helpLayerCB()          ;
void  toggleButtonCB()       ;
void  help_okCB()            ;
void  get_layer_visibility() ;

/*------------------------------------------------------------------------*/
/*                           Widget Definition                            */
/*------------------------------------------------------------------------*/
Widget  LayerForm                    ;
Widget  LayerScrolledWindow          ;
Widget  LayerSeparator               ;
Widget  Layer_ok_button              ;
Widget  Layer_cancel_button          ;
Widget  Layer_help_button            ;
Widget  LayerToggles  [MAX_LAYERS+1] ;
Widget  LayerHelpDialog              ;
Widget  LayerbuttonRC                ;
Widget  LayerToggleRC                ;

/*------------------------------------------------------------------------*/
/*                   Global Variable Definition                           */
/*------------------------------------------------------------------------*/
XmString     help_compoundstr                 ;
XmString     compoundstr[MAX_LAYERS+1]        ;

static  char *layers             [MAX_LAYERS] ;
static  int  visibility          [MAX_LAYERS] ;
static  int  original_visibility [MAX_LAYERS] ;


/*------------------------------------------------------------------------*/
/*                         layer_control()                                */
/*------------------------------------------------------------------------*/
void layer_control(Widget parent)
{
 short  i ;
 short  n ;


 /*---------- Get Layer ID's, Names & Visibilities -----------*/

 get_layer_visibility();


 /*-------------------- FormDialog ---------------------------*/

 xstr = XmStringCreate("Layer Control",CS);
 n=0;
 XtSetArg(args[n] , XmNdialogTitle ,        xstr);n++;
 LayerForm = XmCreateFormDialog(parent,"LayerForm",args,n);


 /*------------------- Scrolled Window ----------------------*/
 n=0;
 XtSetArg(args[n], XmNx               ,           0);n++;
 XtSetArg(args[n], XmNy               ,           0);n++;
 XtSetArg(args[n], XmNwidth           ,         200);n++;
 XtSetArg(args[n], XmNheight          ,         220);n++;
 //XtSetArg(args[n], XmNdepth           ,           8);n++;
 XtSetArg(args[n], XmNscrollingPolicy , XmAUTOMATIC);n++;
 XtSetArg(args[n], XmNworkWindow      , LayerForm );n++;

 LayerScrolledWindow = XmCreateScrolledWindow(LayerForm ,"ScrolledW",args,n);
 XtManageChild(LayerScrolledWindow);


 /*------------- make compund string labels ------------------*/

 for ( i=1 ; i<=(lay_count+1) ; i++ )
     {
      compoundstr[i] = XmStringCreateLtoR(layers[i],CS);
     }


 /*----- create row/column for label and toggle buttons ------*/

 LayerToggleRC = XmCreateRowColumn(LayerScrolledWindow,"LayerToggleRC",NULL,0);
 XtManageChild(LayerToggleRC);

 XtVaSetValues(LayerToggleRC,XmNtopAttachment,    XmATTACH_FORM,
                             XmNleftAttachment,   XmATTACH_FORM,
                             XmNrightAttachment,  XmATTACH_FORM,
                             XmNbottomAttachment, XmATTACH_FORM,
                             XmNorientation,      XmVERTICAL,
                             XmNpacking,          XmPACK_COLUMN,
                             XmNentryAlignment,   XmALIGNMENT_BEGINNING,
                        /*   XmNentryAlignment,   XmALIGNMENT_CENTER,   */
                        /*   XmNentryAlignment,   XmALIGNMENT_END,      */
                        //   XmNbackground,       lgray.pixel,
                             NULL);


 /*----------------- create the toggle buttons ---------------*/

 for( i=1 ; i<=(lay_count+1) ; i++ )
    {
     n=0;
     // XtSetArg(args[n] , XmNbackground  , lgray.pixel);n++;

     LayerToggles[i]=XmCreateToggleButton(LayerToggleRC,layers[i],args,n);
     XtManageChild(LayerToggles[i]);

     XtVaSetValues(LayerToggles[i],XmNset               , visibility[i] ,
                                   XmNhighlightThickness, 0             ,
                                   XmNlabelString       , compoundstr[i],
                                   NULL);

     XtAddCallback(LayerToggles[i],XmNarmCallback,toggleButtonCB,(XtPointer)i);
    }


 /*------------------ add a separator --------------------------*/

 n=0;
 // XtSetArg(args[n] , XmNbackground  , lgray.pixel);n++;
 XtSetArg(args[n] , XmNy           ,         220);n++;

 // LayerSeparator =(Widget)XmCreateSeparator(LayerToggleRC,"LayerSeparator",args,n);
 LayerSeparator =(Widget)XmCreateSeparator(LayerForm,"LayerSeparator",args,n);
 XtManageChild(LayerSeparator);


 /*-------- create row/column for button on bottom -------------*/

 // LayerbuttonRC = XmCreateRowColumn(LayerToggleRC,"LayerbuttonRC",NULL,0);
 LayerbuttonRC = XmCreateRowColumn(LayerForm,"LayerbuttonRC",NULL,0);
 XtManageChild(LayerbuttonRC);

 XtVaSetValues(LayerbuttonRC,XmNorientation, XmHORIZONTAL,
                             XmNalignment,   XmALIGNMENT_CENTER,
                          // XmNbackground,  lgray.pixel,
                             XmNy,           220,
                             NULL);


 /*----------------------- OK Button ---------------------------*/
 n=0;
 // XtSetArg(args[n] , XmNbackground  , gray.pixel);n++;

 Layer_ok_button = XmCreatePushButton(LayerbuttonRC,"    OK    ",args,n);
 XtManageChild(Layer_ok_button);

 XtAddCallback(Layer_ok_button,XmNactivateCallback,okLayerCB,NULL);


 /*-------------------- Cancel Button --------------------------*/
 n=0;
 // XtSetArg(args[n] , XmNbackground  , gray.pixel);n++;

 Layer_cancel_button = XmCreatePushButton(LayerbuttonRC,"  Cancel  ",args,n);
 XtManageChild(Layer_cancel_button);

 XtAddCallback(Layer_cancel_button,XmNactivateCallback,cancelLayerCB,NULL);


 /*--------------------- Help Button ---------------------------*/
 n=0;
 // XtSetArg(args[n] , XmNbackground  , gray.pixel);n++;

 Layer_help_button = XmCreatePushButton(LayerbuttonRC,"   Help   ",args,n);
 XtManageChild(Layer_help_button);

 XtAddCallback(Layer_help_button,XmNactivateCallback,helpLayerCB,NULL);


 /*------------------- Resize Attachments --------------------*/

 n=0;
 XtSetArg(args[n], XmNtopAttachment    , XmATTACH_POSITION);n++;
 XtSetArg(args[n], XmNtopPosition      , 0                );n++;

 XtSetArg(args[n], XmNleftAttachment   , XmATTACH_POSITION);n++;
 XtSetArg(args[n], XmNleftPosition     , 0                );n++;

 XtSetArg(args[n], XmNrightAttachment  , XmATTACH_FORM    );n++;
 XtSetArg(args[n], XmNrightOffset      , 0                );n++;


 XtSetArg(args[n], XmNbottomAttachment , XmATTACH_FORM );n++;
 XtSetArg(args[n], XmNbottomOffset     , 40              );n++;

 XtSetValues(LayerScrolledWindow, args, n);

 n=0;
 XtSetArg(args[n], XmNbottomAttachment , XmATTACH_FORM    );n++;
 XtSetArg(args[n], XmNbottomOffset     , 0                );n++;
 XtSetValues(LayerbuttonRC,     args, n);
 // XtSetValues(Layer_cancel_button, args, n);
 // XtSetValues(Layer_help_button,   args, n);


 /*------------------ Set Default Button ----------------------*/

 XtSetArg(args[0], XmNdefaultButton, Layer_ok_button);
 XtSetValues(LayerForm,args,1);

 /*
 XtSetValues(LayerShell,args,1);
 XtSetValues(LayerbuttonRC,args,1);
 XtSetValues(LayerToggleRC,args,1);
 */

 /*---------------- Set MWM Paramters --------------------------*/

 n=0;
 XtSetArg(args[n], XmNnoResize    ,          True); n++;
 XtSetArg(args[n], XmNmwmFunctions, MWM_FUNC_MOVE); n++;
 XtSetValues(LayerForm, args, n);


 /*---------------- Manage / Display / Add Grab ----------------*/

 XtManageChild(LayerForm);           /* Manage LayerForm   */
 XtRealizeWidget(LayerForm);         /* display the dialog */
 XtAddGrab(LayerForm ,True,False );  /* Add Grab           */
}


/*--------------------------------------------------------------------*/
/*---------------------    CALLBACKS     -----------------------------*/
/*---------------------    CALLBACKS     -----------------------------*/
/*---------------------    CALLBACKS     -----------------------------*/
/*---------------------    CALLBACKS     -----------------------------*/
/*---------------------    CALLBACKS     -----------------------------*/
/*---------------------    CALLBACKS     -----------------------------*/
/*---------------------    CALLBACKS     -----------------------------*/
/*--------------------------------------------------------------------*/


/*------------------------------------------------------------------------*/
/*                           toggleButtonCB()                             */
/*------------------------------------------------------------------------*/
void toggleButtonCB(Widget w, int toggle_number, caddr_t call_data)
{
 int       i , j       ;
 Boolean   value       ;
 Boolean   all_setting ;


 /* this callback will perform all updates to the visibility
    array when any visibility toggle button is pressed */


 if ( toggle_number == (lay_count+1) )
    {
     /* ALL button pressed */
     i=0;
     XtSetArg(args[i], XmNset, &all_setting); i++;
     XtGetValues(LayerToggles[lay_count+1], args, i);

     /* set all buttons to NEW setting of the ALL button
	note that setting of button is value before pressing hence ! */
     for( i=1 ; i<(lay_count+1) ; i++ )
	{
	 j=0;
	 XtSetArg(args[j], XmNset, !all_setting); j++;
	 XtSetValues(LayerToggles[i], args, j);
	 visibility[i]=!all_setting;
	}
    }
 else
    {
     /* only one button pressed */

     /* get visibility value for that button */
     /* note that setting of button is value before pressing hence ! */
     j=0;
     XtSetArg(args[j], XmNset, &value); j++;
     XtGetValues(w, args, j);
     visibility[toggle_number]=!value;
    }
}
/*------------------------------------------------------------------------*/
/*                           okLayerCB()                                  */
/*------------------------------------------------------------------------*/
void okLayerCB()
{
 int   i,j;


 /* Use Global Visibility Array to determine Layer Visibility */
 for( i=1 ; i<=lay_count ; i++ )
    {
      if ( visibility[i] == 1 )
	 {
	  lay[i].displayed[0] = 'Y' ;
	 }
      else
	 {
	  lay[i].displayed[0] = 'N' ;
	 }
     original_visibility[i] = visibility[i] ;
    }


 /* Change feature displayed Status according to layer visibility */
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



 /* free compound strings allocated above */
 for ( i = 1 ; i <= (lay_count+1) ; i++)
     {
      XmStringFree(compoundstr[i]);
     }
 XmStringFree(help_compoundstr);

 XtUnmanageChild(LayerForm);
 XtDestroyWidget(LayerForm);

 draw_all() ;
 // normal_cursor() ;
 return;
}
/*------------------------------------------------------------------------*/
/*                       cancelLayerCB()                                  */
/*------------------------------------------------------------------------*/
void cancelLayerCB()
{

 /* Free compound strings allocated above */
 for ( i = 1 ; i <= (lay_count+1) ; i++)
     {
      XmStringFree(compoundstr[i]);
     }

 XmStringFree(help_compoundstr);

 xstr = XmStringCreate(" INFO : Function Canceled",CS);
 XtSetArg(args[0], XmNlabelString, xstr);
 XtSetValues(output_label, args, 1);
 // normal_cursor() ;

 XtUnmanageChild(LayerForm);
 XtDestroyWidget(LayerForm);
 return;
}
/*------------------------------------------------------------------------*/
/*                          helpLayerCB()                                 */
/*------------------------------------------------------------------------*/
void helpLayerCB(Widget w, caddr_t client_data, caddr_t call_data)
{
 /* Arg args[10]; */
 int n;

/*  help text for the help dialog messageString resource, this text should
 *  be externalized into an application resource file or message file, but
 *  long strings are very cumbersome, so the text is included inline here
 */

 char layr_help_text[]={
"The Layers Dialog is used to turn the layer visibility ON and OFF.\n\n"
"Layers which are present in the workspace are indentified by a series\n"
"of toggle buttons.\n"
"The state of each toggle button represents the current visibility of\n"
"the layer.\n"
"Changing the state of a toggle button indicates that the visibility of\n"
"the respective layer is to be changed.\n"
"The ALL button changes the state of all the toggle buttons to the state\n"
"of the All button.\n\n"
"OK\n"
" This button causes layer visibility to be changed, redraw the workspace,\n"
" close the Layer dialog and returns control to geoINFO\n\n"
"Cancel\n"
" This button Cancel Layer dialog and return control to geoINFO\n\n"
"Help\n"
" Displays this dialog\n\n"
"For more information consult the geoINFO User's Guide."};


 /* create the help dialog, any button press removes the dialog */
 n=0;
 XtSetArg(args[n], XmNautoUnmanage, TRUE       ); n++;
 // XtSetArg(args[n], XmNbackground  , lgray.pixel);n++;

 LayerHelpDialog=XmCreateMessageDialog(Layer_help_button, "LayerHelpDialog", args, n);

 /* create compound string for messageString resource of help dialog  */
 help_compoundstr = XmStringCreateLtoR(layr_help_text,CS);
 XtVaSetValues(LayerHelpDialog,
	XmNdialogType, XmDIALOG_MESSAGE,
	XmNmessageString, help_compoundstr,
	NULL);

 /* only provide ok button, unmanage cancel and help buttons */
 XtUnmanageChild(XmMessageBoxGetChild(LayerHelpDialog, XmDIALOG_CANCEL_BUTTON));
 XtUnmanageChild(XmMessageBoxGetChild(LayerHelpDialog, XmDIALOG_HELP_BUTTON));

 XtManageChild(LayerHelpDialog);

 XtRealizeWidget(LayerHelpDialog); /* display the dialog */

}
/*------------------------------------------------------------------------*/
/*                          help_okCB()                                   */
/*------------------------------------------------------------------------*/
void help_okCB(Widget w, caddr_t client_data, caddr_t call_data)
{
 /* remove the help dialog */
 XtUnmanageChild(LayerHelpDialog);
 XtDestroyWidget(LayerHelpDialog);

}
/*------------------------------------------------------------------------*/
/*                       get_layer_visibility()                           */
/*------------------------------------------------------------------------*/
void get_layer_visibility()
{
 int  vis_flag = TRUE ; /* used for All toggle button setting */


 for ( i=1 ; i<=lay_count ; i++ )
     {
      /* Assign layer names to the list */
      layers[i]=(char *)malloc((LAYER_NAME_LEN+1)*sizeof(char));
      sprintf(layers[i],"  [%02d]  ",lay[i].id  );
      strcat (layers[i],lay[lay[i].id].name);


      /* find layer visibility and set up visibility flag */
      if (lay[i].displayed[0] == 'Y')
	 {
	  visibility[i]= 1 ;
	  vis_flag = vis_flag && visibility[i];
	 }
     else
	 {
	  visibility[i]= 0 ;
	  vis_flag = vis_flag && visibility[i];
	 }

      /* set up the array used by the reset function */
      original_visibility[i] = visibility[i] ;
     }


 /* add ALL name to layer list */
 layers[i]=(char *)malloc((LAYER_NAME_LEN+1) * sizeof(char));
 strcpy(layers[i], "  ALL                ");


 /* check for visibility value for ALL TRUE only if all other layers on */
 visibility[i]=vis_flag;

}

