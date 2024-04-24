#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *func(void *arg) {
	char *msg = (char *) arg;
	printf("Message = %s\n", msg);
	return NULL;
}

int main(int argc, char *argv[]) {
	pthread_t t;
	char *msg = "Threads are awesome!";
	if (pthread_create(&t, NULL, func, msg) != 0) {
		perror("thread creation error");
		return EXIT_FAILURE;
	}
	if(pthread_join(t, NULL) !=0){
        perror("Error");
        EXIT_FAILURE;
    }
	return EXIT_SUCCESS;
}
