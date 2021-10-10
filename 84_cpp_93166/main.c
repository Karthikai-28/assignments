/* COP 3502C Assignment 3
This program is written by: Your Full Name */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "leak_detector_c.h"

#define string_MAX 51
#define MAX_Groups 10
#define MAX_NumOfSoldiers 10000

void debug(void)
{
    printf("Made it Here\n");
    fflush(stdout);
}

typedef struct soldier{
    int sequenceNumber;
    struct soldier* next;
    struct soldier* prev;
}soldier;

typedef struct queue{

    int groundNumber;
    int nodeCount;
    int k;
    int th;
    char queueName[string_MAX];
    struct soldier* soldierFront;
    struct soldier* soldierBack;

}queue;

//Function Definitions
void init(queue*);
void readGroups(FILE*, queue*);
void createReverseCircle(queue*);
void enqueueSoldier(queue*, int);
soldier* createSoldier(int);
void rearrangeCircle(soldier**);
void display_nonEmptyGroups(FILE*, queue*);
void display(FILE*, soldier*);
void Phase1(FILE*, queue*);
void Phase1_Killing(FILE*, queue*);
void Phase2(FILE*, queue*);
void dequeue(queue*);
void deleteSoldier(soldier*);
void sortList(soldier*);

int main(void)
{
    atexit(report_mem_leak);
    
    //Opening Files
    FILE *inFile, *outFile;
    inFile = fopen("in.txt", "r");
    outFile = fopen("out.txt", "w");

    struct queue *q = (struct queue*)malloc(MAX_Groups * sizeof(struct queue));
    init(q);

    //Program Functions
    readGroups(inFile, q);
    display_nonEmptyGroups(outFile, q);
    Phase1(outFile, q);
    Phase2(outFile, q);

    //Closing Files
    fclose(inFile);
    fclose(outFile);
    free(q);
    return 0;

}

void init(queue *q)
{
    //Initializing head and back to Null
    q->soldierBack = NULL;
    q->soldierFront = NULL;
}

//Reading each group in the file
void readGroups(FILE* inFile, queue *q)
{
    int nGroups;
    fscanf(inFile, "%d", &nGroups);
    
    //reading each group
    for(int i = 0; i < nGroups; i++)
    {
        int groundNumber;
        fscanf(inFile, "%d", &groundNumber);
        q[groundNumber].groundNumber = groundNumber;

        fscanf(inFile, "%s", q[groundNumber].queueName);
        fscanf(inFile, "%d", &q[groundNumber].nodeCount);

        //Creating double circular linked list for soldiers in group
        createReverseCircle(&q[groundNumber]);

        fscanf(inFile, "%d", &q[groundNumber].k);
        fscanf(inFile, "%d", &q[groundNumber].th);
    }
}

//Enqueue soldier with node count number of soldiers
void createReverseCircle(queue *q)
{
    for (int i = 0; i < q->nodeCount; i++)
    {
        //Goes to enqueue function
        enqueueSoldier(q, i + 1);
    }
}

void enqueueSoldier(queue *q, int val)
{
    soldier* new = createSoldier(val);

    //Check if the list is empty
    if (!q->soldierFront)
    {
        //Make New head of list
        q->soldierFront = new;
        //Maintain circular propery to point to itself
        q->soldierFront->next = q->soldierFront->prev = q->soldierFront;
        //Add node and end fucntion
        return;
    }

    //When it is not empty

    //Make the new node point to head since it is last node
    new->next = q->soldierFront;

    //Make the new node point to the last node
    new->prev = q->soldierFront->prev;

    //Old last node needs to point to the new node
    new->prev->next = new; 

    //we make the head point the new since it is last element 
    q->soldierFront->prev = new;
}

//It takes an integer, dynamically allocate a soldier structure and returns a soldier node
soldier* createSoldier(int sequence)
{
    soldier* ret= (soldier*)malloc(sizeof(soldier));
    ret->sequenceNumber= sequence;
    ret->next = ret->prev = NULL;
    return ret;
}

//Flip Values of double circular linked list
void rearrangeCircle(soldier **head)
{
    struct soldier *prev, *cur, *next, *last;

    // Head is going to be the last node after reversing list
    last = *head;

    prev  = *head;
    cur   = (*head)->next;
    *head = (*head)->next;

    // Iterate till reaching the initial node in circular list
    while (*head != last)
    {
        *head = (*head)->next;
        cur->next = prev;

        prev = cur;
        cur  = *head;
    }

    cur->next = prev;

    // Make last node as head
    *head = prev;
}

//printing values for nonEmpty groups
void display_nonEmptyGroups(FILE* outFile, queue *q)
{
    fprintf(outFile, "Initial nonempty lists status\n");

    for(int i = 0; i < MAX_Groups; i++)
    {
        if(q[i].nodeCount != 0)
        {
            fprintf(outFile, "%d %s ", i, q[i].queueName);
            rearrangeCircle(&q[i].soldierFront);
            display(outFile, q[i].soldierFront);
        }
    }
    fprintf(outFile, "\n");

    fprintf(outFile, "After ordering nonempty lists status\n");
    for(int i = 0; i < MAX_Groups; i++)
    {
        if(q[i].nodeCount != 0)
        {
            fprintf(outFile, "%d %s ", i, q[i].queueName);
            rearrangeCircle(&q[i].soldierFront);
            display(outFile, q[i].soldierFront);
        }
    }
    fprintf(outFile, "\n");
}

//display Values inside of the double circular linked list given head of soldier
void display(FILE* outFile, soldier *head)
{
    //check if the list is empty
    if(!head)
        return;

    //Store the head in a temp variable
    soldier* temp = head;

    //print the first value before moving to second value
    fprintf(outFile, "%d ", head->sequenceNumber);

    //move to the second value
    head = head->next;

    //loop while current node is not the first node
    while(temp != head)
    {
       fprintf(outFile, "%d ", head->sequenceNumber);
       head = head->next;
    }

    //Formating
    fprintf(outFile, "\n");
}

void Phase1(FILE* outFile, queue *q)
{
    fprintf(outFile, "Phase1 execution\n\n");
    //Phase 1
    for(int i = 0; i < MAX_Groups; i++)
    {
        if(q[i].nodeCount != 0)
        {
            fprintf(outFile, "Line# %d %s\n", i, q[i].queueName);
            Phase1_Killing(outFile, &q[i]);
            fprintf(outFile, "\n");
        }
    }
}

//Function for Phase 1 Killing process
void Phase1_Killing(FILE* outFile, queue *q)
{                                                 
    int soldierNumber;

    while (q->th < q->nodeCount)
    {   
        //iterating soldier k nummber of times
        for (int i=0; i < (q->k) ; i++)
        {
            q->soldierFront = q->soldierFront->next;
        }
        // Store the value that should be returned.
        soldierNumber = q->soldierFront->prev->sequenceNumber;

        // Delete the node
        deleteSoldier(q->soldierFront->prev);

        fprintf(outFile, "Soldier# %d executed\n", soldierNumber);
        (q->nodeCount)--;
    }
}

void Phase2(FILE* outFile, queue *q)
{
    //Phase 2
    fprintf(outFile, "Phase2 execution\n");

    bool finalSoldierFound = false;
    int surviverIndex;

    while(!finalSoldierFound)
    {
        //Reseting values after iterating all groups
        int emptyNodeCount =0;
        int index_of_highest = 0;
        int highest = 0;

        for(int i = 0; i < MAX_Groups; i++)
        {

            //Searching for the highest value of iteration
            if(q[i].nodeCount != 0)
            {   
                //Making sure list is sorted low to high
                sortList(q[i].soldierFront);

                //Assignning highest
                if(q[i].soldierFront->sequenceNumber  > highest)
                {
                    highest = q[i].soldierFront->sequenceNumber;
                    index_of_highest = i;
                }
            }
            else
                emptyNodeCount++;

            //If last Iteration do Killing Process
            if(i == MAX_Groups - 1)
            {   
                fprintf(outFile, "Executed Soldier %d from line %d\n",q[index_of_highest].soldierFront->sequenceNumber, q[index_of_highest].groundNumber);
                dequeue(&q[index_of_highest]);

                highest = 0;
            }

            //Checking for last soldier alive
            if( emptyNodeCount == (MAX_Groups - 1) && q[index_of_highest].nodeCount == 2)
            {
                surviverIndex = index_of_highest;
                fprintf(outFile, "Executed Soldier %d from line %d\n", q[index_of_highest].soldierFront->sequenceNumber, q[index_of_highest].groundNumber);
                dequeue(&q[index_of_highest]);

                //Break Statement
                finalSoldierFound = true;
            }   
        }
    }

    fprintf(outFile, "\nSoldier %d from line %d will survive", q[surviverIndex].soldierFront->sequenceNumber, q[surviverIndex].groundNumber);
    dequeue(&q[surviverIndex]);
}

//Delete given head of soldier list
void dequeue(queue *head)
{
    if(!head->soldierFront)
        return;

    struct queue *curr = head;
    struct soldier* prevNode = NULL;
    struct soldier* temp;

    temp = head->soldierFront;

    // Move prevNode to last node 
    prevNode = head->soldierFront->prev; 
  
    // Move start ahead 
    head->soldierFront = head->soldierFront->next; 

    // Adjust the pointers of prevNode and head node 
    prevNode->next = head->soldierFront; 
    head->soldierFront->prev = prevNode; 

    free(temp);
    (head->nodeCount)-- ;
}

// Function to delete a given node from the list 
void deleteSoldier(soldier *head) 
{ 
    // If list is empty return
    if (head == NULL) 
            return;

    // Declare two pointers and initialize them 
    struct soldier *current = head;
    struct soldier* temp = NULL; 

    // check if it is the front node 
    if (current == head) { 

        // Move temp to last node 
        temp = head->prev; 
  
        // Move start ahead 
        head = head->next; 

        // Adjust the pointers of temp and head node 
        temp->next = head; 
        head->prev = temp; 
        free(current); 
    } 
} 

//Making sure list is sorted
void sortList(soldier *head) 
{  
    //Current will point to head  
    struct soldier *current = head, *index = NULL;  
    int temp;  

    //If head is empty
    if(head == NULL) 
        return;  

    else
    {  
        do
        {  
        //Index will point to node next to current  
        index = current->next;  

            while(index != head) 
            {  
                //If current node is greater swap data  
                if(current->sequenceNumber > index->sequenceNumber) 
                {  
                    temp =current->sequenceNumber;  
                    current->sequenceNumber= index->sequenceNumber;  
                    index->sequenceNumber = temp;  
                }  
                index= index->next;  
            }  
            current =current->next;  
        }
        while(current->next != head);   
    }   
}  