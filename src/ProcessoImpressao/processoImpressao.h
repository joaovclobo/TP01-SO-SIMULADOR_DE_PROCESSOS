#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../GerenciadorProcessos/gerenciadorProcessos.h"

void menuImpressao(GerenciadorProcesso gerenciador, ProcessoSimulado processo);

void imprimirProcessoControle();

void imprimirGerenciadorProcessos(GerenciadorProcesso gerenciador);

void imprimirProcessoSimulado(ProcessoSimulado processo);

void imprimeInfosGeraisProcesso(ProcessoSimulado processo);

void imprimeVariaveisProcesso(int *arrVariaveis, int tamanho);

void imprimeEstadoProcesso(Estado estado);

int numeroVariaveisProcesso(Instrucao* arrPrograma);