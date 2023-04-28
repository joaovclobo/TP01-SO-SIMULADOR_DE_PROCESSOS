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
            // pipeEntreProcessos(comando, 1);
            //lerDoPipe(fd);
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
}