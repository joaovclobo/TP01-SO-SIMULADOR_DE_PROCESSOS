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

    //TODO - Dependem da quantidade de CPUs

    gerenciador->cpus = (CPU**) malloc(numCPUs * sizeof(CPU*));
    
    for (int i = 0; i < numCPUs; i++)
    {
        gerenciador->cpus[i] = inicializaCPU();
    }
    
    //TODO - DEL - apagar
        gerenciador->cpu = inicializaCPU();

        gerenciador->estadoExecucao = NUMVAZIO;
  
    gerenciador->tabelaProcessos = criaLista();
  
    // TODO - ESC descomentar isto
        // gerenciador->estadoPronto = criaFila();
        // gerenciador->estadoBloqueado = criaFila();

    return gerenciador;
}

void gerenciadorProcessos(GerenciadorProcessos *gerenciador, char comando)
{
    
    if (comando == 'U')
    {
        encerraUnidadeTempo(gerenciador);

        if (gerenciador->tempo == 1)
        {   
            //Na primeira unidade de tempo do sistema, é iniciado e carregado o primeiro processo
            iniciaProcessoInit(gerenciador);

            escalonaProcessos(gerenciador, gerenciador->tempo);
            executaProxInstrucao(gerenciador->cpu, gerenciador->tempo, gerenciador->tabelaProcessos, &gerenciador->quantidadeProcessosIniciados);
                
        } else
        {
            //TODO - ESC - Aqui terá uma função que seleciona os processos que estão com o estado PRONTO e os carrega na CPU; fazer funcao que seleciona processo da fila de pronto de acordo com o escalonamento
            //Usa a funcao carrega processo - Este código abaixo simula a troca de contexto; 
            // escalonaProcessos(gerenciador, gerenciador->tempo); //Esta será a função

            // TODO - MCPUs - Esta função irá receber apenas o gerenciador; TODO - MCPUs - Esta função deverá executar o proximo comando em todas as CPUs

            escalonaProcessos(gerenciador, gerenciador->tempo);
            executaProxInstrucao(gerenciador->cpu, gerenciador->tempo, gerenciador->tabelaProcessos, &gerenciador->quantidadeProcessosIniciados);

            //TODO - ESC aqui deve haver uma função que bloqueia os processos
            
            //TODO - DEL - Deletar esta função
            printf("\t\t TEMPO DO SISTEMA %d\n", gerenciador->tempo);
            printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> CPU 0 <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
            imprimeCPU(*gerenciador->cpu);

                if (gerenciador->tempo >= 8)
                {
                    carregaProcesso(gerenciador->cpus[0], buscaProcesso(gerenciador->tabelaProcessos, 1));
                    carregaProcesso(gerenciador->cpus[1], buscaProcesso(gerenciador->tabelaProcessos, 2));

                    executaProxInstrucao(gerenciador->cpus[0], gerenciador->tempo, gerenciador->tabelaProcessos, &gerenciador->quantidadeProcessosIniciados);
                    executaProxInstrucao(gerenciador->cpus[1], gerenciador->tempo, gerenciador->tabelaProcessos, &gerenciador->quantidadeProcessosIniciados);


                    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> CPU 1 <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
                    imprimeCPU(*gerenciador->cpus[0]);
                    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> CPU 2 <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
                    imprimeCPU(*gerenciador->cpus[1]);
                }
        }
    }
}


void encerraUnidadeTempo(GerenciadorProcessos *gerenciador)
{
    gerenciador->tempo += 1;
}


/*------------------------------- Funçẽos que operam processos -------------------------------*/

void escalonaProcessos(GerenciadorProcessos* gerenciador, int escalonamento)
{
    // for (int i = 0; i < gerenciador->numCPUs; i++)
    // {
        //TODO - MCPU - Ao invés de cpu vai ser cpu[i] ou algo do tipo
        escalonaProcessoI(gerenciador->tabelaProcessos, gerenciador->cpu, &gerenciador->estadoExecucao, escalonamento);
    // }
}

//TODO - ESC - esta função receberá uma ou mais filas
void escalonaProcessoI(Lista* tabelaProcessos, CPU* cpu, int* estadoExecucao, int escalonamento)
{
    //TODO - ESC - função pidProximoProcesso vai ver o número da variável escalonamento e desinfileirar o processo da fila que for selecionda
    int pidProxProcesso = pidProximoProcesso(escalonamento, estadoExecucao);

    ProcessoSimulado* proximoProceso = buscaProcesso(tabelaProcessos, pidProxProcesso);
    carregaProcesso(cpu, proximoProceso);
    
}

//TODO - ESC - Talvez isto seja implementado na fila????
int pidProximoProcesso(int escalonamento, int* estadoExecucao)
{
        int numeroInst = 10;
        int numeroProcessos = 4;
    //TODO - ESC - Variavel escalonamento está simulando o tempo do sistema
        int pid = (escalonamento / numeroInst) % numeroProcessos;

    //TODO - ESC - esta será a função que ficará aqui,         
    // desenfileira(filaPronto);
    *estadoExecucao = pid;

    //TODO - ESC - Valor em pid será o valor do processo que será carregado na CPU
    return pid;
}


void iniciaProcessoInit(GerenciadorProcessos* gerenciador)
{
    ProcessoSimulado* processoInit = criaProcessoInit(gerenciador->tempo);
    //TODO - ESC - o carregaProcesso vai ser subistuído por uma função que irá enfilerar o processo Init na fila de PRONTO
        // carregaProcesso(gerenciador->cpu, processoInit);
    insereTabela(gerenciador->tabelaProcessos, processoInit);
    gerenciador->quantidadeProcessosIniciados+=1;

    //TODO - DEL - Depois temos que deletar isso
        imprimeTabela(gerenciador->tabelaProcessos);
    
}

void removeProcessoTabela(ProcessoSimulado *processoEscolhido, GerenciadorProcessos *gerenciador) 
{
    gerenciador->tempoTotalExecucao += processoEscolhido->tempoCPU;
    removeTabela(gerenciador->tabelaProcessos, processoEscolhido->pid);
}
