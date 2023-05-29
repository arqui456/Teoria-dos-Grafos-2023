#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dijkstra.h"

static char INPUT_FILE[90000] = {0};
static char OUTPUT_FILE[90000] = {0};
static unsigned int INITIAL_VERTICE = 0;
static unsigned char OUTPUT_TO_FILE = 0;

int main(int argc, char **argv)
{
    FILE *file;
    int i, v_num, a_num, v1, v2, c;
    int err = 0;
    char line[90000] = {0};
    graph *g = NULL;

    for (i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "-f"))
        {
            strcpy(INPUT_FILE, argv[i + 1]);
            file = fopen(INPUT_FILE, "r");
            if (file == NULL)
                return -1;
            fgets(line, sizeof(line), file);
            err = sscanf(line, "%d %d", &v_num, &a_num);
            g = new_graph(v_num);
            while (fgets(line, sizeof(line), file))
            {
                sscanf(line, "%d %d %d", &v1, &v2, &c);
                add_edge(g, v1 - 1, v2 - 1, c);
            }
            fclose(file);
        }
        else if (!strcmp(argv[i], "-i"))
        {
            sscanf(argv[i + 1], "%u", &INITIAL_VERTICE);
        }
        else if (!strcmp(argv[i], "-o"))
        {
            strcpy(OUTPUT_FILE, argv[i + 1]);
            OUTPUT_TO_FILE = 1;
        }
        else if (!strcmp(argv[i], "-h"))
        {
            help();
        }
    }

    if(g != NULL) {
        g->initialVertex = 0;
        new_dijkstra(g);
        if (OUTPUT_TO_FILE)
        {
            print_graph(g, OUTPUT_FILE);
        } else {
            print_graph(g, NULL);
        }
        free(g);
    }

    return 0;
}