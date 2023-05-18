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

    GerenciadorProcessos* gerenciador  = inicializaGerenciador(numCPUs, tipoEscalonamento);

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

    if (pid > 0) // processo pai - APENAS ESCREVE NO PIPE
    {
        // close(fd[0]);

        while (1)
        {
            if (opcao == 2)
            {
                comando = controle(arquivoDeEntrada, opcao);
                escreverCaractereNoPipe(fd[1], comando);
            }
            else
            {
                scanf(" %c", &comando); // lendo da entrada padrão para escrever no pipe
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

            if (comando == 'M') // encerra as escritas
            {
                break;
            }
        }
        wait(NULL);
        // close(fd[1]);
    }
    else // processo filho do pai aí em cima - APENAS LÊ NO PIPE
    {
        // close(fd[1]);

        while (1)
        {

            comando = lerCaractereDoPipe(fd[0]);

            if (comando == 'U')
            {
                gerenciadorProcessos(gerenciador, comando);
            }

            else if (comando == 'I') // ler da entrada padrão
            {
                if (opcao == 2)
                {
                    impressãoGeral(gerenciador);
                }
                else
                {
                    /* Como tenho pai e filho lendo e escrevendo da entrada padrão concorrentemente,
                preciso desse novo processo pra que tudo isso ocorra de forma sincronizada*/
                    pidImpressao = fork(); // cria um novo processo
                    if (pidImpressao < 0)
                    {
                        printf("ERRO NO FORK() IMPRESSAO\n");
                    }
                    if (pidImpressao > 0) // quer dizer que é o pai, o filho da primeira chamada que leu I
                    {
                        // ESPERANDO O TERMINO DO PROCESSO DE IMPRESSÃO
                        wait(NULL); // o pai do processo impressão vai parar e esperar o impressão executar
                        kill(getppid(), SIGUSR1);
                        sleep(1);
                    }
                    else
                    {
                        // PROCESSO IMPRESSÃO
                        while (opcaoImpressao != 3)
                        {
                            opcaoImpressao = menuImpressao(); // quero ler o que vai imprimir da entrada padrão

                            if (opcaoImpressao == 1)
                            {
                                imprimirGerenciadorProcessos(gerenciador);
                            }
                            else if (opcaoImpressao == 2)
                            {
                                imprimirProcessoSimulado(gerenciador);
                            }
                        }

                        exit(0); // acaba o impressão e volta pra onde parou (ele parou no wait(NULL))
                    }
                }
            }

            if (comando == 'M')
            {
                break;
            }
        }
        // close(fd[0]);
    }
    return 0;
}