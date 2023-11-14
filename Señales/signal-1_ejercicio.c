#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
struct sigaction capturadorSenial;
int i;
void captura (int sig) {
  if (sig==2)
    printf ("Capturada la senial SIGINT con el número %d\n",sig);
else{

}
//  exit(-1);
}
int main(void) {
  capturadorSenial.sa_handler = captura;
  sigaction (SIGINT, &capturadorSenial, NULL);
  sigaction (SIGFPE, &capturadorSenial, NULL);

  while (1){
      printf ("En espera de Ctrl-C \n");
      sleep(10);
  }
}
