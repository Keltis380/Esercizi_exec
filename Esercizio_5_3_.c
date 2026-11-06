#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        char *args[] = {"cat", "/etc/hostname", NULL};
        execvp("cat", args);
        perror("execvp");
        exit(1);
    }

    wait(NULL);
    printf("Figlio terminato\n");

    return 0;
}