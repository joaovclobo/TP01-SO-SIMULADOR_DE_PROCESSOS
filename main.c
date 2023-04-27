#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./src/GerenciadorProcessos/instrucao.h"
#include "./src/Menu/menu.h"

int main(int argc, char **argv)
{
    char caminhoArquivo[MAXBUFFER] = "./data/init.txt";
    char cadaLinha[MAXBUFFER];
    FILE *arquivoDeEntrada;
    int opcao = MenuInicial();

    //APAGAR 
    Instrucao instTemp;

    switch (opcao)
    {
    case 1:
        printf("Entrada padrão\n");
        break;

    case 2:
        if ((arquivoDeEntrada = fopen(caminhoArquivo, "r")) == NULL)
        {
            printf("\nArquivo não encontrado!");
            return 0;
        }

        while (fgets(cadaLinha, MAXBUFFER, arquivoDeEntrada) != NULL)
        {
            instTemp = inicializaInstrucao(cadaLinha);
            //printf(instTemp);
            printInstucao(instTemp);

        }

        break;

    default:
        break;
    }

    fclose(arquivoDeEntrada);

    return 0;
}