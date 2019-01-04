/*------------------------------------------------------------------------*/
/*                geoINFO/6000  Map Projection ( geoprojection.c )        */
/*------------------------------------------------------------------------*/

/*------------------------------------------------------------------------*/
/*                          geoINFO Include Files                         */
/*------------------------------------------------------------------------*/
#include "include/geoIMSextern.h"

/*------------------------------------------------------------------------*/
/*                           Functions Prototypes                         */
/*------------------------------------------------------------------------*/
void cancelProjectionCB();
void okProjectionCB();

double transverse_mercator   (double LAMDA, double PHI, int flag);
double gnomonic              (double LAMDA, double PHI, int flag);
double stereographic         (double LAMDA, double PHI, int flag);
double orthographic          (double LAMDA, double PHI, int flag);
double cassini_solnder       (double LAMDA, double PHI, int flag);
double polar_stereographic   (double LAMDA, double PHI, int flag);
double sanson_flamsteed      (double LAMDA, double PHI, int flag);
double albers_1              (double LAMDA, double PHI, int flag);
double albers_2              (double LAMDA, double PHI, int flag);
double werner                (double LAMDA, double PHI, int flag);

double lambert_conformal_1   (double LAMDA, double PHI, int flag);
double lambert_conformal_2   (double LAMDA, double PHI, int flag);
double lambert_equivalent_cyl(double LAMDA, double PHI, int flag);
double lambert_equivalent_azm(double LAMDA, double PHI, int flag);

double mercx                 (double LAMDA, double PHI);
double mercy                 (double LAMDA, double PHI);
double merclon               (double X    , double Y  );
double merclat               (double X    , double Y  );
double mercm0                (double LAMDA, double PHI);
double mercm90               (double LAMDA, double PHI);

double Long2ETM_X            (double Lon, double Lat);
double Lat2ETM_Y             (double Lon, double Lat);
double ETM_X2Long            (double   X, double Y  );
double ETM_Y2Lat             (double   X, double Y  );
double UTM2ETM_X             (double   X, double Y  );
double UTM2ETM_Y             (double   X, double Y  );
double ETM2UTM_X             (double   X, double Y  );
double ETM2UTM_Y             (double   X, double Y  );

double toETM   (double LAMDA, double PHI, int flag          );
double fromETM (double X    , double Y  , int flag          );
double toUTM   (double LAMDA, double PHI, int flag          );
double fromUTM (double X    , double Y  , int Zone, int flag);
double toUTMa  (double LAMDA, double PHI, int flag          );
double fromUTMa(double X    , double Y  , int Zone, int flag);
double toUTMfz (double LAMDA, double PHI, int Zone, int flag);
double toTM    (double LAMDA, double PHI, double Longo, double Lato, double Xo, double Yo, int flag);
double fromTM  (double X    , double Y  , double Longo, double Lato, double Xo, double Yo, int flag);


/*------------------------------------------------------------------------*/
/*                           Widget Definition                            */
/*------------------------------------------------------------------------*/
Widget  ProjectionShell          ;
Widget  ProjectionForm           ;
Widget  Projection_ok_button     ;
Widget  Projection_cancel_button ;
Widget  Label[10]                ;
Widget  Field[10]                ;

/*------------------------------------------------------------------------*/
/*                   Global Variable Definition                           */
/*------------------------------------------------------------------------*/
XtAppContext  Projection_context ;
Display       *ProjectionDisplay ;
XEvent        ProjectionEvent    ;

short         rpoj_done = 0      ;

double  x_proj; /*** x_proj = Northing ***/
double  y_proj; /*** y_proj = Easting  ***/
double  m0;
double  m90;

double  LAMDA0  = 30.0;
double  PHI0    = 26.5;
double  PHI1    = 25.0;
double  PHI2    = 28.0;

/***********************************************************************
  Angular Distortion : DTHETA = atan( m90/m0 ) - ((double)45.0*PI180);
  Area    Distortion : DAREA  = m90*m0;
**********************************************************************/
#define  ONE   (double)( 1.0 )
#define  PI    (3.14159265)     /* (3.14159265358979323846) */
#define  PI180 (double)( PI/(double)180.0 )
/*** Klarke 1866 ***/
#define  a     (double)(6378206.4)
#define  f     (double)(ONE / (double)298.979)
/********* Egypt ******************************
#define  a     (double)(6378388.0)
#define  f     (double)(ONE / (double)297.000)
***********************************************/
#define  eps   (double)( sqrt ( ONE - (ONE-f)*(ONE-f) ) )
#define  M     (double)( a*(ONE-eps*eps) / pow(ONE-eps*eps*sin(PHI)*sin(PHI) , (double) 1.5) )
#define  N     (double)( a               / pow(ONE-eps*eps*sin(PHI)*sin(PHI) , (double) 0.5) )
#define  R     (double)( sqrt(M*N) )


/*------------------------------------------------------------------------*/
/*                           map_projection()                             */
/*------------------------------------------------------------------------*/

void map_projection()
{
 int       argc = 0 ;
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
 Projection_context = XtCreateApplicationContext();


 /*---------------------  Open Display --------------------------------*/
 ProjectionDisplay = XtOpenDisplay(Projection_context,NULL,NULL,"ProjectionShell",NULL,0,&argc,argv);

 if (ProjectionDisplay == NULL)
    {
     fprintf(stderr,"Projection : Can not open display\n");
     return ;
    }

 /*-------------------  Application Shell --------------------*/
 n = 0;
 XtSetArg(args[n] , XmNwidth       ,         400);n++;
 XtSetArg(args[n] , XmNheight      ,         200);n++;

 ProjectionShell=XtAppCreateShell(NULL,"ProjectionShell",applicationShellWidgetClass,ProjectionDisplay,args,n);

 /*----------------------- Form ------------------------------*/
 xstr = XmStringCreate("Map Projection",CS);
 n=0;
 XtSetArg(args[n] , XmNdialogTitle ,        xstr);n++;
 XtSetArg(args[n] , XmNx           ,           0);n++;
 XtSetArg(args[n] , XmNy           ,           0);n++;
 XtSetArg(args[n] , XmNwidth       ,         400);n++;
 XtSetArg(args[n] , XmNheight      ,         200);n++;
 XtSetArg(args[n] , XmNbackground  , lgray.pixel);n++;

 ProjectionForm = XmCreateForm(ProjectionShell,"ProjectionForm", args,n);
 XtManageChild(ProjectionForm);

 /*---------------------- OK button --------------------------*/
 xstr = XmStringCreate("OK",CS);
 n=0;
 XtSetArg(args[n] , XmNlabelString ,       xstr);n++;
 XtSetArg(args[n] , XmNx           ,         70);n++;
 XtSetArg(args[n] , XmNy           ,        150);n++;
 XtSetArg(args[n] , XmNwidth       ,         80);n++;
 XtSetArg(args[n] , XmNheight      ,         30);n++;
 XtSetArg(args[n] , XmNbackground  , gray.pixel);n++;

 Projection_ok_button = XmCreatePushButton(ProjectionForm,"Button",args,n);
 /*
 XtAddCallback(Projection_ok_button,XmNactivateCallback,okProjectionCB,ProjectionForm);
 */
 XtAddCallback(Projection_ok_button,XmNactivateCallback,okProjectionCB,NULL);
 XtManageChild(Projection_ok_button);

 /*---------------------- Cancel button ----------------------*/
 xstr = XmStringCreate("Cancel",CS);
 n=0;
 XtSetArg(args[n] , XmNlabelString ,       xstr);n++;
 XtSetArg(args[n] , XmNx           ,        230);n++;
 XtSetArg(args[n] , XmNy           ,        150);n++;
 XtSetArg(args[n] , XmNwidth       ,         80);n++;
 XtSetArg(args[n] , XmNheight      ,         30);n++;
 XtSetArg(args[n] , XmNbackground  , gray.pixel);n++;

 Projection_cancel_button = XmCreatePushButton(ProjectionForm,"Button",args,n);
 XtAddCallback(Projection_cancel_button,XmNactivateCallback,cancelProjectionCB,ProjectionForm);
 XtManageChild(Projection_cancel_button);

 /*---------------------- Label[0]     ----------------------*/
 xstr = XmStringCreate("Precentage",CS);
 n=0;
 XtSetArg(args[n] , XmNlabelString ,        xstr);n++;
 XtSetArg(args[n] , XmNx           ,          10);n++;
 XtSetArg(args[n] , XmNy           ,          30);n++;
 XtSetArg(args[n] , XmNwidth       ,         140);n++;
 XtSetArg(args[n] , XmNheight      ,          30);n++;
 XtSetArg(args[n] , XmNbackground  , lgray.pixel);n++;

 Label[0] = XmCreateLabel(ProjectionForm,"Label0",args,n);
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

 Field[0] = XmCreateTextField(ProjectionForm,"Field0",args,n);
 XtManageChild(Field[0]);

 /*---------------------- Label[1]     ----------------------*/
 xstr = XmStringCreate("Muliplay/Devide [M/D]",CS);
 n=0;
 XtSetArg(args[n] , XmNlabelString ,        xstr);n++;
 XtSetArg(args[n] , XmNx           ,          10);n++;
 XtSetArg(args[n] , XmNy           ,          80);n++;
 XtSetArg(args[n] , XmNwidth       ,         140);n++;
 XtSetArg(args[n] , XmNheight      ,          30);n++;
 XtSetArg(args[n] , XmNbackground  , lgray.pixel);n++;

 Label[1] = XmCreateLabel(ProjectionForm,"Label1",args,n);
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

 Field[1] = XmCreateTextField(ProjectionForm,"Field1",args,n);
 XtManageChild(Field[1]);


 /*--------- Set Initial Focus & Default Button ---------------*/

 XtSetArg(args[0], XmNinitialFocus, Field[0]);
 XtSetValues(ProjectionForm,args,1);

 XtSetArg(args[0], XmNdefaultButton, Projection_ok_button);
 XtSetValues(ProjectionForm,args,1);


 /*------------------- Display the Interface ------------------*/

  XtRealizeWidget(ProjectionShell);


 /*--------- Check if any Events Pending ..        ------------*/
 /*--------- this will force display of the dialog ------------*/

  while (XtAppPending(Projection_context))
	{
	 XtAppNextEvent(Projection_context, &ProjectionEvent);
	 XtDispatchEvent(&ProjectionEvent);
	}

  rpoj_done = 0 ;


  /*----------- running from the regular event loop -----------*/
  /*----------- until close button callback sets rpoj_done = 1 -----*/

  while (rpoj_done == 0)
	{
	 XtAppNextEvent(Projection_context, &ProjectionEvent);
	 XtDispatchEvent( &ProjectionEvent);
	}
  XtUnrealizeWidget(ProjectionShell);
  XtDestroyWidget(ProjectionShell);
  XSync(ProjectionDisplay, False);

}

/*------------------------CALL BACKS ------------------------------*/
/*------------------------CALL BACKS ------------------------------*/
/*------------------------CALL BACKS ------------------------------*/
/*------------------------CALL BACKS ------------------------------*/


/*-----------------------------------------------------------------*/
/*                      cancelProjectionCB()                       */
/*-----------------------------------------------------------------*/

void cancelProjectionCB()
{
 return_code = 1 ;   /* function canceled */
 rpoj_done = 1 ;
}


/*-----------------------------------------------------------------*/
/*                        okProjectionCB()                         */
/*-----------------------------------------------------------------*/

void okProjectionCB(Widget w,caddr_t client_data,ANYCBS *call_data)
{
 long  percentage = 0 ;
 char  type  [2]      ;
 char  value [50]     ;
 short rc1 = 0        ;
 short rc2 = 0        ;


 strcpy (value , XmTextGetString(Field[0]));
 rc1 = sscanf (value , "%d",&percentage);

 strcpy (value , XmTextGetString(Field[1]));
 rc2 = sscanf (value , "%s",type);

 if ( type[0] == 'm' )  type[0] == 'M' ;
 if ( type[0] == 'd' )  type[0] == 'D' ;

 /*
 printf("\n feat_count = %d", feat_count);
 printf("\n rc1        = %d", rc1       );
 printf("\n rc2        = %d", rc2       );
 printf("\n percentage = %d", percentage);
 printf("\n type       = %s", type      );
 printf("\n");
 */

 if ( (rc1 == 1 && rc2 == 1) && (type[0]=='M'|| type[0]=='D') )
    {
      if ( type[0] == 'M' )
	 {
	  for ( i=1; i<=feat_count; i++ )
	      {
	       feat[i].xbase     *= percentage ;
	       feat[i].ybase     *= percentage ;
	       feat[i].xend      *= percentage ;
	       feat[i].yend      *= percentage ;
	       feat[i].symb_size *= percentage ;

	       if ( feat[i].has_text[0] == 'Y' )
		  {
		   for(ii=1; ii<=feat[i].text_count; ii++ )
		      {
		       text_index = feat[i].text + ii      ;
		       text[text_index].size *= percentage ;
		       text[text_index].x    *= percentage ;
		       text[text_index].y    *= percentage ;
		      }
		  }

	       if ( feat[i].type == 2 )
		  {
		   for ( ii=1; ii<=feat[i].xy_count; ii++ )
		       {
			xy_index = feat[i].xy + ii ;
			x[xy_index] *= percentage ;
			y[xy_index] *= percentage ;
		       }
		  }
	      }
	 }

 else if ( type[0] == 'D' )
	 {
	  for ( i=1; i<=feat_count; i++)
	      {
	       feat[i].xbase     /= percentage ;
	       feat[i].ybase     /= percentage ;
	       feat[i].xend      /= percentage ;
	       feat[i].yend      /= percentage ;
	       feat[i].symb_size /= percentage ;

	       if ( feat[i].has_text[0] == 'Y' )
		  {
		   for(ii=1; ii<=feat[i].text_count; ii++)
		      {
		       text_index = feat[i].text + ii      ;
		       text[text_index].size /= percentage ;
		       text[text_index].x    /= percentage ;
		       text[text_index].y    /= percentage ;
		      }
		  }

	       if ( feat[i].type == 2 )
		  {
		   for ( ii=1; ii<=feat[i].xy_count; ii++)
		       {
			xy_index = feat[i].xy + ii ;
			x[xy_index] /= percentage ;
			y[xy_index] /= percentage ;
		       }
		  }
	      }
	 }


     draw_all();
     // normal_cursor();
     display_scale();

     rpoj_done = 1 ;
    }
 else
    {
     xstr = XmStringCreate(" ERROR : No values entered for X,Y",CS);
     XtSetArg(args[0], XmNlabelString, xstr);
     XtSetValues(output_label, args, 1);

     rpoj_done = 1 ;
    }

}





/***********************************************************************/
double change_LAMDAo(double value)
{
   LAMDA0=value;
   return(value);
}
/***********************************************************************/
double change_PHIo(double value)
{
   PHI0=value;
   return(value);
}
/***********************************************************************/
double change_PHI1(double value)
{
   PHI1=value;
   return(value);
}
/***********************************************************************/
double change_PHI2(double value)
{
   PHI2=value;
   return(value);
}




/***********************************************************************/
double gnomonic(double LAMDA, double PHI, int flag)
{
  double I,II,III,IV,V,VI,VII,VIII,IX,X;

  PHI   = PHI * PI180;
  LAMDA = LAMDA * PI180;

  I           = ( (double)PHI0*PI180 ) ;
  II          = ( LAMDA - (double)LAMDA0*PI180 ) ;
  III         = R * ( (cos(I)*sin(PHI)) - (sin(I)*cos(PHI)*cos(II)) );
  IV          =     ( (sin(I)*sin(PHI)) + (cos(I)*cos(PHI)*cos(II)) );
  x_proj           = III/IV;

  V           = R * cos(PHI) * sin(II) ;
  y_proj           = V/IV;

  VI          = sin(PHI);
  if(VI == 0)
  {
    VI=0.0001;
  }
  m0  = ONE/( VI    );
  m90 = ONE/( VI*VI );

  switch (flag)
  {
     case 2:
         return(x_proj);
     case 1:
         return(y_proj);
     case 3:
         return(m0);
     case 4:
         return(m90);
     default:
         return(x_proj);
  }
}



/***********************************************************************/
double stereographic(double LAMDA, double PHI, int flag)
{
  double I,II,III,IV,V,VI,VII,VIII,IX,X;

  PHI   = PHI * PI180;
  LAMDA = LAMDA * PI180;

  I           = ( (double)PHI0*PI180 ) ;
  II          = ( LAMDA - (double)LAMDA0*PI180 ) ;
  III         = 2*R * ( (cos(I)*sin(PHI)) - (sin(I)*cos(PHI)*cos(II)) );
  IV          = ( 1.0 + (sin(I)*sin(PHI)) + (cos(I)*cos(PHI)*cos(II)) );
  x_proj           = III/IV;

  V           = 2*R * cos(PHI) * sin(II) ;
  y_proj           = V/IV;

  VI          = cos( (double)45.0*PI180 - PHI*0.5 );
  if(VI == 0)
  {
    VI=0.0001;
  }
  m0 = ONE/( VI*VI );
  m90= m0;

  switch (flag)
  {
     case 2:
         return(x_proj);
     case 1:
         return(y_proj);
     case 3:
         return(m0);
     case 4:
         return(m90);
     default:
         return(x_proj);
  }
}


/***********************************************************************/
double orthographic(double LAMDA, double PHI, int flag)
{
  double I,II,III,IV,V,VI,VII,VIII,IX,X;

  PHI   = PHI * PI180;
  LAMDA = LAMDA * PI180;

  I           = ( (double)PHI0*PI180 ) ;
  II          = ( LAMDA - (double)LAMDA0*PI180 ) ;
  III         = R * ( (cos(I)*sin(PHI)) - (sin(I)*cos(PHI)*cos(II)) );
  x_proj           = III;

  V           = R * cos(PHI) * sin(II) ;
  y_proj           = V;

  VI          = cos( (double)90.0*PI180 - PHI );
  m0 = VI;
  m90= 1.0;

  switch (flag)
  {
     case 2:
         return(x_proj);
     case 1:
         return(y_proj);
     case 3:
         return(m0);
     case 4:
         return(m90);
     default:
         return(x_proj);
  }
}


/***********************************************************************/
double cassini_solnder(double LAMDA, double PHI, int flag)
{
  switch (flag)
  {
     case 1:
         return(LAMDA);
     case 2:
         return(PHI);
     case 3:
         return(1);
     case 4:
         return(1);
     default:
         return(LAMDA);
  }
}


/***********************************************************************/
double lambert_conformal_1(double LAMDA, double PHI, int flag)
{
  double I,II,III,IV,V,VI,VII,VIII,IX,X;
  double p,N0;

  PHI   = PHI * PI180;
  LAMDA = LAMDA * PI180;

  I           = ( ((double)45.0*PI180) - (PHI*(double)0.5) );
  II          = ( ONE + eps*sin(PHI) ) / ( ONE - eps*sin(PHI) );
  III         = ( ((double)45.0*PI180) - (PHI0*PI180*(double)0.5) ) ;
  IV          = ( ONE + eps*sin(PHI0*PI180) ) / ( ONE - eps*sin(PHI0*PI180) );
  V           = tan(I   * pow( II , eps*(double)0.5 ));
  VI          = tan(III * pow( IV , eps*(double)0.5 ));
  VII         = pow( (V/VI) , sin(PHI0*PI180) );
  N0          = (a/pow(ONE-eps*eps*sin(PHI0*PI180)*sin(PHI0*PI180),(double)0.5));
  p           = N0 * VII / tan(PHI0*PI180);

  x_proj           = N0/tan(PHI0*PI180) - p*cos(LAMDA*sin(PHI0*PI180));

  y_proj           = p*sin(LAMDA*sin(PHI0*PI180));

  m0  = (p * sin(PHI0*PI180))/(N * cos(PHI));
  m90 = m0;

  switch (flag)
  {
     case 2:
         return(x_proj);
     case 1:
         return(y_proj);
     case 3:
         return(m0);
     case 4:
         return(m90);
     default:
         return(x_proj);
  }
}



/***********************************************************************/
double lambert_conformal_2(double LAMDA, double PHI, int flag)
{
  double I,II,III,IV,V,VI,VII,VIII,IX,X,XI;
  double p,p0,N0,N1,N2,c,c1,c2,SinPhi0,Phi0;

  PHI   = PHI * PI180;
  LAMDA = LAMDA * PI180;

  I           = ( ((double)45.0*PI180) - (PHI1*PI180*(double)0.5) ) ;
  II          = ( ONE + eps*sin(PHI1*PI180) ) / ( ONE - eps*sin(PHI1*PI180) );
  III         = log(tan(I * pow(II , eps*(double)0.5)));
  IV          = ( ((double)45.0*PI180) - (PHI2*PI180*(double)0.5) ) ;
  V           = ( ONE + eps*sin(PHI2*PI180) ) / ( ONE - eps*sin(PHI2*PI180) );
  VI          = log(tan(IV* pow(V  , eps*(double)0.5)));
  N1          = (a/pow(ONE-eps*eps*sin(PHI1*PI180)*sin(PHI1*PI180),(double)0.5));
  VII         = log(N1*cos(PHI1*PI180));
  N2          = (a/pow(ONE-eps*eps*sin(PHI2*PI180)*sin(PHI2*PI180),(double)0.5));
  VIII        = log(N2*cos(PHI2*PI180));
  SinPhi0     = (VII-VIII)/(III-VI);
  Phi0        = asin(SinPhi0);

  III         = tan(I * pow(II,eps*(double)0.5));
  VI          = tan(IV* pow(V ,eps*(double)0.5));
  c1          = ( N1*cos(PHI1*PI180) )/( SinPhi0*pow((III),SinPhi0) );
  c2          = ( N2*cos(PHI2*PI180) )/( SinPhi0*pow((VI ),SinPhi0) );
  c           = (c1+c2)/2.0;

  IX          = ( ((double)45.0*PI180) - (PHI*(double)0.5) ) ;
  X           = ( ONE + eps*sin(PHI) ) / ( ONE - eps*sin(PHI) );
  XI          = tan(IX * pow( X , eps*(double)0.5 ));
  p           = c*pow(XI,SinPhi0);

  I           = ( ((double)45.0*PI180) - (Phi0*(double)0.5) ) ;
  II          = ( ONE + eps*sin(Phi0) ) / ( ONE - eps*sin(Phi0) );
  III         = tan(I * pow( II , eps*(double)0.5 ));
  p0          = c*pow(III,SinPhi0);

  x_proj           = p0 - p*cos(LAMDA*SinPhi0);

  y_proj           = p*sin(LAMDA*SinPhi0);

  m0 = (p * SinPhi0)/(N * cos(PHI));
  m90 = m0;

  switch (flag)
  {
     case 2:
         return(x_proj);
     case 1:
         return(y_proj);
     case 3:
         return(m0);
     case 4:
         return(m90);
     default:
         return(x_proj);
  }
}



/***********************************************************************/
double polar_stereographic(double LAMDA, double PHI, int flag)
{
  double I,II,III,IV,V,VI,VII,VIII,IX,X;
  double p;

  PHI   = PHI * PI180;
  LAMDA = LAMDA * PI180;

  I           = ( ((double)45.0*PI180) - (PHI*(double)0.5) ) ;
  III         = ( ONE + eps*sin(PHI) );
  IV          = ( ONE - eps*sin(PHI) );
  VI          = tan(I*pow( III/IV , eps*(double)0.5 ));
  VII         = pow( (1.0-eps),(-0.5*(1.0+eps))  );
  VIII        = pow( (1.0+eps),(-0.5*(1.0-eps))  );
  p           = 2.0*a*VIII*VII*VI;

  x_proj           = p*cos(LAMDA);
  y_proj           = p*sin(LAMDA);

  VII         = pow( (1.0-eps),(1.0+2.0*eps)  );
  VIII        = pow( (1.0+eps),(1.0-2.0*eps)  );
  m0  = 1.0+(VII*VIII*(x_proj*x_proj+y_proj*y_proj)/(4.0*a*a));
  m90 = m0;

  switch (flag)
  {
     case 2:
         return(x_proj);
     case 1:
         return(y_proj);
     case 3:
         return(m0);
     case 4:
         return(m90);
     default:
         return(x_proj);
  }
}



/***********************************************************************/
double transverse_mercator(double LAMDA, double PHI, int flag)
{
  double I,II,III,IV,V,VI,VII,VIII,IX,X;

  PHI   = PHI * PI180;
  LAMDA = LAMDA * PI180;

  I           = ( (double)PHI0*PI180 ) ;
  II          = 1.0 + sin(PHI)*sin(I) + cos(PHI)*cos(I)*cos(LAMDA);
  III         = 1.0 - sin(PHI)*sin(I) - cos(PHI)*cos(I)*cos(LAMDA);

  x_proj           = 0.5*R*log(II/III);

  II          = cos(PHI)*sin(LAMDA);
  III         = cos(PHI)*sin(I)*cos(LAMDA) - cos(I)*sin(PHI);
  y_proj           = R*atan(II/III);
  m0  =0 ;
  m90 =0 ;

  switch (flag)
  {
     case 2:
         return(x_proj);
     case 1:
         return(y_proj);
     case 3:
         return(m0);
     case 4:
         return(m90);
     default:
         return(x_proj);
  }
}



/***********************************************************************/
double albers_1(double LAMDA, double PHI, int flag)
{
  switch (flag)
  {
     case 1:
         return(LAMDA);
     case 2:
         return(PHI);
     case 3:
         return(1);
     case 4:
         return(1);
     default:
         return(LAMDA);
  }
}


/***********************************************************************/
double albers_2(double LAMDA, double PHI, int flag)
{
  switch (flag)
  {
     case 1:
         return(LAMDA);
     case 2:
         return(PHI);
     case 3:
         return(1);
     case 4:
         return(1);
     default:
         return(LAMDA);
  }
}



/***********************************************************************/
double lambert_equivalent_cyl(double LAMDA, double PHI, int flag)
{
  PHI   = PHI * PI180;
  LAMDA = LAMDA * PI180;

  x_proj           = R*sin(PHI);
  y_proj           = R*LAMDA;

  m0 = cos(PHI);
  m90 = 1.0/cos(PHI);

  switch (flag)
  {
     case 2:
         return(x_proj);
     case 1:
         return(y_proj);
     case 3:
         return(m0);
     case 4:
         return(m90);
     default:
         return(x_proj);
  }
}



/***********************************************************************/
double lambert_equivalent_azm(double LAMDA, double PHI, int flag)
{
  PHI   = PHI * PI180;
  LAMDA = LAMDA * PI180;

  x_proj           = 2.0*R*sin((double)45.0*PI180-0.5*PHI)*cos(LAMDA);
  y_proj           = 2.0*R*sin((double)45.0*PI180-0.5*PHI)*sin(LAMDA);

  m0  = cos((double)45.0*PI180-0.5*PHI);
  m90 = 1.0/cos((double)45.0*PI180-0.5*PHI);

  switch (flag)
  {
     case 2:
         return(-x_proj);
     case 1:
         return(y_proj);
     case 3:
         return(m0);
     case 4:
         return(m90);
     default:
         return(x_proj);
  }
}



/***********************************************************************/
double sanson_flamsteed(double LAMDA, double PHI, int flag)
{
  PHI   = PHI * PI180;
  LAMDA = LAMDA * PI180;

  x_proj           = R*PHI;
  y_proj           = R*cos(PHI)*LAMDA;

  m0  = sqrt(1.0+sin(PHI)*sin(PHI));
  m90 = 1.0;

  switch (flag)
  {
     case 2:
         return(x_proj);
     case 1:
         return(y_proj);
     case 3:
         return(m0);
     case 4:
         return(m90);
     default:
         return(x_proj);
  }
}



/***********************************************************************/
double werner(double LAMDA, double PHI, int flag)
{
  double I,II,III,IV,V,VI,VII,VIII,IX,X;

  PHI   = PHI * PI180;
  LAMDA = LAMDA * PI180;

  I           = ((double)90.0*PI180 - PHI);
  x_proj           = R*I*cos(cos(PHI)/I*LAMDA);
  y_proj           = R*I*sin(cos(PHI)/I*LAMDA);

  II          = LAMDA*(sin(PHI) - (cos(PHI)/I));
  II          = II*II;
  m0  = sqrt(1.0+II);
  m90 = 1.0;

  switch (flag)
  {
     case 2:
         return(-x_proj);
     case 1:
         return(y_proj);
     case 3:
         return(m0);
     case 4:
         return(m90);
     default:
         return(x_proj);
  }
}



/*------------------------ mercx() --------------------------------*/
double mercx(double LAMDA, double PHI)
{
  double I,II,III,IV,V,VI,VII,VIII,IX;
  double X,Y;

  LAMDA = LAMDA*PI180;
  X     = a*LAMDA;
  return(X);
}
/*------------------------ mercy() --------------------------------*/
double mercy(double LAMDA, double PHI)
{
  double I,II,III,IV,V,VI,VII,VIII,IX;
  double X,Y;

  PHI   = PHI*PI180;
  I     = ( ((double)45.0*PI180) + (PHI*(double)0.5) ) ;
  III   = ( ONE - eps*sin(PHI) );
  IV    = ( ONE + eps*sin(PHI) );
  VI    = pow( III/IV , eps*(double)0.5 );
  Y     = a*log(tan(I*VI));
  return(Y);
}
/*------------------------ merclon() -----------------------------*/
double merclon(double X, double Y)
{
  double LAMDA,PHI;

  LAMDA=X/a;
  LAMDA=LAMDA/PI180;
  return(LAMDA);
}
/*------------------------ merclat() -----------------------------*/
double merclat(double X, double Y)
{
  double LAMDA,PHI;
  double yy,c,sign;

  PHI=2.0*(atan(exp(Y/a))-(PI/4.0));
  c=PHI;
  yy=mercy(LAMDA,c/PI180);
  sign=yy-Y;
  for(c=(PHI+.000001) ; c<(PHI+1) ; c+=.000001)
  {
     yy=mercy(LAMDA,c/PI180);
     if( (sign)*(yy-Y) < 0 )
     {
        PHI=(c-.000001/2.0)/PI180;
        return(PHI);
     }
  }
  PHI=PHI/PI180;
  return(PHI);
}



/*------------------------ mercm0() -------------------------------*/
double mercm0(double LAMDA, double PHI)
{
  double I,II,III,IV,V,VI,VII,VIII,IX;
  double X,Y;

  LAMDA = LAMDA*PI180;
  X     = a*LAMDA;

  m0  = a/( N * cos(PHI) );
  m90 = m0;

  return(m0);
}
/*------------------------ mercm90() ------------------------------*/
double mercm90(double LAMDA, double PHI)
{
  double I,II,III,IV,V,VI,VII,VIII,IX;
  double X,Y;

  PHI   = PHI*PI180;
  I     = ( ((double)45.0*PI180) + (PHI*(double)0.5) ) ;
  III   = ( ONE - eps*sin(PHI) );
  IV    = ( ONE + eps*sin(PHI) );
  VI    = pow( III/IV , eps*(double)0.5 );
  Y     = a*log(tan(I*VI));

  m0  = a/( N * cos(PHI) );
  m90 = m0;

  return(m90);
}






double Long2ETM_X(double Lon, double Lat)
{
    /****** Approximate : LAT/LONG ---to-->  ETM ******/
    return ( ( (Lon-33.0)*96426.5 ) +  807853.0 );
}
double Lat2ETM_Y(double Lon, double Lat)
{
    /****** Approximate : LAT/LONG ---to-->  ETM ******/
    return ( ( (Lat     )*110683.9) - 2510517.7 );
}
double ETM_X2Long(double X, double Y)
{
    /****** Approximate : ETM ---to--> LAT/LONG ******/
    return ( (X-807853.0)/(96426.5) + 33.0 );
}
double ETM_Y2Lat(double X, double Y)
{
    /****** Approximate : ETM ---to--> LAT/LONG ******/
    return ( (Y+2510517.7)/(110683.9) );
}



double UTM2ETM_X(double X, double Y)
{
    /****** Approximate : UTM ---to-->  ETM ******/
    return ( X + 307853.0 );
}
double UTM2ETM_Y(double X, double Y)
{
    /****** Approximate : UTM ---to-->  ETM ******/
    return ( Y - 2510517.7 );
}
double ETM2UTM_X(double X, double Y)
{
    /****** Approximate : ETM ---to-->  UTM ******/
    return ( X - 307853.0 );
}
double ETM2UTM_Y(double X, double Y)
{
    /****** Approximate : ETM ---to-->  UTM ******/
    return ( Y + 2510517.7 );
}



/*-------------------------------- toUTM() ------------------------*/
double toUTM(double LAMDA, double PHI, int flag)
{
	double     X,Y;
	double     K0;
	int        Zone;
	double     LAMDA0,dLAMDA;
	double     J,N1,N2;
	double     tanPHI2,tanPHI4,cosPHI2;
	double     Sphi;

	LAMDA = LAMDA*PI180;
	PHI   =   PHI*PI180;

	K0 = 0.9996;
	Zone = (int)(((double)((double)180.0+(double)(LAMDA/PI180))/(double)(6.0))) + 1;
	LAMDA0 = (double)Zone*6.0 - 3.0 - 180.0;
	LAMDA0 = LAMDA0*PI180;
	dLAMDA = LAMDA - LAMDA0;
	J = dLAMDA*cos(PHI);
	N1 = N*K0;
	N2 = N/M;
	tanPHI2 = tan(PHI)*tan(PHI);
	tanPHI4 = tanPHI2*tanPHI2;
	cosPHI2 = cos(PHI)*cos(PHI);

	X = 500000.0 +
	    N1*J*
	    ( 1.0 + (J*J/6.0)*( (N2-tanPHI2) + (J*J/20.0)*(5.0 - 18.0*tanPHI2 + tanPHI4) ) );
	Sphi = R*K0*
	    (PHI - (0.00513100463)*sin(PHI)*cos(PHI)*
	    (1.0 - (0.00428023)*cosPHI2*(1.0 - (0.005282)*cosPHI2)) );
	Y = Sphi + N1*J*J*tan(PHI)*(0.5 + (J*J/24.0)*(5.0 - tanPHI2));
	if (PHI < 0.0)
		Y = Y + 10000000.0;

	switch(flag)
	{
	case 1:
		return(X);
		break;
	case 2:
		return(Y);
		break;
	case 3:
		return((double)(Zone));
		break;
	default:
		return(X);
		break;
	}

}
/*-------------------------------- fromUTM() --------------------*/
double fromUTM(double X, double Y, int Zone, int flag)
{
	double     X1,Lat1,PHI;
	double     Lat,Long;
	double     K0;
	double     LAMDA0;
	double     w,K;
	double     N1,N2;
	double     meu;
	double     tanPHI2,tanPHI4;

	/***  for Southern hemisphere, use (-ve) zone number ***/
	if (Zone < 0)
	{
		Zone = Zone * (-1);
		Y = Y - 10000000.0;
	}
	K0 = 0.9996;
	LAMDA0 = (double)Zone*6.0 - 3.0 - 180.0;
	LAMDA0 = LAMDA0*PI180;
	X1 = X - 500000.0;
	w = Y/(a*K0);
	Lat1 = w +
	    (0.00510481200)*sin(w)*cos(w)*
	    (1.0 + (0.00594222)*cos(w)*cos(w)*(1.0 + (0.008248)*cos(w)*cos(w)));
	PHI = Lat1;
	tanPHI2 = tan(PHI)*tan(PHI);
	tanPHI4 = tanPHI2*tanPHI2;
	K = 1/(N*M);
	N1 = N*K0;
	N2 = N/M;
	meu = (X1*X1*tan(PHI)*K/2.0)*(1.0 - X1*X1*(5.0 + 3.0*tanPHI2)/(12.0*N1*N1));
	Lat = Lat1 - meu;
	Long = LAMDA0 +
	    (X1/(N1*cos(PHI)))*
	    (1.0 - ((X1*X1)/(6.0*N1*N1))*
	    ( (N2+2.0*tanPHI2) - ((X1*X1)/(20.0*N1*N1))*(5.0+28.0*tanPHI2+24.0*tanPHI4) ));

	switch(flag)
	{
	case 1:
		return(Long/PI180);
		break;
	case 2:
		return(Lat/PI180);
		break;
	default:
		return(Long/PI180);
		break;
	}


}


/*-------------------------------- toTM() -------------------------*/
double toTM(double LAMDA, double PHI, double Longo, double Lato, double Xo, double Yo, int flag)
{
	double     X,Y;
	double     K0;
	double     LAMDA0,dLAMDA;
	double     J,N1,N2;
	double     tanPHI2,tanPHI4,cosPHI2;
	double     Sphi;
	double     Yorigin;

	LAMDA = LAMDA*PI180;
	PHI   =   PHI*PI180;
	Longo = Longo*PI180;
	Lato  =  Lato*PI180;

	K0 = 0.9996;
	LAMDA0 = Longo;
	dLAMDA = LAMDA - LAMDA0;
	J = dLAMDA*cos(PHI);
	N1 = N*K0;
	N2 = N/M;
	tanPHI2 = tan(PHI)*tan(PHI);
	tanPHI4 = tanPHI2*tanPHI2;
	cosPHI2 = cos(PHI)*cos(PHI);

	X = Xo +
	    N1*J*
	    ( 1.0 + (J*J/6.0)*( (N2-tanPHI2) + (J*J/20.0)*(5.0 - 18.0*tanPHI2 + tanPHI4) ) );
	Sphi = R*K0*
	    ( PHI - (0.00513100463)*sin(PHI)*cos(PHI)*
	    (1.0 - (0.00428023)*cosPHI2*(1.0 - (0.005282)*cosPHI2)) );
	Y = Yo + Sphi + N1*J*J*tan(PHI)*(0.5 + (J*J/24.0)*(5.0 - tanPHI2));

	/*** calculate Y origin ***/
	PHI = Lato;
	LAMDA = Longo;
	K0 = 0.9996;
	LAMDA0 = Longo;
	dLAMDA = LAMDA - LAMDA0;
	J = dLAMDA*cos(PHI);
	N1 = N*K0;
	N2 = N/M;
	tanPHI2 = tan(PHI)*tan(PHI);
	tanPHI4 = tanPHI2*tanPHI2;
	cosPHI2 = cos(PHI)*cos(PHI);
	Sphi = R*K0*
	    ( PHI - (0.00513100463)*sin(PHI)*cos(PHI)*
	    (1.0 - (0.00428023)*cosPHI2*(1.0 - (0.005282)*cosPHI2)) );
	Yorigin = Sphi + N1*J*J*tan(PHI)*(0.5 + (J*J/24.0)*(5.0 - tanPHI2));
	Y = Y - Yorigin;

	switch(flag)
	{
	case 1:
		return(X);
		break;
	case 2:
		return(Y);
		break;
	default:
		return(X);
		break;
	}

}

/*-------------------------------- fromTM() -----------------------*/
double fromTM(double X, double Y, double Longo, double Lato, double Xo, double Yo, int flag)
{
	double     X1,Lat1,PHI;
	double     Lat,Long;
	double     K0;
	double     LAMDA0;
	double     w,K;
	double     N1,N2;
	double     meu;
	double     tanPHI2,tanPHI4;

	Longo = Longo*PI180;
	Lato  =  Lato*PI180;

	K0 = 0.9996;
	LAMDA0 = Longo;
	X1 = X - Xo;
	w = (Y-Yo)/(a*K0);
	Lat1 = w +
	    (0.00510481200)*sin(w)*cos(w)*
	    (1.0 + (0.00594222)*cos(w)*cos(w)*(1.0 + (0.008248)*cos(w)*cos(w)));
	PHI = Lat1;
	tanPHI2 = tan(PHI)*tan(PHI);
	tanPHI4 = tanPHI2*tanPHI2;
	K = 1/(N*M);
	N1 = N*K0;
	N2 = N/M;
	meu = (X1*X1*tan(Lat1)*K/2.0)*(1.0 - X1*X1*(5.0 + 3.0*tanPHI2)/(12.0*N1*N1));
	Lat = Lato + Lat1 - meu;

	/*** calculate Long origin using Total Y   !!! ***/
	w = (Y)/(a*K0);
	Lat1 = w +
	    (0.00510481200)*sin(w)*cos(w)*
	    (1.0 + (0.00594222)*cos(w)*cos(w)*(1.0 + (0.008248)*cos(w)*cos(w)));
	PHI = Lat;
	tanPHI2 = tan(PHI)*tan(PHI);
	tanPHI4 = tanPHI2*tanPHI2;
	K = 1/(N*M);
	N1 = N*K0;
	N2 = N/M;
	Long = LAMDA0 +
	    (X1/(N1*cos(PHI)))*
	    (1.0 - ((X1*X1)/(6.0*N1*N1))*
	    ( (N2+2.0*tanPHI2) - ((X1*X1)/(20.0*N1*N1))*(5.0+28.0*tanPHI2+24.0*tanPHI4) ));

	switch(flag)
	{
	case 1:
		return(Long/PI180);
		break;
	case 2:
		return(Lat/PI180);
		break;
	default:
		return(Long/PI180);
		break;
	}


}



/*================================ toUTMa() =======================*/
double toUTMa(double LAMDA, double PHI, int flag)
{
	double     X,Y;
	double     K0;
	int        Zone;
	double     LAMDA0,dLAMDA;
	double     Sphi;
	double     eps2,eps4,eps6;
	double     A0,A1,A2,A3;
	double     e2,e4,e6;
	double     t2,t4,t6;
	double     d,d2,d3,d4,d5,d6;
	double     c,c2,c3,c4,c5,c6;
	double     dALPHA;
	double     k;
	double     temp;

	LAMDA = LAMDA*PI180;
	PHI   =   PHI*PI180;

	K0 = 0.9996;
	Zone = (int)(((double)((double)180.0+(double)(LAMDA/PI180))/(double)(6.0))) + 1;
	LAMDA0 = (double)Zone*6.0 - 3.0 - 180.0;
	LAMDA0 = LAMDA0*PI180;
	dLAMDA = LAMDA - LAMDA0;

	eps2 = eps*eps;
	eps4 = eps2*eps2;
	eps6 = eps2*eps2*eps2;
	A0 = (1.0) - (1.0/4.0)*eps2 - ( 3.0/ 64.0)*eps4 - ( 5.0/ 256.0)*eps6;
	A1 =         (3.0/8.0)*eps2 + ( 3.0/ 32.0)*eps4 + (45.0/1024.0)*eps6;
	A2 =                          (15.0/256.0)*eps4 + (45.0/1024.0)*eps6;
	A3 =                                              (35.0/3072.0)*eps6;
	Sphi = a*( A0*PHI - A1*sin(2*PHI) + A2*sin(4*PHI) - A3*sin(6*PHI) );

	t2 = tan(PHI)*tan(PHI);
	t4 = t2*t2;
	t6 = t2*t2*t2;
	e2 = eps2*cos(PHI)*cos(PHI)/(1.0-eps2);
	e4 = e2*e2;
	e6 = e2*e2*e2;
	d  = dLAMDA;
	d2 = d*d;
	d3 = d*d*d;
	d4 = d*d*d*d;
	d5 = d*d*d*d*d;
	d6 = d*d*d*d*d*d;
	c  = cos(PHI);
	c2 = c*c;
	c3 = c*c*c;
	c4 = c*c*c*c;
	c5 = c*c*c*c*c;
	c6 = c*c*c*c*c*c;

	X = 500000.0+
	    N*K0*( (d*c        )+
	    (d3*c3/6.0  )*(1.0 - t2 + e2)+
	    (d5*c5/120.0)*(5.0 - 18.0*t2 + t4 + 14.0*e2 - 58.0*t2*e2 + 13*e4) );

	Y = N*K0*( (Sphi/N)+
	    (d2*sin(PHI)*c /2.0      )+
	    (d4*sin(PHI)*c3/24.0     )*(5.0 - t2 + 9.0*e2 + 4.0*e4)+
	    (d6*sin(PHI)*c5/720.0    )*(61.0 - 58.0*t2 + t4 + 270.0*e2 - 330.0*t2*e2 + 445.0*e4) );
	if (PHI < 0.0)
		Y = Y + 10000000.0;
	/***----------------------------------------------------------------***/
	/*** Now, claculate :                                               ***/
	/*** [1] Meridans convergence, which is the difference between      ***/
	/***     Grid North and Geodetic North at this point .              ***/
	/*** [2] Scale factor (k);                                          ***/
	/***----------------------------------------------------------------***/
	dALPHA = d*sin(PHI)*( 1.0 + d2*c2*(1.0+3.0*e2)/3.0 + d4*c4*(2.0-t2)/15.0 );
	k = 1.0 + d2*c2*(1.0+e2)/2.0 +
	    d4*c4*(5.0-4.0*t2+14.0*e2+13.0*e4-28.0*t2*e2+4.0*e6-48.0*t2*e4-24.0*t2*e6)/24.0 +
	    d6*c6*(61.0-148.0*t2+16.0*t4)/720.0 ;
	k = k*K0;

	switch(flag)
	{
	case 1:
		return(X);
		break;
	case 2:
		return(Y);
		break;
	case 3:
		return((double)(Zone));
		break;
	case 4:
		return(dALPHA/PI180);
		break;
	case 5:
		return(k);
		break;
	default:
		return(X);
		break;
	}

}
/*================================ toUTMfz() =======================*/
double toUTMfz(double LAMDA, double PHI, int Zone, int flag)
{
	double     X,Y;
	double     K0;
	double     LAMDA0,dLAMDA;
	double     Sphi;
	double     eps2,eps4,eps6;
	double     A0,A1,A2,A3;
	double     e2,e4,e6;
	double     t2,t4,t6;
	double     d,d2,d3,d4,d5,d6;
	double     c,c2,c3,c4,c5,c6;
	double     dALPHA;
	double     k;
	double     temp;

	LAMDA = LAMDA*PI180;
	PHI   =   PHI*PI180;

	K0 = 0.9996;
	LAMDA0 = (double)Zone*6.0 - 3.0 - 180.0;
	LAMDA0 = LAMDA0*PI180;
	dLAMDA = LAMDA - LAMDA0;

	eps2 = eps*eps;
	eps4 = eps2*eps2;
	eps6 = eps2*eps2*eps2;
	A0 = (1.0) - (1.0/4.0)*eps2 - ( 3.0/ 64.0)*eps4 - ( 5.0/ 256.0)*eps6;
	A1 =         (3.0/8.0)*eps2 + ( 3.0/ 32.0)*eps4 + (45.0/1024.0)*eps6;
	A2 =                          (15.0/256.0)*eps4 + (45.0/1024.0)*eps6;
	A3 =                                              (35.0/3072.0)*eps6;
	Sphi = a*( A0*PHI - A1*sin(2*PHI) + A2*sin(4*PHI) - A3*sin(6*PHI) );

	t2 = tan(PHI)*tan(PHI);
	t4 = t2*t2;
	t6 = t2*t2*t2;
	e2 = eps2*cos(PHI)*cos(PHI)/(1.0-eps2);
	e4 = e2*e2;
	e6 = e2*e2*e2;
	d  = dLAMDA;
	d2 = d*d;
	d3 = d*d*d;
	d4 = d*d*d*d;
	d5 = d*d*d*d*d;
	d6 = d*d*d*d*d*d;
	c  = cos(PHI);
	c2 = c*c;
	c3 = c*c*c;
	c4 = c*c*c*c;
	c5 = c*c*c*c*c;
	c6 = c*c*c*c*c*c;

	X = 500000.0+
	    N*K0*( (d*c        )+
	    (d3*c3/6.0  )*(1.0 - t2 + e2)+
	    (d5*c5/120.0)*(5.0 - 18.0*t2 + t4 + 14.0*e2 - 58.0*t2*e2 + 13*e4) );

	Y = N*K0*( (Sphi/N)+
	    (d2*sin(PHI)*c /2.0      )+
	    (d4*sin(PHI)*c3/24.0     )*(5.0 - t2 + 9.0*e2 + 4.0*e4)+
	    (d6*sin(PHI)*c5/720.0    )*(61.0 - 58.0*t2 + t4 + 270.0*e2 - 330.0*t2*e2 + 445.0*e4) );
	if (PHI < 0.0)
		Y = Y + 10000000.0;
	/***----------------------------------------------------------------***/
	/*** Now, claculate :                                               ***/
	/*** [1] Meridans convergence, which is the difference between      ***/
	/***     Grid North and Geodetic North at this point .              ***/
	/*** [2] Scale factor (k);                                          ***/
	/***----------------------------------------------------------------***/
	dALPHA = d*sin(PHI)*( 1.0 + d2*c2*(1.0+3.0*e2)/3.0 + d4*c4*(2.0-t2)/15.0 );
	k = 1.0 + d2*c2*(1.0+e2)/2.0 +
	    d4*c4*(5.0-4.0*t2+14.0*e2+13.0*e4-28.0*t2*e2+4.0*e6-48.0*t2*e4-24.0*t2*e6)/24.0 +
	    d6*c6*(61.0-148.0*t2+16.0*t4)/720.0 ;
	k = k*K0;

	switch(flag)
	{
	case 1:
		return(X);
		break;
	case 2:
		return(Y);
		break;
	case 3:
		return((double)(Zone));
		break;
	case 4:
		return(dALPHA/PI180);
		break;
	case 5:
		return(k);
		break;
	default:
		return(X);
		break;
	}

}

/*================================ fromUTMa() ===================*/
double fromUTMa(double X, double Y, int Zone, int flag)
{
	double     X1,Y1,PHI1,PHI;
	double     Lat,Long;
	double     K0;
	double     LAMDA0;
	double     Sphi;
	double     eps2,eps4,eps6;
	double     A0,A1,A2,A3;
	double     R1,N1;
	double     e2;
	double     t,t2,t4;
	double     dLAMDA,dPHI;


	/***  for Southern hemisphere, use (-ve) zone number ***/
	if (Zone < 0)
	{
		Zone = Zone * (-1);
		Y = Y - 10000000.0;
	}
	K0 = 0.9996;
	LAMDA0 = (double)Zone*6.0 - 3.0 - 180.0;
	LAMDA0 = LAMDA0*PI180;
	X1 = (X - 500000.0)/K0;

	/***----------------------------------------------------------------***/
	/*** solve for foot point latitude by iteration using : Sphi = Y/Ko ***/
	/***----------------------------------------------------------------***/
	/*** for northen hemishepre : Y    ranges from 0 .. 10000000        ***/
	/***                          Lat  ranges from 0 .. 90              ***/
	/***                          approx Lat = Y / 10000000 * 90        ***/
	/*** the same may be applied for southern hemisphere .              ***/
	/***----------------------------------------------------------------***/
	eps2 = eps*eps;
	eps4 = eps2*eps2;
	eps6 = eps2*eps2*eps2;
	A0 = (1.0) - (1.0/4.0)*eps2 - ( 3.0/ 64.0)*eps4 - ( 5.0/ 256.0)*eps6;
	A1 =         (3.0/8.0)*eps2 + ( 3.0/ 32.0)*eps4 + (45.0/1024.0)*eps6;
	A2 =                          (15.0/256.0)*eps4 + (45.0/1024.0)*eps6;
	A3 =                                              (35.0/3072.0)*eps6;
	PHI = Y*(90.0/10000000.0)*PI180;
	Y1 = 0;
	while( (abs(Y-Y1)>100) && ((PHI/PI180)<90) )
	{
		Sphi = a*( A0*PHI - A1*sin(2*PHI) + A2*sin(4*PHI) - A3*sin(6*PHI) );
		Y1 = Sphi*K0;
		if (PHI < 0.0)
		   PHI -= 0.00001;
		else
		   PHI += 0.00001;
	}
	if (PHI < 0.0)
	   PHI += 0.00001;
	else
	   PHI -= 0.00001;

	t  = tan(PHI);
	t2 = t*t;
	t4 = t2*t2;
	e2 = eps2*cos(PHI)*cos(PHI)/(1.0-eps2);
	N1 = N;
	R1 = M;
	dPHI = t*(-(X1*X1)/(2.0*R1*N1) + (X1*X1*X1*X1)/(24.0*R1*N1*N1*N1)*(5.0+3.0*t2));
	dLAMDA = (1.0/cos(PHI))*( (X1/N1) - (1/6.0)*(pow((X1/N1),3.0))*(1.0+2.0*t2+e2) +
	    (1/120.0)*(pow((X1/N1),5.0))*(5.0+28.0*t2+24.0*t4) );
	Lat  = dPHI   + PHI;
	Long = dLAMDA + LAMDA0;

	switch(flag)
	{
	case 1:
		return(Long/PI180);
		break;
	case 2:
		return(Lat/PI180);
		break;
	default:
		return(Long/PI180);
		break;
	}


}



/*-------------------------------- toETM() ------------------------*/
double toETM(double Long, double Lat, int flag)
{
	double   X,Y;

	X = toTM(Long, Lat, (31.0), (30.0), (615000.0), (810000.0), 1);
	Y = toTM(Long, Lat, (31.0), (30.0), (615000.0), (810000.0), 2);
	switch(flag)
	{
	case 1:
		return(X);
		break;
	case 2:
		return(Y);
		break;
	default:
		return(X);
		break;
	}
}
/*-------------------------------- fromETM() --------------------*/
double fromETM(double X, double Y, int flag)
{
 double  Long, Lat ;

 Long = fromTM(X, Y, (31.0), (30.0), (615000.0), (810000.0), 1);
 Lat  = fromTM(X, Y, (31.0), (30.0), (615000.0), (810000.0), 2);

 switch(flag)
       {
	case 1:
		return(Long);
		break;
	case 2:
		return(Lat);
		break;
	default:
		return(Long);
		break;
       }
}
