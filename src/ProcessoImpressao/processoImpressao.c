#include "processoImpressao.h"

void imprimeGerenciador(GerenciadorProcesso *gerenciador) 
{
    printf("\nTempo de uso do sistema no momento atual: %d unidades de tempo\n", gerenciador->tempo);
    printf("\nID dos processos em estado pronto: ");
    imprimeFila(gerenciador->estadoPronto);
    printf("\nID dos processos em estado bloqueado: ");
    imprimeFila(gerenciador->estadoBloqueado);
}
