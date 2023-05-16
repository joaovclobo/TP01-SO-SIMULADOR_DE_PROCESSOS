#include "processoImpressao.h"

// TODO: fazer com que os menus sejam chamadas em uma pilha, ou seja, poder voltar em cada ação

void menuImpressao(GerenciadorProcesso gerenciador, ProcessoSimulado processo)
{
    int opcao;

    printf("======== MENU DE IMPRESSAO ========\n\n");
    printf("1 - Imprimir processo controle\n");
    printf("2 - Imprimir gerenciador de processos\n");
    printf("3 - Imprimir processo simulado\n");
    printf("====================================\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    if (opcao == 1)
    {
        imprimirProcessoControle();
    }
    else if (opcao == 2)
    {
        imprimirGerenciadorProcessos(gerenciador);
    }
    else if (opcao == 3)
    {
        imprimirProcessoSimulado(processo);
    }
}

void imprimirProcessoControle()
{
    // TODO: no controle, imprime o tempo médio de resposta do sistema toda vez que lê o comando I
}

void imprimirGerenciadorProcessos(GerenciadorProcesso gerenciador)
{
    int opcao;

    printf("======== GERENCIADOR DE PROCESSOS ========\n\n");
    printf("1 - Tempo de uso atual do sistema\n");
    printf("2 - Processo em execução na CPU\n");
    printf("3 - Processos em estado bloqueado\n");
    printf("4 - Processos em estado pronto\n");
    printf("5 - Quantidade de processos executados até o momento\n");
    printf("6 - Informações sobre a CPU no momento atual\n");
    printf("7 - Informações sobre a Tabela de Processos no momento atual\n");
    printf("====================================\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    if (opcao == 1)
    {
        printf("\nTempo de uso do sistema no momento atual: %d unidades de tempo\n", gerenciador.tempo);
    }
    else if (opcao == 2)
    {
        printf("\nProcesso em execução na CPU:\n");
        // TODO: buscar na tabela de processos qual tem o mesmo ID do que está em execução e imprimí-lo
        //       utilizando a função imprimeProcesso -> localizada aqui no impressão mesmo
    }
    else if (opcao == 3)
    {
        printf("\nProcessos em estado bloqueado:");
        // TODO: buscar na tabela de processos qual tem o mesmo ID do que está em cada posição e ir imprimindo
        //       a cada busca, utilizando a função imprimeProcesso -> localizada aqui no impressão mesmo
        //       OU A OUTRA OPÇÃO
        //       apenas imprimir o PID de cada processo que está bloqueado de forma formatada
    }
    else if (opcao == 4)
    {
        printf("\nProcessos em estado pronto:");
        // TODO: buscar na tabela de processos qual tem o mesmo ID do que está em cada posição e ir imprimindo
        //       a cada busca, utilizando a função imprimeProcesso -> localizada aqui no impressão mesmo
        //       OU A OUTRA OPÇÃO
        //       apenas imprimir o PID de cada processo que está bloqueado de forma formatada
    }
    else if (opcao == 5)
    {
        printf("\nQuantidade de processos executados até o momento: %d\n", gerenciador.quantidadeProcessosExecutados);
    }
    else if (opcao == 6)
    {
        printf("\nInformações sobre a CPU no momento atual:");
        // TODO: chamar função que exibe informações sobre a cpu
    }
    else if (opcao == 7)
    {
        printf("\nInformações sobre a Tabela de Processos no momento atual:");
        // TODO: chamar função que exibe informações sobre a Tabela de Processos
    }
}

void imprimirProcessoSimulado(ProcessoSimulado processo)
{
    int opcao;

    printf("======== PROCESSO SIMULADO ========\n\n");
    printf("1 - Imprimir informações gerais sobre o processo\n");
    printf("2 - Imprimir informações gerais e as variáveis do programa\n");
    printf("====================================\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    if (opcao == 1)
    {
        imprimeInfosGeraisProcesso(processo);
    }
    else if (opcao == 2)
    {
        imprimeInfosGeraisProcesso(processo);
        imprimeVariaveis(processo.arrVariaveis, numeroVariaveis(*processo.arrPrograma));
    }
}

void imprimeInfosGeraisProcesso(ProcessoSimulado processo)
{
    printf("->> Processo - PID %2d | ", processo.pid);
    printf("PPID %2d | ", processo.ppid);
    printf("PC %2d | ", *(processo.pc));
    printf("Prioridade %d | ", processo.prioridade);
    imprimeEstado(processo.estado);
    printf("Tempo de inicio %2d | ", processo.tempoInicio);
    printf("Tempo de CPU %2d\n", processo.tempoCPU);
}

void imprimeVariaveisProcesso(int *arrVariaveis, int tamanho)
{
    printf("Valores atuais das variáveis:\n");

    for (int i = 0; i < tamanho; i++)
    {
        printf("%d | ", arrVariaveis[i]);
    }
    putchar('\n');
}

int numeroVariaveisProcesso(Instrucao *arrPrograma)
{
    return arrPrograma[0].parametroNumerico1;
}

void imprimeEstadoProcesso(Estado estado)
{
    switch (estado)
    {
    case BLOQUEADO:
        printf("Estado: BLOQUEADO | ");
        break;

    case EXECUCAO:
        printf("Estado: EXECUCAO | ");
        break;

    case PRONTO:
        printf("Estado: PRONTO | ");
        break;

    default:
        break;
    }
}
