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
    int Tamanho;
}TipoFila;

TipoFila* criaFila();
int filaVazia(TipoFila* Fila);
void Enfileira(int pid, int tempoExecutado, TipoFila *Fila);

int Desenfileirar(TipoFila* fila);
PidTempo criaCelulaPidTempo(int PID, int tempoExecutado);

void imprimeFila(TipoFila *fila);
void imprimeFilas(TipoFila** filas, int numFilas);
