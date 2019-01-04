/*------------------------------------------------------------------------*/
/*                    geoINFO/6000  Convert Symbol                        */
/*------------------------------------------------------------------------*/

/*------------------------------------------------------------------------*/
/*                          Standard Include Files                        */
/*------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <math.h>

/*------------------------------------------------------------------------*/
/*                         Global Variables                               */
/*------------------------------------------------------------------------*/


int   i  , ii , j           ;
char  line    [82]          ;
char  keyword [21]          ;

FILE  *fp_i                 ; /* Input  file pointer                  */
FILE  *fp_o                 ; /* Output file pointer                  */
char  InputFile  [51]       ; /* Input  file name                     */
char  OutputFile [51]       ; /* Output file name                     */

typedef struct
  {
   int    stroke         ;
   int    grid           ;
   int    mv_draw [200]  ;
   int    x       [200]  ;
   int    y       [200]  ;
  } Symbols ;

Symbols   symb[300]      ; /* Symbol set data                      */

int  upy       ;
int  bas       ;
int  x_shift   ;
int  y_shift   ;
int  grid_size ;

int  min_x     ;
int  max_x     ;

/*------------------------------------------------------------------------*/
/*                                main()                                  */
/*------------------------------------------------------------------------*/

main(int argc, char *argv[])
{


 if ( argc == 4 )
    {
     sscanf(argv[1],"%s",InputFile );
     sscanf(argv[2],"%d",&upy      );
     sscanf(argv[3],"%d",&bas      );
    }

 printf ("\n InputFile = %s  ",InputFile );
 printf ("\n upy       = %d  ",upy       );
 printf ("\n bas       = %d\n",bas       );

/* x_shift   = (upy - bas)/2       ; */
 y_shift   = (upy - bas)/2 + bas ;
 grid_size =  upy - bas          ;


/* fsb("symd","Select Symbol File"); */

 fp_i = fopen (InputFile,"rt");
 if  ( fp_i == NULL )
     {
      printf ("\n Can't open input file  !");
      return ;
     }

 printf ("\n processing GPG symbol file .." );


/*---------------------------------------------------------------------*/
/*                        Read GPG Symbol Set                          */
/*---------------------------------------------------------------------*/

 while ( fgets (line,81,fp_i) != '' )
 {

  /* printf("\n %s",line); */

  sscanf(line,"%s", keyword );

       if ( strcmp (keyword,"SYMBOL") == 0 )
	  {
	   sscanf(line,"%s%d%d",keyword,&j,&i) ;
	   ii = 0 ;

	   switch (i)
		{
		 case 129:   i = 97  ;  break;    /*  a  */
		 case 130:   i = 98  ;  break;    /*  b  */
		 case 131:   i = 99  ;  break;    /*  c  */
		 case 132:   i = 100 ;  break;    /*  d  */
		 case 133:   i = 101 ;  break;    /*  e  */
		 case 134:   i = 102 ;  break;    /*  f  */
		 case 135:   i = 103 ;  break;    /*  g  */
		 case 136:   i = 104 ;  break;    /*  h  */
		 case 137:   i = 105 ;  break;    /*  i  */
		 case 145:   i = 106 ;  break;    /*  j  */
		 case 146:   i = 107 ;  break;    /*  k  */
		 case 147:   i = 108 ;  break;    /*  l  */
		 case 148:   i = 109 ;  break;    /*  m  */
		 case 149:   i = 110 ;  break;    /*  n  */
		 case 150:   i = 111 ;  break;    /*  o  */
		 case 151:   i = 112 ;  break;    /*  p  */
		 case 152:   i = 113 ;  break;    /*  q  */
		 case 153:   i = 114 ;  break;    /*  r  */
		 case 162:   i = 115 ;  break;    /*  s  */
		 case 163:   i = 116 ;  break;    /*  t  */
		 case 164:   i = 117 ;  break;    /*  u  */
		 case 165:   i = 118 ;  break;    /*  v  */
		 case 166:   i = 119 ;  break;    /*  w  */
		 case 167:   i = 120 ;  break;    /*  x  */
		 case 168:   i = 121 ;  break;    /*  y  */
		 case 169:   i = 122 ;  break;    /*  z  */

		 case 193:   i = 65  ;  break;    /*  A  */
		 case 194:   i = 66  ;  break;    /*  B  */
		 case 195:   i = 67  ;  break;    /*  C  */
		 case 196:   i = 68  ;  break;    /*  D  */
		 case 197:   i = 69  ;  break;    /*  E  */
		 case 198:   i = 70  ;  break;    /*  F  */
		 case 199:   i = 71  ;  break;    /*  G  */
		 case 200:   i = 72  ;  break;    /*  H  */
		 case 201:   i = 73  ;  break;    /*  I  */
		 case 209:   i = 74  ;  break;    /*  J  */
		 case 210:   i = 75  ;  break;    /*  K  */
		 case 211:   i = 76  ;  break;    /*  L  */
		 case 212:   i = 77  ;  break;    /*  M  */
		 case 213:   i = 78  ;  break;    /*  N  */
		 case 214:   i = 79  ;  break;    /*  O  */
		 case 215:   i = 80  ;  break;    /*  P  */
		 case 216:   i = 81  ;  break;    /*  Q  */
		 case 217:   i = 82  ;  break;    /*  R  */
		 case 226:   i = 83  ;  break;    /*  S  */
		 case 227:   i = 84  ;  break;    /*  T  */
		 case 228:   i = 85  ;  break;    /*  U  */
		 case 229:   i = 86  ;  break;    /*  V  */
		 case 230:   i = 87  ;  break;    /*  W  */
		 case 231:   i = 88  ;  break;    /*  X  */
		 case 232:   i = 89  ;  break;    /*  Y  */
		 case 233:   i = 90  ;  break;    /*  Z  */

		 case 240:   i = 48  ;  break;    /*  0  */
		 case 241:   i = 49  ;  break;    /*  1  */
		 case 242:   i = 50  ;  break;    /*  2  */
		 case 243:   i = 51  ;  break;    /*  3  */
		 case 244:   i = 52  ;  break;    /*  4  */
		 case 245:   i = 53  ;  break;    /*  5  */
		 case 246:   i = 54  ;  break;    /*  6  */
		 case 247:   i = 55  ;  break;    /*  7  */
		 case 248:   i = 56  ;  break;    /*  8  */
		 case 249:   i = 57  ;  break;    /*  9  */

		 case  64:   i = 32  ;  break;    /* space */
		 case  75:   i = 46  ;  break;    /*  .  */
		 case  76:   i = 60  ;  break;    /*  <  */
		 case  77:   i = 40  ;  break;    /*  (  */
		 case  78:   i = 43  ;  break;    /*  +  */
		 case  79:   i = 124 ;  break;    /*  |  */
		 case  80:   i = 38  ;  break;    /*  &  */
		 case  90:   i = 33  ;  break;    /*  !  */
		 case  91:   i = 36  ;  break;    /*  $  */
		 case  92:   i = 42  ;  break;    /*  *  */
		 case  93:   i = 41  ;  break;    /*  )  */
		 case  94:   i = 59  ;  break;    /*  ;  */
	     /*  case  95:   i =     ;  break;        ^  */
		 case  96:   i = 45  ;  break;    /*  -  */
		 case  97:   i = 47  ;  break;    /*  /  */
		 case 107:   i = 44  ;  break;    /*  ,  */
		 case 108:   i = 37  ;  break;    /*  %  */
		 case 109:   i = 95  ;  break;    /*  _  */
		 case 110:   i = 62  ;  break;    /*  >  */
		 case 111:   i = 63  ;  break;    /*  ?  */
		 case 122:   i = 58  ;  break;    /*  :  */
		 case 123:   i = 35  ;  break;    /*  #  */
		 case 124:   i = 64  ;  break;    /*  @  */
		 case 125:   i = 39  ;  break;    /*  '  */
		 case 126:   i = 61  ;  break;    /*  =  */
		 case 127:   i = 34  ;  break;    /*  "  */

		 default:    i = 0   ;  break;
		}

	   /* printf("\nsymb no %d",i); */
	  }

  else if ( strcmp (keyword,"STROKE") == 0 )
	  {
	   ii++ ;
	   sscanf(line,"%s%d%d%d",keyword,&symb[i].mv_draw[ii],&symb[i].x[ii],&symb[i].y[ii]);

	   /* symb[i].x[ii] -= x_shift ; */
	   symb[i].y[ii] -= y_shift ;
	  }

  else if ( strcmp (keyword,"END") == 0 )
	  {
	   symb[i].grid   = grid_size ;
	   symb[i].stroke = ii        ;
	   strcpy(line,"")            ;
	  }

 }

 fclose(fp_i);

 /*-------------------------------------------------------------*/
 /*                    Save geoINFO font                        */
 /*-------------------------------------------------------------*/

 strcpy (OutputFile,InputFile);
 strcat (OutputFile,".font");

 fp_o=fopen(OutputFile,"wt");
 if  ( fp_o== NULL )
     {
      printf ("\nERROR : Can't save font file !\n");
      return ;
     }

 printf ("\n processing geoINFO font file ..\n" );


 for ( i=1; i<= 255; i++ )
     {
      max_x = 0 ;
      for ( ii=1; ii<=symb[i].stroke; ii++ )
	  {
	   if ( symb[i].x[ii] > max_x )  { max_x = symb[i].x[ii] ; }
	  }

      min_x = 1000 ;
      for ( ii=1; ii<=symb[i].stroke; ii++ )
	  {
	   if ( symb[i].x[ii] < min_x )  { min_x = symb[i].x[ii] ; }
	  }


      /* x_shift = abs ( (max_x/2) - (upy - bas)/2 ) ; */

      x_shift = ( max_x + min_x )/ 2 ;

      if ( x_shift > ((upy - bas)/2) )
	 {
	  x_shift =(upy - bas)/2 ;
	 }


      for ( ii=1; ii<=symb[i].stroke; ii++ )
	  {
	   symb[i].x[ii] -= x_shift ;
	  }
     }


 /* write space charcter ' '  */

 fprintf(fp_o,"\n\n' '");
 fprintf(fp_o,"\n32");
 fprintf(fp_o,"\n0" );
 fprintf(fp_o,"\n0" );


 for ( i=1; i<= 255; i++ )
     {
      if (symb[i].stroke != 0)
	 {
	  fprintf(fp_o,"\n\n'"               ) ;
	  fputc  ( i  ,fp_o                  ) ;
	  fprintf(fp_o,"'"                   ) ;
	  fprintf(fp_o,"\n%d", i             ) ;
	  fprintf(fp_o,"\n%d", symb[i].grid  ) ;
	  fprintf(fp_o,"\n%d", symb[i].stroke) ;

	  for ( ii=1 ; ii<=symb[i].stroke ; ii++ )
	      {
	       fprintf(fp_o,"\n%d   ", symb[i].mv_draw[ii]) ;
	       fprintf(fp_o,"%3d    ", symb[i].x[ii]) ;
	       fprintf(fp_o,"%3d    ", symb[i].y[ii]) ;
	      }
	 }
     }

 fclose(fp_o);

}
