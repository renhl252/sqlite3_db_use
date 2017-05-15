//http://www.runoob.com/sqlite/sqlite-c-cpp.html
//INSERT 操作
//下面的 C 代码段显示了如何在上面创建的 COMPANY 表中创建记录：

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "log.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
   int i;
   for(i=0; i<argc; i++){
      LOG_STR("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   LOG_STR("\n");
   return 0;
}

int main(int argc, char* argv[])
{
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *sql;

   /* Open database */
   rc = sqlite3_open("test.db", &db);
   if( rc ){
      LOG_STR("Can't open database: %s\n", sqlite3_errmsg(db));
      exit(0);
   }else{
      LOG_STR("Opened database successfully\n");
   }

   /* Create SQL statement */
   sql = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
         "VALUES (1, 'Paul', 32, 'California', 20000.00 ); " \
         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
         "VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "     \
         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
         "VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );" \
         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
         "VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
      LOG_STR("SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      LOG_STR("Records created successfully\n");
   }
   sqlite3_close(db);
   return 0;
}

