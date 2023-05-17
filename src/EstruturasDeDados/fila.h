#include <stdio.h>
#include <stdlib.h>
//#include "../ProcessoSimulado/processoSimulado.h"

typedef struct Celula_str* Ponteiro;

typedef struct PidTempo
{
    int pid;
    int tempoExecutado;
}PidTempo;

typedef struct Celula_str 
{
    PidTempo pidTempo;
    Ponteiro Prox;
}Celula_str;

typedef struct TipoFila
{
    Ponteiro Frente, Tras;
}TipoFila;

// TipoFila* InicializaFila();

void FFVazia(TipoFila* Fila);
int Vazia(TipoFila* Fila);
void Enfileira(int pid, int tempoExecutado, TipoFila *Fila);
//void enfileiraPorPrioridade(TipoFila *Fila, int prioridade, int pid, int tempoExecutado);
void Imprime(TipoFila Fila);
void imprimeFila(TipoFila *fila);
PidTempo criaCelulaPidTempo(int PID, int tempoExecutado);
// typedef struct PrioridadePid
// {
//     int prioridade;
//     int pid;
//     int tempoExecutado;
// }PrioridadePid;

// typedef struct No
// {
//     PrioridadePid *prioridadePid;
//     struct No *prox;
// } No;

// typedef struct Fila
// {
//     No *inicio;
//     No *fim;
//     int tamanho;
// } Fila;

// Fila *criaFila();
// void destroiFila(Fila *f);
// PrioridadePid* criaCelulaPrioridadePid(int prioridade, int PID, int tempoExecutado);
// void enfileiraPrioridade(Fila *f, int prioridade, int PID, int tempoExecutado);
// void enfileira(Fila *f, int prioridade, int PID, int tempoExecutado);
// void desenfileira(Fila *f);
// int filaVazia(Fila *f);
// int filaCheia(Fila *f);