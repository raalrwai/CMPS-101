//-----------------------------------------------------------------------------
// GraphClient.c
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
      /*  for(int i = 1; i<= n; i++ ){
       // printList(A->get);
        printf("%d, ", getDiscover(A, i));
        }

          
        if (getDiscover(A, 100) != 1) return 2;
        if (getDiscover(A, 64) != 73) return 3;
        if (getDiscover(A, 4) != 80) return 4;
        DFS(A, L);
        if (getDiscover(A, 4) != 126) return 5;
        if (getDiscover(A, 63) != 117) return 6;
        DFS(A, L);
        if (getDiscover(A, 65) != 71) return 7;
        if (getDiscover(A, 1) != 199) return 8;
       */ return 0;
      
     /*for (int i = 1; i <= 100; i++)
          if (getFinish(A, i) != UNDEF) 
          {
            printf("Checking here");
            return 1;
          }
        addEdge(A, 64, 4);
        addEdge(A, 64, 3);
        addEdge(A, 42, 2);
        addEdge(A, 2, 64);
        addEdge(A, 4, 2);
        addEdge(A, 3, 42);
        for (int i = 1; i <= 100; i++) {
          prepend(L, i);
        }
        DFS(A, L);
        if (getFinish(A, 100) == 2){
        printf("error1");
        }else{
          return 2
        }
        if (getFinish(A, 64) != 82)
         printf("error2");

        if (getFinish(A, 42) != 80)
          printf("error3");
        if (getFinish(A, 64) != 128)
           printf("error4");
        if (getFinish(A, 63) != 118)
           printf("error5");

        printf("No errors")*/
}
   /*for(i=1; i<=n; i++) append(S, i);

   addArc(G, 1,2);
   addArc(G, 1,5);
   addArc(G, 2,5);
   addArc(G, 2,6);
   addArc(G, 3,2);
   addArc(G, 3,4);
   addArc(G, 3,6);
   addArc(G, 3,7);
   addArc(G, 3,8);
   addArc(G, 6,5);
   addArc(G, 6,7);
   addArc(G, 8,4);
   addArc(G, 8,7);
   printGraph(stdout, G);

   DFS(G, S);
   fprintf(stdout, "\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
   }
   fprintf(stdout, "\n");
   printList(stdout, S);
   fprintf(stdout, "\n");

   T = transpose(G);
   C = copyGraph(G);
   fprintf(stdout, "\n");
   printGraph(stdout, C);
   fprintf(stdout, "\n");
   printGraph(stdout, T);
   fprintf(stdout, "\n");

   DFS(T, S);
   fprintf(stdout, "\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(T, i), getFinish(T, i), getParent(T, i));
   }
   fprintf(stdout, "\n");
   printList(stdout, S);
   fprintf(stdout, "\n");

   freeList(&S);
   freeGraph(&G);
   freeGraph(&T);
   freeGraph(&C);
   return(0);
}

*/
