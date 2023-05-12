#include "fila.h"

Fila* criaFila()
{
    Fila *f = (Fila*) malloc(sizeof(Fila));
    if (f == NULL)
    {
        printf("Erro: nao foi possivel alocar memoria.\n");
        exit(1);
    }
    f->inicio = NULL;
    f->fim = NULL;
    f->tamanho = 0;
    return f;
}

void destroiFila(Fila *f)
{
    No *aux = f->inicio;
    while (aux != NULL)
    {
        No *tmp = aux->prox;
        free(aux);
        aux = tmp;
    }
    free(f);
}

void enfileira(Fila *f, PrioridadePid *prioridadePid)
{
    No *novoNo = (No*) malloc(sizeof(No));
    if (prioridadePid->prioridade > f->inicio->prioridadePid->prioridade) 
    {
        novoNo->prox = f->inicio;
        f->inicio = novoNo;
    }
    else {
        No *atual = f->inicio;

        while (atual->prox != NULL && atual->prox->prioridadePid->prioridade >= prioridadePid->prioridade) {
            atual = atual->prox;
        }

        novoNo->prox = atual->prox;
        atual->prox = novoNo;
    }
    f->tamanho++;
}

void desenfileira(Fila *f)
{
    if (f->inicio == NULL)
    {
        printf("Erro: fila vazia.\n");
        exit(1);
    }
    PrioridadePid *valor = f->inicio->prioridadePid;
    No *tmp = f->inicio;
    f->inicio = f->inicio->prox;
    if (f->inicio == NULL)
    {
        f->fim = NULL;
    }
    free(tmp);
    f->tamanho--;
}

int filaVazia(Fila *f)
{
    return (f->inicio == NULL);
}

int filaCheia(Fila *f)
{
    No *novoNo = (No*) malloc(sizeof(No));
    if (novoNo == NULL)
    {
        return 1;
    }
    free(novoNo);
    return 0;
}


void imprimeFila(Fila *fila) {
    No *no = fila->inicio;
    while (no != NULL) {
        printf("Pid: %d, Prioridade: %d\n ", no->prioridadePid->pid, no->prioridadePid->prioridade);
        no = no->prox;
    }
}