#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
struct sigaction capturadorSenial;
int i;
void capturaSigInt (int sig) {
  printf ("Capturada la senial SIGINT con el número %d\n",sig);
  exit(-1);
}
int main(void) {
  capturadorSenial.sa_handler = capturaSigInt;
  sigaction (SIGINT, &capturadorSenial, NULL);

  while (1){
      printf ("En espera de Ctrl-C \n");
      sleep(999);
  }
}
