//O arquivo "grafo.txt" deve conter na primeira linha o numero de vertices seguido do numero de arestas
//Nas proximas linhas, o arquivo deve apresentar o numero do primeiro vertice, seguido do numero do segundo, indicando uma aresta
//existente entre esses dois vertices
struct vertice
{
    struct aresta *primeiro;
    int grau;

};
struct aresta
{
    int ligacao;
    struct aresta *proximo;
};
//Definicao das funcoes
struct vertice *(cria)();
void destroi (struct vertice *lista);