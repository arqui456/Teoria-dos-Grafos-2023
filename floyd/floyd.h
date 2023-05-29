#ifndef _FLOYD_H_
#define _FLOYD_H_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct AdjListNode AdjListNode;
typedef struct AdjList AdjList;
typedef struct graph graph;

struct AdjListNode
{
    int dest;
    int weight;
    AdjListNode *next;
};

struct AdjList
{
    AdjListNode *head;
};

struct graph
{
    int V;
    AdjList *array;
};

AdjListNode *newAdjListNode(int dest, int weight);
graph *new_graph(int V);
void add_vertex(graph *graph, int src, int dest, int weight);
void floydWarshall(graph *graph, char *output_file);
void help();

#endif