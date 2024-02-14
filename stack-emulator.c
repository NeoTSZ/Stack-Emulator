
// Earl James Williams Aliñgasa (NeoTSZ on GitHub)

/*============================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define COMMAND_SIZE 5

/*============================================================*/

typedef struct Stack 
{
    int value; 
    struct Stack *nextNodePtr; 
} Stack; 

/*============================================================*/

int showMenu();
int giveWidth(int number); 
int findLargestWidth(Stack **startPtr); 
void push(Stack **startPtr);
void showStack(Stack **startPtr, int nodeCount);
void pop(Stack **startPtr);

/*============================================================*/

int main()
{
    Stack **startPtr; 
    *startPtr = NULL; 
    int nodeCount = 0; 

    // Looping program 
    while (1) 
    {
        system("@cls||clear");
        printf("\n:: STACK EMULATOR ::\n");
        if (!nodeCount)
            printf("\n:: The stack is empty. ::\n");
        else 
            showStack(startPtr, nodeCount); 

        int choice = showMenu(); 
        switch (choice)
        {
        case 1: // Push
            nodeCount++; 
            push(startPtr);
            break; 
        case 2: // Pop
            if (nodeCount)
            {
                nodeCount--; 
                pop(startPtr); 
            }
            break;
        default: 
            printf("\n:: Exiting program. ::\n\n");
            return 0; 
        }
    }
    
    return 0;
}

/*============================================================*/

int showMenu()
{
    printf("\nChoose an option below to modify the stack.\n");
    printf("\n(1) Push a node onto the stack.");
    printf("\n(2) Pop a node from the stack.");
    printf("\n(Other) Exit program.\n\n%c ", 175);

    int choice; 
    scanf("%d", &choice);
    return choice; 
}

/*============================================================*/

int giveWidth(int number) 
{
    return 1 + (int) log10((double) number); 
}

/*============================================================*/

int findLargestWidth(Stack **startPtr)
{
    int width = 1; 
    Stack *currentPtr = *startPtr; 

    while (currentPtr != NULL)
    {
        int tempWidth = giveWidth(currentPtr -> value); 
        if (tempWidth > width)
            width = tempWidth; 
        
        currentPtr = currentPtr -> nextNodePtr; 
    }

    return width; 
}

/*============================================================*/

void push(Stack **startPtr)
{
    Stack *node = (Stack*) malloc(sizeof(Stack)); 

    if (*startPtr == NULL)
        *startPtr = node; 
    else 
    {
        // Traversing stack 
        Stack *currentPtr = *startPtr; 
        while (currentPtr != NULL)
        {
            if ((currentPtr -> nextNodePtr) == NULL)
            {
                currentPtr -> nextNodePtr = node;
                break; 
            } 
            else 
                currentPtr = currentPtr -> nextNodePtr; 
        }
    }
    node -> nextNodePtr = NULL; 

    // Getting and validating node value 
    printf("\nEnter a non-negative integer for the node value.\n%c ", 175);
    int tempValue; 
    scanf("%d", &tempValue);
    while (tempValue < 0)
    {
        printf("\nInvalid node value.\nPlease try again.\n%c ", 175);
        scanf("%d", &tempValue);
    }
    node -> value = tempValue; 
    printf("\n:: Node successfully added. ::\n");
}

/*============================================================*/

void showStack(Stack **startPtr, int nodeCount)
{
    int width = findLargestWidth(startPtr),
        *displayArray = (int*) malloc(nodeCount * sizeof(int)),
        arrayIndex = 0; 
    Stack *currentPtr = *startPtr; 

    // Printing top border 
    printf("\n\t\t%c", 201);
    for (int i = 0; i < (2 + width); i++)
        printf("%c", 205);
    printf("%c\n", 187);
    
    while (currentPtr != NULL)
    {   
        *(displayArray + arrayIndex++) = currentPtr -> value; 
        currentPtr = currentPtr -> nextNodePtr;
    }

    for (int i = (arrayIndex - 1); i >= 0; i--)
    {
        // Left border 
        printf("\t\t%c", 186);

        // Finding spaces 
        int tempWidth = giveWidth(*(displayArray + i)); 
        int leftSpaces = 1 + (int) ceil((double) (width - tempWidth) / 2); 
        int rightSpaces = 2 + width - tempWidth - leftSpaces; 

        // Printing node 
        for (int j = 0; j < leftSpaces; j++)
            printf("%c", 255);
        printf("%d", *(displayArray + i));
        for (int j = 0; j < rightSpaces; j++)
            printf("%c", 255);

        // Right border 
        printf("%c\n", 186);

        // Printing bottom border 
        printf("\t\t");
        if (!i)
        {
            printf("%c", 200);
            for (int j = 0; j < (2 + width); j++)
                printf("%c", 205);
            printf("%c\n", 188);
        }
        else 
        {
            printf("%c", 199);
            for (int j = 0; j < (2 + width); j++)
                printf("%c", 196);
            printf("%c\n", 182);
        }
    }

    free(displayArray); 
}

/*============================================================*/

void pop(Stack **startPtr)
{
    Stack *currentPtr = *startPtr;
    Stack *tempPtr; 

    if ((currentPtr -> nextNodePtr) == NULL)
    {
        free(currentPtr); 
        *startPtr = NULL; 
    }
    else 
    {
        // Traversing stack 
        while (currentPtr != NULL)
        {
            if ((currentPtr -> nextNodePtr) == NULL)
                break; 
            else 
            {
                tempPtr = currentPtr; 
                currentPtr = currentPtr -> nextNodePtr;
            } 
        }

        tempPtr -> nextNodePtr = NULL; 
        free(currentPtr); 
    }


    printf("\n:: Node successfully removed. ::\n");
}
