#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main(void) {
	int pid, estado;
	char *programa,*path;
	path ="/home/tani/Sistemas-Operativos/Procesos/argumentos";
	estado = execl(path,"a", NULL);
	if (estado==-1)
	{
		perror ("Error 1 en execl");
	_exit(2);
  }
_exit(0);
}
