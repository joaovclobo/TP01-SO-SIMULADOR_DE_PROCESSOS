#include "./src/ProcessoControle/processoControle.h"
#include "./src/ProcessoImpressao/processoImpressao.h"
#include <sys/wait.h>
#include <signal.h>

int impressaoExecutando = 1;
void semaforoImpressao(int signum)
{
    impressaoExecutando = 0;
}

int main(int argc, char **argv)
{
    int fd[2];
    char comando = '!';
    FILE *arquivoDeEntrada;
    int numCPUs = atoi(argv[1]);
    int tipoEscalonamento = atoi(argv[2]);
    GerenciadorProcessos *gerenciador = inicializaGerenciador(numCPUs, tipoEscalonamento);

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
                    signal(SIGUSR1, semaforoImpressao);

                    while (impressaoExecutando)
                    {
                        sleep(1);
                    }
                    impressaoExecutando = 1;
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
                    // impressãoGeral(gerenciador);
                }
                else
                {

                    pidImpressao = fork();
                    if (pidImpressao < 0)
                    {
                        printf("ERRO NO FORK() IMPRESSAO\n");
                    }
                    if (pidImpressao > 0)
                    {
                        // ESPERANDO O TERMINO DO PROCESSO DE IMPRESSÃO
                        wait(NULL);
                        kill(getppid(), SIGUSR1);
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
                                // imprimirGerenciadorProcessos(gerenciador);
                            }
                        }

                        exit(0);
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