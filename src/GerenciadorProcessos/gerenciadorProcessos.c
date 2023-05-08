#include "gerenciadorProcessos.h"
void gerenciadorProcessos(GerenciadorProcesso *gerenciador, char comando)
{
    
    if (comando == 'U')
    {
        encerraUnidadeTempo(gerenciador);
    }
}

void encerraUnidadeTempo(GerenciadorProcesso *gerenciador)
{
    gerenciador->tempo += 1;
}

void inicializaGerenciador(GerenciadorProcesso *gerenciador)
{
    gerenciador->tempo = 0;

    gerenciador->quantidadeProcessosExecutados = 0;
    gerenciador->tempoTotalExecucao = 0;

    gerenciador->cpu = inicializaCPU();

    gerenciador->tabelaProcessos = criaLista();
    gerenciador->estadoPronto = criaFila();
    gerenciador->estadoBloqueado = criaFila();
    
}

void gerenciaTabelaProcessos(GerenciadorProcesso *gerenciador, ProcessoSimulado *processo,
                            int opcao)
{
    if (opcao == 1) // adiciona um processo na tabela
    {
        insereFim(gerenciador->tabelaProcessos, processo);
        gerenciador->quantidadeProcessosExecutados += 1;
    }
    else // remove um processo da tabela
    {
        removeItem(gerenciador->tabelaProcessos, processo);
        gerenciador->tempoTotalExecucao += processo->tempoCPU;
    }
}

void imprimeTabelaProcesso(Lista *tabelaProcesso)
{
    Celula *percorre = tabelaProcesso->inicio;
    printf("\n");
    printf("+------------------------------+------------------------------\n");
    printf("| PID | PPID | PC | Variaveis | Prioridade | Estado | Tempo Inicial | Tempo CPU | Programa |");
    printf("+------------------------------+------------------------------\n");
    while(percorre != NULL)
    {
        ProcessoSimulado *processo = percorre->processo;
        printf("| %d | %d | %c | %c | %d | %c | %d | %d | %c |", processo->pid, processo->ppid, 'p', 'a', 
                processo->prioridade, 'e',processo->tempoInicio, processo->tempoCPU, 'a');
        printf("+------------------------------+------------------------------\n");
        percorre = percorre->proximo;
    }
}

int criaPID(GerenciadorProcesso *gerenciador)
{
    Celula *inicio = gerenciador->tabelaProcessos->inicio;
    int novoPID = gerenciador->tabelaProcessos->inicio->processo->pid;
    Celula *atual = inicio->proximo;
    while (atual != NULL)
    {
        if (atual->processo->pid > novoPID)
        {
            novoPID = atual->processo->pid;
        }
        atual = atual->proximo;
    }
    return novoPID+1;
}