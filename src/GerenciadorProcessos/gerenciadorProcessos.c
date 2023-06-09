#include "gerenciadorProcessos.h"

GerenciadorProcessos *inicializaGerenciador(int numCPUs)
{
    GerenciadorProcessos *gerenciador = (GerenciadorProcessos *)malloc(sizeof(GerenciadorProcessos));

    gerenciador->tempo = 0;
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

    gerenciador->estadoPronto = (TipoFila **)malloc(sizeof(TipoFila *) * NUMCLASPRIORI);

    for (int i = 0; i < NUMCLASPRIORI; i++)
    {
        gerenciador->estadoPronto[i] = criaFila();
    }

    gerenciador->estadoBloqueado = criaFila();

    return gerenciador;
}

void iniciaProcessoInit(GerenciadorProcessos *gerenciador)
{
    ProcessoSimulado *processoInit = criaProcessoInit(gerenciador->tempo);
    enfileira(processoInit->pid, NUMVAZIO, gerenciador->estadoPronto[0]);
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
            if (filasVazias(gerenciador->estadoPronto, NUMCLASPRIORI) == 0)
            {
                escalonaProcesso(gerenciador->tabelaProcessos, gerenciador->cpus[i], gerenciador->estadoExecucao + i, gerenciador->estadoPronto);
            }
        }
    }
}

void escalonaProcesso(Lista *tabelaProcessos, CPU *cpu, int *estadoExecucao, TipoFila **estadoPronto)
{

    int pidProcesso = desenfileirarFilas(estadoPronto, NUMCLASPRIORI);

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
            executaProxInstrucao(gerenciador->cpus[i], gerenciador->tempo, gerenciador->tabelaProcessos, &gerenciador->quantidadeProcessosIniciados, gerenciador->estadoPronto, gerenciador->estadoBloqueado);
        }
    }
}

void trocaDeContexto(GerenciadorProcessos *gerenciador)
{
    for (int i = 0; i < gerenciador->numCPUs; i++)
    {
        if (!(cpuLivre(gerenciador->cpus[i])))
        {
            removeProcessoCPU(gerenciador->cpus[i], gerenciador->tabelaProcessos, gerenciador->estadoPronto);
        }
    }
}

void removeProcessoCPU(CPU *cpu, Lista *tabelaProcessos, TipoFila **estadoPronto)
{
    ProcessoSimulado *processoNaCPU = buscaProcesso(tabelaProcessos, *(cpu->pidProcessoAtual));

    if (processoNaCPU != NULL)
    {
        if (cpu->fatiaQuantum >= calcPot(2, processoNaCPU->prioridade)) // Remove se o quantum for maior q o permitido pra classe
        {
            processoNaCPU->estado = PRONTO;

            if (processoNaCPU->prioridade < NUMCLASPRIORI - 1)
            {
                processoNaCPU->prioridade++;
            }
            processoNaCPU->tempoCPU += cpu->fatiaQuantum;

            enfileira(processoNaCPU->pid, NUMVAZIO, estadoPronto[processoNaCPU->prioridade]);
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
            enfileira(pidTempo->pid, NUMVAZIO, gerenciador->estadoPronto[processo->prioridade]);
        }
        else
        {
            enfileira(pidTempo->pid, pidTempo->tempoExecutado, gerenciador->estadoBloqueado);
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
