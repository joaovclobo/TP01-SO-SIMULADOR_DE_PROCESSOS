#include<stdlib.h>
#include "./instrucao.h"

typedef enum {
    BLOQUEADO,
    EXECUCAO,
    PRONTO
} Estado;

typedef struct ProcessoSimulado
{
    int pid;                    //ID do proceso
    int ppid;                   //ID do proceso pai
    int* pc;                    //Contador de programa (posição da proxima istrução que sera lida do array de instruções)
    int* arrVariaveis;          //Ponteiro para onde as variáveis do processo são armazenadas
    int prioridade;             //Prioridade do processo (valor de 0 a 3, onde 0 tem menor tempo de CPU e 3 o maior)
    Estado estado;              //Estado do processo podendo ser um dos 3 valores do enum
    int tempoInicio;            //Tempo do sistema que o processo começou
    int tempoCPU;               //Tempo que o processo já passou executando
    Instrucao** arrPrograma;     //Array com as instruções do processo (programa)
} ProcessoSimulado;

void criaProcessoInit(ProcessoSimulado** processoInit, int tempoSistema);

void copiaProcesso(ProcessoSimulado** novoProcesso, ProcessoSimulado processo);
void copiaVariaveis(int* arrVariaveisBase, int* arrVariaveisNovo, int tamanho);
void copiaArrPrograma(ProcessoSimulado* novoProcesso, ProcessoSimulado processoPai);

void atualizaArrPrograma(char* caminhoArquivo, ProcessoSimulado* novoProcesso);

int numeroVariaveis(ProcessoSimulado processo);

void imprimeProcesso(ProcessoSimulado processo, int opcao);
void imprimeEstado(Estado estado);
void imprimeVariaveis(int* arrVariaveis, int tamanho);
