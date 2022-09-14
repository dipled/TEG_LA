#include <stdio.h>
#include <stdlib.h>
#include "arq.h"
int main()
{
    struct vertice *lista;
    lista = cria();
    printf("v[2] - v[%d]\n",lista[2].primeiro->ligacao);
    destroi(lista);
    return 0;
}