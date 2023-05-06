#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "./src/ProcessoSimulado/processoSimulado.h"

int main()
{
    // Instrucao* programa;
    // leInstrucoesArquivo("./data/init", &programa);
    // imprimeArrPrograma(programa);
    int opcao = 2;

    printf("\nEscolha as informações para exibir do  processo");
    printf("\n1) Não exibir nenhuma;");
    printf("\n2) Variáveis do processo;");
    printf("\n3) Instruções do processo;");
    printf("\n4) Instruções e variáveis do processo;");
    printf("\n>> Escolha a opção: ");
    scanf("%d", &opcao);
    
    ProcessoSimulado* processoInit;
    criaProcessoInit(&processoInit, 0);
    imprimeProcesso(*processoInit, opcao);
    
    // ProcessoSimulado* novoProcessoFork;
    // copiaProcesso(&novoProcessoFork, *processoInit);
    // imprimeProcesso(*novoProcessoFork, opcao);

    // int* arr = (int*) malloc(5 * sizeof(int));

    // for (int i = 0; i < 5; i++)
    // {
    //     arr[i] = i*(i+1)*10;
    // }

    // int* arrNovo;
    
    // imprimeVariaveis(arr, 5);
    // copiaVariaveis(arr, arrNovo, 5);
    // imprimeVariaveis(arr, 5);

}
