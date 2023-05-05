#include "instrucao.h"

void inicializaInstrucao(char *instrucaoLida, Instrucao* instrucao)
{
    char* token;

    token = strtok(instrucaoLida, " ");
    
    instrucao->tipoDeInstrucao = token[0];
    instrucao->parametroNumerico1 = -1;
    instrucao->parametroNumerico2 = -1;
    strcpy(instrucao->parametroTexto, "#####");

    token = strtok(NULL, " ");

    while (token != NULL)
    {

        if (instrucao->tipoDeInstrucao == 'N' ||
            instrucao->tipoDeInstrucao == 'D' ||
            instrucao->tipoDeInstrucao == 'F' ||
            instrucao->tipoDeInstrucao == 'B')
        {
            instrucao->parametroNumerico1 = atoi(token);
            break;
        }

        else if (instrucao->tipoDeInstrucao == 'V' ||
                 instrucao->tipoDeInstrucao == 'S' ||
                 instrucao->tipoDeInstrucao == 'A')
        {
            instrucao->parametroNumerico1 = atoi(token);
            token = strtok(NULL, " ");
            instrucao->parametroNumerico2 = atoi(token);
            break;
        }

        else if (instrucao->tipoDeInstrucao == 'R')
        {
            strcpy(instrucao->parametroTexto, token);
            break;
        }

        else if (instrucao->tipoDeInstrucao == 'T')
        {
            break;
        }

        else
        {
            printf("\nErro");
            break;
        }
    }
}

void leInstrucoesArquivo(char* caminhoArquivo, Instrucao** programa)
{
    Instrucao* arrPrograma = (Instrucao*) malloc(MAXINTRUC * sizeof(Instrucao));
    int i = 0;
    
    //TODO - Simplificar usando a função
    char* cadaLinha = malloc(MAXBUFFER * sizeof(char));
    FILE* arquivoDeEntrada;

    if ((arquivoDeEntrada = fopen(caminhoArquivo, "r")) == NULL){
        printf("\nArquivo não encontrado!");
        
    }

    while (fgets(cadaLinha, MAXBUFFER, arquivoDeEntrada) != NULL)
    {   
        cadaLinha[strcspn(cadaLinha, "\n")] = '\0';
        inicializaInstrucao(cadaLinha, arrPrograma+i);
        i++;

    }
    *programa = arrPrograma;

}


void imprimeInstucao(Instrucao instrucao)
{
    printf("Instrução - ");
    printf(" | Tipo %c", instrucao.tipoDeInstrucao);
    printf(" | Param 1 %5d", instrucao.parametroNumerico1);
    printf(" | Param 2 %5d", instrucao.parametroNumerico2);
    printf(" | Param txt %s\n", instrucao.parametroTexto);
}

void imprimeArrPrograma(Instrucao* arrPrograma)
{
    int i = 1;

    while (arrPrograma[i-1].tipoDeInstrucao != 'T')
    {
        imprimeInstucao(arrPrograma[i]);
        i++;
    }
}