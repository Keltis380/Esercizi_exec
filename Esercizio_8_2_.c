#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    char comando[100];

    while (1) {
        while (waitpid(-1, NULL, WNOHANG) > 0) {
        }

        printf("Inserisci comando: ");
        fflush(stdout);

        if (fgets(comando, sizeof(comando), stdin) == NULL)
            break;

        comando[strcspn(comando, "\n")] = '\0';

        if (strcmp(comando, "exit") == 0)
            break;

        if (strlen(comando) == 0)
            continue;

        pid_t pid = fork();

        if (pid == -1) {
            perror("fork");
            continue;
        }

        if (pid == 0) {
            char *args[] = {comando, NULL};
            execvp(comando, args);
            perror("execvp");
            exit(127);
        }

        else {
            printf("Creato figlio PID: %d\n", pid);
        }
    }

    while (wait(NULL) > 0) {
    }

    return 0;
}