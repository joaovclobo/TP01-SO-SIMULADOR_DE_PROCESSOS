#include "../Pipe/pipe.h"
#include "cpu.h"
#include <math.h>
#define NUMCLASPRIORI 4

typedef struct GerenciadorProcessos
{
    int tempo;
    int* estadoExecucao;
    int quantidadeProcessosIniciados;
    int tempoTotalExecucao;
    CPU** cpus;
    int numCPUs;
    Lista *tabelaProcessos;
    TipoFila** estadoPronto;
    TipoFila* estadoBloqueado;
} GerenciadorProcessos;

GerenciadorProcessos* inicializaGerenciador(int numCPUs);
void gerenciadorProcessos(GerenciadorProcessos* gerenciador, char comando);
void encerraUnidadeTempo(GerenciadorProcessos *gerenciador);

/*------------------------------- Funçẽos que operam processos -------------------------------*/

void escalonaProcessosCPUs(GerenciadorProcessos* gerenciador);

void escalonaProcesso(Lista* tabelaProcessos, CPU* cpu, int* estadoExecucao, TipoFila** estadoPronto, int NUMcpu);
    
int pidProximoProcesso(int escalonamento, int* estadoExecucao);

void executaCPUs(GerenciadorProcessos* gerenciador);

void trocaDeContexto(GerenciadorProcessos* gerenciador);

void iniciaProcessoInit(GerenciadorProcessos *gerenciador);

void removeProcessoTabela(ProcessoSimulado *processoEscolhido, GerenciadorProcessos *gerenciador);

void imprimeCPUs_2(GerenciadorProcessos *gerenciador);
