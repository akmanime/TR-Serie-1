#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;     // Identifiant de la tâche
    int period; // Période de la tâche en secondes
} PeriodicTask;

// Fonction exécutée par chaque thread de tâche
void *taskFunction(void *arg) {
    PeriodicTask *task = (PeriodicTask *)arg;

    while (1) { // Boucle infinie pour exécuter la tâche périodiquement
        sleep(task->period); // Pause selon la période spécifiée
        printf("Task %d executed.\n", task->id); // Affichage de l'exécution de la tâche
    }

    return NULL;
}

int main(int argc, char *argv[]) {
    PeriodicTask task1, task2;
    task1.id = 1;       // Identifiant de la première tâche
    task1.period = 1;   // Période de la première tâche en secondes
    task2.id = 2;       // Identifiant de la deuxième tâche
    task2.period = 2;   // Période de la deuxième tâche en secondes

    pthread_t t1;   // Identifiant du premier thread
    pthread_t t2;   // Identifiant du deuxième thread

    // Création du premier thread pour exécuter la première tâche
    if (pthread_create(&t1, NULL, taskFunction, &task1) != 0) {
        perror("thread creation error"); // Affichage d'un message d'erreur en cas d'échec
        return EXIT_FAILURE; // Terminaison du programme avec un code d'erreur
    }

    // Création du deuxième thread pour exécuter la deuxième tâche
    if (pthread_create(&t2, NULL, taskFunction, &task2) != 0) {
        perror("thread creation error"); // Affichage d'un message d'erreur en cas d'échec
        return EXIT_FAILURE; // Terminaison du programme avec un code d'erreur
    }

    // Attente de la fin de l'exécution des threads
    if (pthread_join(t1, NULL) != 0) {
        perror("Error"); // Affichage d'un message d'erreur en cas d'échec
        return EXIT_FAILURE; // Terminaison du programme avec un code d'erreur
    }

    if (pthread_join(t2, NULL) != 0) {
        perror("Error"); // Affichage d'un message d'erreur en cas d'échec
        return EXIT_FAILURE; // Terminaison du programme avec un code d'erreur
    }

    return EXIT_SUCCESS; // Terminaison du programme avec succès
}
