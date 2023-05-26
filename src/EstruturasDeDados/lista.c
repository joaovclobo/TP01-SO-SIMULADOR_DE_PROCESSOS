#include "lista.h"

Lista* criaLista()
{
    Lista* lista = (Lista*) malloc(sizeof(Lista));

    lista->inicio = (Celula*) malloc (sizeof (Celula));
    lista->fim = lista->inicio;
    lista->inicio->proximo = NULL;

    return lista;

}

int listaVazia(Lista* lista)
{
    return (lista->inicio == lista->fim);
}

void insereTabela(Lista* lista, ProcessoSimulado* processo)
{
    lista->fim->proximo = (Celula*) malloc(sizeof(Celula));
    lista->fim = lista->fim->proximo;
    lista->fim->processo = processo;
    lista->fim->proximo = NULL;
}

ProcessoSimulado* buscaProcesso(Lista* lista, int PID)
{
    Celula* percorre;
    percorre = lista->inicio->proximo;
    while (percorre != NULL)
    {
        if(percorre->processo->pid == PID)
        {
            return percorre->processo;
        }
        percorre = percorre->proximo;
    }
    return NULL;
}

void removeTabela(Lista* lista, int PID) {
    if (listaVazia(lista)) {
        printf("Lista vazia. Nenhum processo para remover.\n");
        return;
    }

    Celula* anterior = lista->inicio;
    Celula* atual = lista->inicio->proximo;

    while (atual != NULL) {
        if (atual->processo->pid == PID) {
            anterior->proximo = atual->proximo;

            if (atual == lista->fim) {
                lista->fim = anterior;
            }

            free(atual);
            return;
        }

        anterior = atual;
        atual = atual->proximo;
    }

    printf("Processo com PID %d não encontrado na lista.\n", PID);
}


int maiorPIDTabela(Lista* lista)
{
    Celula* percorre;
    int maiorPID = 0;
    percorre = lista->inicio->proximo;
    while (percorre != NULL)
    {
        if(percorre->processo->pid >= maiorPID)
        {
            maiorPID = percorre->processo->pid;
        }
        percorre = percorre->proximo;
    }
    return maiorPID;
}

void imprimeTabela(Lista* lista)
{
    Celula* aux;
    aux = lista->inicio->proximo;
    while (aux != NULL)
    {
        imprimeProcesso(*(aux->processo), 1);
        aux = aux->proximo;
    }
}
