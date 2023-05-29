#include "floyd.h"

AdjListNode *newAdjListNode(int dest, int weight)
{
    AdjListNode *newNode = ( AdjListNode *)malloc(sizeof( AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

graph *new_graph(int V)
{
    graph *g = ( graph *)malloc(sizeof( graph));
    g->V = V;

    g->array = ( AdjList *)malloc(V * sizeof( AdjList));

    for (int i = 0; i < V; ++i)
        g->array[i].head = NULL;

    return g;
}

void add_vertex( graph *g, int src, int dest, int weight)
{
    AdjListNode *newNode = newAdjListNode(dest, weight);
    newNode->next = g->array[src].head;
    g->array[src].head = newNode;

    newNode = newAdjListNode(src, weight);
    newNode->next = g->array[dest].head;
    g->array[dest].head = newNode;
}

void floydWarshall(graph *g, char *output_file)
{
    if (g == NULL)
    {
        printf("No graph supplied.\n");
        return;
    }

    FILE *file;
    if(output_file != NULL){
        file = fopen(output_file, "w+");
    }

    int V = g->V;
    int dist[V][V];

    for (int i = 0; i < V; ++i)
    {
        for (int j = 0; j < V; ++j)
        {
            dist[i][j] = INT_MAX;
        }
    }

    for (int i = 0; i < V; ++i)
    {
        dist[i][i] = 0;
    }

    for (int i = 0; i < V; ++i)
    {
        AdjListNode *node = g->array[i].head;
        while (node != NULL)
        {
            dist[i][node->dest] = node->weight;
            node = node->next;
        }
    }

    for (int k = 0; k < V; ++k)
    {
        for (int i = 0; i < V; ++i)
        {
            for (int j = 0; j < V; ++j)
            {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    int first = 1;
    for (int i = 0; i < g->V; ++i)
    {
        if (dist[0][i] == INT_MAX)
        {
            printf("%d:-1", i + 1);
        }
        else
        {
            if(output_file != NULL) {
                if (first)
                {
                    fprintf(file, "%d:%d", i + 1, dist[0][i]);
                    first = 0;
                }
                else
                {
                    fprintf(file," %d:%d", i + 1, dist[0][i]);
                }
            } else {
                if (first)
                {
                    printf("%d:%d", i + 1, dist[0][i]);
                    first = 0;
                }
                else
                {
                    printf(" %d:%d", i + 1, dist[0][i]);
                }
            }
        }
    }
    if(output_file != NULL) {
        fclose(file);
    }
}

void help()
{
    printf("Usage: prim.bin [OPTIONS]... \n");
    printf(" -f <arquivo>   indica o 'arquivo' que contem o grafo de entrada \n");
    printf(" -o <arquivo>   redireciona a saida para o 'arquivo' \n");
    printf(" -i             vertice inicial");
}
