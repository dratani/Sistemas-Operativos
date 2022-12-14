#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int main ()
{
	while (1) {
    sleep(2);
		kill(26726,SIGFPE);
		kill(26726,SIGALRM);
		printf("Envié dos señales \n");
  }
}
