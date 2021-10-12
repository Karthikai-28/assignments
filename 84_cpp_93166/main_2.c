#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <math.h>
#include "leak_detector_c.h"

#define EMPTY -1


//soldier struct
typedef struct soldier
{
    int seqNumber;
    struct soldier *next;
    struct soldier *prev;
} soldier;



//queue struct 
typedef struct queue
{
    int gNumber;
    int soldierCount;
    int k;
    int th;
    char *queueName;
    soldier *front;
    soldier *back;
} queue;



//create soldier struct: taken and int, dynamically and allocate a soldier struct and return a soldier struct
soldier *createSoldier(int sequence)
{
    soldier *temp;
    temp = (soldier *)malloc(sizeof(soldier));
    temp->seqNumber = sequence;
    temp->next = NULL;
    temp->prev = NULL;
    return temp;
}


//create reverse circle: take reference of a queu and create a circular doubly linked list for that queue where the nodes have sequence numbers in reverse order. use create_soldier and enqueue() to add soldier to the queue
void createReverseCircle(queue *q)
{
  q->front = createSoldier(q->soldierCount);
  q->front->next = q->front;
  q->front->prev = q->front;
  q->back = q->front->prev;
  for(int i = q->soldierCount-1;i>0;i--)
  {
    enqueue(q,i);
  }
  q->back = q->front->prev;
}



//take reference of a queue and reverse the given circular double linked list where the first node of the linked list is pointed by the front of the queue
void rearrangeCircle(queue *q)
{
  if(q->front == NULL) return;
  soldier *curr, *temp;
  
  q->front = q->front->prev;
  curr = q->front;
  for(int i = 0; i < q->soldierCount; i++)
  {
    temp = curr->next;
    curr->next = curr->prev;
    curr->prev = temp;
    curr = curr->next;
  }
}



//display a given queue 
void display(queue q, FILE *ofp)
{
  soldier *temp = q.front;
  if(temp!=NULL)
  {
    printf("%d %s", q.gNumber, q.queueName);
    fprintf(ofp, "%d %s", q.gNumber, q.queueName);
    while (temp->next!=q.front)
    {
      printf(" %d",temp->seqNumber);
      fprintf(ofp, " %d", temp->seqNumber);
      temp = temp->next;
    }
    printf(" %d",temp->seqNumber);
    fprintf(ofp, " %d", temp->seqNumber);
  printf("\n");
  fprintf(ofp, "\n");
  }
}


//create phase1 function
//create phase2 function. need to use the dequeue function 
//create other auxiliary functions to simplify the code

/*
//linked list and queue below
struct node
{
  int data;
  struct node* next;
};
struct queue{
  struct node* front;
  struct node* back;
};
int empty(struct queue* qPtr){
  return qPtr->front == NULL;
}
int front(struct queue* qPtr){
  if(qPtr->front != NULL){
    return qPtr->front->data;
  }
  else{
    return EMPTY; 
  }
}
void displayQueue(struct queue* MyQueuePtr){
  struct node*t = MyQueuePtr->front;
  while(t){
    printf("%d ", t->data);
    t = t->next;
  }
}
int enqueue(struct queue* qPtr, int val){
  struct node* temp;
  temp = (struct node*)malloc(sizeof(struct node));
  if(temp != NULL){
    temp->data = val;
    temp->next = NULL;
    if(qPtr->back != NULL){
      qPtr->back->next = temp;
    }
    qPtr->back = temp;
    if(qPtr->front == NULL){
      qPtr->front = temp;
    }
    return 1;
  }
}
int dequeue(struct queue* qPtr){
  struct node* tmp;
  int retval;
  if(qPtr->front == NULL){
    return EMPTY;
  }
  retval = qPtr->front->data;
  tmp = qPtr->front;
  qPtr->front = qPtr->front->next;
  if(qPtr->front== NULL){
  qPtr->back = NULL;
  }
  free(tmp);
  return retval;
}
void init(struct queue* qPtr){
}
int main(void) {
  struct queue* MyQueuePtr = (struct queue*)malloc(sizeof(struct queue));
  init(MyQueuePtr);
  int choice;
  int data;
  while(1){
  
  printf("\n1.Insert elements to queue \n");
  printf("2.Delete elements from queue \n");
  printf("3.Display all elements of queue \n");
  printf("4.Quit \n");
  printf("Enter your choice");
  scanf("%d", &choice);
  switch(choice){
    case 1:
      printf("\nWhat data you want to put in the queue:");
      scanf("%d", &data);
      enqueue(MyQueuePtr, data);
      displayQueue(MyQueuePtr);
      break;
    case 2:
      data = dequeue(MyQueuePtr);
      if(data!=EMPTY){
       printf("\n%d deleted from queue\n", data);
       displayQueue(MyQueuePtr);
     }
     else{
       printf("Empty queue\n");
     }
      break;
    case 3:
      displayQueue(MyQueuePtr);
      break;
    case 4:
      exit(1);
  }
  }
}
*/


//condition before running (cbr) - qptr points to a valid struct queue 



// cbr.after,the struct that qPtr points to will be set up to represent a blank queue
void init(queue *qPtr)
{
    qPtr->front = NULL;
    qPtr->back = NULL;
}



// cbr. after, it returns true if the queue pointed to by pPtr is empty
int isEmpty(queue *qPtr)
{
    return qPtr->front == NULL;
}



// cbr. if the queue is pointed to a non-empty qPtr, then the front value is deleted and returned; else, -1 is printed to say the queue was already empty. deletes the first node in the queue too 
void dequeue(queue *q)
{
  if(q->soldierCount > 0)
  {
    soldier *temp = q->front;
    q->front = q->front->next;
    q->back->next = q->front;
    q->front->prev = temp->prev;
    q->soldierCount -= 1;
    if(q->soldierCount == 0)
    {
      q->front = NULL;
      q->back = NULL;
    }
    free(temp);
  }
}




// cbr. if the queue is pointed to a non-empty qPtr, then the front value is returned; else, -1 is returned to show that this queue is empty
int front(struct queue *qPtr)
{
    if (!isEmpty(qPtr))
        return qPtr->front->seqNumber;
    else
        return EMPTY;
}



// returns the number of soldiers of the first node in the queue
int peek(queue *q)
{
  return q->front->seqNumber;
}



// cbr2- qPtr points to a valid struct queue and val is the value to enqueue into the queue pointed to by qPtr


// cbr2. if the operation is successful, 1 will be returned, else, no change is made and 0 is returned
void enqueue(queue *qPtr, int val)
{
    soldier *newSoldier = createSoldier(val);
    soldier *temp = qPtr->back;
    temp->next = newSoldier;
    newSoldier->prev = temp;
    newSoldier->next = qPtr->front;
    qPtr->front->prev = newSoldier;
    qPtr->back = newSoldier;
}



//create a singular group
void createGroup(queue *q, int gNumber, FILE *inFile)
{
    char name[256];
    int soldierCount;
    int k, th;
    fscanf(inFile, "%s", name);
    q->queueName = malloc(sizeof(char) * (strlen(name)) + 1);
    strcpy(q->queueName, name);
    fscanf(inFile, "%d %d %d", &soldierCount, &k, &th);
    q->soldierCount = soldierCount;
    q->k = k;
    q->th = th;
    q->gNumber = gNumber;
    createReverseCircle(q);
}



//print out the group number, group, and soldiers, then reverse the soldier order
void print1(queue *MyQueuePtr, FILE *inFile, FILE *ofp)
{
    int groupCount;
    int gNumber;
    fscanf(inFile, "%d", &groupCount);
    for (int i = 0; i < groupCount; i++)
    {
        fscanf(inFile, "%d", &gNumber);
        createGroup(&MyQueuePtr[gNumber], gNumber, inFile);
    }
    printf("Initial nonempty lists status\n");
    fprintf(ofp, "Initial nonempty lists status\n");
    for (int i = 1; i <= 10; i++)
    {
        display(MyQueuePtr[i], ofp);
    }
    printf("\nAfter ordering nonempty lists status\n");
    fprintf(ofp, "\nAfter ordering nonempty lists status\n");
    for (int i = 1; i <= 10; i++)
    {
        rearrangeCircle(&MyQueuePtr[i]);
        display(MyQueuePtr[i], ofp);
    }
}



//go through the first phase for singular queue 
void phase1Execution(queue *q, FILE *ofp)
{
  soldier *temp, *curr;
  curr = q->front;
  
  int count = q->soldierCount;
  
  while(count > q->th)
  {
    for(int i = 0; i < q->k-1; i++)
    {
      curr = curr->next;
    }
    temp = curr;
    curr = curr->next;
    if(temp->seqNumber == q->front->seqNumber)
      q->front = q->front->next;
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    printf("Soldier# %d executed\n",temp->seqNumber);
    fprintf(ofp, "Soldier# %d executed\n", temp->seqNumber);
    count-=1;
    free(temp);
  }
  q->soldierCount = count;
}



//run through first execution for each queue element
void firstExecution(queue *q, FILE *ofp)
{ 
  for(int i=1; i<=10; i++){
    if(!isEmpty(&q[i])){
      printf("Line# %d %s\n", q[i].gNumber, q[i].queueName);
      fprintf(ofp, "Line# %d %s\n", q[i].gNumber, q[i].queueName);
      phase1Execution(&q[i], ofp);
      printf("\n");
      fprintf(ofp, "\n");
    }
  }
}



//run through phase 2 executions
void phase2Execution(queue *q, int length, FILE *ofp)
{
  int highest = 0;
  for(int i = 0; i < length; i++)
  {
    if(!isEmpty(&q[i]))
      if(highest < peek(&q[i]))
        highest = peek(&q[i]);
  }
  for(int i = 0; i < length; i++)
  {
    if (!isEmpty(&q[i]))
    {
      if (peek(&q[i]) == highest)
      {
        dequeue(&q[i]);
        printf("\nExecuted Soldier %d from line %d",highest,q[i].gNumber);
        fprintf(ofp, "\nExecuted Soldier %d from line %d", highest, q[i].gNumber);
        break;
      }
    }
  }
}



//get final soldiers for phase 2's execution
void secondExecution(queue *q, FILE *ofp)
{
  int totalSoldiers = 0;
  int numGroups = 0;
  for(int i = 0; i <= 10; i++)
  {
    if(!isEmpty(&q[i]))
    totalSoldiers += q[i].soldierCount;
    numGroups++;
  }
  //repeat phase 2 of execution until there is only 1 soldier
  while(totalSoldiers > 1)
  {
    phase2Execution(q, numGroups, ofp);
    totalSoldiers -= 1;
  }
}



//find the survivor
void findSurvivor(queue *q, FILE *ofp)
{
  int lastSoldier = 0;
  int lastGroup = 0;
  // save their value
  for(int i = 1; i <= 10; i++)
  {
    if(!isEmpty(&q[i]))
    {
      lastSoldier = peek(&q[i]);
      lastGroup = q[i].gNumber;
    }
  }
  //print out in output and file the survivor
  printf("\n\nSoldier %d from line %d will survive",lastSoldier,lastGroup);
  fprintf(ofp, "\n\nSoldier %d from line %d will survive\n", lastSoldier, lastGroup);
}



//release all allocated memory by dequeue and free()
void release_memory(queue *q)
{
  for (int i = 1; i <= 10; i++)
  {
    free(q[i].queueName);
    while (!isEmpty(&q[i]))
    {
      dequeue(&q[i]);
    }
  }
  free(q);
}



int main(void)
{
    atexit(report_mem_leak); //memory leak detector

    FILE *inFile, *outFile;
    inFile = fopen("in.txt", "r");
    outFile = fopen("out.txt", "w");

    soldier *root = NULL;

    queue *MyQueuePtr = (queue *)malloc(sizeof(queue) * 11);

    if (inFile != NULL)
    {
        //initialize the 10 queue's
        for (int i = 1; i <= 10; i++)
        {
            init(&MyQueuePtr[i]);
        }
        
        print1(MyQueuePtr, inFile, outFile);

        printf("\nPhase1 execution\n\n");
        fprintf(outFile, "\nPhase1 execution\n\n");

        firstExecution(MyQueuePtr, outFile);

        printf("Phase2 execution");
        fprintf(outFile, "Phase2 execution");

        secondExecution(MyQueuePtr, outFile);

        findSurvivor(MyQueuePtr, outFile);
    }
    else
    {
        printf("Please provide correct input file");
        fprintf(outFile,"Please provide correct input file");
        exit(-1);
    }

    release_memory(MyQueuePtr);
    fclose(inFile);
    return 0;
}