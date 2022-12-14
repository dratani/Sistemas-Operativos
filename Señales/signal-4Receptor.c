#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
void accion_alarma (int s)
{
	printf("Señal alarma: %d\n",s);
}
void acction_flotante (int s)
{
	printf("Se recibió un flotante %d \n",s );
}
int main ()
{
	printf("Mi pid es:%d\n",getpid());
	struct sigaction tratamiento_alarma;
	struct sigaction tratamiento_flotante;
	tratamiento_alarma.sa_handler = accion_alarma;
	tratamiento_flotante.sa_handler = acction_flotante;
	sigaction (SIGALRM, &tratamiento_alarma,NULL);
	sigaction(SIGFPE, &tratamiento_flotante,NULL);
	while (1) {
		printf("Esperando...\n" );
		pause();

  }
}
