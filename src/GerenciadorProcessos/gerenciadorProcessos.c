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
    //MUDAR PARA Celula *percorre = tabelaProcesso->inicio;
    Celula *percorre = tabelaProcesso->inicio;
    printf("+-------+-------+------+------------+------------+--------+---------------+-----------+----------+\n");
    printf("| PID   | PPID  | PC   | Variaveis  | Prioridade | Estado | Tempo Inicial | Tempo CPU | Programa |\n");
    printf("+-------+-------+------+------------+------------+--------+---------------+-----------+----------+\n");
    while(percorre != NULL)
    {
        //achar um jeito de printar arrays e estados
        ProcessoSimulado *processo = percorre->processo;
       printf("| %d     | %d     | %d  | %c | %d       | %c | %d      | %d  | %c |\n", processo->pid, processo->ppid, *processo->pc, 'a', 
                processo->prioridade, 'e',processo->tempoInicio, processo->tempoCPU, 'a');
        printf("+-------+-------+------+------------+------------+--------+---------------+-----------+----------+\n");        percorre = percorre->proximo;
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