#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../GerenciadorProcessos/gerenciadorProcessosFS.h"

int menuImpressao();

int numeroVariaveisProcesso(Instrucao *arrPrograma);

void impressaoArquivo(GerenciadorProcessos *gerenciador);

void imprimirEstadoAtualSistema(GerenciadorProcessos *gerenciador);

void imprimirGerenciadorProcessos(GerenciadorProcessos *gerenciador);

void imprimeInfosGeraisProcesso(ProcessoSimulado *processo);

void imprimeVariaveisProcesso(int *arrVariaveis, int tamanho);

void imprimeEstadoProcesso(Estado estado);

void imprimeCPUs(GerenciadorProcessos *gerenciador);

void imprimeCPU(CPU *cpu);

void imprimeTabelaProcessos(GerenciadorProcessos *gerenciador);