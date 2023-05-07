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
void trocaProcesso(CPU* cpu, ProcessoSimulado* processoAtual);
void imprimeCPU(CPU cpu);

//Instruçẽos de programa que são processadas na CPU

int* instrucaoN(int n);
void instrucaoD(int x, int *vetorPosicoes);
void instrucaoV(int x, int n,int *vetorPosicoes);
void instrucaoA(int x, int n, int *vetorPosicoes);
void instrucaoS(int x, int n, int *vetorPosicoes);
int instrucaoB(int n);
void instrucaoT();
void instrucaoF(int n);
void instrucaoR(char* nomeDoArquivo);
