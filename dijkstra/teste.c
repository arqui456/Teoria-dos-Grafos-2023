#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_NODES 100

// Node structure
typedef struct Node {
    int vertex;
    int weight;
    struct Node* next;
} Node;

// Priority queue node structure
typedef struct PriorityQueueNode {
    int vertex;
    int priority;
} PriorityQueueNode;

// Priority queue structure
typedef struct PriorityQueue {
    PriorityQueueNode* array[MAX_NODES];
    int size;
} PriorityQueue;

// Graph structure
typedef struct Graph {
    Node* array[MAX_NODES];
    int numNodes;
} Graph;

// Create a new node
Node* createNode(int v, int weight) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// Create a priority queue node
PriorityQueueNode* createPriorityQueueNode(int v, int priority) {
    PriorityQueueNode* newNode = (PriorityQueueNode*)malloc(sizeof(PriorityQueueNode));
    newNode->vertex = v;
    newNode->priority = priority;
    return newNode;
}

// Create a graph with n nodes
Graph* createGraph(int n) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numNodes = n;
    int i;
    for (i = 0; i < n; i++)
        graph->array[i] = NULL;
    return graph;
}

// Add an edge to the graph
void addEdge(Graph* graph, int src, int dest, int weight) {
    // Add edge from src to dest
    Node* newNode = createNode(dest, weight);
    newNode->next = graph->array[src];
    graph->array[src] = newNode;

    // Add edge from dest to src (undirected graph)
    newNode = createNode(src, weight);
    newNode->next = graph->array[dest];
    graph->array[dest] = newNode;
}

// Create a priority queue
PriorityQueue* createPriorityQueue() {
    PriorityQueue* queue = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    queue->size = 0;
    return queue;
}

// Swap two priority queue nodes
void swap(PriorityQueueNode** a, PriorityQueueNode** b) {
    PriorityQueueNode* temp = *a;
    *a = *b;
    *b = temp;
}

// Min-Heapify the priority queue
void minHeapify(PriorityQueue* queue, int idx, int* positions) {
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

// Check if the priority queue is empty
int isEmpty(PriorityQueue* queue) {
    return queue->size == 0;
}

// Extract the minimum node from the priority queue
PriorityQueueNode* extractMin(PriorityQueue* queue, int* positions) {
    if (isEmpty(queue))
        return NULL;

    PriorityQueueNode* root = queue->array[0];
    PriorityQueueNode* lastNode = queue->array[queue->size - 1];
    queue->array[0] = lastNode;
    positions[root->vertex] = queue->size - 1;
    positions[lastNode->vertex] = 0;
    --queue->size;
    minHeapify(queue, 0, positions);
    return root;
}

// Decrease the priority of a vertex in the priority queue
void decreasePriority(PriorityQueue* queue, int vertex, int priority, int* positions) {
    int i = positions[vertex];
    queue->array[i]->priority = priority;

    while (i > 0 && queue->array[i]->priority < queue->array[(i - 1) / 2]->priority) {
        positions[queue->array[i]->vertex] = (i - 1) / 2;
        positions[queue->array[(i - 1) / 2]->vertex] = i;
        swap(&queue->array[i], &queue->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Enqueue a vertex with its priority in the priority queue
void enqueue(PriorityQueue* queue, int vertex, int priority, int* positions) {
    PriorityQueueNode* newNode = createPriorityQueueNode(vertex, priority);
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

// Print the shortest path from source to destination
void printPath(int parent[], int j) {
    if (parent[j] == -1) {
        printf("No path");
        return;
    }
    printPath(parent, parent[j]);
    printf("-> %d ", j);
}

// Print the distance from the source to all vertices
void printSolution(int dist[], int parent[], int src, int numNodes) {
    int i;
    printf("Vertex\t Distance\tPath\n");
    for (i = 0; i < numNodes; i++) {
        if (i != src) {
            printf("%d -> %d\t ", src, i);
            if (dist[i] == INT_MAX) {
                printf("-1\t");
            } else {
                printf("%d\t", dist[i]);
            }
            printPath(parent, i);
            printf("\n");
        }
    }
}

// Dijkstra's algorithm
void dijkstra(Graph* graph, int src) {
    int dist[MAX_NODES];     // Stores the shortest distance from src to i
    int parent[MAX_NODES];   // Stores the parent node of i in the shortest path
    int visited[MAX_NODES];  // Tracks visited nodes
    int positions[MAX_NODES]; // Tracks the position of nodes in the priority queue

    // Initialize dist[], parent[], visited[], and positions[]
    int i;
    for (i = 0; i < graph->numNodes; i++) {
        dist[i] = INT_MAX;
        parent[i] = -1;
        visited[i] = 0;
        positions[i] = -1;  // Initialize positions with an invalid position
    }

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Create a priority queue and insert the source node with priority 0
    PriorityQueue* queue = createPriorityQueue();
    enqueue(queue, src, 0, positions);

    while (!isEmpty(queue)) {
        // Extract the vertex with the minimum distance from the priority queue
        PriorityQueueNode* minNode = extractMin(queue, positions);
        int u = minNode->vertex;
        visited[u] = 1;

        // Update dist[v] and parent[v] for all adjacent vertices of the picked vertex
        Node* adjNode = graph->array[u];
        while (adjNode != NULL) {
            int v = adjNode->vertex;
            int weight = adjNode->weight;

            if (!visited[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                if (positions[v] == -1) {
                    enqueue(queue, v, dist[v], positions);
                } else {
                    decreasePriority(queue, v, dist[v], positions);
                }
            }

            adjNode = adjNode->next;
        }
    }

    // Print the shortest paths
    printSolution(dist, parent, src, graph->numNodes);
}

// Test the algorithm
int main() {
    // Create a graph
    int numNodes = 8;
    Graph* graph = createGraph(numNodes);
    addEdge(graph, 1 - 1, 2-1, 5);
    addEdge(graph, 1-1, 3-1, 4);
    addEdge(graph, 1-1, 4-1, 2);
    addEdge(graph, 1-1, 6-1, 6);
    addEdge(graph, 2-1, 4-1, 1);
    addEdge(graph, 2-1, 5-1, 7);
    addEdge(graph, 3-1, 5-1, 6);
    addEdge(graph, 4-1, 6-1, 1);
    addEdge(graph, 7-1, 8-1, 10); 

    int sourceNode = 0;
    dijkstra(graph, sourceNode);

    return 0;
}



