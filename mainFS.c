#include "./src/ProcessoControle/processoControle.h"
#include "./src/ProcessoImpressao/processoImpressaoFS.h"
#include <sys/wait.h>
#include <signal.h>

int impressaoExecutando = 0;
void semaforoImpressao(int signum)
{
    impressaoExecutando = 0; // INDICA QUE O PROCESSO IMPRESSÃO NÃO VAI EXECUTAR MAIS
}

int main(int argc, char **argv)
{
    int fd[2];
    char comando = '!';
    FILE *arquivoDeEntrada;
    int numCPUs = atoi(argv[1]);
    int quantum = atoi(argv[2]);
    GerenciadorProcessos *gerenciador = inicializaGerenciador(numCPUs, quantum);

    int opcao = MenuInicial(&arquivoDeEntrada);
    int opcaoImpressao = 0;
    int PID;
    int status;

    if (pipe(fd) == -1)
    {
        perror("Erro ao criar o pipe");
        return 1;
    }

    pid_t pidImpressao;
    pid_t pid = fork();

    if (pid == -1)
    {
        perror("Erro ao criar o processo");
        return 1;
    }

    if (pid > 0)
    {
        // A função signal quando recebe o sinal SIGUSR1 executa o que está dentro de semaforoImpressao
        signal(SIGUSR1, semaforoImpressao); // Ela apenas registra o sinal do processo impressão

        while (1)
        {
            if (opcao == 2)
            {
                comando = controle(arquivoDeEntrada, opcao);
                escreverCaractereNoPipe(fd[1], comando);
            }
            else
            {
                scanf(" %c", &comando);
                escreverCaractereNoPipe(fd[1], comando);

                if (comando == 'I')
                {
                    impressaoExecutando = 1; // PROCESSO IMPRESSÃO PODE EXECUTAR

                    while (impressaoExecutando)
                    {
                        sleep(1);
                    }
                }
            }

            if (comando == 'M')
            {
                break;
            }
        }
        wait(NULL);
    }
    else
    {

        while (1)
        {

            comando = lerCaractereDoPipe(fd[0]);

            if (comando == 'U')
            {
                gerenciadorProcessos(gerenciador, comando);
            }

            else if (comando == 'I')
            {
                if (opcao == 2)
                {
                    impressaoArquivo(gerenciador);
                }
                else
                {

                    pidImpressao = fork();
                    if (pidImpressao < 0)
                    {
                        printf("ERRO NO FORK() IMPRESSAO\n");
                    }

                    // ABAIXO É COMO SE FOSSE UMA BIFURCAÇÃO
                    if (pidImpressao > 0) // é o processo filho do processo de leitura do pipe
                    {
                        wait(NULL); // ESPERANDO O TERMINO DO PROCESSO DE IMPRESSÃO
                        kill(getppid(), SIGUSR1); // ENVIA O SINAL PRO PROCESSO QUE LÊ DO PIPE
                        sleep(1);
                    }
                    else
                    {
                        // PROCESSO IMPRESSÃO
                        while (opcaoImpressao != 2)
                        {
                            opcaoImpressao = menuImpressao();

                            if (opcaoImpressao == 1)
                            {
                                imprimirGerenciadorProcessos(gerenciador);
                            }
                        }

                        exit(0); // VOLTA PARA O WAIT(NULL)
                    }
                }
            }

            if (comando == 'M')
            {
                break;
            }
        }
    }
    return 0;
}