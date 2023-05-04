#include "menu.h"

int MenuInicial(FILE** arquivoDeEntrada)
{
    int opcao;

    do
    {
   
    printf("\n\n=========== MENU ===========");
    printf("\n1) Entrada padrão");
    printf("\n2) Entrada por arquivo");
    printf("\n>> Escolha a opção: ");
    scanf("%d", &opcao);

    if (opcao == 1 ){
        printf("\nEntre com um dos comandos a seguir para:\n");
        printf("U) Indicar o fim de uma unidade de tempo;\n");
        printf("I) Imprimir o estado atual do sistema;\n");
        printf("M) Imprimir o tempo médio de resposta e finalizar o sistema.\n");

    } else if (opcao == 2){
        *arquivoDeEntrada = abreArquivoRead("./data/comandosControle");

    } else {
        printf("Opção inválida! Tente novamente.\n");

    }
    
    } while (opcao != 1 && opcao != 2);

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
