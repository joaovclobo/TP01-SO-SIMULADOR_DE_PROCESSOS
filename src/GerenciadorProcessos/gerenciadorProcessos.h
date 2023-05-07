#include "../Pipe/pipe.h"
#include "../EstruturasDeDados/fila.h"
#include "../EstruturasDeDados/lista.h"
#include "cpu.h"

typedef struct GerenciadorProcesso
{
    int tempo;
    int estadoExecucao;
    int quantidadeProcessosExecutados;
    int tempoTotalExecucao;
    CPU cpu;
    Lista *tabelaProcessos;
    Fila *estadoPronto;
    Fila *estadoBloqueado;
} GerenciadorProcesso;

void inicializaGerenciador(GerenciadorProcesso *gerenciador);

void gerenciadorProcessos(GerenciadorProcesso *gerenciador, char comando);

void encerraUnidadeTempo(GerenciadorProcesso *gerenciador);

void gerenciaTabelaProcessos(GerenciadorProcesso *gerenciador, ProcessoSimulado *processo, int opcao);