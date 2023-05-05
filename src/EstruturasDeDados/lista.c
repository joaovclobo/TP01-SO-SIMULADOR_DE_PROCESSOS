#include "lista.h"

Lista* criaLista() {
    novaEntrada->inicio = (Celula*)malloc(sizeof(Celula));
    novaEntrada->fim = novaEntrada->inicio;
    novaEntrada->tamanho = 0;
    return novaEntrada;
}

void insereFim(Lista* lista, ProcessoSimulado processo) {
    Celula* novaEntrada = (Celula*)malloc(sizeof(Celula));
    novaEntrada->processo = processo;
    novaEntrada->proximo = NULL;
    if (lista->fim == NULL) {
        lista->inicio = novaEntrada;
        lista->fim = novaEntrada;
    } else {
        lista->fim->proximo = novaEntrada;
        lista->fim = novaEntrada;
    }
    lista->tamanho++;
}

void remove_inicio(Lista* lista) {
    if (lista->inicio != NULL) {
        Nodo* removido = lista->inicio;
        lista->inicio = lista->inicio->proximo;
        if (lista->inicio == NULL) {
            lista->fim = NULL;
        }
        free(removido);
        lista->tamanho--;
    }
}

void remove_fim(Lista* lista) {
    if (lista->fim != NULL) {
        Nodo* atual = lista->inicio;
        Nodo* anterior = NULL;
        while (atual->proximo != NULL) {
            anterior = atual;
            atual = atual->proximo;
        }
        if (anterior != NULL) {
            anterior->proximo = NULL;
        } else {
            lista->inicio = NULL;
        }
        free(atual);
        lista->fim = anterior;
        lista->tamanho--;
    }
}

int busca_elemento(Lista* lista, int dado) {
    Nodo* atual = lista->inicio;
    int posicao = 0;
    while (atual != NULL) {
        if (atual->dado == dado) {
            return posicao;
        }
        atual = atual->proximo;
        posicao
