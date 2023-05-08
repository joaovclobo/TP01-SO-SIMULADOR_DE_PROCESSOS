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

GerenciadorProcesso* inicializaGerenciador()
{
    GerenciadorProcesso *gerenciador;
    gerenciador->tempo = 0;
    gerenciador->quantidadeProcessosExecutados = 0;
    gerenciador->tempoTotalExecucao = 0;
    gerenciador->cpu = inicializaCPU();
    gerenciador->tabelaProcessos = criaLista();
    gerenciador->estadoPronto = criaFila();
    gerenciador->estadoBloqueado = criaFila();
    return gerenciador;
}

void insereProcessoTabela(ProcessoSimulado *processoEscolhido, GerenciadorProcesso *gerenciador)
{
    insereInicio(gerenciador->tabelaProcessos, processoEscolhido);
    gerenciador->quantidadeProcessosExecutados+=1;
}

void removeProcessoTabela(ProcessoSimulado *processoEscolhido, GerenciadorProcesso *gerenciador) {
    removeItem(gerenciador->tabelaProcessos, processoEscolhido);
    gerenciador->tempoTotalExecucao += processoEscolhido->tempoCPU;
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