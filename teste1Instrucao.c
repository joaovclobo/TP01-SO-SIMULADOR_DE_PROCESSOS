#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXBUFFER 100
#define MAXINTRUC 100
#define NUMVAZIO -1
#define TXTVAZIO "#####"

int MenuInicial(FILE** arquivoDeEntrada);
int MenuImpressaoProcesso();
FILE* abreArquivoRead(char* nomeArquivo);

void flag(int i);

int MenuInicial(FILE** arquivoDeEntrada)
{
    int opcao;

    do
    {
   
    printf("\n\n=========== MENU ===========");
    printf("\n1) Entrada padrão");
    printf("\n2) Entrada por arquivo");
    printf("\n>> Escolha a opção: ");
    scanf("%d", &opcao);

    if (opcao == 1 ){
        printf("\nEntre com um dos comandos a seguir para:\n");
        printf("U) Indicar o fim de uma unidade de tempo;\n");
        printf("I) Imprimir o estado atual do sistema;\n");
        printf("M) Imprimir o tempo médio de resposta e finalizar o sistema.\n");

    } else if (opcao == 2){
        *arquivoDeEntrada = abreArquivoRead("./data/comandosControle");

    } else {
        printf("Opção inválida! Tente novamente.\n");

    }
    
    } while (opcao != 1 && opcao != 2);

    return opcao;
}

int MenuImpressaoProcesso()
{   
    int opcao = 1;

    printf("\n1) Não exibir nenhuma;");
    printf("\n2) Variáveis do processo;");
    printf("\n3) Instruções do processo;");
    printf("\n4) Instruções e variáveis do processo;");
    printf("\n>> Escolha a opção: ");
    scanf("%d", &opcao);

    return opcao;
    
}

FILE* abreArquivoRead(char* nomeArquivo)
{

    FILE *fptr;

    printf("\tAbrindo o arquivo: %s\n", nomeArquivo);
    
    fptr = fopen(nomeArquivo, "r");

    if (fptr == NULL){
        printf("\nERRO: Arquivo não encontrado!\nPor favor, insira um arquivo válido!\n");
        return NULL;

    } else{
        return fptr;

    }
}

//TODO - apagar dps do fim

void flag(int i)
{
    printf("\n------------------- FLAG %d -------------------\n", i);
}

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

void inicializaInstrucao(char *instrucaoLida, Instrucao* instrucao)
{
    char* token;

    token = strtok(instrucaoLida, " ");
    
    instrucao->tipoDeInstrucao = token[0];
    instrucao->parametroNumerico1 = NUMVAZIO;
    instrucao->parametroNumerico2 = NUMVAZIO;
    strcpy(instrucao->parametroTexto, TXTVAZIO);

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
    int i = 0;

    Instrucao* arrPrograma = (Instrucao*) malloc(MAXINTRUC * sizeof(Instrucao));
    
    char* cadaLinha = malloc(MAXBUFFER * sizeof(char));

    FILE* arquivoDeEntrada = abreArquivoRead(caminhoArquivo);

    while (fgets(cadaLinha, MAXBUFFER, arquivoDeEntrada) != NULL)
    {   
        cadaLinha[strcspn(cadaLinha, "\n")] = '\0';
        inicializaInstrucao(cadaLinha, arrPrograma+i);
        i++;

    }

    *programa = arrPrograma;
}

void copiaInstrucao(Instrucao* novaInstrucao, Instrucao* instrucaoBase)
{
    novaInstrucao->tipoDeInstrucao = instrucaoBase->tipoDeInstrucao;
    novaInstrucao ->parametroNumerico1 = instrucaoBase->parametroNumerico1;
    novaInstrucao->parametroNumerico2 = instrucaoBase->parametroNumerico2;
    strcpy(novaInstrucao->parametroTexto, instrucaoBase->parametroTexto);
}

void imprimeInstucao(Instrucao instrucao)
{
    printf("    └ Instrução -  Tipo %c", instrucao.tipoDeInstrucao);
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

void copiaProcesso(ProcessoSimulado** novoProcesso, ProcessoSimulado processoPai, int tempoAtualSistema);
void copiaVariaveis(int* arrVariaveisBase, int* arrVariaveisNovo, int tamanho);
void copiaArrPrograma(Instrucao** arrNovo, Instrucao* arrBase);

int numeroVariaveis(ProcessoSimulado processo);

void imprimeProcesso(ProcessoSimulado processo, int opcao);
void imprimeEstado(Estado estado);
void imprimeVariaveis(int* arrVariaveis, int tamanho);

void criaProcessoInit(ProcessoSimulado** processoInit, int tempoSistema)
{
    ProcessoSimulado* processo = (ProcessoSimulado*) malloc(sizeof(ProcessoSimulado));

    processo->pid = 0;
    processo->ppid = 0;
    processo->pc = (int*) malloc(sizeof(int));
    *(processo->pc) = 0;
    processo->prioridade = 0;
    processo->estado = PRONTO;
    processo->tempoInicio = tempoSistema;
    processo->tempoCPU = 0;

    processo->arrPrograma = (Instrucao**) malloc(sizeof(Instrucao));
    leInstrucoesArquivo("./data/init", processo->arrPrograma);

    processo->arrVariaveis = (int*) malloc(numeroVariaveis(*processo) * sizeof(int));

    //TODO - APAGAR ISSO PELAMOR DE DEUS

    for (int i = 0; i < 5; i++)
    {
        processo->arrVariaveis[i] = (i+3)*10;
    }

    *processoInit = processo;
    
}

void copiaProcesso(ProcessoSimulado** novoProcesso, ProcessoSimulado processoPai, int tempoAtualSistema)
{
    ProcessoSimulado* processo = (ProcessoSimulado*) malloc(sizeof(ProcessoSimulado));

    //TODO - Confirmar com o daniel como sera
    processo->pid = processoPai.pid;
    processo->ppid = processoPai.ppid;

    //+1 porque deve pular exatamente uma instrução
    processo->pc = (int*) malloc(sizeof(int));
    *(processo->pc) = *(processoPai.pc) + 1; 

    processo->arrVariaveis = (int*) malloc(numeroVariaveis(processoPai) * sizeof(int));
    copiaVariaveis(processoPai.arrVariaveis, processo->arrVariaveis, numeroVariaveis(processoPai));

    processo->prioridade = processoPai.prioridade;
    processo->estado = PRONTO;
    processo->tempoInicio = tempoAtualSistema;
    processo->tempoCPU = 0;

    processo->arrPrograma = (Instrucao**) malloc(sizeof(Instrucao));
    copiaArrPrograma(processo->arrPrograma, *(processoPai.arrPrograma));

    *novoProcesso = processo;

}

void copiaVariaveis(int* arrVariaveisBase, int* arrVariaveisNovo, int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        arrVariaveisNovo[i] = arrVariaveisBase[i];
    }
}

void copiaArrPrograma(Instrucao** arrNovo, Instrucao* arrBase)
{
    Instrucao* arrPrograma = (Instrucao*) malloc(MAXINTRUC * sizeof(Instrucao));

    int i = 0;

    while (arrBase[i-1].tipoDeInstrucao != 'T')
    {
        copiaInstrucao(&arrPrograma[i], &arrBase[i]);
        i++;
    }

    *arrNovo = arrPrograma;
}

int numeroVariaveis(ProcessoSimulado processo)
{
    return (processo.arrPrograma)[0]->parametroNumerico1;
}


void imprimeProcesso(ProcessoSimulado processo, int opcao)
{

    printf("-> Processo - PID %2d | ", processo.pid);
    printf("PPID %2d | ", processo.ppid);
    printf("PC %2d | ", *(processo.pc));
    printf("Prioridade %d | ", processo.prioridade);
    imprimeEstado(processo.estado);
    printf("Tempo de inicio %2d | ", processo.tempoInicio);
    printf("Tempo de CPU %2d\n", processo.tempoCPU);
    
    switch (opcao)
    {

        case 1:
        break;

        case 2:
            imprimeVariaveis(processo.arrVariaveis, numeroVariaveis(processo));
            break;
    
        case 3:
            imprimeArrPrograma(*(processo.arrPrograma));
        break;
    
        case 4:
            imprimeVariaveis(processo.arrVariaveis, numeroVariaveis(processo));
            imprimeArrPrograma(*(processo.arrPrograma));

        default:
            break;
    }
    putchar('\n');

}

void imprimeEstado(Estado estado)
{
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

void imprimeVariaveis(int* arrVariaveis, int tamanho)
{
    printf("   └ Variáveis - ");

    for (int i = 0; i < tamanho; i++)
    {
        printf("%d ", arrVariaveis[i]);

    }
    putchar('\n');

}

typedef struct CPU
{
    int *pidProcessoAtual;
    Instrucao **programaProcessoAtual;
    int *pcProcessoAtual;
    int **variaveisProcessoAtual;
    int fatiaQuantum;       //Quanto do quantum de tempo já foi usada pelo processo em execução
} CPU;

void inicializaCPU(CPU* cpu);
void trocaPrograma(CPU* cpu, ProcessoSimulado* processoAtual);
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


void inicializaCPU(CPU* cpu)
{   
    cpu = (CPU*) malloc(sizeof(CPU));
    
    cpu->pidProcessoAtual = (int*) malloc(sizeof(int));
    *cpu->pidProcessoAtual = 57;
    cpu->pcProcessoAtual = (int*) malloc(sizeof(int));

    cpu->programaProcessoAtual = (Instrucao**) malloc(sizeof(Instrucao));
    cpu->variaveisProcessoAtual = (int**) malloc(sizeof(int));

    cpu->fatiaQuantum = 0;

}

void trocaPrograma(CPU* cpu, ProcessoSimulado* processoAtual)
{
    flag(0);

    printf("\n ------------ %d ------------------\n", *(cpu->pidProcessoAtual));

    // cpu->pidProcessoAtual = &(processoAtual->pid);

    // cpu->pcProcessoAtual = processoAtual->pc;

    // cpu->programaProcessoAtual = processoAtual->arrPrograma;
    // cpu->variaveisProcessoAtual = &processoAtual->arrVariaveis;

    // cpu->fatiaQuantum = 0;

}

void imprimeCPU(CPU cpu)
{   

    printf("CPU processando o processo: PID: %2d ", *cpu.pidProcessoAtual);
    printf("PC: %d", *cpu.pcProcessoAtual);
    // imprimeArrPrograma(*(cpu.arrProcessoAtual));
    //TODO - mudar o numero de variáveis
    // imprimeVariaveis(cpu.arrVariaveisProcessoAtual, 2);
    printf("Fatia do quantum já executado: %d", cpu.fatiaQuantum);

}

//Instruçẽos de programa que são processadas na CPU

int *instrucaoN(int n)
{
    // Função N declara e aloca um vetor de “n” posições dinamicamente e
    // retorna um ponteiro para este vetor (vetorVariaveis);

    int *vetorPosicoes;
    vetorPosicoes = (int *)malloc(n * sizeof(int));
    if (vetorPosicoes == NULL)
    {
        printf("Erro ao alocar memória");
        exit(1);
    }
    return vetorPosicoes;
}


void instrucaoD(int x, int *vetorPosicoes)
{
    // Função D “seta” 0 nos índices na posição x do vetor.
    vetorPosicoes[x] = 0;
}

void instrucaoV(int x, int n, int *vetorPosicoes)
{
    // V “seta” n nos índice x do vetor.
    vetorPosicoes[x] = n;
}

void instrucaoA(int x, int n, int *vetorPosicoes)
{
    // A soma n ao valor à variável no índice x.
    vetorPosicoes[x] += n;
}

void instrucaoS(int x, int n, int *vetorPosicoes){
    // 	S subtrai n ao valor à variável no índice x.
    vetorPosicoes[x] = vetorPosicoes[x] - n;
}

int instrucaoB(int n)
{
    // TO DO: escalonador responsavel por mudar o processo de bloqueado para pronto e de pronto
    // para em execução

    // manda um comando para bloquear o processo e esperar n unidades de tempo e
    // depois volta ele para “Pronto”. (Simula entrada e saída?)
    //chamar as funções enfileira dos estadoPronto e estadoBloqueado?
}

void instrucaoT()
{
    //	Termina o processo (Manda “encerrei” p/ o gerenciador de processo).
}

//TODO - esta função além de duplicar o processo que está na CPU deve incrementar em n o PC deste
void instrucaoF(int n)
{
    // Inicia outro processo Filho.
    // Filho - Copia exata do pai.
    // Filho - Executa após as próximas instruções do pai.
    // Pai - Pula n instruções depois de ler um comando F n (aumenta o PC do processo
    // executando em n na CPU).
}

void instrucaoR(char *nomeDoArquivo)
{
    // PC aponta pro PC do novo processo.
}




int main()
{
    CPU* cpu;
    
    inicializaCPU(cpu);
    
    ProcessoSimulado* processoInit;
    criaProcessoInit(&processoInit, 0);
    printf("Processo pai: \n");

    imprimeProcesso(*processoInit, 1);

    trocaPrograma(cpu, processoInit);
    // imprimeCPU(*cpu);
}

