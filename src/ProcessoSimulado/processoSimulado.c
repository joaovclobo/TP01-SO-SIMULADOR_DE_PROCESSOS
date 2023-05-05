#include "processoSimulado.h"
#define MAXBUFFER 100

void criaProcessoInit(ProcessoSimulado* processoInit, int tempoSistema)
{

    processoInit->pid = 0;
    processoInit->ppid = 0;
    processoInit->pc = 0;
    //arrVariaveis não é iniciado quando o processo é criado
    processoInit->prioridade;
    processoInit->estado = PRONTO;
    processoInit->tempoInicio = tempoSistema;
    processoInit->tempoCPU = 0;
    processoInit->arrPrograma;

    leInstrucoesArquivo(".../data/init", processoInit->arrPrograma);
    
}

//Funções para executar as instruções de um processo simulado

int* instrucaoN(int n){
    int* arrVariaveis = (int*) malloc(n * sizeof(int));
    return arrVariaveis;
}
