#include <stdio.h>
#include <unistd.h>
int main(void){
	int pid;
	printf("hola pid=%d \n",getpid());
	pid=fork();
	if (pid==0){
		printf("[Hijo] ID=%d \n",getpid());
	}
	else{
		printf("[Padre] ID=%d \n",getpid());
	}
	printf("adios pid=%d\n",getpid());
	return(0);
}
