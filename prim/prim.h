#ifndef _PRIM_H_
#define _PRIM_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct graph graph;
typedef struct adj_list adj_list;
typedef struct heap heap;

struct adj_list
{
    int cost;
    int vertex;
    int origin;
    adj_list *next;
};

struct heap
{
    int max_size;
    int current_size;
    adj_list **edges;
};

struct graph
{
    adj_list **vertices;
    int size;
    int cost;
};

void help();
graph *new_graph(int size);
void add_edge(graph *g, int v1, int v2, int cost);
void print_graph(graph *g, unsigned char return_cost, char *output_file);
adj_list *add_adj_list(int vertex, int origin, int cost);
graph *new_prim(graph *g, int initial_vertex);
heap *new_heap(int size);
void enqueue(heap *heap, adj_list *edge);
adj_list *dequeue(heap *heap);
int ascendent_index(int);
int descendent_left_index(int);
int descendent_right_index(int);
void min_heapify(heap *heap, int i);
int is_empty_heap(heap *heap);
void print_heap(heap *heap);

#endif
