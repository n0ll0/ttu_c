#include "../include/main.h"
#include "../include/cmenu.h"

#include "../include/waitForUser.h"

#include "../include/menuoption/display_all.h"
#include "../include/menuoption/edit.h"
#include "../include/menuoption/search_phones.h"
/**
 * File:        ll_basecode.c
 * Author:      Risto Heinsar
 * Created:     12.04.2016
 * Modified:    13.06.2023
 *
 * Description: Linked list lab task basecode.
 */

#include "../include/ll_basecode.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  list* pHead = NULL;

  char* name;
  int id;

  while (1) {
    PrintMenu();

    switch (GetInputInRange(0, M_CNT - 1)) {
    case M_EXIT:
      /* Destroy the list and exit the program */
      Unload(pHead);
      exit(EXIT_SUCCESS);
      break;
    case M_PRINT:
      /* Call PrintList() to print the list */
      PrintList(pHead);
      break;
    case M_INSERT:
      /* Ask user for the name; use CreateNode() to allocate the node.
       * Use InsertNode() to add it to the list.*/
      printf("Enter node name: ");
      scanf("%ms", &name);
      InsertNode(&pHead, CreateNode(name));
      free(name);
      break;
    case M_FIND_ID:
      /* Allows the user to enter a node ID.
         Finds a node by the id value using FindNodeById().
         Returned pointer is passed to PrintNode() to display it */
      printf("Enter node ID: ");
      scanf("%d", &id);
      PrintNode(FindNodeByID(pHead, id));
      break;
    case M_FIND_NAME:
      /* Allows the user to enter a node name.
         Finds a node by the id value using FindNodeByName().
         Returned pointer is passed to PrintNode() to display it */
      printf("Enter node name: ");
      scanf("%ms", &name);
      PrintNode(FindNodeByName(pHead, name));
      free(name);
      break;
    case M_REM_ID:
      /* Allows the user to enter a node ID.
         Find and removes the node by that ID (if it exists). */
      printf("Enter node ID: ");
      scanf("%d", &id);
      RemoveNodeByID(&pHead, id);
      break;
    case M_REM_NAME:
      /* Allows the user to enter a node name.
         Find and removes the node by that name (if it exists). */
      printf("Enter node name: ");
      scanf("%ms", &name);
      RemoveNodeByName(&pHead, name);
      free(name);
      break;
    default:
      puts("Unrecognized input!\0");
      break;
    }
  }
  Unload(pHead);
  return EXIT_SUCCESS;
}

/**
 * Returns an input between min and max, inclusive
 */
int GetInputInRange(int min, int max) {
  int input;

  while (1) {
    printf("> \0");
    scanf("%d", &input);

    if (input <= max && input >= min)
      return input;

    fprintf(stderr, "Input out of bounds!\n\0");
  }
}

/**
 * Prints the available menu options
 */
void PrintMenu(void) {
  puts("\0");
  puts("Select a task\0");

  printf("%d - Print list\n\0", M_PRINT);
  printf("%d - Insert a node\n\0", M_INSERT);
  printf("%d - Find a node by ID\n\0", M_FIND_ID);
  printf("%d - Find a node by name\n\0", M_FIND_NAME);
  printf("%d - Erase a node by ID\n\0", M_REM_ID);
  printf("%d - Erase a node by name\n\0", M_REM_NAME);
  printf("%d - Exit\n\0", M_EXIT);
}

/**
 * Prints out the entire linked list
 */
void PrintList(list* pHead) {
  if (pHead == NULL) {
    puts("List empty!\0");
    return;
  }

  for (list* pTemp = pHead; pTemp; pTemp = pTemp->pNext)
    PrintNode(pTemp);
}

void PrintNode(list* pNode) {
  if (pNode) {
    printf("{\n\tid  \t-\t%d,\n\tname\t-\t%s\n\tnext\t-\t%p\n}\n\0", pNode->id,
           pNode->name, pNode->pNext);
  }
}

void test() {
  list* pHead = NULL;
  /**************************************************************************
   *  TESTING STAGE 1: PrintNode is complete                                *
   **************************************************************************/
  {
    PrintNode(
        &(struct node){.id = 2, .name = "Maamees Jaanes\0", .pNext = NULL});
    PrintNode(NULL);
    printf("TESTING STAGE 1 DONE\0");
  }
  //~ return EXIT_SUCCESS;

  /**************************************************************************
   *  TESTING STAGE 2: PrintList is complete                                *
   **************************************************************************/
  {
    struct node c = {.id = 2, .name = "Maamees Jaanes\0", .pNext = NULL};
    struct node b = {.id = 1, .name = "Linnud Tõnisted\0", .pNext = &c};
    struct node a = {
        .id = 0, .name = "Kivipallur Jürto Nii-Dommzonn\0", .pNext = &b};

    pHead = &a;

    PrintList(pHead);
    //~ return EXIT_SUCCESS;
    printf("TESTING STAGE 2 DONE\0");
  }

  /**************************************************************************
   *  TESTING STAGE 3: CreateNode() is complete                             *
   **************************************************************************/
  {
    struct node* a = CreateNode("Kivipallur Jürto Nii-Dommzonn\0");
    struct node* b = CreateNode("Linnud Tõnisted\0");
    struct node* c = CreateNode("Maamees Jaanes\0");

    b->pNext = c;
    a->pNext = b;
    pHead = a;

    PrintList(pHead);
    //~ return EXIT_SUCCESS;
    printf("TESTING STAGE 3 DONE\0");
  }

  /**************************************************************************
   *  TESTING STAGE 4: InsertNode() is complete                             *
   **************************************************************************/
  // {
  struct node* a1 = CreateNode("Kivipallur Jürto Nii-Dommzonn\0");
  struct node* b1 = CreateNode("Linnud Tõnisted\0");
  struct node* c1 = CreateNode("Maamees Jaanes\0");

  InsertNode(&pHead, c1);
  InsertNode(&pHead, b1);
  InsertNode(&pHead, a1);

  PrintList(pHead);
  printf("TESTING STAGE 4 DONE\0");
  // } //~ return EXIT_SUCCESS;

  /**************************************************************************
   *  TESTING STAGE 5: Unload is completed                                  *
   **************************************************************************/
  {
    IDCNT = 0;
    struct node* a = CreateNode("Kivipallur Jürto Nii-Dommzonn\0");
    struct node* b = CreateNode("Linnud Tõnisted\0");
    struct node* c = CreateNode("Maamees Jaanes\0");

    InsertNode(&pHead, c);
    InsertNode(&pHead, b);
    InsertNode(&pHead, a);

    PrintList(pHead);

    Unload(pHead);
    PrintList(pHead);
    //~ return EXIT_SUCCESS;
    printf("TESTING STAGE 5 DONE\0");
  }

  /**************************************************************************
   *  TESTING STAGE 6: Both Find() functions are complete                   *
   **************************************************************************/
  {
    struct node* a = CreateNode("Kivipallur Jürto Nii-Dommzonn\0");
    PrintNode(a);
    struct node* b = CreateNode("Linnud Tõnisted\0");
    PrintNode(b);
    struct node* c = CreateNode("Maamees Jaanes\0");
    PrintNode(c);

    InsertNode(&pHead, c);
    InsertNode(&pHead, b);
    InsertNode(&pHead, a);

    PrintList(pHead);

    printf("TESTING Linnud Tõnisted\0");
    PrintNode(FindNodeByName(pHead, "Linnud Tõnisted\0"));
    printf("TESTING meow\0");
    PrintNode(FindNodeByName(pHead, "meow\0"));

    PrintNode(FindNodeByID(pHead, 2));
    PrintNode(FindNodeByID(pHead, 5));

    Unload(pHead);
    //~ return EXIT_SUCCESS;
    printf("TESTING STAGE 6 DONE\0");
  }
}