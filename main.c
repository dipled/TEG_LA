#include <stdio.h>
#include <stdlib.h>
#include "arq.h"
int main()
{
    struct descritor *desc;
    desc = cria();
    printar_grafo(desc);
    destroi(desc);
    cria_tabela();
    return 0;
}