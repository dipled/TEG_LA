#include <stdio.h>
#include <stdlib.h>
#include "arq.h"
int main()
{
    struct vertice *lista;
    lista = cria();
    printar_grafo(lista);
    destroi(lista);
    return 0;
}