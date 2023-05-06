#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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

void imprimeInstucao(Instrucao Instrucao);
void imprimeArrPrograma(Instrucao* arrPrograma);

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

void imprimeProcesso(ProcessoSimulado processo);
void imprimeEstado(Estado estado);

//Funções para executar as instruções de um processo simulado

int* instrucaoN(int n);
void instrucaoD(int x);
void instrucaoV(int x, int n);
void instrucaoA(int x, int n);
void instrucaoS(int x, int n);
void instrucaoB(int n);
void instrucaoT();
void instrucaoF(int n);
void instrucaoR(char* nomeDoArquivo);

void inicializaInstrucao(char *instrucaoLida, Instrucao* instrucao)
{
    char* token;

    token = strtok(instrucaoLida, " ");
    
    instrucao->tipoDeInstrucao = token[0];
    instrucao->parametroNumerico1 = -1;
    instrucao->parametroNumerico2 = -1;
    strcpy(instrucao->parametroTexto, "#####");

    token = strtok(NULL, " ");

    while (token != NULL)
    {

        if (instrucao->tipoDeInstrucao == 'N' ||
            instrucao->tipoDeInstrucao == 'D' ||
            instrucao->tipoDeInstrucao == 'F' ||
            instrucao->tipoDeInstrucao == 'B')
        {
            instrucao->parametroNumerico1 = atoi(token);
            break;
        }

        else if (instrucao->tipoDeInstrucao == 'V' ||
                 instrucao->tipoDeInstrucao == 'S' ||
                 instrucao->tipoDeInstrucao == 'A')
        {
            instrucao->parametroNumerico1 = atoi(token);
            token = strtok(NULL, " ");
            instrucao->parametroNumerico2 = atoi(token);
            break;
        }

        else if (instrucao->tipoDeInstrucao == 'R')
        {
            strcpy(instrucao->parametroTexto, token);
            break;
        }

        else if (instrucao->tipoDeInstrucao == 'T')
        {
            break;
        }

        else
        {
            printf("\nErro");
            break;
        }
    }
}

void leInstrucoesArquivo(char* caminhoArquivo, Instrucao** programa)
{
    Instrucao* arrPrograma = (Instrucao*) malloc(MAXINTRUC * sizeof(Instrucao));
    int i = 0;
    
    //TODO - Simplificar usando a função
    char* cadaLinha = malloc(MAXBUFFER * sizeof(char));
    FILE* arquivoDeEntrada;

    if ((arquivoDeEntrada = fopen(caminhoArquivo, "r")) == NULL){
        printf("\nArquivo não encontrado!");
        
    }

    while (fgets(cadaLinha, MAXBUFFER, arquivoDeEntrada) != NULL)
    {   
        cadaLinha[strcspn(cadaLinha, "\n")] = '\0';
        inicializaInstrucao(cadaLinha, arrPrograma+i);
        i++;

    }

    *programa = arrPrograma;
}


void imprimeInstucao(Instrucao instrucao)
{
    printf("Instrução -  Tipo %c", instrucao.tipoDeInstrucao);
    printf(" | Param 1 %3d", instrucao.parametroNumerico1);
    printf(" | Param 2 %5d", instrucao.parametroNumerico2);
    printf(" | Param txt %s\n", instrucao.parametroTexto);
}

void imprimeArrPrograma(Instrucao* arrPrograma)
{
    int i = 0;

    while (arrPrograma[i-1].tipoDeInstrucao != 'T')
    {
        imprimeInstucao(arrPrograma[i]);
        i++;
    }
}

void criaProcessoInit(ProcessoSimulado** processoInit, int tempoSistema)
{
    ProcessoSimulado* processo = (ProcessoSimulado*) malloc(sizeof(ProcessoSimulado));

    processo->pid = 0;
    processo->ppid = 0;
    processo->pc = 0;
    //arrVariaveis não é iniciado quando o processo é criado
    processo->prioridade = 0;
    processo->estado = PRONTO;
    processo->tempoInicio = tempoSistema;
    processo->tempoCPU = 0;

    processo->arrPrograma = (Instrucao**) malloc(sizeof(Instrucao*));
    leInstrucoesArquivo("./data/init", processo->arrPrograma);

    *processoInit = processo;
}


// void copiaProcesso(ProcessoSimulado* processoPai, ProcessoSimulado processoFilho)
// {
//     processoFilho->pid = processoPai->pid;
//     processoFilho->ppid =  processoPai->ppid;
//     processoFilho->pc =  processoPai->pc;
//     processoFilho->prioridade = processoPai->prioridade;
//     processoFilho->estado =  processoPai->estado;
//     processoFilho->tempoInicio =  processoPai->tempoInicio;
//     processoFilho->tempoCPU =  processoPai->tempoCPU;

// }

//Funções para executar as instruções de um processo simulado

void imprimeProcesso(ProcessoSimulado processo)
{
    int opcao = 2;

    printf("Processo - pid %2d | ", processo.pid);
    printf("ppid %2d | ", processo.ppid);
    printf("pc %2d | ", processo.pc);
    printf("prioridade %d | ", processo.prioridade);
    imprimeEstado(processo.estado);
    printf("tempoInicio %d | ", processo.tempoInicio);
    printf("tempoCPU %d\n", processo.tempoCPU);

    printf("Escolha as informações para exibir do  processo");
    printf("\n1) Não exibir nenhuma;");
    printf("\n2) Variáveis do processo;");
    printf("\n3) Instruções do processo;");
    printf("\n4) Instruções e variáveis do processo;");
    printf("\n>> Escolha a opção: ");
    scanf("%d", &opcao);
    
    switch (opcao)
    {

        case 1:
        break;

        case 2:
            printf("Variaveis\n");
            break;
    
        case 3:
            imprimeArrPrograma(*(processo.arrPrograma));
        break;
    
        case 4:
            printf("Variaveis\n");
            imprimeArrPrograma(*(processo.arrPrograma));

        default:
            break;
    }
}

void imprimeEstado(Estado estado) {

    switch (estado)
    {
        case BLOQUEADO:
            printf("Estado: BLOQUEADO | ");
            break;

        case EXECUCAO:
            printf("Estado: EXECUCAO | ");
            break;

        case PRONTO:
            printf("Estado: PRONTO | ");
            break;
            
        default:
            break;
    }
} 


int* instrucaoN(int n){
    int* arrVariaveis = (int*) malloc(n * sizeof(int));
    return arrVariaveis;
}

int main()
{
    // Instrucao* programa;
    // leInstrucoesArquivo("./data/init", &programa);
    // imprimeArrPrograma(programa);
    
    ProcessoSimulado* processoInit;
    criaProcessoInit(&processoInit, 0);
    imprimeProcesso(*processoInit);

}

