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
    int opcao = MenuImpressaoProcesso();
    
    ProcessoSimulado* processoInit;
    criaProcessoInit(&processoInit, 0);
    printf("Processo pai: \n");
    imprimeProcesso(*processoInit, opcao);
    
    ProcessoSimulado* novoProcessoFork;
    copiaProcesso(&novoProcessoFork, *processoInit, 10);
    printf("Processo Filho: \n");
    imprimeProcesso(*novoProcessoFork, opcao);

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
