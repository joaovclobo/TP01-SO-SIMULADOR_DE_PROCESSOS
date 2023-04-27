#include "lista.h"

void FLVazia(TipoLista *Lista)
{ Lista -> Primeiro = (TipoApontador) malloc(sizeof(TipoCelula));
  Lista -> Ultimo = Lista -> Primeiro;
  Lista -> Primeiro -> Prox = NULL;
}

int Vazia(TipoLista Lista)
{ 
  return (Lista.Primeiro == Lista.Ultimo);
}

void Insere(int linha,int coluna, TipoLista *Lista)
{ Lista -> Ultimo -> Prox = (TipoApontador) malloc(sizeof(TipoCelula));
  Lista -> Ultimo = Lista -> Ultimo -> Prox;
  Lista -> Ultimo -> Item.LL = linha;
  Lista->Ultimo->Item.CC = coluna;
  Lista -> Ultimo -> Prox = NULL;
}

void Imprime(TipoLista Lista)
{ TipoApontador Aux;
  Aux = Lista.Primeiro -> Prox;
  while (Aux != NULL) 
    { 
      printf("LL: %d ", Aux -> Item.LL);
      printf("CC: %d\n", Aux -> Item.CC);
      Aux = Aux -> Prox;
    }
}
int BuscaPosicao(TipoLista Lista, int linha, int coluna){
  TipoApontador aux;
  aux = Lista.Primeiro->Prox;
  while (aux != NULL)
  {
    if(aux->Item.LL == linha && aux->Item.CC == coluna){
      return 1;
    }
    aux = aux->Prox;
  }
  return 0;
  
}