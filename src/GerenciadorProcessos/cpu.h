#include <stdio.h>
#include <stdlib.h>
#include "../EstruturasDeDados/fila.h"
#include "../EstruturasDeDados/lista.h"

typedef struct CPU
{
    int *pidProcessoAtual;
    Instrucao **programaProcessoAtual;
    int *pcProcessoAtual;
    int **variaveisProcessoAtual;
    int fatiaQuantum;       //Quanto do "quantum" de tempo já foi usada pelo processo em execução
} CPU;

CPU* inicializaCPU();
void carregaProcesso(CPU* cpu, ProcessoSimulado* processoAtual);
void executaProxInstrucao(CPU* cpu, int tempoAtualSistema, Lista* tabelaProcessos,
                             int* quantidadeProcessosIniciados, TipoFila** estadoPronto, TipoFila* estadoBloqueado);
int cpuLivre(CPU* cpu);
void imprimeCPU_2(CPU* cpu);
void zeraCPU(CPU* cpu);

/* -------------- Instruçẽos de programa que são processadas na CPU -------------- */

int* instrucaoN(int n);
void instrucaoD(int x, int *arrVariaveis);
void instrucaoV(int x, int n, int *arrVariaveis);
void instrucaoA(int x, int n, int *arrVariaveis);
void instrucaoS(int x, int n, int *arrVariaveis);
void instrucaoB(int n, int* pidProcessoAtual, Lista* tabelaProcessos, TipoFila* estadoBloqueado);
void instrucaoT(int* pidProcessoAtual, Lista* tabelaProcessos);
void instrucaoF(int n, int* pidProcessoAtual, int* pcProcessoAtual, int* quantidadeProcessosIniciados, int tempoAtualSistema, Lista* tabelaProcessos, TipoFila** filaPronto);
void instrucaoR(char *nomeDoArquivo, Instrucao** arrPrograma, int* pcProcessoAtual);
