#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <mysql/mysql.h>
#include <stdint.h> //uint8_t definitions
#include <time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
 
int main(){
    int fd;
    if((fd=serialOpen("/dev/ttyACM2",115200))<0){
        fprintf(stderr,"Unable to open serial device: %s\n", strerror(errno));
        return 1;
    }
    for(;;){
        serialPutchar(fd, 49);
	    delay(50);
        //printf("SERIAL PUT\n");
        putchar(serialGetchar(fd));
        //printf("SERIAR RCV\n");
        fflush(stdout);
    }
}
