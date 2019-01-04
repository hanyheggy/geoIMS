static char sqla_program_id[162] = 
{
 42,0,65,68,65,75,65,73,71,69,79,78,69,84,87,79,111,65,78,97,
 78,70,72,86,48,49,49,49,49,32,50,32,8,0,71,69,79,73,78,70,
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


#line 1 "geonetwork.sqc"
/*------------------------------------------------------------------------*/
/*              geoINFO/6000  Shortest Path ( geonetwork.sqc )            */
/*------------------------------------------------------------------------*/

/*------------------------------------------------------------------------*/
/*                          Standard Include Files                        */
/*------------------------------------------------------------------------*/
#include "include/geoIMSextern.h"

#include <sqlenv.h>
#include <sqlda.h>

// #define  CHECKERR(CE_STR) if (check_error (CE_STR,&sqlca) != 0) printf("error");

/*
EXEC SQL INCLUDE SQLCA;
*/

/* SQL Communication Area - SQLCA - structures and constants */
#include "sqlca.h"
struct sqlca sqlca;


#line 14 "geonetwork.sqc"



#define  Max_Path         60000
#define  Path_Nodes       200
#define  Max_Net_Node     300
#define  Max_Arc_at_Node  10


/*------------------------------------------------------------------------*/
/*                           Functions Prototypes                         */
/*------------------------------------------------------------------------*/
void search_at_node();


/*------------------------------------------------------------------------*/
/*                   Global Variable Definition                           */
/*------------------------------------------------------------------------*/

unsigned short count        [Max_Path]             ;
unsigned short path         [Max_Path][Path_Nodes] ;
unsigned short path_segment [Max_Path][Path_Nodes] ;
unsigned short path_update  [Max_Path]             ;
unsigned short path_weight  [Max_Path]             ;


typedef struct
  {
   unsigned short current                     ;
   unsigned short count                       ;
   unsigned short s_node    [Max_Arc_at_Node] ;
   unsigned short arc       [Max_Arc_at_Node] ;
   unsigned short e_node    [Max_Arc_at_Node] ;
   unsigned short weight    [Max_Arc_at_Node] ;
   unsigned short direction [Max_Arc_at_Node] ;
  } Nodes  ;

Nodes node[Max_Net_Node]        ;
int   k                         ;
int   node_count                ;
int   path_count                ;
int   real_path_count           ;
int   branch_counter            ;
int   need_update               ;
int   last_arc_weight           ;  // To hold weight before new segmaent at case 2
int   min_weight                ;
int   min_path                  ;



/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 63 "geonetwork.sqc"

   long    s_node1              ;
   long    arc1                 ;
   long    e_node1              ;
   long    weight1              ;
   long    direction            ;
   long    far_node             ;
   long    current_node         ;
   long    previous_node        ;

/*
EXEC SQL END DECLARE SECTION;
*/

#line 72 "geonetwork.sqc"




/*------------------------------------------------------------------------*/
/*                           shortest_path()                              */
/*------------------------------------------------------------------------*/
void shortest_path(int origin, int dest)
{
 int ii ;


 ///////////////////////////////////////////////////////////////////////////
 // Caching Nodes & possible New Nodes
 ///////////////////////////////////////////////////////////////////////////

 printf("===============================================\n");
 printf(">> Caching Network Information From DataBase <<\n");
 printf("===============================================\n");

 // Declare DB Cursors
 
/*
EXEC SQL DECLARE path0  CURSOR FOR
          SELECT  NODE_NUM
          FROM    NODE
          FOR     READ ONLY ;
*/

#line 96 "geonetwork.sqc"


 
/*
EXEC SQL DECLARE path1  CURSOR FOR
          SELECT  S_NODE ,
                  ARC    ,
        	  E_NODE ,
	          WEIGHT ,
	          DIRECTION
	  FROM    CONNECTIVITY
          WHERE   E_NODE = :current_node OR ( S_NODE = :current_node  AND  DIRECTION = 1 )
	  FOR     READ ONLY ;
*/

#line 106 "geonetwork.sqc"


 // Initailize Node variables
 for (i=1; i<=(Max_Net_Node-1) ; i++)
     {
      node[i].current = 0 ;
      node[i].count   = 0 ;
      for (ii=1; ii<=(Max_Arc_at_Node-1) ; ii++)
          {
           node[i].s_node[ii]    = 0 ;
           node[i].arc   [ii]    = 0 ;
           node[i].e_node[ii]    = 0 ;
           node[i].weight[ii]    = 0 ;
           node[i].direction[ii] = 0 ;
          }
     }

 // Caching Nodes From Node Table
 //..............................
 
/*
EXEC SQL OPEN  path0    ;
*/

{
#line 125 "geonetwork.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 125 "geonetwork.sqc"
  sqlacall((unsigned short)26,1,0,0,0L);
#line 125 "geonetwork.sqc"
  sqlastop(0L);
}

#line 125 "geonetwork.sqc"

 // CHECKERR ("OPEN CURSOR");
 do {
     
/*
EXEC SQL FETCH path0 INTO :s_node1 ;
*/

{
#line 128 "geonetwork.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 128 "geonetwork.sqc"
  sqlaaloc(3,1,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 128 "geonetwork.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 128 "geonetwork.sqc"
      sql_setdlist[0].sqldata = (void*)&s_node1;
#line 128 "geonetwork.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 128 "geonetwork.sqc"
      sqlasetdata(3,0,1,sql_setdlist,NULL,0L);
    }
#line 128 "geonetwork.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 128 "geonetwork.sqc"
  sqlastop(0L);
}

#line 128 "geonetwork.sqc"

     if ( SQLCODE != 0 )  break ;
     if ( s_node1 != 0 )
        {
         node_count++  ;
         node[s_node1].current = s_node1 ;
         // printf("node_count    = %d   " ,node_count    );
         // printf("s_node1       = %d   " ,s_node1       );
         // printf("node[s_node1] = %d \n" ,node[s_node1].current );
        }
    } while(1);
 
/*
EXEC SQL CLOSE path0  ;
*/

{
#line 139 "geonetwork.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 139 "geonetwork.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 139 "geonetwork.sqc"
  sqlastop(0L);
}

#line 139 "geonetwork.sqc"


 // Caching ALL Nodes Connected to the Current Node
 //................................................
 for ( i=1; i<=(Max_Net_Node-1) ; i++ )
     {
      if (node[i].current != 0 )
         {
          k = 0 ;
          current_node = node[i].current ;

          
/*
EXEC SQL OPEN  path1    ;
*/

{
#line 150 "geonetwork.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 150 "geonetwork.sqc"
  sqlaaloc(2,2,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 150 "geonetwork.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 150 "geonetwork.sqc"
      sql_setdlist[0].sqldata = (void*)&current_node;
#line 150 "geonetwork.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 150 "geonetwork.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 150 "geonetwork.sqc"
      sql_setdlist[1].sqldata = (void*)&current_node;
#line 150 "geonetwork.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 150 "geonetwork.sqc"
      sqlasetdata(2,0,2,sql_setdlist,NULL,0L);
    }
#line 150 "geonetwork.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 150 "geonetwork.sqc"
  sqlastop(0L);
}

#line 150 "geonetwork.sqc"

          // CHECKERR ("OPEN CURSOR");

          do {
              
/*
EXEC SQL FETCH path1 INTO :s_node1, :arc1, :e_node1, :weight1, :direction ;
*/

{
#line 154 "geonetwork.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 154 "geonetwork.sqc"
  sqlaaloc(3,5,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 154 "geonetwork.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 154 "geonetwork.sqc"
      sql_setdlist[0].sqldata = (void*)&s_node1;
#line 154 "geonetwork.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 154 "geonetwork.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 154 "geonetwork.sqc"
      sql_setdlist[1].sqldata = (void*)&arc1;
#line 154 "geonetwork.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 154 "geonetwork.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 154 "geonetwork.sqc"
      sql_setdlist[2].sqldata = (void*)&e_node1;
#line 154 "geonetwork.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 154 "geonetwork.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 154 "geonetwork.sqc"
      sql_setdlist[3].sqldata = (void*)&weight1;
#line 154 "geonetwork.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 154 "geonetwork.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 154 "geonetwork.sqc"
      sql_setdlist[4].sqldata = (void*)&direction;
#line 154 "geonetwork.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 154 "geonetwork.sqc"
      sqlasetdata(3,0,5,sql_setdlist,NULL,0L);
    }
#line 154 "geonetwork.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 154 "geonetwork.sqc"
  sqlastop(0L);
}

#line 154 "geonetwork.sqc"

              if ( SQLCODE != 0    ) break ;
              node[i].s_node[++k ] = s_node1   ;
              node[i].arc   [k]    = arc1      ;
              node[i].e_node[k]    = e_node1   ;
              node[i].weight[k]    = weight1   ;
              node[i].direction[k] = direction ;
             } while(1);

          node[i].count = k  ;
          
/*
EXEC SQL CLOSE path1 ;
*/

{
#line 164 "geonetwork.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 164 "geonetwork.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 164 "geonetwork.sqc"
  sqlastop(0L);
}

#line 164 "geonetwork.sqc"

         }
     }

 //  print node data
 /*
   for ( i=1; i<= node_count ; i++ )
       {
        printf("[ i = %d ] Node = %d \n",i ,node[i].current ) ;
        for ( k=1; k<= node[i].count ; k++ )
            {
             printf("s_node = %d    " ,node[i].s_node[k] );
             printf("arc    = %d    " ,node[i].arc[k]    );
             printf("e_node = %d    " ,node[i].e_node[k] );
             printf("weight = %d    " ,node[i].weight[k] );
             printf("direction = %d \n" ,node[i].direction[k] );
            }
       }
 */




 ///////////////////////////////////////////////////////////////////////////
 // Initialize variables
 ///////////////////////////////////////////////////////////////////////////
 i  = 0 ;
 ii = 0 ;
 k  = 0 ;
 path_count      = 0        ;
 node_count      = 0        ;
 real_path_count = 0        ;
 min_weight      = 99999999 ;

 for (i=0; i<=(Max_Path -1); i++)
     {
      count[i]       = 0 ;
      path_weight[i] = 0 ;
      path_update[i] = 0 ;
      for (ii=0; ii<=(Path_Nodes -1); ii++)
          {
           path[i][ii]         = 0 ;
           path_segment[i][ii] = 0 ;
          }
     }

 ///////////////////////////////////////////////////////////////////////////
 // Search at Destenation Node
 ///////////////////////////////////////////////////////////////////////////
 printf(">>>>>>>>>> Search at Destenation  Node <<<<<<<<<<\n");

 current_node = dest ;
 search_at_node (origin, dest, current_node) ;

 if ( path_count == 0 )
    {
     printf(" Error : Node [%d], Not Connected to Network ! \n",dest);
     return ;
    }

 ///////////////////////////////////////////////////////////////////////////
 // Search at Other Nodes
 ///////////////////////////////////////////////////////////////////////////
 do {
     need_update = 0 ;

     for ( i=1 ; i<= path_count ; i++ )
         {

          if (i < Max_Path )  path_update[i] = 0 ;

          if ( path[i][0] == 0 && i < Max_Path ) //&& path_weight[i] < min_weight )
             {
              need_update = 1 ;
              current_node = path[i][count[i]] ;

              search_at_node (origin, dest, current_node) ;

              /* if no Update Done (No more Nodes at path) skip path */
              if ( path_update[i] == 0 )
                 {
                  count[i]       = count[path_count]       ;
                  path_weight[i] = path_weight[path_count] ;
                  for ( k=0; k<=(Path_Nodes-1); k++ )
                      {
                       path[i][k]         = path[path_count][k]         ;
                       path_segment[i][k] = path_segment[path_count][k] ;
                      }
                  count[path_count]       = 0 ;
                  path_weight[path_count] = 0 ;
                  path_update[path_count] = 0 ;
                  for ( k=0; k<=(Path_Nodes-1); k++ )
                      {
                       path[path_count][k]         = 0 ;
                       path_segment[path_count][k] = 0 ;
                      }
                  path_count-- ;
                 }
             }
         }

     if ( need_update == 0 )  break ;
     printf("Real  Path count = %d \n",real_path_count);
     printf("Total Path count = %d \n",path_count);

    } while(1);


 ///////////////////////////////////////////////////////////////////////////
 //  print results
 ///////////////////////////////////////////////////////////////////////////


   for (i=1; i<= path_count; i++ )
     {
      if ( path[i][0] == 1 )  /* 0 Under process   1 Path   2 Ignored  */
         {
          printf("-----------------------------------------------------\n");
          for (ii=1; ii<= count[i]; ii++ )
              {
               printf ("PATH  [%d][%d] = %d \n",i,ii,path[i][ii]);
              }
          printf("Total Path Weight [%d] = %d \n",i,path_weight[i]);
         }
     }


 ///////////////////////////////////////////////////////////////////////////
 // Selecte Min Path
 ///////////////////////////////////////////////////////////////////////////
 min_weight = 99999999 ;

 for ( i=1 ; i <= path_count ; i++ )
     {
      if ( path[i][0] == 1 )  /* 0 Under process   1 Real Path   2 Ignored Path */
         {
          if ( min_weight > path_weight[i] )
             {
              min_path   =  i ;
              min_weight = path_weight[i] ;
             }
         }
     }

 ///////////////////////////////////////////////////////////////////////////
 // Highlight Shortest Path Segments
 ///////////////////////////////////////////////////////////////////////////
 k = 0 ;
 for ( ii=count[min_path] ; ii>= 2 ; ii-- )
     {
      printf ("PATH Segment [%d] = %d \n",++k,path_segment[min_path][ii]);
      for (i=1 ; i<= feat_count ; i++)
          {
           if ( feat[i].num == path_segment[min_path][ii] )
              {
               highlight_feature (i);
              }
          }
     }

 ///////////////////////////////////////////////////////////////////////////
 // Print Selected Min Path
 ///////////////////////////////////////////////////////////////////////////
 printf("--------------------------------------------------------------\n");
 printf(">>>>>>>>>>>>>  Min Path Number [ %d ]  <<<<<<<<<<<<<<\n",min_path);
 printf("Min Path Weight = %d \n",path_weight[min_path]);

 k = 0;
 for ( ii=count[min_path]; ii>= 1 ; ii-- )
     {
      printf ("PATH [%5d] = %3d \n",++k ,path[min_path][ii]);
     }

 printf("--------------------------------------------------------------\n");
 printf("Total Path count= %d \n",path_count);
 printf("--------------------------------------------------------------\n");
}


/*------------------------------------------------------------------------*/
/*                          search_at_node()                              */
/*------------------------------------------------------------------------*/
void search_at_node(int origin, int dest, int current_node)
{
 int index ;


 branch_counter = 0 ;

 for( index=1; index<=node[current_node].count; index++ )
    {
     s_node1   = node[current_node].s_node[index]    ;
     arc1      = node[current_node].arc[index]       ;
     e_node1   = node[current_node].e_node[index]    ;
     weight1   = node[current_node].weight[index]    ;
     direction = node[current_node].direction[index] ;

/*   printf("------------------------------------\n");
     printf("i            = %d \n",i                );
     printf("count[i]     = %d \n",count[i]         );
     printf("Current_node = %d \n",current_node     );

     printf("s_node = %d    " ,s_node1              );
     printf("arc    = %d    " ,arc1                 );
     printf("e_node = %d    " ,e_node1              );
     printf("weight = %d    " ,weight1              );
     printf("direction = %d \n",direction           );   */


     if ( s_node1 == dest && direction == 0 ) continue ;

     branch_counter++ ;
     	

     if ( current_node == dest )  /////////////  CASE I  ///////////////////
        {
         //printf("CASE 1");
         k = 0 ;
         path[++path_count][++k] = dest ;

         if ( s_node1 == current_node )
            { far_node = e_node1 ; }
         else
            { far_node = s_node1 ; }


         path[path_count][++k]       = far_node ;
         path_segment[path_count][k] = arc1     ;
         count[path_count]           = k        ;
         path_weight[path_count]    += weight1  ;

         if ( far_node == origin )
            {
             real_path_count++       ;
             path[path_count][0] = 1 ;
             if ( real_path_count == 1 )
                { min_weight = path_weight[path_count] ; }
             printf ("Origin Reached !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
            }
         printf ("  PATH [%5d]  %3d  %3d   Weight = %d\n",path_count,current_node,far_node,path_weight[path_count]);
        }


     else if ( branch_counter == 1 )  /////////  CASE II  /////////////////
        {
         //printf("CASE 2");
         k = count[i]    ;
         previous_node = path[i][count[i]-1];

         if ( s_node1 == current_node )
            { far_node = e_node1 ; }
         else
            { far_node = s_node1 ; }

         // printf("  prv_node = %d",previous_node);
         // printf("  far_node = %d",far_node);

         ///////////////////////////////////////////////////////////////////
         // Skip same Arc segment
         ///////////////////////////////////////////////////////////////////
         if ( far_node == previous_node )
            {
             branch_counter = 0 ;
             // printf("  skip same Arc\n");
             goto skip_case2 ;
            }

         ///////////////////////////////////////////////////////////////////
         // Skip Path if loop Found
         ///////////////////////////////////////////////////////////////////
         for (ii = 1; ii<= k; ii++)
             {
              if ( far_node == path[i][ii] )
                 {
                  branch_counter = 0 ;
                  // printf("  skip loop path  \n")   ;
                  goto skip_case2 ;
                 }
             }

         ///////////////////////////////////////////////////////////////////
         // Skip Path if its weight > min_weight
         ///////////////////////////////////////////////////////////////////
         if ( (path_weight[i] + weight1 ) > min_weight )
            {
             branch_counter = 0 ;
             // printf(" skip path for weight \n")   ;
             goto skip_case2 ;
            }


         path[i][++k]       = far_node ;
         path_segment[i][k] = arc1     ;
         count[i]           = k        ;
         path_update[i]     = 1        ;
         last_arc_weight    =  weight1 ;
         path_weight[i]    +=  weight1 ;
         printf ("  PATH [%5d]  %3d  %3d   Weight = %d\n",i,current_node,far_node,path_weight[i]);

         if ( far_node == origin )
            {
             real_path_count++ ;
             path[i][0] = 1    ;
             if ( real_path_count == 1 )
                { min_weight = path_weight[i] ; }
             else
             if ( min_weight > path_weight[i] )
                { min_weight = path_weight[i] ; }

             for ( ii=1 ; ii<=path_count ; ii++ )
                 {
                  if ( path_weight[ii] > min_weight )
                     {
                      count[ii]       = count[path_count]       ;
                      path_weight[ii] = path_weight[path_count] ;
                      for ( k=0; k<=(Path_Nodes-1); k++ )
                          {
                           path[ii][k]         = path[path_count][k]         ;
                           path_segment[ii][k] = path_segment[path_count][k] ;
                          }
                      count[path_count]       = 0 ;
                      path_weight[path_count] = 0 ;
                      path_update[path_count] = 0 ;
                      for ( k=0; k<=(Path_Nodes-1); k++ )
                          {
                           path[path_count][k]         = 0 ;
                           path_segment[path_count][k] = 0 ;
                          }
                      path_count-- ;
                     }
                 }
             printf ("Origin Reached !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
            }

         skip_case2:
         {int koko ;
               koko++ ; }
        }


     else  //////////////////////  CASE III  ///////////////////////////////
        {
         //printf("CASE 3");
         k = count[i] - 1  ;
         previous_node = path[i][k-1];


         if ( s_node1 == current_node )
            { far_node = e_node1 ; }
         else
            { far_node = s_node1 ; }

         // printf("  prv_node = %d",previous_node);
         // printf("  far_node = %d",far_node);

         ///////////////////////////////////////////////////////////////////
         // Skip same Arc segment
         ///////////////////////////////////////////////////////////////////
         if ( far_node == previous_node )
            {
             // printf("  skip same Arc\n");
             goto skip_case3 ;
            }

         ///////////////////////////////////////////////////////////////////
         // Skip Path if loop Found
         ///////////////////////////////////////////////////////////////////
         for (ii = 1; ii<= k; ii++)
             {
              if ( far_node == path[i][ii] )
                 {
                  // printf("  skip loop path  \n")   ;
                  goto skip_case3 ;
                 }
             }

         ///////////////////////////////////////////////////////////////////
         // Skip Path if its weight > min_weight
         ///////////////////////////////////////////////////////////////////
         if ( ( path_weight[i] - last_arc_weight + weight1) > min_weight )
            {
             // printf(" skip path for weight \n")   ;
             goto skip_case3 ;
            }


         if ( i > 64990  )
            {
             // printf(" skip path for weight \n")   ;
             goto skip_case3 ;
            }


         for (ii = 1; ii<= k; ii++)
             {
              path[path_count+1][ii]         = path[i][ii] ;
              path_segment[path_count+1][ii] = path_segment[i][ii] ;
             }

         path[++path_count][++k]     = far_node ;
         path_segment[path_count][k] = arc1     ;
         count[path_count]           = k        ;
         path_weight[path_count]     = path_weight[i] - last_arc_weight + weight1 ;

         printf ("  PATH [%5d]  %3d  %3d   Weight = %d\n",path_count,current_node,far_node,path_weight[path_count]);

         if ( far_node == origin )
            {
             real_path_count++       ;
             path[path_count][0] = 1 ;
             if ( real_path_count == 1 )
                { min_weight = path_weight[path_count] ; }
             else
             if ( min_weight > path_weight[path_count] )
                { min_weight = path_weight[path_count] ; }

             for ( ii=1 ; ii<=path_count ; ii++ )
                 {
                  if ( path_weight[ii] > min_weight )
                     {
                      count[ii]       = count[path_count]       ;
                      path_weight[ii] = path_weight[path_count] ;
                      for ( k=0; k<=(Path_Nodes-1); k++ )
                          {
                           path[ii][k]         = path[path_count][k]         ;
                           path_segment[ii][k] = path_segment[path_count][k] ;
                          }
                      count[path_count]       = 0 ;
                      path_weight[path_count] = 0 ;
                      path_update[path_count] = 0 ;
                      for ( k=0; k<=(Path_Nodes-1); k++ )
                          {
                           path[path_count][k]         = 0 ;
                           path_segment[path_count][k] = 0 ;
                          }
                      path_count-- ;
                     }
                 }
             printf ("Origin Reached !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
            }

         skip_case3:
                { int yoyoyo =0 ; }
        }


    } /* end of loop */

}
