#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
//   int LL;
//   int CC;
  /* outros componentes */
} TipoItem;

typedef struct TipoCelula *TipoApontador;

typedef struct TipoCelula {
  TipoItem Item;
  TipoApontador Prox;
} TipoCelula;

typedef struct {
  TipoApontador Primeiro, Ultimo;
} TipoLista;

/* ========================================================================= */

void FLVazia(TipoLista *Lista);
void Insere(int linha, int coluna, TipoLista *Lista);
void Imprime(TipoLista Lista);
int Vazia(TipoLista Lista);
int BuscaPosicao(TipoLista Lista, int linha, int coluna);