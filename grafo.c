#include "arq.h"
#include <stdio.h>
#include <stdlib.h>
struct descritor *(cria)()
{
    FILE *fp = fopen("grafo.txt", "r");
    int n_vertices;
    fscanf(fp, "%d", &n_vertices);
    struct descritor *desc = malloc(sizeof(struct descritor));
    desc->quantidade_vertices = n_vertices;
    desc->lista = calloc(n_vertices, sizeof(struct vertice));
    desc->lista->primeiro = NULL;
    int v1, v2;
    while (1)
    {
        if(feof(fp)) //retorna um não 0 quando chega no fim do arquivo
            break;
        fscanf(fp, "%d %d", &v1, &v2);

        // Bloco de codigo que vai encadear a ligacao do primeiro vertice da dupla ordenada (aresta)

        struct aresta *novo = malloc(sizeof(struct aresta));
        novo->ligacao = v2;
        novo->proximo = NULL;
        if (desc->lista[v1 - 1].primeiro == NULL)
        {
            desc->lista[v1 - 1].primeiro = novo;
            desc->lista[v1 - 1].grau = 1;
        }
        else
        {
            desc->lista[v1 - 1].grau += 1;
            struct aresta *aux = malloc(sizeof(struct aresta));

            aux = desc->lista[v1 - 1].primeiro;
            while (aux->proximo != NULL)
            {
                aux = aux->proximo;
            }
            aux->proximo = novo;
        }

        // Bloco de codigo que vai encadear a ligacao do segundo vertice da dupla ordenada (aresta)

        struct aresta *novo2 = malloc(sizeof(struct aresta));
        novo2->ligacao = v1;
        novo2->proximo = NULL;
        if (desc->lista[v2 - 1].primeiro == NULL)
        {
            desc->lista[v2 - 1].grau += 1;
            desc->lista[v2 - 1].primeiro = novo2;
        }
        else
        {
            struct aresta *aux = malloc(sizeof(struct aresta));

            aux = desc->lista[v2 - 1].primeiro;
            while (aux->proximo != NULL)
            {
                aux = aux->proximo;
            }
            aux->proximo = novo2;
        }
    }
    return desc;
}

void destroi(struct descritor *desc)
{
    int tamanho = desc->quantidade_vertices;
    for (int i = 0; i < tamanho; i += 1)
    {
        if (desc->lista[i].primeiro == NULL)
            free(desc->lista[i].primeiro);
        else
        {
            struct aresta *aux = desc->lista[i].primeiro;

            while (aux->proximo != NULL)
            {
                desc->lista[i].primeiro = aux->proximo;
                free(aux);
                aux = desc->lista[i].primeiro;
            }
            free(desc->lista[i].primeiro);
        }
    }
    free(desc);
}

void printar_grafo(struct descritor *desc)
{
   int tamanho = desc->quantidade_vertices;
    for (int i = 0; i < tamanho; i += 1)
    {
        printf("v[%d]",i+1);
        struct aresta *aux = desc->lista[i].primeiro;

        while(aux != NULL)
        {
            printf("--%d",aux->ligacao);
            aux = aux->proximo;
        }
        printf("--/\n");
    }
}

void ordena()
{

}
void leitor()
{   
    ordena();
    FILE *fp = fopen("grafo.txt", "r");
    int dist=0;
    int v1,v2;
    int min,max;
    int num_vertices;
    double* vet = malloc(150*sizeof(double));

    //ler txt e botar no vetor

    for(int i=0; i<num_vertices; i++)
    {
        fscanf(fp, "%ld", vet[i]);
    }

    min = vet[0];
    max = vet[num_vertices];

    for(int i=0; i<num_vertices;i++)
    {
        v1 = vet[i];
        while(1)
        {
            fscanf(fp,"%ld", &v2);
            dist = ((v1 - v2)-min)/(max-min);
            if(dist<0.3)
            {
                fprintf(fp,"%ld %d", v1, v2);
            }
        }
        

    }
}