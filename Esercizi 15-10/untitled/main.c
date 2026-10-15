#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     // Per fork(), sleep(), getpid()
#include <sys/wait.h>   // Per wait()

#define NUM_FIGLI 3

int main(void) {
    printf("[PADRE] Avvio del processo padre (PID: %d)\n", getpid());

    for (int i = 0; i < NUM_FIGLI; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("Errore nella creazione del figlio");
            return 1;
        }
        else if (pid == 0) {
            printf("  (figlio %d) Avviato con PID: %d (Padre PID: %d)\n", i + 1, getpid(), getppid());
            fflush(stdout);

            sleep(2); // Pausa di 2 secondi

            printf("  (figlio %d) Terminato.\n", i + 1);
            fflush(stdout);

            exit(0);
        }
    }

    printf("(padre) Tutti i figli creati. Attendo la loro conclusione\n");

    for (int i = 0; i < NUM_FIGLI; i++) {
        pid_t pid_finito = wait(NULL);
        printf("(padre) Ricevuta terminazione dal figlio con PID: %d\n", pid_finito);
    }

    return 0;
}