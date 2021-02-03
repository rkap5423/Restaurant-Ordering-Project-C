//
// Created by rkap on 3/22/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "proj4.h"

//function to add in-restaurant order to queue
void doAdd (struct Queue** q)
{
    /* get number of burgers ordered from input */
    int NumBurgers = getPosInt();
    if (NumBurgers < 0)
    {
        printf ("Error: Add command requires an integer value of at least 0\n");
        printf ("Add command is of form: a <# burgers> <# salads> <name>\n");
        printf ("  where:<# burgers> is the number of ordered burgers\n");
        printf ("        <# salads> is the number of ordered salads\n");
        printf ("        <name> is the name of the person putting the order\n");
        return;
    }

    /* get number of salads ordered from input */
    int NumSalads = getPosInt();
    if (NumSalads < 0)
    {
        printf ("Error: Add command requires an integer value of at least 0\n");
        printf ("Add command is of form: a <# burgers> <# salads> <name>\n");
        printf ("  where:<# burgers> is the number of ordered burgers\n");
        printf ("        <# salads> is the number of ordered salads\n");
        printf ("        <name> is the name of the person putting the order\n");
        return;
    }

    /* get group name from input */
    char *name = getName();
    if (NULL == name)
    {
        printf ("Error: Add command requires a name to be given\n");
        printf ("Add command is of form: a <# burgers> <# salads> <name>\n");
        printf ("  where:<# burgers> is the number of ordered burgers\n");
        printf ("        <# salads> is the number of ordered salads\n");
        printf ("        <name> is the name of the person putting the order\n");
        return;
    }

    if (doesNameExist(q,name)==TRUE){ //check if name already exists
        printf("Error, name already exists\n");
        return;
    }

    printf ("Adding In-restaurant order for \"%s\": %d burgers and %d salads\n", name,NumBurgers ,NumSalads);

    addToList(q,name,NumBurgers,NumSalads,TRUE);
}

//function to add a call ahead order to queue
void doCallAhead (struct Queue** q)
{
    /* get number of burgers ordered from input */
    int NumBurgers = getPosInt();
    if (NumBurgers < 0)
    {
        printf ("Error: Call-ahead command requires an integer value of at least 0\n");
        printf ("Call-ahead command is of form: c <# burgers> <# salads> <name>\n");
        printf ("  where:<# burgers> is the number of ordered burgers\n");
        printf ("        <# salads> is the number of ordered salads\n");
        printf ("        <name> is the name of the person putting the order\n");
        return;
    }

    /* get number of salads ordered from input */
    int NumSalads = getPosInt();
    if (NumSalads < 0)
    {
        printf ("Error: Call-ahead command requires an integer value of at least 0\n");
        printf ("Call-ahead command is of form: c <# burgers> <# salads> <name>\n");
        printf ("  where:<# burgers> is the number of ordered burgers\n");
        printf ("        <# salads> is the number of ordered salads\n");
        printf ("        <name> is the name of the person putting the order\n");
        return;
    }


    /* get group name from input */
    char *name = getName();
    if (NULL == name)
    {
        printf ("Error: Call-ahead command requires a name to be given\n");
        printf ("Call-ahead command is of form: c <# burgers> <# salads> <name>\n");
        printf ("  where:<# burgers> is the number of ordered burgers\n");
        printf ("        <# salads> is the number of ordered salads\n");
        printf ("        <name> is the name of the person putting the order\n");
        return;
    }
    if (doesNameExist(q,name)==TRUE){ //check if name already exists
        printf("Error, name already exists\n");
        return;
    }

    printf ("Adding Call-ahead order for \"%s\": %d burgers and %d salads\n", name,NumBurgers ,NumSalads);

    addToList(q,name,NumBurgers,NumSalads,FALSE);
}

//function to change call-ahead order to say it's now waiting in-restaurant
void doWaiting (struct Queue** q)
{
    /* get order name from input */
    char *name = getName();
    if (NULL == name)
    {
        printf ("Error: Waiting command requires a name to be given\n");
        printf ("Waiting command is of form: w <name>\n");
        printf ("  where: <name> is the name of the group that is now waiting\n");
        return;
    }

    if (doesNameExist(q,name)==FALSE){
        printf("Error, cannot update status\n");
        return;
    }


    boolean isHere; //make boolean to capture updateStatus() return
    isHere=updateStatus(q,name);
    if (isHere==FALSE)
        printf("Error, cannot update status\n");
    else
        printf ("Call-ahead order \"%s\" is now waiting in the restaurant\n", name);
}

//function to serve food and remove order from queue
void doRetrieve (struct Queue** q)
{
    /* get info of prepared food ready on the counter from input */
    int PreparedBurgers = getPosInt();
    if (PreparedBurgers < 0)
    {
        printf ("Error: Retrieve command requires an integer value of at least 0\n");
        printf ("Retrieve command is of form: r <# burgers> <# salads>\n");
        printf ("  where: <# burgers> is the number of burgers waiting on the counter for pick up\n");
        printf ("         <# saladss> is the number of salads waiting on the counter for pick up\n");
        return;
    }

    int PreparedSalads = getPosInt();
    if (PreparedSalads < 0)
    {
        printf ("Error: Retrieve command requires an integer value of at least 0\n");
        printf ("Retrieve command is of form: r <# burgers> <# salads>\n");
        printf ("  where: <# burgers> is the number of burgers waiting on the counter for pick up\n");
        printf ("         <# saladss> is the number of salads waiting on the counter for pick up\n");
        return;
    }

    clearToEoln();
    printf ("Retrieve (and remove) the first group that can pick up the order of %d burgers and %d salads\n", PreparedBurgers ,PreparedSalads);


    char* temp=retrieveAndRemove(q, PreparedBurgers,PreparedSalads);
    if (temp==NULL)
        printf("No order of the proper size is currently available\n");
    else{
        printf("Served %s\n",temp);
    }
}

//function to list all orders ahead of a given order
void doList(struct Queue** q)
{
    /* get order name from input */
    char *name = getName();
    if (NULL == name)
    {
        printf ("Error: List command requires a name to be given\n");
        printf ("List command is of form: l <name>\n");
        printf ("  where: <name> is the name of the order to inquire about\n");
        return;
    }
    if (doesNameExist(q,name)==FALSE){
        printf("Error, order doesn't exist");
        return;
    }
    printf("There are %d orders in front of %s's order\n",countOrdersAhead(q,name),name);
    printf ("Order for \"%s\" is behind the following orders\n", name);

    displayOrdersAhead(q,name);
}

//function to list all orders in queue
void doDisplay (struct Queue** q)
{
    clearToEoln();
    printf ("Display information about all orders\n");

    displayListInformation(q);
}

//function to display estimated waiting time for a given order
void doEstimateTime(struct Queue** q)
{
    /* get order name from input */

    char *name = getName();
    if (NULL == name)
    {
        printf ("Error: List command requires a name to be given\n");
        printf ("List command is of form: t <name>\n");
        printf ("  where: <name> is the name of the order to inquire about\n");
        return;
    }

    if (doesNameExist(q,name)==FALSE){
        printf("Error, order doesn't exist\n");
        return;
    }
    printf("The estimated waiting time is %d\n",displayWaitingTime(q,name));
}

