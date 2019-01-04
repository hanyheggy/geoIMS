/*------------------------------------------------------------------------*/
/*                 geoIMS  DXF Import/Export (geoIMS_dxfio.c )            */
/*------------------------------------------------------------------------*/

/*------------------------------------------------------------------------*/
/*                          Standard Include Files                        */
/*------------------------------------------------------------------------*/
#include "include/geoIMSextern.h"

/*------------------------------------------------------------------------*/
/*                           Functions Prototypes                         */
/*------------------------------------------------------------------------*/
void read_line()      ;
void read_pline()     ;
void read_vertex()    ;
void read_text()      ;
void read_arc()       ;
void read_circle()    ;

void write_line()     ;
void write_pline()    ;
void write_text()     ;

void check_layer()    ;
void check_font()     ;
void check_linetype() ;

/*------------------------------------------------------------------------*/
/*                   Global Variable Definition                           */
/*------------------------------------------------------------------------*/
float unit_factor = 10. ;   /* 10000. for reading DXF in KM & DBU = DM */
                            /* 10.    for reading DXF in M  & DBU = DM */
                            /* 1.     for reading DXF in DM & DBU = DM */
                            /* .1     for reading DXF in CM & DBU = DM */
                            /* .01    for reading DXF in MM & DBU = DM */

/*------------------------------------------------------------------------*/
/*                                dxfin()                                 */
/*------------------------------------------------------------------------*/
void dxfin()
{
 short process_entities ;

 
 switch(DB_UNIT)
       {
        case MM:
                switch(DXF_DB_UNIT)
                      {
                       case MM: unit_factor = 1.      ; break;
                       case CM: unit_factor = 10.     ; break;
                       case DM: unit_factor = 100.    ; break;
                       case  M: unit_factor = 1000.   ; break;
                       case KM: unit_factor = 1000000.; break;
                      }
                 break;

        case CM:
                switch(DXF_DB_UNIT)
                      {
                       case MM: unit_factor = .1      ; break;
                       case CM: unit_factor = 1.      ; break;
                       case DM: unit_factor = 10.     ; break;
                       case  M: unit_factor = 100.    ; break;
                       case KM: unit_factor = 100000. ; break;
                      }
                break;

        case DM:
                switch(DXF_DB_UNIT)
                      {
                       case MM: unit_factor = .01    ; break;
                       case CM: unit_factor = .1     ; break;
                       case DM: unit_factor = 1.     ; break;
                       case  M: unit_factor = 10.    ; break;
                       case KM: unit_factor = 10000. ; break;
                      }
                break;

        case  M:
                switch(DXF_DB_UNIT)
                      {
                       case MM: unit_factor = .001   ; break;
                       case CM: unit_factor = .01    ; break;
                       case DM: unit_factor = .1     ; break;
                       case  M: unit_factor = 1.     ; break;
                       case KM: unit_factor = 1000.  ; break;
                      }
                break;

        case KM:
                switch(DXF_DB_UNIT)
                      {
                       case MM: unit_factor = .000001; break;
                       case CM: unit_factor = .00001 ; break;
                       case DM: unit_factor = .0001  ; break;
                       case  M: unit_factor = .001   ; break;
                       case KM: unit_factor = 1.     ; break;
                      }
                break;

       }  /* END OF Switch */  


 fp_i = fopen (InputFile,"rt");
 if  ( fp_i == NULL )
     {
      fprintf (stderr,"ERROR : Can't open DXF input file \n");
      return ;
     }

 fprintf (stdout,"INFO  : Processing DXF input file ..." );

 i          = 0         ;    /* Used for workspace Merge */
 xy_index   = xy_LAST   ;
 text_index = text_LAST ;
 process_entities = 0   ;

 do
  {
   rc = fscanf(fp_i,"%d", &dxf.code );
        fscanf(fp_i,"%s", &dxf.value);

   if ( process_entities == 0 )
      {
       if ( strcmp(dxf.value , "ENTITIES") == 0 )
          {
           process_entities = 1 ;
          }
      }
   else
      {
       switch (dxf.code)
              {
               case 0:

                     if ( strcmp(dxf.value , "LINE") == 0 )
                        {
                         read_line ();
                         break ;
                        }

                else if ( strcmp(dxf.value , "POLYLINE") == 0 )
                        {
                         read_pline ();
                         break ;
                        }

                else if ( strcmp(dxf.value , "TEXT") == 0 )
                        {
                         read_text ();
                         break ;
                        }

                else if ( strcmp(dxf.value , "ARC") == 0 )
                        {
                         read_arc ();
                         break ;
                        }

                else if ( strcmp(dxf.value , "CIRCLE") == 0 )
                        {
                         read_circle ();
                         break ;
                        }
                break ;


               default:
                break ;
              }
      }

 }  while ( rc != EOF ) ;


 fclose(fp_i);

 fprintf (stdout,"INFO  : Feature Count = [%d]\n",feat_count) ;
 
 update_layer() ;
}
/*----------------------------------------------------------------*/
/*                        Read Line                               */
/*----------------------------------------------------------------*/
void read_line ()
{
 feat_count++ ;

 feat[feat_count].num            = feat[feat_count-1].num + 1 ;
 strcpy (feat[feat_count].code ,"DXFline" )    ;  /* set default Code  */
 feat[feat_count].type           = 2           ;
 feat[feat_count].layer          = 99          ;  /* set default Layer */
 feat[feat_count].scale_range[0] = 'Y'         ;
 feat[feat_count].scale_range[1] = 'Y'         ;
 feat[feat_count].scale_range[2] = 'Y'         ;
 feat[feat_count].scale_range[3] = 'Y'         ;
 feat[feat_count].scale_range[4] = 'Y'         ;
 feat[feat_count].displayed[0]   = 'Y'         ;
 feat[feat_count].selectble[0]   = 'I'         ;  /* Record Imported from DXF */
 feat[feat_count].has_attrib[0]  = 'Y'         ;
 feat[feat_count].has_text[0]    = 'N'         ;
 feat[feat_count].color          = white.pixel ;  /* set default Color    */
 feat[feat_count].linetype       = 1           ;  /* set default linetype */
 feat[feat_count].linewidth      = 1           ;  /* set default linewidth*/
 feat[feat_count].xy_count       = 0           ;


 read_next :
 fscanf (fp_i,"%d", &dxf.code) ;

 switch (dxf.code)
	{
         case 6:
	 fscanf (fp_i,"%s" ,&dxf.linetype);
	 check_linetype();
	 goto read_next  ;

         case 8:
	 fscanf (fp_i,"%s" ,&dxf.layer);
	 check_layer() ;
	 goto read_next;

         case 39:
	 fscanf (fp_i,"%d" ,&dxf.i_value)         ;
	 feat[feat_count].linewidth = dxf.i_value ;
	 goto read_next ;

	 case 62:
	 fscanf (fp_i,"%d" ,&dxf.color);
	 switch(dxf.color)
	       {
		case 5:   feat[feat_count].color = 1 ;/*blue.pixel */ ; break;  // ImageMAgick
		case 1:   feat[feat_count].color = 2 ;/*red.pixel  */ ; break;
		case 6:   feat[feat_count].color = 3 ;/*pink.pixel */ ; break;
		case 3:   feat[feat_count].color = 4 ;/*green.pixel*/ ; break;
		case 4:   feat[feat_count].color = 5 ;/*cyan.pixel */ ; break;
		case 2:   feat[feat_count].color = 6 ;/*yellow.pixel*/; break;
		case 7:   feat[feat_count].color = 7 ;/*white.pixel */; break;
		case 9:   feat[feat_count].color = 1 ;/*blue.pixel  */; break;
		case 10:  feat[feat_count].color = 2 ;/*red.pixel  */ ; break;
		case 11:  feat[feat_count].color = 3 ;/*pink.pixel  */; break;
		case 12:  feat[feat_count].color = 4 ;/*green.pixel */; break;
		case 13:  feat[feat_count].color = 5 ;/*cyan.pixel */ ; break;
		case 14:  feat[feat_count].color = 6 ;/*yellow.pixel*/; break;
		case 8:   feat[feat_count].color = 9 ;/*gray.pixel  */; break;
		case 126: feat[feat_count].color = 11;/*brown.pixel */; break;
		case 134: feat[feat_count].color = 11;/*brown.pixel */; break;
		default:  feat[feat_count].color = 7 ;/*white.pixel */; break;
	       }
	 goto read_next;


	 case 10:
	 fscanf (fp_i,"%f" ,&dxf.x1)                   ;
	 feat[feat_count].xbase = dxf.x1 * unit_factor ;
	 goto read_next ;

	 case 20:
	 fscanf (fp_i,"%f" ,&dxf.y1)                   ;
	 feat[feat_count].ybase = dxf.y1 * unit_factor ;
	 goto read_next ;

	 case 30:
	 fscanf (fp_i,"%f" ,&dxf.z1) ;
	 goto read_next ;

	 case 11:
	 fscanf (fp_i,"%f" ,&dxf.x2)                  ;
	 feat[feat_count].xend = dxf.x2 * unit_factor ;
	 goto read_next ;

	 case 21:
	 fscanf (fp_i,"%f" ,&dxf.y2)                  ;
	 feat[feat_count].yend = dxf.y2 * unit_factor ;
	 goto read_next ;

	 case 31:
	 fscanf (fp_i,"%f" ,&dxf.z2) ;
	 goto read_next ;

	} /* end switch */


 if (dxf.code != 0)
    {
     fgets (dxf.value, 81 , fp_i );
     fgets (dxf.value, 81 , fp_i );
     goto read_next ;
    }
 else
    {
     return ;
    }
}
/*----------------------------------------------------------------*/
/*                        Read Poly Line                          */
/*----------------------------------------------------------------*/
void read_pline ()
{
 feat_count++ ;
 xy_index = xy_LAST ;

 feat[feat_count].num            = feat[feat_count-1].num + 1 ;
 strcpy (feat[feat_count].code ,"DXFpline")    ;  /* set default Code  */
 feat[feat_count].type           = 2           ;
 feat[feat_count].layer          = 99          ;  /* set default Layer */
 feat[feat_count].scale_range[0] = 'Y'         ;
 feat[feat_count].scale_range[1] = 'Y'         ;
 feat[feat_count].scale_range[2] = 'Y'         ;
 feat[feat_count].scale_range[3] = 'Y'         ;
 feat[feat_count].scale_range[4] = 'Y'         ;
 feat[feat_count].displayed[0]   = 'Y'         ;
 feat[feat_count].selectble[0]   = 'I'         ;  /* Record Imported from DXF */
 feat[feat_count].has_attrib[0]  = 'Y'         ;
 feat[feat_count].has_text[0]    = 'N'         ;
 feat[feat_count].color          = white.pixel ;  /* set default Color    */
 feat[feat_count].linetype       = 1           ;  /* set default linetype */
 feat[feat_count].linewidth      = 1           ;  /* set default linewidth*/
 feat[feat_count].xy_count       = 1           ;
 feat[feat_count].xy             = xy_index    ;

 ii = 0 ;
 dxf.pline_flag = 0 ;

 read_next :
 fscanf (fp_i,"%d", &dxf.code) ;


 switch_next :
 switch (dxf.code)
	{
	 case 0:
	 fscanf (fp_i,"%s" ,&dxf.value);
	 if ( strcmp (dxf.value , "VERTEX") == 0 )
	    {
	     read_vertex() ;
	     goto switch_next;
	    }
	 else
	 if ( strcmp (dxf.value , "SEQEND") == 0 )
	    {
	     ii--;
	     if ( dxf.pline_flag == 1 )
		{
		 feat[feat_count].xend = feat[feat_count].xbase ;
		 feat[feat_count].yend = feat[feat_count].ybase ;
		 xy_LAST = xy_LAST + ii ;
		 feat[feat_count].xy_count = ii ;
		}
	      else
		{
		 feat[feat_count].xend = x[xy_index+ii] ;
		 feat[feat_count].yend = y[xy_index+ii] ;
		 ii--;
		 xy_LAST = xy_LAST + ii ;
		 feat[feat_count].xy_count = ii ;
		}
	     return ;
	    }
	 goto read_next;


         case 6:
	 fscanf (fp_i,"%s" ,&dxf.linetype);
	 check_linetype ();
	 goto read_next;

         case 8:
	 fscanf (fp_i,"%s" ,&dxf.layer);
	 check_layer ();
	 goto read_next;

         case 39:
	 fscanf (fp_i,"%d" ,&dxf.i_value)         ;
	 feat[feat_count].linewidth = dxf.i_value ;
	 goto read_next ;

	 case 62:
	 fscanf (fp_i,"%d" ,&dxf.color);
	 switch(dxf.color)
	       {
		case 5:   feat[feat_count].color = 1 ;/*blue.pixel */ ; break;  // ImageMAgick
		case 1:   feat[feat_count].color = 2 ;/*red.pixel  */ ; break;
		case 6:   feat[feat_count].color = 3 ;/*pink.pixel */ ; break;
		case 3:   feat[feat_count].color = 4 ;/*green.pixel*/ ; break;
		case 4:   feat[feat_count].color = 5 ;/*cyan.pixel */ ; break;
		case 2:   feat[feat_count].color = 6 ;/*yellow.pixel*/; break;
		case 7:   feat[feat_count].color = 7 ;/*white.pixel */; break;
		case 9:   feat[feat_count].color = 1 ;/*blue.pixel  */; break;
		case 10:  feat[feat_count].color = 2 ;/*red.pixel  */ ; break;
		case 11:  feat[feat_count].color = 3 ;/*pink.pixel  */; break;
		case 12:  feat[feat_count].color = 4 ;/*green.pixel */; break;
		case 13:  feat[feat_count].color = 5 ;/*cyan.pixel */ ; break;
		case 14:  feat[feat_count].color = 6 ;/*yellow.pixel*/; break;
		case 8:   feat[feat_count].color = 9 ;/*gray.pixel  */; break;
		case 126: feat[feat_count].color = 11;/*brown.pixel */; break;
		case 134: feat[feat_count].color = 11;/*brown.pixel */; break;
		default:  feat[feat_count].color = 7 ;/*white.pixel */; break;
	       }
	 goto read_next ;

	 case 66:
	 fscanf (fp_i,"%s" ,&dxf.value);
	 goto read_next;

	 case 70:
	 fscanf (fp_i,"%d" ,&dxf.pline_flag);
	 goto read_next;

	} /* end switch */


 fgets (dxf.value, 81 , fp_i );
 fgets (dxf.value, 81 , fp_i );
 goto read_next ;

}
/*----------------------------------------------------------------*/
/*                        Read Vertex                             */
/*----------------------------------------------------------------*/
void read_vertex()
{
 read_next :
 fscanf (fp_i,"%d", &dxf.code) ;

 switch (dxf.code)
	{
	 case 10:
	 fscanf (fp_i,"%f" ,&dxf.x1);
	 if ( ii == 0 ) { feat[feat_count].xbase = dxf.x1 * unit_factor ; }
	 else           { x[xy_index+ii] = dxf.x1 * unit_factor ;         }
	 goto read_next ;

	 case 20:
	 fscanf (fp_i,"%f" ,&dxf.y1);
	 if ( ii == 0 ) { feat[feat_count].ybase = dxf.y1 * unit_factor ; }
	 else           { y[xy_index+ii] = dxf.y1 * unit_factor ;         }
	 goto read_next ;

	 case 30:
	 fscanf (fp_i,"%f" ,&dxf.z1);
	 goto read_next ;
	} /* end switch */

 if (dxf.code != 0)
    {
     fgets (dxf.value, 81 , fp_i );
     fgets (dxf.value, 81 , fp_i );
     goto read_next ;
    }
 else
    {
     if ( dxf.x1 > 0  &&  dxf.y1 > 0 )
	{
	 ii++   ;
	 return ;
	}
     else
	{
	 return ;            /* skip negtive, zero Vertex */
	}
    }
}
/*----------------------------------------------------------------*/
/*                        Read Text                               */
/*----------------------------------------------------------------*/
void read_text()
{
 feat_count++ ;
 text_index = text_LAST ;

 feat[feat_count].num = feat[feat_count-1].num + 1 ;
 strcpy (feat[feat_count].code ,"DXFtext")         ; /* set default Code  */
 feat[feat_count].type           =  1              ;
 feat[feat_count].layer          =  99             ; /* set default Layer */
 feat[feat_count].scale_range[0] = 'Y'             ;
 feat[feat_count].scale_range[1] = 'Y'             ;
 feat[feat_count].scale_range[2] = 'Y'             ;
 feat[feat_count].scale_range[3] = 'Y'             ;
 feat[feat_count].scale_range[4] = 'Y'             ;
 feat[feat_count].displayed[0]   = 'Y'             ;
 feat[feat_count].selectble[0]   = 'I'             ; /* Record Imported from DXF */
 feat[feat_count].has_attrib[0]  = 'Y'             ;
 feat[feat_count].has_text[0]    = 'Y'             ;
 feat[feat_count].color          =  white.pixel    ; /* set default Color     */
 feat[feat_count].linetype       =  1              ; /* set default linetype  */
 feat[feat_count].linewidth      =  1              ; /* set default linewidth */
 feat[feat_count].xy_count       =  0              ;
 feat[feat_count].text_count     =  1              ;
 feat[feat_count].text           =  text_index++   ;
 feat[feat_count].symb_size      =  30             ; /* set default size  */

 text[text_index].angle         = 0                ; /* set default angle */
 text[text_index].just          = 1                ; /* set default just  */
 text[text_index].font          = 1                ; /* set default font  */

 dxf.hz_just = 0 ;  /* reset just flags */
 dxf.vl_just = 0 ;


 read_next :
 fscanf (fp_i,"%d", &dxf.code) ;

 switch (dxf.code)
	{
         case 6:
	 fscanf (fp_i,"%s" ,&dxf.linetype);
	 check_linetype ();
	 goto read_next;

         case 7:
	 fscanf (fp_i,"%s" ,&dxf.font);
	 check_font()  ;
	 goto read_next;

         case 8:
	 fscanf (fp_i,"%s" ,&dxf.layer);
	 check_layer ();
	 goto read_next;

         case 39:
	 fscanf (fp_i,"%d" ,&dxf.i_value)         ;
	 feat[feat_count].linewidth = dxf.i_value ;
	 goto read_next ;

         case 62:
	 fscanf (fp_i,"%d" ,&dxf.color);
	 switch(dxf.color)
	       {
		case 5:   feat[feat_count].color = 1 ;/*blue.pixel */ ; break;  // ImageMAgick
		case 1:   feat[feat_count].color = 2 ;/*red.pixel  */ ; break;
		case 6:   feat[feat_count].color = 3 ;/*pink.pixel */ ; break;
		case 3:   feat[feat_count].color = 4 ;/*green.pixel*/ ; break;
		case 4:   feat[feat_count].color = 5 ;/*cyan.pixel */ ; break;
		case 2:   feat[feat_count].color = 6 ;/*yellow.pixel*/; break;
		case 7:   feat[feat_count].color = 7 ;/*white.pixel */; break;
		case 9:   feat[feat_count].color = 1 ;/*blue.pixel  */; break;
		case 10:  feat[feat_count].color = 2 ;/*red.pixel  */ ; break;
		case 11:  feat[feat_count].color = 3 ;/*pink.pixel  */; break;
		case 12:  feat[feat_count].color = 4 ;/*green.pixel */; break;
		case 13:  feat[feat_count].color = 5 ;/*cyan.pixel */ ; break;
		case 14:  feat[feat_count].color = 6 ;/*yellow.pixel*/; break;
		case 8:   feat[feat_count].color = 9 ;/*gray.pixel  */; break;
		case 126: feat[feat_count].color = 11;/*brown.pixel */; break;
		case 134: feat[feat_count].color = 11;/*brown.pixel */; break;
		default:  feat[feat_count].color = 7 ;/*white.pixel */; break;
	       }
	 goto read_next ;

	 case 10:
	 fscanf (fp_i,"%f" ,&dxf.x1);
	 text[text_index].x     = dxf.x1 * unit_factor ;
	 feat[feat_count].xbase = dxf.x1 * unit_factor ;
	 goto read_next ;

	 case 20:
	 fscanf (fp_i,"%f" ,&dxf.y1);
	 text[text_index].y     = dxf.y1 * unit_factor ;
	 feat[feat_count].ybase = dxf.y1 * unit_factor ;
	 goto read_next ;

	 case 30:
	 fscanf (fp_i,"%f" ,&dxf.z1);
	 goto read_next ;

	 case 40:
	 fscanf (fp_i,"%f" ,&dxf.f_value);
	 text[text_index].size      = dxf.f_value * unit_factor ;
	 feat[feat_count].symb_size = dxf.f_value * unit_factor ;
	 goto read_next ;

	 case 50:
	 fscanf (fp_i,"%f" ,&dxf.f_value);
	 text[text_index].angle = dxf.f_value ;
	 goto read_next ;

	 case 1:
	 fgets (dxf.value, 81 , fp_i );   /* read up to line end '\n' */
	 fgets (dxf.value, 81 , fp_i );
	 for ( i=0 ; i <= 15 ; i++)       /* delete ' ' from left & right */
	     {
	      if (dxf.value[0] == ' ')
		 {
		  for ( ii=0 ; ii <= 79 ; ii++ ) dxf.value[ii] = dxf.value[ii+1] ;
		 }
	     }
	 for ( i=0 ; i <= 49 ; i++)
	     {
	      if (( dxf.value[i] == '\n' ) ||
  /*		  ( dxf.value[i] == ''  && dxf.value[i+1] == ''  ) ||   LINUX */
		  ( dxf.value[i] == ' ' && dxf.value[i+1] == ' ' ))
		 {
		  dxf.value[i] = '\0' ; break ;
		 }
	     }
	 strcpy (text[text_index].string,dxf.value) ;
	 goto read_next ;

	 case 11:
	 fscanf (fp_i,"%f" ,&dxf.x2);
	 text[text_index].x     = dxf.x2 * unit_factor ;
	 feat[feat_count].xbase = dxf.x2 * unit_factor ;
	 goto read_next ;

	 case 21:
	 fscanf (fp_i,"%f" ,&dxf.y2);
	 text[text_index].y     = dxf.y2 * unit_factor ;
	 feat[feat_count].ybase = dxf.y2 * unit_factor ;
	 goto read_next ;

	 case 31:
	 fscanf (fp_i,"%f" ,&dxf.z2);
	 goto read_next ;

	 case 72:
	 fscanf (fp_i,"%d" ,&dxf.hz_just) ;
	 goto read_next ;

	 case 73:
	 fscanf (fp_i,"%d" ,&dxf.vl_just) ;
	 goto read_next ;

        } /* end switch */


 if (dxf.code != 0)
    {
     fgets (dxf.value, 81 , fp_i ); /* read up to '\n' */
     fgets (dxf.value, 81 , fp_i ); /* read line       */
     goto read_next ;
    }
 else
    {
	  if ( dxf.vl_just == 1 && dxf.hz_just == 0 ) text[text_index].just = 1 ;
     else if ( dxf.vl_just == 1 && dxf.hz_just == 1 ) text[text_index].just = 2 ;
     else if ( dxf.vl_just == 1 && dxf.hz_just == 2 ) text[text_index].just = 3 ;
     else if ( dxf.vl_just == 2 && dxf.hz_just == 0 ) text[text_index].just = 4 ;
     else if ( dxf.vl_just == 2 && dxf.hz_just == 1 ) text[text_index].just = 5 ;
     else if ( dxf.vl_just == 2 && dxf.hz_just == 2 ) text[text_index].just = 6 ;
     else if ( dxf.vl_just == 3 && dxf.hz_just == 0 ) text[text_index].just = 7 ;
     else if ( dxf.vl_just == 3 && dxf.hz_just == 1 ) text[text_index].just = 8 ;
     else if ( dxf.vl_just == 3 && dxf.hz_just == 2 ) text[text_index].just = 9 ;
     else if ( dxf.vl_just == 0 && dxf.hz_just == 1 ) text[text_index].just = 2 ;
     else if ( dxf.vl_just == 0 && dxf.hz_just == 2 ) text[text_index].just = 3 ;
     else if ( dxf.vl_just == 0 && dxf.hz_just == 4 ) text[text_index].just = 5 ;

     text_LAST = text_LAST + 1 ;
     return ;
    }

}
/*----------------------------------------------------------------*/
/*                        Read Arc                                */
/*----------------------------------------------------------------*/
void read_arc ()
{
 int   x_c       ;  //  X center
 int   y_c       ;  //  Y center
 int   r         ;  //  Radius
 float s_angle   ;  //  start angle
 float e_angle   ;  //  end   angle
 float hz_angle  ;  //  end   angle
 float jj        ;  //  angle counter


 feat_count++ ;
 xy_index = xy_LAST ;


 feat[feat_count].num            = feat[feat_count-1].num + 1 ;
 strcpy (feat[feat_count].code ,"DXFarc" )     ;  /* set default Code  */
 feat[feat_count].type           = 2           ;
 feat[feat_count].layer          = 99          ;  /* set default Layer */
 feat[feat_count].scale_range[0] = 'Y'         ;
 feat[feat_count].scale_range[1] = 'Y'         ;
 feat[feat_count].scale_range[2] = 'Y'         ;
 feat[feat_count].scale_range[3] = 'Y'         ;
 feat[feat_count].scale_range[4] = 'Y'         ;
 feat[feat_count].displayed[0]   = 'Y'         ;
 feat[feat_count].selectble[0]   = 'I'         ;  /* Record Imported from DXF */
 feat[feat_count].has_attrib[0]  = 'Y'         ;
 feat[feat_count].has_text[0]    = 'N'         ;
 feat[feat_count].color          = white.pixel ;  /* set default Color    */
 feat[feat_count].linetype       = 1           ;  /* set default linetype */
 feat[feat_count].linewidth      = 1           ;  /* set default linewidth*/
 feat[feat_count].xy             = xy_index    ;


 read_next :
 fscanf (fp_i,"%d", &dxf.code) ;

 switch (dxf.code)
	{
         case 6:
	 fscanf (fp_i,"%s" ,&dxf.linetype);
	 check_linetype();
	 goto read_next  ;

         case 8:
	 fscanf (fp_i,"%s" ,&dxf.layer);
	 check_layer() ;
	 goto read_next;

         case 39:
	 fscanf (fp_i,"%d" ,&dxf.i_value)         ;
	 feat[feat_count].linewidth = dxf.i_value ;
	 goto read_next ;

	 case 62:
	 fscanf (fp_i,"%d" ,&dxf.color);
	 switch(dxf.color)
	       {
		case 5:   feat[feat_count].color = 1 ;/*blue.pixel */ ; break;  // ImageMAgick
		case 1:   feat[feat_count].color = 2 ;/*red.pixel  */ ; break;
		case 6:   feat[feat_count].color = 3 ;/*pink.pixel */ ; break;
		case 3:   feat[feat_count].color = 4 ;/*green.pixel*/ ; break;
		case 4:   feat[feat_count].color = 5 ;/*cyan.pixel */ ; break;
		case 2:   feat[feat_count].color = 6 ;/*yellow.pixel*/; break;
		case 7:   feat[feat_count].color = 7 ;/*white.pixel */; break;
		case 9:   feat[feat_count].color = 1 ;/*blue.pixel  */; break;
		case 10:  feat[feat_count].color = 2 ;/*red.pixel  */ ; break;
		case 11:  feat[feat_count].color = 3 ;/*pink.pixel  */; break;
		case 12:  feat[feat_count].color = 4 ;/*green.pixel */; break;
		case 13:  feat[feat_count].color = 5 ;/*cyan.pixel */ ; break;
		case 14:  feat[feat_count].color = 6 ;/*yellow.pixel*/; break;
		case 8:   feat[feat_count].color = 9 ;/*gray.pixel  */; break;
		case 126: feat[feat_count].color = 11;/*brown.pixel */; break;
		case 134: feat[feat_count].color = 11;/*brown.pixel */; break;
		default:  feat[feat_count].color = 7 ;/*white.pixel */; break;
	       }
	 goto read_next;


	 case 10:
	 fscanf (fp_i,"%f" ,&dxf.x1) ;
	 x_c = dxf.x1 * unit_factor  ;
	 goto read_next ;

	 case 20:
	 fscanf (fp_i,"%f" ,&dxf.y1) ;
	 y_c = dxf.y1 * unit_factor  ;
	 goto read_next ;

	 case 40:
	 fscanf (fp_i,"%f" ,&dxf.f_value) ;
	 r = dxf.f_value * unit_factor    ;
	 goto read_next ;

	 case 50:
	 fscanf (fp_i,"%f" ,&dxf.f_value) ;
         s_angle = dxf.f_value / DEG2RAD ;
	 goto read_next ;

	 case 51:
	 fscanf (fp_i,"%f" ,&dxf.f_value) ;
         e_angle = dxf.f_value / DEG2RAD ;

         if ( e_angle ==  0. )
            {
             e_angle = 360. / DEG2RAD ;
            }

	 goto read_next ;

	} /* end switch */



 if (dxf.code != 0)
    {
     fgets (dxf.value, 81 , fp_i );
     fgets (dxf.value, 81 , fp_i );
     goto read_next ;
    }
 else
    {

     feat[feat_count].xbase = x_c + r * cos (s_angle);
     feat[feat_count].ybase = y_c + r * sin (s_angle);
     feat[feat_count].xend  = x_c + r * cos (e_angle);
     feat[feat_count].yend  = y_c + r * sin (e_angle);

     if ( s_angle < e_angle )
        {
         ii=1 ;
         for ( jj=s_angle+(1./DEG2RAD) ; jj<e_angle ; jj+= (1./DEG2RAD)  )
             {
              x[xy_index+ii] = x_c + r * cos (jj) ;
              y[xy_index+ii] = y_c + r * sin (jj) ;

              // jj+= (1./DEG2RAD) ;
              ii++;
             }

         ii--;
         xy_LAST = xy_LAST + ii         ;
         feat[feat_count].xy_count = ii ;
        }
      else
        {
         hz_angle = 360.0 / DEG2RAD ;

         ii=1 ;
         for ( jj=s_angle+(1./DEG2RAD) ; jj< hz_angle ;   )
             {
              x[xy_index+ii] = x_c + r * cos (jj) ;
              y[xy_index+ii] = y_c + r * sin (jj) ;

              jj+= (1./DEG2RAD) ;
              ii++;
             }

         for ( jj=0 ; jj<e_angle ;   )
             {
              x[xy_index+ii] = x_c + r * cos (jj) ;
              y[xy_index+ii] = y_c + r * sin (jj) ;

              jj+= (1./DEG2RAD) ;
              ii++;
             }

         ii--;
         xy_LAST = xy_LAST + ii         ;
         feat[feat_count].xy_count = ii ;
        }

     return ;
    }
}
/*----------------------------------------------------------------*/
/*                        Read Circle                             */
/*----------------------------------------------------------------*/
void read_circle ()
{
 int    x_c      ;  //  X center
 int    y_c      ;  //  Y center
 int    r        ;  //  Radius
 float  jj       ;  //  angle counter


 feat_count++ ;
 xy_index = xy_LAST ;


 feat[feat_count].num            = feat[feat_count-1].num + 1 ;
 strcpy (feat[feat_count].code ,"DXFcircle" )  ;  /* set default Code  */
 feat[feat_count].type           = 2           ;
 feat[feat_count].layer          = 99          ;  /* set default Layer */
 feat[feat_count].scale_range[0] = 'Y'         ;
 feat[feat_count].scale_range[1] = 'Y'         ;
 feat[feat_count].scale_range[2] = 'Y'         ;
 feat[feat_count].scale_range[3] = 'Y'         ;
 feat[feat_count].scale_range[4] = 'Y'         ;
 feat[feat_count].displayed[0]   = 'Y'         ;
 feat[feat_count].selectble[0]   = 'I'         ;  /* Record Imported from DXF */
 feat[feat_count].has_attrib[0]  = 'Y'         ;
 feat[feat_count].has_text[0]    = 'N'         ;
 feat[feat_count].color          = white.pixel ;  /* set default Color    */
 feat[feat_count].linetype       = 1           ;  /* set default linetype */
 feat[feat_count].linewidth      = 1           ;  /* set default linewidth*/
 feat[feat_count].xy             = xy_index    ;


 read_next :
 fscanf (fp_i,"%d", &dxf.code) ;

 switch (dxf.code)
	{
         case 6:
	 fscanf (fp_i,"%s" ,&dxf.linetype);
	 check_linetype();
	 goto read_next  ;

         case 8:
	 fscanf (fp_i,"%s" ,&dxf.layer);
	 check_layer() ;
	 goto read_next;

         case 39:
	 fscanf (fp_i,"%d" ,&dxf.i_value)         ;
	 feat[feat_count].linewidth = dxf.i_value ;
	 goto read_next ;

	 case 62:
	 fscanf (fp_i,"%d" ,&dxf.color);
	 switch(dxf.color)
	       {
		case 5:   feat[feat_count].color = 1 ;/*blue.pixel */ ; break;  // ImageMAgick
		case 1:   feat[feat_count].color = 2 ;/*red.pixel  */ ; break;
		case 6:   feat[feat_count].color = 3 ;/*pink.pixel */ ; break;
		case 3:   feat[feat_count].color = 4 ;/*green.pixel*/ ; break;
		case 4:   feat[feat_count].color = 5 ;/*cyan.pixel */ ; break;
		case 2:   feat[feat_count].color = 6 ;/*yellow.pixel*/; break;
		case 7:   feat[feat_count].color = 7 ;/*white.pixel */; break;
		case 9:   feat[feat_count].color = 1 ;/*blue.pixel  */; break;
		case 10:  feat[feat_count].color = 2 ;/*red.pixel  */ ; break;
		case 11:  feat[feat_count].color = 3 ;/*pink.pixel  */; break;
		case 12:  feat[feat_count].color = 4 ;/*green.pixel */; break;
		case 13:  feat[feat_count].color = 5 ;/*cyan.pixel */ ; break;
		case 14:  feat[feat_count].color = 6 ;/*yellow.pixel*/; break;
		case 8:   feat[feat_count].color = 9 ;/*gray.pixel  */; break;
		case 126: feat[feat_count].color = 11;/*brown.pixel */; break;
		case 134: feat[feat_count].color = 11;/*brown.pixel */; break;
		default:  feat[feat_count].color = 7 ;/*white.pixel */; break;
	       }
	 goto read_next;


	 case 10:
	 fscanf (fp_i,"%f" ,&dxf.x1) ;
	 x_c = dxf.x1 * unit_factor  ;
	 goto read_next ;

	 case 20:
	 fscanf (fp_i,"%f" ,&dxf.y1) ;
	 y_c = dxf.y1 * unit_factor  ;
	 goto read_next ;

	 case 40:
	 fscanf (fp_i,"%f" ,&dxf.f_value) ;
	 r = dxf.f_value * unit_factor    ;
	 goto read_next ;

        } /* end switch */


 if (dxf.code != 0)
    {
     fgets (dxf.value, 81 , fp_i );
     fgets (dxf.value, 81 , fp_i );
     goto read_next ;
    }
 else
    {
     feat[feat_count].xbase = x_c + r ;
     feat[feat_count].ybase = y_c     ;

     feat[feat_count].xend  = x_c + r ;
     feat[feat_count].yend  = y_c     ;


     ii=1 ;
     for ( jj=(1./DEG2RAD) ; jj<=(360./DEG2RAD) ;   )
         {
          x[xy_index+ii] = x_c + r * cos (jj) ;
          y[xy_index+ii] = y_c + r * sin (jj) ;

          jj+= (1./DEG2RAD) ;
          ii++;
         }

     ii--;
     xy_LAST = xy_LAST + ii         ;
     feat[feat_count].xy_count = ii ;

     return ;
    }
}
/*------------------------------------------------------------------------*/
/*                               dxfout()                                 */
/*------------------------------------------------------------------------*/
dxfout()
{
 strcpy ( OutputFile , "saved.dxf" ) ;

 fp_o=fopen(OutputFile,"wt");
 if  ( fp_i== NULL )
     {
      printf ("\n  Can't open output file  ! ") ;
      return ;
     }

 printf ("\n  processing output file ..." );

 fprintf ( fp_o ,"0   \nSECTION"  ) ;  /* Begin Section  */
 fprintf ( fp_o ,"\n2 \nENTITIES" ) ;  /* Entities       */


 for (i=1 ; i<=feat_count ; i++)
     {
	   if (feat[i].color == blue.pixel   )  dxf.color = 5 ;
      else if (feat[i].color == red.pixel    )  dxf.color = 1 ;
      else if (feat[i].color == pink.pixel   )  dxf.color = 6 ;
      else if (feat[i].color == green.pixel  )  dxf.color = 3 ;
      else if (feat[i].color == cyan.pixel   )  dxf.color = 4 ;
      else if (feat[i].color == yellow.pixel )  dxf.color = 2 ;
      else if (feat[i].color == white.pixel  )  dxf.color = 7 ;
      else                                      dxf.color = 7 ;

      switch(feat[i].linetype)
            {
             case 1:   strcpy (dxf.linetype , "CONTINUOUS"); break;
             case 2:   strcpy (dxf.linetype , "DASH")      ; break;
             case 3:   strcpy (dxf.linetype , "DOT")       ; break;
             case 4:   strcpy (dxf.linetype , "DASHDOT")   ; break;
             case 5:   strcpy (dxf.linetype , "DASHDOTDOT"); break;
             default:  strcpy (dxf.linetype , "CONTINUOUS"); break;
            }


	    if ( feat[i].type == 1 )
	       {
		if ( feat[i].has_text[0] == 'Y' )
		   {
		    for (ii=1 ; ii<= feat[i].text_count ; ii++)
			{
			 text_index = feat[i].text + ii ;
			 write_text () ;
			}
		   }
		/* write_block () ;  --> symbol  */
	       }

      else if ( feat[i].type == 2  &&  feat[i].xy_count == 0 )
	      {
	       if ( feat[i].has_text[0] == 'Y' )
		  {
		   for (ii=1 ; ii<= feat[i].text_count ; ii++)
		       {
			text_index = feat[i].text + ii ;
			write_text () ;
		       }
		  }
	       write_line () ;
	      }

      else if ( feat[i].type == 2  &&  feat[i].xy_count > 0 )
	      {
	       if ( feat[i].has_text[0] == 'Y' )
		  {
		   for (ii=1 ; ii<= feat[i].text_count ; ii++)
		       {
			text_index = feat[i].text + ii ;
			write_text () ;
		       }
		  }
	       write_pline () ;
	      }


     } /* main loop */


 fprintf ( fp_o ,"\n0 \nENDSEC" ) ;    /* End section    */
 fprintf ( fp_o ,"\n0 \nEOF"    ) ;    /* write EOF      */


 fclose(fp_o) ;
}
/*----------------------------------------------------------------*/
/*                       Write Line                               */
/*----------------------------------------------------------------*/
void write_line ()
{
 dxf.x1 = feat[i].xbase   ;
 dxf.y1 = feat[i].ybase   ;
 dxf.x2 = feat[i].xend    ;
 dxf.y2 = feat[i].yend    ;

 fprintf ( fp_o ,"\n0  \nLINE"                 ); /* LINE       */
 fprintf ( fp_o ,"\n6  \n%s" ,dxf.linetype     ); /* Line Type  */
 fprintf ( fp_o ,"\n8  \n%d" ,feat[i].layer    ); /* Layer      */
 fprintf ( fp_o ,"\n39 \n%d" ,feat[i].linewidth); /* Line width */
 fprintf ( fp_o ,"\n62 \n%d" ,dxf.color        ); /* Color      */
 fprintf ( fp_o ,"\n10 \n%f" ,dxf.x1           ); /* X base     */
 fprintf ( fp_o ,"\n20 \n%f" ,dxf.y1           ); /* Y base     */
 fprintf ( fp_o ,"\n11 \n%f" ,dxf.x2           ); /* X end      */
 fprintf ( fp_o ,"\n21 \n%f" ,dxf.y2           ); /* Y end      */

 return ;
}
/*----------------------------------------------------------------*/
/*                       Write Poly Line                          */
/*----------------------------------------------------------------*/
void write_pline ()
{
 if (feat[i].xbase == feat[i].xend && feat[i].ybase == feat[i].yend)
    {
     dxf.pline_flag = 1 ;  /* closed polyline     */
    }
 else
    {
     dxf.pline_flag = 0 ;  /* non closed polyline */
    }

 fprintf ( fp_o ,"\n0  \nPOLYLINE"             ); /* POLYLINE    */
 fprintf ( fp_o ,"\n6  \n%s" ,dxf.linetype     ); /* Line Type   */
 fprintf ( fp_o ,"\n8  \n%d" ,feat[i].layer    ); /* Layer       */
 fprintf ( fp_o ,"\n39 \n%d" ,feat[i].linewidth); /* Line width  */
 fprintf ( fp_o ,"\n62 \n%d" ,dxf.color        ); /* Color       */
 fprintf ( fp_o ,"\n66 \n1"                    ); /* 66 flag     */
 fprintf ( fp_o ,"\n10 \n0.0"                  ); /* x = 0.0     */
 fprintf ( fp_o ,"\n20 \n0.0"                  ); /* y = 0.0     */
 fprintf ( fp_o ,"\n70 \n%d" ,dxf.pline_flag   ); /* closed flag */

 dxf.x1 = feat[i].xbase ;
 dxf.y1 = feat[i].ybase ;

 fprintf ( fp_o ,"\n0  \nVERTEX"            ); /* last VERTEX */
 fprintf ( fp_o ,"\n8  \n%d" ,feat[i].layer ); /* Layer       */
 fprintf ( fp_o ,"\n10 \n%f" ,dxf.x1        ); /* X base      */
 fprintf ( fp_o ,"\n20 \n%f" ,dxf.y1        ); /* Y base      */


 for ( ii=1 ; ii<=feat[i].xy_count ; ii++ )
     {
      dxf.x1 = x[feat[i].xy+ii] ;
      dxf.y1 = y[feat[i].xy+ii] ;

      fprintf ( fp_o ,"\n0  \nVERTEX"            ); /* other VERTEX */
      fprintf ( fp_o ,"\n8  \n%d" ,feat[i].layer ); /* Layer        */
      fprintf ( fp_o ,"\n10 \n%f" ,dxf.x1        ); /* X coord.     */
      fprintf ( fp_o ,"\n20 \n%f" ,dxf.y1        ); /* Y coord.     */
     }

 if ( dxf.pline_flag == 0 )  /* non closed polyline */
    {
     dxf.x1 = feat[i].xend ;
     dxf.y1 = feat[i].yend ;

     fprintf ( fp_o ,"\n0  \nVERTEX"            ); /* 1 st VERTEX */
     fprintf ( fp_o ,"\n8  \n%d" ,feat[i].layer ); /* Layer       */
     fprintf ( fp_o ,"\n10 \n%f" ,dxf.x1        ); /* X base      */
     fprintf ( fp_o ,"\n20 \n%f" ,dxf.y1        ); /* Y base      */
    }

 fprintf ( fp_o ,"\n0  \nSEQEND" ); /* END OF POLYLINE   */

 return ;
}
/*----------------------------------------------------------------*/
/*                        Write Text                              */
/*----------------------------------------------------------------*/
void write_text()
{
 dxf.hz_just = 0 ;
 dxf.vl_just = 0 ;

      if ( text[text_index].just == 1 ) { dxf.vl_just = 1; dxf.hz_just = 0; }
 else if ( text[text_index].just == 2 ) { dxf.vl_just = 1; dxf.hz_just = 1; }
 else if ( text[text_index].just == 3 ) { dxf.vl_just = 1; dxf.hz_just = 2; }
 else if ( text[text_index].just == 4 ) { dxf.vl_just = 2; dxf.hz_just = 0; }
 else if ( text[text_index].just == 5 ) { dxf.vl_just = 2; dxf.hz_just = 1; }
 else if ( text[text_index].just == 6 ) { dxf.vl_just = 2; dxf.hz_just = 2; }
 else if ( text[text_index].just == 7 ) { dxf.vl_just = 3; dxf.hz_just = 0; }
 else if ( text[text_index].just == 8 ) { dxf.vl_just = 3; dxf.hz_just = 1; }
 else if ( text[text_index].just == 9 ) { dxf.vl_just = 3; dxf.hz_just = 2; }


 switch(text[text_index].font)
       {
        case 1:   strcpy (dxf.font , "Normal")    ; break;
        case 2:   strcpy (dxf.font , "Courier")   ; break;
        case 3:   strcpy (dxf.font , "Romans")    ; break;
        case 4:   strcpy (dxf.font , "Cursive")   ; break;
        default:  strcpy (dxf.font , "Normal")    ; break;
       }


 fprintf ( fp_o ,"\n0  \nTEXT"                             ); /* TEXT       */
 fprintf ( fp_o ,"\n6  \n%s" ,dxf.linetype                 ); /* Line Type  */
 fprintf ( fp_o ,"\n8  \n%d" ,feat[i].layer                ); /* Layer      */
 fprintf ( fp_o ,"\n39 \n%d" ,feat[i].linewidth            ); /* Line width */
 fprintf ( fp_o ,"\n62 \n%d" ,dxf.color                    ); /* Color      */
 fprintf ( fp_o ,"\n10 \n%f" ,(float)text[text_index].x    ); /* X text     */
 fprintf ( fp_o ,"\n20 \n%f" ,(float)text[text_index].y    ); /* Y text     */
 fprintf ( fp_o ,"\n40 \n%f" ,(float)text[text_index].size ); /* size       */
 fprintf ( fp_o ,"\n50 \n%f" ,text[text_index].angle       ); /* angle      */
 fprintf ( fp_o ,"\n1  \n%s" ,text[text_index].string      ); /* string     */
 fprintf ( fp_o ,"\n7  \n%s" ,dxf.font                     ); /* font       */

 if ( dxf.hz_just != 0 ) fprintf ( fp_o ,"\n72 \n%d" ,dxf.hz_just );
 if ( dxf.vl_just != 0 ) fprintf ( fp_o ,"\n73 \n%d" ,dxf.vl_just );

 if ( dxf.hz_just != 0 || dxf.vl_just != 0 )
    {
     fprintf ( fp_o ,"\n11 \n%f" ,(float)text[text_index].x );
     fprintf ( fp_o ,"\n21 \n%f" ,(float)text[text_index].y );
    }

 return ;
}
/*----------------------------------------------------------------*/
/*                        check_layer                             */
/*----------------------------------------------------------------*/
void check_layer()
{

      if ( strcmp(dxf.layer,"0") == 0 )
	 {
	  feat[i].layer = 0 ;
	  feat[i].color = white.pixel ;
	 }
 else if ( strcmp(dxf.layer,"AIRPORT") == 0 )
	 {
	  feat[feat_count].layer = 28 ;
	  feat[feat_count].color = red.pixel ;
	  strcpy (feat[feat_count].code,dxf.layer) ;
	 }
 else if ( strcmp(dxf.layer,"ARABIC") == 0 )
	 {
	  feat[feat_count].layer = 27 ;
	  feat[feat_count].color = white.pixel ;
	  strcpy (feat[feat_count].code,dxf.layer) ;
	 }
 else if ( strcmp(dxf.layer,"BEACH_SINGLE") == 0 )
	 {
	  feat[feat_count].layer = 18 ;
	  feat[feat_count].color = yellow.pixel ;
	  strcpy (feat[feat_count].code,dxf.layer) ;
	 }
 else if ( strcmp(dxf.layer,"BOUNDARY") == 0 )
	 {
	  feat[feat_count].layer = 6 ;
	  feat[feat_count].color = blue.pixel ;
	  strcpy (feat[feat_count].code,dxf.layer) ;
	 }
 else if (strcmp(dxf.layer,"BREAKWATER_DAMS") == 0)
	 {
	  feat[feat_count].layer = 22 ;
	  feat[feat_count].color = red.pixel ;
	  strcpy (feat[feat_count].code,dxf.layer) ;
	 }
 else if (strcmp(dxf.layer,"BRIDGE_CULVERT" ) == 0)
	 {
	  feat[feat_count].layer = 23 ;
	  feat[feat_count].color = blue.pixel ;
	  strcpy (feat[feat_count].code,dxf.layer) ;
	 }
 else if ( strcmp(dxf.layer,"BUILDING") == 0 )
	 {
	  feat[feat_count].layer = 5 ;
	  feat[feat_count].color = white.pixel ;
	  strcpy (feat[feat_count].code,dxf.layer) ;
	 }
 else if ( strcmp(dxf.layer,"CANALS") == 0 )
	 {
	  feat[feat_count].layer = 19 ;
	  feat[feat_count].color = blue.pixel ;
	  strcpy (feat[feat_count].code,dxf.layer) ;
	 }
 else if ( strcmp(dxf.layer,"CAR_PARK") == 0 )
	 {
	  feat[feat_count].layer = 21 ;
	  feat[feat_count].color = white.pixel ;
	  strcpy (feat[feat_count].code,dxf.layer) ;
	 }
 else if ( strcmp(dxf.layer,"CONTOUR") == 0 )
	 {
	  feat[feat_count].layer = 7 ;
	  feat[feat_count].color = cyan.pixel ;
	  strcpy (feat[feat_count].code,dxf.layer) ;
	 }
 else if ( strcmp(dxf.layer,"CULTIVATED_AREA") == 0 )
	 {
	  feat[feat_count].layer = 16 ;
	  feat[feat_count].color = green.pixel ;
	  strcpy (feat[feat_count].code,dxf.layer) ;
	 }
 else if ( strcmp(dxf.layer,"FENCE") == 0 )
	 {
	  feat[feat_count].layer = 8 ;
	  feat[feat_count].color = yellow.pixel ;
	  strcpy (feat[feat_count].code,dxf.layer) ;
	 }
 else if ( strcmp(dxf.layer,"GARDEN") == 0 )
	 {
	  feat[feat_count].layer = 11 ;
	  feat[feat_count].color = green.pixel ;
	  strcpy (feat[feat_count].code,dxf.layer) ;
	 }
 else if ( strcmp(dxf.layer,"GRAVEL") == 0 )
	 {
	  feat[feat_count].layer = 24 ;
	  feat[feat_count].color = blue.pixel ;
	  strcpy (feat[feat_count].code,dxf.layer) ;
	 }
 else if ( strcmp(dxf.layer,"LABELS") == 0 )
	 {
	  feat[feat_count].layer = 9 ;
	  feat[feat_count].color = white.pixel ;
	  strcpy (feat[feat_count].code,dxf.layer) ;
	 }
 else if ( strcmp(dxf.layer,"LAKES") == 0 )
	 {
	  feat[feat_count].layer = 20 ;
	  feat[feat_count].color = blue.pixel ;
	  strcpy (feat[feat_count].code,dxf.layer) ;
	 }
 else if ( strcmp(dxf.layer,"LAND_BOUNDARY") == 0 )
	 {
	  feat[feat_count].layer = 14 ;
	  feat[feat_count].color = white.pixel ;
	  strcpy (feat[feat_count].code,dxf.layer) ;
	 }
 else if ( strcmp(dxf.layer,"LOCAL_BOUNDARY") == 0 )
	 {
	  feat[feat_count].layer = 15 ;
	  feat[feat_count].color = white.pixel ;
	  strcpy (feat[feat_count].code,dxf.layer) ;
	 }
 else if ( strcmp(dxf.layer,"MOSQUE") == 0 )
	 {
	  feat[feat_count].layer = 10 ;
	  feat[feat_count].color = green.pixel ;
	  strcpy (feat[feat_count].code,dxf.layer) ;
	 }
 else if ( strcmp(dxf.layer,"PAVED_ROAD") == 0 )
	 {
	  feat[feat_count].layer = 12 ;
	  feat[feat_count].color = blue.pixel ;
	  strcpy (feat[feat_count].code,dxf.layer) ;
	 }
 else if ( strcmp(dxf.layer,"UNPAVED_ROAD") == 0 )
	 {
	  feat[feat_count].layer = 13 ;
	  feat[feat_count].color = blue.pixel ;
	  strcpy (feat[feat_count].code,dxf.layer) ;
	 }
 else if ( strcmp(dxf.layer,"RUIN") == 0 )
	 {
	  feat[feat_count].layer = 25 ;
	  feat[feat_count].color = red.pixel ;
	  strcpy (feat[feat_count].code,dxf.layer) ;
	 }
 else if ( strcmp(dxf.layer,"STREAMS_WADI") == 0 )
	 {
	  feat[feat_count].layer = 17 ;
	  feat[feat_count].color = white.pixel ;
	  strcpy (feat[feat_count].code,dxf.layer) ;
	 }
 else if ( strcmp(dxf.layer,"STREET_ANNOTATION")== 0 )
	 {
	  feat[feat_count].layer = 26 ;
	  feat[feat_count].color = blue.pixel ;
	  strcpy (feat[feat_count].code,dxf.layer) ;
	 }
 else if ( strcmp(dxf.layer,"SCHOOL")== 0 )
	 {
	  feat[feat_count].layer = 29 ;
	  feat[feat_count].color = cyan.pixel ;
	  strcpy (feat[feat_count].code,dxf.layer) ;
	 }
 else if ( strcmp(dxf.layer,"BUILD")== 0 )
	 {
	  feat[feat_count].layer = 5 ;
	  feat[feat_count].color = white.pixel ;
	  strcpy (feat[feat_count].code,dxf.layer) ;
	 }
 else if ( strcmp(dxf.layer,"BLOCK")== 0 )
	 {
	  feat[feat_count].layer = 6 ;
	  feat[feat_count].color = green.pixel ;
	  strcpy (feat[feat_count].code,dxf.layer) ;
	 }
 else if ( strcmp(dxf.layer,"ROADFAC")== 0 )
	 {
	  feat[feat_count].layer = 31 ;
	  feat[feat_count].color = gray.pixel ;
	  strcpy (feat[feat_count].code,dxf.layer) ;
	 }

 return ;
}
/*----------------------------------------------------------------*/
/*                        check_linetype                          */
/*----------------------------------------------------------------*/
void check_linetype()
{

      if ( strcmp(dxf.linetype,"CONTINUOUS") == 0 )
         {
          feat[feat_count].linetype = 1 ;
         }
 else if ( strcmp(dxf.linetype,"DASH") == 0 )
         {
          feat[feat_count].linetype = 2 ;
         }
 else if ( strcmp(dxf.linetype,"DOT") == 0 )
         {
          feat[feat_count].linetype = 3 ;
         }
 else if ( strcmp(dxf.linetype,"DASHDOT") == 0 )
         {
          feat[feat_count].linetype = 4 ;
         }
 else if ( strcmp(dxf.linetype,"DASHDOTDOT") == 0 )
         {
          feat[feat_count].linetype = 5 ;
         }
 else  // Default Linetype
         {
          feat[feat_count].linetype = 1 ;
         }

 return ;
}
/*----------------------------------------------------------------*/
/*                        check_font                              */
/*----------------------------------------------------------------*/
void check_font()
{

      if ( strncmp(dxf.font,"Normal",6) == 0 ||
           strncmp(dxf.font,"NORMAL",6) == 0   )
         {
          text[text_index].font = 1 ;
         }
 else if ( strncmp(dxf.font,"Courier",7) == 0 ||
           strncmp(dxf.font,"COURIER",7) == 0   )
         {
          text[text_index].font = 2 ;
         }
 else if ( strncmp(dxf.font,"Romans",6) == 0 ||
           strncmp(dxf.font,"ROMANS",6) == 0   )
         {
          text[text_index].font = 9 ;
         }
 else if ( strncmp(dxf.font,"Cursive",7) == 0 ||
           strncmp(dxf.font,"CURSIVE",7) == 0   )
         {
          text[text_index].font = 4 ;
         }
 else  // Default Font
         {
          text[text_index].font = 1 ;
         }

 return ;
}
