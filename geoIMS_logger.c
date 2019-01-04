/*------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
/*                             Logging Module :  geoIMS_logger.c                                  */
/*------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/


//-----------------------------------------------------------------------------------------------
//   THINGS TO DO
//
// implement qeueuing (linked list)
// check timeout connection paramter 
// check if connection to DB is down, reconnect again
// DSN_NAME ,USER, PWD to be readed from paramter  file                   ( done )
// close this thread if odbc_replicator is flaged to be stopped           ( done )

//------------------------------------------------------------------------------------------------


/*------------------------------------------------------------------------------------------------*/
/*                                      Include Files                                             */
/*------------------------------------------------------------------------------------------------*/
#include "odbc_replicator.h"

/*------------------------------------------------------------------------------------------------*/
/*                                       Global Variables                                         */
/*------------------------------------------------------------------------------------------------*/
SQLHENV      log_env                    ; // Environment handle 
SQLHDBC      log_hdbc                   ; // Connection  handle 
SQLHSTMT     log_hstmt                  ; // Statement   handle  
SQLINTEGER   log_SQLCODE                ; // SQL Code          
char         log_SQLSTATE  [10]         ; // SQL Status           
char         log_SQLERR   [400]         ; // SQL Error Message 
SQLSMALLINT  log_SQLERRLEN              ; // SQL Message length


/*------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
/*                                     system_logger()                                            */
/*------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------*/
void * system_logger() 
{
 /*----------------------------*/
 /* Local Varibles             */
 /*----------------------------*/
 int       i  = 0                     ;   // Loop counter
 int       rc = 0                     ;   // Local return code
 time_t    current_time               ;   // Current time string  
 char      INSERT_SQL [1000]          ;   // SQL to be inserted to LOG table  
 
 char      module[]={"system_logger"} ;   // Module Name

 
 
 RE_CONNECT:
 
 sys.logger_status = 1 ;
 
 /*----------------------------------------------------------------------*/
 /* 1. allocate environment handle and register version                  */
 /*----------------------------------------------------------------------*/
 rc = SQLAllocHandle ( SQL_HANDLE_ENV, SQL_NULL_HANDLE, &log_env );
 if ( rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO )
    {
     current_time = time(NULL);
     fprintf(stderr,"[%s] Time  : %s",module,ctime(&current_time));
     fprintf(stderr,"[%s] ERROR : Cannot allocate Environment handle.\n",module);
     sys.logger_status = 0 ;
    }
 
 /*----------------------------------------------------------------------*/
 /* 2. Register version of environment handle                            */
 /*----------------------------------------------------------------------*/
 rc = SQLSetEnvAttr ( log_env, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0 ); 
 if ( rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO )
    {
     current_time = time(NULL);
     fprintf(stderr,"[5s] Time  : %s",module,ctime(&current_time));
     fprintf(stderr,"[%s] ERROR : Cannot register ODBC version.\n",module);
     sys.logger_status = 0 ;
    }

 /*----------------------------------------------------------------------*/
 /* 3. allocate connection handle, set timeout, auto commit ON           */      
 /*----------------------------------------------------------------------*/
 rc = SQLAllocHandle ( SQL_HANDLE_DBC, log_env, &log_hdbc ); 
 if ( rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO )
    {
     current_time = time(NULL);
     fprintf(stderr,"[%s] Time  : %s",module,ctime(&current_time));
     fprintf(stderr,"[%s] ERROR : Cannot allocate connection handle.\n",module);
     SQLFreeHandle(SQL_HANDLE_ENV, log_env);
     sys.logger_status = 0 ;
    }
    
 // set LOGIN TIMEOUT 5 seconds
 rc = SQLSetConnectAttr( log_hdbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER *)5, 0);
 if ( rc != 0 )
    {
     current_time = time(NULL);
     fprintf(stderr,"[%s] Time  : %s",module,ctime(&current_time));
     fprintf(stderr,"[%s] ERROR : Cannot set connection timeout.\n",module);
    } 
 
 // set AUTOCOMMIT ON              
 rc = SQLSetConnectAttr(log_hdbc, SQL_ATTR_AUTOCOMMIT, (SQLPOINTER)SQL_AUTOCOMMIT_ON, SQL_NTS);
 if ( rc != 0 )
    {
     current_time = time(NULL);
     fprintf(stderr,"[%s] Time  : %s",module,ctime(&current_time));
     fprintf(stderr,"[%s] ERROR : Cannot set connection autocommit ON.\n",module);
    } 
 
 /*----------------------------------------------------------------------*/
 /* 4. Connect to the database (datasource DSN)                          */
 /*----------------------------------------------------------------------*/
 rc = SQLConnect( log_hdbc, (SQLCHAR*) sys.dsn_name , SQL_NTS,
                            (SQLCHAR*) sys.dsn_user , SQL_NTS,
                            (SQLCHAR*) sys.dsn_pwd  , SQL_NTS ); 
 
 if ( rc != SQL_SUCCESS &&  rc != SQL_SUCCESS_WITH_INFO )
    {
     SQLGetDiagRec(SQL_HANDLE_DBC,log_hdbc,1,log_SQLSTATE,&log_SQLCODE,log_SQLERR,400,&log_SQLERRLEN);
     fprintf(stderr,"[%s] Time  : %s",module,ctime(&current_time));
     fprintf(stderr,"[%s] ERROR : Cannot Connect to DSN [%s]\n",module,sys.dsn_name);
     fprintf(stderr,"                SQLCODE  [%d]\n",log_SQLCODE);
     fprintf(stderr,"                SQLSTATE [%s]\n",log_SQLSTATE);
     fprintf(stderr,"                Message  [%s]\n",log_SQLERR);
     SQLFreeHandle(SQL_HANDLE_DBC, log_hdbc);
     SQLFreeHandle(SQL_HANDLE_ENV, log_env );
     sys.logger_status = 0 ;
    }

 /*----------------------------------------------------------------------*/
 /* 5. allocate a statement handle                                       */
 /*----------------------------------------------------------------------*/
 rc = SQLAllocHandle (SQL_HANDLE_STMT,  log_hdbc, &log_hstmt);
 if ( rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO )
    {
     SQLGetDiagRec(SQL_HANDLE_DBC,log_hdbc,1,log_SQLSTATE,&log_SQLCODE,log_SQLERR,400,&log_SQLERRLEN);
     current_time = time(NULL);
     fprintf(stderr,"[%s] Time  : %s",module,ctime(&current_time));
     fprintf(stderr,"[%s] ERROR : Cannot allocate statement handle.\n",module);
     fprintf(stderr,"                SQLCODE  [%d]\n",log_SQLCODE);
     fprintf(stderr,"                SQLSTATE [%s]\n",log_SQLSTATE);
     fprintf(stderr,"                Message  [%s]\n",log_SQLERR);
     SQLFreeHandle(SQL_HANDLE_DBC, log_hdbc);
     SQLFreeHandle(SQL_HANDLE_ENV, log_env );
     sys.logger_status = 0 ;
    }
 
 /*----------------------------------------------------------------------*/
 /*                               Main loop                              */
 /*----------------------------------------------------------------------*/
 do{
    for ( i=1; i<=1000; i++ )
        { 
         if ( log_queue[i].status == 1 ) 
            {
             if ( sys.logger_status == 1 )
	        {
		 // insert system message into log table
		 check_single_quote (&log_queue[i].message );
                 sprintf (INSERT_SQL, "insert into ODBC_SYSTEM_LOG VALUES (DEFAULT, %d,'%s','%s','%s','%s')",log_queue[i].service_id,log_queue[i].timein,log_queue[i].type,log_queue[i].module,log_queue[i].message);
                 rc=SQLExecDirect( log_hstmt,(SQLCHAR *)INSERT_SQL,SQL_NTS);
                 if ( rc != SQL_SUCCESS && rc != SQL_SUCCESS_WITH_INFO )
                    {
                     if ( SQLError(log_env,log_hdbc,log_hstmt,log_SQLSTATE,&log_SQLCODE,log_SQLERR,400,&log_SQLERRLEN) == SQL_SUCCESS )
                        {
                         fprintf(stderr,"[%s] Time  : %s",module,ctime(&current_time));
                         fprintf(stderr,"[%s] ERROR : SQLERROR while inserting logs into odbc_system_log table\n",module);     
                         fprintf(stderr,"             SQLCODE   [%d]\n", log_SQLCODE   );
                         fprintf(stderr,"             SQLSTATE  [%s]\n", log_SQLSTATE  );
                         fprintf(stderr,"             Message   [%s]\n", log_SQLERR    );
                         fprintf(stderr,"[%s][%s] %s : Service: %d Message: %s\n",log_queue[i].module,log_queue[i].timein,log_queue[i].type,log_queue[i].service_id,log_queue[i].message,log_queue[i].message);
		        }
                    }

                 // sprintf (INSERT_SQL, "commit work");
                 // rc=SQLExecDirect( log_hstmt,(SQLCHAR *)INSERT_SQL,SQL_NTS);
                 log_queue[i].status = 0 ;
	        }
             else
	        { 
		 // print system message to standard error 
                 fprintf(stderr,"[%s][%s] %s : Service: %d Message: %s\n",log_queue[i].module,log_queue[i].timein,log_queue[i].type,log_queue[i].service_id,log_queue[i].message,log_queue[i].message);
                 log_queue[i].status = 0 ;
                 // sys.logger_status = 0 ;
                }
		
            }	//  end if ( log_queue[i].status == 1 )
	   	
	}  // end for

/*	
    if ( sys.logger_status == 0 )
       { 
        SQLFreeHandle(SQL_HANDLE_STMT,log_hstmt);
        SQLDisconnect(log_hdbc);
        SQLFreeHandle(SQL_HANDLE_DBC,log_hdbc);
        SQLFreeHandle(SQL_HANDLE_ENV,log_env );
	
	goto RE_CONNECT ;
       }
*/	    
    /*--------------------------------------*/
    /* Sleep 1 second then loop             */
    /*--------------------------------------*/
    sleep (1) ;
    
    /*--------------------------------------*/
    /* Check if system logger to be stopped */
    /*--------------------------------------*/
    if ( sys.end_logger_thread == 1 ) 
       { 
        sys.logger_status = 0 ;
        return ;
       }

           
   } while(1) ;

}

