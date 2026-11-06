#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int fd[2];

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }

    pid_t pid1 = fork();

    if (pid1 == -1) {
        perror("fork");
        exit(1);
    }

    if (pid1 == 0) {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);

        char *args[] = {"ls", "/tmp", NULL};
        execvp("ls", args);

        perror("execvp");
        exit(1);
    }

    pid_t pid2 = fork();

    if (pid2 == -1) {
        perror("fork");
        exit(1);
    }

    if (pid2 == 0) {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);

        char *args[] = {"wc", "-l", NULL};
        execvp("wc", args);

        perror("execvp");
        exit(1);
    }

    close(fd[0]);
    close(fd[1]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}