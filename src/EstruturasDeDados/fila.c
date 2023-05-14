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

PrioridadePid* criaCelulaPrioridadePid(int prioridade, int PID, int tempoExecutado)
{
    PrioridadePid *celula;
    celula->pid = PID;
    celula->prioridade = prioridade;
    celula->tempoExecutado = tempoExecutado;
    return celula;
}

void enfileiraPrioridade(Fila *f, int prioridade, int PID, int tempoExecutado)
{
    printf("\n ENTROU NA ENFILEIRA PRIORIDADE \n");
    PrioridadePid *celula = criaCelulaPrioridadePid(prioridade, PID, tempoExecutado);
    No *novoNo = (No*) malloc(sizeof(No));
    
    if(f->tamanho == 0)
    {
        printf("\n ENTROU COM FILA VAZIA \n");
        f->inicio = novoNo;

    }
    // else if(f->tamanho == 1)
    // {
    //     printf("a1");
    // }
    // else if(f->tamanho == 2)
    // {
    //     printf("a2");
    // }
    // else if(f->tamanho == 3)
    // {
    //     printf("a3");
    // }
    // else if(f->tamanho == 4)
    // {
    //     printf("a4");
    // }
    else 
    {
        printf("\nENTROU ELSE => TAMANHO FILA > 0\n");
        printf("\n prioridade: %d \n", f->inicio->prioridadePid->prioridade);
        // printf("\n prioridade: %d \n", f->inicio->prox->prioridadePid->prioridade);
        if (prioridade > f->fim->prioridadePid->prioridade) 
        {
            printf("\n ENTROU COM PRIORIDADE MAIOR \n");
            novoNo->prox = f->inicio;
            f->inicio = novoNo;
        }
        else
        {
            printf("\n ENTROU COM PRIORIDADE MENOR \n");
            No *atual = f->inicio;

            while (atual->prox != NULL && atual->prox->prioridadePid->prioridade >= prioridade) {
                atual = atual->prox;
            }

            novoNo->prox = atual->prox;
            atual->prox = novoNo;
        }
    }
    f->tamanho++;
    printf("\n SAIU DA ENFILEIRAPRIORIDADE \n");
}

void enfileira(Fila *f, int prioridade, int PID, int tempoExecutado)
{
    printf("\nENTROU NA FUNÇÃO\n");
    struct No *novo = (struct No *)malloc(sizeof(struct No));
    PrioridadePid *celula = criaCelulaPrioridadePid(prioridade, PID, tempoExecutado);
    novo->prioridadePid = celula;
    novo->prox = NULL;
    printf("\nALOCA\n");
    if (f->inicio == NULL)
    {
        printf("\nINSEREVAZIO\n");
        f->inicio = novo;
    }
    else
    {
        printf("\nINSEREFIM\n");
        f->fim->prox = novo;
    }
    f->fim = novo;
    f->tamanho++;
    printf("\nSAIU DA FUNÇÃO\n");
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