#ifndef _List_H_INCLUDE_
#define _List_H_INCLUDE_
 
#include<stdio.h>

typedef struct ListObj* List;
 // Constructors-Destructors ---------------------------------------------------
 // Returns reference to new empty List object.
 List newList(void);
 void freeList(List* pL);
//exported type
  
 // Access functions -----------------------------------------------------------
 int length(List L);
 int index(List L);
 int front(List L);
 int back(List L);
 int get(List L);
 int equals(List A, List B);
// // Manipulation procedures ----------------------------------------------------
// // Re-sets this List to the empty state.
 void clear(List L);
 void moveFront(List L);
 void moveBack(List L);
 void movePrev(List L);
 void moveNext(List L);
 void prepend(List L, int data);
 void append(List L, int data);
 void insertBefore(List L, int data);
 void insertAfter(List L, int data);
 void deleteFront(List L);
 void deleteBack(List L);
 void delete(List L);
 //other functions
 void printList(FILE* out, List L);
 List copyList(List L);
 #endif
