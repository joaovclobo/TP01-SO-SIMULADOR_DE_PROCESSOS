#include "gerenciadorProcessos.h"

GerenciadorProcessos* inicializaGerenciador(int numCPUs)
{
    GerenciadorProcessos *gerenciador = (GerenciadorProcessos*) malloc(sizeof(GerenciadorProcessos));

    gerenciador->tempo = 0;
    gerenciador->quantidadeProcessosIniciados = 0;
    gerenciador->tempoTotalExecucao = 0;

    gerenciador->numCPUs = numCPUs;

    gerenciador->cpus = (CPU**) malloc(numCPUs * sizeof(CPU*));
    gerenciador->estadoExecucao = (int*) malloc(numCPUs * sizeof(int));

    for (int i = 0; i < numCPUs; i++)
    {
        gerenciador->cpus[i] = inicializaCPU();
        gerenciador->estadoExecucao[i] = NUMVAZIO;
    }

    gerenciador->tabelaProcessos = criaLista();

    gerenciador->estadoPronto = (TipoFila**)malloc(sizeof(TipoFila*)*NUMCLASPRIORI);
  
    for (int i = 0; i < NUMCLASPRIORI; i++)
    {
        gerenciador->estadoPronto[i] = criaFila();
    }

    gerenciador->estadoBloqueado = criaFila();

    return gerenciador;
}


void gerenciadorProcessos(GerenciadorProcessos *gerenciador, char comando)
{
    int proxPid;
    if (comando == 'U')
    {
        encerraUnidadeTempo(gerenciador);

        if (gerenciador->tempo == 1)
        {   
            iniciaProcessoInit(gerenciador);    //Na primeira unidade de tempo do sistema, é iniciado e carregado o primeiro processo

            // proxPid = desenfileirarFilas(gerenciador->estadoPronto, NUMCLASPRIORI);
            // imprimeFilas(gerenciador->estadoPronto, NUMCLASPRIORI);
            // printf("TIROU O: %d\n", proxPid);

            // carregaProcesso(gerenciador->cpus[0], buscaProcesso(gerenciador->tabelaProcessos, proxPid));

            escalonaProcessosCPUs(gerenciador);

            executaCPUs(gerenciador);
            
            trocaDeContexto(gerenciador);

            //TODO - ESC aqui deve haver uma função que bloqueia/remove os processos
                
        } else
        {
            // proxPid = desenfileirarFilas(gerenciador->estadoPronto, NUMCLASPRIORI);
            // printf("TIROU O: %d\n", proxPid);

            // carregaProcesso(gerenciador->cpus[0], buscaProcesso(gerenciador->tabelaProcessos, proxPid));

            escalonaProcessosCPUs(gerenciador);
            
            executaCPUs(gerenciador);

            trocaDeContexto(gerenciador);

            //TODO - ESC aqui deve haver uma função que bloqueia/remove os processos
        }
    }
}

void encerraUnidadeTempo(GerenciadorProcessos *gerenciador)
{
    gerenciador->tempo += 1;
}

/*------------------------------- Funçẽos que operam processos -------------------------------*/

void escalonaProcessosCPUs(GerenciadorProcessos* gerenciador)
{
    int i = 0;
    // for (int i = 0; i < gerenciador->numCPUs; i++)
    // {
        // if (cpuLivre(gerenciador->cpus[i])
        // {
            escalonaProcesso(gerenciador->tabelaProcessos, gerenciador->cpus[i], gerenciador->estadoExecucao+i, gerenciador->estadoPronto, i);
        // }
    // }
}

void escalonaProcesso(Lista* tabelaProcessos, CPU* cpu, int* estadoExecucao, TipoFila** estadoPronto, int NUMcpu)   
{
    int pidProcesso = desenfileirarFilas(estadoPronto, NUMCLASPRIORI);
    printf("\n\tTIROU O: %d\n", pidProcesso);
    imprimeFilas(estadoPronto, NUMCLASPRIORI);

    if (pidProcesso >= 0)
    {
        *estadoExecucao = pidProcesso;

        ProcessoSimulado* proximoProceso = buscaProcesso(tabelaProcessos, pidProcesso);

        carregaProcesso(cpu, proximoProceso);
    }
}

void trocaDeContexto(GerenciadorProcessos* gerenciador)
{
    ProcessoSimulado* processoNaCPU = buscaProcesso(gerenciador->tabelaProcessos, *(gerenciador->cpus[0]->pidProcessoAtual));

    if (processoNaCPU->prioridade < NUMCLASPRIORI-1)
    {
        processoNaCPU->prioridade++;
    }

    Enfileira(processoNaCPU->pid, gerenciador->cpus[0]->fatiaQuantum, gerenciador->estadoPronto[processoNaCPU->prioridade]);
    printf("\n\tCOLOCOU O: %d\n", processoNaCPU->pid);
    imprimeFilas(gerenciador->estadoPronto, NUMCLASPRIORI);
}

void executaCPUs(GerenciadorProcessos* gerenciador)
{
    for (int i = 0; i < gerenciador->numCPUs; i++)
    {   
        //Se a CPU não esta livre, ou seja carregada com um processo, ela executa o próximo comando do processo dela
        if (!(cpuLivre(gerenciador->cpus[i])))
        {   
            executaProxInstrucao(gerenciador->cpus[i], gerenciador->tempo, gerenciador->tabelaProcessos, &gerenciador->quantidadeProcessosIniciados, gerenciador->estadoPronto);
        }
    }
}

void iniciaProcessoInit(GerenciadorProcessos* gerenciador)
{
    ProcessoSimulado* processoInit = criaProcessoInit(gerenciador->tempo);
    Enfileira(processoInit->pid, processoInit->tempoCPU, gerenciador->estadoPronto[0]);
    insereTabela(gerenciador->tabelaProcessos, processoInit);
    gerenciador->quantidadeProcessosIniciados+=1;
    
}

void removeProcessoTabela(ProcessoSimulado *processoEscolhido, GerenciadorProcessos *gerenciador)
{
    gerenciador->tempoTotalExecucao += processoEscolhido->tempoCPU;
    removeTabela(gerenciador->tabelaProcessos, processoEscolhido->pid);
}
