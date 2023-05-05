#include "processoSimulado.h"
#define MAXBUFFER 100

void criaProcessoInit(ProcessoSimulado** processoInit, int tempoSistema)
{
    ProcessoSimulado* processo = (ProcessoSimulado*) malloc(sizeof(ProcessoSimulado));

    processo->pid = 0;
    processo->ppid = 0;
    processo->pc = 0;
    //arrVariaveis não é iniciado quando o processo é criado
    processo->prioridade;
    processo->estado = PRONTO;
    processo->tempoInicio = tempoSistema;
    processo->tempoCPU = 0;

    processo->arrPrograma = (Instrucao**) malloc(MAXINTRUC * sizeof(Instrucao));
    leInstrucoesArquivo("./data/init", processo->arrPrograma);

    *processoInit = processo;
    
}

// void copiaProcesso(ProcessoSimulado* processoPai, ProcessoSimulado processoFilho)
// {
//     processoFilho->pid = processoPai->pid;
//     processoFilho->ppid =  processoPai->ppid;
//     processoFilho->pc =  processoPai->pc;
//     processoFilho->prioridade = processoPai->prioridade;
//     processoFilho->estado =  processoPai->estado;
//     processoFilho->tempoInicio =  processoPai->tempoInicio;
//     processoFilho->tempoCPU =  processoPai->tempoCPU;

// }

//Funções para executar as instruções de um processo simulado

void imprimeProcesso(ProcessoSimulado processo)
{
    int opcao = 2;

    printf("Processo - pid %2d | ", processo.pid);
    printf("ppid %2d | ", processo.ppid);
    printf("pc %2d | ", processo.pc);
    printf("prioridade %d | ", processo.prioridade);
    imprimeEstado(processo.estado);
    printf("tempoInicio %d | ", processo.tempoInicio);
    printf("tempoCPU %d\n", processo.tempoCPU);

    printf("Escolha as informações para exibir do  processo");
    printf("\n1) Não exibir nenhuma;");
    printf("\n2) Variáveis do processo;");
    printf("\n3) Instruções do processo;");
    printf("\n4) Instruções e variáveis do processo;");
    printf("\n>> Escolha a opção: ");
    scanf("%d", &opcao);
    
    switch (opcao)
    {

        case 1:
        break;

        case 2:
            printf("Variaveis\n");
            break;
    
        case 3:
            imprimeArrPrograma(*(processo.arrPrograma));
        break;
    
        case 4:
            printf("Variaveis\n");
            imprimeArrPrograma(*(processo.arrPrograma));

        default:
            break;
    }
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

int* instrucaoN(int n){
    int* arrVariaveis = (int*) malloc(n * sizeof(int));
    return arrVariaveis;
}
