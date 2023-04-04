#include <stdio.h>
#include <unistd.h>
int main (int argc, char *argv[]){
printf("Programa secundario\n");
for (int i=0;i<argc;i++){
  printf("Argumento %d:%s\n",i,argv[i]);
}
_exit(0);
}
