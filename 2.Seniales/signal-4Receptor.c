#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
void captura (int s)
{
	if (s==SIGALRM) {
		printf("Pasaron 2 segundos, señal: %d\n",s);
	}
	if (s==SIGFPE) {
		printf("Error punto flotante, señal: %d\n",s);
	}
	if (s==SIGINT){
		printf("Recibí interrupción por teclado, señal: %d\n",s);
	}
}

int main ()
{
	struct sigaction capturadorSenial;
	capturadorSenial.sa_handler = captura;
	sigaction (SIGALRM, &capturadorSenial,NULL);
	sigaction(SIGFPE, &capturadorSenial,NULL);
	sigaction(SIGINT, &capturadorSenial, NULL);
	while (1) {
		printf("Esperando...\n" );
		pause();

  }
}
