//ANTONIS TSIGGERHS 
#ifndef TEST_ERGASIA3_KRUSKAL_H
#define TEST_ERGASIA3_KRUSKAL_H

#endif 
#include <stdio.h>
#include <stdlib.h>

// Struct gia na antiproswpeuei ena akro (edge)
struct Edge {
    int source, destination, baros; // Pinaka kai proorismos tou akrou, kai to baros tou
    struct Edge* nextEdge; // Deiktis sto epomeno akro stin lista geitniasis
};

// Struct gia na antiproswpeuei tin domi Union-Find (gia tin parakolouthisi set)
struct UnionSelection {
    int parent; // O goneas tou sto set
    int UnionID; // To 'rank' i 'id' tou set, gia na kanei pio apodotiki tin syndesi (union)
};

// Struct gia na antiproswpeuei ton grafo Kruskal
struct GraphKruskal {
    int vertices; // O arithmos twn korifwn ston grafo
    struct Edge** adjList; // Pinakas apo deiktes se listes geitniasis (kathe thesi gia mia korifi)
};

// Synartisi gia dimiourgia neou grafou gia ton algorithmo Kruskal
struct GraphKruskal* createGraphKruskal(int Vertices) {
    // Dimiourgei ena grafo me Vertices korifes
    struct GraphKruskal* newGraph = (struct GraphKruskal*)malloc(sizeof(struct GraphKruskal)); // Desmeusi mnimis gia to grafo
    newGraph->vertices = Vertices; // Arxikopoiisi tou arithmou twn korifwn
    newGraph->adjList = (struct Edge**)malloc(Vertices * sizeof(struct Edge*)); // Desmeusi mnimis gia ton pinaka twn listwn geitniasis
    for (int i = 0; i < Vertices; ++i)
    {
        newGraph->adjList[i] = NULL; // Arxikopoiisi kathe listis geitniasis se NULL
    }
    return newGraph; // Epistrefei ton neo grafo
}

// Synartisi gia dimiourgia neou akrou
struct Edge* createEdge(int newSource, int newDestination, int newBaros) {
    // Dimiourgei mia domi edge kai tin epistrefei
    struct Edge* newEdge = (struct Edge*)malloc(sizeof(struct Edge)); // Desmeusi mnimis gia to neo akro
    newEdge->source = newSource; // Arxikopoiisi pinaka
    newEdge->destination = newDestination; // Arxikopoiisi proorismou
    newEdge->baros = newBaros; // Arxikopoiisi barous
    newEdge->nextEdge = NULL; // Arxikopoiisi epomenou akrou se NULL
    return newEdge; // Epistrefei to neo akro
}

// Synartisi gia prosthiki akrou ston grafo Kruskal
void addEdgeKruskal(struct GraphKruskal* graph, int newSource, int newDestination, int newBaros) {
    // Prosthiki akrou apo newSource se newDestination
    struct Edge* newEdge = createEdge(newSource, newDestination, newBaros); // Dimiourgia neou akrou
    newEdge->nextEdge = graph->adjList[newSource]; // Syndesi tou neou akrou me tin arxi tis listis geitniasis tou newSource
    graph->adjList[newSource] = newEdge; // To neo akro ginetai to kefali tis listis tou newSource

    // Epeidi einai undirected grafo, prosthetei kai to akro apo newDestination se newSource
    newEdge = createEdge(newDestination, newSource, newBaros); // Dimiourgia allou neou akrou
    newEdge->nextEdge = graph->adjList[newDestination]; // Syndesi me tin arxi tis listis geitniasis tou newDestination
    graph->adjList[newDestination] = newEdge; // To neo akro ginetai to kefali tis listis tou newDestination
}

// Synartisi Find gia tin Union-Find domi
int FindParent(struct UnionSelection *unionSelectionArray, int i) {
    // Briskei ton gonea enos komvou
    // An o goneas tou i den einai o idios (den einai i riza tou set)
    if (unionSelectionArray[i].parent != i)
    {
        // Recursively briskei ton gonea kai kanei path compression
        unionSelectionArray[i].parent = FindParent(unionSelectionArray, unionSelectionArray[i].parent);
    }
    return unionSelectionArray[i].parent; // Epistrefei ton gonea
}

// Synartisi Union gia tin Union-Find domi
void unionSet(struct UnionSelection unionSelectionArray[], int xchild, int ychild) {
    // Ekteli tin syndesi dyo set (xchild kai ychild) xrisimopoiwntas to UnionID (rank)
    int xparent = FindParent(unionSelectionArray, xchild); // Briskei ton gonea tou xchild
    int yparent = FindParent(unionSelectionArray, ychild); // Briskei ton gonea tou ychild

    // Syndesi tou set me mikrotero rank me to set me megalutero rank
    if (unionSelectionArray[xparent].UnionID <unionSelectionArray[yparent].UnionID)
    {
        unionSelectionArray[xparent].parent = yparent;
    }
    else if (unionSelectionArray[xparent].UnionID > unionSelectionArray[yparent].UnionID)
    {
        unionSelectionArray[yparent].parent = xparent;
    }
    else // An ta rank einai isa, dialegoume ena tuxaia kai ayxanoume to rank tou
    {
        unionSelectionArray[yparent].parent = xparent;
        unionSelectionArray[xparent].UnionID++;
    }
}

// Synartisi sygkrishs gia tin taxinomisi twn akmwn (gia tin qsort)
int compare(const void* a, const void* b) {
    // Synartisi sygkrishs gia taxinomisi akmwn vasismeni sta bari tous
    struct Edge* a1 = *(struct Edge**)a; // Metatropi void* se Edge*
    struct Edge* b1 = *(struct Edge**)b; // Metatropi void* se Edge*
    return a1->baros - b1->baros; // Epistrefei tin diafora twn barwn gia taxinomisi se auksousa seira
}

// Synartisi gia tin ylopoiisi tou algorithmou Kruskal gia MST
void kruskalMinimun_spanning_tree(struct GraphKruskal* graph) {
    int V = graph->vertices; // O arithmos twn korifwn
    struct Edge* finalResult[V]; // Pinakas pou tha apothikeusei to teliko elaxisto spanning tree (MST)
    int sizeofFinal = 0; // Metritis gia ta akra sto finalResult[]
    int sizeOfEdges = 0; // Metritis gia ta taxinomimena akra (allEdges)

    // Desmeusi mnimis gia tous ypokathetes (gia tin Union-Find domi)
    struct UnionSelection* unionSelectionArray = (struct UnionSelection*)malloc(V * sizeof(struct UnionSelection));

    // Arxikopoiisi ypokatheton: kathe korifi einai riza tou dikou tis set kai exei rank 0
    for (int j = 0; j < V; ++j) {
        unionSelectionArray[j].parent = j;
        unionSelectionArray[j].UnionID = 0;
    }

    // Apothikeusi olon twn akmwn tou grafou se enan pinaka
    struct Edge* allEdges[V * V]; // Pinakas gia ola ta akra (V*V einai to megisto plithos akmwn se pliri grafo)
    int numEdges = 0; // Metritis gia to pragmatiko plithos twn akmwn

    // Diaperasi tis listis geitniasis kai prosthiki twn akmwn ston pinaka allEdges
    for (int v = 0; v < V; ++v) {
        struct Edge* tempEges = graph->adjList[v];
        while (tempEges != NULL)
        {
            // Prosthetoume mono mia fora kathe akro (apefktoume dipla akra afou o grafo einai undirected)
            // Gia apofygw diplwn akmwn (px. 0-1 kai 1-0) prosthetoume mono an source <= destination
            // Auto prepei na ginete stin addEdgeKruskal i na elegxete edw pio prosektika
            // Afou to graph->adjList[v] periexei kai ta dyo endia (px 0->1 kai 1->0), theloume mono to ena apo auta.
            // Tha prosthesoume mono an "v < tempEges->destination" gia na apofygoume dipla akra.
            // Pros to paron, an to allEdges periexei ta dipla akra, to qsort kai o algorithmos tha doulepsoun swsta
            // alla apla exoume diplo plithos ston pinaka allEdges.
            if (v <= tempEges->destination) { // elegxos gia na min prosthesw to idio akro 2 fores (px 0-1 kai 1-0)
                allEdges[numEdges++] = tempEges;
            }
            tempEges = tempEges->nextEdge;
        }
    }
    // Taxinomisi olon twn akmwn se auksousa seira vasismeni sta bari tous
    qsort(allEdges, numEdges, sizeof(struct Edge*), compare);

    // Epanalipsi os pou na vroume V-1 akra gia to MST i os pou na exetastoume ola ta akra
    while (sizeofFinal < V - 1 && sizeOfEdges < numEdges)
    {
        struct Edge* next_edge = allEdges[sizeOfEdges++]; // Epilogei tou epomenou mikroterou akrou

        int xparent = FindParent(unionSelectionArray, next_edge->source); // Briskei ton gonea tou source tou akrou
        int ychild = FindParent(unionSelectionArray, next_edge->destination); // Briskei ton gonea tou destination tou akrou

        // An oi goneis einai diaforetikoi, simainei oti den einai idi sto idio set (den dimiourgoun kyklous)
        if (xparent != ychild)
        {
            finalResult[sizeofFinal++] = next_edge; // Prostithetai to akro sto MST
            unionSet(unionSelectionArray, xparent, ychild); // Syndesi twn dyo set
        }
    }
    // Ektypwsi tou elaxistou spanning tree
    printf("\nEdges minimum spanning tree created with Kruskal algorithm :\n");
    for (sizeOfEdges = 0; sizeOfEdges < sizeofFinal; ++sizeOfEdges)
        printf("%d <--> %d\tWeight: %d\n", finalResult[sizeOfEdges]->source, finalResult[sizeOfEdges]->destination, finalResult[sizeOfEdges]->baros);
}
