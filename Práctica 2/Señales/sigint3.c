/* sigint3.c:      Forzar dos SIGINT para matar proceso */

#include <stdio.h>
#include <signal.h>

struct sigaction trataSenial, trataAnteriorSenial;

void capturaSigInt (int i) {
  printf ("Capturada la senial SIGINT\n");
  sigaction (SIGINT, &trataAnteriorSenial, NULL);
}

int main(void) {
  int i,j;

  trataSenial.sa_handler = capturaSigInt;
  sigaction (SIGINT, &trataSenial, &trataAnteriorSenial);
  for (i=0; i<80000; i++)
    for (j=0; j<20000; j++);
  printf ("Fin de sigint3\n");
}