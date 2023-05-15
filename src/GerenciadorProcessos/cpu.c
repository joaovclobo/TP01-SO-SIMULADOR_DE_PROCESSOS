#include "cpu.h"

CPU* inicializaCPU()
{   
    CPU* cpu = (CPU*) malloc(sizeof(CPU));
    
    cpu->pidProcessoAtual = (int*) malloc(sizeof(int));
    *cpu->pidProcessoAtual = NUMVAZIO;
    cpu->pcProcessoAtual = (int*) malloc(sizeof(int));

    cpu->programaProcessoAtual = (Instrucao**) malloc(sizeof(Instrucao));
    cpu->variaveisProcessoAtual = (int**) malloc(sizeof(int));

    cpu->fatiaQuantum = 0;

    return cpu;
}

void carregaProcesso(CPU* cpu, ProcessoSimulado* processoAtual)
{
    cpu->pidProcessoAtual = &(processoAtual->pid);
    cpu->pcProcessoAtual = processoAtual->pc;

    cpu->programaProcessoAtual = processoAtual->arrPrograma;
    cpu->variaveisProcessoAtual = &processoAtual->arrVariaveis;

    cpu->fatiaQuantum = 0;

}

void executaProxInstrucao(CPU* cpu, int tempoAtualSistema, Lista* tabelaProcessos)
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
        instrucaoF(paramNum1, cpu->pidProcessoAtual, cpu->pcProcessoAtual, tempoAtualSistema, tabelaProcessos);
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
    imprimeArrPrograma(*cpu.programaProcessoAtual, *cpu.pcProcessoAtual);
    putchar('\n');

}


/* -------------- Instruçẽos de programa que são processadas na CPU -------------- */

int *instrucaoN(int n)
{

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
    arrVariaveis[x] = 0;
}

void instrucaoV(int x, int n, int *arrVariaveis)
{
    arrVariaveis[x] = n;
}

void instrucaoA(int x, int n, int *arrVariaveis)
{
    arrVariaveis[x] += n;
}

void instrucaoS(int x, int n, int *arrVariaveis){
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

void instrucaoF(int n, int* pidProcessoAtual, int* pcProcessoAtual,int tempoAtualSistema, Lista* tabelaProcessos)
{

    ProcessoSimulado* processoPai = buscaProcesso(tabelaProcessos, *pidProcessoAtual);
    ProcessoSimulado* processoFilho = copiaProcesso(*processoPai, tempoAtualSistema, maiorPIDTabela(tabelaProcessos)+1);

    insereTabela(tabelaProcessos, processoFilho);
    imprimeTabela(tabelaProcessos);

    *pcProcessoAtual += n;

}

void instrucaoR(char *nomeDoArquivo, Instrucao** arrPrograma, int* pcProcessoAtual)
{   
    char caminhoArquivo[MAXBUFFER] = "./data/";
    strcat(caminhoArquivo, nomeDoArquivo);
    printf("%s ", caminhoArquivo);
    leInstrucoesArquivo(caminhoArquivo, arrPrograma);

    *pcProcessoAtual = -1;

}
