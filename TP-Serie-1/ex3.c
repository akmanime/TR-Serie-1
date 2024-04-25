#include <pthread.h> // Bibliothèque pour la gestion des threads
#include <stdio.h>
#include <stdlib.h>

void *Tachel(void *arg) { // Fonction exécutée par le premier thread
    int i = 0;
    while (i < 5) { // Boucle pour effectuer la tâche plusieurs fois
        printf("Execution de Tache 1\n");
        sleep(1); // Pause d'une seconde
        i++;
    }
    return NULL; // Fin de la fonction
}

void *Tache2(void *arg) { // Fonction exécutée par le deuxième thread
    int j = 0;
    while (j < 3) { // Boucle pour effectuer la tâche plusieurs fois
        printf("Execution de Tache 2\n");
        sleep(2); // Pause de deux secondes
        j++;
    }
    return NULL; // Fin de la fonction
}

int main(int argc, char *argv[]) {
    pthread_t thread1, thread2; // Déclaration des identifiants de thread

    // Test 1 : Démarrer les deux threads en même temps
    /*pthread_create(&thread1, NULL, Tachel, NULL);
    pthread_create(&thread2, NULL, Tache2, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);*/

    // Test 2 : Attendre que le premier thread se termine avant de démarrer le deuxième
    pthread_create(&thread1, NULL, Tachel, NULL); // Démarrer le premier thread
    pthread_join(thread1, NULL); // Attendre que le premier thread se termine
    pthread_create(&thread2, NULL, Tache2, NULL); // Démarrer le deuxième thread
    pthread_join(thread2, NULL); // Attendre que le deuxième thread se termine

    return EXIT_SUCCESS; // Fin du programme
}
