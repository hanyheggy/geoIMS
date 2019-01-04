/*-------------------------------------------------------------------------------------------*/
/*                            Indego Arabic test module                                      */
/*-------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------*/
/*                                   Include Files                                           */
/*-------------------------------------------------------------------------------------------*/
#include "include/unixODBC.h"

/*-------------------------------------------------------------------------------------------*/
/*                                       Global Variables                                    */
/*-------------------------------------------------------------------------------------------*/
SQLHENV      log_env             ; // Environment handle
SQLHDBC      log_hdbc            ; // Connection  handle
SQLHSTMT     log_hstmt           ; // Statement   handle
SQLINTEGER   log_SQLCODE         ; // SQL Code
char         log_SQLSTATE  [10]  ; // SQL Status
char         log_SQLERR    [400] ; // SQL Error Message
SQLSMALLINT  log_SQLERRLEN       ; // SQL Message length

char         SQL           [500] ;
int          rc  = 0             ;

/*-------------------------------------------------------------------------------------------*/
/*                                     main()                                                */
/*-------------------------------------------------------------------------------------------*/
read_db(int id, char *UTF_TEXT)
{
 char utf8   [1000] ;
 char dsn_name [20] ;
 char dsn_user [20] ;
 char dsn_pwd  [20] ;

 /*----------------------------------------------------------------------*/
 /* 1. allocate environment handle and register version                  */
 /*----------------------------------------------------------------------*/
 rc = SQLAllocHandle ( SQL_HANDLE_ENV, SQL_NULL_HANDLE, &log_env );

 /*----------------------------------------------------------------------*/
 /* 2. Register version of environment handle                            */
 /*----------------------------------------------------------------------*/
 rc = SQLSetEnvAttr ( log_env, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0 );

 /*----------------------------------------------------------------------*/
 /* 3. allocate connection handle, set timeout, auto commit ON           */
 /*----------------------------------------------------------------------*/
 rc = SQLAllocHandle ( SQL_HANDLE_DBC, log_env, &log_hdbc );

 // set LOGIN TIMEOUT 5 seconds
 rc = SQLSetConnectAttr( log_hdbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER *)5, 0);

 // set AUTOCOMMIT ON
 rc = SQLSetConnectAttr(log_hdbc, SQL_ATTR_AUTOCOMMIT, (SQLPOINTER)SQL_AUTOCOMMIT_ON, SQL_NTS);

 /*----------------------------------------------------------------------*/
 /* 4. Connect to the database (datasource DSN)                          */
 /*----------------------------------------------------------------------*/
 //strcpy(dsn_name,"geoinfo"  );
 //strcpy(dsn_user,"geoinfo"  );
 //strcpy(dsn_pwd ,"fsh170405");
 
 strcpy(dsn_name,"odbcrep"  );
 strcpy(dsn_user,"test"  );
 strcpy(dsn_pwd ,"test33h");

 rc = SQLConnect( log_hdbc, (SQLCHAR*) dsn_name , SQL_NTS,
                            (SQLCHAR*) dsn_user , SQL_NTS,
                            (SQLCHAR*) dsn_pwd  , SQL_NTS );

 if (rc != 0)
    {
     printf("Connect Return Code = %d\n",rc);
     exit (-1) ;
    }

 /*----------------------------------------------------------------------*/
 /* 5. allocate a statement handle                                       */
 /*----------------------------------------------------------------------*/
 rc = SQLAllocHandle (SQL_HANDLE_STMT,  log_hdbc, &log_hstmt);

 /*----------------------------------------------------------------------*/
 /* 6. Bind Columns  (use i-1 to get the correct string array index)    */
 /*----------------------------------------------------------------------*/
 rc = SQLBindCol( log_hstmt, 1, SQL_C_CHAR, &utf8, 500, &log_SQLCODE);

 /*----------------------------------------------------------------------*/
 /* 7. Execute the statement directly                                   */
 /*----------------------------------------------------------------------*/
 sprintf(SQL,"SELECT utf8_L2R from arabic where id = %d ",id);
 rc=SQLExecDirect( log_hstmt,(SQLCHAR *)SQL,SQL_NTS);

 /*----------------------------------------------------------------------*/
 /* 8. Fetch LOOP                                                       */
 /*----------------------------------------------------------------------*/
 rc=SQLFetch(log_hstmt);

 SQLFreeHandle (SQL_HANDLE_STMT,log_hstmt);

 /*------------------------------------------------------------------------------------------------*/
 /*  9. Disconnect From DB                                                                         */
 /*------------------------------------------------------------------------------------------------*/
 SQLDisconnect(log_hdbc);
 SQLFreeHandle(SQL_HANDLE_DBC, log_hdbc);
 SQLFreeHandle(SQL_HANDLE_ENV, log_env);

 printf("===>>TEXT from DB [%s]\n",utf8);
 strcpy (UTF_TEXT,utf8);
 printf("===>>TEXT from DB [%s]\n",UTF_TEXT);

 return ;

}
