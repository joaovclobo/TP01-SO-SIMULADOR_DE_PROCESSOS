#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAXBUFFER 100

//TAD que define os comandos possíveis de um processo simulado

typedef struct Instrucao
{
    char tipoDeInstrucao;   //Armazena a letra que representa o comando
    int parametroNumerico1; //Armazena o valor do primeiro parametro numérico
    int parametroNumerico2; //Armazena o valor do segundo parametro numérico quando existir
    char* parametroTexto;   //Armazena nomes dos arquivos
}Instrucao;

Instrucao inicializaInstrucao(char* instrucaoLida);
void printInstucao(Instrucao Instrucao);
