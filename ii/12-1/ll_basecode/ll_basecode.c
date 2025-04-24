/**
 * File:        ll_basecode.c
 * Author:      Risto Heinsar
 * Created:     12.04.2016
 * Modified:    13.06.2023
 *
 * Description: Linked list lab task basecode.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ll_basecode.h"

int main(void)
{
    list *pHead = NULL;


    /**************************************************************************
     *  TESTING STAGE 1: PrintNode is complete                                *
     **************************************************************************/
    
    //~ PrintNode(&(struct node){.id = 2, .name = "Maamees Jaanes", .pNext = NULL});
    //~ PrintNode(NULL);
    
    //~ return EXIT_SUCCESS;
    

    /**************************************************************************
     *  TESTING STAGE 2: PrintList is complete                                *
     **************************************************************************/
    //~ struct node c = {.id = 2, .name = "Maamees Jaanes", .pNext = NULL};
    //~ struct node b = {.id = 1, .name = "Linnud Tõnisted", .pNext = &c};
    //~ struct node a = {.id = 0, .name = "Kivipallur Jürto Nii-Dommzonn", .pNext = &b};

    //~ pHead = &a;
    
    //~ PrintList(pHead);
    
    //~ return EXIT_SUCCESS;
    
    
    /**************************************************************************
     *  TESTING STAGE 3: CreateNode() is complete                             *
     **************************************************************************/    
    //~ struct node *a = CreateNode("Kivipallur Jürto Nii-Dommzonn");
    //~ struct node *b = CreateNode("Linnud Tõnisted");
    //~ struct node *c = CreateNode("Maamees Jaanes");
    
    //~ b->pNext = c;
    //~ a->pNext = b;
    //~ pHead = a;
    
    //~ PrintList(pHead);
    
    //~ return EXIT_SUCCESS;
    
    
    /**************************************************************************
     *  TESTING STAGE 4: InsertNode() is complete                             *
     **************************************************************************/   
    //~ struct node *a = CreateNode("Kivipallur Jürto Nii-Dommzonn");
    //~ struct node *b = CreateNode("Linnud Tõnisted");
    //~ struct node *c = CreateNode("Maamees Jaanes");
    
    //~ InsertNode(&pHead, c);
    //~ InsertNode(&pHead, b);
    //~ InsertNode(&pHead, a);
    
    //~ PrintList(pHead);
    
    //~ return EXIT_SUCCESS;
    
    
    /**************************************************************************
     *  TESTING STAGE 5: Unload is completed                                  *
     **************************************************************************/   
    //~ struct node *a = CreateNode("Kivipallur Jürto Nii-Dommzonn");
    //~ struct node *b = CreateNode("Linnud Tõnisted");
    //~ struct node *c = CreateNode("Maamees Jaanes");
    
    //~ InsertNode(&pHead, c);
    //~ InsertNode(&pHead, b);
    //~ InsertNode(&pHead, a);
    
    //~ Unload(pHead);
    //~ return EXIT_SUCCESS;
    

    /**************************************************************************
     *  TESTING STAGE 6: Both Find() functions are complete                   *
     **************************************************************************/   
    //~ struct node *a = CreateNode("Kivipallur Jürto Nii-Dommzonn");
    //~ struct node *b = CreateNode("Linnud Tõnisted");
    //~ struct node *c = CreateNode("Maamees Jaanes");
    
    //~ InsertNode(&pHead, c);
    //~ InsertNode(&pHead, b);
    //~ InsertNode(&pHead, a);
    
    //~ PrintNode(FindNodeByName(pHead, "Linnud Tõnisted"));
    //~ PrintNode(FindNodeByName(pHead, "meow"));
    
    //~ PrintNode(FindNodeByID(pHead, 2));
    //~ PrintNode(FindNodeByID(pHead, 5));
    
    //~ Unload(pHead);
    //~ return EXIT_SUCCESS;
        
    
    while (1)
    {
        PrintMenu();
        
        switch (GetInputInRange(0, M_CNT - 1))
        {
            case M_EXIT:
                /* Destroy the list and exit the program */
                
                exit(EXIT_SUCCESS);
                break;
            case M_PRINT:
                /* Call PrintList() to print the list */ 
                
                break;
            case M_INSERT:
                /* Ask user for the name; use CreateNode() to allocate the node.
                 * Use InsertNode() to add it to the list.*/
                
                break;
            case M_FIND_ID:
                /* Allows the user to enter a node ID. 
                   Finds a node by the id value using FindNodeById().
                   Returned pointer is passed to PrintNode() to display it */
                
                break;
            case M_FIND_NAME:   
                /* Allows the user to enter a node name. 
                   Finds a node by the id value using FindNodeByName().
                   Returned pointer is passed to PrintNode() to display it */
                   
                break;
            case M_REM_ID:
                /* Allows the user to enter a node ID.
                   Find and removes the node by that ID (if it exists). */
                   
                break;
            case M_REM_NAME:
                /* Allows the user to enter a node name.
                   Find and removes the node by that name (if it exists). */
                   
                break;
            default:
                puts("Unrecognized input!");
                break;
        }
    }
    return EXIT_SUCCESS;
}


/**
 * Returns an input between min and max, inclusive
 */
int GetInputInRange(int min, int max)
{
    int input;

    while (1)
    {
        printf("> ");
        scanf("%d", &input);

        if (input <= max && input >= min)
            return input;
            
        fprintf(stderr, "Input out of bounds!\n");
    }
}


/**
 * Prints the available menu options
 */
void PrintMenu(void)
{
    puts("");
    puts("Select a task");
    
    printf("%d - Print list\n",           M_PRINT);
    printf("%d - Insert a node\n",        M_INSERT);
    printf("%d - Find a node by ID\n",    M_FIND_ID);
    printf("%d - Find a node by name\n",  M_FIND_NAME);
    printf("%d - Erase a node by ID\n",   M_REM_ID);
    printf("%d - Erase a node by name\n", M_REM_NAME);
    printf("%d - Exit\n",                 M_EXIT);
}


/**
 * Prints out the entire linked list
 */
void PrintList(list *pHead)
{
    if (pHead == NULL)
    {
        puts("List empty!");
        return;
    }
    
    for (list *pTemp = pHead; pTemp; pTemp = pTemp->pNext)
        PrintNode(pTemp);
}
