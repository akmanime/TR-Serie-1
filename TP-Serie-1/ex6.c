#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int tab[12] = {5, 2, 7, 9, 3, 4, 6, 8, 1, 3, 8, 5}; // Tableau d'entiers
int somme = 0; // Variable pour stocker la somme totale

typedef struct {
    int start; // Indice de début de la section du tableau
    int end;   // Indice de fin de la section du tableau
    //pthread_mutex_t *lock; // Verrou pour la synchronisation
} PartialSumArgs;

// Fonction exécutée par chaque thread pour calculer la somme partielle de sa section
void *sum_partial(void *arg) {
    PartialSumArgs *indice = (PartialSumArgs *)arg;
    int i;
    for (i = indice->start; i <= indice->end; i++) {
        somme = somme + tab[i]; // Ajoute chaque élément de la section à la somme totale
    }
    return NULL; // Fin du thread
}

int main() {
    pthread_t t1; // Identifiant du premier thread
    pthread_t t2; // Identifiant du deuxième thread
    pthread_t t3; // Identifiant du troisième thread
    PartialSumArgs ps1, ps2, ps3; // Arguments pour les threads

    // Configuration des sections du tableau pour chaque thread
    ps1.start = 0;
    ps1.end = 4;

    ps2.start = 5;
    ps2.end = 8;

    ps3.start = 9;
    ps3.end = 11;

    // Création du premier thread pour calculer la somme de la première section
    if (pthread_create(&t1, NULL, sum_partial, &ps1) != 0) {
        perror("Erreur lors de la création du thread 1");
        return EXIT_FAILURE;
    }

    // Création du deuxième thread pour calculer la somme de la deuxième section
    if (pthread_create(&t2, NULL, sum_partial, &ps2) != 0) {
        perror("Erreur lors de la création du thread 2");
        return EXIT_FAILURE;
    }

    // Création du troisième thread pour calculer la somme de la troisième section
    if (pthread_create(&t3, NULL, sum_partial, &ps3) != 0) {
        perror("Erreur lors de la création du thread 3");
        return EXIT_FAILURE;
    }

    // Attente de la fin de chaque thread
    if (pthread_join(t1, NULL) != 0) {
        perror("Erreur lors de l'attente du thread 1");
        return EXIT_FAILURE;
    }

    if (pthread_join(t2, NULL) != 0) {
        perror("Erreur lors de l'attente du thread 2");
        return EXIT_FAILURE;
    }

    if (pthread_join(t3, NULL) != 0) {
        perror("Erreur lors de l'attente du thread 3");
        return EXIT_FAILURE;
    }

    // Affichage de la somme totale
    printf("%d\n", somme);

    return EXIT_SUCCESS;
}
