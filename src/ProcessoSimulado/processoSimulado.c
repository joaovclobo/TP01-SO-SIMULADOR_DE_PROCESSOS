#include "processoSimulado.h"
#define MAXBUFFER 100

void criaProcessoInit(ProcessoSimulado** processoInit, int tempoSistema)
{
    ProcessoSimulado* processo = (ProcessoSimulado*) malloc(sizeof(ProcessoSimulado));

    processo->pid = 0;
    processo->ppid = 0;
    processo->pc = 0;
    processo->prioridade;
    processo->estado = PRONTO;
    processo->tempoInicio = tempoSistema;
    processo->tempoCPU = 0;

    processo->arrPrograma = (Instrucao**) malloc(MAXINTRUC * sizeof(Instrucao));
    leInstrucoesArquivo("./data/init", processo->arrPrograma);

    //TODO - APAGAR ISSO PELAMOR DE DEUS
    processo->arrVariaveis = (int*) malloc(numeroVariaveis(*processo) * sizeof(int));

    for (int i = 0; i < 5; i++)
    {
        processo->arrVariaveis[i] = (i+3)*10;
    }

    *processoInit = processo;
    
}

void copiaProcesso(ProcessoSimulado** novoProcesso, ProcessoSimulado processoPai)
{
    ProcessoSimulado* processo = (ProcessoSimulado*) malloc(sizeof(ProcessoSimulado));

    processo->pid = processoPai.pid;
    processo->ppid = processoPai.ppid;
    processo->pc = processoPai.pc;

    //TODO - Copiar as variáveis
    // processo->arrVariaveis = 

    processo->prioridade = processoPai.prioridade;
    processo->estado = processoPai.estado;
    processo->tempoInicio = processoPai.tempoInicio;
    processo->tempoCPU = processoPai.tempoCPU;

    processo->arrPrograma = (Instrucao**) malloc(MAXINTRUC * sizeof(Instrucao));
    //TODO - Copiar só a proxima que é o R
    // leInstrucoesArquivo("./data/init", processo->arrPrograma);

    *novoProcesso = processo;
    
}

void copiaVariaveis(int* arrVariaveisBase, int* arrVariaveisNovo, int tamanho)
{
    int* arrtemp = (int*) malloc(tamanho * sizeof(int));

    for (int i = 0; i < tamanho; i++) {
        arrtemp[i] = arrVariaveisBase[i];
    }

    arrVariaveisNovo = arrtemp;
}

int numeroVariaveis(ProcessoSimulado processo)
{
    return (processo.arrPrograma)[0]->parametroNumerico1;
}

void imprimeProcesso(ProcessoSimulado processo, int opcao)
{

    printf("-> Processo - pid %2d | ", processo.pid);
    printf("ppid %2d | ", processo.ppid);
    printf("pc %2d | ", processo.pc);
    printf("prioridade %d | ", processo.prioridade);
    imprimeEstado(processo.estado);
    printf("tempoInicio %d | ", processo.tempoInicio);
    printf("tempoCPU %d\n", processo.tempoCPU);
    
    switch (opcao)
    {

        case 1:
        break;

        case 2:
            imprimeVariaveis(processo.arrVariaveis, numeroVariaveis(processo));
            break;
    
        case 3:
            imprimeArrPrograma(*(processo.arrPrograma));
        break;
    
        case 4:
            imprimeVariaveis(processo.arrVariaveis, numeroVariaveis(processo));
            imprimeArrPrograma(*(processo.arrPrograma));

        default:
            break;
    }
    putchar('\n');

}

void imprimeEstado(Estado estado) {

    switch (estado)
    {
        case BLOQUEADO:
            printf("Estado: BLOQUEADO | ");
            break;

        case EXECUCAO:
            printf("Estado: EXECUCAO | ");
            break;

        case PRONTO:
            printf("Estado: PRONTO | ");
            break;
            
        default:
            break;
    }
} 

void imprimeVariaveis(int* arrVariaveis, int tamanho)
{
    printf("   └ Variáveis do processo: ");

    for (int i = 0; i < tamanho; i++)
    {
        printf("%d ", arrVariaveis[i]);

    }
    putchar('\n');

}

//Funções para executar as instruções de um processo simulado
//TODO - Não vão ficar aqui

int* instrucaoN(int n){
    int* arrVariaveis = (int*) malloc(n * sizeof(int));
    return arrVariaveis;
}
