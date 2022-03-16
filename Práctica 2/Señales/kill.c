#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
int main(void){
	int pid;
	if (pid = fork() ==0){
		/* código de proceso hijo*/
		while (1) {
			/* code */
			printf("Hijo. PID=%d \n",getpid());
			sleep(1);
		}
	}
	sleep(10);
	printf("Padre. Terminación del proceso %d  \n", pid);
	kill (pid,SIGTERM);
	exit(0);
}
