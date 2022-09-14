#include "arq.h"
#include <stdio.h>
#include <stdlib.h>
struct vertice *(cria)()
{
    FILE *fp = fopen("grafo.txt", "r");
    int n_vertices;
    int n_arestas;
    fscanf(fp, "%d %d", &n_vertices, &n_arestas);
    struct vertice *lista = calloc(n_vertices, sizeof(struct vertice));
    lista->primeiro = NULL;
    int v1, v2;
    while (n_arestas)
    {
        n_arestas -= 1;
        fscanf(fp, "%d %d", &v1, &v2);

        // Bloco de codigo que vai encadear a ligacao do primeiro vertice da dupla ordenada (aresta)

        struct aresta *novo = malloc(sizeof(struct aresta));
        novo->ligacao = v2;
        novo->proximo = NULL;
        if (lista[v1 - 1].primeiro == NULL)
        {
            lista[v1 - 1].primeiro = novo;
            lista[v1 - 1].grau = 1;
        }
        else
        {
            lista[v1 - 1].grau += 1;
            struct aresta *aux = malloc(sizeof(struct aresta));

            aux = lista[v1 - 1].primeiro;
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
        if (lista[v2 - 1].primeiro == NULL)
        {
            lista[v2 - 1].grau += 1;
            lista[v2 - 1].primeiro = novo2;
        }
        else
        {
            struct aresta *aux = malloc(sizeof(struct aresta));

            aux = lista[v2 - 1].primeiro;
            while (aux->proximo != NULL)
            {
                aux = aux->proximo;
            }
            aux->proximo = novo2;
        }
    }
    return lista;
}

void destroi(struct vertice *lista)
{
    int tamanho = sizeof(lista);
    for (int i = 0; i < tamanho; i += 1)
    {
        if (lista[i].primeiro == NULL)
            free(lista[i].primeiro);
        else
        {
            struct aresta *aux = lista[i].primeiro;

            while (aux->proximo != NULL)
            {
                lista[i].primeiro = aux->proximo;
                free(aux);
                aux = lista[i].primeiro;
            }
            free(lista[i].primeiro);
        }
    }
}