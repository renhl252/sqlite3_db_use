//http://www.runoob.com/sqlite/sqlite-c-cpp.html
//创建表
//下面的 C 代码段将用于在先前创建的数据库中创建一个表：

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
   int  rc;
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
   sql = "CREATE TABLE COMPANY("  \
         "ID INT PRIMARY KEY     NOT NULL," \
         "NAME           TEXT    NOT NULL," \
         "AGE            INT     NOT NULL," \
         "ADDRESS        CHAR(50)," \
         "SALARY         REAL );";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
		LOG_STR("SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      LOG_STR("Table created successfully\n");
   }
   sqlite3_close(db);
   return 0;
}
