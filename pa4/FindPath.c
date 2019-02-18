//Rami Alrwais
//CS 101
//pa4
//FindPath.c
//Performs graph operations using Graph and List ADT's
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define string_max_length 9999
#include "Graph.h"
#include "List.h"
int main(int argc, char const *argv[]){
  if( argc != 3){
    fprintf( stderr,"%s\n", "Invalid input number");
    exit(1);
  }
  FILE* in = fopen(argv[1], "r");
  FILE* out = fopen(argv[2], "w");
  char line[string_max_length + 1];
  fgets(line, string_max_length, in);
  int num_V = atoi(line);
  Graph new_G = newGraph(num_V);
  while(1){
    fgets(line, string_max_length, in);
    char* tok = strtok(line, " ");
    int first = atoi(tok);
    tok = strtok(NULL, " ");
    int second = atoi(tok);
    if(first == second){
      if(first == 0){
        break;
      }

    }
    addEdge(new_G, first, second);
  }
  printGraph(out, new_G);

  while(1){
    fgets(line, string_max_length, in);
    char* tok = strtok(line, " ");
    int first = atoi(tok);
    tok = strtok(NULL, " ");
    int second = atoi(tok);
    if(first == second){
      if (first == 0){
        break;
      }
    }

    BFS(new_G, first);
    int D = getDist(new_G, second);
    List path = newList();
    getPath(path, new_G, second);
    if(D >= 0){
      fprintf(out, "\nThe distance from %d to %d is %d\n", first, second, getDist(new_G, second));
      fprintf(out, "A shortest %d-%d path is:", first, second);
      printList(out, path);
    }else{
      fprintf(out, "\nThe distance from %d to %d is infinity\n", first, second);
      fprintf(out, "No %d-%d path exists", first, second);
    }
    freeList(&path);
  }
  freeGraph(&new_G);

  fclose(in);
  fclose(out);
  return 0;
}
