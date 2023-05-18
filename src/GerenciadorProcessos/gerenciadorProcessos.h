#include "../Pipe/pipe.h"
#include "cpu.h"

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
    // TODO - ESC descomentar isto
    TipoFila *estadoPronto;
    TipoFila *estadoBloqueado;
} GerenciadorProcessos;

GerenciadorProcessos* inicializaGerenciador(int numCPUs, int tipoEscalonamento);
void gerenciadorProcessos(GerenciadorProcessos* gerenciador, char comando);
void encerraUnidadeTempo(GerenciadorProcessos *gerenciador);

/*------------------------------- Funçẽos que operam processos -------------------------------*/

void escalonaProcessosCPUs(GerenciadorProcessos* gerenciador, int escalonamento);

void escalonaProcesso(Lista* tabelaProcessos, CPU* cpu, int* estadoExecucao, int escalonamento, int NUMcpu);
    
int pidProximoProcesso(int escalonamento, int* estadoExecucao);

void executaCPUs(GerenciadorProcessos* gerenciador);

void iniciaProcessoInit(GerenciadorProcessos *gerenciador);

void removeProcessoTabela(ProcessoSimulado *processoEscolhido, GerenciadorProcessos *gerenciador);