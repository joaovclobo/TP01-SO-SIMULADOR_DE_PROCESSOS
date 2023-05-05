#include <stdio.h>
#include <stdlib.h>

typedef struct No
{
    int info;
    struct No *prox;
} No;

typedef struct Fila
{
    No *inicio;
    No *fim;
    int tamanho;
} Fila;

Fila *criaFila();
void destroiFila(Fila *f);
void enfileira(Fila *f, int valor);
void desenfileira(Fila *f);
int filaVazia(Fila *f);
int filaCheia(Fila *f);
void imprimeFila(Fila *fila);