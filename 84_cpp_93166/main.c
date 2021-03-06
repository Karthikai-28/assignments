/* COP 3502C Assignment 3
This program is written by: Your Full Name */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leak_detector_c.h"
#define G_MAX 10
#define MAX_LENTGH 50

//This singly linked list is used to sort the input
typedef struct node{
    int info;
    struct node* next;
    struct queue* queueInList;
}node;

//This is the circular doubly linked that will be used to fill each queue
typedef struct soldier{
    int data;
    struct soldier* next;
    struct soldier* prev;
}soldier;

//This is the queue definition. It contains variables for each ground info
typedef struct queue{
    int gNumber;
    int nodeCount;
    int originalNodeCount;
    int k;
    int th;
    char* name;
    soldier* head;
    soldier* tail;
}queue;

//This funtion returns 0 if the queue is empty
int empty(queue* qPtr);//this one is used in more than one phase
//This initiates the elements of the array of queues
void initQueue(queue* queuePtr);
//This sorts the input into a singly linked list
node* sortInsert(node* head, int nGrouds, char* groundName, int nSoldiers, int k, int th);
//this frees the singly linked list used in prePhase1
void freeList(node* head);
//These are the functions asked by the professor. They do what is specified in the instructions
soldier* createSoldier(int sequence);
void createReverseCircle(queue* q);
void rearrangeCircle(queue* q);
void display(queue q);//this one is used in more than one phase
void printQueue(queue q, FILE* output);//This does the same as display but prints the output in a txt file.
//Queue functions
void enqueue(queue* qPtr, int val);
//This moves the head n times positions so that dequeue can delete always the head (front)
void rotateQueue(queue* q, int k);
int dequeue(queue* q);//this one is used in more than one phase
//These divide phases of the program so that main function is readable
void prePhase1(FILE* input, FILE* output, int G, queue** queuePtr);
void phase1(queue** q, FILE* output);
void prePhase2(queue** q);
void phase2(queue** q, FILE* output, int G);
//This sorts the list inside the queue after phase 1
void sortNewLists(queue* q);
//This frees the array of queues after phase 2 is completed
void freeMemory(queue** q);
//Program starts here
int main(){
    
    atexit(report_mem_leak);
    FILE* input;
    FILE* output;

    input = fopen("in.txt", "rt");
    output = fopen("out.txt", "wt");
    
    //This notifies the user if files cannot be opened, created or found
    if (input == NULL) {
        printf("File could not be read\n");
        return 1;
    }
    if (output == NULL) {
        printf("File could not be written\n");
        return 1;
    }
    
    int G;
    fscanf(input,"%d", &G);//This scans the number of grounds of the input (1st number)
    
    //DMA array of queues. I know it could be static, but I like it complicated
    queue** queuePtr = (struct queue**) malloc(G_MAX * sizeof(queue*));
    for (int i = 0; i < G_MAX; i++) {
        queuePtr[i] = (struct queue*) malloc(sizeof(queue));
        initQueue(queuePtr[i]);
    }
    
    //Phases
    prePhase1(input, output, G, queuePtr);
    phase1(queuePtr, output);
    prePhase2(queuePtr);
    phase2(queuePtr, output, G);
    //Free memory
    freeMemory(queuePtr);
    //Close files
    fclose(input);
    fclose(output);
    return 0;
}
void initQueue(queue* queuePtr){
    queuePtr->head = NULL;
    queuePtr->tail = NULL;
}
node* sortInsert(node* head, int nGrouds, char* groundName, int nSoldiers, int k, int th){
//This sorts grounds from smaller to higher groun number. It also copies info from singly linked list to queue
    node* temp;
    node* t;
    temp = (node*) malloc(sizeof(node));
    temp->info = nGrouds;
    temp->next = NULL;
    temp->queueInList = (queue*) malloc(sizeof(queue));
    temp->queueInList->name = (char*) malloc(MAX_LENTGH * sizeof(char));
    temp->queueInList->name = strcpy(temp->queueInList->name, groundName);
    temp->queueInList->nodeCount = nSoldiers;
    temp->queueInList->originalNodeCount = nSoldiers;
    temp->queueInList->k = k;
    temp->queueInList->th = th;
    temp->queueInList->gNumber = temp->info;

    if (head == NULL || head->info >= nGrouds) {
        temp->next = head;
        head = temp;
    } else {
        t = head;
        while (t->next != NULL && t->next->info < nGrouds) {
            t = t->next;
        }
        temp->next = t->next;
        t->next = temp;
    }
    return head;
}
soldier* createSoldier(int sequence){
//This allocates a soldier node and returns it
    soldier* newSoldier = (soldier*) malloc(sizeof(soldier));
    if (newSoldier != NULL) {
        newSoldier->data = sequence;
        newSoldier->next = NULL;
        newSoldier->prev = NULL;
        return newSoldier;
    }
    return 0;
}
void enqueue(queue* qPtr, int val){
    
    struct soldier* temp = createSoldier(val);
    
    if (!qPtr->head) {//This makes the linked list circular since the start
        qPtr->head = temp;
        qPtr->head->next = qPtr->head;
        qPtr->head->prev = qPtr->head;
        qPtr->tail = qPtr->head->prev;
        return;
    }
    
    temp->next = qPtr->head;
    temp->prev = qPtr->head->prev; //here new soldier points to old last soldier
    temp->prev->next = temp;
    qPtr->head->prev = temp;
    qPtr->tail = temp;
}
void createReverseCircle(queue* q){
    //This creates the queues but inversed
    int counter = q->nodeCount;
    for (int j = 0; j < G_MAX; j++) {
        if (counter > 0) {
            enqueue(q, counter);
        }
        counter--;
    }
}
void rearrangeCircle(queue* q){
    //This function reverses the queues
    if (q->head == NULL) {
        printf("Lsit is empty\n");
        return;
    }
    soldier* current;
    soldier* t;
    current = q->head;
    do {
        soldier* temp;
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->next;
    } while (current != q->head);
    t = q->head;
    q->head = q->tail;
    q->tail = t;
}
int empty(queue* qPtr){
    return qPtr->nodeCount == 0;
}
void display(queue q){
    //I created this function with parameters listed in the instructions, so it only prints to the console
    if (q.head == NULL) {
        printf("Queue is empty\n");
        return;
    }
    
    soldier* t = q.head;
    printf("%d %s ", q.gNumber, q.name);
    printf("%d ", q.head->data);
    q.head = q.head->next;
    
    while (t != q.head) {
        printf("%d ", q.head->data);
        q.head = q.head->next;
    }
    printf("\n");
}
void printQueue(queue q, FILE* output){
    //This is the one that prints in the out.txt file
    if (q.head == NULL) {
        fprintf(output,"Queue is empty\n");
        return;
    }
    
    soldier* t = q.head;
    fprintf(output ,"%d %s ", q.gNumber, q.name);
    fprintf(output ,"%d ", q.head->data);
    q.head = q.head->next;
    
    while (t != q.head) {
        fprintf(output ,"%d ", q.head->data);
        q.head = q.head->next;
    }
    fprintf(output, "\n");
}

void fillQueueInfo(queue* q, node* head){
    //This is used so that I can free the singly linked list as soon as possible
    q->gNumber = head->queueInList->gNumber;
    q->name = head->queueInList->name;
    q->k = head->queueInList->k;
    q->th = head->queueInList->th;
    q->nodeCount = head->queueInList->nodeCount;
    q->originalNodeCount = head->queueInList->originalNodeCount;
}
void freeList(node* head){
    while (head != NULL) {
        free(head->queueInList->name);
        head = head->next;
    }
    free(head);
}
void prePhase1(FILE* input, FILE* output, int G, queue** queuePtr){
    
    node* head = NULL;
    int nGrouds, nSoldiers, k ,th;
    char groundName[MAX_LENTGH];
    //Sorting part
    for (int i = 0; i < G; i++) {
        fscanf(input, "%d %s %d %d %d", &nGrouds, groundName, &nSoldiers, &k, &th);
        head = sortInsert(head, nGrouds, groundName, nSoldiers, k, th);
    }
    //Enqueue part
    fprintf(output, "Initial nonempty lists status\n");
    printf("Initial nonempty lists status\n");
    for (int i = 0; i < G; i++) {
        fillQueueInfo(queuePtr[i], head);
        createReverseCircle(queuePtr[i]);
        display(*queuePtr[i]);
        printQueue(*queuePtr[i] , output);
        head = head->next;
    }
    //Reversing part
    fprintf(output, "\nAfter ordering nonempty lists status\n");
    printf("\nAfter ordering nonempty lists status\n");
    for (int i = 0; i < G; i++) {
        rearrangeCircle(queuePtr[i]);
        display(*queuePtr[i]);
        printQueue(*queuePtr[i] , output);
    }
    //Here I free the singly linked list, for it completed its purpose
    freeList(head);
}
int dequeue(queue* q){
    soldier* temp;
    int retval;
    
    if (q->head == NULL) {
        return -1;
    }
    retval = q->head->data;
    temp = q->head;
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    q->head = q->head->next;
    q->tail = q->head->prev;
    if (q->head == NULL) {
        q->tail = NULL;
    }

    free(temp);
    return retval;
}
void rotateQueue(queue* q, int k){
    if (k == 0) {
        return;
    }
    soldier* current = q->head;
    int count = 0;
    while (count < k - 1) {
        current = current->next;
        count++;
    }
    soldier* t = current;
    while (current->next != q->head) {
        current = current->next;
    }
    current->next = q->head;
    q->head = t->next;
    t->next = q->head;
}
void phase1(queue** q, FILE* output){
    
    fprintf(output, "\nPhase1 execution\n");
    printf("\nPhase1 execution\n");
    fprintf(output, "\n");
    printf("\n");
    for (int i = 0; i < G_MAX; i++) {
        if (empty(q[i])) {
            return;
        }
        int executed;
        //This is not part of the loop because the head is counted as skipped member in the sample output
        rotateQueue(q[i], q[i]->k - 1);
        executed = dequeue(q[i]);
        q[i]->nodeCount--;
        fprintf(output, "Line# %d %s\n", q[i]->gNumber, q[i]->name);
        printf("Line# %d %s\n", q[i]->gNumber, q[i]->name);
        fprintf(output, "Soldier# %d executed\n", executed);
        printf("Soldier# %d executed\n", executed);
        for (int j = q[i]->nodeCount; j > q[i]->th ; j--) {
            rotateQueue(q[i], q[i]->k - 1);
            executed = dequeue(q[i]);
            q[i]->nodeCount--;
            fprintf(output, "Soldier# %d executed\n", executed);
            printf("Soldier# %d executed\n", executed);
        }
        fprintf(output, "\n");
        printf("\n");
    }
}
void sortNewLists(queue* q){
    //This is used in prePhase2 to sort the remaining members of the queues
    while (q->head->data > q->head->next->data) {
        q->head = q->head->next;
        if (q->head->prev->data < q->head->data) {
            q->head = q->head->prev;
        }
    }
    q->tail = q->head->prev;
}
void prePhase2(queue** q){
    for (int i = 0; i < G_MAX; i++) {
        if (empty(q[i])) {
            return;
        }
        sortNewLists(q[i]);
    }
}
void phase2(queue** q, FILE* output, int G){
    //This function in complex
    fprintf(output, "Phase 2 execution\n");
    printf("Phase 2 execution\n");
    int count = 0;
    //This is the th counter. It will stop the executing process when there is only one soldier remaining
    for (int i = 0; i < G; i++) {
        count += q[i]->th;
    }
    //These two check if the queue are empty
    for (int i = 0; i < G; i++) {
        if (empty(q[i])){
            break;
        }
        int max = 0;
        for (int j = 0; j < G; j++) {
            if (empty(q[j])) {
                break;
            }
            //This first major if stament runs if 2 grounds have the same original nodecount
            if (q[j]->originalNodeCount == q[i]->originalNodeCount && i != j && q[j]->originalNodeCount != 0 && q[i]->originalNodeCount != 0) {//If two
                if (q[j]->gNumber < q[i]->gNumber) {
                    for (int k = 0; k < q[j]->nodeCount; k++) {
                        if (count == 1) {
                            int soldierChosen = dequeue(q[j]);
                            fprintf(output, "\nSoldier %d from line %d will survive\n", soldierChosen, q[j]->gNumber);
                            printf("\nSoldier %d from line %d will survive\n", soldierChosen, q[j]->gNumber);
                            break;
                        }
                        int soldierExecuted = dequeue(q[j]);
                        fprintf(output, "Executed soldier %d from line %d\n", soldierExecuted, q[j]->gNumber);
                        printf("Executed soldier %d from line %d\n", soldierExecuted, q[j]->gNumber);
                        count--;
                        q[j]->originalNodeCount = 0;
                    }
                    for (int k = 0; k < q[i]->nodeCount; k++) {
                        if (count == 1) {
                            int soldierChosen = dequeue(q[i]);
                            fprintf(output, "\nSoldier %d from line %d will survive\n", soldierChosen, q[i]->gNumber);
                            printf("\nSoldier %d from line %d will survive\n", soldierChosen, q[i]->gNumber);
                            break;
                        }
                        int soldierExecuted = dequeue(q[i]);
                        fprintf(output, "Executed soldier %d from line %d\n", soldierExecuted, q[i]->gNumber);
                        printf("Executed soldier %d from line %d\n", soldierExecuted, q[i]->gNumber);
                        count--;
                        q[i]->originalNodeCount = 0;
                    }
                } else {
                    for (int k = 0; k < q[i]->nodeCount; k++) {
                        if (count == 1) {
                            int soldierChosen = dequeue(q[i]);
                            fprintf(output, "\nSoldier %d from line %d will survive\n", soldierChosen, q[i]->gNumber);
                            printf("\nSoldier %d from line %d will survive\n", soldierChosen, q[i]->gNumber);
                            break;
                        }
                        int soldierExecuted = dequeue(q[i]);
                        fprintf(output, "Executed soldier %d from line %d", soldierExecuted, q[i]->gNumber);
                        printf("Executed soldier %d from line %d", soldierExecuted, q[i]->gNumber);
                        count--;
                        q[i]->originalNodeCount = 0;
                    }
                    for (int k = 0; k < q[j]->nodeCount; k++) {
                        if (count == 1) {
                            int soldierChosen = dequeue(q[j]);
                            fprintf(output, "\nSoldier %d from line %d will survive\n", soldierChosen, q[j]->gNumber);
                            printf("\nSoldier %d from line %d will survive\n", soldierChosen, q[j]->gNumber);
                            break;
                        }
                        int soldierExecuted = dequeue(q[j]);
                        fprintf(output, "Executed soldier %d from line %d\n", soldierExecuted, q[j]->gNumber);
                        printf("Executed soldier %d from line %d\n", soldierExecuted, q[j]->gNumber);
                        count--;
                        q[j]->originalNodeCount = 0;
                    }
                }
            } else if (q[i]->originalNodeCount > q[j]->originalNodeCount){
                if (q[i]->originalNodeCount > q[max]->originalNodeCount) {
                    max = i;
                }
            } else
                if (q[j]->originalNodeCount > q[max]->originalNodeCount) {
                    max = j;
                }
        }
        for (int k = 0; k < q[max]->nodeCount; k++) {
            if (count == 1) {
                int soldierChosen = dequeue(q[max]);
                fprintf(output, "\nSoldier %d from line %d will survive\n", soldierChosen, q[max]->gNumber);
                printf("\nSoldier %d from line %d will survive\n", soldierChosen, q[max]->gNumber);
                break;
            }
            int soldierExecuted = dequeue(q[max]);
            fprintf(output, "Executed soldier %d from line %d\n", soldierExecuted, q[max]->gNumber);
            printf("Executed soldier %d from line %d\n", soldierExecuted, q[max]->gNumber);
            count--;
            q[max]->originalNodeCount = 0;
        }
    }
}
void freeMemory(queue** q){
    //This executes after all the output is printed
    for (int i = 0; i < G_MAX; i++) {
        free(q[i]);
    }
    free(q);
}
