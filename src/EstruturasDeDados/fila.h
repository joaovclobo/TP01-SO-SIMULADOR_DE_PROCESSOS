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

// TipoFila* InicializaFila();

TipoFila* CriaFila();
int Vazia(TipoFila* Fila);
void Enfileira(int pid, int tempoExecutado, TipoFila *Fila);
void imprimeFila(TipoFila *fila);
int Desenfileirar(TipoFila* fila);
PidTempo criaCelulaPidTempo(int PID, int tempoExecutado);