#include "processoControle.h"

char controle(FILE* arquivoDeEntrada, int opcao)
{
    char cadaLinha[MAXBUFFER];
    char comando;

    switch (opcao) {
        case 1:
            scanf(" %c", &comando);
            break;

        case 2:
            if (fgets(cadaLinha, MAXBUFFER, arquivoDeEntrada) != NULL){
                comando = cadaLinha[0];

            }
            break;

        default:
            break;
            
    }
    return comando;

}
