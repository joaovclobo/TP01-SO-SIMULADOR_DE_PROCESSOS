#include "fila.h"

TipoFila* criaFila()
{
    TipoFila* fila = (TipoFila*) malloc(sizeof(TipoFila));
    
    fila->Frente = (Ponteiro) malloc(sizeof(Celula_str));
    fila->Tras = fila->Frente;
    fila->Frente->Prox = NULL;
    fila->Tamanho = 0;

    return fila;
} 

int filaVazia(TipoFila* Fila)
{   
    return (Fila->Tamanho == 0);
}

//Retorna 1 se todas as filas são vazias
int filasVazias(TipoFila** filas, int numFilas)
{
    for (int i = 0; i < numFilas; i++)
    {
        if (!filaVazia(filas[i]))
        {
            return 0;
        }
    }
    
    return 1;
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
    Fila->Tamanho++;
}

int desenfileirar(TipoFila* fila)
{
    if (filaVazia(fila)) {
        return -1;
    }

    int processoRemovido = fila->Frente->pidTempo.pid;
    Celula_str* celulaRemovida = fila->Frente;

    fila->Frente = fila->Frente->Prox;
    free(celulaRemovida);

    if (fila->Frente == NULL) {
        fila->Tras = NULL;
    }

    fila->Tamanho--;

    return processoRemovido;
}

int desenfileirarFilas(TipoFila** filas, int numFilas)
{
    int pidProcessoRemovido = -1, i = 0;

    while (pidProcessoRemovido == -1 && i < numFilas)
    {
        pidProcessoRemovido = desenfileirar(filas[i]);
        if (pidProcessoRemovido >= 0)
        {
            return pidProcessoRemovido;
        }else
        {
            i++;
        }
    }

    return pidProcessoRemovido;
}

PidTempo criaCelulaPidTempo(int PID, int tempoExecutado)
{
    PidTempo celula;
    celula.pid = PID;
    celula.tempoExecutado = tempoExecutado;
    return celula;
}

void imprimeFila(TipoFila *fila)
{
    if (filaVazia(fila))
    {
        printf("Fila Vazia!\n");

    } else
    {
        Celula_str *celula = fila->Frente;
        while (celula != NULL) {
            printf("\nPid: %d, Tempo: %d", celula->pidTempo.pid, celula->pidTempo.tempoExecutado);
            celula = celula->Prox;
        }

        putchar('\n');
    }
}

void imprimeFilas(TipoFila** filas, int numFilas)
{
    for (int i = 0; i < numFilas; i++)
    {
        TipoFila* fila = filas[i];

        printf("\nFila nº %d:", i);

        if (filaVazia(fila))
        {
            printf("\nFila Vazia!\n");

        } else
        {
            Celula_str *celula = fila->Frente;
            while (celula != NULL) {
                printf("\n   Pid: %d, Tempo: %d", celula->pidTempo.pid, celula->pidTempo.tempoExecutado);
                celula = celula->Prox;
            }
            putchar('\n');
        }
    }
}
