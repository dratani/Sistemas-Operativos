#include <stdio.h>
#include <unistd.h>
int main(int argc, char *argv[]){
	int pid;
	pid=fork();
	if (pid==0){
		printf("[Hijo] ID=%d mi padre es=%d \n"
			,getpid(),getppid());
	}
	else{
		printf("[Padre] ID=%d mi padre es=%d \n"
			,getpid(),getppid());
	}
	printf("adios pid=%d\n",getpid());
	return(0);
}
