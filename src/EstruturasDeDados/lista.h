#include <stdio.h>
#include <stdlib.h>
#include "../ProcessoSimulado/processoSimulado.h"

typedef struct celula_str Celula;
struct celula_str {
    ProcessoSimulado* processo;
    Celula* proximo;
};

typedef struct tipolista {
    Celula* inicio;
    Celula* fim;
} Lista;

Lista* criaLista();
int listaVazia(Lista* lista);

void insereTabela(Lista* lista, ProcessoSimulado* processo);
void removeTabela(Lista* lista, int PID);
ProcessoSimulado* buscaProcesso(Lista* lista, int PID);

int maiorPIDTabela(Lista* lista);

void imprimeTabela(Lista* lista);
