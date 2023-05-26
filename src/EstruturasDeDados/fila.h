#include <stdio.h>
#include <stdlib.h>

typedef struct CelulaPidTempo* Ponteiro;

typedef struct PidTempo
{
    int pid;
    int tempoExecutado;
}PidTempo;

typedef struct CelulaPidTempo 
{
    PidTempo pidTempo;
    Ponteiro Prox;
}CelulaPidTempo;

typedef struct TipoFila
{
    Ponteiro Frente, Tras;
    int Tamanho;
}TipoFila;

TipoFila* criaFila();

int filaVazia(TipoFila* Fila);
int filasVazias(TipoFila** filas, int numFilas);

void enfileira(int pid, int tempoExecutado, TipoFila *Fila);

PidTempo* desenfileirar(TipoFila* fila);
int desenfileirarPID(TipoFila* fila);
int desenfileirarFilas(TipoFila** filas, int numFilas);

PidTempo criaCelulaPidTempo(int PID, int tempoExecutado);

void imprimeFila(TipoFila *fila);
void imprimeFilas(TipoFila** filas, int numFilas);
