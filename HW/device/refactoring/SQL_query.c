#include "SQL_query.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>

MYSQL* connectsql(char* host, char* user, char* pass, char* dbname){
	MYSQL *conn;
	conn = mysql_init(NULL);
	conn =mysql_real_connect(conn, host, user, pass, dbname, 0, NULL, 0);
	if (!conn)
	{
		fprintf(stderr, "ERROR: %s[%d]\n", mysql_error(conn), mysql_errno(conn));
		exit(1);
	}
	else{
		printf("Connection Successful!\n\n");
		return conn;
	}
}

void error(MYSQL *conn){
	fprintf(stderr, "%s\n", mysql_error(conn));
	mysql_close(conn);
}

MYSQL_RES* get_timetable(MYSQL *conn){
	mysql_query(conn, "select * from local_timetable");
	MYSQL_RES *result = mysql_store_result(conn);
	return result;
}

MYSQL_ROW get_field(MYSQL_RES *result, MYSQL *conn, char* tbuf){
	if (result == NULL) error(conn);
	int fields = mysql_num_fields(result);
	MYSQL_ROW row;
	for(int i=0; i<fields; ++i){
		row = mysql_fetch_row(result);
		if(strcmp(row[0],tbuf)==0) break;
	}
	return row;
}

void insert_query(MYSQL *conn, int emptyflag, int amount, int remain){
	char buf[1024];
	sprintf(buf, "insert into local_feeding_log (empty, amount, remain) values ('%d', '%d', '%d')",emptyflag, amount, remain);
	int res = mysql_query(conn, buf);
	if (!res)
		printf("Insert <%d> <%d> <%d> successful!\n", emptyflag, amount, remain);
	else
		error(conn);
}