#include "../include/main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static int bst_node_count = 0;
static FILE* bst_outfile = NULL;

static BSTNode* CreateBSTNode(const char* name) {
  BSTNode* node = malloc(sizeof(BSTNode));
  if (!node)
    return NULL;
  strncpy(node->name, name, NAME_LEN - 1);
  node->name[NAME_LEN - 1] = '\0';
  node->count = 1;
  node->left = node->right = NULL;
  bst_node_count++;
  return node;
}

static BSTNode* InsertBST(BSTNode* root, const char* name) {
  if (!root)
    return CreateBSTNode(name);
  int cmp = strcmp(name, root->name);
  if (cmp == 0) {
    root->count++;
  } else if (cmp < 0) {
    root->left = InsertBST(root->left, name);
  } else {
    root->right = InsertBST(root->right, name);
  }
  return root;
}

static void PrintBST(BSTNode* root) {
  if (!root)
    return;
  PrintBST(root->left);
  fprintf(bst_outfile, "%s %d\n", root->name, root->count);
  PrintBST(root->right);
}

static void FreeBST(BSTNode* root) {
  if (!root)
    return;
  FreeBST(root->left);
  FreeBST(root->right);
  free(root);
}

void RunBSTSolution(const char* input_filename) {
  struct TimePoints tp;
  tp.start = clock();

  FILE* fin = fopen(input_filename, "r");
  if (!fin) {
    perror("Input file open failed");
    exit(1);
  }

  BSTNode* root = NULL;
  char eid[32], fname[32], lname[32], city[32];
  char combined[NAME_LEN];

  while (fscanf(fin, "%31s %31s %31s %31s", eid, fname, lname, city) == 4) {
    snprintf(combined, sizeof(combined), "%s %s", fname, lname);
    root = InsertBST(root, combined);
  }
  fclose(fin);
  tp.read = clock();

  bst_outfile = fopen("output_bst.txt", "w");
  if (!bst_outfile) {
    perror("Output file open failed");
    FreeBST(root);
    exit(1);
  }
  PrintBST(root);
  fclose(bst_outfile);
  tp.print = clock();

  FreeBST(root);
  tp.free = clock();

  printf("Found %d names\n\n", bst_node_count);
  PrintTime(tp);
}
