#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     // Contiene fork(), sleep()
#include <sys/wait.h>   // Contiene wait()

int main(void) {
    // processo padre
    pid_t pid = fork();

    if (pid < 0) {
        // Se fork() restituisce un valore negativo, c'è stato un errore
        perror("Errore durante la creazione del processo");
        return 1;
    }
    else if (pid == 0) {
        printf("Sono il figlio: Processo avviato (PID: %d, Padre PID: %d)\n", getpid(), getppid());

        for (int i = 1; i <= 5; i++) {
            printf("(figlio) Numero: %d\n", i);
            fflush(stdout); // Forza lo svuotamento del buffer di stampa prima dello sleep
            sleep(1);       // Pausa di 1 secondo
        }

        exit(0); // Il figlio termina
    }
    else {
        printf("Sono il padre: Attendo che il figlio (PID: %d) finisca\n", pid);

        // Il padre si blocca qui finché il figlio non chiama exit()
        wait(NULL);

        printf("Il figlio ha finito. Ora stampo i numeri\n");

        for (int i = 6; i <= 10; i++) {
            printf("(Padre) Numero: %d\n", i);
            fflush(stdout);
            sleep(1);
        }

    }

    return 0;
}