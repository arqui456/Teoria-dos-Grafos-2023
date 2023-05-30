#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_SIZE 100000

typedef struct node node;
typedef struct priority_queue_node priority_queue_node;
typedef struct priority_queue priority_queue;
typedef struct graph graph;

struct node {
    int vertex;
    int weight;
    struct node* next;
};

struct priority_queue_node {
    int vertex;
    int priority;
};

struct priority_queue {
    priority_queue_node* array[MAX_SIZE];
    int size;
};

struct graph {
    node* array[MAX_SIZE];
    int num_vertices;
};

node* new_node(int v, int weight);
priority_queue_node* new_priority_queue_node(int v, int priority);
graph* new_graph(int n);
void add_edge(graph* g, int src, int dest, int weight);
priority_queue* new_priority_queue();
void swap(priority_queue_node** a, priority_queue_node** b);
void minHeapify(priority_queue* queue, int idx, int* positions);
int is_empty(priority_queue* queue);
priority_queue_node* extractMin(priority_queue* queue, int* positions);
void decreasePriority(priority_queue* queue, int vertex, int priority, int* positions);
void enqueue(priority_queue* queue, int vertex, int priority, int* positions);
void print_graph(int dist[], int src, int num_vertices, char *output_file);
void dijkstra(graph* g, int src, char *output_file);
void help();

#endif
