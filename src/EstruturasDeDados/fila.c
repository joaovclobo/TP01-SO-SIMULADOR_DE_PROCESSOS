#include "fila.h"

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

void Enfileira(int pid, int tempoExecutado, TipoFila *Fila)
{
    
    Fila->Tras->Prox = (Ponteiro) malloc(sizeof(Celula_str)); 
    Fila->Tras = Fila->Tras->Prox;
    Fila->Tras->pidTempo = criaCelulaPidTempo(pid, tempoExecutado);
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
        printf("pid: %d\n", Aux->pidTempo.pid);
        printf("tempoExecutado: %d\n", Aux->pidTempo.tempoExecutado);
        Aux = Aux->Prox;
    }
}

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

// void enfileiraPorPrioridade(TipoFila *Fila, int prioridade, int pid, int tempoExecutado)
// {
//     printf("\n ENTROU NA ENFILEIRA PRIORIDADE \n");
//     Celula_str *celula = (Ponteiro) malloc(sizeof(Celula_str));
//     Fila->Tras = Fila->Tras->Prox; 
//     Fila->Tras->pidTempo.pid = pid;
//     Fila->Tras->pidTempo.prioridade = prioridade;
//     Fila->Tras->pidTempo.tempoExecutado = tempoExecutado;
    
//     if(Fila->Frente == NULL)
//     {
//         Fila->Frente = (Ponteiro) malloc(sizeof(Celula_str));
//         Fila->Tras = Fila->Tras->Prox; 
//         Fila->Tras->pidTempo.pid = pid;
//         Fila->Tras->pidTempo.prioridade = prioridade;
//         Fila->Tras->pidTempo.tempoExecutado = tempoExecutado;
//     }
//     else 
//     {
    
//         if (prioridade > Fila->Frente->pidTempo.prioridade) 
//         {
//             celula->Prox = Fila->Frente;
//             Fila->Frente = celula;
//         }
//         else
//         {
//             Celula_str *atual = Fila->Frente;

//             while (atual->Prox != NULL && atual->Prox->pidTempo.prioridade >= prioridade) {
//                 atual = atual->Prox;
//             }

//             celula->Prox = atual->Prox;
//             atual->Prox = celula;
//         }
//     }
//     //Fila->tamanho++;
// }


// Fila* criaFila()
// {
//     Fila *f = (Fila*) malloc(sizeof(Fila));
//     if (f == NULL)
//     {
//         printf("Erro: nao foi possivel alocar memoria.\n");
//         exit(1);
//     }
//     f->inicio = NULL;
//     f->fim = NULL;
//     f->tamanho = 0;
//     return f;
// }

// void destroiFila(Fila *f)
// {
//     No *aux = f->inicio;
//     while (aux != NULL)
//     {
//         No *tmp = aux->prox;
//         free(aux);
//         aux = tmp;
//     }
//     free(f);
// }

// PidTempo* criaCelulaPidTempo(int prioridade, int PID, int tempoExecutado)
// {
//     PidTempo *celula;
//     celula->pid = PID;
//     celula->prioridade = prioridade;
//     celula->tempoExecutado = tempoExecutado;
//     return celula;
// }

// void enfileiraPrioridade(Fila *f, int prioridade, int PID, int tempoExecutado)
// {
//     printf("\n ENTROU NA ENFILEIRA PRIORIDADE \n");
//     PidTempo *celula = criaCelulaPidTempo(prioridade, PID, tempoExecutado);
//     No *novoNo = (No*) malloc(sizeof(No));
    
//     if(f->tamanho == 0)
//     {
//         printf("\n ENTROU COM FILA VAZIA \n");
//         f->inicio = novoNo;

//     }
//     // else if(f->tamanho == 1)
//     // {
//     //     printf("a1");
//     // }
//     // else if(f->tamanho == 2)
//     // {
//     //     printf("a2");
//     // }
//     // else if(f->tamanho == 3)
//     // {
//     //     printf("a3");
//     // }
//     // else if(f->tamanho == 4)
//     // {
//     //     printf("a4");
//     // }
//     else 
//     {
//         printf("\nENTROU ELSE => TAMANHO FILA > 0\n");
//         printf("\n prioridade: %d \n", f->inicio->pidTempo->prioridade);
//         // printf("\n prioridade: %d \n", f->inicio->prox->pidTempo->prioridade);
//         if (prioridade > f->fim->pidTempo->prioridade) 
//         {
//             printf("\n ENTROU COM PRIORIDADE MAIOR \n");
//             novoNo->prox = f->inicio;
//             f->inicio = novoNo;
//         }
//         else
//         {
//             printf("\n ENTROU COM PRIORIDADE MENOR \n");
//             No *atual = f->inicio;

//             while (atual->prox != NULL && atual->prox->pidTempo->prioridade >= prioridade) {
//                 atual = atual->prox;
//             }

//             novoNo->prox = atual->prox;
//             atual->prox = novoNo;
//         }
//     }
//     f->tamanho++;
//     printf("\n SAIU DA ENFILEIRAPRIORIDADE \n");
// }

// void enfileira(Fila *f, int prioridade, int PID, int tempoExecutado)
// {
//     printf("\nENTROU NA FUNÇÃO\n");
//     struct No *novo = (struct No *)malloc(sizeof(struct No));
//     PidTempo *celula = criaCelulaPidTempo(prioridade, PID, tempoExecutado);
//     novo->pidTempo = celula;
//     novo->prox = NULL;
//     printf("\nALOCA\n");
//     if (f->inicio == NULL)
//     {
//         printf("\nINSEREVAZIO\n");
//         f->inicio = novo;
//     }
//     else
//     {
//         printf("\nINSEREFIM\n");
//         f->fim->prox = novo;
//     }
//     f->fim = novo;
//     f->tamanho++;
//     printf("\nSAIU DA FUNÇÃO\n");
// }

// void desenfileira(Fila *f)
// {
//     if (f->inicio == NULL)
//     {
//         printf("Erro: fila vazia.\n");
//         exit(1);
//     }
//     PidTempo *valor = f->inicio->pidTempo;
//     No *tmp = f->inicio;
//     f->inicio = f->inicio->prox;
//     if (f->inicio == NULL)
//     {
//         f->fim = NULL;
//     }
//     free(tmp);
//     f->tamanho--;
// }

// int filaVazia(Fila *f)
// {
//     return (f->inicio == NULL);
// }

// int filaCheia(Fila *f)
// {
//     No *novoNo = (No*) malloc(sizeof(No));
//     if (novoNo == NULL)
//     {
//         return 1;
//     }
//     free(novoNo);
//     return 0;
// }
