#include "./src/ProcessoControle/processoControle.h"
#include "./src/ProcessoImpressao/processoImpressao.h"
//#include "./src/GerenciadorProcessos/gerenciadorProcessos.h"
#include "./src/EstruturasDeDados/tesFila.h"
#include <time.h>

int main(int argc, char **argv)
{
    int fd[2];
    char comando = '!';
    FILE *arquivoDeEntrada;
    GerenciadorProcesso* gerenciador;
    // Fila* filaPronto = criaFila();
    TipoFila filaPronto;
    FFVazia(&filaPronto);
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

        while (1)
        {
            
            comando = lerCaractereDoPipe(fd[0]);
            gerenciadorProcessos(gerenciador, comando);
            CPU *cpu = inicializaCPU();
            
            
            ProcessoSimulado *processoInit;
            
            criaProcessoInit(&processoInit);
            carregaProcesso(cpu, processoInit);
            for(int j = 0; j < 3; j++)
            {
                executaProxInstrucao(cpu, 0, gerenciador->tabelaProcessos);
            }
            ProcessoSimulado *processo1 = copiaProcesso(*processoInit, 10, 1); 
            ProcessoSimulado *processo2 = copiaProcesso(*processoInit, 20, 2);
            ProcessoSimulado *processo3 = copiaProcesso(*processoInit, 30, 3);
            ProcessoSimulado *processo4 = copiaProcesso(*processoInit, 40, 4);
            ProcessoSimulado *processo5 = copiaProcesso(*processoInit, 50, 5);
            processo1->prioridade = 1;
            processo2->prioridade = 2;
            processo3->prioridade = 3;
            processo4->prioridade = 4;
            processo5->prioridade = 5;
            //ISSO TUDO AQUI EM CIMA, É SÓ INICIALIZAR OS PROCESSOS NORMAL

            // Enfileira(processo1->prioridade, processo1->pid, processo1->tempoCPU, &filaPronto);
            // Enfileira(processo4->prioridade, processo4->pid, processo4->tempoCPU, &filaPronto);
            // Enfileira(processo2->prioridade, processo2->pid, processo2->tempoCPU, &filaPronto);
            // Enfileira(processo5->prioridade, processo5->pid, processo5->tempoCPU, &filaPronto);
            // Enfileira(processo3->prioridade, processo3->pid, processo3->tempoCPU, &filaPronto);

            //enfileira(filaPronto,processo1->prioridade, processo1->pid, processo1->tempoCPU);
            // printf("\nTamanho da fila = %d\n", filaPronto->tamanho);
            enfileiraPorPrioridade(&filaPronto,processo4->prioridade, processo4->pid, processo4->tempoCPU);
            enfileiraPorPrioridade(&filaPronto,processo2->prioridade, processo2->pid, processo2->tempoCPU);
            enfileiraPorPrioridade(&filaPronto,processo5->prioridade, processo5->pid, processo5->tempoCPU);
            enfileiraPorPrioridade(&filaPronto,processo3->prioridade, processo3->pid, processo3->tempoCPU);
            imprimeFila(&filaPronto);
            
            //imprimeCPU(*cpu);
            // if (comando == 'I')
            // {
            //     printf("\n\n======== INFORMAÇÕES SOBRE O SISTEMA ========\n");
            //     imprimeGerenciador(&gerenciador);
            //     // imprimeControle();
            //     // imprimeSimulado();
            // }

            // else 
            if (comando == 'M')
            {
                break;
            }
        }
        close(fd[0]);

    }
    return 0;
}
