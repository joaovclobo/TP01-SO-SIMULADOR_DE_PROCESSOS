#include "./src/ProcessoControle/processoControle.h"
#include "./src/GerenciadorProcessos/gerenciadorProcessos.h"
#include "./src/Menu/menu.h"

int main(int argc, char **argv)
{
    int fd[2];
    char comando = '!';
    FILE* arquivoDeEntrada;

    int opcao = MenuInicial(&arquivoDeEntrada);

    if (pipe(fd) == -1) {
        perror("Erro ao criar o pipe");
        return 1;
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("Erro ao criar o processo");
        return 1;
    }

    if (pid > 0) {
        close(fd[0]);

        while (1) {
            comando = controle(arquivoDeEntrada, opcao);
            escreverCaractereNoPipe(fd[1], comando);
            
            if (comando == 'M') {
                break;
            }
        }
        close(fd[1]);

    } else {
        close(fd[1]);

        while (1) {
            comando = lerCaractereDoPipe(fd[0]);
            gerenciadorProcessos(comando);

            if (comando == 'M') {
                break;
            }
        }
        close(fd[0]);

    }
    return 0;

}
