#include "instrucao.h"

Instrucao inicializaInstrucao(char *instrucaoLida)
{
    Instrucao instrucao;
    char *token;

    token = strtok(instrucaoLida, " ");
    
    instrucao.tipoDeInstrucao = token[0];
    instrucao.parametroNumerico1 = -1;
    instrucao.parametroNumerico2 = -1;
    strcpy(instrucao.parametroTexto, "#####");

    token = strtok(NULL, " ");

    while (token != NULL)
    {

        if (instrucao.tipoDeInstrucao == 'N' ||
            instrucao.tipoDeInstrucao == 'D' ||
            instrucao.tipoDeInstrucao == 'F' ||
            instrucao.tipoDeInstrucao == 'B')
        {
            instrucao.parametroNumerico1 = atoi(token);
            break;
        }

        else if (instrucao.tipoDeInstrucao == 'V' ||
                 instrucao.tipoDeInstrucao == 'S' ||
                 instrucao.tipoDeInstrucao == 'A')
        {
            instrucao.parametroNumerico1 = atoi(token);
            token = strtok(NULL, " ");
            instrucao.parametroNumerico2 = atoi(token);
            break;
        }

        else if (instrucao.tipoDeInstrucao == 'R')
        {
            strcpy(instrucao.parametroTexto, token);
            break;
        }

        else if (instrucao.tipoDeInstrucao == 'T')
        {
            break;
        }

        else
        {
            printf("\nErro");
            break;
        }
    }

    return instrucao;
}

void printInstucao(Instrucao instrucao)
{
    printf("Instrução Lida - ");
    printf(" | tipoDeInstrucao %c", instrucao.tipoDeInstrucao);
    printf(" | parametroNumerico1 %d", instrucao.parametroNumerico1);
    printf(" | parametroNumerico2 %d", instrucao.parametroNumerico2);
    printf(" | parametroTexto %s\n", instrucao.parametroTexto);
}

/*
char str[] = "hello world";
char *token;

token = strtok(str, " ");
while (token != NULL) {
    printf("%s\n", token);
    token = strtok(NULL, " ");
    }
*/