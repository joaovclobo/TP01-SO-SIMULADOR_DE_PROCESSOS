#include <stdio.h>
#include <stdlib.h>
#include "unistd.h"

int main() {
    int fd[2];
    pid_t pid;

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {  // Processo filho
        close(fd[1]);  // Fecha a extremidade de escrita do pipe

        char buffer[255];
        int bytes_read = read(fd[0], buffer, sizeof(buffer));  // Lê os dados do pipe
        printf("Filho: %.*s\n", bytes_read, buffer);  // Imprime os dados lidos

        close(fd[0]);  // Fecha a extremidade de leitura do pipe
        exit(EXIT_SUCCESS);
    } else {  // Processo pai
        close(fd[0]);  // Fecha a extremidade de leitura do pipe

        char *message = "Hello, pipe!";
        write(fd[1], message, sizeof(message));  // Escreve dados no pipe

        close(fd[1]);  // Fecha a extremidade de escrita do pipe
        wait(NULL);  // Aguarda o processo filho terminar
        exit(EXIT_SUCCESS);
    }
}