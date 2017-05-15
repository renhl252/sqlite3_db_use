//http://www.runoob.com/sqlite/sqlite-c-cpp.html
//DELETE 操作
//下面的 C 代码段显示了如何使用 DELETE 语句删除任何记录，然后从 COMPANY 表中获取并显示剩余的记录：

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 
#include "log.h"
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h> 

static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
   fprintf(stderr, "%s: ", (const char*)data);
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
   sql = "DELETE from COMPANY where ID=2; " \
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