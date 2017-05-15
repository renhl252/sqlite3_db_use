//http://www.runoob.com/sqlite/sqlite-c-cpp.html
//连接数据库
//下面的 C 代码段显示了如何连接到一个现有的数据库。如果数据库不存在，那么它就会被创建，最后将返回一个数据库对象。

#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>
#include "log.h"

int main(int argc, char* argv[])
{
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;

   rc = sqlite3_open("test.db", &db);

   if( rc ){
      LOG_STR("Can't open database: %s\n", sqlite3_errmsg(db));
      exit(0);
   }else{
      LOG_STR("Opened database successfully\n");
   }
   sqlite3_close(db);
}