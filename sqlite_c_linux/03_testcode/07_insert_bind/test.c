//http://www.runoob.com/sqlite/sqlite-c-cpp.html
//DELETE 操作
//下面的 C 代码段显示了如何使用 DELETE 语句删除任何记录，然后从 COMPANY 表中获取并显示剩余的记录：

#include <stdio.h>
//http://www.runoob.com/sqlite/sqlite-c-cpp.html
//DELETE 操作
//下面的 C 代码段显示了如何使用 DELETE 语句删除任何记录，然后从 COMPANY 表中获取并显示剩余的记录：

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "log.h"

static sqlite3 *db;

int callback(void *NotUsed, int argc, char **argv, char **azColName){
	int i;
	for(i=0; i<argc; i++){
		LOG_STR("%s = %s\n",azColName[i], argv[i]?argv[i]:"NULL");
	}
	LOG_STR("\n");
	return 0;
}

sqlite3 *db_connect(char *db_name)
{
	int rc;
	rc = sqlite3_open(db_name, &db);
	return db;
}

int db_exec_stmt(char *sql)
{
	int rc;
	char *zErrMsg = 0;
	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	if( rc!=SQLITE_OK ){
		LOG_STR("SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
		exit(1);
	}
	return 0;
}

void db_exec()
{
	char *sql = "insert into user_info (id, user_name) values(?,?)";
	sqlite3_stmt *stmt;
	const char *tail;
	int i;
	int ncols;
	int rc; 
	char *name="xiaoliang";

	rc = sqlite3_prepare(db, sql, strlen(sql), &stmt, NULL);
	if (rc != SQLITE_OK)
	{
		LOG_STR("sql error:%s\n", sqlite3_errmsg(db));
	}
	
	LOG_STR("col 1 name is %s",sqlite3_bind_parameter_name(stmt, 0));
	LOG_STR("col 2 name is %s",sqlite3_bind_parameter_name(stmt, 2));
	LOG_STR("count is %d",sqlite3_bind_parameter_count(stmt));

	sqlite3_bind_int(stmt, 1, 20);
	sqlite3_bind_text(stmt, 2, name, strlen(name), SQLITE_STATIC);
	
	sqlite3_step(stmt);
	
	sqlite3_finalize(stmt);

}

int main(int argc, char **argv)
{
	char *db_name="test.db";

	db = db_connect(db_name);
	// rc = db_exec_stmt(sql);
	db_exec();

	sqlite3_close(db);
	return 0;
}