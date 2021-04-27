
#ifndef UNTITLED_MAIN_H
#define UNTITLED_MAIN_H

int contains(const char *array, char chr);

void createGraph(char *inputFile, char *outputFile);

void addVertexAndEdgeToGraph(char ***adjacencyList, char **vertices, int **edgesCount, int *op, const char *vertex,
                             const char *edge);

struct Graph;
typedef struct Graph graph;

#endif //UNTITLED_MAIN_H
