//Rami Alrwais
//CS 101
//ID #1403536
//Graph.c
//Uses List ADT to perform graph operations
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <assert.h>
#include "List.h"
#include "Graph.h"
#define white 10
#define gray 15
#define black 20
#define INF -1
#define NIL -1
// structs
typedef struct GraphObj {
  List *array;
  int *color;//visit status
  int *parent;//reference
  int *distance;//distance between
  int number_V; // number of vertices
  int number_E; // number of edges
  int source; // lead
} GraphObj;

// constructors/deconstructors
Graph newGraph(int n) {
  Graph graph = malloc(sizeof(struct GraphObj));
  graph->array = calloc(n + 1, sizeof(List));
  graph->color = calloc(n + 1, sizeof(int));
  graph->parent = calloc(n + 1, sizeof(int));
  graph->distance = calloc(n + 1, sizeof(int));
  graph->number_V = n;
  graph->number_E = 0;
  graph->source = NIL;
  for(int i = 1; i < n + 1; i++) {
    graph->array[i] = newList();
    graph->color[i] = white;
    graph->parent[i] = NIL;
    graph->distance[i] = INF;
  }
  return graph;
}
void freeGraph(Graph* pG) {//free graph memory
  // Graph tmp = *pG;
  for(int i = 1; i <= getOrder(*pG); i++)
    freeList(&((*pG)->array[i]));
  free(&(*pG)->array);
  free(&(*pG)->color);
  free(&(*pG)->parent);
  free(&(*pG)->distance);
  free(&(*pG));
  *pG = NULL;
}
int getOrder(Graph G) {//return order
  if(G == NULL) {
    fprintf(stderr, "Graph error: getOrder() called on null Graph reference\n");
    exit(1);
  }
  return G->number_V;
}
int getSize(Graph G) {//return size
  if(G == NULL) {
    fprintf(stderr, "Graph error: getSize() called on null Graph reference\n");
    exit(1);
  }
  return G->number_E;
}
int getSource(Graph G) {//get source of graph
  if(G == NULL) {
    fprintf(stderr, "Graph error: getSource() called on null Graph reference\n");
    exit(1);
  }
  return G->source;
}
int getParent(Graph G, int u) {// get parent of graph
  if(G == NULL) {
    fprintf(stderr, "Graph error: getParent() called on null Graph reference\n");
    exit(1);
  }
  return G->parent[u];
}
int getDist(Graph G, int u) {//get distance of graph
  if(G == NULL) {
    fprintf(stderr, "Graph error: getDist() called on null Graph reference\n");
    exit(1);
  }
  if(getSource(G) == NIL) return INF;
  return G->distance[u];
}
void getPath(List L, Graph G, int u) {
  if(u == getSource(G))
    append(L, getSource(G));
  else if(G->parent[u] == NIL)
    append(L, NIL);
  else {
    getPath(L, G, G->parent[u]);
    append(L, u);
  }
}
void makeNull(Graph G){
  Graph input = G;
  int howMuch = input->number_V;
  for(int i = 1; i <= howMuch; i++){
    clear(input->array[i]);
    input->color[i] = white;
    input->parent[i] = NIL;
    input->distance[i] = INF;
  }
  G->number_E = 0;
  G->source = NIL;

}
void IS(List list, int x){
  if (length(list) == 0){
    append(list, x);
    return;
  }
  for(moveFront(list); index(list) != -1; moveNext(list)){
    if(x < get(list)){
      insertBefore(list, x);
      break;
    }
  }
  if(index(list) == -1){
    append(list, x);
  }
}

void addArc(Graph G, int u, int v) {
  if ( G == NULL ) {
    printf("Graph Error: calling addArc() on NULL GraphRef\n");
    exit(1);
  }
  if ( u < 1 || u > getOrder(G) ) {
    printf("Graph Error: calling addArc() on u non-existent within bounds of order\n");
    exit(1);
  }
  if ( v < 1 || v > getOrder(G) ) {
    printf("Graph Error: calling addArc() on v non-existent within bounds of order\n");
    exit(1);
  }
  IS(G->array[u],v);
  ++G->number_E;
}
void addEdge(Graph G, int u, int v){

  if (G == NULL) {
    printf("Error: addEdge called on NULL Graph pointer\n");
    exit(1);
  } else if (u < 1 || v < 1 || u > getOrder(G) || v > getOrder(G)) {
    printf("Error: addEdge called with invalid indices.\n");
    exit(1);
  } else if (u == v) {
    printf("Error: addEdge called with two identical indices.\n");
    exit(1);
  }
  // Sorted insert v into array[u]
  List U = G->array[u];
  IS(U, v);
  // Sorted insert u into array[V]
  List V = G->array[v];
  IS(V, u);
  // Update G's edge field
  ++G->number_E;
}
void BFS(Graph G, int s){//return BFS of graph
  G->source = s;
  List queue = newList();
  for(int i = 1; i <= getOrder(G); i++){
    G->color[i] = white;
    G->parent[i] = NIL;
    G->distance[i] = INF;
  }
  G->color[s] = gray;
  G->distance[s] = 0;
  G->parent[s] = NIL;

  prepend(queue, s);
  while(length(queue)> 0){
    int process = front(queue);
    deleteFront(queue);
    List Adj = G->array[process];
    moveFront(Adj);
    while(index(Adj) >= 0){
      int checker = get(Adj);
      if(G->color[checker] == white){
        G->color[checker] = gray;
        G->distance[checker] = G->distance[process] + 1;
        G->parent[checker] = process;
        append(queue, checker);
      }
      moveNext(Adj);
    }
    G->color[process] = black;
  }
  freeList(&queue);
}

void printGraph(FILE* out, Graph G){
  for (int i = 1; i <= getOrder(G); i++){
    List list = G->array[i];
    fprintf(out, "%d:", i);
    for (moveFront(list); index(list) != -1; moveNext(list)){
      fprintf(out, " %d", get(list));
    }
    fprintf(out, "\n");
  }

}
