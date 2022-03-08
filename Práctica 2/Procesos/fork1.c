#include <stdio.h>
#include <unistd.h>
int main(void){
	int pid;
	printf("hola pid=%d",getpid());
	fflush(NULL);
	pid=fork();
	if (pid==0){
		printf("Hijo\n");
	}
	else{
		printf("Padre\n");
	}
	printf("adios pid=%d\n",getpid());
}
