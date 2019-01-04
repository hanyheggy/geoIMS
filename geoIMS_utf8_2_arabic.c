/*-------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------*/
/*                               geoIMS_utf8_2_arabic.c                                      */
/*-------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------*/
/*               UTF8 String BIDI, auto-shaping and Arabic-Symbol generation                 */
/*-------------------------------------------------------------------------------------------*/
/*                                                                                           */
/* This Code do the following:                                                               */
/*                                                                                           */
/* 1. Convert UTF-8 to unicode UCS4  ( UCS4 = Uni Code String )                              */
/*                                                                                           */
/* 2. BIDI the arabic UCS4 string                                                            */
/*                                                                                           */
/* 3. Auto-shape the arabic UCS4 string                                                      */
/*                                                                                           */
/* 4. Generate Single byte Arabic Ascii code string  ( for Arabic Symbol set )               */
/*                                                                                           */
/*-------------------------------------------------------------------------------------------*/
/*                                                                                           */
/* INPUT  : Double byte UTF-8 string, Direction RTL/LTR/CHECK                                */
/*                                                                                           */
/* OUTPUT : Single byte Arabic Ascii code string                                             */
/*                                                                                           */
/*-------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------*/
/*                                Standard Include Files                                     */
/*-------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <glib.h>

/*-------------------------------------------------------------------------------------------*/
/*                                  Defined Macros                                           */
/*-------------------------------------------------------------------------------------------*/
#define DEBUG(x) fprintf(stderr, "%s\n", x)

/*-------------------------------------------------------------------------------------------*/
/*                                       Global Variables                                    */
/*-------------------------------------------------------------------------------------------*/
typedef struct
{
 gboolean  junk     ;
 gunichar  isolated ;
 gunichar  initial  ;
 gunichar  medial   ;
 gunichar  final    ;
}
ARABIC_CHAR;

ARABIC_CHAR arabic_table[] = {
//[i]  ucs4       Junk  Isolated Initial Medial  Final        Character
/* 0  0x621 */  { FALSE, 0x0080, 0x0000, 0x0000, 0x0000}, //  Hamzah            (128,000,000,000)
/* 1  0x622 */  { FALSE, 0x0081, 0x0000, 0x0000, 0x0082}, //  Alef with Madah   (129,000,000,130)
/* 2  0x623 */  { FALSE, 0x0083, 0x0000, 0x0000, 0x0084}, //  Alef with Hamza   (131,000,000,132)
/* 3  0x624 */  { FALSE, 0x0085, 0x0000, 0x0000, 0x0085}, //  Wawo with Hamza   (133,000,000,133)
/* 4  0x625 */  { FALSE, 0x0086, 0x0000, 0x0000, 0x0087}, //  Alef with Kasrah  (134,000,000,135)
/* 5  0x626 */  { FALSE, 0x0088, 0x008A, 0x008A, 0x0089}, //  Hamzah over Yeeh  (136,138,138,137)
/* 6  0x627 */  { FALSE, 0x008B, 0x0000, 0x0000, 0x008C}, //  Alef              (139,000,000,140)
/* 7  0x628 */  { FALSE, 0x008D, 0x008E, 0x008E, 0x008D}, //  Beha              (141,142,142,141)
/* 8  0x629 */  { FALSE, 0x008F, 0x0000, 0x0000, 0x0090}, //  Tehah marbotah    (143,000,000,144)
/* 9  0x62A */  { FALSE, 0x0091, 0x0092, 0x0092, 0x0091}, //  Tehah             (145,146,146,145)
/* 10 0x62B */  { FALSE, 0x0093, 0x0094, 0x0094, 0x0093}, //  Theeah            (147,148,148,147)
/* 11 0x62C */  { FALSE, 0x0095, 0x0097, 0x0097, 0x0096}, //  Geem              (149,151,151,150)
/* 12 0x62D */  { FALSE, 0x0098, 0x009A, 0x009A, 0x0099}, //  Haah              (152,154,154,153)
/* 13 0x62E */  { FALSE, 0x009B, 0x009D, 0x009D, 0x009C}, //  Khaah             (155,157,157,156)
/* 14 0x62F */  { FALSE, 0x009E, 0x0000, 0x0000, 0x009E}, //  Daal              (158,000,000,158)
/* 15 0x630 */  { FALSE, 0x009F, 0x0000, 0x0000, 0x009F}, //  Thaal             (159,000,000,159)
/* 16 0x631 */  { FALSE, 0x00A0, 0x0000, 0x0000, 0x00A0}, //  Reaah             (160,000,000,160)
/* 17 0x632 */  { FALSE, 0x00A1, 0x0000, 0x0000, 0x00A1}, //  Zane              (161,000,000,161)
/* 18 0x633 */  { FALSE, 0x00A2, 0x00A3, 0x00A3, 0x00A2}, //  Seen              (162,163,163,162)
/* 19 0x634 */  { FALSE, 0x00A4, 0x00A5, 0x00A5, 0x00A4}, //  Sheen             (164,165,165,164)
/* 20 0x635 */  { FALSE, 0x00A6, 0x00A7, 0x00A7, 0x00A6}, //  Saad              (166,167,167,166)
/* 21 0x636 */  { FALSE, 0x00A8, 0x00A9, 0x00A9, 0x00A8}, //  Daad              (168,169,169,168)
/* 22 0x637 */  { FALSE, 0x00AA, 0x00AA, 0x00AA, 0x00AA}, //  Taah              (170,170,170,170)
/* 23 0x638 */  { FALSE, 0x00AB, 0x00AB, 0x00AB, 0x00AB}, //  Thaah             (171,171,171,171)
/* 24 0x639 */  { FALSE, 0x00AC, 0x00AE, 0x00AF, 0x00AD}, //  3een              (172,174,175,173)
/* 25 0x63A */  { FALSE, 0x00B0, 0x00B2, 0x00B3, 0x00B1}, //  3'een             (176,178,179,177)
/* 26 0x63B */  { TRUE , 0x0000, 0x0000, 0x0000, 0x0000}, //  - Junk -
/* 27 0x63C */  { TRUE , 0x0000, 0x0000, 0x0000, 0x0000}, //  - Junk -
/* 28 0x63D */  { TRUE , 0x0000, 0x0000, 0x0000, 0x0000}, //  - Junk -
/* 29 0x63E */  { TRUE , 0x0000, 0x0000, 0x0000, 0x0000}, //  - Junk -
/* 30 0x63F */  { TRUE , 0x0000, 0x0000, 0x0000, 0x0000}, //  - Junk -
/* 31 0x640 */  { FALSE, 0x00B4, 0x0000, 0x0000, 0x0000}, //  Cashedah -       (180,000,000,000)
/* 32 0x641 */  { FALSE, 0x00B5, 0x00B6, 0x00B6, 0x00B5}, //  Faa              (181,182,182,180)
/* 33 0x642 */  { FALSE, 0x00B7, 0x00B8, 0x00B8, 0x00B7}, //  Kaaf             (183,184,184,183)
/* 34 0x643 */  { FALSE, 0x00B9, 0x00BA, 0x00BA, 0x00B9}, //  Kaf              (185,186,186,185)
/* 35 0x644 */  { FALSE, 0x00BB, 0x00BC, 0x00BC, 0x00BB}, //  Lam              (187,188,188,187)
/* 36 0x645 */  { FALSE, 0x00BD, 0x00BE, 0x00BE, 0x00BD}, //  Meem             (189,190,190,189)
/* 37 0x646 */  { FALSE, 0x00BF, 0x00C0, 0x00C0, 0x00BF}, //  Noon             (191,192,192,191)
/* 38 0x647 */  { FALSE, 0x00C1, 0x00C3, 0x00C4, 0x00C2}, //  heeh             (193,195,196,194)
/* 39 0x648 */  { FALSE, 0x00C5, 0x0000, 0x0000, 0x00C5}, //  Wow              (197,000,000,197)
/* 40 0x649 */  { FALSE, 0x00C6, 0x0000, 0x0000, 0x00C7}, //  yeeah            (198,000,000,199)
/* 41 0x64A */  { FALSE, 0x00C8, 0x00CA, 0x00CA, 0x00C9}  //  yeeh             (180,000,000,000)
};

typedef struct
{
 gunichar  isolated ;
}
ENGLISH_CHAR;

ENGLISH_CHAR english_table[] = {
//[i] ucs4 ascii     Isolated       Character
/* 0  0x20  32  */  { 0x0020 }, //  space
/* 1  0x21  33  */  { 0x0021 }, //  !
/* 2  0x22  34  */  { 0x0022 }, //  "
/* 3  0x23  35  */  { 0x0023 }, //  #
/* 4  0x24  36  */  { 0x0024 }, //  $
/* 5  0x25  37  */  { 0x0025 }, //  %
/* 6  0x26  38  */  { 0x0026 }, //  &
/* 7  0x27  39  */  { 0x0027 }, //  '
/* 8  0x28  40  */  { 0x0028 }, //  (
/* 9  0x29  41  */  { 0x0029 }, //  )
/* 10 0x2A  42  */  { 0x002A }, //  *
/* 11 0x2B  43  */  { 0x002B }, //  +
/* 12 0x2C  44  */  { 0x002C }, //  ,
/* 13 0x2D  45  */  { 0x002D }, //  -
/* 14 0x2E  46  */  { 0x002E }, //  .
/* 15 0x2F  47  */  { 0x002F }, //  /
/* 16 0x30  48  */  { 0x0030 }, //  0
/* 17 0x31  49  */  { 0x0031 }, //  1
/* 18 0x32  50  */  { 0x0032 }, //  2
/* 19 0x33  51  */  { 0x0033 }, //  3
/* 20 0x34  52  */  { 0x0034 }, //  4
/* 21 0x35  53  */  { 0x0035 }, //  5
/* 22 0x36  54  */  { 0x0036 }, //  6
/* 23 0x37  55  */  { 0x0037 }, //  7
/* 24 0x38  56  */  { 0x0038 }, //  8
/* 25 0x39  57  */  { 0x0039 }, //  9
/* 26 0x3A  58  */  { 0x003A }, //  :
/* 27 0x3B  59  */  { 0x003B }, //  ;
/* 28 0x3C  60  */  { 0x003C }, //  =
/* 29 0x3D  61  */  { 0x003D }, //  <
/* 30 0x3E  62  */  { 0x003E }, //  >
/* 31 0x3F  63  */  { 0x003F }, //  ?
/* 32 0x40  64  */  { 0x0040 }, //  @
/* 33 0x41  65  */  { 0x0041 }, //  A
/* 34 0x42  66  */  { 0x0042 }, //  B
/* 35 0x43  67  */  { 0x0043 }, //  C
/* 36 0x44  68  */  { 0x0044 }, //  D
/* 37 0x45  69  */  { 0x0045 }, //  E
/* 38 0x46  70  */  { 0x0046 }, //  F
/* 39 0x47  71  */  { 0x0047 }, //  G
/* 40 0x48  72  */  { 0x0048 }, //  H
/* 41 0x49  73  */  { 0x0049 }, //  I
/* 42 0x4A  74  */  { 0x004A }, //  J
/* 43 0x4B  75  */  { 0x004B }, //  K
/* 44 0x4C  76  */  { 0x004C }, //  L
/* 45 0x4D  77  */  { 0x004D }, //  M
/* 46 0x4E  78  */  { 0x004E }, //  N
/* 47 0x4F  79  */  { 0x004F }, //  O
/* 48 0x50  80  */  { 0x0050 }, //  P
/* 49 0x51  81  */  { 0x0051 }, //  Q
/* 50 0x52  82  */  { 0x0052 }, //  R
/* 51 0x53  83  */  { 0x0053 }, //  S
/* 52 0x54  84  */  { 0x0054 }, //  T
/* 53 0x55  85  */  { 0x0055 }, //  U
/* 54 0x56  86  */  { 0x0056 }, //  V
/* 55 0x57  87  */  { 0x0057 }, //  W
/* 56 0x58  88  */  { 0x0058 }, //  X
/* 57 0x59  89  */  { 0x0059 }, //  Y
/* 58 0x5A  90  */  { 0x005A }, //  Z
/* 59 0x5B  91  */  { 0x005B }, //  [
/* 60 0x5C  92  */  { 0x005C }, //  \
/* 61 0x5D  93  */  { 0x005D }, //  ]
/* 62 0x5E  94  */  { 0x005E }, //  ^
/* 63 0x5F  95  */  { 0x005F }, //  _
/* 64 0x60  96  */  { 0x0060 }, //  `
/* 65 0x61  97  */  { 0x0061 }, //  a
/* 66 0x62  98  */  { 0x0062 }, //  b
/* 67 0x63  99  */  { 0x0063 }, //  c
/* 68 0x64  100 */  { 0x0064 }, //  d
/* 69 0x65  101 */  { 0x0065 }, //  e
/* 70 0x66  102 */  { 0x0066 }, //  f
/* 71 0x67  103 */  { 0x0067 }, //  g
/* 72 0x68  104 */  { 0x0068 }, //  h
/* 73 0x69  105 */  { 0x0069 }, //  i
/* 74 0x6A  106 */  { 0x006A }, //  j
/* 75 0x6B  107 */  { 0x006B }, //  k
/* 76 0x6C  108 */  { 0x006C }, //  l
/* 77 0x6D  109 */  { 0x006D }, //  m
/* 78 0x6E  110 */  { 0x006E }, //  n
/* 79 0x6F  111 */  { 0x006F }, //  o
/* 80 0x70  112 */  { 0x0070 }, //  p
/* 81 0x71  113 */  { 0x0071 }, //  q
/* 82 0x72  114 */  { 0x0072 }, //  r
/* 83 0x73  115 */  { 0x0073 }, //  s
/* 84 0x74  116 */  { 0x0074 }, //  t
/* 85 0x75  117 */  { 0x0075 }, //  u
/* 86 0x76  118 */  { 0x0076 }, //  v
/* 87 0x77  119 */  { 0x0077 }, //  w
/* 88 0x78  120 */  { 0x0078 }, //  x
/* 89 0x79  121 */  { 0x0079 }, //  y
/* 90 0x7A  122 */  { 0x007A }, //  z
/* 91 0x7B  123 */  { 0x007B }, //  {
/* 92 0x7C  124 */  { 0x007C }, //  |
/* 93 0x7D  125 */  { 0x007D }, //  }
/* 94 0x7E  126 */  { 0x007E }  //  ~
};

typedef struct
{
 gunichar  isolated ;
}
ARABIC_NUMERIC;

ARABIC_NUMERIC arabic_numeric_table[] = {
//[i] ucs4       Isolated        Character
/* 0  0x660 */  { 0x00DC },  //  0
/* 1  0x661 */  { 0x00DD },  //  1
/* 2  0x662 */  { 0x00DE },  //  2
/* 3  0x663 */  { 0x00DF },  //  3
/* 4  0x664 */  { 0x00E0 },  //  4
/* 5  0x665 */  { 0x00E1 },  //  5
/* 6  0x666 */  { 0x00E2 },  //  6
/* 7  0x667 */  { 0x00E3 },  //  7
/* 8  0x668 */  { 0x00E4 },  //  8
/* 9  0x669 */  { 0x00E5 },  //  9
/* 10 0x66A */  { 0x00E6 }   //  %
};


/*-------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------*/
/*                                     utf8_2_arabic()                                       */
/*-------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------------*/
int utf8_2_arabic ( unsigned char *utf , char *direction )
{
 /*---------------------*/
 /* Local Varibles      */
 /*---------------------*/
 gint       i                 = 0     ;  // Loop Counter
 gint       ii                = 0     ;  // Loop Counter
 gint       j                 = 0     ;  // Loop Counter
 gint       k                 = 0     ;  // Loop Counter
 gint       kk                = 0     ;  // Loop Counter
 gint       l                 = 0     ;  // Loop Counter

 gboolean   ARABIC_START      = 0     ;  // BIDI ARABIC_START Flag

 gint       x                 = 0     ;  // auto_shaped_ucs string length  (in double bytes)
 glong      len               = 0     ;  //             ucs string length  (in double bytes)
 gunichar  *ucs               = NULL  ;  // Original unicode string in ucs4 encoding
 gunichar  *bidi_ucs          = NULL  ;  // BIDI     unicode string in ucs4 encoding
 gunichar  *auto_shaped_ucs   = NULL  ;  // Auto_shaped         unicode string after auto_shaping in ucs4 encoding
 gunichar  *auto_shaped_ucs_R = NULL  ;  // Reverse Auto_shaped unicode string after auto_shaping in ucs4 encoding



 /*-------------------------------------------------------------------------------------------*/
 /*-------------------------------------------------------------------------------------------*/
 /*                              1. Convert UTF8 to Unicode USC4                              */
 /*-------------------------------------------------------------------------------------------*/
 /*-------------------------------------------------------------------------------------------*/
 ucs               = g_utf8_to_ucs4_fast (utf, -1, &len)   ;  // len is calculated here

 bidi_ucs          = g_malloc (sizeof(gunichar) * (len+1)) ;  bidi_ucs          [len] = 0 ;
 auto_shaped_ucs   = g_malloc (sizeof(gunichar) * (len+1)) ;  auto_shaped_ucs   [len] = 0 ;
 auto_shaped_ucs_R = g_malloc (sizeof(gunichar) * (len+1)) ;  auto_shaped_ucs_R [len] = 0 ;

 /*-------------------------------------------------------------------------------------------*/
 /*-------------------------------------------------------------------------------------------*/
 /*                                    2. BIDI USC4 String                                    */
 /*-------------------------------------------------------------------------------------------*/
 /*-------------------------------------------------------------------------------------------*/

 /*-----------------------------------------------------------*/
 /* 2.1 Check of String (Arabic starting or English starting) */
 /*-----------------------------------------------------------*/
 if ( strcmp (direction,"RTL") == 0 || strcmp (direction,"rtl") == 0 )
    {
     // fprintf(stdout,">>>>>>>>>>> PARAMTER DIR  RTL \n");
     ARABIC_START = TRUE ;
    }
 else
 if ( strcmp (direction,"LTR") == 0 || strcmp (direction,"ltr") == 0 )
    {
     // fprintf(stdout,">>>>>>>>>>> PARAMTER DIR  LTR \n");
     ARABIC_START = FALSE ;
    }
 else
    {
     for ( i=0 ; i<len ; i++ )   // Check the Direction
         {
          if ( (ucs[i] >= 0x621 && ucs[i] <= 0x63A) ||
               (ucs[i] >= 0x641 && ucs[i] <= 0x64A) ||
               (ucs[i] >= 0x660 && ucs[i] <= 0x669)   )  // ARABIC Letter & Numeric Range
             {
              // fprintf(stdout,">>>>>>>>>>> PROGRAM DIR  RTL \n");
              ARABIC_START = TRUE ;
              goto END_TEST       ;
             }
          else
          if ( (ucs[i] >= 0x41 && ucs[i] <= 0x5A) ||
               (ucs[i] >= 0x61 && ucs[i] <= 0x7A) ||
               (ucs[i] >= 0x30 && ucs[i] <= 0x39)    )  // ENGLISH Letter & Numeric Range
             {
              // fprintf(stdout,">>>>>>>>>>> PROGRAM DIR  LTR \n");
              ARABIC_START = FALSE ;
              goto END_TEST        ;
             }
          else
             {
              continue ;
             }
         }
    }

 END_TEST:

 /*-----------------------------------------------------------*/
 /* 2.2 BIDI UCS4 String based on its starting character      */
 /*-----------------------------------------------------------*/
 if ( ARABIC_START )
    {
     /////////////////////////////////////////
     /*  DIRECTION :  RTL                   */
     /////////////////////////////////////////
     for ( i=0 ; i<len ; i++ )
         {
          next_RTL_char:

          if ( ucs[i] == 0x20 )  { bidi_ucs[(len-1) - i] = ucs[i] ; }  //  Space
          else
          if ( ucs[i] == 0x28 )  { bidi_ucs[(len-1) - i] = 0x29   ; }  //  (
          else
          if ( ucs[i] == 0x29 )  { bidi_ucs[(len-1) - i] = 0x28   ; }  //  )
          else
          if ( ucs[i] == 0x5B )  { bidi_ucs[(len-1) - i] = 0x5D   ; }  //  [
          else
          if ( ucs[i] == 0x5D )  { bidi_ucs[(len-1) - i] = 0x5B   ; }  //  ]
          else
          if ( ucs[i] == 0x3C )  { bidi_ucs[(len-1) - i] = 0x3E   ; }  //  <
          else
          if ( ucs[i] == 0x3E )  { bidi_ucs[(len-1) - i] = 0x3C   ; }  //  >
          else
          if ( ucs[i] == 0x7B )  { bidi_ucs[(len-1) - i] = 0x7D   ; }  //  {
          else
          if ( ucs[i] == 0x7D )  { bidi_ucs[(len-1) - i] = 0x7B   ; }  //  }
          else
          if ( ucs[i] >= 0x621 && ucs[i] <= 0x64A )
             {
              /*----------------------------------------------------*/
              /* FOUND Arabic Letter, Search for 1st English Letter */
              /*----------------------------------------------------*/
              for ( j=i+1 ; j<len ; j++ )
                  {
                   if ( (ucs[j] >= 0x41   &&  ucs[j] <= 0x5A  ) ||  // Capital English Letters
                        (ucs[j] >= 0x61   &&  ucs[j] <= 0x7A  ) ||  // Small   English Letters
                        (ucs[j] >= 0x30   &&  ucs[j] <= 0x39  ) ||  // English Numeric Range
                        (ucs[j] >= 0x660  &&  ucs[j] <= 0x669 ) ||  // Arabic Numeric Range
                         ucs[j] == 0x20   ||                        // Sapce
                         ucs[j] == 0x28   ||                        // (
                         ucs[j] == 0x29   ||                        // )
                         ucs[j] == 0x5B   ||                        // [
                         ucs[j] == 0x5D   ||                        // [
                         ucs[j] == 0x3C   ||                        // <
                         ucs[j] == 0x3E   ||                        // >
                         ucs[j] == 0x7B   ||                        // {
                         ucs[j] == 0x7D       )                     // }
                      {
                       for ( k=i ; k<j ; k++ )
                           {
                            bidi_ucs[(len-1) - k] = ucs[k] ;
                           }

                       i = j   ;
                       goto next_RTL_char ;
                      }
                  }
              /*---------------------------------------------------------*/
              /* IF No more English Found (The rest of string is arabic) */
              /*---------------------------------------------------------*/
              if ( j >= len  )
                 {
                  for ( k=i ; k<j ; k++ )
                      {
                       bidi_ucs[(len-1) - k] = ucs[k] ;
                      }
                  goto END_BIDI ;
                 }
             }
          else
             {
              /*----------------------------------------------------*/
              /* FOUND English Letter, Search for 1st Arabic Letter */
              /*----------------------------------------------------*/
              for ( j=i+1 ; j<len ; j++ )
                  {
                   if ( ucs[j] >= 0x621  &&  ucs[j] <= 0x64A )   // Arabic Letters
                      {
                       if ( ucs[j-1] == 0x20 ||
                            ucs[j-1] == 0x28 || ucs[j-1] == 0x29 ||
                            ucs[j-1] == 0x5B || ucs[j-1] == 0x5D ||
                            ucs[j-1] == 0x3C || ucs[j-1] == 0x3E ||
                            ucs[j-1] == 0x7B || ucs[j-1] == 0x7B    )
                          {
                           kk = len - j ;
                           for ( ii=j-1 ; ii>i ; ii--,kk++ )
                               {
                                if ( ucs[ii] == 0x20 ||
                                     ucs[ii] == 0x28 || ucs[ii] == 0x29 ||
                                     ucs[ii] == 0x5B || ucs[ii] == 0x5D ||
                                     ucs[ii] == 0x3C || ucs[ii] == 0x3E ||
                                     ucs[ii] == 0x7B || ucs[ii] == 0x7D    )
                                   {
                                         if (ucs[ii] == 0x28) bidi_ucs[kk] = 0x29    ;
                                    else if (ucs[ii] == 0x29) bidi_ucs[kk] = 0x28    ;
                                    else if (ucs[ii] == 0x5B) bidi_ucs[kk] = 0x5D    ;
                                    else if (ucs[ii] == 0x5D) bidi_ucs[kk] = 0x5B    ;
                                    else if (ucs[ii] == 0x3C) bidi_ucs[kk] = 0x3E    ;
                                    else if (ucs[ii] == 0x3E) bidi_ucs[kk] = 0x3C    ;
                                    else if (ucs[ii] == 0x7B) bidi_ucs[kk] = 0x7D    ;
                                    else if (ucs[ii] == 0x7D) bidi_ucs[kk] = 0x7B    ;
                                    else                      bidi_ucs[kk] = ucs[ii] ;
                                    continue ;
                                   }
                                else
                                   {
                                    ii++  ;
                                    break ;
                                   }
                                }

                           // printf("  INFO 1 i%d  ii%d ucs[i] %X\n",i,ii,ucs[i]);
                           if  ( i == ii )
                               {
                                bidi_ucs[kk] = ucs[i] ;
                               }
                           else
                               {
                                for ( k=i ; k<ii ; k++,kk++)  // k<=
                                    {
                                     bidi_ucs[kk] = ucs[k] ;
                                    }
                               }

                          }
                        else
                          {
                           kk = len  - j ;
                           for ( k=i ; k<j ; k++,kk++)
                               {
                                bidi_ucs[kk] = ucs[k] ;
                               }
                          }

                       i = j     ;
                       goto next_RTL_char ;
                      }
                  }
              /*---------------------------------------------------------*/
              /* IF No more Arabic Found (The rest of string is English) */
              /*---------------------------------------------------------*/
              if ( j >= len  )
                 {
                       if ( ucs[j-1] == 0x20 ||
                            ucs[j-1] == 0x28 || ucs[j-1] == 0x29 ||
                            ucs[j-1] == 0x5B || ucs[j-1] == 0x5D ||
                            ucs[j-1] == 0x3C || ucs[j-1] == 0x3E ||
                            ucs[j-1] == 0x7B || ucs[j-1] == 0x7B    )
                          {
                           kk = len - j ;
                           for ( ii=j-1 ; ii>i ; ii--,kk++ )
                               {
                                if ( ucs[ii] == 0x20 ||
                                     ucs[ii] == 0x28 || ucs[ii] == 0x29 ||
                                     ucs[ii] == 0x5B || ucs[ii] == 0x5D ||
                                     ucs[ii] == 0x3C || ucs[ii] == 0x3E ||
                                     ucs[ii] == 0x7B || ucs[ii] == 0x7D    )
                                   {
                                         if (ucs[ii] == 0x28) bidi_ucs[kk] = 0x29    ;
                                    else if (ucs[ii] == 0x29) bidi_ucs[kk] = 0x28    ;
                                    else if (ucs[ii] == 0x5B) bidi_ucs[kk] = 0x5D    ;
                                    else if (ucs[ii] == 0x5D) bidi_ucs[kk] = 0x5B    ;
                                    else if (ucs[ii] == 0x3C) bidi_ucs[kk] = 0x3E    ;
                                    else if (ucs[ii] == 0x3E) bidi_ucs[kk] = 0x3C    ;
                                    else if (ucs[ii] == 0x7B) bidi_ucs[kk] = 0x7D    ;
                                    else if (ucs[ii] == 0x7D) bidi_ucs[kk] = 0x7B    ;
                                    else                      bidi_ucs[kk] = ucs[ii] ;
                                    continue ;
                                   }
                                else
                                   {
                                    ii++  ;
                                    break ;
                                   }
                                }

                           // printf("  INFO 2 i%d  ii%d ucs[i] %X\n",i,ii,ucs[i]);
                           if  ( i == ii )
                               {
                                bidi_ucs[kk] = ucs[i] ;
                               }
                           else
                               {
                                for ( k=i ; k<ii ; k++,kk++)  // k<=
                                    {
                                     bidi_ucs[kk] = ucs[k] ;
                                    }
                               }
                          }
                        else
                          {
                           kk = len  - j ;
                           for ( k=i ; k<j ; k++,kk++)
                               {
                                bidi_ucs[kk] = ucs[k] ;
                               }
                          }

              goto END_BIDI ;
             }
           }
         }
    }
 else
    {
     //////////////////////////////////////////
     /*  DIRECTION :  LTR                    */
     //////////////////////////////////////////
     for ( i=0 ; i<len ; i++ )
         {
          next_LTR_char:

          if ( ( ucs[i] == 0x20 ) ||   // FOUND Space
               ( ucs[i] == 0x28 ) ||   // FOUND (
               ( ucs[i] == 0x29 ) ||   // FOUND )
               ( ucs[i] == 0x5B ) ||   // FOUND [
               ( ucs[i] == 0x5D ) ||   // FOUND ]
               ( ucs[i] == 0x3C ) ||   // FOUND <
               ( ucs[i] == 0x3E ) ||   // FOUND >
               ( ucs[i] == 0x7B ) ||   // FOUND {
               ( ucs[i] == 0x7D )    ) // FOUND }
             {
              bidi_ucs[i] = ucs[i] ;
             }
          else
          if ( (ucs[i] >= 0x621) && (ucs[i] <= 0x64A) )
             {
              /*----------------------------------------------------*/
              /* FOUND Arabic Letter, Search for 1st English Letter */
              /*----------------------------------------------------*/
              for ( j=i+1 ; j<len ; j++ )
                  {
                   if ( (ucs[j] >= 0x41   &&  ucs[j] <= 0x5A  ) ||  // Capital English Letters
                        (ucs[j] >= 0x61   &&  ucs[j] <= 0x7A  ) ||  // Small   English Letters
                        (ucs[j] >= 0x30   &&  ucs[j] <= 0x39  ) ||  // English Numeric Range
                        (ucs[j] >= 0x660  &&  ucs[j] <= 0x669 ) ||  // Arabic Numeric Range
                         ucs[j] == 0x20   ||                        // Sapce
                         ucs[j] == 0x28   ||                        // (
                         ucs[j] == 0x29   ||                        // )
                         ucs[j] == 0x5B   ||                        // [
                         ucs[j] == 0x5D   ||                        // [
                         ucs[j] == 0x3C   ||                        // <
                         ucs[j] == 0x3E   ||                        // >
                         ucs[j] == 0x7B   ||                        // {
                         ucs[j] == 0x7D       )                     // }
                      {
                       kk = j-1 ;
                       for ( k=i ; k<j ; k++,kk--)
                           {
                            bidi_ucs[k] = ucs[kk] ;
                           }

                       i = j   ;
                       goto next_LTR_char ;
                      }
                  }

              /*---------------------------------------------------------*/
              /* If No more English Found (the rest of string is arabic) */
              /*---------------------------------------------------------*/
              if ( j >= len  )
                 {
                      kk = j-1 ;
                      for ( k=i ; k<j ; k++,kk--)
                          {
                           bidi_ucs[k] = ucs[kk] ;
                          }
                  goto END_BIDI ;
                 }
             }
          else
             {
              /*----------------------------------------------------*/
              /* FOUND English Letter, Search for 1st Arabic Letter */
              /*----------------------------------------------------*/
              for ( j=i+1 ; j<len ; j++ )
                  {
                   if ( ucs[j] >= 0x621  &&  ucs[j] <= 0x64A )    // Arabic Letters
                      {
                       for ( k=i ; k<j ; k++ )
                           {
                            bidi_ucs[k] = ucs[k] ;
                           }

                       i = j     ;
                       goto next_LTR_char ;
                      }
                  }

              /*---------------------------------------------------------*/
              /* If No more Arabic Found (the rest of string is English) */
              /*---------------------------------------------------------*/
              if ( j == len  )
                 {
                  for ( k=i ; k<j ; k++ )
                      {
                       bidi_ucs[k] = ucs[k] ;
                      }
                  goto END_BIDI ;
                 }

             }
         }
    }

 END_BIDI:

 //  printf("\nBIDI RESULT \n");
 //  for ( i=0; i < len; i++ )
 //      {  printf("[%02d]  ucs [%04X]   bidi_ucs [%04X] \n",i,ucs[i],bidi_ucs[i]);  }

 /*-----------------------------------------------------------*/
 /* 2.3 Copy the bidi string to ucs[]                         */
 /*-----------------------------------------------------------*/
 for ( i=0; i < len; i++ )
     {
      ucs[i]=bidi_ucs[i];
     }

 /*-------------------------------------------------------------------------------------------*/
 /*-------------------------------------------------------------------------------------------*/
 /*                                 3. Auto_Shape USC4 String                                 */
 /*-------------------------------------------------------------------------------------------*/
 /*-------------------------------------------------------------------------------------------*/
 for ( i=(len-1) ; i>=0 ; i-- )
     {
      gboolean have_previous = TRUE ;
      gboolean have_next     = TRUE ;

      /*-------------------------------------------------------------------*/
      /* 3.1 If not in Arabic Range, Check English Range & Arabic Numerics */
      /*-------------------------------------------------------------------*/
      if ( (ucs[i] < 0x621) || (ucs[i] > 0x64A) )
         {
          // DEBUG ("Character not in ARABIC Letter Range");

         if ((ucs[i] >= 0x20) && (ucs[i] <= 0x7E))  // ENGLISH Letters and Numeric
            {
             auto_shaped_ucs[x++] = english_table[ucs[i] - 0x20].isolated ;
            }
         else
         if ((ucs[i] >= 0x660) && (ucs[i] <= 0x66A)) // ARABIC Numeric
            {
             auto_shaped_ucs[x++] = arabic_numeric_table[ucs[i] - 0x660].isolated ;
            }
         else
         if ( ucs[i] == 0x61F )  // ARABIC Question Mark
            {
             auto_shaped_ucs[x++] = 0x02EE ;
            }
         else
         if ( ucs[i] == 0x60C )  // ARABIC comma
            {
             auto_shaped_ucs[x++] = 0x02EC ;
            }
         else
         if ( ucs[i] == 0x61B )  // ARABIC dotted comma
            {
             auto_shaped_ucs[x++] = 0x02ED ;
            }
         else                    // Replace any other Charcter with space
            {
             auto_shaped_ucs[x++] =  0x0020 ;  // (0x0020 -> space, 0x0000 -> blank box)
            }
          continue;
         }

      /*-----------------------------------------------------------------*/
      /* 3.2 If in Arabic Range, but junk character, replace with space  */
      /*-----------------------------------------------------------------*/
      if (arabic_table[(ucs[i] - 0x621)].junk)
         {
          // DEBUG ("Junk character");
          auto_shaped_ucs[x++] =  0x0020 ;
          continue;
         }

      /*-------------------------------------------------------------*/
      /* 3.3 Check if character have previous                        */
      /*-------------------------------------------------------------*/
      if (((ucs[i + 1] < 0x621) || (ucs[i + 1] > 0x64A)) ||
          (!(arabic_table[(ucs[i + 1] - 0x621)].initial) &&
           !(arabic_table[(ucs[i + 1] - 0x621)].medial)))
         {
          // DEBUG ("No previous");
          have_previous = FALSE;
         }

      /*-------------------------------------------------------------*/
      /* 3.4 Check if character have next                            */
      /*-------------------------------------------------------------*/
      if (((ucs[i - 1] < 0x621) || (ucs[i - 1] > 0x64A)) ||
          (!(arabic_table[(ucs[i - 1] - 0x621)].medial) &&
           !(arabic_table[(ucs[i - 1] - 0x621)].final)
             && (ucs[i - 1] != 0x640)))
         {
          // DEBUG ("No next\n");
          have_next = FALSE;
         }

      /*-------------------------------------------------------------*/
      /* 3.5 Check if character is ARABIC LAM                        */
      /*-------------------------------------------------------------*/
      if (ucs[i] == 0x644)
         {
          if (have_next)
             {
              if ( (ucs[i - 1] == 0x622) ||
                   (ucs[i - 1] == 0x623) ||
                   (ucs[i - 1] == 0x625) ||
                   (ucs[i - 1] == 0x627) ) // ARABIC ALEF
                 {
                  if (have_previous)
                     {
                      if (ucs[i - 1] == 0x622)
                         {
                          auto_shaped_ucs[x++] = 0xCC ; // Dec 182, indigo Glyph 0x03F6;
                         }
                      else
                      if (ucs[i - 1] == 0x623)
                         {
                          auto_shaped_ucs[x++] = 0xCE ; // Dec 184, indigo Glyph 0x03F8;
                         }
                      else
                      if (ucs[i - 1] == 0x625)
                         {
                          auto_shaped_ucs[x++] = 0xE0 ; // Dec 187, indigo Glyph 0x03FA;
                         }
                      else
                         {
                          auto_shaped_ucs[x++] = 0xE2 ; // Dec 187, indigo Glyph 0x03FC;
                         }
                     }
                  else
                     {
                      if (ucs[i - 1] == 0x622)
                         {
                          auto_shaped_ucs[x++] = 0xCB ; // Dec 181, indigo Glyph 0x03F5;
                         }
                      else
                      if (ucs[i - 1] == 0x623)
                         {
                          auto_shaped_ucs[x++] = 0xCD ; // Dec 183, indigo Glyph 0x03F7;
                         }
                      else
                      if (ucs[i - 1] == 0x625)
                         {
                          auto_shaped_ucs[x++] = 0xCF ; // Dec 186, indigo Glyph 0x03F9;
                         }
                     else
                         {
                          auto_shaped_ucs[x++] = 0xE1 ; // Dec 186, indigo Glyph 0x03FB;
                         }
                     }
                  i--;
                  continue;
               }
            }
         }

      /*-------------------------------------------------------------*/
      /* 3.6 Give the correct shape to any other character           */
      /*-------------------------------------------------------------*/
      if ( (have_previous) && (have_next) && (arabic_table[(ucs[i] - 0x621)].medial) )
         {
          //////////////
          //  Medial  //
          //////////////
          auto_shaped_ucs[x++] = arabic_table[(ucs[i] - 0x621)].medial;
          continue;
         }
      else
      if ( (have_previous) && (arabic_table[(ucs[i] - 0x621)].final) )
         {
          //////////////
          //  Final   //
          //////////////
          auto_shaped_ucs[x++] = arabic_table[(ucs[i] - 0x621)].final;
          continue;
         }
      else
      if ( (have_next) && (arabic_table[(ucs[i] - 0x621)].initial) )
         {
          ///////////////
          //  Initial  //
          ///////////////
          auto_shaped_ucs[x++] = arabic_table[(ucs[i] - 0x621)].initial;
          continue;
         }
      else
         {
          ////////////////
          //  Isolated  //
          ////////////////
          if ( arabic_table[(ucs[i] - 0x621)].isolated )
             {
              auto_shaped_ucs[x++] = arabic_table[(ucs[i] - 0x621)].isolated;
             }
          else
             {
              auto_shaped_ucs[x++] = ucs[i];
             }
          continue;
         }

     }  // end for loop

 auto_shaped_ucs[x] = 0x0;

 /*-------------------------------------------------------------*/
 /* 3.7 Reverse the auto_shaped string                          */
 /*-------------------------------------------------------------*/
 len = x ;
 for ( i=1 ; i<=len; i++)
     {
      auto_shaped_ucs_R[i-1] = auto_shaped_ucs [len-i] ;
     }


 /*-------------------------------------------------------------------------------------------*/
 /*-------------------------------------------------------------------------------------------*/
 /*                    4. Generate Single byte Arabic Ascii code string                       */
 /*-------------------------------------------------------------------------------------------*/
 /*-------------------------------------------------------------------------------------------*/

 strcpy(utf,"") ;

 for ( i=0; i < len; i++ )
     {
      if (auto_shaped_ucs_R[i] >64  &&  auto_shaped_ucs_R[i] < 122 )
         {
          utf[i] = auto_shaped_ucs_R[i] - '\1' ;
          printf("[%02d] Charater [%04X] Dec [%d]  Symbol [%d]\n",i,auto_shaped_ucs_R[i],auto_shaped_ucs_R[i],utf[i]);
         }
      else
         {
          utf[i] = auto_shaped_ucs_R[i]   ;
          printf("[%02d] Charater [%04X] Dec [%d]  Symbol [%d]\n",i,auto_shaped_ucs_R[i],auto_shaped_ucs_R[i],utf[i]);
         }
     }
 utf[len] = '\0' ;

/*
 unsigned char symbol [5] ;
 for ( i=0; i < len; i++ )
     {
      if (auto_shaped_ucs_R[i] >64  &&  auto_shaped_ucs_R[i] < 122 )
         {
          sprintf(symbol,"%c", (auto_shaped_ucs_R[i])-1 );
          strcat (utf,symbol);
          printf("[%02d] Charater [%04X] Dec [%d]  Symbol [%d]\n",i,auto_shaped_ucs_R[i],auto_shaped_ucs_R[i],(int)utf[i]);
         }
      else
         {
          sprintf(symbol,"%c", (auto_shaped_ucs_R[i]) );
          strcat (utf,symbol);
          printf("[%02d] Charater [%04X] Dec [%d]  Symbol [%d]\n",i,auto_shaped_ucs_R[i],auto_shaped_ucs_R[i],(int)utf[i]);
          }
     }
 utf[len] = '\0' ;
*/


/*
      char hex   [7] ;
      char glyph [7] ;
      printf("[%02d] charater [%04X]  ",i,auto_shaped_ucs_R[i]);
      sprintf(hex,"%X",auto_shaped_ucs_R[i]);
      switch ( strlen(hex) )
             {
              case 1:
                   sprintf(glyph,"%c",hex[0] ) ;
                   strcat (utf,glyph) ;
                   printf ("hex   [%4s]  ",hex)   ;
                   printf ("glyph [%6s]\n",glyph) ;
                   break ;
              case 2:
                   sprintf(glyph,"%c%c",hex[0],hex[1] ) ;
                   strcat (utf,glyph) ;
                   printf ("hex   [%4s]  ",hex)   ;
                   printf ("glyph [%6s]\n",glyph) ;
                   break ;
              case 3:
                   sprintf(glyph,"%c%c%c",hex[0],hex[1],hex[2] ) ;
                   strcat (utf,glyph) ;
                   printf ("hex   [%4s]  ",hex)   ;
                   printf ("glyph [%6s]\n",glyph) ;
                   break ;
             }
*/



 /*-------------------------------------------------------------------------------------------*/
 /*-------------------------------------------------------------------------------------------*/
 /*                             5. Free data sturcture & return                               */
 /*-------------------------------------------------------------------------------------------*/
 /*-------------------------------------------------------------------------------------------*/
 g_free (ucs);
 g_free (bidi_ucs);
 g_free (auto_shaped_ucs);
 g_free (auto_shaped_ucs_R);

 return 0;

}

