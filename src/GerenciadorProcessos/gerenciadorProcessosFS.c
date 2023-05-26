#include "gerenciadorProcessosFS.h"

GerenciadorProcessos *inicializaGerenciador(int numCPUs, int quantum)
{
    GerenciadorProcessos *gerenciador = (GerenciadorProcessos *)malloc(sizeof(GerenciadorProcessos));

    gerenciador->tempo = 0;
    gerenciador->quantum = quantum;
    gerenciador->quantidadeProcessosIniciados = 0;
    gerenciador->tempoTotalExecucao = 0;

    gerenciador->numCPUs = numCPUs;

    gerenciador->cpus = (CPU **)malloc(numCPUs * sizeof(CPU *));
    gerenciador->estadoExecucao = (int *)malloc(numCPUs * sizeof(int));

    for (int i = 0; i < numCPUs; i++)
    {
        gerenciador->cpus[i] = inicializaCPU();
        gerenciador->estadoExecucao[i] = NUMVAZIO;
    }

    gerenciador->tabelaProcessos = criaLista();

    gerenciador->estadoProntoFS = criaFila();

    gerenciador->estadoBloqueado = criaFila();

    return gerenciador;
}

void iniciaProcessoInit(GerenciadorProcessos *gerenciador)
{
    ProcessoSimulado *processoInit = criaProcessoInit(gerenciador->tempo);
    Enfileira(processoInit->pid, NUMVAZIO, gerenciador->estadoProntoFS);
    insereTabela(gerenciador->tabelaProcessos, processoInit);
    gerenciador->quantidadeProcessosIniciados += 1;
}

void gerenciadorProcessos(GerenciadorProcessos *gerenciador, char comando)
{
    if (comando == 'U')
    {
        encerraUnidadeTempo(gerenciador);

        if (gerenciador->tempo == 1)
        {
            iniciaProcessoInit(gerenciador); // Na primeira unidade de tempo do sistema, é iniciado e carregado o primeiro processo

            escalonaProcessosCPUs(gerenciador);

            executaCPUs(gerenciador);

            trocaDeContexto(gerenciador);
        }
        else
        {

            escalonaProcessosCPUs(gerenciador);

            executaCPUs(gerenciador);

            trocaDeContexto(gerenciador);
        }
    }
}

void encerraUnidadeTempo(GerenciadorProcessos *gerenciador)
{
    gerenciador->tempo += 1;
}

/*------------------------------- Funçẽos que operam processos -------------------------------*/

void escalonaProcessosCPUs(GerenciadorProcessos *gerenciador)
{
    verificaBloqueados(gerenciador);

    for (int i = 0; i < gerenciador->numCPUs; i++)
    {
        if (cpuLivre(gerenciador->cpus[i]) == 1)
        {
            if (filaVazia(gerenciador->estadoProntoFS) == 0)
            {
                escalonaProcesso(gerenciador->tabelaProcessos, gerenciador->cpus[i], gerenciador->estadoExecucao + i, gerenciador->estadoProntoFS);
            }
        }
    }
}

void escalonaProcesso(Lista *tabelaProcessos, CPU *cpu, int *estadoExecucao, TipoFila *estadoProntoFS)
{

    int pidProcesso = desenfileirar(estadoProntoFS)->pid;

    if (pidProcesso >= 0)
    {
        *estadoExecucao = pidProcesso;

        ProcessoSimulado *proximoProceso = buscaProcesso(tabelaProcessos, pidProcesso);

        proximoProceso->estado = EXECUCAO;

        carregaProcesso(cpu, proximoProceso);
    }
}

void executaCPUs(GerenciadorProcessos *gerenciador)
{
    for (int i = 0; i < gerenciador->numCPUs; i++)
    {
        // Se a CPU não esta livre, ou seja carregada com um processo, ela executa o próximo comando do processo dela
        if (!(cpuLivre(gerenciador->cpus[i])))
        {
            executaProxInstrucao(gerenciador->cpus[i], gerenciador->tempo, gerenciador->tabelaProcessos, &gerenciador->quantidadeProcessosIniciados, gerenciador->estadoProntoFS, gerenciador->estadoBloqueado);
        }
    }
}

void trocaDeContexto(GerenciadorProcessos *gerenciador)
{
    for (int i = 0; i < gerenciador->numCPUs; i++)
    {
        if (!(cpuLivre(gerenciador->cpus[i])))
        {
            removeProcessoCPU(gerenciador->cpus[i], gerenciador->tabelaProcessos, gerenciador->estadoProntoFS, gerenciador->quantum);
        }
    }
}

void removeProcessoCPU(CPU *cpu, Lista *tabelaProcessos, TipoFila* estadoProntoFS, int quantum)
{
    ProcessoSimulado *processoNaCPU = buscaProcesso(tabelaProcessos, *(cpu->pidProcessoAtual));

    if (processoNaCPU != NULL)
    {
        if (cpu->fatiaQuantum >= quantum) // Remove se o quantum executado for maior que o quantum maxim 
        {
            processoNaCPU->estado = PRONTO;

            processoNaCPU->tempoCPU += cpu->fatiaQuantum;

            Enfileira(processoNaCPU->pid, NUMVAZIO, estadoProntoFS);
            zeraCPU(cpu);
        }
        else if (processoNaCPU->estado == BLOQUEADO)
        {
            processoNaCPU->tempoCPU += cpu->fatiaQuantum;
            zeraCPU(cpu);

            if (*processoNaCPU->pc == NUMVAZIO)
            {
                removeTabela(tabelaProcessos, processoNaCPU->pid);
            }
        }
    }
}

void verificaBloqueados(GerenciadorProcessos *gerenciador)
{
    for (int i = 0; i < gerenciador->estadoBloqueado->Tamanho; i++)
    {
        PidTempo *pidTempo = desenfileirar(gerenciador->estadoBloqueado);

        pidTempo->tempoExecutado--;

        if (pidTempo->tempoExecutado <= 0)
        {
            ProcessoSimulado *processo = buscaProcesso(gerenciador->tabelaProcessos, pidTempo->pid);
            Enfileira(pidTempo->pid, NUMVAZIO, gerenciador->estadoProntoFS);
        }
        else
        {
            Enfileira(pidTempo->pid, pidTempo->tempoExecutado, gerenciador->estadoBloqueado);
        }
    }
}

void removeProcessoTabela(ProcessoSimulado *processoEscolhido, GerenciadorProcessos *gerenciador)
{
    gerenciador->tempoTotalExecucao += processoEscolhido->tempoCPU;
    removeTabela(gerenciador->tabelaProcessos, processoEscolhido->pid);
}

double calcPot(double base, int expoente)
{
    double resultado = 1.0;
    int i;

    for (i = 0; i < expoente; i++)
    {
        resultado *= base;
    }

    return resultado;
}
