#include "../Pipe/pipe.h"
#include "cpu.h"
#include <math.h>
#define NUMCLASPRIORI 4

typedef struct GerenciadorProcessos
{
    int tipoEscalonamento;
    int tempo;
    int* estadoExecucao;
    int quantidadeProcessosIniciados;
    int tempoTotalExecucao;
    CPU** cpus;
    int numCPUs;
    Lista *tabelaProcessos;
    TipoFila** estadoProntoPriori;
    TipoFila* estadoProntoFIFO;
    TipoFila* estadoBloqueado;
} GerenciadorProcessos;

GerenciadorProcessos* inicializaGerenciador(int numCPUs, int tipoEscalonamento);
void gerenciadorProcessos(GerenciadorProcessos* gerenciador, char comando);
void encerraUnidadeTempo(GerenciadorProcessos *gerenciador);

/*------------------------------- Funçẽos que operam processos -------------------------------*/

void escalonaProcessosCPUs(GerenciadorProcessos* gerenciador);

void escalonaProcesso(Lista* tabelaProcessos, CPU* cpu, int* estadoExecucao, TipoFila** estadoProntoPriori, TipoFila* estadoProntoFIFO, int tipoEscalonamento);
    
int pidProximoProcesso(int* estadoExecucao, TipoFila** estadoProntoPriori, TipoFila* estadoProntoFIFO, int tipoEscalonamento);

void executaCPUs(GerenciadorProcessos* gerenciador);

void iniciaProcessoInit(GerenciadorProcessos *gerenciador);

void trocaDeContexto(GerenciadorProcessos* gerenciador);

ProcessoSimulado* verificaCPU(Lista* tabelaProcessos, CPU* cpu);

void removeProcessoTabela(ProcessoSimulado *processoEscolhido, GerenciadorProcessos *gerenciador);


double calcularPotencia(double base, int expoente);
