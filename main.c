#include "./src/ProcessoControle/processoControle.h"
#include "./src/GerenciadorProcessos/gerenciadorProcessos.h"

int main(int argc, char **argv)
{
    int fd[2];
    pipe(fd);

    controle(fd);
    // gerenciadorProcessos(fd);

    return 0;
}