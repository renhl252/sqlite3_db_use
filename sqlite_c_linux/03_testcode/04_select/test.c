//http://www.runoob.com/sqlite/sqlite-c-cpp.html
//SELECT 操作
//在我们开始讲解获取记录的实例之前，让我们先了解下回调函数的一些细节，这将在我们的实例使用到。这个回调提供了一个从 SELECT 语句获得结果的方式。它声明如下：
//typedef int (*sqlite3_callback)(
//void*,    /* Data provided in the 4th argument of sqlite3_exec() */
//int,      /* The number of columns in row */
//char**,   /* An array of strings representing fields in the row */
//char**    /* An array of strings representing column names */
//);
//如果上面的回调在 sqlite_exec() 程序中作为第三个参数，那么 SQLite 将为 SQL 参数内执行的每个 SELECT 语句中处理的每个记录调用这个回调函数。
//下面的 C 代码段显示了如何从前面创建的 COMPANY 表中获取并显示记录：

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "log.h"

static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
   LOG_STR("%s: ", (const char*)data);
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

   /* Create SQL statement */
   sql = "SELECT * from COMPANY";

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

