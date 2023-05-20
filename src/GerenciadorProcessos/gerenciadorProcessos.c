#include "gerenciadorProcessos.h"

GerenciadorProcessos* inicializaGerenciador(int numCPUs, int tipoEscalonamento)
{
    GerenciadorProcessos *gerenciador = (GerenciadorProcessos*) malloc(sizeof(GerenciadorProcessos));
    //TODO - ESC - Decidir se o escalonamento ficará assim
    gerenciador->tipoEscalonamento = tipoEscalonamento;

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

    gerenciador->estadoProntoPriori = (TipoFila**)malloc(sizeof(TipoFila*)*NUMCLASPRIORI);
  
    if(tipoEscalonamento == 0)
    {
        for (int i = 0; i < NUMCLASPRIORI; i++)
        {
            gerenciador->estadoProntoPriori[i] = criaFila();
        }

    } else
    {
        gerenciador->estadoProntoFIFO = criaFila(); 
    }

    gerenciador->estadoBloqueado = criaFila();

    return gerenciador;
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
            printf("FLAG");
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
    for (int i = 0; i < gerenciador->numCPUs; i++)
    {
        if (cpuLivre(gerenciador->cpus[i]) && (filasVazias(gerenciador->estadoProntoPriori, NUMCLASPRIORI) == 0))
        {   
            escalonaProcesso(gerenciador->tabelaProcessos, gerenciador->cpus[i], gerenciador->estadoExecucao+i, 
                                gerenciador->estadoProntoPriori, gerenciador->estadoProntoFIFO, gerenciador->tipoEscalonamento);
        }
    }
}

void escalonaProcesso(Lista* tabelaProcessos, CPU* cpu, int* estadoExecucao,
                         TipoFila** estadoProntoPriori, TipoFila* estadoProntoFIFO, int tipoEscalonamento)
{
    int pid = pidProximoProcesso(estadoExecucao, estadoProntoPriori, estadoProntoFIFO, tipoEscalonamento);

    ProcessoSimulado* proximoProceso = buscaProcesso(tabelaProcessos, pid);

    carregaProcesso(cpu, proximoProceso);

    // imprimeCPU(*cpu);
            printf("flaG\n");

}

//TODO - ESC - função pidProximoProcesso vai ver o número da variável escalonamento e desinfileirar o processo da fila que for selecionda
//TODO - ESC - Talvez isto seja implementado na fila????
int pidProximoProcesso(int* estadoExecucao, TipoFila** estadoProntoPriori, TipoFila* estadoProntoFIFO, int tipoEscalonamento)
{
    int pid = 0;        //Valor em pid será     o valor do processo que será carregado na CPU
    
    if (tipoEscalonamento == 0)
    {
        for (int i = 0; i < NUMCLASPRIORI; i++)
        {   
            if (!Vazia(estadoProntoPriori[i]))
            {
                pid = Desenfileirar(estadoProntoPriori[i]);
            }
        }
    } else
    {
        pid = Desenfileirar(estadoProntoFIFO);
    }

    printf("Desenfilerou %d\n", pid);

    *estadoExecucao = pid;

    return pid;
}


void executaCPUs(GerenciadorProcessos* gerenciador)
{
    for (int i = 0; i < gerenciador->numCPUs; i++)
    {   
        //Se a CPU não esta livre, ou seja carregada com um processo, ela executa o próximo comando do processo dela
        if (!(cpuLivre(gerenciador->cpus[i])))
        {   
            executaProxInstrucao(gerenciador->cpus[i], gerenciador->tempo, 
                gerenciador->tabelaProcessos, &gerenciador->quantidadeProcessosIniciados,
                     gerenciador->estadoProntoPriori, gerenciador->estadoProntoFIFO, gerenciador->tipoEscalonamento, gerenciador->estadoBloqueado);
        }
    }
}

void iniciaProcessoInit(GerenciadorProcessos* gerenciador)
{
    ProcessoSimulado* processoInit = criaProcessoInit(gerenciador->tempo);
    enfileraPronto(processoInit, gerenciador->estadoProntoPriori, gerenciador->estadoProntoFIFO, gerenciador->tipoEscalonamento);
    printf("Enfilerou %d\n", processoInit->pid);
    insereTabela(gerenciador->tabelaProcessos, processoInit);
    gerenciador->quantidadeProcessosIniciados+=1;
    
}

void trocaDeContexto(GerenciadorProcessos* gerenciador)
{
    printf("Quall seu problema amigo?\n");
    // for (int i = 0; i < gerenciador->numCPUs; i++)
    // {   
    //     printf("CPU %d, %d\n", i, cpuLivre(gerenciador->cpus[i]) == 0);
    //     // if (!(cpuLivre(gerenciador->cpus[i]) == 0))
    //     // {
    //     //     if (gerenciador->tipoEscalonamento == 0)
    //     //     {
    //     //         ProcessoSimulado* processo = verificaCPU(gerenciador->tabelaProcessos, gerenciador->cpus[i]);   
    //     //         enfileraPronto(processo, gerenciador->estadoProntoPriori, gerenciador->estadoProntoFIFO, gerenciador->tipoEscalonamento);
    //     //         printf("Enfilerou %d\n", processo->pid);
    //     //     } else
    //     //     {
    //     //         // TODO - 
    //     //     }
    //     // }
    // }   
}

ProcessoSimulado* verificaCPU(Lista* tabelaProcessos, CPU* cpu)
{
    ProcessoSimulado* processoDaCPU = buscaProcesso(tabelaProcessos, *cpu->pidProcessoAtual);

    if(cpu->fatiaQuantum >= calcularPotencia(2, processoDaCPU->prioridade))     //Tempo de cada classe é dado por 2^(Número da classe)
    {   
        if (processoDaCPU->prioridade < 3){
            processoDaCPU->prioridade++;
            
        }
        zeraCPU(cpu);
    }    

    return processoDaCPU;
}

void removeProcessoTabela(ProcessoSimulado *processoEscolhido, GerenciadorProcessos *gerenciador)
{
    gerenciador->tempoTotalExecucao += processoEscolhido->tempoCPU;
    removeTabela(gerenciador->tabelaProcessos, processoEscolhido->pid);
}


double calcularPotencia(double base, int expoente)
{
    double resultado = 1.0;
    int i;

    for (i = 0; i < expoente; i++) {
        resultado *= base;
    }

    return resultado;
}
