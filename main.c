#include "./src/ProcessoControle/processoControle.h"
#include "./src/ProcessoImpressao/processoImpressao.h"
//#include "./src/GerenciadorProcessos/gerenciadorProcessos.h"
#include <time.h>

int main(int argc, char **argv)
{
    int fd[2];
    char comando = '!';
    FILE *arquivoDeEntrada;
    GerenciadorProcesso* gerenciador;
    gerenciador = inicializaGerenciador();

    int opcao = MenuInicial(&arquivoDeEntrada);

    if (pipe(fd) == -1)
    {
        perror("Erro ao criar o pipe");
        return 1;
    }

    pid_t pid = fork();

    if (pid == -1)
    {
        perror("Erro ao criar o processo");
        return 1;
    }

    if (pid > 0)
    {
        close(fd[0]);

        while (1)
        {
            comando = controle(arquivoDeEntrada, opcao);
            escreverCaractereNoPipe(fd[1], comando);

            if (comando == 'M')
            {
                break;
            }
        }
        close(fd[1]);
    }
    else
    {
        close(fd[1]);
        
        //copiaProcesso(&processo1, *processoInit, 10, 1);
        //copiaProcesso(&processo2, *processoInit, 20, 2); 
        //copiaProcesso(&processo3, *processoInit, 30, 3);
        //copiaProcesso(&processo4, *processoInit, 40, 4);
        //copiaProcesso(&processo5, *processoInit, 50, 5);  
        //printf("quebrou nao");
        //insereProcessoTabela(processoInit, gerenciador);
        //insereProcessoTabela(processo1, gerenciador);
        //insereProcessoTabela(processo2, gerenciador);
        //insereProcessoTabela(processo3, gerenciador);
        //insereProcessoTabela(processo4, gerenciador);
        //insereProcessoTabela(processo5, gerenciador);
        //imprimeTabelaProcesso(gerenciador->tabelaProcessos);

        //while (1)
        for(int i = 0; i < 1; i++)
        {
            comando = lerCaractereDoPipe(fd[0]);
            gerenciadorProcessos(gerenciador, comando);
            CPU *cpu = inicializaCPU();
            Fila* filaPronto = criaFila();
            
            ProcessoSimulado *processoInit;
            ProcessoSimulado *processo1;
            ProcessoSimulado *processo2;
            ProcessoSimulado *processo3;
            ProcessoSimulado *processo4;
            ProcessoSimulado *processo5;
            criaProcessoInit(&processoInit, 1);
            carregaProcesso(cpu, processoInit);
            for(int j = 0; j < 3; j++)
            {
                executaProxInstrucao(cpu, 0, gerenciador->tabelaProcessos);
            }
            copiaProcesso(&processo1, *processoInit, 10, 1);
            copiaProcesso(&processo2, *processoInit, 20, 2); 
            copiaProcesso(&processo3, *processoInit, 30, 3);
            copiaProcesso(&processo4, *processoInit, 40, 4);
            copiaProcesso(&processo5, *processoInit, 50, 5);  
            insereProcessoTabela(processoInit, gerenciador);
            insereProcessoTabela(processo1, gerenciador);
            insereProcessoTabela(processo2, gerenciador);
            insereProcessoTabela(processo3, gerenciador);
            insereProcessoTabela(processo4, gerenciador);
            insereProcessoTabela(processo5, gerenciador);
            imprimeTabelaProcesso(gerenciador->tabelaProcessos);
            //imprimeCPU(*cpu);
            // if (comando == 'I')
            // {
            //     printf("\n\n======== INFORMAÇÕES SOBRE O SISTEMA ========\n");
            //     imprimeGerenciador(&gerenciador);
            //     // imprimeControle();
            //     // imprimeSimulado();
            // }

            // else if (comando == 'M')
            // {
            //     break;
            // }
        }
        close(fd[0]);

        
    }
    return 0;
}
