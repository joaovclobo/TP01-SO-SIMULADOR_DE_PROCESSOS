#include "menu.h"

int MenuInicial() {
    int opcao;

    printf("\n\n=========== MENU ===========");
    printf("\n1) Entrada padrão");
    printf("\n2) Entrada por arquivo");
    printf("\n>> Escolha a opção: ");
    scanf("%d", &opcao);
    
    return opcao;
}