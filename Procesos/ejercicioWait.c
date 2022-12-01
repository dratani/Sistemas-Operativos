#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
  int pid;
  int status;
  pid = fork();
  if(pid==0)
    {
      printf("[H1] Dormiré 5 seg\n");
      sleep(5);
      exit(5);
    }
    else
    {
      printf("[P] Esperaré al H1\n");
      pid = wait(&status);
    }
  pid = fork();
  if(pid== 0)
  {
    printf("[H2] Dormiré 1 seg\n");
    sleep(1);
    exit(1);
  }
  else
  {
    printf("[Padre] Esperaré al H2\n");
    pid = wait(&status);
  }
}
