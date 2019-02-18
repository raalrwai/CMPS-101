//Rami Alrwais
//Pa2
//ID #1403536
// List.c
// Implementation file for List ADT

#include "List.h"
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj{
  int data;
  struct NodeObj* next;
  struct NodeObj* prev;
} NodeObj;

typedef NodeObj* Node;
typedef struct ListObj{
  Node front;
  Node back;
  Node current;
  int length;
  int cursorIndex;
} ListObj;

void freeNode(Node* pN){
  if(*pN != NULL && pN != NULL)
  {
    (*pN)->next = NULL;
    (*pN) = NULL;
  }
}
//constructors, Deconstructors
Node newNode(int data){
  Node N = malloc(sizeof(NodeObj));
  assert(N!=NULL);
  N->data = data;
  N->next = NULL;
  N->prev = NULL;
  return(N);
}

List newList(void){
  List newList = malloc(sizeof( ListObj));
  assert(newList!=NULL);
  newList->length = 0;
  newList->cursorIndex = -1;
  newList->front = NULL;
  newList->back = NULL;
  newList->current = NULL;
  return newList;
}
// freeQueue()
// Frees all heap memory associated with Queue *pQ, and sets *pQ to NULL.S
void freeList(List* pL){
  if(*pL != NULL && pL != NULL){
    clear(*pL);
    free(*pL);
    *pL = NULL;

  }
}
// Access functions -----------------------------------------------------------
int length(List L){
  if(L==NULL){
    assert(L);
  }
  return L->length;
}
int index(List L){
  if(L==NULL){
    assert(L);
  }// if(L->length==0){
  // return -1;}
  return L->cursorIndex;
}

//Pre: L must be defined and list must not be empty
//returns front element
int front(List L){
  if( L==NULL ){
    assert(L);
  } if(L->length==0){
    printf("Queue Error: calling getFront() on an empty Queue\n");
    exit(1);
  }
  return(L->front->data);
}
//pre:list must be defined and not empty
//returns back of list

int back(List L){
  if( L==NULL){
    assert(L);
  } if(L->length==0){
    printf("Queue Error: calling back() on an empty list\n");
    exit(1);
  } return (L->back->data);
}
//pre: Length>0
//returns cursor element
int get(List L){
  if(L==NULL){
    printf("Que");
    exit(1);
  } 
  if(L->length==0){
    printf("Que");
    exit(1);
  }
  if(L->cursorIndex==-1){
    printf("Que");
    exit(1);
  }
  return L->current->data;
}
//returns true if the List and L are the same type
int equals(List A, List B){
  if(A == NULL || B == NULL){
    printf("Error: Empty List\n");
    exit(1);
  }
  if(A->length != B->length) return 0;
  Node tmp1 = A->front;
  Node tmp2 = B->front;
  while(tmp1 != NULL && tmp2 != NULL){
    if(tmp1->data != tmp2->data) return 0;
    else{
      tmp1 = tmp1->next;
      tmp2 = tmp2->next;
    }
  }
  return 1;
}
// isEmpty()
// Returns true (1) if Q is empty, otherwise returns false (0)
int isEmpty(List L){
  if( L==NULL ){
    printf("Queue Error: calling isEmpty() on NULL Queue reference\n");
    exit(1);
  }
  assert(L);
  return(L->length==0);
}

// Manipulation procedures ----------------------------------------------------
void clear(List L){
  if(L==NULL)
  {
    fprintf(stderr, "error123\n");
    exit(1);
  }
  while(L->length > 0){ 
    deleteFront(L);
  }
}
//List must not be empty
//moves cursor to front
void moveFront(List L){
  if(L==NULL){
    fprintf(stderr, "Error: moveFront() called on empty List.");
    assert(L);
    exit(1);
  }
  if(L->length !=0){
    L->current = L->front;
    L->cursorIndex = 0;
  }
}
//List must not be empty
//moves element to the back
void moveBack(List L){
  if(L==NULL){
    fprintf(stderr, "Error: moveBack() called on empty List");
  }
  if(L->length != 0){
    L->current = L->back;
    L->cursorIndex = L->length - 1;
  }
}
//List must not be empty 
//moves cursor one element back
void movePrev(List L){
  assert(L);
  if(L->cursorIndex != -1){
    L->cursorIndex -=1;
    L->current = L->current->prev;
    assert(L);
  }
}
//List must not be empty
//moves cursor one element next
void moveNext(List L){
  if(L->cursorIndex == L->length-1){
    L->current = NULL;
    L->cursorIndex = -1;
  }
  if(L->cursorIndex != -1){
    L-> cursorIndex +=1;
    L->current = L->current->next;
  }
}
//List must be defined
//inserts node at beginning
void prepend(List L, int data){
  if(L==NULL){
    fprintf(stderr, "Error: prepend() called on null List");
    exit(1);
  }
  Node tmp = newNode(data);

  if(L->length ==0){
    L->back= L->front = tmp;
  }
  else{ 
    tmp->next = L->front;
    L->front->prev = tmp;
    L->front = tmp;
    if (L->current != NULL) L->cursorIndex+=1;
  }
  L->length +=1;
}
//List must be not mepty
//Inserts node at the end
void append(List L, int data){
  Node tmp = newNode(data);

  if(L==NULL){
    fprintf(stderr, "Error");
    exit(1);
  } if(L->length ==0){
    // assert(L);
    L->front = L->back = tmp;
  } else{
    tmp->prev = L->back;
    L->back->next = tmp;
    L->back = tmp;
    printf("%d", tmp->data);
  }
  L->length +=1;

}
//List must be defined
//Inserts node before cursors position
void insertBefore(List L, int data){
  if(L==NULL){
    assert(L);
  }
  if(L->length<=0){
    assert(L);
  }
  if(L->cursorIndex ==0){
    prepend(L, data);
  }else{
    Node tmp = newNode(data);
    assert(tmp);
    L->current->prev->next = tmp;
    tmp->prev = L->current->prev;
    L->current->prev = tmp;
    tmp->next = L->current;
    L->cursorIndex++;

    L->length++;
  }
}
//List must be defined
//Inserts element after cursor
void insertAfter(List L, int data){
  if(L==NULL){
    assert(L);
  }
  if(L->length<=0){
    assert(L);
  }
  if(L->current==NULL){
    assert(L);
  }
  if(L->current == L->back){
    append(L, data);
  }else{
    Node tmp = newNode(data);

    L->current->next->prev = tmp;
    tmp->next = L->current->next;
    tmp->prev = L->current;
    L->current->next = tmp;
    L->length++;
  }
}
//List must be defined and not empty
//deletes front element
void deleteFront(List L){
  if(L == NULL){
    fprintf(stderr, "Error, deleteFront() called on NULL list.\n");
    exit(1);
  }
  if(L->length<=0){
    fprintf(stderr, "Error, deleteFront() called on empty List\n");
    exit(1);
  }
  Node tmp = L->front;
  if(length(L)>1){
    if (L->current == L->front) {
      L->current = NULL;
      L->cursorIndex = -1;
    }
    L->front = L->front->next;
    L->front->prev = NULL;
    if(L->current!=NULL) L->cursorIndex--;
  }else{
    L->front = L->back = NULL;
    L->current = NULL;
    L->cursorIndex = -1;
  } 
  L->length--;
  freeNode(&tmp);
}
void deleteBack(List L){
  if(L==NULL){
    fprintf(stderr, "error, deleteBack() called on NULL list.\n");
    exit(1);
  }
  if(L->length<=0){
    fprintf(stderr, "Error, deleteBack() called on Empty List\n");
  }
  Node tmp = L->back;
  if(length(L)>1){
    if (L->current == L->back) {
      L->current = NULL;
      L->cursorIndex = -1;
    }
    L->back = L->back->prev;
    L->back->next = NULL;

  } else {
    L->front = L->back = NULL;
    L->current = NULL;
    L->cursorIndex = -1;
  }

  L->length--;
  freeNode(&tmp);
}
//List must be defined and not emepty
//deletes List
void delete(List L) {
  Node N = NULL;
  if(L == NULL) {
    fprintf(stderr, "List error: delete() called on null List reference\n");
    exit(1);
  }
  if(L->length <= 0) {
    fprintf(stderr, "List error: delete() called on empty List\n");
    exit(1);
  }
  if(L->current == NULL) {
    fprintf(stderr, "List error: delete() called on undefined cursor");
    exit(1);
  }
  if(L->current == L->back) {
    deleteBack(L);
    return;
  }
  else if(L->current == L->front) {
    deleteFront(L);
    return;
  }

  N = L->current;
  L->current = NULL;
  N->prev->next = N->next;
  N->next->prev = N->prev;

  L->length--;
  freeNode(&L->current);
}

// Other Functions -----------  -------------------------------------------------
// printList()
// Prints data elements in Q on a single line to stdout.
void printList(FILE* out, List L){
  if(L==NULL){
    fprintf(stderr, "Errer\n");
    exit(1);
  }

  for(Node N=L->front; N!=NULL; N=N->next) fprintf(out,"%d ", N->data);
  fprintf(out, "\n");
}
//Copies List
List copyList(List L){
  List N = newList();
  Node tmp = L->front;
  while(tmp != NULL){
    append(N, tmp->data);
    tmp = tmp->next;
  }
  return N;
}

