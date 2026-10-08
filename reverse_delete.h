//ANTONIS TSIGGERHS 2026
//06/06/2025
//ERGASIA 3 OMADA 8

#ifndef TEST_ERGASIA3_REVERSE_DELETE_H
#define TEST_ERGASIA3_REVERSE_DELETE_H

#endif //TEST_ERGASIA3_REVERSE_DELETE_H
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> // Xreiazetai gia to malloc

#define MAX_VERTICES 1000000 // Megisto plithos korifon (kai akmon, giati kathe akmi apothikeuetai)

// Struct gia na antiproswpeuei ena akro gia ton algorithmo Reverse Delete
typedef struct {
    int source; // H pinaka korifi tou akrou
    int destination; // H korifi proorismos tou akrou
    int weight; // To baros tou akrou
} EdgeReverse;

// Struct gia na antiproswpeuei enan grafo gia ton algorithmo Reverse Delete
typedef struct {
    int numVertices; // O arithmos twn korifwn ston grafo
    int numEdges; // O arithmos twn akmon ston grafo
    EdgeReverse edges[MAX_VERTICES]; // Pinakas pou periexei oles tis akmes tou grafou
} GraphReverse;

// Synartisi gia dimiourgia enos grafou gia ton algorithmo Reverse Delete
GraphReverse* createGraphReverse(int numVertices, int numEdges) {
    // Arxikopoiei ton grafo pou exei ton arithmo twn korifwn kai ton arithmo twn akmwn
    GraphReverse* graph = (GraphReverse*)malloc(sizeof(GraphReverse)); // Desmeusi mnimis gia to grafo
    graph->numVertices = numVertices; // Arxikopoiisi arithmou korifwn
    graph->numEdges = numEdges; // Arxikopoiisi arithmou akmwn (arxika 0)
    return graph; // Epistrefei ton neo grafo
}

// Synartisi gia prosthiki akrou ston grafo Reverse Delete
void addEdgeReverse(GraphReverse * graph, int source, int destination, int weight) {
    graph->edges[graph->numEdges].source = source; // Arxikopoiisi pinakas akrou
    graph->edges[graph->numEdges].destination = destination; // Arxikopoiisi proorismou akrou
    graph->edges[graph->numEdges].weight = weight; // Arxikopoiisi barous akrou
    graph->numEdges++; // Ayxanei ton arithmo twn akmwn tou grafou
}

// Synartisi DFS (Depth First Search) gia elegxo syndesimotitas
void DFS(int currentNode, bool* visited, EdgeReverse* edgeReverse , int numEdges) {
    visited[currentNode] = true; // Markarei tin trexousa korifi os episkefthike

    // Diapernaei oles tis akmes gia na brei geitones
    for (int i = 0; i < numEdges; i++) {
        // Elegxei an i trexousa akmi syndeei ton currentNode me kapoio allo komvo
        // kai an to baros tis den einai -1 (pou simainei oti exei afairethei proswrina)
        if ((edgeReverse[i].source == currentNode || edgeReverse[i].destination == currentNode) && edgeReverse[i].weight != -1) {
            // Briskei ton geitona tou currentNode meso autis tis akmis
            int neighbor = (edgeReverse[i].source == currentNode) ? edgeReverse[i].destination : edgeReverse[i].source;
            // An o geitonas den exei episkeftei akoma, kalei tin DFS gia auton
            if (!visited[neighbor]) {
                DFS(neighbor, visited, edgeReverse, numEdges);
            }
        }
    }
}

// Synartisi gia tin efarmogi tou algorithmou Reverse Delete kai eyresi tou Minimum Spanning Tree
void reverseDelete(GraphReverse * graph) {
    int i, j;
    bool visited[graph->numVertices]; // Pinakas gia na kratame poies korifes exoun episkeftei stin DFS

    // Taxinomisi twn akmwn se fthinousa seira me basi to baros tous (apo to pio megalo sto pio mikro)
    for (i = 0; i < graph->numEdges; i++) {
        for (j = i + 1; j < graph->numEdges; j++) {
            if (graph->edges[i].weight < graph->edges[j].weight) {
                // Allagi thesewn twn akmwn (swap)
                EdgeReverse temp = graph->edges[i];
                graph->edges[i] = graph->edges[j];
                graph->edges[j] = temp;
            }
        }
    }
    printf("=====================\n");

    printf("Minimum Spanning Tree Edges:\n");
    // Diapernaei oles tis taxinomimenes akmes (apo to pio megalo baros sto pio mikro)
    for (i = 0; i < graph->numEdges; i++) {
        // Proswrini afairesi tou akrou apo ton grafo thetontas to baros tou se -1
        EdgeReverse currentEdge = graph->edges[i]; // Apothikeusi tou trexontos akrou
        graph->edges[i].weight = -1; // "Diagrafi" tou akrou

        // Elegxos an o grafo paramenei syndedemenos meta tin afairesi tou akrou
        bool isConnected = true;
        // Arxikopoiisi olon ton korifwn os "mi episkefthikes" gia tin DFS
        for(int k=0;k<graph->numVertices;k++)
        {
            visited[k] = false;
        }
        // Ektelesi DFS apo tin korifi 0 (i opoia prepei na einai syndedemeni me ton grafo)
        DFS(0,visited,graph->edges,graph->numEdges);
        // Elegxos an oles oi korifes episkefthikan (dhladh, an o grafo paramenei syndedemenos)
        for(int k=0;k<graph->numVertices;k++)
        {
            if(visited[k]==false)
            {
                isConnected = false; // An brethei mia mi episkefthiki korifi, o grafo den einai syndedemenos
                break; // Den xreiazetai na elegxoume alles korifes
            }
        }

        // An o grafos den paramenei syndedemenos meta tin afairesi tou akrou,
        // simainei oti to akro auto einai aparaitito gia tin syndesimotita (einai akmi tou MST)
        if (!isConnected)
        {
            graph->edges[i].weight=currentEdge.weight; // Epanafora tou barous tou akrou
            // Ektypwsi tou akrou tou Minimum Spanning Tree
            printf("%d <--> %d\tWeight: %d\n", graph->edges[i].source, graph->edges[i].destination, graph->edges[i].weight);
        }
    }
}