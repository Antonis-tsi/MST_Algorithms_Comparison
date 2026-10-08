//ANTONIS TSIGGERHS 2026
//06/06/2025
//ERGASIA 3 OMADA 8

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "kruskal.h" // Periexei tis synartiseis gia ton algorithm Kruskal
#include "reverse_delete.h" // Periexei tis synartiseis gia ton algorithm Reverse Delete
#include <unistd.h>
#include <string.h>


// Struct gia enan komvo tis listas geitniasis
struct AdjListNode {
    int destination; // O proorismos tou akrou
    int baros; // To baros tou akrou
    struct AdjListNode* nextlist; // Deiktis ston epomeno komvo sti lista
};

// Struct gia ti lista geitniasis
struct AdjList {
    struct AdjListNode* header; // Deiktis ston arxiko komvo tis listas
};

// Struct gia to grafo me mia lista apo listes geitniasis kai ton arithmo ton korifon 'Vertices'
struct Graph {
    int Vertices; // Arithmos korifon
    struct AdjList* list; // Pinakas apo listes geitniasis
};

// Diloseis synartiseon tou algorithmou Prim
struct AdjListNode* newAdjListNode(int destination, int baros); // Dimiourgei ena neo komvo listas geitniasis
struct Graph* createGraph(int Vertices); // Dimiourgei ena neo grafo
void addEdge(struct Graph* current_graph, int source, int destination, int baros); // Prostithei ena akro sto grafo
int minKey(int *cost, bool *visited, int Vertices); // Briskei tin korifi me to elaxisto kostos
void print_minimum_spanning_tree(int *parent, int graphSize, int** graph); // Typonei to elaxisto spanning tree
void primMST(struct Graph* graph, int** graphMatrix); // Ylopoiisi tou algorithmou Prim
void printGraph(struct Graph* graph); // Typonei to grafo (gia debugging kyrios)

int main() {

    int numVertices=0, percentageToRemove=0; // Arithmos korifon kai pososto akmon pros afairesi
    double sum=0,sum2=0,sum3=0; // Athroismata xronon gia ton ypologismo mesou orou
    double cpu_time_used_for_prim[4]; // Pinakas gia tous xronous tou Prim
    double cpu_time_used_for_kruskal[4]; // Pinakas gia tous xronous tou Kruskal
    double cpu_time_used_for_Reverse_delete[4]; // Pinakas gia tous xronous tou Reverse Delete
    clock_t start1, end1, start2, end2, start3 , end3; // Metablites gia metrisi xronou

    // Eisagogi arithmou korifon apo ton xristi (prepei na einai toulaxiston 2)
    do{
        printf("Enter the number of nodes: ");
        scanf("%d", &numVertices);
    }while(numVertices<2);

    // Eisagogi posostou akmon pros afairesi (apo 0% eos 100%)
    do
    {
        printf("Enter the percentage of edges to remove: ");
        scanf("%d", &percentageToRemove);
    }while(percentageToRemove>100 || percentageToRemove<0);

    // Epanalipsi 4 fores gia na paroume mesous orous xronon
    for(int k=0;k<4;k++)
    {
        // Dimiourgia domon gia kathe algorithmo kai arxikopoiisi
        int numEdges = 0; // Arithmos akmon (tha sypologistei stin poreia)
        struct Graph *graph = createGraph(numVertices); // Grafo gia Prim
        struct GraphKruskal *graphKruskal = createGraphKruskal(numVertices); // Grafo gia Kruskal
        GraphReverse* graphReverse = createGraphReverse(numVertices, numEdges); // Grafo gia Reverse Delete

        srand(time(NULL)); // Arxikopoiisi tou pseudotixaiou generatora arithmon (me basi ton xrono)
        sleep(2); // Pause 2 deuterolepta (gia na min exoun oles oi epanalipseis ton idio seed an ektelountai grigora)

        // Dimiourgia tixaiou grafou (idia akra gia olous tous algorithmous)
        for (int i = 0; i < numVertices; ++i) {
            for (int j = i + 1; j < numVertices; ++j) {
                // An to tixaio pososto einai megalytero i iso apo to percentageToRemove, prosthes akro
                if (rand() % 100 >= percentageToRemove) {
                    int weight1 = rand() % 100 + 1; // Tixaio baros akrou
                    addEdge(graph, i, j, weight1); // Prosthiki akrou gia Prim
                    addEdgeKruskal(graphKruskal, i, j, weight1); // Prosthiki akrou gia Kruskal
                    addEdgeReverse(graphReverse, i, j, weight1); // Prosthiki akrou gia Reverse Delete
                }
            }
        }

        // Desmeusi mnimis gia ton pinaka geitniasis (gia Prim)
        int **graphMatrix = (int **) malloc(numVertices * sizeof(int *));
        for (int i = 0; i < numVertices; ++i)
            graphMatrix[i] = (int *) malloc(numVertices * sizeof(int));

        // Metatropi tis listas geitniasis se pinaka geitniasis
        for (int i = 0; i < numVertices; ++i) {
            struct AdjListNode *temp = graph->list[i].header;
            while (temp != NULL) {
                graphMatrix[i][temp->destination] = temp->baros;
                temp = temp->nextlist;
            }
        }

        printf("======== Graph#%d ========\n",k+1); // Ektypwsi tou arithmou tou grafou
        //printGraph(graph); //  typonei olo to grafo

        printf("Prim : \n");
        start1 = clock(); // Enarksi metrisis xronou gia Prim
        primMST(graph, graphMatrix); // Ektelesi algorithmou Prim
        end1 = clock(); // Lixi metrisis xronou gia Prim
        cpu_time_used_for_prim[k]= (double)(end1 - start1) / (CLOCKS_PER_SEC); // Ypologismos xronou se deuterolepta
        sum = sum + cpu_time_used_for_prim[k]; // Prosthiki sto synoliko athroisma xronou gia Prim
        printf("-------------------------------\n");

        printf("Kruskal : \n");
        start2 = clock(); // Enarksi metrisis xronou gia Kruskal
        kruskalMinimun_spanning_tree(graphKruskal); // Ektelesi algorithmou Kruskal
        end2 = clock(); // Lixi metrisis xronou gia Kruskal
        cpu_time_used_for_kruskal[k]= (double)(end2 - start2) / (CLOCKS_PER_SEC); // Ypologismos xronou se deuterolepta
        sum2 = sum2 + cpu_time_used_for_kruskal[k]; // Prosthiki sto synoliko athroisma xronou gia Kruskal
        printf("-------------------------------\n");

        printf("Reverse-delete : \n");
        start3 = clock(); // Enarksi metrisis xronou gia Reverse Delete
        reverseDelete(graphReverse); // Ektelesi algorithmou Reverse Delete
        end3 = clock(); // Lixi metrisis xronou gia Reverse Delete
        cpu_time_used_for_Reverse_delete[k]= (double)(end3 - start3) / (CLOCKS_PER_SEC); // Ypologismos xronou se deuterolepta
        sum3 = sum3 + cpu_time_used_for_Reverse_delete[k]; // Prosthiki sto synoliko athroisma xronou gia Reverse Delete
        printf("-------------------------------\n");
    }

    // Ektypwsi xronon gia kathe epanalipsi
    for(int q=0;q<4;q++) {
        printf("O xronos poy etreje o Prim thn %d fora einai :(prim)%lf ms\n", q + 1, cpu_time_used_for_prim[q]);
        printf("-------------------------------\n");
        printf("O xronos poy etreje o Kruskal thn %d fora einai :(kruskal)%lf ms\n", q + 1, cpu_time_used_for_kruskal[q]);
        printf("-------------------------------\n");
        printf("O xronos poy etreje o Reverse-delete thn %d fora einai :(Reverse-delete)%lf ms\n", q + 1, cpu_time_used_for_Reverse_delete[q]);
        printf("-------------------------------\n");
    }

    // Ektypwsi mesou orou xronon gia olous tous algorithmous
    printf("Average time of prim is:(prim)%lf ms\n",sum / (double) 4); // Mesos oros xronou gia Prim
    printf("Average time of kruskal is:(kruskal)%lf ms\n",sum2 / (double) 4); // Mesos oros xronou gia Kruskal
    printf("Average time of Reserve delete is:(Reverse-delete)%lf ms\n",sum3 / (double) 4); // Mesos oros xronou gia Reverse Delete

    return 0; // Epistrofi 0 gia epityxi ektelesi
}

// Synartisi pou dimiourgei ena neo komvo listas geitniasis
struct AdjListNode* newAdjListNode(int destination, int baros)
{
    struct AdjListNode* newNode_make= (struct AdjListNode*)malloc(sizeof(struct AdjListNode)); // Desmeusi mnimis
    newNode_make->destination = destination; // Arxikopoiisi proorismou
    newNode_make->baros = baros; // Arxikopoiisi barous
    newNode_make->nextlist = NULL; // O epomenos komvos einai NULL arxika
    return newNode_make; // Epistrofi tou neou komvou
}

// Synartisi pou dimiourgei ena neo grafo
struct Graph* createGraph(int Vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph)); // Desmeusi mnimis gia to grafo
    graph->Vertices = Vertices; // Arxikopoiisi arithmou korifon
    graph->list = (struct AdjList*)malloc(Vertices * sizeof(struct AdjList)); // Desmeusi mnimis gia ton pinaka liston geitniasis
    // Arxikopoiisi tou header kathe listas se NULL
    for (int i = 0; i < Vertices; ++i)
        graph->list[i].header = NULL;
    return graph; // Epistrofi tou neou grafou
}

// Synartisi pou prosthetei ena akro se enan undirected grafo
void addEdge(struct Graph* current_graph, int source, int destination, int baros)
{
    // Prosthiki akrou apo source se destination
    struct AdjListNode* newNode_make= newAdjListNode(destination, baros); // Dimiourgia neou komvou
    newNode_make->nextlist = current_graph->list[source].header; // Syndesi me tin arxi tis listas tou source
    current_graph->list[source].header = newNode_make; // O neos komvos ginetai to header

    // Afou einai undirected, prosthes akro kai apo destination se source
    newNode_make = newAdjListNode(source, baros); // Dimiourgia allou neou komvou
    newNode_make->nextlist = current_graph->list[destination].header; // Syndesi me tin arxi tis listas tou destination
    current_graph->list[destination].header = newNode_make; // O neos komvos ginetai to header
}

// Synartisi pou briskei tin korifi me to elaxisto kostos pou den exei episkeftei
int minKey(int *cost, bool *visited, int Vertices) {
    int min = INT_MAX; // Arxikopoiisi elaxistou me tin megalyteri dynati timi
    int min_vertex_ID; // Metabliti gia to ID tis korifis me to elaxisto kostos

    // Perasma olon ton korifon
    for (int i = 0; i < Vertices; ++i)
    {
        // An i korifi den exei episkeftei kai to kostos tis einai mikrotero apo to trexon elaxisto
        if (visited[i] == false && cost[i] < min)
        {
            min = cost[i]; // Enimerosi elaxistou kostous
            min_vertex_ID = i; // Enimerosi ID tis korifis
        }
    }
    return min_vertex_ID; // Epistrofi tou ID tis korifis me to elaxisto kostos
}

// Synartisi pou typonei to elaxisto spanning tree tou algorithmou Prim
void print_minimum_spanning_tree(int *parent, int graphSize, int** graph) {
    printf("The algorithm with the Adjacency Lists gives the following minimum spanning tree:\n");
    // Perasma apo ti deuteri korifi (i proti einai i riza)
    for (int j = 1; j < graphSize; ++j)
    {
        // Ektypwsi tou akrou kai tou barous tou (undirected)
        printf("%d <--> %d :weight: %d\n", parent[j], j, graph[j][parent[j]]);
    }
}

// Ylopoiisi tou algorithmou Prim gia EYRESH elaxistou spanning tree
void primMST(struct Graph* graph, int** graphMatrix){
    int VerticesNumber = graph->Vertices; // Arithmos korifon tou grafou
    int parent[VerticesNumber]; // Pinakas pou apothikeuei ton "gonea" kathe korifis sto MST
    int cost[VerticesNumber]; // Pinakas pou apothikeuei to elaxisto baros akrou pou syndeei mia korifi me to MST
    bool visited[VerticesNumber]; // Pinakas pou deixnei an mia korifi exei episkeftei (perilifthei sto MST)

    // Arxikopoiisi olon ton koston se INT_MAX kai olon ton visited se false
    for (int v = 0; v < VerticesNumber; ++v)
    {
        cost[v] = INT_MAX;
        visited[v] = false;
    }

    cost[0] = 0; // To kostos tis protis korifis einai 0 (einai i arxi tou MST)
    parent[0] = -1;  // H proti korifi einai i riza, den exei gonea

    // O algorithmos ekteloumai N-1 fores gia N korifes
    for (int count = 0; count < VerticesNumber - 1; ++count)
    {
        int u = minKey(cost, visited, VerticesNumber); // Brei tin korifi me to elaxisto kostos pou den exei episkeftei

        visited[u] = true; // Markarei tin korifi os episkefthike (tin prosthetei sto MST)

        // Perasma olon ton geitonon tis korifis u
        struct AdjListNode* temp = graph->list[u].header;
        while (temp != NULL)
        {
            int v = temp->destination; // O geitonas
            int weight = temp->baros; // To baros tou akrou (u, v)

            // An o geitonas den exei episkeftei kai to baros tou akrou (u, v) einai mikrotero apo to trexon kostos tou geitona
            if (visited[v] == false && weight < cost[v])
            {
                parent[v] = u; // O goneas tou v ginetai o u
                cost[v] = weight; // To kostos tou v ginetai to baros tou akrou (u, v)
            }
            temp = temp->nextlist; // Proxora ston epomeno geitona
        }
    }

    print_minimum_spanning_tree(parent, VerticesNumber, graphMatrix); // Typonei to teliko MST
}

// Synartisi pou typonei to grafo (gia elegxo)
void printGraph(struct Graph* graph) {
    // Perasma apo kathe korifi tou grafou
    for (int v = 0; v < graph->Vertices; ++v)
    {
        struct AdjListNode* temp = graph->list[v].header; // Proxora sto header tis listas geitniasis
        while (temp) {
            printf("Node %d: %d->%d W: %d\n", v, v, temp->destination, temp->baros); // Typonei to akro kai to baros
            temp = temp->nextlist; // Proxora ston epomeno komvo
        }
    }
}