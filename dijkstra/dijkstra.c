#include "dijkstra.h"

graph *new_graph(int size)
{
    int i = 0;
    graph *new = (graph *)malloc(sizeof(graph));
    new->size = size;
    
    new->adjacencyList = (edge **)malloc(size * sizeof(edge *));
    for (i = 0; i < size; i++)
    {
        new->adjacencyList[i] = NULL;
        new->previous[i] = -1;
    }
    return new;
}

void add_edge(graph *g, int initialVertex, int targetVertex, int cost)
{
    edge *newEdge = (edge *)malloc(sizeof(edge));
    newEdge->vertex = targetVertex;
    newEdge->cost = cost;
    newEdge->next = g->adjacencyList[initialVertex];
    g->adjacencyList[initialVertex] = newEdge;
}

void new_dijkstra(graph *g)
{
    int size = g->size;
    int i, count;
    vertex *vertices = (vertex *)malloc(size * sizeof(vertex));

    for (i = 0; i < size; i++)
    {
        vertices[i].cost = INT_MAX;
        vertices[i].visited = 0;
    }

    vertices[g->initialVertex].cost = 0;

    for (count = 0; count < size - 1; count++)
    {
        int minCost = INT_MAX;
        int minNode = -1;

        for (i = 0; i < size; i++)
        {
            if (vertices[i].visited == 0 && vertices[i].cost < minCost)
            {
                minCost = vertices[i].cost;
                minNode = i;
            }
        }

        vertices[minNode].visited = 1;

        edge *current = g->adjacencyList[minNode];
        while (current != NULL)
        {
            int neighbor = current->vertex;
            int newCost = vertices[minNode].cost + current->cost;
            if (newCost < vertices[neighbor].cost)
            {
                vertices[neighbor].cost = newCost;
                g->previous[neighbor] = minNode;
            }
            current = current->next;
        }
    }
    g->vertices = vertices;
}

void print_graph(graph *g, char *output_file)
{
    FILE *file;
    int size = g->size;
    int i = 0;
    int first = 1;

    if (output_file != NULL)
    {
        file = fopen(output_file, "w+");
    }

    for (int i = 0; i < size; i++)
    {
        if (output_file != NULL)
        {
            if (first)
            {
                fprintf(file, "%d:%d", i + 1, g->vertices[i].cost);
                first = 0;
            }
            else
            {
                fprintf(file, " %d:%d", i + 1, g->vertices[i].cost);
            }
        }
        else
        {
            if (first)
            {
                printf("%d:%d", i + 1, g->vertices[i].cost);
                first = 0;
            }
            else
            {
                printf(" %d:%d", i + 1, g->vertices[i].cost);
            }
        }
    }

    if (output_file != NULL)
    {
        fclose(file);
    }
}

void help()
{
    printf("Usage: prim.bin [OPTIONS]... \n");
    printf(" -f <arquivo>   indica o 'arquivo' que contem o grafo de entrada \n");
    printf(" -o <arquivo>   redireciona a saida para o 'arquivo' \n");
    printf(" -s             mostra a solucao\n");
    printf(" -i             vertice inicial");
}