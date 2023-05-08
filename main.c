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
//#include "./src/GerenciadorProcessos/cpu.h"
#include "./src/GerenciadorProcessos/gerenciadorProcessos.h"
int main()
{
    CPU* cpu = inicializaCPU();
    // int opcao = 4;
    
    //TODO - isto ficará no momento de inicio de "inicio" do gerenciador de processo
    ProcessoSimulado* processoInit;
    criaProcessoInit(&processoInit, 0);
    escalonaProcesso(cpu, processoInit);
    executaProxInstrucao(cpu, 0);

    int count = 11;

    for (int i = 0; i < count; i++)
    {
        imprimeCPU(*cpu);
        executaProxInstrucao(cpu, 27);
    }

    // printf("Processo pai: \n");
    // imprimeProcesso(*processoInit, opcao);
    
    // ProcessoSimulado* novoProcessoFork;
    // copiaProcesso(&novoProcessoFork, *processoInit, 10);
    // printf("Processo Filho: \n");
    // imprimeProcesso(*novoProcessoFork, 4);


    // printf("\t ---- CPU 2 ----\n");
    // escalonaProcesso(cpu, novoProcessoFork);
    // imprimeCPU(*cpu);

}
