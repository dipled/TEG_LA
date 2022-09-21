#include <stdio.h>
#include <stdlib.h>
#include "arq.h"

int main()
{
    struct descritor *desc;
    desc = cria();
    int sumgraus = 0;
    for(int i = 0; i < 150; i += 1)
    {
        printf("%d\n",desc->lista[i].grau);
        sumgraus += desc->lista[i].grau;
    }
    printf("\n\n%d\n\n",sumgraus);
    //printar_grafo(desc);
    //destroi(desc);
    //double **matrix = cria_tabela();
    //leitor(matrix);
    return 0;
}