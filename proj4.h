//
// Created by rkap on 3/24/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {FALSE = 0, TRUE, NO = 0, YES} boolean; //boolean variable enumeration
boolean DebugMode; //boolean variable to check for debugmode

// A linked list node
typedef struct Node //node structure
{
    boolean status; //boolean for if order is in restaurant or not
    int burgers; //number of burgers ordered
    int salads;//number of salads ordered
    struct Node *next;//next order in queue
    char *name;//name of order
} Node;

struct Queue { //queue structure
    //nodes to keep track of front and back of queue
    struct Node *front;
    struct Node *back;
};

int getNextNWSChar();
int getPosInt();
char *getName();
void clearToEoln();
void printCommands();


void doAdd(struct Queue** q);
void doCallAhead(struct Queue** q);
void doWaiting(struct Queue** q);
void doRetrieve(struct Queue** q);
void doList(struct Queue** q);
void doDisplay(struct Queue** q);
void doEstimateTime(struct Queue** q);

struct Queue* createQueue();
void addToList(struct Queue** q, char* Name, int numBurgers, int numSalads, boolean Status);
char* retrieveAndRemove(struct Queue** q,int numBurgers, int numSalads);
boolean doesNameExist(struct Queue** q, char *Name);
boolean updateStatus(struct Queue** q, char *Name);
int countOrdersAhead(struct Queue** q, char *Name);
int displayWaitingTime(struct Queue** q, char *Name);
void displayOrdersAhead(struct Queue** q, char *Name);
void displayListInformation(struct Queue** q);