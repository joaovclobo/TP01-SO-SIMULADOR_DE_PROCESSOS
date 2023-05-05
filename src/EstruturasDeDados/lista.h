#include <stdio.h>
#include <stdlib.h>
#include "../ProcessoSimulado/processoSimulado.h"

typedef struct Celula {
    ProcessoSimulado* processo;
    struct Celula* prox;
} Celula;

typedef struct Lista {
    Celula* inicio;
    Celula* fim;
    int tamanho;
} Lista;

Lista* criaLista();
void destroi_lista(Lista* lista);
void insere_inicio(Lista* lista, int dado);
void insereFim(Lista* lista, int dado);
void remove_inicio(Lista* lista);
void remove_fim(Lista* lista);
int busca_elemento(Lista* lista, int dado);
void imprime_lista(Lista* lista);