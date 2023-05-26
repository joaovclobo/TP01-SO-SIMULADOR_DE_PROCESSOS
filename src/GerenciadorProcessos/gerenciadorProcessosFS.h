#include "../Pipe/pipe.h"
#include "cpuFS.h"
#include <math.h>
#define NUMCLASPRIORI 4

typedef struct GerenciadorProcessos
{
    int tempo;
    int quantum;
    int* estadoExecucao;
    int quantidadeProcessosIniciados;
    int tempoTotalExecucao;
    CPU** cpus;
    int numCPUs;
    Lista *tabelaProcessos;
    TipoFila* estadoProntoFS;
    TipoFila* estadoBloqueado;
} GerenciadorProcessos;

GerenciadorProcessos* inicializaGerenciador(int numCPUs, int quantum);
void iniciaProcessoInit(GerenciadorProcessos *gerenciador);
void gerenciadorProcessos(GerenciadorProcessos* gerenciador, char comando);
void encerraUnidadeTempo(GerenciadorProcessos *gerenciador);

/*------------------------------- Funçẽos que operam processos -------------------------------*/

void escalonaProcessosCPUs(GerenciadorProcessos* gerenciador);

void escalonaProcesso(Lista* tabelaProcessos, CPU* cpu, int* estadoExecucao, TipoFila* estadoProntoFS);
    
int pidProximoProcesso(int escalonamento, int* estadoExecucao);

void executaCPUs(GerenciadorProcessos* gerenciador);

void trocaDeContexto(GerenciadorProcessos* gerenciador);

void removeProcessoCPU(CPU *cpu, Lista *tabelaProcessos, TipoFila* estadoProntoFS, int quantum);

void verificaBloqueados(GerenciadorProcessos* gerenciador);

void iniciaProcessoInit(GerenciadorProcessos *gerenciador);

void removeProcessoTabela(ProcessoSimulado *processoEscolhido, GerenciadorProcessos *gerenciador);

double calcPot(double base, int expoente);
