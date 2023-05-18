#include "fila.h"

void FFVazia(TipoFila* Fila)
{
    Fila->Frente = (Ponteiro) malloc(sizeof(Celula_str));
    Fila->Tras = Fila->Frente;
    Fila->Frente->Prox = NULL;
    Fila->Tamanho = 0;
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


// void Imprime(TipoFila Fila)
// {
//     printf("3-entrou imprimir fila\n");
//     Ponteiro Aux;
//     Aux = Fila.Frente->Prox;
//     while (Aux != NULL)
//     {
//         printf("pid: %d\n", Aux->pidTempo.pid);
//         printf("tempoExecutado: %d\n", Aux->pidTempo.tempoExecutado);
//         Aux = Aux->Prox;
//     }
// }

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
        printf("Pid: %d, Tempo: %d\n ", celula->pidTempo.pid, celula->pidTempo.tempoExecutado);
        celula = celula->Prox;
    }
}