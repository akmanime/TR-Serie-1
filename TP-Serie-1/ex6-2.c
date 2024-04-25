#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 10   // Taille du tableau
#define NUM_THREADS 4   // Nombre de threads


int totalSum = 0;  // Variable globale pour stocker la somme totale


typedef struct {
    int *start;            // Pointeur vers le début de la section du tableau à traiter
    int *end;              // Pointeur vers la fin de la section du tableau à traiter
    pthread_mutex_t *lock; // Pointeur vers le verrou pour la synchronisation
} PartialSumArgs;


void *sum_partial(void *args) {
    PartialSumArgs *partialArgs = (PartialSumArgs *)args;

    int partialSum = 0;

    // Boucle pour calculer la somme partielle de la section du tableau
    int *p;
    for (p = partialArgs->start; p < partialArgs->end; p++) {
        partialSum += *p;
    }

    // Verrouillage pour mettre à jour la somme totale en toute sécurité
    pthread_mutex_lock(partialArgs->lock);

    // Mise à jour de la somme totale
    totalSum += partialSum;

    // Déverrouillage après la mise à jour de la somme totale
    pthread_mutex_unlock(partialArgs->lock);

    pthread_exit(NULL); // Fin du thread
}

int main() {
    int array[ARRAY_SIZE];
    int i;

    // Initialisation du tableau avec des valeurs de 1 à ARRAY_SIZE
    for (i = 0; i < ARRAY_SIZE; ++i) {
        array[i] = i + 1;
    }

    pthread_mutex_t lock;
    pthread_mutex_init(&lock, NULL); // Initialisation du verrou

    pthread_t threads[NUM_THREADS]; // Tableau d'identifiants de threads
    PartialSumArgs threadArgs[NUM_THREADS]; // Tableau d'arguments pour les threads

    int sectionSize = ARRAY_SIZE / NUM_THREADS; // Taille de chaque section du tableau pour chaque thread
    for (i = 0; i < NUM_THREADS; ++i) {
        // Configuration des arguments pour chaque thread
        threadArgs[i].start = (array + i * sectionSize);
        threadArgs[i].end = (array + ((i == NUM_THREADS - 1) ? ARRAY_SIZE : (i + 1) * sectionSize));
        threadArgs[i].lock = &lock;

        // Création des threads
        if (pthread_create(&threads[i], NULL, sum_partial, (void *)&threadArgs[i]) != 0) {
            fprintf(stderr, "Erreur lors de la création du thread %d\n", i); // Affichage d'une erreur en cas d'échec
            return 1; // Terminaison du programme avec un code d'erreur
        }
    }

    // Attente de la fin de chaque thread
    for (i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    // Affichage de la somme totale
    printf("Somme totale : %d\n", totalSum);

    pthread_mutex_destroy(&lock); // Destruction du verrou

    return 0; // Terminaison du programme avec succès
}
