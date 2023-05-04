#include "pipe.h"

//TODO - apagar estes prints???

void escreverCaractereNoPipe(int fd, char caractere)
{
    write(fd, &caractere, sizeof(char));
    printf("Caractere escrito no pipe: %c\n", caractere);
}

char lerCaractereDoPipe(int fd)
{
    char caractere;
    read(fd, &caractere, sizeof(char));

    printf("Caractere lido no pipe: %c\n", caractere);
    
    return caractere;
}
