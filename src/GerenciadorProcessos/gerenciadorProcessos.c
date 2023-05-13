#include "gerenciadorProcessos.h"
void gerenciadorProcessos(GerenciadorProcesso *gerenciador, char comando)
{
    
    if (comando == 'U')
    {
        encerraUnidadeTempo(gerenciador);
        if (gerenciador->tempo == 1)
        {
            iniciaProcessoInit(gerenciador);

        } else
        {
            //fazer funcao que seleciona processo da fila de pronto de acordo com o escalonamento
            //Usa a funcao carrega processo 
            executaProxInstrucao(gerenciador->cpu, gerenciador->tempo,gerenciador->tabelaProcessos);
            
            imprimeCPU(*gerenciador->cpu);
        }
    }
}

void encerraUnidadeTempo(GerenciadorProcesso *gerenciador)
{
    gerenciador->tempo += 1;
}

GerenciadorProcesso* inicializaGerenciador()
{
    GerenciadorProcesso *gerenciador = (GerenciadorProcesso*) malloc(sizeof(GerenciadorProcesso));
    gerenciador->tempo = 0;
    gerenciador->quantidadeProcessosExecutados = 0;
    gerenciador->tempoTotalExecucao = 0;
    gerenciador->cpu = inicializaCPU();
    gerenciador->tabelaProcessos = criaLista();
    gerenciador->estadoPronto = criaFila();
    gerenciador->estadoBloqueado = criaFila();

    return gerenciador;
}

void iniciaProcessoInit(GerenciadorProcesso* gerenciador)
{
     ProcessoSimulado* processoInit = criaProcessoInit(gerenciador->tempo);
    carregaProcesso(gerenciador->cpu, processoInit);
    insereTabela(gerenciador->tabelaProcessos, processoInit);
    imprimeTabela(gerenciador->tabelaProcessos);
    
}

void insereProcessoTabela(ProcessoSimulado *processoEscolhido, GerenciadorProcesso *gerenciador)
{
    insereTabela(gerenciador->tabelaProcessos, processoEscolhido);
    gerenciador->quantidadeProcessosExecutados+=1;
}

void removeProcessoTabela(ProcessoSimulado *processoEscolhido, GerenciadorProcesso *gerenciador) {
    //Talvez mudar isso
    removeTabela(gerenciador->tabelaProcessos, processoEscolhido->pid);
    gerenciador->tempoTotalExecucao += processoEscolhido->tempoCPU;
}
