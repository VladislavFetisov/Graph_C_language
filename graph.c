#include <stdio.h>
#include <stdlib.h>
#include "main.h"

typedef struct Graph {
    char **adjacencyList;
    char *vertices;
    int *edgesCount;
} Graph;

void createGraph(char *inputFile, char *outputFile) {
    Graph graph;
    graph.adjacencyList = NULL;
    graph.vertices = NULL;
    graph.edgesCount = NULL;
    int order = 0;//индекс прохода по массивам vertices и edgesCount.
    char vertex, edge;
    FILE *fp;

    if ((fp = fopen(inputFile, "r")) == NULL) {
        printf("Failed to open\n");
        exit(1);
    }

    while (fscanf(fp, "%c-%c\n", &vertex, &edge) == 2) {
        addVertexAndEdgeToGraph(&graph.adjacencyList, &graph.vertices, &graph.edgesCount, &order, &vertex, &edge);
        addVertexAndEdgeToGraph(&graph.adjacencyList, &graph.vertices, &graph.edgesCount, &order, &edge, &vertex);
    }
    if ((fp = fopen(outputFile, "w")) == NULL) {
        printf("Fail when open file\n");
        exit(1);
    }
    for (int i = 0; i < order; i++) {
        register int size = graph.edgesCount[i];
        fprintf(fp, "%c-", graph.vertices[i]);
        for (int j = 0; j < size; j++) {
            if (j != 0) fprintf(fp, ",");
            fprintf(fp, "%c", graph.adjacencyList[i][j]);
        }
        fprintf(fp, "\n");
    }

    for (int i = 0; i < order; i++)
        free(graph.adjacencyList[i]);
    free(graph.adjacencyList);
    free(graph.vertices);
    free(graph.edgesCount);
    fclose(fp);
}

void addVertexAndEdgeToGraph(char ***adjacencyList, char **vertices, int **edgesCount, int *op, const char *vertex,
                             const char *edge) {
    int indexOfVertex = contains(*vertices, *vertex);

    if (indexOfVertex == -1) {
        *vertices = (char *) realloc(*vertices, (*op + 1) * sizeof(char));
        (*vertices)[*op] = *vertex;


        *adjacencyList = (char **) realloc(*adjacencyList, (*op + 1) * sizeof(char *));
        if (*adjacencyList == NULL) {
            printf("Pointer to array of pointers if empty");
            exit(1);
        }

        *edgesCount = (int *) realloc(*edgesCount, (*op + 1) * sizeof(int));
        (*edgesCount)[*op] = 1;
        if (contains(*vertices, *edge) == -1) {

        }
        (*adjacencyList)[*op] = NULL;
        (*adjacencyList)[*op] = (char *) realloc((*adjacencyList)[*op], 1 * sizeof(char));
        if ((*adjacencyList)[*op] == NULL) {
            printf("Sequence %d is empty", *op);
            exit(1);
        }
        (*adjacencyList)[*op][0] = *edge;
        *op += 1;
    } else if (contains((*adjacencyList)[indexOfVertex], *edge) == -1) {
        (*adjacencyList)[indexOfVertex] = (char *)
                realloc((*adjacencyList)[indexOfVertex], ((*edgesCount)[indexOfVertex] + 1) * sizeof(char));
        if (adjacencyList[indexOfVertex] == NULL) exit(1);
        (*edgesCount)[indexOfVertex] += 1;
        (*adjacencyList)[indexOfVertex][(*edgesCount)[indexOfVertex] - 1] = *edge;
    }
}

int contains(const char *array, char chr) {
    if (array != NULL) {
        register int t;
        for (t = 0; array[t]; t++)
            if (array[t] == chr) return t;
    }
    return -1;
}
