#include <mysql/mysql.h>

MYSQL* connectsql(char* host, char* user, char* pass, char* dbname);

void error(MYSQL *conn);

MYSQL_RES* get_timetable(MYSQL *conn);
MYSQL_ROW get_field(MYSQL_RES *result, MYSQL *conn, char* tbuf);
void insert_query(MYSQL *conn, int emptyflag, int amount, int remain);