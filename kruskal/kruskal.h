#ifndef _KRUSKAL_H_
#define _KRUSKAL_H_

#include <stdio.h>
#include <stdlib.h>

#define INFINITY 99999999
#define N_VERTEX -1
#define COST_N 0

typedef struct edge edge;
typedef struct graph graph;

struct graph
{
    int **adj_matrix;
    edge **edges;
    int size;
};

struct edge
{
    int u;
    int v;
    int cost;
};

void make_set(int *ascendent, int *rank, int x);

int find(int *ascendent, int x);

void union_(int *ascendent, int *rank, int x, int y);

int find(int *ascendent, int x);

void mergesort(int p, int r, edge **v);

graph *new_graph(int size);

edge **new_edges(int size);

void add_edge(graph *g, int u, int v, int cost);

graph *new_kruskal(graph *g);

void print_graph(graph *g, unsigned char return_cost, char *output_file);

void help();

#endif