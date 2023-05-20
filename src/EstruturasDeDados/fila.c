#include "fila.h"

TipoFila* CriaFila()
{
    TipoFila* fila = (TipoFila*) malloc(sizeof(TipoFila));
    
    fila->Frente = (Ponteiro) malloc(sizeof(Celula_str));
    fila->Tras = fila->Frente;
    fila->Frente->Prox = NULL;
    fila->Tamanho = 0;

    return fila;
} 

int Vazia(TipoFila* Fila)
{
    return (Fila->Frente == Fila->Tras);
}

void Enfileira(int pid, int tempoExecutado, TipoFila *Fila)
{
    if(Fila->Tamanho == 0)
    {
        Fila->Frente = (Ponteiro) malloc(sizeof(Celula_str)); 
        Fila->Tras = Fila->Frente; // Ajusta a atribuição de Fila->Tras para o primeiro elemento
        Fila->Tras->Prox = NULL;
        Fila->Frente->pidTempo = criaCelulaPidTempo(pid, tempoExecutado);
    }
    else
    {
        Fila->Tras->Prox = (Ponteiro) malloc(sizeof(Celula_str)); 
        Fila->Tras = Fila->Tras->Prox;
        Fila->Tras->Prox = NULL;
        Fila->Tras->pidTempo = criaCelulaPidTempo(pid, tempoExecutado);
    }
    Fila->Tamanho += 1;
}

int Desenfileirar(TipoFila* fila)
{
    if (Vazia(fila)) {
        printf("Erro: a fila está vazia\n");
        exit(1);
    }

    int processoRemovido = fila->Frente->pidTempo.pid;
    Celula_str* celulaRemovida = fila->Frente;

    fila->Frente = fila->Frente->Prox;
    free(celulaRemovida);

    if (fila->Frente == NULL) {
        fila->Tras = NULL;
    }

    return processoRemovido;
}
PidTempo criaCelulaPidTempo(int PID, int tempoExecutado)
{
    PidTempo celula;
    celula.pid = PID;
    celula.tempoExecutado = tempoExecutado;
    return celula;
}

void imprimeFila(TipoFila *fila) {
    Celula_str *celula = fila->Frente;
    while (celula != NULL) {
        printf("\nPid: %d, Tempo: %d", celula->pidTempo.pid, celula->pidTempo.tempoExecutado);
        celula = celula->Prox;
    }
}