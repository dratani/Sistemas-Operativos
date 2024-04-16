#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
int main(void){
	int pid = fork();
	if (pid==0){
		/* código de proceso hijo*/
		while (1) {
			/* code */
			printf("Hijo. PID=%d \n",getpid());
			sleep(2);
		}
	}
	else{
		sleep(10);
		printf("Padre %d. Terminación del proceso %d  \n", getpid(), pid);
		kill (pid,SIGTERM);
		exit(0);
	}
}
