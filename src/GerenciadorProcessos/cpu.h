#include <stdio.h>
#include <stdlib.h>
#include "../EstruturasDeDados/fila.h"
#include "../EstruturasDeDados/lista.h"

typedef struct CPU
{
    int *pid;
    Instrucao **arrPrograma;
    int *pcProgramaAtual;
    int **arrVariaveis;
    int quantum;
} CPU;

CPU* inicializaCPU();

int* instrucaoN(int n);
void instrucaoD(int x, int *vetorPosicoes);
void instrucaoV(int x, int n,int *vetorPosicoes);
void instrucaoA(int x, int n, int *vetorPosicoes);
void instrucaoS(int x, int n, int *vetorPosicoes);
int instrucaoB(int n);
void instrucaoT();
void instrucaoF(int n);
void instrucaoR(char* nomeDoArquivo);
