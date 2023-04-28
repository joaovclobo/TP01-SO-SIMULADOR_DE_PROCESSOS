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

FILE* abreArquivoRead(char* nomeArquivo)
{

    FILE *fptr;

    printf("\tAbrindo o arquivo: %s\n", nomeArquivo);
    
    fptr = fopen(nomeArquivo, "r");

    if (fptr == NULL){
        printf("\nERRO: Arquivo não encontrado!\nPor favor, insira um arquivo válido!\n");
        return NULL;

    } else{
        return fptr;

    }
}