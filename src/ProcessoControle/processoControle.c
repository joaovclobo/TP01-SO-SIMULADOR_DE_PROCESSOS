#include "processoControle.h"

char controle(FILE* arquivoDeEntrada, int opcao)
{
    char cadaLinha[MAXBUFFER];
    char comando;

    switch (opcao) {
        case 1:
            //Esse print pode ser um problema
            // printf("Digite um comando: ");
            scanf(" %c", &comando);
            break;

        case 2:

            if (fgets(cadaLinha, MAXBUFFER, arquivoDeEntrada) != NULL){
                printf("%s", cadaLinha);
                comando = cadaLinha[0];

            }

            break;

        default:
            break;
    }
    return comando;

}
