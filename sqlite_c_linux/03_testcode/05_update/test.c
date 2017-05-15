//http://www.runoob.com/sqlite/sqlite-c-cpp.html
//UPDATE 操作
//下面的 C 代码段显示了如何使用 UPDATE 语句来更新任何记录，然后从 COMPANY 表中获取并显示更新的记录：

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 
#include "log.h"

static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
   fprintf(stderr, "%s: ", (const char*)data);
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int main(int argc, char* argv[])
{
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *sql;
   const char* data = "Callback function called";

   /* Open database */
   rc = sqlite3_open("test.db", &db);
   if( rc ){
      LOG_STR("Can't open database: %s\n", sqlite3_errmsg(db));
      exit(0);
   }else{
      LOG_STR("Opened database successfully\n");
   }

   /* Create merged SQL statement */
   sql = "UPDATE COMPANY set SALARY = 25000.00 where ID=1; " \
         "SELECT * from COMPANY";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
   if( rc != SQLITE_OK ){
      LOG_STR("SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      LOG_STR("Operation done successfully\n");
   }
   sqlite3_close(db);
   return 0;
}

