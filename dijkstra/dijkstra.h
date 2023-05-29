#ifndef _DJIKSTRA_H_
#define _DJIKSTRA_H_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX_SIZE 2048

typedef struct graph graph;
typedef struct edge edge;
typedef struct vertex vertex;

struct edge
{
    int vertex;
    int cost;
    edge *next;
};

struct graph
{
    int size;
    int initialVertex;
    int targetVertex;
    edge **adjacencyList;
    int previous[MAX_SIZE];
    vertex *vertices;
};

struct vertex
{
    int cost;
    int visited;
};

graph *new_graph(int size);
void add_edge(graph *g, int v1, int v2, int cost);
void new_dijkstra(graph *g);
void help();
void print_graph(graph *g, char *output_file);

#endif
