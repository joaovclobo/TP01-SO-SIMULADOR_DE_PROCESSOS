#include "processoImpressao.h"

void imprimeGerenciador(GerenciadorProcesso *gerenciador) 
{
    printf("\nTempo de uso do sistema no momento atual: %d unidades de tempo\n", gerenciador->tempo);
    printf("\nID dos processos em estado pronto: ");
    imprimeFila(gerenciador->estadoPronto);
    printf("\nID dos processos em estado bloqueado: ");
    imprimeFila(gerenciador->estadoBloqueado);
}

// void imprimeTabelaProcesso(Lista *tabelaProcesso)
// {
//     //MUDAR PARA Celula *percorre = tabelaProcesso->inicio;
//     Celula *percorre = tabelaProcesso->inicio;
//     // printf("+-------+-------+------+------------+------------+--------+---------------+-----------+----------+\n");
//     // printf("| PID   | PPID  | PC   | Variaveis  | Prioridade | Estado | Tempo Inicial | Tempo CPU | Programa |\n");
//     // printf("+-------+-------+------+------------+------------+--------+---------------+-----------+----------+\n");
//     printf(">>>>>>>>>>>>> Tabela de processos: <<<<<<<<<<<<<<<<\n");
//     while(percorre != NULL)
//     {
//         //achar um jeito de printar arrays e estados
//         //Usar as funções imprime variaveis e imprime estados
//         ProcessoSimulado *processo = percorre->processo;
//         // printf("| %d     | %d     | %d  | %c | %d       | %c | %d      | %d  | %c |\n", processo->pid, processo->ppid, *processo->pc, 'a', 
//         //         processo->prioridade, 'e',processo->tempoInicio, processo->tempoCPU, 'a');
//         // printf("+-------+-------+------+------------+------------+--------+---------------+-----------+----------+\n");        
//         imprimeProcesso(*(percorre->processo), 4);

//         percorre = percorre->proximo;
//     }
// }