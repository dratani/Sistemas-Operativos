#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#define BLOQUE 4096

int main(int argc, char **argv) {
  char buffer[BLOQUE];
  int dfOrg, dfDst, leidos, escritos;
  dfOrg = open (argv[1], O_RDONLY);
  dfDst = open (argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0600);
  do {
    leidos = read (dfOrg, buffer, BLOQUE);
    escritos= write (dfDst, buffer, leidos);
    printf("*******************************************\n" );
    printf("Bytes leídos: %d\n",leidos);
    printf("Bytes escritos: %d\n",escritos);
    printf("Búffer: %s \n",buffer);
    sleep(.1);
  } while (leidos == BLOQUE);
  close(dfOrg);
  close(dfDst);
}
