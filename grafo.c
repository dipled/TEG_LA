#include "arq.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
struct descritor *(cria)()
{
    FILE *fp = fopen("criat.txt", "r");
    if (fp == NULL)
        return NULL;
    int n_vertices;
    fscanf(fp, "%d", &n_vertices);
    struct descritor *desc = malloc(sizeof(struct descritor));
    desc->quantidade_vertices = n_vertices;
    desc->lista = calloc(n_vertices, sizeof(struct vertice));
    desc->lista->primeiro = NULL;
    int v1, v2;
    while (!feof(fp))
    {
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
        if (v1 != v2)
        {

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
    }
    if (fp != NULL)
        fclose(fp);
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
        printf("v[%d]", i + 1);
        struct aresta *aux = desc->lista[i].primeiro;

        while (aux != NULL)
        {
            printf("--%d", aux->ligacao);
            aux = aux->proximo;
        }
        printf("--/\n");
    }
}

void leitor(double **matrix) // le a matriz e cria um txt
{
    char buffer[100];
    FILE *fp = fopen("criatxt2.txt", "w");
    fgets(buffer, 100, fp); // Ignorando a primeira linha

    for (int i = 0; i < 15; i++)
    {
        for (int j = i+1; j < 15; j++)
        {
            if (matrix[i][j] < 0.3)
                fprintf(fp, "%d %d\n", i+1, j+1);
        }
    }
}

double **cria_tabela()
{
    FILE *fp = fopen("teste.csv", "r");
    double maior = 0; // para fazer a normalização
    double menor = 0;
    double dist = 0; // distancia entre nodos
    double **matrix = malloc(15 * sizeof(double *));
    if (fp == NULL)
        return NULL;
    char buffer[100];
    fpos_t segunda_linha;
    fpos_t linha_atual;
    fgetpos(fp, &linha_atual);
    fgets(buffer, 100, fp);      // Ignorando a ultima coluna
    fgetpos(fp, &segunda_linha); // salva a segunda linha pra sempre voltar nela no segundo while
    fsetpos(fp, &linha_atual);
    double x, y, z, w, esp, x2, y2, z2, w2, esp2;

    int i = 0, j = 1;
    while (i < 15)
    {
        fgets(buffer, 100, fp); // Ignorando a linha
        fgetpos(fp, &linha_atual);
        fscanf(fp, "%lf, %lf, %lf, %lf,", &x, &y, &z, &w);
        fgets(buffer, 100, fp); // Ignorando a ultima coluna
        matrix[i] = malloc(15 * sizeof(double));
        printf("\n");

        fsetpos(fp, &segunda_linha);
        while (j < 15)
        {

            fscanf(fp, "%lf, %lf, %lf, %lf,", &x2, &y2, &z2, &w2);
            fgets(buffer, 100, fp);
            dist = sqrt(pow((x - x2), 2) + pow((y - y2), 2) + pow((z - z2), 2) + pow((w - w2), 2));
            matrix[i][j] = dist;
            if (i == 0)
            {
                maior = dist;
                menor = dist;
            }
            else if (dist < menor)
            {
                menor = dist;
            }
            else if (dist > maior)
            {
                maior = dist;
            }
            printf("i = [%d] j = [%d] - %lf\n", i, j, matrix[i][j]);

            j++;
        }
        fsetpos(fp, &linha_atual);
        i++;
        j = i +1;
    }
    matrix = normaliza(matrix, menor, maior);
    return matrix;
}

double **normaliza(double **matrix, double menor, double maior)
{
    printf("\n\n\n");

    for (int i = 0; i < 15; i++)
    {
        for (int j = i+1; j < 15; j++)
        {
            matrix[i][j] = (matrix[i][j] - menor) / (maior - menor);
            printf("i = [%d] j = [%d] - %lf\n", i, j, matrix[i][j]);
        }
    }
    return matrix;
}
