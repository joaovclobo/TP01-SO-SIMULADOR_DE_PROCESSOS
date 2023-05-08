#include "cpu.h"

CPU* inicializaCPU()
{   
    CPU* cpu = (CPU*) malloc(sizeof(CPU));
    
    cpu->pidProcessoAtual = (int*) malloc(sizeof(int));
    *cpu->pidProcessoAtual = 57;
    cpu->pcProcessoAtual = (int*) malloc(sizeof(int));

    cpu->programaProcessoAtual = (Instrucao**) malloc(sizeof(Instrucao));
    cpu->variaveisProcessoAtual = (int**) malloc(sizeof(int));

    cpu->fatiaQuantum = 0;

    return cpu;
}

void escalonaProcesso(CPU* cpu, ProcessoSimulado* processoAtual)
{
    cpu->pidProcessoAtual = &(processoAtual->pid);
    cpu->pcProcessoAtual = processoAtual->pc;

    cpu->programaProcessoAtual = processoAtual->arrPrograma;
    cpu->variaveisProcessoAtual = &processoAtual->arrVariaveis;

    cpu->fatiaQuantum = 0;

}

void executaProxInstrucao(CPU* cpu)
{   
    char tipo = ((*cpu->programaProcessoAtual)[*cpu->pcProcessoAtual]).tipoDeInstrucao;
    int paramNum1 = ((*cpu->programaProcessoAtual)[*cpu->pcProcessoAtual]).parametroNumerico1;
    int paramNum2 = ((*cpu->programaProcessoAtual)[*cpu->pcProcessoAtual]).parametroNumerico2;
    char paramTxt[MAXBUFFER];
    strcpy(paramTxt, ((*cpu->programaProcessoAtual)[*cpu->pcProcessoAtual]).parametroTexto);

    switch (tipo)
    {
    case 'N':
        *cpu->variaveisProcessoAtual = instrucaoN(paramNum1);
        break;

    case 'D':
        instrucaoD(paramNum1, *cpu->variaveisProcessoAtual);
        break;

    case 'V':
        instrucaoV(paramNum1, paramNum2, *cpu->variaveisProcessoAtual);
        break;

    case 'A':
        instrucaoA(paramNum1, paramNum2, *cpu->variaveisProcessoAtual);
        break;

    case 'S':
        instrucaoS(paramNum1, paramNum2, *cpu->variaveisProcessoAtual);
        break;
    
    case 'B':
        break;

    case 'T':
        break;
    
    case 'F':
        
        break;

    case 'R':
        instrucaoR(paramTxt, cpu->programaProcessoAtual, cpu->pcProcessoAtual);
        break;

    default:
        break;
    }

    *(cpu->pcProcessoAtual) += 1;
}

void imprimeCPU(CPU cpu)
{   

    printf("Processo na CPU - PID %2d | ", *cpu.pidProcessoAtual);
    printf("PC %2d | ", *cpu.pcProcessoAtual);
    printf("Fatia do quantum já executado: %2d\n", cpu.fatiaQuantum);

    imprimeVariaveis(*cpu.variaveisProcessoAtual, numeroVariaveis(*cpu.programaProcessoAtual));
    //TODO - Descomentar isso
    imprimeArrPrograma(*cpu.programaProcessoAtual);
    putchar('\n');

}


/* -------------- Instruçẽos de programa que são processadas na CPU -------------- */
//TODO - manteremos os comentários sobre como funcionam as funções?

int *instrucaoN(int n)
{
    // Função N declara e aloca um vetor de “n” posições dinamicamente e
    // retorna um ponteiro para este vetor (vetorVariaveis);

    int *arrVariaveis;
    arrVariaveis = (int *)malloc(n * sizeof(int));
    if (arrVariaveis == NULL)
    {
        printf("Erro ao alocar memória");
        exit(1);
    }

    return arrVariaveis;
}

void instrucaoD(int x, int *arrVariaveis)
{
    // Função D “seta” 0 nos índices na posição x do vetor.
    arrVariaveis[x] = 0;
}

void instrucaoV(int x, int n, int *arrVariaveis)
{
    // V grava n nos índice x do vetor.
    arrVariaveis[x] = n;
}

void instrucaoA(int x, int n, int *arrVariaveis)
{
    // A soma n ao valor à variável no índice x.
    arrVariaveis[x] += n;
}

void instrucaoS(int x, int n, int *arrVariaveis){
    // 	S subtrai n ao valor à variável no índice x.
    arrVariaveis[x] -= n;
}

// int instrucaoB(int n)
// {
//     // TO DO: escalonador responsavel por mudar o processo de bloqueado para pronto e de pronto
//     // para em execução

//     // manda um comando para bloquear o processo e esperar n unidades de tempo e
//     // depois volta ele para “Pronto”. (Simula entrada e saída?)
//     //chamar as funções enfileira dos estadoPronto e estadoBloqueado?
// }

// void instrucaoT()
// {
//     //	Termina o processo (Manda “encerrei” p/ o gerenciador de processo).
// }

//TODO - esta função além de duplicar o processo que está na CPU deve incrementar em n o PC deste
void instrucaoF(int n)
{
    // Inicia outro processo Filho.
    // Filho - Copia exata do pai.
    // Filho - Executa após as próximas instruções do pai.
    // Pai - Pula n instruções depois de ler um comando F n (aumenta o PC do processo
    // executando em n na CPU).
    // ProcessoSimulado* novoProcessoFork;
    // copiaProcesso(&novoProcessoFork, *processoInit, 10);
    // printf("Processo Filho criado: \n");
    // imprimeProcesso(*novoProcessoFork, 4);


}

void instrucaoR(char *nomeDoArquivo, Instrucao** arrPrograma, int* pcProgramaAtual)
{   
    char caminhoArquivo[MAXBUFFER] = "./data/";
    strcat(caminhoArquivo, nomeDoArquivo);
    printf("%s ", caminhoArquivo);
    leInstrucoesArquivo(caminhoArquivo, arrPrograma);

    *pcProgramaAtual = -1;

}


