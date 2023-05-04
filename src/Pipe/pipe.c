#include "pipe.h"

void escreverCaractereNoPipe(int fd, char caractere)
{
    write(fd, &caractere, sizeof(char));

}

char lerCaractereDoPipe(int fd)
{
    char caractere;
    read(fd, &caractere, sizeof(char));
   
    return caractere;
}
