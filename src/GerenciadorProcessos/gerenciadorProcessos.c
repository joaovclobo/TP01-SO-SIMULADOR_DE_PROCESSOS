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

    for (int  i = 0; i < gerenciador->numCPUs; i++){ printf("%d ", gerenciador->estadoExecucao[i]); }

    
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
        printf("\t\t TEMPO DO SISTEMA %d\n", gerenciador->tempo);

        if (gerenciador->tempo == 1)
        {   
            //Na primeira unidade de tempo do sistema, é iniciado e carregado o primeiro processo
            iniciaProcessoInit(gerenciador);

            escalonaProcessosCPUs(gerenciador, gerenciador->tempo);
            executaCPUs(gerenciador);
                
        } else
        {
            //TODO - ESC - Aqui terá uma função que seleciona os processos que estão com o estado PRONTO e os carrega na CPU; fazer funcao que seleciona processo da fila de pronto de acordo com o escalonamento
            //Usa a funcao carrega processo - Este código abaixo simula a troca de contexto; 
            // escalonaProcessosCPUs(gerenciador, gerenciador->tempo); //Esta será a função

            escalonaProcessosCPUs(gerenciador, gerenciador->tempo);
            
                // //TODO - DEL - Deletar esta função
                // if (gerenciador->tempo >= 8)
                // {
                //     carregaProcesso(gerenciador->cpus[1], buscaProcesso(gerenciador->tabelaProcessos, 1));
                //     carregaProcesso(gerenciador->cpus[2], buscaProcesso(gerenciador->tabelaProcessos, 2));
                // }

            executaCPUs(gerenciador);
            //TODO - ESC aqui deve haver uma função que bloqueia os processos
        }
    }
}


void encerraUnidadeTempo(GerenciadorProcessos *gerenciador)
{
    gerenciador->tempo += 1;
}


/*------------------------------- Funçẽos que operam processos -------------------------------*/

void escalonaProcessosCPUs(GerenciadorProcessos* gerenciador, int escalonamento)
{
    for (int i = 0; i < gerenciador->numCPUs; i++)
    {
        //TODO - ESC - verifica se tem proccesos prontos para a execuçãp
        if (cpuLivre(gerenciador->cpus[i]))
        {
            escalonaProcesso(gerenciador->tabelaProcessos, gerenciador->cpus[i], gerenciador->estadoExecucao+i, escalonamento, i);
        }
    }

    printf("\n-----------> ESTADO EXECUÇÃO <-----------\n"); 
    for (int  i = 0; i < gerenciador->numCPUs; i++){ printf("%d ", gerenciador->estadoExecucao[i]); }
    putchar('\n');
    
}

//TODO - ESC - esta função receberá uma ou mais filas
void escalonaProcesso(Lista* tabelaProcessos, CPU* cpu, int* estadoExecucao, int escalonamento, int NUMcpu)
{
    int pid = pidProximoProcesso(escalonamento, estadoExecucao);

    ProcessoSimulado* proximoProceso = buscaProcesso(tabelaProcessos, pid);
    if(pid == NUMcpu) {carregaProcesso(cpu, proximoProceso);}
    // carregaProcesso(cpu, proximoProceso);
}

//TODO - ESC - função pidProximoProcesso vai ver o número da variável escalonamento e desinfileirar o processo da fila que for selecionda
//TODO - ESC - Talvez isto seja implementado na fila????
int pidProximoProcesso(int escalonamento, int* estadoExecucao)
{
    int pid = 0;        //Valor em pid será o valor do processo que será carregado na CPU
    
    //TODO - ESC - Variavel escalonamento está simulando o tempo do sistema
    switch (escalonamento)
    {
    case 1: pid = 0; break;
    case 7: pid = 1; break;
    case 8: pid = 2; break;
    case 9: pid = 3; break;
    default: break;
    }

    //     int numeroInst = 10;
    //     int numeroProcessos = 4;
    //     int pid = (escalonamento / numeroInst) % numeroProcessos;

    //TODO - ESC - apenas esta função que ficará aqui      
    // desenfileira(filaPronto);
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
            //TODO - Tirar este print e encontrar um jeito de mostrar o numero da CPU no momento que ela é exibida
            printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> CPU %d <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n", i);
            executaProxInstrucao(gerenciador->cpus[i], gerenciador->tempo, gerenciador->tabelaProcessos, &gerenciador->quantidadeProcessosIniciados);
        }
    }
}

void iniciaProcessoInit(GerenciadorProcessos* gerenciador)
{
    ProcessoSimulado* processoInit = criaProcessoInit(gerenciador->tempo);
    insereTabela(gerenciador->tabelaProcessos, processoInit);
    gerenciador->quantidadeProcessosIniciados+=1;
   
}

void removeProcessoTabela(ProcessoSimulado *processoEscolhido, GerenciadorProcessos *gerenciador) 
{
    gerenciador->tempoTotalExecucao += processoEscolhido->tempoCPU;
    removeTabela(gerenciador->tabelaProcessos, processoEscolhido->pid);
}
