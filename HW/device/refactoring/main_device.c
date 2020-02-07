#include "rpi_gpio.h"
#include "SQL_query.h"

#include <time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	// device path
	char *device= "/dev/ttyACM3";

	// file descriptor
	int fd=0;
	unsigned long baud = 9600;

	//sql settings
	static char *host = "localhost";
	static char *user = "dev1";
	static char *pass = "1234";
	static char *dbname = "feed";
	char currenttime[1024];

	// for child process
	pid_t pid;
		
	MYSQL *conn = connectsql(host,user,pass,dbname);
	fd = connectpi(fd, baud, device);
	setdefault();	
	char* data = serial_signal(fd);
	int remainfood = atoi(data);
	
	time_t restime=time(NULL);
	sprintf(currenttime, "%d:%d:00", localtime(&restime)->tm_hour, localtime(&restime)->tm_min);
	MYSQL_RES *result = get_timetable(conn);
	MYSQL_ROW row = get_field(result,conn,currenttime);
	int loopcnt=0;
	if (argc > 1) loopcnt=atoi(argv[1])/50;
	if(strcmp(row[0],currenttime)==0) atoi(row[1])/50;
	
	// food distribute
		if(loopcnt){
		for (int i = 0; i < loopcnt; ++i)
			goFront(128); //512 for 1loop
		end();
		printf("feed %d Times!\n", loopcnt);
		// empty sensing
		pid = fork();
		int checkcnt = 1e5;
		if (pid == 0) {
			//IR SENSING
			int threshold=0;
			int needtofill = 0;
			while (checkcnt--) {
				if (EMPTYCHECK()==1) {
					++threshold;
					if (threshold > 5) {
						needtofill = 1;
						insert_query(conn,needtofill,loopcnt*50,remainfood);
						exit(1);
					}
				}
			}
			insert_query(conn,needtofill,loopcnt*50,remainfood);
			exit(1);
		}
		else {
		//IR TRANSMITTING
			IR_TRANSMITTING(checkcnt);
			exit(1);
		}
	}
	printf("deactivate\n");
	return 0;
}
