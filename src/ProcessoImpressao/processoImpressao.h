#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../GerenciadorProcessos/gerenciadorProcessos.h"

int menuImpressao();

int numeroVariaveisProcesso(Instrucao* arrPrograma);

void imprimirGerenciadorProcessos(GerenciadorProcessos *gerenciador);

void imprimirProcessoSimulado(GerenciadorProcessos *gerenciador);

void imprimeInfosGeraisProcesso(ProcessoSimulado *processo);

void imprimeVariaveisProcesso(int *arrVariaveis, int tamanho);

void imprimeEstadoProcesso(Estado estado);

void imprimirFila(TipoFila *fila);