#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Fonction exécutée par le thread
void *func(void *arg) {
	// Récupérer le message passé en argument
	char *msg = (char *) arg;
	// Afficher le message
	printf("Message = %s\n", msg);
	// Retourner NULL pour terminer la fonction
	return NULL;
}

int main(int argc, char *argv[]) {
	// Identifiant du thread
	pthread_t t;
	// Message à passer au thread
	char *msg = "Les threads sont géniaux !";
	// Créer un nouveau thread
	if (pthread_create(&t, NULL, func, msg) != 0) {
		perror("Erreur lors de la création du thread");
		return EXIT_FAILURE;
	}
	// Attendre que le thread se termine
	if(pthread_join(t, NULL) != 0){
        perror("Erreur");
        return EXIT_FAILURE;
    }
	// Retourner SUCCESS en cas de succès
	return EXIT_SUCCESS;
}
