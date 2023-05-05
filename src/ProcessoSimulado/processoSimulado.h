#include<stdlib.h>
#include "../GerenciadorProcessos/instrucao.h"


typedef struct ProcessoSimulado
{
    int pid;
    int ppid;
    int* pc;
    int* arrVariaveis;
    int prioridade; 
    enum estado{bloqueado, execucao, pronto}estado; //talvez usemos um define???
    int tempoInicio;
    int tempoCPU;
    //instrucao* arrPrograma;
} ProcessoSimulado;
