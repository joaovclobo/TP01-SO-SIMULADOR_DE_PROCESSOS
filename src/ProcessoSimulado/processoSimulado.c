#include "processoSimulado.h"
#define MAXBUFFER 100

ProcessoSimulado* criaProcessoInit(int tempoSistema)
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

    processo->arrPrograma = (Instrucao**) malloc(sizeof(Instrucao));
    leInstrucoesArquivo("./data/init", processo->arrPrograma);

    return processo;
    
}

ProcessoSimulado* copiaProcesso(ProcessoSimulado processoPai, int tempoAtualSistema, int novoPid)
{
    ProcessoSimulado* processo = (ProcessoSimulado*) malloc(sizeof(ProcessoSimulado));

    processo->pid = novoPid;
    processo->ppid = processoPai.pid;

    //+1 porque deve pular exatamente uma instrução
    processo->pc = (int*) malloc(sizeof(int));
    *(processo->pc) = *(processoPai.pc) + 1; 

    processo->arrVariaveis = (int*) malloc(numeroVariaveis(*processoPai.arrPrograma) * sizeof(int));
    copiaVariaveis(processoPai.arrVariaveis, processo->arrVariaveis, numeroVariaveis(*processoPai.arrPrograma));

    processo->prioridade = processoPai.prioridade;
    processo->estado = PRONTO;
    processo->tempoInicio = tempoAtualSistema;
    processo->tempoCPU = 0;

    processo->arrPrograma = (Instrucao**) malloc(sizeof(Instrucao));
    copiaArrPrograma(processo->arrPrograma, *(processoPai.arrPrograma));

    return processo;

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

int numeroVariaveis(Instrucao* arrPrograma)
{
    return arrPrograma[0].parametroNumerico1;
}


void imprimeProcesso(ProcessoSimulado processo, int opcao)
{

    printf("-> Processo - PID %2d | ", processo.pid);
    printf("PPID %2d | ", processo.ppid);
    printf("PC %2d | ", *(processo.pc));
    printf("Prioridade %d | ", processo.prioridade);
    imprimeEstado(processo.estado);
    printf("Tempo de inicio %2d | ", processo.tempoInicio);
    printf("Tempo de CPU %2d\n", processo.tempoCPU);
    
    switch (opcao)
    {

        case 1:
        break;

        case 2:
            imprimeVariaveis(processo.arrVariaveis, numeroVariaveis(*processo.arrPrograma));
            break;
    
        case 3:
            imprimeArrPrograma(*(processo.arrPrograma), *processo.pc);
        break;
    
        case 4:
            imprimeVariaveis(processo.arrVariaveis, numeroVariaveis(*processo.arrPrograma));
            imprimeArrPrograma(*(processo.arrPrograma), *processo.pc);

        default:
            break;
    }
    putchar('\n');

}


void imprimeVariaveis(int* arrVariaveis, int tamanho)
{
    printf("  |Variáveis: ");

    for (int i = 0; i < tamanho; i++)
    {
        printf("%d ", arrVariaveis[i]);

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
            printf("Estado: EXECUCAO  | ");
            break;

        case PRONTO:
            printf("Estado: PRONTO    | ");
            break;
            
        default:
            break;
    }
} 
