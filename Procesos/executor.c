#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
int main(void) {
	int pid, estado;
	char programa[20];
	printf (">");
	scanf("%s", programa);
	while (programa[0] != '0') {
		if (fork() == 0) {
			estado = execl(programa,0);
			printf ("Srror en %s => %d\n", programa, estado);
			_exit (1);
		} else {
			pid = wait(&estado);
			printf (">");
			scanf("%s", programa);
		}
	}
}
