#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <conio.h>
#include <stdbool.h>

int contains(const char array[], char chr);

typedef struct Vertex {
    const char chr;
} Vertex;
typedef struct Graph {
    int size;
    char **adjacencyList;
} Graph;

int main(void) {
//	Graph graph;
    char **adjacencyList = NULL;
    char *vertices = NULL;
    int *edgesCount = NULL;
    int order = 0;//индекс прохода по массиву
    char first, second = 0;
    FILE *fp;

    if ((fp = fopen("C:/5th/Graph.txt", "r")) == NULL) {
        printf("Failed to open\n");
        exit(1);
    }

    while (fscanf(fp, "%c-%c\n", &first, &second) == 2) {
        int indexOfVertex = contains(vertices, first);
        if (indexOfVertex == -1) {
            vertices = (char *) realloc(vertices, (order + 1) * sizeof(char));
            vertices[order] = first;

            adjacencyList = (char **) realloc(adjacencyList, (order + 1) * sizeof(char *));
            if (adjacencyList == NULL) {
                printf("Pointer to array of pointers");
                exit(1);
            }

            edgesCount = (int *) realloc(edgesCount, (order + 1) * sizeof(int));
            edgesCount[order] = 1;

            adjacencyList[order] = NULL;
            adjacencyList[order] = (char *) realloc(adjacencyList[order], 1 * sizeof(char));
            if (adjacencyList[order] == NULL) {
                printf("Sequence %d is empty", order);
                exit(1);
            }
            adjacencyList[order][0] = second;
            order++;
        } else {
            adjacencyList[indexOfVertex] = (char *)
                    realloc(adjacencyList[indexOfVertex], (edgesCount[indexOfVertex] + 1) * sizeof(char));
            if (adjacencyList[indexOfVertex] == NULL) exit(1);
            edgesCount[indexOfVertex]++;
            adjacencyList[indexOfVertex][ edgesCount[indexOfVertex]-1] = second;
        }
    }
    for (int i = 0; i < order; i++) {
        register int size = edgesCount[i];
        printf("%c-", vertices[i]);
        for (int j = 0; j < size; j++) {
            if (j != 0)printf(",");

            printf("%c", adjacencyList[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < order; i++)
        free(adjacencyList[i]);
    free(adjacencyList);
    free(vertices);
    fclose(fp);
    return EXIT_SUCCESS;
}

int contains(const char array[], char chr) {
    if (array != NULL) {
        register int t;
        for (t = 0; array[t]; t++)
            if (array[t] == chr) return t;
    }
    return -1;
}
