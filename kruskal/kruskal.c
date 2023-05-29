#include "kruskal.h"

void make_set(int *ascendent, int *rank, int x)
{
    ascendent[x] = x;
    rank[x] = 0;
}

int find(int *ascendent, int x)
{
    int target = x;
    while (ascendent[target] != target)
    {
        target = ascendent[target];
    }
    return target;
}

void union_(int *ascendent, int *rank, int x, int y)
{
    if (rank[x] >= rank[y])
    {
        ascendent[y] = x;
        if (rank[x] == rank[y])
        {
            rank[x]++;
        }
    }
    else
    {
        ascendent[x] = y;
    }
}

static void merge(int p, int q, int r, edge **v)
{
    int i, j, k;
    edge **w;

    w = (edge **)malloc((r - p) * sizeof(edge *));
    i = p;
    j = q;
    k = 0;

    while (i < q && j < r)
    {
        if (v[i]->cost <= v[j]->cost)
        {
            w[k++] = v[i++];
        }
        else
        {
            w[k++] = v[j++];
        }
    }
    while (i < q)
    {
        w[k++] = v[i++];
    }
    while (j < r)
    {
        w[k++] = v[j++];
    }
    for (i = p; i < r; ++i)
    {
        v[i] = w[i - p];
    }
    free(w);
}

void mergesort(int p, int r, edge **v)
{
    if (p < r - 1)
    {
        int q = (p + r) / 2;
        mergesort(p, q, v);
        mergesort(q, r, v);
        merge(p, q, r, v);
    }
}

graph *new_graph(int size)
{
    graph *new = (graph *)malloc(sizeof(graph));
    new->size = size;
    int **adj_matrix = (int **)malloc(size * sizeof(int *));
    int i, j;

    for (i = 0; i < size; i++)
    {
        adj_matrix[i] = (int *)malloc(size * sizeof(int));
    }

    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            adj_matrix[i][j] = COST_N;
        }
    }
    new->adj_matrix = adj_matrix;
    new->edges = new_edges(size);

    return new;
}

edge **new_edges(int size)
{
    edge **a = (edge **)malloc(size * size * sizeof(edge *));
    int t = size * size;
    int i;
    for (i = 0; i < t; i++)
    {
        a[i] = (edge *)malloc(sizeof(edge));
        a[i]->u = N_VERTEX;
        a[i]->v = N_VERTEX;
        a[i]->cost = INFINITY;
    }
    return a;
}

void add_edge(graph *g, int u, int v, int cost)
{
    g->adj_matrix[u][v] = cost;
    int index = u * g->size + v;
    g->edges[index]->u = u;
    g->edges[index]->v = v;
    g->edges[index]->cost = cost;
}

graph *new_kruskal(graph *g)
{
    int ascendent[g->size];
    int rank[g->size];
    int i;
    int t = g->size * g->size;
    graph *kruskal = new_graph(g->size);

    mergesort(0, t, g->edges);

    for (i = 0; i < g->size; i++)
    {
        make_set(ascendent, rank, i);
    }
    for (i = 0; i < t; i++)
    {
        if (g->edges[i]->cost == INFINITY)
        {
            break;
        }
        int u = g->edges[i]->u;
        int v = g->edges[i]->v;
        int cost = g->edges[i]->cost;
        int ascendent_u = find(ascendent, u);
        int ascendent_v = find(ascendent, v);
        if (ascendent_u != ascendent_v)
        {
            kruskal->adj_matrix[u][v] = cost;
            union_(ascendent, rank, ascendent_u, ascendent_v);
        }
    }
    kruskal->edges = g->edges;
    return kruskal;
}

void print_graph(graph *g, unsigned char return_cost, char *output_file)
{
    FILE *file;
    int first = 1;
    int i, j, t_cost = 0;
    

    if (output_file != NULL)
    {
        file = fopen(output_file, "w+");
    }

    for (i = 0; i < g->size; i++)
    {
        for (j = 0; j < g->size; j++)
        {
            if (g->adj_matrix[i][j] == 0)
            {
                continue;
            }
            if (return_cost)
            {
                if (output_file != NULL)
                {
                    if (first)
                    {
                        fprintf(file, "(%d %d)", (i + 1), (j + 1));
                        first = 0;
                    }
                    else
                    {
                        fprintf(file, " (%d %d)", (i + 1), (j + 1));
                    }
                }
                else
                {
                    if (first)
                    {
                        printf("(%d %d)", (i + 1), (j + 1));
                        first = 0;
                    }
                    else
                    {
                        printf(" (%d %d)", (i + 1), (j + 1));
                    }
                }
            }
            t_cost += g->adj_matrix[i][j];
        }
    }
    if (!return_cost)
    {
        if (output_file != NULL)
        {
            fprintf(file, "%d", t_cost);
            fclose(file);
            return;
        }
        printf("%d", t_cost);
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
