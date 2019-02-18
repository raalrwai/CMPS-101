//Rami ALrwais
//#1403536
//CS 101
//pa5
//FindComponents.c
//Finds strongest connected components of Graph
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"Graph.h"
#include"List.h"
#define null NULL
#define white 10
#define gray 15
#define black 20
#define INF -1
#define NIL -1
#define UNDEF -1
#define string_maxl 9999
int main(int argc, char const *argv[]){
  if(argc != 3){
    fprintf(stderr, "%s\n", "Invalid input");
    exit(1);
  }
  FILE* in = fopen(argv[1], "r");
  FILE* out = fopen(argv[2], "w");
  char line[string_maxl +1];

  fgets(line, string_maxl, in);
  int number_V = atoi(line);
  List order = newList();
  Graph new_G = newGraph(number_V);
  while(1){
    fgets(line, string_maxl, in);
    char* token = strtok(line, " ");
    int first = atoi(token);
    token = strtok(NULL, " ");
    int second = atoi(token);
    if(first == second){
      if(first == 0){
        break;
      }
    }
    addArc(new_G, first, second);
  }
  for(int i = 1; i <= number_V; i++){
    append(order, i);
  }
  fprintf(out, "Adjacency list representation of G:\n");
  printGraph(out, new_G);
  Graph t = transpose(new_G);
  DFS(new_G, order);
  DFS(t, order);
  moveFront(order);
  int compNum = 0;
  while(index(order)>= 0){
    int vert = get(order);
    if(getParent(t, vert)==NIL){
      compNum++;
    }
    moveNext(order);
  }
  moveFront(order);
  List* print = calloc(compNum, sizeof(List));
  fprintf(out, "\nG contains %d strongly connected components:\n", compNum);
  compNum = -1;
  while(index(order) >= 0){
    int vertex = get(order);
    if(getParent(t, vertex) == NIL){
      compNum ++;
      print[compNum] = newList();
      append(print[compNum], vertex);
    } else {
      append(print[compNum], vertex);
    }
    moveNext(order);
  }
  for(int i = compNum; i >= 0; i--){
    fprintf(out, "Component%d: ", (compNum - i + 1));
    printList(out, print[i]);
    freeList(&print[i]);
  }
  free(print);
  freeList(&order);
  freeGraph(&new_G);
  freeGraph(&t);

  fclose(in);
  fclose(out);
  return 0;
}
