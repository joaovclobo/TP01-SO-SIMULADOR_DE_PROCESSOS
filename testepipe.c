#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


#define BUFFER 256

int main(void)
{
    int fd[2]; /* File descriptors pro Pipe*/
    pid_t pid; /* Variável para armazenar o pid*/

    /* Criando nosso Pipe */
    if(pipe(fd)<0) {
        perror("pipe") ;
        return -1 ;
    }

    /* Criando o processo filho*/
    if ((pid = fork()) < 0)
    {
        perror("fork");
        exit(1);
    }
    /* Processo Pai*/

    char str[BUFFER] = "Aprendi a usar Pipes em C!";

    while (strcmp(str, "M") != 0)
    {
        scanf("%s", str);
    
        if (pid > 0)
        {
            /*No pai, vamos ESCREVER, então vamos fechar a LEITURA do Pipe neste lado*/
            close(fd[0]);

            printf("String enviada pelo pai no Pipe: '%s'", str);

            /* Escrevendo a string no pipe */
            write(fd[1], str, sizeof(str) + 1);
            exit(0);
        }
        /* Processo Filho*/
        else
        {
            char str_recebida[BUFFER];

            /* No filho, vamos ler. Então vamos fechar a entrada de ESCRITA do pipe */
            close(fd[1]);

            /* Lendo o que foi escrito no pipe, e armazenando isso em 'str_recebida' */
            read(fd[0], str_recebida, sizeof(str_recebida));

            printf("\nString lida pelo filho no Pipe : '%s'\n\n", str_recebida);
            exit(0);
        }
    }

    return(0);
}