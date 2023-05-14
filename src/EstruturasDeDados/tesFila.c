#include "tesFila.h"

// TipoFila* InicializaFila(){
//     TipoFila* fila = (TipoFila*)malloc(sizeof(TipoFila));
//     printf("1-inicializou fila\n");
//     return fila;   
// }

void FFVazia(TipoFila* Fila)
{
    Fila->Frente = (Ponteiro) malloc(sizeof(Celula_str));
    Fila->Tras = Fila->Frente;
    Fila->Frente->Prox = NULL;
} 

int Vazia(TipoFila* Fila)
{
    return (Fila->Frente == Fila->Tras);
}

void Enfileira(int prioridade, int pid, int tempoExecutado, TipoFila *Fila)
{
    
    Fila->Tras->Prox = (Ponteiro) malloc(sizeof(Celula_str)); 
    Fila->Tras = Fila->Tras->Prox;
    
    Fila->Tras->prioridadePid.pid = pid;
    Fila->Tras->prioridadePid.prioridade = prioridade;
    Fila->Tras->prioridadePid.tempoExecutado = tempoExecutado;
    Fila->Tras->Prox = NULL;
    
    printf("2-inseriu na fila\n");
}


void Imprime(TipoFila Fila)
{
    printf("3-entrou imprimir fila\n");
    Ponteiro Aux;
    Aux = Fila.Frente->Prox;
    while (Aux != NULL)
    {
        printf("pid: %d\n", Aux->prioridadePid.pid);
        printf("prioridade: %d\n", Aux->prioridadePid.prioridade);
        printf("tempoExecutado: %d\n", Aux->prioridadePid.tempoExecutado);
        Aux = Aux->Prox;
    }
}

void enfileiraPorPrioridade(TipoFila *Fila, int prioridade, int pid, int tempoExecutado)
{
    printf("\n ENTROU NA ENFILEIRA PRIORIDADE \n");
    Celula_str *celula = (Ponteiro) malloc(sizeof(Celula_str));
    Fila->Tras = Fila->Tras->Prox; 
    Fila->Tras->prioridadePid.pid = pid;
    Fila->Tras->prioridadePid.prioridade = prioridade;
    Fila->Tras->prioridadePid.tempoExecutado = tempoExecutado;
    
    if(Fila->Frente == NULL)
    {
        Fila->Frente = (Ponteiro) malloc(sizeof(Celula_str));
        Fila->Tras = Fila->Tras->Prox; 
        Fila->Tras->prioridadePid.pid = pid;
        Fila->Tras->prioridadePid.prioridade = prioridade;
        Fila->Tras->prioridadePid.tempoExecutado = tempoExecutado;
    }
    else 
    {
    
        if (prioridade > Fila->Frente->prioridadePid.prioridade) 
        {
            celula->Prox = Fila->Frente;
            Fila->Frente = celula;
        }
        else
        {
            Celula_str *atual = Fila->Frente;

            while (atual->Prox != NULL && atual->Prox->prioridadePid.prioridade >= prioridade) {
                atual = atual->Prox;
            }

            celula->Prox = atual->Prox;
            atual->Prox = celula;
        }
    }
    //Fila->tamanho++;
}
