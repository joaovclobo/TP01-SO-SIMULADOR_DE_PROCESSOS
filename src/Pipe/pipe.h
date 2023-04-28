#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#define MAXBUFFER 100

void escreverNoPipe(int fd[2], char letra);
void lerDoPipe(int fd[2]);