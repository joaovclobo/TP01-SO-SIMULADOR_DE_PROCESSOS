#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#define MAXBUFFER 100

void escreverCaractereNoPipe(int fd, char caractere);
char lerCaractereDoPipe(int fd);
