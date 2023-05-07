// #include "./src/ProcessoControle/processoControle.h"
// #include "./src/ProcessoImpressao/processoImpressao.h"
// #include <time.h>

// int main(int argc, char **argv)
// {
//     int fd[2];
//     char comando = '!';
//     FILE *arquivoDeEntrada;
//     GerenciadorProcesso gerenciador;

//     int opcao = MenuInicial(&arquivoDeEntrada);

//     if (pipe(fd) == -1)
//     {
//         perror("Erro ao criar o pipe");
//         return 1;
//     }

//     pid_t pid = fork();

//     if (pid == -1)
//     {
//         perror("Erro ao criar o processo");
//         return 1;
//     }

//     if (pid > 0)
//     {
//         close(fd[0]);

//         while (1)
//         {
//             comando = controle(arquivoDeEntrada, opcao);
//             escreverCaractereNoPipe(fd[1], comando);

//             if (comando == 'M')
//             {
//                 break;
//             }
//         }
//         close(fd[1]);
//     }
//     else
//     {
//         close(fd[1]);

//         while (1)
//         {
//             comando = lerCaractereDoPipe(fd[0]);
//             gerenciadorProcessos(&gerenciador, comando);
//             inicializaGerenciador(&gerenciador);

//             if (comando == 'I')
//             {
//                 printf("\n\n======== INFORMAÇÕES SOBRE O SISTEMA ========\n");
//                 imprimeGerenciador(&gerenciador);
//                 // imprimeControle();
//                 // imprimeSimulado();
//             }

//             else if (comando == 'M')
//             {
//                 break;
//             }
//         }
//         close(fd[0]);
//     }
//     return 0;
// }

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

