#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct No
{
    int info;
    struct No *prox;
}No;

typedef struct Fila
{
    struct No *inicio;
    struct No *fim;
    int tamanho;
}Fila;

Fila *CriaFila();    

void DestroiFila(Fila *f); 
void Enfileira(Fila *f, int valor); 

int FilaVazia(Fila *f); 
int FilaCheia(Fila *f); 
int Desenfileira(Fila *f);     