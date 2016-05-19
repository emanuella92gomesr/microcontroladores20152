#include <stdio.h>
#include <errno.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int fd;
int cont=0;
char charRecebido;
int flagOn = 0;

PI_THREAD (recebe_serial) {  // ler os caracteres enviados pelo microcontrolador
(void)piHiPri (10) ;
	charRecebido = serialGetchar(fd);
	if(charRecebido == 'G') {
		printf("Vazamento detectado \n");
		fflush(stdout);
		flagOn = 1;
		printf("%d\n", flagOn);
		system("./msg.sh");
	}
}

int main (void){   // comunica褯 serial
	wiringPiSetupGpio () ;	
	if ((fd = serialOpen ("/dev/ttyAMA0", 9600)) < 0){
		fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
		return 1;
	} 
	
	while(1) {
		piThreadCreate (recebe_serial) ;
	}
		
} 
