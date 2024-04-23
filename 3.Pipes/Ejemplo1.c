#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int fd[2]; // Array para almacenar los descriptores de archivo de la tubería
    char message[] = "Hola hijo!";
    char buffer[20]; // Buffer para almacenar el mensaje recibido

    // Crear la tubería
    if (pipe(fd) == -1) {
        perror("Error al crear la tubería");
        exit(EXIT_FAILURE);
    }

    // Crear un nuevo proceso
    pid_t pid = fork();

    if (pid < 0) {
        perror("Error al crear un nuevo proceso");
        exit(EXIT_FAILURE);
    } else if (pid > 0) { // Proceso padre
        close(fd[0]); // Cierra el extremo de lectura del padre
        // Escribir en la tubería desde el padre
        write(fd[1], message, sizeof(message));
        close(fd[1]); // Cierra el extremo de escritura después de escribir
    } else { // Proceso hijo
        close(fd[1]); // Cierra el extremo de escritura del hijo
        // Leer desde la tubería en el hijo
        read(fd[0], buffer, sizeof(buffer));
        printf("Mensaje recibido en el hijo: %s\n", buffer);
        close(fd[0]); // Cierra el extremo de lectura después de leer
    }

    return 0;
}

