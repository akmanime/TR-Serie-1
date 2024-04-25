#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Fonction exécutée par le premier thread
void *thread_func1(void *arg) {
	printf("Thread 1: Bonjour !\n");
	return NULL;
}

// Fonction exécutée par le deuxième thread
void *thread_func2(void *arg) {
	printf("Thread 2: Salut !\n");
	return NULL;
}

int main(int argc, char *argv[]) {
	pthread_t t1;
	pthread_t t2;
	
	// Création du premier thread
	if (pthread_create(&t1, NULL, thread_func1, NULL) != 0) {
		perror("thread creation error"); // Affiche un message d'erreur en cas d'échec
		return EXIT_FAILURE; // Termine le programme avec un code d'erreur
	}
	
	// Création du deuxième thread
	if (pthread_create(&t2, NULL, thread_func2, NULL) != 0) {
		perror("thread creation error"); // Affiche un message d'erreur en cas d'échec
		return EXIT_FAILURE; // Termine le programme avec un code d'erreur
	}
	
	// Attente de la fin de l'exécution des threads
	if(pthread_join(t1, NULL) != 0){
        perror("Error"); // Affiche un message d'erreur en cas d'échec
        return EXIT_FAILURE; // Termine le programme avec un code d'erreur
    }
    
    if(pthread_join(t2, NULL) != 0){
        perror("Error"); // Affiche un message d'erreur en cas d'échec
        return EXIT_FAILURE; // Termine le programme avec un code d'erreur
    }
	
	return EXIT_SUCCESS; // Termine le programme avec succès
}
