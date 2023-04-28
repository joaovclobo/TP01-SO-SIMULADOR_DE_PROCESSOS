#include "pipe.h"

void escreverNoPipe(int fd[2], char letra) {
    close(fd[0]); 
    printf("Letra escrita: %c\n", letra);
    write(fd[1], &letra, sizeof(char)); 
    close(fd[1]);
}

void lerDoPipe(int fd[2]) {
    close(fd[1]);  
    char letra;
    read(fd[0], &letra, sizeof(char));  
    printf("Letra recebida: %c\n", letra);
    close(fd[0]);  
}

/*
>> MAIN
#include "./src/ProcessoControle/processoControle.h"
#include "./src/GerenciadorProcessos/gerenciadorProcessos.h"

int main(int argc, char **argv)
{
    int fd[2];
    pipe(fd);

    controle(fd);
    gerenciadorProcessos(fd);

    return 0;
}

>> GERENCIADOR
#include "gerenciadorProcessos.h"
#include "../Pipe/pipe.h"
#define MAXBUFFER 100

void gerenciadorProcessos(int fd[2])
{
    lerDoPipe(fd);
}

>> CONTROLE
#include "processoControle.h"

void controle(int fd[2])
{
    char caminhoArquivo[MAXBUFFER] = "./data/comands";

    char cadaLinha[MAXBUFFER];
    int opcao = MenuInicial();

    switch (opcao)
    {
    case 1:
        char comando[MAXBUFFER];

        printf("Entrada padrão\n");

        while (comando[0] != 'M')
        {
            scanf("%s", comando);
            escreverNoPipe(fd, comando[0]);
            lerDoPipe(fd);
        }
        break;

    case 2:
        FILE *arquivoDeEntrada = abreArquivoRead(caminhoArquivo);

        while (fgets(cadaLinha, MAXBUFFER, arquivoDeEntrada) != NULL)
        {
            printf("%s", cadaLinha);
            // pipeEntreProcessos(cadaLinha, 1);
        }

        fclose(arquivoDeEntrada);
        break;

    default:
        break;
    }

    // Fechando os descritores de arquivo no processo pai após a escrita
    close(fd[1]); 
}

>> PIPE
void escreverNoPipe(int fd[2], char letra) {
    printf("Letra escrita: %c\n", letra);
    write(fd[1], &letra, sizeof(char)); 
}

void lerDoPipe(int fd[2]) {
    char letra;
    read(fd[0], &letra, sizeof(char));  
    printf("Letra recebida: %c\n", letra);
    
    // Fechando o descritor de arquivo no processo filho após a leitura
    close(fd[0]);  
}

*/