#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main(void) {
	int pid, estado;
	pid = fork();
	if (pid==0) {
		sleep(5);
		printf("[H] MiPadre = %5d Yo = %5d\n", getppid(), getpid());
		_exit(255);
	} else {
		printf("[P] MiPadre = %5d Yo = %5d MiHijo = %5d\n",
		getppid(), getpid(), pid);
		pid = wait (&estado);
//   pid = waitpid(-1,&estado,0);
			if (WIFEXITED(estado)){
			printf("[P]: Termino el hijo %d con estado %d\n",
		 	pid, WEXITSTATUS(estado));
		}
	}
}
