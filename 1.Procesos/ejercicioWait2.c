#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
  int pid;
  int status;
  int cero=0;
  pid = fork();
  if(pid==0)
    {
      printf("[H1] Dormiré 5 seg\n");
      sleep(5);
      printf("[H1] Desperté\n");
      pid = pid/cero;
      exit(1);
    }
  pid = fork();
  if(pid== 0)
  {
    printf("[H2] Dormiré 1 seg\n");
    sleep(1);
    printf("[H2] Desperté\n");
    exit(2);
  }
    printf("[P]Esperando a los hijos\n");
    pid = wait(&status);
    printf("[P]El hijo %d ha despertado\n",pid);
    if (WIFEXITED(status)!=0)//true si el hijo terminó correctamente
      printf("exit del hijo=%d\n",WEXITSTATUS(status));
    pid = wait(&status);
    printf("[P]El hijo %d ha despertado\n",pid);
    if (WIFEXITED(status)!=0)//true si el hijo terminó correctamente
      printf("exit del hijo=%d\n",WEXITSTATUS(status));
    if (WIFSIGNALED(status))//true si el hijo terminó de manera abrupta
      printf("Señal num=%d\n",WTERMSIG(status));
}
