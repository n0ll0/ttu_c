#include "../include/ll_basecode.h"

#include "stdlib.h"
#include "string.h"

int IDCNT = 0;

struct node* CreateNode(char* name) {
  struct node* Node = malloc(sizeof(struct node));
  if (Node == NULL) {
    return NULL;
  }
  Node->id = IDCNT++;
  Node->name = strdup(name);
  if (!Node->name) {
    free(Node);
    return NULL;
  }
  Node->pNext = NULL;
  return Node;
}

void InsertNode(list** pHead, struct node* pNode) {
  if (!pNode) {
    return;
  }
  pNode->pNext = *pHead;
  (*pHead) = pNode;
}

void InsertNodeAplhabetically(list** pHead, struct node* pNode) {
  if (!pNode || !pHead) {
    return;
  }

  struct node** current = pHead;

  while (*current) {
    if (strcmp((*current)->name, pNode->name) >= 0) {
      current = &(*current)->pNext;
      break;
    }
  }

  pNode->pNext = *current;
  *current = pNode;
}

void Unload(list* pHead) {
  while (pHead) {
    struct node* next = pHead->pNext;
    if (pHead->name) {
      free(pHead->name);
    }
    free(pHead);
    pHead = next;
  }
}

struct node* FindNodeByName(list* pHead, char* name) {
  while (pHead) {
    list* next = pHead->pNext;
    if (strcmp(pHead->name, name) == 0)
      return pHead;
    pHead = next;
  }

  return NULL;
}

struct node* FindNodeByID(list* pHead, int id) {
  while (pHead) {
    list* next = pHead->pNext;
    if (pHead->id == id)
      return pHead;
    pHead = next;
  }
  return NULL;
}

/**
 * Functions to implement for the ADVANCED TASK 2
 */
void RemoveNodeByID(list** pHead, int id) {
  struct node* prevNode = NULL;
  struct node* currentNode = *pHead;

  while (currentNode) {
    if (currentNode->id == id) {
      if (prevNode) {
        prevNode->pNext = currentNode->pNext;
      } else {
        *pHead = currentNode->pNext;
      }
      free(currentNode->name);
      free(currentNode);
      return;
    }
    prevNode = currentNode;
    currentNode = currentNode->pNext;
  }
}

void RemoveNodeByName(list** pHead, char* name) {
  struct node* prevNode = NULL;
  struct node* currentNode = *pHead;

  while (currentNode) {
    if (strcmp(currentNode->name, name) == 0) {
      if (prevNode) {
        prevNode->pNext = currentNode->pNext;
      } else {
        *pHead = currentNode->pNext;
      }
      free(currentNode->name);
      free(currentNode);
      return;
    }
    prevNode = currentNode;
    currentNode = currentNode->pNext;
  }
}
