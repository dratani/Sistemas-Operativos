#include <stdio.h>
#include <signal.h>
struct sigaction trataSenial;
void capturaSigInt (int i) {
printf ("Capturada la senial SIGINT\n");
}
int main(void) {
int i,j;
trataSenial.sa_handler = capturaSigInt;
sigaction (SIGINT, &trataSenial, NULL);
for (i=0; i<80000; i++)
for (j=0; j<20000; j++);
printf ("Fin de sigint2\n");
}