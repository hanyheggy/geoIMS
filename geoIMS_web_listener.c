/*-------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------*/
/*  HOME                         geoIMS_web_listenser.c                          */
/*-------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------*/
/*                            Standard Include Files                             */
/*-------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

/*-------------------------------------------------------------------------------*/
/*                             Socket Include Files                              */
/*-------------------------------------------------------------------------------*/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>

/*-------------------------------------------------------------------------------*/
/*                             Thrread Include Files                             */
/*-------------------------------------------------------------------------------*/
#include <pthread.h>

/*-------------------------------------------------------------------------------*/
/*                             geoIMS Include Files                              */
/*-------------------------------------------------------------------------------*/
#include "include/geoIMSextern.h"

/*-------------------------------------------------------------------------------*/
/*                              Function Declaration                             */
/*-------------------------------------------------------------------------------*/
void * client_agent() ;

/*-------------------------------------------------------------------------------*/
/*                               Global Variables                                */
/*-------------------------------------------------------------------------------*/
int     create_socket        ;
int     client_socket [200]  ;
int     addrlen              ;
int     connected_clients    ;
int     connection_handle    ;

struct  sockaddr_in  address ;


/*-------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------*/
/*  1. Create TCP Socket                                                         */
/*  2. Set    Socket Proprites ( IP, Port, Blocking Mode )                       */
/*  3. Bind   Socket                                                             */
/*  4. Listen on Port                                                            */
/*  5. Generate Web include file                                                 */
/*  6. Accept Connection Loop                                                    */
/*-------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------*/
/*                                web_listener()                                 */
/*-------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------*/
void * web_listener()
{
 /*-------------------------*/
 /* Local variables         */
 /*-------------------------*/
 int        i   = 0                      ;
 int        rc  = 0                      ;
 FILE       *fp_o                        ;
 pthread_t  client_agent_thread [200]    ;

 char       module[]={"Web Listener"}    ;


RETRY:

 /*-------------------------*/
 /* Initialize variables    */
 /*-------------------------*/
 connected_clients = 0 ;
 connection_handle = 0 ;

 for ( i=0; i<200; i++ )
     {
      session[i].status = 0 ;
      strcpy (session[i].php_id,"");
     }

 /*------------------------------------------------------------*/
 /* 1. Create TCP Socket                                       */
 /*------------------------------------------------------------*/
 if ((create_socket = socket(AF_INET,SOCK_STREAM,0)) > 0)
    {
     printf("INFO  : Socket created successfully\n");
    }
 else
    {
     //sprintf(log,"Failed to create socket, Retry after 1 second ...");
     //system_log(moduleid,"ERROR",module,log);
     printf("ERROR : Failed to create socket, Retry after 1 second ...");
     sleep (1)  ;
     goto RETRY ;
    }

 /*------------------------------------------------------------*/
 /* 2. Set Socket Proprities (IP, Port, Blocking Mode, ...)    */
 /*------------------------------------------------------------*/
 address.sin_family      = AF_INET                 ;  // ( AF  -> TCP )  ( PF -> UDP )
 address.sin_addr.s_addr = inet_addr(sys.web_ip)   ;  // = INADDR_ANY ;   IF we need to listen on ALL IP's
 address.sin_port        = htons    (sys.web_port) ;
 /*
 if (fcntl(create_socket,F_SETFL ,O_NONBLOCK) < 0 )
    { printf("ERROR : Cannot set socket nonblocking mode\n"); }
 */

 /*------------------------------------------------------------*/
 /* 3. Bind Socket to IP & Port                                */
 /*------------------------------------------------------------*/
 if (bind(create_socket,(struct sockaddr *)&address,sizeof(address)) == 0)
    {
     printf("INFO  : Socket binded to port successfully\n");
    }
 else
    {
     // sprintf(log,"Failed to bind socket to port [%d], Retry port [%d] ...",sys.web_port,sys.web_port+1);
     // system_log(moduleid,"ERROR",module,log);
     printf("ERROR : Failed to bind socket to port [%d], Retry port [%d] ...\n",sys.web_port,sys.web_port+1);
     close(create_socket);
     sys.web_port++  ;
     goto RETRY ;
    }

 /*------------------------------------------------------------*/
 /* 4. Listen on port ( Pending connection Queue Max of 50 )   */
 /*------------------------------------------------------------*/
 listen(create_socket,50);
 addrlen = sizeof(struct sockaddr_in);
 printf("INFO  : Start listening on port [%d]\n",sys.web_port);

 /*------------------------------------------------------------*/
 /* 5. Generate Web IP-Port include file                       */
 /*------------------------------------------------------------*/
 fp_o=fopen(sys.web_include_file,"wt");
 if  ( fp_o== NULL )
     {
      printf("ERROR : Cannnot open WEB include file [%s]",sys.web_include_file);
      //sprintf(log,"Cannnot open WEB include file [%s]",sys.web_include_file);
      //system_log(moduleid,"SEVERE ERROR",module,log);
     }
 else
     {
      fprintf(fp_o,"<? $address=\"%s\"; $service_port=\"%d\"; ?> \n",sys.web_ip,sys.web_port);
      fclose (fp_o ) ;
      /*
      if ( sys.log_level >= 3 )
         {
          sprintf(log,"Start listening to port [%d]",sys.web_port);
          system_log(moduleid,"INFO",module,log);
         } */
     }

 /*------------------------------------------------------------*/
 /* 6. Accept Connection                                       */
 /*------------------------------------------------------------*/
 do{
    connection_handle++ ;

    client_socket[connection_handle] = accept(create_socket,(struct sockaddr *)&address,&addrlen);
    if (client_socket[connection_handle] > 0)
       {
        /*------------------------*/
        /* Create Agent Thread    */
        /*------------------------*/
        // printf("INFO  : Client IP [%s] is connected ...\n",inet_ntoa(address.sin_addr));
        rc = pthread_create(&client_agent_thread[connection_handle], NULL, client_agent,(int*) connection_handle);
        if ( rc != 0 )
           {
            printf("ERROR : Failed to create client_agent thread \n");
            connection_handle-- ;
	    continue ;
	   }
        else
	   {
            connected_clients++ ;
	   }
        }
     else
        {
         printf ("ERROR : Client [%s] Connection falied \n",inet_ntoa(address.sin_addr));
         connection_handle-- ;
        }

    /*---------------------------*/
    /* Check if Restart Needed   */
    /*---------------------------*/
    if ( connected_clients < 0 )
       {
        printf ("INFO  : Number of connected clients = %d \n",connected_clients);
        close(create_socket);
        goto RETRY ;
       }

    /*---------------------------*/
    /* Wait xx Seconds           */
    /*---------------------------*/
    sleep (1) ;


   } while(1) ;


 close(create_socket);

 return (NULL);

}

/*-------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------*/
/*  1. Recieve Request                                                           */
/*  2. Creat New Session if needed, else use Exsisting Session (sid)             */
/*  3. Execute GIS Fuctions based on recieved command                            */
/*  4. Send Image Path/Name to Client                                            */
/*  5. Close Scoket and end thread, return                                       */
/*-------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------*/
/*                                client_agent()                                 */
/*-------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------*/
void * client_agent(int client_id)
{
 int    i            = 0                ;
 int    sid          = 0                ;
 
 int    bufsize      = 1024             ;
 char   *recv_buffer = malloc(bufsize)  ;
 char   *send_buffer = malloc(bufsize)  ;
 char   my_buffer            [bufsize]  ;
 
 char   php_session          [40]       ;
 char   geoIMS_cmd           [100]      ;
 
 char   image_file_name      [50]       ;
 char   image_full_path_name [200]      ;

 char   system_cmd           [100]      ;
 float  x1,y1,x2,y2                     ;
 
 time_t current_time                    ;   // Time string


 // printf("Client [%d] >> Start Processing\n",client_id);


 /*------------------------------------------------------------*/
 /* 1. Recieve Request                                         */
 /*------------------------------------------------------------*/
 recv(client_socket[client_id],recv_buffer,bufsize,0 ); // MSG_NOSIGNAL
 if ( strlen(recv_buffer) == 0 )
    {
     sprintf(send_buffer,"INFO  : Empty buffer",recv_buffer);
     goto SEND ;
    }
 else
    {
     // Copy recv_buffer (charcter pointer) to my_buffer (local charcter array)
     strncpy (my_buffer,recv_buffer,strlen(recv_buffer)-1) ;
     my_buffer[strlen(recv_buffer)] = '\0' ;
     // printf("Client [%d] >> Command recieved [%s] \n",client_id,my_buffer);
    }

 /*------------------------------------------------------------*/
 /* 2. Check if Session exsist get its sid else create one     */
 /*------------------------------------------------------------*/
 sscanf (my_buffer,"%s%s",php_session, geoIMS_cmd);

 sid = 0 ;
 for ( i=1; i<200; i++ )
     {
      if (strcmp (php_session, session[i].php_id) == 0 )
         {
          time   (&current_time)                 ;
          session[i].start_time = current_time   ; // Save Session last action time Time  
          fprintf(stdout,"INFO  : Exsisting Session [%d], last action time [%d]\n",i,current_time);
	  // printf(">>>>>>>>>>>>> Session exsist sid = %d \n\n",sid);
          sid = i ;
	  
	  break ;
	 }
      }

 GET_SESSION:
      
 if ( sid == 0 ) // New Session
    {
     for ( i=1; i<200; i++ )
         {
          if ( session[i].status == 0 )
             {
	      session[i].status     = 1              ;
	      session[i].x_min      = x_min          ;  // Initial MAP ( Xmin,Ymin,Xmax,Ymax )
	      session[i].y_min      = y_min          ;
	      session[i].x_max      = x_max          ;
	      session[i].y_max      = y_max          ;
              strcpy (session[i].php_id,php_session) ;
	      
	      time   (&current_time)                 ;
	      session[i].start_time = current_time   ; // Save Session Start Time  
              
	      fprintf(stdout,"INFO  : New Session [%d], start time [%d]\n",i,current_time);
              // printf(">>>>>>>>>> NEW Session created sid = %d  \n\n",sid);
              sid = i  ;
	      
              break ;
	     }
	 }
      }

 if ( sid == 0 )
    {
     sleep (1)        ;
     goto GET_SESSION ;
    } 
      
 /*------------------------------------------------------------*/
 /* 3. Execute GIS Fuctions based on recived command           */
 /*------------------------------------------------------------*/
 if ( strcmp(geoIMS_cmd,"draw_all") == 0 )
    {
     sprintf (image_full_path_name,"/home/geoinfo/WEB/gis/maps/%s.%d.gif",php_session,client_id ) ;
     draw_all(image_full_path_name,sid)  ;
     sprintf (image_file_name,"maps/%s.%d.gif",php_session,client_id) ;
     strcpy  (send_buffer,image_file_name);
    }
 else
 if ( strcmp(geoIMS_cmd,"zoom_in") == 0 )
    {
     sprintf (image_full_path_name,"/home/geoinfo/WEB/gis/maps/%s.%d.gif",php_session,client_id ) ;
     zoom_in (image_full_path_name,sid)  ;
     sprintf (image_file_name,"maps/%s.%d.gif",php_session,client_id ) ;
     strcpy  (send_buffer,image_file_name);
    }
 else
 if ( strcmp(geoIMS_cmd,"zoom_out") == 0 )
    {
     sprintf (image_full_path_name,"/home/geoinfo/WEB/gis/maps/%s.%d.gif",php_session,client_id ) ;
     zoom_out(image_full_path_name,sid)  ;
     sprintf (image_file_name,"maps/%s.%d.gif",php_session,client_id ) ;
     strcpy  (send_buffer,image_file_name);
    }
 else
 if ( strcmp(geoIMS_cmd,"zoom_all") == 0 )
    {
     sprintf (image_full_path_name,"/home/geoinfo/WEB/gis/maps/%s.%d.gif",php_session,client_id ) ;
     zoom_all(image_full_path_name,sid)  ;
     sprintf (image_file_name,"maps/%s.%d.gif",php_session,client_id ) ;
     strcpy  (send_buffer,image_file_name);
    }
 else
 if ( strcmp(geoIMS_cmd,"pan_left") == 0 )
    {
     sprintf (image_full_path_name,"/home/geoinfo/WEB/gis/maps/%s.%d.gif",php_session,client_id ) ;
     pan_left(image_full_path_name,sid)  ;
     sprintf (image_file_name,"maps/%s.%d.gif",php_session,client_id ) ;
     strcpy  (send_buffer,image_file_name);
    }
 else
 if ( strcmp(geoIMS_cmd,"pan_right") == 0 )
    {
     sprintf  (image_full_path_name,"/home/geoinfo/WEB/gis/maps/%s.%d.gif",php_session,client_id ) ;
     pan_right(image_full_path_name,sid)  ;
     sprintf  (image_file_name,"maps/%s.%d.gif",php_session,client_id ) ;
     strcpy   (send_buffer,image_file_name);
    }
 else
 if ( strcmp(geoIMS_cmd,"pan_up") == 0 )
    {
     sprintf (image_full_path_name,"/home/geoinfo/WEB/gis/maps/%s.%d.gif",php_session,client_id ) ;
     pan_up  (image_full_path_name,sid)  ;
     sprintf (image_file_name,"maps/%s.%d.gif",php_session,client_id ) ;
     strcpy  (send_buffer,image_file_name);
    }
 else
 if ( strcmp(geoIMS_cmd,"pan_down") == 0 )
    {
     sprintf (image_full_path_name,"/home/geoinfo/WEB/gis/maps/%s.%d.gif",php_session,client_id);
     pan_down(image_full_path_name,sid);
     sprintf (image_file_name,"maps/%s.%d.gif",php_session,client_id);
     strcpy  (send_buffer,image_file_name);
    }
 else
 if ( strcmp(geoIMS_cmd,"window") == 0 )
    {
     sscanf  (my_buffer,"%s %s %f %f %f %f",php_session, geoIMS_cmd,&x1,&y1,&x2,&y2);
     sprintf (image_full_path_name,"/home/geoinfo/WEB/gis/maps/%s.%d.gif",php_session,client_id);
     window  (image_full_path_name,(int)x1,499-(int)y1,(int)x2,499-(int)y2,sid);
     sprintf (image_file_name,"maps/%s.%d.gif",php_session,client_id);
     strcpy  (send_buffer,image_file_name);
    }
 else
    {
     sprintf(send_buffer,"%s, Unknown Command.",recv_buffer);
    }


 /*------------------------------------------------------------*/
 /* 4. Send Image Name to Client                               */
 /*------------------------------------------------------------*/
 SEND:
 send(client_socket[client_id],send_buffer,strlen(send_buffer),0);


 /*------------------------------------------------------------*/
 /* 5. Close Socket, End Thread and Return                     */
 /*------------------------------------------------------------*/
 CLOSE:
 close(client_socket[client_id]);
 connected_clients-- ;
 // printf("Client [%d] >> Clinet IP [%s] Disconnected\n",client_id,inet_ntoa(address.sin_addr));

 return (NULL);
}

/*-------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------*/
/*                           stamp_session_start_time()                          */
/*-------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------*/
stamp_session_start_time ( int sid )
{ 
 //char        TIMEIN[21]                      ;   // Time variable
 time_t      current_time                    ;   // Time string
 //struct tm  *time_structure                  ;   // Time structure

 /*---------------------------------------------------*/
 /* Allocate time_structure                           */
 /*---------------------------------------------------*/
 time (&current_time);
 //time_structure = localtime (&current_time) ;

 /*----------------------------------------------------------------*/
 /* Format  System timestamp to DB format                          */
 /*----------------------------------------------------------------
  sprintf (TIMEIN,"%4d-%02d-%02d-%02d.%02d.%02d"
                 ,time_structure->tm_year+1900
                 ,time_structure->tm_mon+1
                 ,time_structure->tm_mday
                 ,time_structure->tm_hour
                 ,time_structure->tm_min
                 ,time_structure->tm_sec );

 /*----------------------------------------------------------------*/
 /* Stamp Session start time                                       */
 /*----------------------------------------------------------------*/
 
 //session[sid].start_time = time_structure->tm_hour*3600 + time_structure->tm_min*60 + time_structure->tm_sec  ;
// printf("Session start time [%s] in seconds [%d] current_time[%d]\n",TIMEIN,session[sid].start_time,current_time);
 printf("Session start time [%d]\n",current_time);

}




