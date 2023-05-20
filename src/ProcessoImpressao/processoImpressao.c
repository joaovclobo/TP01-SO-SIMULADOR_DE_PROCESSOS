#include "processoImpressao.h"

int menuImpressao()
{
    int opcao = 0;
    printf("\n\n======== MENU DE IMPRESSAO ========\n");
    printf("1 - Imprimir gerenciador de processos\n");
    printf("2 - Sair do menu impressão\n");
    printf("====================================\n");
    printf("Escolha uma opção: ");
    scanf(" %d", &opcao);
    printf("\n\n");
    return opcao;
}

// void imprimirEstadoAtualSistema(GerenciadorProcessos *gerenciador)
// {
//     printf("\n\n>>>>>>> ESTADO ATUAL DO SISTEMA <<<<<<<\n\n");
//     printf("\n\nTempo de uso do sistema no momento atual: %d unidades de tempo\n", gerenciador->tempo);
//     imprimeCPUs(gerenciador);
// }

// void imprimirGerenciadorProcessos(GerenciadorProcessos *gerenciador)
// {
//     int opcao = 0;

//     while (opcao != 8)
//     {
//         printf("\n\n>>>>>>> GERENCIADOR DE PROCESSOS <<<<<<<\n\n");
//         printf("1 - Informações gerais sobre o gerenciador");
//         printf("2 - Tempo de uso atual do sistema\n");
//         printf("3 - Processos em estado bloqueado\n");
//         printf("4 - Processos em estado pronto\n");
//         printf("5 - Quantidade de processos executados até o momento\n");
//         printf("6 - Informações sobre a CPU no momento atual\n");
//         printf("7 - Informações sobre a Tabela de Processos no momento atual\n");
//         printf("8 - Retornar ao menu de impressão\n");
//         printf("====================================\n");
//         printf("Escolha uma opção: ");
//         scanf(" %d%*[^\n]", &opcao);

//         if (opcao == 1)
//         {
//             imprimirEstadoAtualSistema(gerenciador);
//         }
//         else if (opcao == 2)
//         {
//             printf("\n\nTempo de uso do sistema no momento atual: %d unidades de tempo\n", gerenciador->tempo);
//         }
//         else if (opcao == 3)
//         {
//             printf("\n\nProcessos em estado bloqueado:");
//             // imprimirFila(bloqueados);
//         }
//         else if (opcao == 4)
//         {
//             printf("\n\nProcessos em estado pronto:");
//             // TODO: buscar na tabela de processos qual tem o mesmo ID do que está em cada posição e ir imprimindo
//             //       a cada busca, utilizando a função imprimeProcesso -> localizada aqui no impressão mesmo
//         }
//         else if (opcao == 5)
//         {
//             printf("\n\nQuantidade de processos executados até o momento: %d\n", gerenciador->quantidadeProcessosIniciados);
//         }
//         else if (opcao == 6)
//         {
//             imprimeCPUs(gerenciador);
//         }
//         else if (opcao == 7)
//         {
//             int PID;
//             int opcaoProcesso = 0;
//             ProcessoSimulado *processo;

//             imprimeTabelaProcessos(gerenciador);
//             printf("\n");
//             printf("Deseja imprimir informações mais detalhadas sobre algum processo (0-NÃO/1-SIM): ");
//             scanf(" %d%*[^\n]", &opcaoProcesso);

//             if (opcaoProcesso == 1)
//             {
//                 printf("\nInforme o PID do processo: ");
//                 scanf(" %d%*[^\n]", &PID);
//                 processo = buscaProcesso(gerenciador->tabelaProcessos, PID);
//                 imprimeInfosGeraisProcesso(processo);
//                 imprimeVariaveisProcesso(processo->arrVariaveis, numeroVariaveis(*processo->arrPrograma));
//                 imprimeArrPrograma(*processo->arrPrograma, *processo->pc);
//             }
//         }
//     }
// }

// void imprimeInfosGeraisProcesso(ProcessoSimulado *processo)
// {
//     printf("-> Processo - PID %d | ", processo->pid);
//     printf("PPID %d | ", processo->ppid);
//     printf("PC %d | ", *(processo->pc));
//     printf("Prioridade %d | ", processo->prioridade);
//     imprimeEstado(processo->estado);
//     printf("Tempo de inicio %d | ", processo->tempoInicio);
//     printf("Tempo de CPU %d\n", processo->tempoCPU);
// }

// void imprimeVariaveisProcesso(int *arrVariaveis, int tamanho)
// {
//     printf("| Valores atuais das variáveis: ");

//     for (int i = 0; i < tamanho; i++)
//     {
//         printf(" %d ", arrVariaveis[i]);
//     }
//     printf("\n");
// }

// int numeroVariaveisProcesso(Instrucao *arrPrograma)
// {
//     return arrPrograma[0].parametroNumerico1;
// }

// void imprimeEstadoProcesso(Estado estado)
// {
//     switch (estado)
//     {
//     case BLOQUEADO:
//         printf("Estado: BLOQUEADO | ");
//         break;

//     case EXECUCAO:
//         printf("Estado: EXECUCAO | ");
//         break;

//     case PRONTO:
//         printf("Estado: PRONTO | ");
//         break;

//     default:
//         break;
//     }
// }

// void impressaoArquivo(GerenciadorProcessos *gerenciador)
// {
//     printf("\n\n>>>>>>> GERENCIADOR DE PROCESSOS <<<<<<<\n\n");
//     printf("\n°° Tempo de uso do sistema no momento atual: %d unidades de tempo", gerenciador->tempo);
//     printf("\n\n°° Processos em estado bloqueado:");
//     printf("\n\n°° Processos em estado pronto:");
//     printf("\n\n°° Quantidade de processos executados até o momento: %d", gerenciador->quantidadeProcessosIniciados);
//     imprimeCPUs(gerenciador);
//     imprimeTabelaProcessos(gerenciador->tabelaProcessos);
// }

// void imprimeCPUs(GerenciadorProcessos *gerenciador)
// {
//     for (int i = 0; i < gerenciador->numCPUs; i++)
//     {
//         if (cpuLivre(gerenciador->cpus[i]))
//         {
//             printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> CPU %d <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n", i);
//             imprimeCPU(gerenciador->cpus[i]);
//         }
//     }
// }

// void imprimeCPU(CPU *cpu)
// {
//     printf("\n->> Processo em execução - PID %d | ", cpu->pidProcessoAtual);
//     printf("PC %d |", cpu->pcProcessoAtual);
//     printf(" Fatia do quantum já executado: %d ", cpu->fatiaQuantum);
//     imprimeVariaveisProcesso(cpu->variaveisProcessoAtual, numeroVariaveis(cpu->programaProcessoAtual));
//     printf("\n");
// }

// void imprimeTabelaProcessos(GerenciadorProcessos *gerenciador)
// {
//     printf("\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> TABELA DE PROCESSOS <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
//     imprimeTabela(gerenciador->tabelaProcessos);
// }