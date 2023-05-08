#include "../Pipe/pipe.h"
#include "cpu.h"

typedef struct GerenciadorProcesso
{
    int tempo;
    int estadoExecucao;
    int quantidadeProcessosExecutados;
    int tempoTotalExecucao;
    CPU* cpu;
    Lista *tabelaProcessos;
    Fila *estadoPronto;
    Fila *estadoBloqueado;
} GerenciadorProcesso;

GerenciadorProcesso* inicializaGerenciador();

void gerenciadorProcessos(GerenciadorProcesso *gerenciador, char comando);

void encerraUnidadeTempo(GerenciadorProcesso *gerenciador);

void removeProcessoTabela(ProcessoSimulado *processoEscolhido, GerenciadorProcesso *gerenciador);

void insereProcessoTabela(ProcessoSimulado *processoEscolhido, GerenciadorProcesso *gerenciador);

void imprimeTabelaProcesso(Lista *tabelaProcesso);

int criaPID(GerenciadorProcesso *gerenciador);