#include "dijkstra.h"

node* new_node(int v, int weight) {
    node* newNode = (node*)malloc(sizeof(node));
    newNode->vertex = v;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

priority_queue_node* new_priority_queue_node(int v, int priority) {
    priority_queue_node* newNode = (priority_queue_node*)malloc(sizeof(priority_queue_node));
    newNode->vertex = v;
    newNode->priority = priority;
    return newNode;
}

graph* new_graph(int n) {
    graph* g = (graph*)malloc(sizeof(graph));
    g->num_vertices = n;
    int i;
    for (i = 0; i < n; i++)
        g->array[i] = NULL;
    return g;
}

void add_edge(graph* g, int src, int dest, int weight) {
    node* newNode = new_node(dest, weight);
    newNode->next = g->array[src];
    g->array[src] = newNode;

    newNode = new_node(src, weight);
    newNode->next = g->array[dest];
    g->array[dest] = newNode;
}

priority_queue* new_priority_queue() {
    priority_queue* queue = (priority_queue*)malloc(sizeof(priority_queue));
    queue->size = 0;
    return queue;
}

void swap(priority_queue_node** a, priority_queue_node** b) {
    priority_queue_node* temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(priority_queue* queue, int idx, int* positions) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < queue->size && queue->array[left]->priority < queue->array[smallest]->priority)
        smallest = left;

    if (right < queue->size && queue->array[right]->priority < queue->array[smallest]->priority)
        smallest = right;

    if (smallest != idx) {
        positions[queue->array[smallest]->vertex] = idx;
        positions[queue->array[idx]->vertex] = smallest;
        swap(&queue->array[smallest], &queue->array[idx]);
        minHeapify(queue, smallest, positions);
    }
}

int is_empty(priority_queue* queue) {
    return queue->size == 0;
}

priority_queue_node* extractMin(priority_queue* queue, int* positions) {
    if (is_empty(queue))
        return NULL;

    priority_queue_node* root = queue->array[0];
    priority_queue_node* lastNode = queue->array[queue->size - 1];
    queue->array[0] = lastNode;
    positions[root->vertex] = queue->size - 1;
    positions[lastNode->vertex] = 0;
    --queue->size;
    minHeapify(queue, 0, positions);
    return root;
}

void decreasePriority(priority_queue* queue, int vertex, int priority, int* positions) {
    int i = positions[vertex];
    queue->array[i]->priority = priority;

    while (i > 0 && queue->array[i]->priority < queue->array[(i - 1) / 2]->priority) {
        positions[queue->array[i]->vertex] = (i - 1) / 2;
        positions[queue->array[(i - 1) / 2]->vertex] = i;
        swap(&queue->array[i], &queue->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void enqueue(priority_queue* queue, int vertex, int priority, int* positions) {
    priority_queue_node* newNode = new_priority_queue_node(vertex, priority);
    queue->array[queue->size] = newNode;
    positions[vertex] = queue->size;
    ++queue->size;

    int i = queue->size - 1;
    while (i > 0 && queue->array[i]->priority < queue->array[(i - 1) / 2]->priority) {
        positions[queue->array[i]->vertex] = (i - 1) / 2;
        positions[queue->array[(i - 1) / 2]->vertex] = i;
        swap(&queue->array[i], &queue->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void print_graph(int dist[], int src, int num_vertices, char *output_file) {
    int i;
    FILE *file;

    if (output_file != NULL)
    {
        file = fopen(output_file, "w+");
        fprintf(file, "1:0 ");
    } else {
        printf("1:0 ");
    }

    for (i = 0; i < num_vertices; i++) {
        if (i != src) {
            if(output_file != NULL) {
                fprintf(file, "%d:",i+1);
                if (dist[i] == INT_MAX) {
                    fprintf(file,"-1 ");
                } else {
                    fprintf(file,"%d ", dist[i]);
                }    
            } else {
                printf("%d:",i+1);
                if (dist[i] == INT_MAX) {
                    printf("-1 ");
                } else {
                    printf("%d ", dist[i]);
                }
            }
        }
    }

    if (output_file != NULL)
    {
        fclose(file);
    }
}

void dijkstra(graph* g, int src, char *output_file) {
    int dist[MAX_SIZE];
    int visited[MAX_SIZE];
    int positions[MAX_SIZE];

    int i;
    for (i = 0; i < g->num_vertices; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
        positions[i] = -1;
    }

    dist[src] = 0;

    priority_queue* queue = new_priority_queue();
    enqueue(queue, src, 0, positions);

    while (!is_empty(queue)) {
        priority_queue_node* minNode = extractMin(queue, positions);
        int u = minNode->vertex;
        visited[u] = 1;

        node* adjNode = g->array[u];
        while (adjNode != NULL) {
            int v = adjNode->vertex;
            int weight = adjNode->weight;

            if (!visited[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                if (positions[v] == -1) {
                    enqueue(queue, v, dist[v], positions);
                } else {
                    decreasePriority(queue, v, dist[v], positions);
                }
            }
            adjNode = adjNode->next;
        }
    }
    print_graph(dist, src, g->num_vertices, output_file);
}

void help()
{
    printf("Usage: prim.bin [OPTIONS]... \n");
    printf(" -f <arquivo>   indica o 'arquivo' que contem o grafo de entrada \n");
    printf(" -o <arquivo>   redireciona a saida para o 'arquivo' \n");
    printf(" -s             mostra a solucao\n");
    printf(" -i             vertice inicial");
}