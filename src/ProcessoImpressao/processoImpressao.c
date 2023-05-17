#include "processoImpressao.h"

int menuImpressao()
{
    int opcao = 0;
    printf("\n\n======== MENU DE IMPRESSAO ========\n");
    printf("1 - Imprimir gerenciador de processos\n");
    printf("2 - Imprimir processo simulado\n");
    printf("3 - Sair do menu impressão\n");
    printf("====================================\n");
    printf("Escolha uma opção: ");
    scanf(" %d", &opcao);
    printf("\n\n");
    return opcao;
}

void imprimirGerenciadorProcessos(GerenciadorProcessos *gerenciador)
{
    int opcao = 0;
    int *PID;
    CPU *cpu = gerenciador->cpu;
    Lista *tabela = gerenciador->tabelaProcessos;
    TipoFila *prontos = gerenciador->estadoBloqueado;
    TipoFila *bloqueados = gerenciador->estadoPronto;
    ProcessoSimulado *processo;

    while (opcao != 8)
    {
        printf("\n\n======== GERENCIADOR DE PROCESSOS ========\n\n");
        printf("1 - Tempo de uso atual do sistema\n");
        printf("2 - Processo em execução na CPU\n");
        printf("3 - Processos em estado bloqueado\n");
        printf("4 - Processos em estado pronto\n");
        printf("5 - Quantidade de processos executados até o momento\n");
        printf("6 - Informações sobre a CPU no momento atual\n");
        printf("7 - Informações sobre a Tabela de Processos no momento atual\n");
        printf("8 - Retornar ao menu de impressão\n");
        printf("====================================\n");
        printf("Escolha uma opção: ");
        scanf(" %d%*[^\n]", &opcao);

        if (opcao == 1)
        {
            printf("\n\nTempo de uso do sistema no momento atual: %d unidades de tempo\n", gerenciador->tempo);
        }
        else if (opcao == 2)
        {
            PID = cpu->pidProcessoAtual;
            processo = buscaProcesso(tabela, *PID);
            printf("\n\nProcesso em execução na CPU:\n");
            imprimeInfosGeraisProcesso(processo);
        }
        else if (opcao == 3)
        {
            printf("\n\nProcessos em estado bloqueado:");
            // imprimirFila(bloqueados);
        }
        else if (opcao == 4)
        {
            printf("\n\nProcessos em estado pronto:");
            // TODO: buscar na tabela de processos qual tem o mesmo ID do que está em cada posição e ir imprimindo
            //       a cada busca, utilizando a função imprimeProcesso -> localizada aqui no impressão mesmo
        }
        else if (opcao == 5)
        {
            printf("\n\nQuantidade de processos executados até o momento: %d\n", gerenciador->quantidadeProcessosIniciados);
        }
        else if (opcao == 6)
        {
            printf("\n\nInformações sobre a CPU no momento atual:");
            printf("\n->> Processo em execução - PID %d | ", *cpu->pidProcessoAtual);
            printf("PC %d |", *cpu->pcProcessoAtual);
            printf(" Fatia do quantum já executado: %d ", cpu->fatiaQuantum);
            imprimeVariaveisProcesso(*cpu->variaveisProcessoAtual, numeroVariaveis(*cpu->programaProcessoAtual));
            imprimeArrPrograma(*cpu->programaProcessoAtual, *cpu->pcProcessoAtual);
        }
        else if (opcao == 7)
        {
            printf("\n\nInformações sobre a Tabela de Processos no momento atual:\n");
            imprimeTabela(tabela);
        }
    }
}

void imprimirProcessoSimulado(GerenciadorProcessos *gerenciador)
{
    int opcao = 0;
    int PID;
    ProcessoSimulado *processo;

    while (opcao != 2)
    {
        printf("\n======== PROCESSO SIMULADO ========");
        printf("\n1 - Imprimir informações sobre o processo");
        printf("\n2 - Retornar ao menu impressão");
        printf("\n====================================\n");
        printf("Escolha uma opção: ");
        scanf(" %d%*[^\n]", &opcao);

        if (opcao == 1)
        {
            printf("<< ATENÇÃO: você pode encontrar o PID do processo que deseja imprimir na tabela de processos >>\n");
            printf("\nInforme o PID do processo: ");
            scanf(" %d%*[^\n]", &PID);
            processo = buscaProcesso(gerenciador->tabelaProcessos, PID);
            imprimeInfosGeraisProcesso(processo);
            imprimeVariaveisProcesso(processo->arrVariaveis, numeroVariaveis(*processo->arrPrograma));
            imprimeArrPrograma(*processo->arrPrograma, *processo->pc);
        }
    }
}

void imprimeInfosGeraisProcesso(ProcessoSimulado *processo)
{
    printf("->> Processo - PID %d | ", processo->pid);
    printf("PPID %d | ", processo->ppid);
    printf("PC %d | ", *(processo->pc));
    printf("Prioridade %d | ", processo->prioridade);
    imprimeEstado(processo->estado);
    printf("Tempo de inicio %d | ", processo->tempoInicio);
    printf("Tempo de CPU %d\n", processo->tempoCPU);
}

void imprimeVariaveisProcesso(int *arrVariaveis, int tamanho)
{
    printf("| Valores atuais das variáveis: ");

    for (int i = 0; i < tamanho; i++)
    {
        printf(" %d ", arrVariaveis[i]);
    }
    printf("\n");
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
