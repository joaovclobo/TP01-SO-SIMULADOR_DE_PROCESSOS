#include "instrucao.h"

void inicializaInstrucao(char *instrucaoLida, Instrucao* instrucao)
{
    char* token;

    token = strtok(instrucaoLida, " ");
    
    instrucao->tipoDeInstrucao = token[0];
    instrucao->parametroNumerico1 = NUMVAZIO;
    instrucao->parametroNumerico2 = NUMVAZIO;
    strcpy(instrucao->parametroTexto, TXTVAZIO);

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

void leInstrucoesArquivo(char* caminhoArquivo, Instrucao** arrPrograma)
{
    int i = 0;

    Instrucao* arrInstrucoes = (Instrucao*) malloc(MAXINTRUC * sizeof(Instrucao));
    
    char* cadaLinha = malloc(MAXBUFFER * sizeof(char));

    FILE* arquivoDeEntrada = abreArquivoRead(caminhoArquivo);

    while (fgets(cadaLinha, MAXBUFFER, arquivoDeEntrada) != NULL)
    {   
        cadaLinha[strcspn(cadaLinha, "\n")] = '\0';
        inicializaInstrucao(cadaLinha, arrInstrucoes+i);
        i++;

    }

    *arrPrograma = arrInstrucoes;
}

void copiaInstrucao(Instrucao* novaInstrucao, Instrucao* instrucaoBase)
{
    novaInstrucao->tipoDeInstrucao = instrucaoBase->tipoDeInstrucao;
    novaInstrucao ->parametroNumerico1 = instrucaoBase->parametroNumerico1;
    novaInstrucao->parametroNumerico2 = instrucaoBase->parametroNumerico2;
    strcpy(novaInstrucao->parametroTexto, instrucaoBase->parametroTexto);
}

void imprimeInstucao(Instrucao instrucao, int apontadorInst)
{
    
    if (apontadorInst == 1)
    {
        printf("->|Instrução: Tipo %c", instrucao.tipoDeInstrucao);

    } else
    {
        printf("  |Instrução: Tipo %c", instrucao.tipoDeInstrucao);
    }
    
    printf(" | Param 1 %3d", instrucao.parametroNumerico1);
    printf(" | Param 2 %5d", instrucao.parametroNumerico2);
    printf(" | Param txt %10s|\n", instrucao.parametroTexto);
}

void imprimeArrPrograma(Instrucao* arrPrograma, int pc)
{
    int i = 0;
    printf("  +------------------------ Programa do processo ------------------------+\n");

    while (arrPrograma[i-1].tipoDeInstrucao != 'T')
    {   
        if(i == pc)
        {
            imprimeInstucao(arrPrograma[i], 1);
        } else 
        {
            imprimeInstucao(arrPrograma[i], 0);
        }
        
        i++;
    }
}
