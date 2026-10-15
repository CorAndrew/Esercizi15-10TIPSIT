#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     // Per fork(), sleep(), getpid(), getppid()
#include <sys/wait.h>   // Per wait()

int main(void) {
    printf("(nonno) Avviato con PID: %d\n", getpid());
    fflush(stdout);

    // Il Nonno crea il Padre
    pid_t pid_padre = fork();

    if (pid_padre < 0) {
        perror("Errore nella fork del Nonno");
        return 1;
    }
    else if (pid_padre == 0) {-
        printf("(padre) Avviato con PID: %d (Mio padre/Nonno PID: %d)\n", getpid(), getppid());
        fflush(stdout);
        pid_t pid_nipote = fork();

        if (pid_nipote < 0) {
            perror("Errore nella fork del Padre");
            exit(1);
        }
        else if (pid_nipote == 0) {
            printf( "(figlio) Avviato con PID: %d (Mio padre PID: %d)\n", getpid(), getppid());
            fflush(stdout);

            sleep(1);

            printf(" (figlio) Ho finito\n");
            fflush(stdout);
            exit(0);
        }
        else {
            printf("(padre) In attesa del figlio (PID: %d)...\n", pid_nipote);
            fflush(stdout);

            wait(NULL);

            printf("(padre) posso terminare \n");
            fflush(stdout);
            exit(0);
        }
    }
    else {
        printf("(nonno) In attesa del Padre (PID: %d)...\n", pid_padre);
        fflush(stdout);

        wait(NULL);

        printf("(nonno) posso terminare\n");
        fflush(stdout);
    }

    return 0;
}