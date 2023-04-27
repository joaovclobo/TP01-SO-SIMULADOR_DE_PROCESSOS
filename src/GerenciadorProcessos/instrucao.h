#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAXBUFFER 100

typedef struct Instrucao
{
    char tipoDeInstrucao;
    int parametroNumerico1;
    int parametroNumerico2;
    char* parametroTexto;
}Instrucao;

Instrucao inicializaInstrucao(char *instrucaoLida);
void printInstucao(Instrucao Instrucao);
