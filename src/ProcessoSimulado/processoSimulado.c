#include "processoSimulado.h"
#define MAXBUFFER 100

void criaProcessoInit(ProcessoSimulado* processoInit, int tempoSistema)
{
    processoInit->pid = 0;
    processoInit->ppid = 0;
    processoInit->pc = 0;
    // processoInit.arrVariaveis = ?
    processoInit->prioridade;
    processoInit->estado = PRONTO;
    processoInit->tempoInicio = tempoSistema;
    processoInit->tempoCPU = 0;
    processoInit->arrPrograma;

    leInstrucoesArquivo(".../data/init", processoInit->arrPrograma);
}
