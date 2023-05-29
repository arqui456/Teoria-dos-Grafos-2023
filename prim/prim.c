#include "prim.h"

static inline int min(int a, int b)
{
    return a < b ? a : b;
}

static inline int max(int a, int b)
{
    return a > b ? a : b;
}

heap *new_heap(int max_size)
{
    heap *new = (heap *)malloc(sizeof(heap));
    int i;

    new->max_size = max_size;
    new->current_size = 0;
    new->edges = (adj_list **)malloc(max_size * sizeof(adj_list *));

    for (i = 0; i < max_size; ++i)
    {
        new->edges[i] = NULL;
    }
    return new;
}

void enqueue(heap *heap, adj_list *edge)
{
    if (heap->current_size >= heap->max_size)
    {
        printf("heap overflow!, size: %d, max: %d \n", heap->current_size, heap->max_size);
    }
    else
    {
        adj_list *edge_adc = add_adj_list(edge->vertex, edge->origin, edge->cost);
        heap->edges[heap->current_size] = edge_adc;
        int index = heap->current_size;
        int asc_index = ascendent_index(heap->current_size);
        heap->current_size++;
        while ((asc_index >= 0) && (heap->edges[index]->cost < heap->edges[asc_index]->cost))
        {
            adj_list *aux = heap->edges[index];
            heap->edges[index] = heap->edges[asc_index];
            heap->edges[asc_index] = aux;
            index = asc_index;
            asc_index = ascendent_index(index);
        }
    }
}

adj_list *dequeue(heap *heap)
{
    if (heap->current_size == 0)
    {
        printf("heap underflow!");
        exit(0);
    }
    else
    {
        adj_list *dequeued = heap->edges[0];
        heap->edges[0] = heap->edges[--(heap->current_size)];
        min_heapify(heap, 0);
        return dequeued;
    }
}
int ascendent_index(int i)
{
    return i / 2;
}
int descendent_left_index(int i)
{
    return i * 2;
}
int descendent_right_index(int i)
{
    return (2 * i) + 1;
}
void min_heapify(heap *heap, int i)
{
    int smaller;
    int left_idx = descendent_left_index(i);
    int right_idx = descendent_right_index(i);

    if ((left_idx <= (heap->current_size - 1)) && (heap->edges[i]->cost > heap->edges[left_idx]->cost))
    {
        smaller = left_idx;
    }
    else
    {
        smaller = i;
    }

    if ((right_idx <= (heap->current_size - 1)) && (heap->edges[smaller]->cost > heap->edges[right_idx]->cost))
    {
        smaller = right_idx;
    }

    if (heap->edges[i]->cost != heap->edges[smaller]->cost)
    {
        adj_list *aux = heap->edges[i];
        heap->edges[i] = heap->edges[smaller];
        heap->edges[smaller] = aux;
        min_heapify(heap, smaller);
    }
}

int is_empty_heap(heap *heap)
{
    return (heap->current_size == 0);
}
void print_heap(heap *heap)
{
    int i;
    printf("Heap:\n");
    for (i = 0; i < heap->current_size; i++)
    {
        printf("%d || ", heap->edges[i]->cost);
    }
    printf("\n");
}

graph *new_graph(int size)
{

    graph *new = (graph *)malloc(sizeof(graph));
    int i;

    new->vertices = (adj_list **)malloc(size * sizeof(adj_list *));
    new->size = size;
    new->cost = 0;

    for (i = 0; i < size; ++i)
    {
        new->vertices[i] = NULL;
    }
    return new;
}

void add_edge(graph *g, int vertex1, int vertex2, int cost)
{
    adj_list *temp = add_adj_list(vertex2, vertex1, cost);

    temp->next = g->vertices[vertex1];
    g->vertices[vertex1] = temp;

    temp = add_adj_list(vertex1, vertex2, cost);

    temp->next = g->vertices[vertex2];
    g->vertices[vertex2] = temp;

    g->cost += cost;
}

adj_list *add_adj_list(int vertex, int origin, int cost)
{
    adj_list *new = (adj_list *)malloc(sizeof(adj_list));
    new->vertex = vertex;
    new->cost = cost;
    new->origin = origin;
    new->next = NULL;
    return new;
}

graph *new_prim(graph *g, int initial_vertex)
{
    graph *ACM = new_graph(g->size);
    heap *heap;
    adj_list *edges;
    adj_list *min_edge;
    int added = 1;

    edges = g->vertices[initial_vertex];

    heap = new_heap(90000);

    while (added < g->size)
    {
        while (edges != NULL)
        {
            enqueue(heap, edges);
            edges = edges->next;
        }
        min_edge = dequeue(heap);

        if (ACM->vertices[min_edge->vertex] == NULL)
        {
            added += 1;

            add_edge(ACM, min_edge->origin, min_edge->vertex, min_edge->cost);
            edges = g->vertices[min_edge->vertex];
        }
    }
    return ACM;
}

void print_graph(graph *g, unsigned char return_cost, char *output_file)
{
    FILE *file;
    int i, t_cost = 0;
    int first = 1;
    adj_list *temp;
    int repeated[90000] = {0};

    if (output_file != NULL)
    {
        file = fopen(output_file, "w+");
    }

    for (i = 0; i < g->size; i++)
    {
        temp = g->vertices[i];
        while (temp != NULL)
        {
            repeated[(temp->vertex + 1) * (i + 1)]++;
            if (repeated[(temp->vertex + 1) * (i + 1)] == 1)
            {
                if (return_cost)
                {
                    if (output_file != NULL)
                    {
                        if (first)
                        {
                            first = 0;
                            fprintf(file, "(%d %d)", (i + 1), temp->vertex + 1);
                        }
                        else
                        {
                            fprintf(file, " (%d %d)", (i + 1), temp->vertex + 1);
                        }
                    }
                    else
                    {
                        if (first)
                        {
                            first = 0;
                            printf("(%d %d)", (i + 1), temp->vertex + 1);
                        }
                        else
                        {
                            printf(" (%d %d)", (i + 1), temp->vertex + 1);
                        }
                    }
                }
                t_cost += temp->cost;
            }
            temp = temp->next;
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
