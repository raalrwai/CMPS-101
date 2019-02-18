//Rami Alrwais
//CS 101
//Lex.java
//ID #1403536
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "List.h"
#define strng_max_len 160
#define array_max_len 1500

int main(int argc, char* argv[]) {
  if(argc != 3) {//throws error for wrong number of args 
    fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
    exit(1);
  }
  char** inp_array = malloc(array_max_len*sizeof(char*));
  FILE* in = fopen(argv[1], "r");
  FILE* out = fopen(argv[2], "w");
  char line[strng_max_len +1];
  int lineNumber = 0;

  if(in == NULL) {
    fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
    exit(1);
  }
  if(out==NULL){
    fprintf(stderr, "Unabel to open file %s for writing\n", argv[2]);
  }
  //counts number of lines
  while(fgets(line, strng_max_len, in)!=NULL){
    inp_array[lineNumber] = malloc((strlen(line)+1)*sizeof(char));
    sprintf(inp_array[lineNumber], "%s", line);
    lineNumber++;
  }

  List newL = newList();
  int i = 0;
  int index_status = -1;
  //sorting algorithm
  for(i=0; i< lineNumber; i++){
    if(length(newL)==0){
      append(newL, i);
    }else{
      moveFront(newL);
      while(index(newL)>=0){
        index_status = get(newL);
        if(strcmp(inp_array[index_status], inp_array[i]) >= 0){
          insertBefore(newL, i);
          break;
        }
        moveNext(newL);
      }
      if (index(newL) == -1) {
        append(newL, i);
      }
    }
  }

  //write to output file
  moveFront(newL);
  while(index(newL)>=0){
    fprintf(out, "%s", inp_array[get(newL)]);
    moveNext(newL);
  }for(i=0; i<lineNumber; i++){
    free(inp_array[i]);
  }
  //free memeory and close files
  free(inp_array);
  freeList(&newL);
  fclose(in);
  fclose(out);
  return 0;
}
