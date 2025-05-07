#pragma once
#include <stdio.h>
#include <time.h>

#define NAME_LEN 64

typedef struct {
  char name[NAME_LEN];
  int count;
} NameEntry;

struct TimePoints {
  clock_t start;
  clock_t read;
  clock_t print;
  clock_t free;
};

void PrintTime(struct TimePoints t);
int GetNameIndex(NameEntry* arr, int size, const char* name);

typedef struct BSTNode {
  char name[NAME_LEN];
  int count;
  struct BSTNode *left, *right;
} BSTNode;

void RunBSTSolution(const char* input_filename);
void RunLinearSolution(const char* input_filename);

// Trie
#define ALPHA_LEN 29 // 26 letters + space + '-' + '\0'
typedef struct TrieNode {
  char ch;
  int count;
  struct TrieNode *chars[ALPHA_LEN];
} TrieNode;

void RunTrieSolution(const char* input_filename);
