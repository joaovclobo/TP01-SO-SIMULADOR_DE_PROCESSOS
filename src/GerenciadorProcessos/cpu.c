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

void executaProxInstrucao(CPU* cpu, int tempoAtualSistema, Lista* tabelaProcessos,
                             int* quantidadeProcessosIniciados, TipoFila** estadoPronto, TipoFila* estadoBloqueado)
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
        instrucaoB(paramNum1, cpu->pidProcessoAtual, estadoBloqueado);
        break;

    case 'T':
        break;
    
    case 'F':
        instrucaoF(paramNum1, cpu->pidProcessoAtual, cpu->pcProcessoAtual, quantidadeProcessosIniciados, tempoAtualSistema, tabelaProcessos, estadoPronto);
        break;

    case 'R':
        instrucaoR(paramTxt, cpu->programaProcessoAtual, cpu->pcProcessoAtual);
        break;

    default:
        break;
    }

    *(cpu->pcProcessoAtual) += 1;
    cpu->fatiaQuantum++;
}

int cpuLivre(CPU* cpu)
{
    return *(cpu->pidProcessoAtual) == NUMVAZIO; 
}

void imprimeCPU_2(CPU* cpu)
{   
    if(cpuLivre(cpu))
    {
        printf("CPU LIVRE!!!!\n");
    }else
    {
    printf("\nProcesso na CPU - PID %2d | ", *cpu->pidProcessoAtual);
    printf("PC %2d | ", *cpu->pcProcessoAtual);
    printf("Fatia do quantum já executado: %2d\n", cpu->fatiaQuantum);

    // imprimeVariaveis(*cpu->variaveisProcessoAtual, numeroVariaveis(*cpu->programaProcessoAtual));
    // imprimeArrPrograma(*cpu->programaProcessoAtual, *cpu->pcProcessoAtual);
    putchar('\n');
    }
}

void zeraCPU(CPU* cpu)
{
    cpu->pidProcessoAtual = (int*) malloc(sizeof(int));
    *cpu->pidProcessoAtual = NUMVAZIO;
    cpu->pcProcessoAtual = (int*) malloc(sizeof(int));
    *(cpu->pcProcessoAtual) = NUMVAZIO;

    cpu->programaProcessoAtual = NULL;
    cpu->variaveisProcessoAtual = NULL;

    cpu->fatiaQuantum = 0;
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

int instrucaoB(int n, int* pidProcessoAtual, TipoFila* estadoBloqueado)
{
    Enfileira(*pidProcessoAtual, n, estadoBloqueado);
}

// void instrucaoT()
// {
//     //	Termina o processo (Manda “encerrei” p/ o gerenciador de processo).
// }

void instrucaoF(int n, int* pidProcessoAtual, int* pcProcessoAtual, int* quantidadeProcessosIniciados, int tempoAtualSistema, Lista* tabelaProcessos, TipoFila** estadoPronto)
{

    ProcessoSimulado* processoPai = buscaProcesso(tabelaProcessos, *pidProcessoAtual);
    ProcessoSimulado* processoFilho = copiaProcesso(*processoPai, tempoAtualSistema, maiorPIDTabela(tabelaProcessos)+1);

    insereTabela(tabelaProcessos, processoFilho);
    Enfileira(processoFilho->pid, processoPai->tempoCPU, estadoPronto[processoFilho->prioridade]);
    quantidadeProcessosIniciados += 1;

    *pcProcessoAtual += n;

}

void instrucaoR(char *nomeDoArquivo, Instrucao** arrPrograma, int* pcProcessoAtual)
{   
    char caminhoArquivo[MAXBUFFER] = "./data/";
    strcat(caminhoArquivo, nomeDoArquivo);
    leInstrucoesArquivo(caminhoArquivo, arrPrograma);

    *pcProcessoAtual = -1;

}
