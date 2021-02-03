//
// Created by rkap on 3/22/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "proj4.h"

//function to create empty queue
struct Queue* createQueue()
{
    struct Queue* q = (struct Queue*) malloc(sizeof(struct Queue));
    q->front = q->back = NULL; //set front and back of queue to null
    return q;
}

//function to add an order to end of queue
void addToList(struct Queue** q, char* Name, int numBurgers, int numSalads, boolean Status)
{
    // Create a new Node
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->next = NULL;
    temp->name=Name;
    temp->burgers=numBurgers;
    temp->salads=numSalads;
    temp->status=Status;

    // If queue is empty, then new node is front and rear both
    if ((*q)->back == NULL) {
        (*q)->front = (*q)->back = temp;
        return;
    }

    // Add the new node at the end of queue and change rear
    (*q)->back->next = temp;
    (*q)->back = temp;
}

//function to serve an order and remove it from the queue, returns the name of the order served
char* retrieveAndRemove(struct Queue** q, int numBurgers, int numSalads)
{
    // If queue is empty, return NULL.
    if ((*q)->front == NULL)
        return NULL;

    Node* temp=(*q)->front; //start at front of queue
    Node* tempNext;

    if (temp->burgers<=numBurgers && temp->salads<=numSalads && temp->status==TRUE){ //case to handle if first order in queue needs to be served
        if (DebugMode==TRUE){
            if (temp->status==TRUE)
                printf("DEBUG: %s's order, %d burgers, %d salads, Waiting in restaurant\n",temp->name,temp->burgers,temp->salads);
            else
                printf("DEBUG: %s's order, %d burgers, %d salads, called ahead\n",temp->name,temp->burgers,temp->salads);
        }
        char *orderName = malloc(30); //temp name variable
        orderName = temp->name;
        (*q)->front=temp->next; //update front pointer
        return orderName;
    }
    else {
        //printf("else test");
        while (temp->next != NULL) { //loop through queue
            if (temp->next->burgers <= numBurgers && temp->next->salads <= numSalads && temp->next->status == TRUE)
                if (DebugMode==TRUE){
                    if (temp->next->status==TRUE)
                        printf("DEBUG: %s's order, %d burgers, %d salads, Waiting in restaurant\n",temp->next->name,temp->next->burgers,temp->next->salads);
                    else
                        printf("DEBUG: %s's order, %d burgers, %d salads, called ahead\n",temp->next->name,temp->next->burgers,temp->next->salads);
                }
                break;
            temp = temp->next;
        }
        if (temp->next==NULL) //no valid order found
            return NULL;
        tempNext = temp->next;
        char *orderName = malloc(30);
        if ((*q)->back == tempNext) { //case to handle if valid order is at end of queue
            orderName = tempNext->name;
            temp->next = NULL;
            (*q)->back = temp; //update back pointer
            free(tempNext);
            return orderName;
        }
        orderName = tempNext->name;
        temp->next = tempNext->next;
        free(tempNext);
        return orderName;
    }
}

//function to return boolean value checking if a name exists in queue or not
boolean doesNameExist(struct Queue** q, char *Name){
    boolean check=FALSE;
    Node* temp=(*q)->front; //start at front of queue
    while (temp!=NULL){ //loop through queue
        if (DebugMode==TRUE){
            if (temp->status==TRUE)
                printf("DEBUG: %s's order, %d burgers, %d salads, Waiting in restaurant\n",temp->name,temp->burgers,temp->salads);
            else
                printf("DEBUG: %s's order, %d burgers, %d salads, called ahead\n",temp->name,temp->burgers,temp->salads);
        }
        if (strcmp(temp->name,Name)==0){
            check=TRUE; //if name matches, return true
            return check;
        }
        temp=temp->next;
    }
    return check; //name not found, returns false
}

//function to update a call-ahead order to say its currently waiting in restaurant
boolean updateStatus(struct Queue** q, char *Name){
    Node* temp=(*q)->front; //start at front of queue
    while (temp!=NULL){ //loop through queue
        if (DebugMode==TRUE){
            if (temp->status==TRUE)
                printf("DEBUG: %s's order, %d burgers, %d salads, Waiting in restaurant\n",temp->name,temp->burgers,temp->salads);
            else
                printf("DEBUG: %s's order, %d burgers, %d salads, called ahead\n",temp->name,temp->burgers,temp->salads);
        }
        if (strcmp(temp->name,Name)==0){
            break; //name matches
        }
        temp=temp->next;
    }
    if (temp==NULL) //looped through entire queue, name not found
        return FALSE;
    if (temp->status==TRUE) //order is already waiting in restaurant
        return FALSE;
    else{
        temp->status=TRUE; //update status
        return TRUE;
    }
}

//function to see how many orders are ahead of a given order
int countOrdersAhead(struct Queue** q, char *Name){
    int counter=0;
    Node* temp=(*q)->front; //start at front of queue
    while (strcmp(temp->name,Name)!=0){//loop through queue, until name is found
        if (DebugMode==TRUE){
            if (temp->status==TRUE)
                printf("DEBUG: %s's order, %d burgers, %d salads, Waiting in restaurant\n",temp->name,temp->burgers,temp->salads);
            else
                printf("DEBUG: %s's order, %d burgers, %d salads, called ahead\n",temp->name,temp->burgers,temp->salads);
        }
        counter++; //count order
        temp=temp->next;
    }
    return counter;
}

//function to return estimated waiting time for a given order
int displayWaitingTime(struct Queue** q, char *Name){
    int waitTime=0;
    Node* temp=(*q)->front;//start at front of queue
    while (strcmp(temp->name,Name)!=0){//loop through queue, until name is found
        if (DebugMode==TRUE){
            if (temp->status==TRUE)
                printf("DEBUG: %s's order, %d burgers, %d salads, Waiting in restaurant\n",temp->name,temp->burgers,temp->salads);
            else
                printf("DEBUG: %s's order, %d burgers, %d salads, called ahead\n",temp->name,temp->burgers,temp->salads);
        }
        waitTime=waitTime+10*temp->burgers; //add burger wait time
        waitTime=waitTime+5*temp->salads;//add salad wait time
        temp=temp->next;
    }
    return waitTime;
}

//function to print out information of all orders ahead of a given order
void displayOrdersAhead(struct Queue** q, char *Name){
    Node* temp=(*q)->front;
    printf("These are the orders ahead of %s's order:\n",Name);
    while (strcmp(temp->name,Name)!=0){//loop through queue, until name is found
        if (DebugMode==TRUE){
            if (temp->status==TRUE)
                printf("DEBUG: %s's order, %d burgers, %d salads, Waiting in restaurant\n",temp->name,temp->burgers,temp->salads);
            else
                printf("DEBUG: %s's order, %d burgers, %d salads, called ahead\n",temp->name,temp->burgers,temp->salads);
        }
        if (temp->status==TRUE)
            printf("%s ordered %d burgers and %d salads, and they are currently in-restaurant.\n",temp->name,temp->burgers,temp->salads);
        else
            printf("%s ordered %d burgers and %d salads, and they have called ahead but are not in-restaurant yet.\n",temp->name,temp->burgers,temp->salads);
        temp=temp->next;
    }
}

//function to print out order information of all orders in queue
void displayListInformation(struct Queue** q){
    Node* temp=(*q)->front;
    int counter=0;
    printf("These are the orders in the queue:\n");
    while (temp!=NULL){//loop through entire queue
        if (DebugMode==TRUE){
            if (temp->status==TRUE)
                printf("DEBUG: %s's order, %d burgers, %d salads, Waiting in restaurant\n",temp->name,temp->burgers,temp->salads);
            else
                printf("DEBUG: %s's order, %d burgers, %d salads, called ahead\n",temp->name,temp->burgers,temp->salads);
        }
        counter++;
        if (temp->status==TRUE)
            printf("%s ordered %d burgers and %d salads, and they are currently in-restaurant.\n",temp->name,temp->burgers,temp->salads);
        else
            printf("%s ordered %d burgers and %d salads, and they have called ahead but are not in-restaurant yet.\n",temp->name,temp->burgers,temp->salads);
        temp=temp->next;
    }
    printf("The total number of orders is %d",counter);
}


