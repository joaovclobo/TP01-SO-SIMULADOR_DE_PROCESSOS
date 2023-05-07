#include "cpu.h"

CPU* inicializaCPU()
{
    CPU* cpu;
    //TODO - definir um numero invalido
    cpu->pid = NUMVAZIO;
    cpu->arrPrograma = (Instrucao**) malloc(sizeof(Instrucao));
    cpu->pcProgramaAtual = NUMVAZIO;
    cpu->arrVariaveis = (Instrucao**) malloc(sizeof(Instrucao));
    cpu->quantum = 0;

}

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