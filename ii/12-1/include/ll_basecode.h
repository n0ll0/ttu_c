/**
 * File:        ll_basecode.h
 * Author:      Risto Heinsar
 * Created:     12.04.2016
 * Modified:    13.06.2023
 *
 * Description: Header for the linked list lab task basecode
 */
#ifndef LINKED_LIST_LAB_TASK
#define LINKED_LIST_LAB_TASK

int IDCNT;

typedef struct node
{
    int id;
    char *name;
    struct node *pNext;
} list;

enum MenuOpt {M_EXIT, 
              M_PRINT,
              M_INSERT, 
              M_FIND_ID, 
              M_FIND_NAME, 
              M_REM_ID,
              M_REM_NAME,
              M_CNT};

/* These 3 functions have already been completed for you */
void PrintMenu(void);
int GetInputInRange(int min, int max);
void PrintList(list *pHead);

/**
 * Functions to implement for the BASE TASK!
 */
void PrintNode(list *pNode);
struct node *CreateNode(char *name);
void InsertNode(list **pHead, struct node *pNode);  
void Unload(list *pHead);
struct node *FindNodeByName(list *pHead, char *name);
struct node *FindNodeByID(list *pHead, int id);

/**
 * Functions to implement for the ADVANCED TASK 2
 */
void RemoveNodeByID(list **pHead, int id);
void RemoveNodeByName(list **pHead, char *name);

#endif
