#include "fila.h"

Fila *CriaFila()
{
    Fila *f = (Fila *)malloc(sizeof(Fila));
    f->inicio = NULL;
    f->fim = NULL;
    f->tamanho = 0;
    return f;
}

void DestroiFila(Fila *f)
{
    while (f->inicio != NULL)
    {
        struct No *aux = f->inicio;
        f->inicio = f->inicio->prox;
        free(aux);
    }
    free(f);
}

int FilaVazia(Fila *f)
{
    return (f->inicio == NULL);
}

int FilaCheia(Fila *f)
{
    return 0; // Fila dinâmica nunca está cheia
}

void Enfileira(Fila *f, int valor)
{
    struct No *novo = (struct no *)malloc(sizeof(struct No));
    novo->info = valor;
    novo->prox = NULL;
    if (f->inicio == NULL)
    {
        f->inicio = novo;
    }
    else
    {
        f->fim->prox = novo;
    }
    f->fim = novo;
    f->tamanho++;
}

int Desenfileira(Fila *f)
{
    if (FilaVazia(f))
    {
        printf("Erro: fila vazia.\n");
        exit(1);
    }
    int valor = f->inicio->info;
    struct No *aux = f->inicio;
    f->inicio = f->inicio->prox;
    free(aux);
    f->tamanho--;
    return valor;
}
