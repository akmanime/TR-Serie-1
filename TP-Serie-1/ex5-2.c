#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_TASKS 3

// Structure pour représenter une tâche périodique
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

int main() {
    int TASK_PERIODS[] = {1, 2, 3}; // Périodes des tâches en secondes
    pthread_t threads[NUM_TASKS];   // Tableau pour stocker les identifiants des threads
    PeriodicTask tasks[NUM_TASKS];  // Tableau pour stocker les informations sur les tâches
    int i;

    // Création des threads pour chaque tâche
    for (i = 0; i < NUM_TASKS; ++i) {
        tasks[i].id = i + 1;            // Attribution des identifiants aux tâches
        tasks[i].period = TASK_PERIODS[i]; // Attribution des périodes aux tâches
        pthread_create(&threads[i], NULL, taskFunction, (void *)&tasks[i]); // Création des threads
    }

    sleep(10); // Pause de 10 secondes pour permettre l'exécution des tâches

    // Annulation et attente de la terminaison de chaque thread
    for (i = 0; i < NUM_TASKS; ++i) {
        pthread_cancel(threads[i]); // Annulation du thread
        pthread_join(threads[i], NULL); // Attente de la terminaison du thread
    }

    return 0; // Fin du programme
}
