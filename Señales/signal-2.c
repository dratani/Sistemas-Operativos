#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
void accion_alarma (int s)
{
	printf("Pasaron 2 segundos, señal: %d\n",s);
}
int main ()
{
	struct sigaction tratamiento_alarma;
	tratamiento_alarma.sa_handler = accion_alarma;
	sigaction (SIGALRM, &tratamiento_alarma,NULL);
	while (1) {
    alarm(2);
    pause();
  }
}
