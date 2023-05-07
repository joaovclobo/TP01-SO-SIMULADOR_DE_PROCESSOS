#include "processoSimulado.h"
#define MAXBUFFER 100

void criaProcessoInit(ProcessoSimulado** processoInit, int tempoSistema)
{
    ProcessoSimulado* processo = (ProcessoSimulado*) malloc(sizeof(ProcessoSimulado));

    processo->pid = 0;
    processo->ppid = 0;
    processo->pc = (int*) malloc(sizeof(int));
    *(processo->pc) = 0;
    processo->prioridade = 0;
    processo->estado = PRONTO;
    processo->tempoInicio = tempoSistema;
    processo->tempoCPU = 0;

    printf("pc processo filho: %d\n", processo->pc);

    processo->arrPrograma = (Instrucao**) malloc(MAXINTRUC * sizeof(Instrucao));
    leInstrucoesArquivo("./data/init", processo->arrPrograma);

    processo->arrVariaveis = (int*) malloc(numeroVariaveis(*processo) * sizeof(int));

    //TODO - APAGAR ISSO PELAMOR DE DEUS

    for (int i = 0; i < 5; i++)
    {
        processo->arrVariaveis[i] = (i+3)*10;
    }

    *processoInit = processo;
    
}

void copiaProcesso(ProcessoSimulado** novoProcesso, ProcessoSimulado processoPai, int tempoAtualSistema)
{
    ProcessoSimulado* processo = (ProcessoSimulado*) malloc(sizeof(ProcessoSimulado));

    //TODO - Confirmar com o daniel como sera
    processo->pid = processoPai.pid;
    processo->ppid = processoPai.ppid;

    //+1 porque deve pular exatamente uma instrução
    processo->pc = (int*) malloc(sizeof(int));
    *(processo->pc) = *(processoPai.pc) + 1; 

    processo->arrVariaveis = (int*) malloc(numeroVariaveis(processoPai) * sizeof(int));
    copiaVariaveis(processoPai.arrVariaveis, processo->arrVariaveis, numeroVariaveis(processoPai));

    processo->prioridade = processoPai.prioridade;
    processo->estado = PRONTO;
    processo->tempoInicio = tempoAtualSistema;
    processo->tempoCPU = 0;

    processo->arrPrograma = (Instrucao**) malloc(MAXINTRUC * sizeof(Instrucao));
    copiaArrPrograma(processo->arrPrograma, *(processoPai.arrPrograma));

    *novoProcesso = processo;

}

void copiaVariaveis(int* arrVariaveisBase, int* arrVariaveisNovo, int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        arrVariaveisNovo[i] = arrVariaveisBase[i];
    }
}

void copiaArrPrograma(Instrucao** arrNovo, Instrucao* arrBase)
{
    Instrucao* arrPrograma = (Instrucao*) malloc(MAXINTRUC * sizeof(Instrucao));

    int i = 0;

    while (arrBase[i-1].tipoDeInstrucao != 'T')
    {
        copiaInstrucao(&arrPrograma[i], &arrBase[i]);
        i++;
    }

    *arrNovo = arrPrograma;
}

int numeroVariaveis(ProcessoSimulado processo)
{
    return (processo.arrPrograma)[0]->parametroNumerico1;
}


void imprimeProcesso(ProcessoSimulado processo, int opcao)
{

    printf("-> Processo - pid %2d | ", processo.pid);
    printf("ppid %2d | ", processo.ppid);
    printf("pc %2d | ", *(processo.pc));
    printf("prioridade %d | ", processo.prioridade);
    imprimeEstado(processo.estado);
    printf("tempoInicio %2d | ", processo.tempoInicio);
    printf("tempoCPU %2d\n", processo.tempoCPU);
    
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

void imprimeEstado(Estado estado)
{
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
