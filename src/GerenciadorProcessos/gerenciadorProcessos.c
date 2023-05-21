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

void iniciaProcessoInit(GerenciadorProcessos* gerenciador)
{
    ProcessoSimulado* processoInit = criaProcessoInit(gerenciador->tempo);
    Enfileira(processoInit->pid, processoInit->tempoCPU, gerenciador->estadoPronto[0]);
    insereTabela(gerenciador->tabelaProcessos, processoInit);
    gerenciador->quantidadeProcessosIniciados+=1;
    
}

void gerenciadorProcessos(GerenciadorProcessos *gerenciador, char comando)
{
    if (comando == 'U')
    {
        encerraUnidadeTempo(gerenciador);

        if (gerenciador->tempo == 1)
        {   
            iniciaProcessoInit(gerenciador);    //Na primeira unidade de tempo do sistema, é iniciado e carregado o primeiro processo

            escalonaProcessosCPUs(gerenciador); 

            executaCPUs(gerenciador);
            
            trocaDeContexto(gerenciador);

        } else
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

void escalonaProcessosCPUs(GerenciadorProcessos* gerenciador)
{
    for (int i = 0; i < gerenciador->numCPUs; i++)
    {
        if (cpuLivre(gerenciador->cpus[i]) == 1)
        {
            if (filasVazias(gerenciador->estadoPronto, NUMCLASPRIORI) == 0)
            {
                escalonaProcesso(gerenciador->tabelaProcessos, gerenciador->cpus[i], gerenciador->estadoExecucao+i, gerenciador->estadoPronto, i);
            }
        }
    }
        printf("\t\tDepois de escalonado:\n"); imprimeCPUs_2(gerenciador); 
}

void escalonaProcesso(Lista* tabelaProcessos, CPU* cpu, int* estadoExecucao, TipoFila** estadoPronto, int NUMcpu)   
{
        imprimeFilas(estadoPronto, NUMCLASPRIORI);

    int pidProcesso = desenfileirarFilas(estadoPronto, NUMCLASPRIORI);

    if (pidProcesso >= 0)
    {
        *estadoExecucao = pidProcesso;

        ProcessoSimulado* proximoProceso = buscaProcesso(tabelaProcessos, pidProcesso);

        carregaProcesso(cpu, proximoProceso);
    }
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
        printf("\t\tDepois de EXECUTADO:\n"); imprimeCPUs_2(gerenciador); 

}

void trocaDeContexto(GerenciadorProcessos* gerenciador)
{
    for (int i = 0; i < gerenciador->numCPUs; i++)
    {
        if (!(cpuLivre(gerenciador->cpus[i])))
        {
            removeProcessoCPU(gerenciador->cpus[i], gerenciador->tabelaProcessos, gerenciador->estadoPronto);
        }
    }
        imprimeFilas(gerenciador->estadoPronto, NUMCLASPRIORI);

        printf("\t\tDepois da TROCA DE CONTEXTO:\n"); imprimeCPUs_2(gerenciador); 
}

void removeProcessoCPU(CPU* cpu, Lista* tabelaProcessos, TipoFila** estadoPronto)
{
    ProcessoSimulado* processoNaCPU = buscaProcesso(tabelaProcessos, *(cpu->pidProcessoAtual));

    if (cpu->fatiaQuantum >= calcPot(2, processoNaCPU->prioridade)) //Remove se o quantum for maior q o permitido pra classe
    {
        processoNaCPU->estado = PRONTO;

        if (processoNaCPU->prioridade < NUMCLASPRIORI-1)
        {
            processoNaCPU->prioridade++;
        }
        processoNaCPU->tempoCPU += cpu->fatiaQuantum;

        Enfileira(processoNaCPU->pid, processoNaCPU->tempoCPU, estadoPronto[processoNaCPU->prioridade]);
        zeraCPU(cpu);
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

        for (i = 0; i < expoente; i++) {
            resultado *= base;
        }

        return resultado;
    }

    void imprimeCPUs_2(GerenciadorProcessos *gerenciador)
    {
        for (int i = 0; i < gerenciador->numCPUs; i++)
        {
            printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> CPU %d <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n", i);
            if (cpuLivre(gerenciador->cpus[i]))
            {
                printf("\n->> CPU LIVRE\n");
            }
            else
            {
                imprimeCPU_2(gerenciador->cpus[i]);
            }
        }
    }
