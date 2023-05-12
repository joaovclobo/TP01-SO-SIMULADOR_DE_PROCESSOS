#include <stdio.h>
#include <stdlib.h>
//#include "../ProcessoSimulado/processoSimulado.h"
typedef struct PrioridadePid
{
    int prioridade;
    int pid;
}PrioridadePid;

typedef struct No
{
    PrioridadePid *prioridadePid;
    struct No *prox;
} No;

typedef struct Fila
{
    No *inicio;
    No *fim;
    int tamanho;
} Fila;

Fila *criaFila();
void destroiFila(Fila *f);
void enfileira(Fila *f, PrioridadePid *prioridaedPid);
void desenfileira(Fila *f);
int filaVazia(Fila *f);
int filaCheia(Fila *f);
void imprimeFila(Fila *fila);