#include "fila.h"

TipoFila* criaFila()
{
    TipoFila* fila = (TipoFila*) malloc(sizeof(TipoFila));
    
    fila->Frente = (Ponteiro) malloc(sizeof(CelulaPidTempo));
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

void enfileira(int pid, int tempoExecutado, TipoFila *Fila)
{
    if(Fila->Tamanho == 0)
    {
        Fila->Frente = (Ponteiro) malloc(sizeof(CelulaPidTempo)); 
        Fila->Tras = Fila->Frente; // Ajusta a atribuição de Fila->Tras para o primeiro elemento
        Fila->Tras->Prox = NULL;
        Fila->Frente->pidTempo = criaCelulaPidTempo(pid, tempoExecutado);
    }
    else
    {
        Fila->Tras->Prox = (Ponteiro) malloc(sizeof(CelulaPidTempo)); 
        Fila->Tras = Fila->Tras->Prox;
        Fila->Tras->Prox = NULL;
        Fila->Tras->pidTempo = criaCelulaPidTempo(pid, tempoExecutado);
    }
    Fila->Tamanho++;
}

PidTempo* desenfileirar(TipoFila* fila)
{
    if (filaVazia(fila)) {
        return NULL;
    }

    PidTempo* pidTempoRemovido = (PidTempo*) malloc(sizeof(PidTempo));

    pidTempoRemovido->pid = fila->Frente->pidTempo.pid;
    pidTempoRemovido->tempoExecutado = fila->Frente->pidTempo.tempoExecutado;
    CelulaPidTempo* celulaRemovida = fila->Frente;

    fila->Frente = fila->Frente->Prox;
    free(celulaRemovida);

    if (fila->Frente == NULL) {
        fila->Tras = NULL;
    }

    fila->Tamanho--;

    return pidTempoRemovido;
}

int desenfileirarPID(TipoFila* fila)
{
    if (filaVazia(fila)) {
        return -1;
    }

    int processoRemovido = fila->Frente->pidTempo.pid;
    CelulaPidTempo* celulaRemovida = fila->Frente;

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
        pidProcessoRemovido = desenfileirarPID(filas[i]);
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
        printf("   Fila Vazia!\n");

    } else
    {
        CelulaPidTempo *celula = fila->Frente;
        while (celula != NULL) {
            if (celula->pidTempo.tempoExecutado == -1)
            {
                printf("\n   Pid: %d", celula->pidTempo.pid);
            }else
            {
                printf("\n   Pid: %d, Tempo bloqueado: %d", celula->pidTempo.pid, celula->pidTempo.tempoExecutado);
            }
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
            printf("\n   Fila Vazia!\n");

        } else
        {
            CelulaPidTempo *celula = fila->Frente;
            while (celula != NULL) {
                if (celula->pidTempo.tempoExecutado == -1)
                {
                    printf("\n   Pid: %d", celula->pidTempo.pid);
                }else
                {
                    printf("\n   Pid: %d, Tempo bloqueado: %d", celula->pidTempo.pid, celula->pidTempo.tempoExecutado);
                }
                
                celula = celula->Prox;
            }
            putchar('\n');
        }
    }
}
