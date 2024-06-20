#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

//declaración condición consumidor
pthread_cond_t vacio = PTHREAD_COND_INITIALIZER;

// declaración de mutex
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

int buffer = 0;
// Función hilo
void* consumir(void *){
	// acquire a lock
	pthread_mutex_lock(&lock);
	printf("Consumidor-Intento de consumo\n");
	if (buffer <= 0) {
		// espera a la variable no_vacío
		pthread_cond_wait(&vacio, &lock);
		buffer --;
		printf("Consumidor-He consumido\n");
	}
	pthread_mutex_unlock(&lock);
	pthread_exit(0);
}
void * producir(void *){
	pthread_mutex_lock(&lock);
	printf("Productor-He producido\n");
	buffer ++;
	// Manda una señal de a la var no_vacío
	printf("Productor - Enviando la señal para iniciar consumo\n");
	pthread_cond_signal(&vacio);
	pthread_mutex_unlock(&lock);
	pthread_exit(0);
}
int main(){
	pthread_t productor, consumidor;
	pthread_create(&consumidor,NULL,consumir,NULL);
	pthread_create(&productor, NULL, producir, NULL);
	pthread_join(productor, NULL);
	pthread_join(consumidor,NULL);
	return 0;
}

