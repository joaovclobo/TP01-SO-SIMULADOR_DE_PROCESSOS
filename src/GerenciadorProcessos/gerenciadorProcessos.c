#include "gerenciadorProcessos.h"
#include "../Pipe/pipe.h"
#define MAXBUFFER 100

void gerenciadorProcessos(int fd[2])
{
    lerDoPipe(fd);
}