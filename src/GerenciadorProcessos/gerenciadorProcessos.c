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

void gerenciaEstadoPronto(Fila *estadoPronto, int indiceProcesso, int opcao)
{
    if (opcao == 1) // adicionar processo no estado pronto
    {
        enfileira(estadoPronto, indiceProcesso);
    }
    else // remove processo do estado pronto
    {
        desenfileira(estadoPronto);
    }
}

void gerenciaEstadoBloqueado(Fila *estadoBloqueado, int indiceProcesso, int opcao)
{
    if (opcao == 1) // adicionar processo no estado bloqueado
    {
        enfileira(estadoBloqueado, indiceProcesso);
    }
    else // remove processo do estado bloqueado
    {
        desenfileira(estadoBloqueado);
    }
}

void gerenciaTabelaProcessos(Lista *tabelaProcessos, ProcessoSimulado *processo, int opcao, GerenciadorProcesso *gerenciador)
{
    if (opcao == 1) // adiciona um processo na tabela
    {
        insereFim(tabelaProcessos, processo);
        gerenciador->quantidadeProcessosExecutados += 1;
    }
    else // remove um processo da tabela
    {
        // removeLista()
       //  gerenciador->tempoTotalExecucao += processo->tempo
    }
}