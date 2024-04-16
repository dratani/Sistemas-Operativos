#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main(void) {
	int pid, estado;
	char *programa,*path;
	path ="/home/tani/Sistemas-Operativos/1.Procesos/args";
	printf("Programa principal\n");
	estado = execl(path,"a", NULL);
	if (estado==-1)
	{
		perror ("Error 1 en execl");
	_exit(2);
  }
  printf("HOLA");
_exit(0);
}
