//-----------------------------------------------------------------------------
// GraphTest.c
// Test client for the Graph ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"Graph.h"


int main(int argc, char* argv[]){
   int i, n=100;
   List S = newList();
   Graph A = newGraph(100);
//   Graph T=NULL, C=NULL;
     List L = newList();

        for (int i = 1; i <= 100; i++)
          if (getDiscover(A, i) != UNDEF) return 1;
        addArc(A, 64, 4);
        addArc(A, 64, 3);
        addArc(A, 42, 2);
        addArc(A, 2, 64);
        addArc(A, 4, 2);
        addArc(A, 3, 42);
        for (int i = 1; i <= 100; i++) {
          prepend(L, i);
        }
        DFS(A, L);
}
