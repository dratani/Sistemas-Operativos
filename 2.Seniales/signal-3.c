#include <stdio.h>
#include <signal.h>
#include <unistd.h>
struct sigaction trataSenial;
int segundos;

struct sigaction trataSenial;

void tic (int sig) {
  printf("Señal %d recibida - ",sig );
}

int main(void) {
  int segundos;

  trataSenial.sa_handler = tic;
  sigaction (SIGALRM, &trataSenial, NULL);
  for (segundos=1; segundos<11; segundos++) {
    alarm(1);
    pause();
    printf ("%2d segundos.\n", segundos);
  }
}
