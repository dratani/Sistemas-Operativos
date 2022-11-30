#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main(void) {
	int pid, estado;
	char *programa,*path;
	path ="/home/tani/Sistemas-Operativos/Práctica 2/Procesos/execl.c";
	estado = execl(path,path, NULL);
	if (estado==-1)
	{
		perror ("Error 1 en execl");
	_exit(2);
  }
_exit(0);
}
