/*------------------------------------------------------*/
/* sigint1.c: Obervar tratamiento por defecto SIGINT    */
/*------------------------------------------------------*/

#include <stdio.h>

int main(void) {
  int i,j;

  for (i=0; i<80000; i++)
    for (j=0; j<20000; j++);
  printf ("Fin de sigint1\n");
}