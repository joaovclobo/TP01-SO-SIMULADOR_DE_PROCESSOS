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
    gerenciador->estadoPronto = criaFila();
    gerenciador->estadoBloqueado = criaFila();
    gerenciador->tabelaProcessos = criaLista();
    gerenciador->tempoTotalExecucao = 0;
    gerenciador->quantidadeProcessosExecutados = 0;
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
    return novoPID;
}