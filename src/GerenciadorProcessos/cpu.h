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
    int fatiaQuantum;       //Quanto do quantum de tempo já foi usada pelo processo em execução
} CPU;

CPU* inicializaCPU();
void escalonaProcesso(CPU* cpu, ProcessoSimulado* processoAtual);
void executaProxInstrucao(CPU* cpu, int tempoAtualSistema);
void imprimeCPU(CPU cpu);

//Instruçẽos de programa que são processadas na CPU

int* instrucaoN(int n);
void instrucaoD(int x, int *arrVariaveis);
void instrucaoV(int x, int n, int *arrVariaveis);
void instrucaoA(int x, int n, int *arrVariaveis);
void instrucaoS(int x, int n, int *arrVariaveis);
// int instrucaoB(int n);
// void instrucaoT();
void instrucaoF(int n, int* pidProcessoAtual, int* pcProcessoAtual,int tempoAtualSistema);
void instrucaoR(char *nomeDoArquivo, Instrucao** arrPrograma, int* pcProcessoAtual);
