#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../Menu/menu.h"

#define MAXBUFFER 100
#define MAXINTRUC 100

//TAD que define os comandos possíveis de um processo simulado

typedef struct Instrucao
{
    char tipoDeInstrucao;               //Armazena a letra que representa o comando
    int parametroNumerico1;             //Armazena o valor do primeiro parametro numérico
    int parametroNumerico2;             //Armazena o valor do segundo parametro numérico quando existir
    char parametroTexto[MAXBUFFER];     //Armazena nomes dos arquivos
}Instrucao;

void inicializaInstrucao(char* instrucaoLida, Instrucao* instrucao);
void leInstrucoesArquivo(char* caminhoArquivo, Instrucao** programa);
void copiaInstrucao(Instrucao* novaInstrucao, Instrucao* instrucaoBase);

void imprimeInstucao(Instrucao Instrucao);
void imprimeArrPrograma(Instrucao* arrPrograma);
