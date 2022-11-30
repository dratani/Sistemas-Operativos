#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
void accion_alarma (int s)
{
	printf("Pasaron 2 segundos, señal: %d\n",s);
}
void acction_flotante (int s)
{
	printf("Se recibió un flotante %d \n",s );
}
int main ()
{
	struct sigaction tratamiento_alarma;
	struct sigaction tratamiento_flotante;
	tratamiento_alarma.sa_handler = accion_alarma;
	tratamiento_flotante.sa_handler = acction_flotante;
	sigaction (SIGALRM, &tratamiento_alarma,NULL);
	sigaction(SIGFPE, &tratamiento_flotante,NULL);
	while (1) {
    alarm(2);
    pause();
		kill(0,SIGFPE);
  }
}
