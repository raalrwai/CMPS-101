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
  int *discover;
  int *finish;
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
  graph->discover = calloc(n+1, sizeof(int));
  graph->finish = calloc(n+1, sizeof(int));
  graph->number_V = n;
  graph->number_E = 0;
  graph->source = NIL;
  for(int i = 1; i < n + 1; i++) {
    graph->array[i] = newList();
    graph->color[i] = white;
    graph->parent[i] = NIL;
    graph->discover[i] = UNDEF;
    graph->finish[i] = UNDEF;
  }
  return graph;
}
void freeGraph(Graph* pG) {//free graph memory
  // Graph tmp = *pG;
  // for(int i = 1; i <= getOrder(*pG); i++)
  if(pG!=NULL && *pG!=NULL)
  {
    makeN(*pG);
    //  freeList(&((*pG)->array[i]));
    free((*pG)->array);
    free((*pG)->color);
    free((*pG)->parent);
    free((*pG)->discover);
    free((*pG)->finish);
    free((*pG)->distance);
    free((*pG));
    *pG = NULL;

  }
}

void makeN(Graph G)
{
  if(G == NULL){
    fprintf(stderr, "Graph error: getOrder() called on null Graph reference\n");
    exit(1);
  }

  G->number_E = 0;
  G->source = NIL;
  for(int i=1; i<=G->number_V; i++)
  {
    G->parent[i] = NIL;
    G->distance[i] = INF;
    G->color[i] = 0;
    clear(G->array[i]);
  }
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
int getParent(Graph G, int u) {// get parent of graph
  if(G == NULL) {
    fprintf(stderr, "Graph error: getParent() called on null Graph reference\n");
    exit(1);
  }

  if(u <1 || u > G->number_V){
    fprintf(stderr, "error");
    exit(1);
  }
  return G->parent[u];
}
int getDiscover(Graph G, int u){ /* Pre: 1<=u<=n=getOrder(G) */
  if(G==NULL){
    fprintf(stderr, "Error: getDiscover() called on NULL Graph");
    exit(1);
  }

  if(u <1 || u > G->number_V){
    fprintf(stderr, "error");
    exit(1);
  }
  return G->discover[u];

}
int getFinish(Graph G, int u){ /* Pre: 1<=u<=n=getOrder(G) */
  if(G==NULL){
    fprintf(stderr, "Error: getFinish() called on NULL Graph");
    exit(1);
  }

  if(u <1 || u > G->number_V){
    fprintf(stderr, "error");
    exit(1);
  }
  return G->finish[u];
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
Graph transpose(Graph G) {
  Graph t = newGraph(getOrder(G));
  for(int i = 1; i <= getOrder(G); i++) {
    moveFront(G->array[i]);
    if(length(G->array[i]) == 0) continue;
    else {
      while(index(G->array[i]) != -1) {
        addArc(t, get(G->array[i]), i);
        moveNext(G->array[i]);
      }
    }
  }
  return t;
}

void visit(Graph G, List S, int u, int *time){

  G->discover[u] = ++*time;
  G->color[u] = gray;
  //moveFront(G->array[u]);
  List l = G->array[u];
  if(length(l) > 0){
    for(moveFront(l); index(l)>= 0; moveNext(l)){
      int y = get(l);
      if(G->color[y] == white) {
        G->parent[y] = u;
        visit(G, S, y, time);
      }
    }
  }
  G->color[u] = black;
  G->finish[u] = ++*time;
  prepend(S, u);
}

void DFS(Graph G, List s) {
  if(G == NULL) {
    fprintf(stderr, "Error : Null input in DFS");
    exit(1); 
  }
  if(s == NULL){
    fprintf(stderr, "error");
    exit(1);
  }
  if(length(s) != G->number_V) {
    fprintf(stderr, "Precondition Failure : List length != G->order in DFS");
    exit(1); 
  }
  // List newL = newList();
  for(int i = 1; i <= G->number_V; i++) {
    G->color[i] = white;
    G->parent[i] = NIL;
  }
  int time = 0;
  for(moveFront(s); index(s) >= 0; moveNext(s)) {
    int pre = get(s);
    if(G->color[pre] == white) {
      visit(G, s, pre, &time);
    }  
  }
  for(int i=1; i<=G->number_V; i++){
    deleteBack(s); 
  }
}

Graph copyGraph(Graph G) {
  Graph new_G = newGraph(G->number_V);
  for(int i = 0; i < G->number_V; i++) {
    List * tmp = &G->array[i];

    for(moveFront(*tmp); index(*tmp) >= 0; moveNext(*tmp)) {
      addArc(new_G, i+1, get(*tmp)+1);
    }
  }

  return new_G;
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
