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
