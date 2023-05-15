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

void removeTabela(Lista* lista, int PID)
{
    if (listaVazia(lista))
    {
        printf("Lista Vazia\n");
        return;
    }

    Celula *anterior = lista->inicio;
    Celula *percorre = lista->inicio->proximo;

    while (percorre != NULL)
    {
        if (percorre->processo->pid == PID)
        {
            anterior->proximo = percorre->proximo;

            if (percorre == lista->fim)
            {
                lista->fim = anterior;
            }

            free(percorre);
            return;
        }

        anterior = percorre;
        percorre = percorre->proximo;
    }

    printf("Processo com PID %d não encontrado na lista\n", PID);
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

// void imprimeTabelaProcesso(Lista *tabelaProcesso)
// {
//     //MUDAR PARA Celula *percorre = tabelaProcesso->inicio;
//     Celula *percorre = tabelaProcesso->inicio;
//     // printf("+-------+-------+------+------------+------------+--------+---------------+-----------+----------+\n");
//     // printf("| PID   | PPID  | PC   | Variaveis  | Prioridade | Estado | Tempo Inicial | Tempo CPU | Programa |\n");
//     // printf("+-------+-------+------+------------+------------+--------+---------------+-----------+----------+\n");
//     printf(">>>>>>>>>>>>> Tabela de processos: <<<<<<<<<<<<<<<<\n");
//     while(percorre != NULL)
//     {
//         //achar um jeito de printar arrays e estados
//         //Usar as funções imprime variaveis e imprime estados
//         ProcessoSimulado *processo = percorre->processo;
//         // printf("| %d     | %d     | %d  | %c | %d       | %c | %d      | %d  | %c |\n", processo->pid, processo->ppid, *processo->pc, 'a', 
//         //         processo->prioridade, 'e',processo->tempoInicio, processo->tempoCPU, 'a');
//         // printf("+-------+-------+------+------------+------------+--------+---------------+-----------+----------+\n");        
//         imprimeProcesso(*(percorre->processo), 4);

//         percorre = percorre->proximo;
//     }
// }
