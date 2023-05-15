#include <stdio.h>
#include <stdlib.h>
//#include "../ProcessoSimulado/processoSimulado.h"
typedef struct PrioridadePid
{
    int prioridade;
    int pid;
    int tempoExecutado;
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
PrioridadePid* criaCelulaPrioridadePid(int prioridade, int PID, int tempoExecutado);
void enfileiraPrioridade(Fila *f, int prioridade, int PID, int tempoExecutado);
void enfileira(Fila *f, int prioridade, int PID, int tempoExecutado);
void desenfileira(Fila *f);
int filaVazia(Fila *f);
int filaCheia(Fila *f);
void imprimeFila(Fila *fila);