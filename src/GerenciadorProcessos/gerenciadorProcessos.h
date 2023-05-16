#include "../Pipe/pipe.h"
#include "cpu.h"

typedef struct GerenciadorProcessos
{
    int tempo;
    //Estado pronto vai ser um array
    int estadoExecucao;
    int quantidadeProcessosIniciados;
    int tempoTotalExecucao;
    //TODO - MCPU - além do array de CPUs devemos criar uma variável nº de CPUs
    //TODO - MCPU - ela será inicializada com o gerenciador e o numero deverá ser passado por arg
        CPU* cpu;
        int numCPUs;
    Lista *tabelaProcessos;
    // TODO - ESC descomentar isto
        // Fila *estadoPronto;
        // Fila *estadoBloqueado;
} GerenciadorProcessos;

GerenciadorProcessos* inicializaGerenciador();
void gerenciadorProcessos(GerenciadorProcessos* gerenciador, char comando);
void encerraUnidadeTempo(GerenciadorProcessos *gerenciador);

/*------------------------------- Funçẽos que operam processos -------------------------------*/

void escalonaProcessos(GerenciadorProcessos* gerenciador, int escalonamento);

//TODO - ESC - esta função receberá uma ou mais filas
void escalonaProcessoI(Lista* tabelaProcessos, CPU* cpu, int* estadoExecucao, int escalonamento);
    
int pidProximoProcesso(int escalonamento, int* estadoExecucao);


void iniciaProcessoInit(GerenciadorProcessos* gerenciador);

void removeProcessoTabela(ProcessoSimulado *processoEscolhido, GerenciadorProcessos *gerenciador);