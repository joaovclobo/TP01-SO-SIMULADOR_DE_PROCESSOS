#include "./src/ProcessoControle/processoControle.h"
#include "./src/ProcessoImpressao/processoImpressao.h"
//#include "./src/GerenciadorProcessos/gerenciadorProcessos.h"
#include <time.h>

// int main(int argc, char **argv)
// {
//     int fd[2];
//     char comando = '!';
//     FILE *arquivoDeEntrada;
//     GerenciadorProcesso* gerenciador;
//     gerenciador = inicializaGerenciador();

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
//             gerenciadorProcessos(gerenciador, comando);
 
//             //Isto só esta comentado pq ainda não está implementado por completo

//             // if (comando == 'I')
//             // {
//             //     printf("\n\n======== INFORMAÇÕES SOBRE O SISTEMA ========\n");
//             //     imprimeGerenciador(&gerenciador);
//             //     // imprimeControle();
//             //     // imprimeSimulado();
//             // }

//             // else 
//             if (comando == 'M')
//             {
//                 break;
//             }
//         }
//         close(fd[0]);

//     }
//     return 0;
// }


int main(int argc, char **argv)
{
    GerenciadorProcesso* gerenciador;
    gerenciador = inicializaGerenciador();


        // while (1)
        // {
            
        //     comando = lerCaractereDoPipe(fd[0]);
        //     gerenciadorProcessos(gerenciador, comando);
 
        
        //     // if (comando == 'I')
        //     // {
        //     //     printf("\n\n======== INFORMAÇÕES SOBRE O SISTEMA ========\n");
        //     //     imprimeGerenciador(&gerenciador);
        //     //     // imprimeControle();
        //     //     // imprimeSimulado();
        //     // }

        //     // else if (comando == 'M')
        //     // {
        //     //     break;
        //     // }
        // }
        // close(fd[0]);

        CPU *cpu = inicializaCPU();
        Fila* filaPronto = criaFila();
        
        ProcessoSimulado *processoInit = criaProcessoInit(1);

        carregaProcesso(cpu, processoInit);
        for(int j = 0; j < 6; j++)
        {
            executaProxInstrucao(cpu, 0, gerenciador->tabelaProcessos);
        }

        imprimeProcesso(*processoInit, 4);
        
        ProcessoSimulado *processo1 = copiaProcesso(*processoInit, 10, 1);
        imprimeProcesso(*processo1, 4);

        ProcessoSimulado *processo2 = copiaProcesso(*processo1, 13, 14);
        imprimeProcesso(*processo2, 4);

        // ProcessoSimulado *processo3 = copiaProcesso(*processoInit, 30, 3);
        // ProcessoSimulado *processo4 = copiaProcesso(*processoInit, 40, 4);
        // ProcessoSimulado *processo5 = copiaProcesso(*processoInit, 50, 5);  
        
        insereProcessoTabela(processoInit, gerenciador);
        insereProcessoTabela(processo1, gerenciador);
        insereProcessoTabela(processo2, gerenciador);
        // insereProcessoTabela(processo3, gerenciador);
        // insereProcessoTabela(processo4, gerenciador);
        // insereProcessoTabela(processo5, gerenciador);

        imprimeTabelaProcesso(gerenciador->tabelaProcessos);

    return 0;
}

