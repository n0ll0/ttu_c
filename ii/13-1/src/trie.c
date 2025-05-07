#include "../include/main.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>

static int trie_node_count = 0;
static FILE *trie_outfile = NULL;

// Map character to index: a-z -> 0-25, ' ' -> 26, '-' -> 27, '\0' -> 28
static int char_to_index(char c) {
    if (c >= 'a' && c <= 'z') return c - 'a';
    if (c >= 'A' && c <= 'Z') return c - 'A';
    if (c == ' ') return 26;
    if (c == '-') return 27;
    if (c == '\0') return 28;
    return -1;
}

static TrieNode* CreateTrieNode(char ch) {
    TrieNode *node = malloc(sizeof(TrieNode));
    if (!node) return NULL;
    node->ch = ch;
    node->count = 0;
    for (int i = 0; i < ALPHA_LEN; ++i)
        node->chars[i] = NULL;
    return node;
}

static void InsertTrie(TrieNode *root, const char *name) {
    TrieNode *cur = root;
    for (const char *p = name; ; ++p) {
        int idx = char_to_index(*p);
        if (idx < 0) continue; // skip invalid chars
        if (!cur->chars[idx]) {
            cur->chars[idx] = CreateTrieNode(*p);
            if (*p == '\0') trie_node_count++;
        }
        cur = cur->chars[idx];
        if (*p == '\0') {
            cur->count++;
            break;
        }
    }
}

// Helper to print names recursively
static void PrintTrieRec(TrieNode *node, char *buffer, int depth) {
    if (!node) return;
    if (node->ch == '\0' && node->count > 0) {
        buffer[depth] = '\0';
        fprintf(trie_outfile, "%s %d\n", buffer, node->count);
    }
    for (int i = 0; i < ALPHA_LEN; ++i) {
        if (node->chars[i]) {
            if (node->chars[i]->ch != '\0')
                buffer[depth] = node->chars[i]->ch;
            PrintTrieRec(node->chars[i], buffer, node->chars[i]->ch == '\0' ? depth : depth + 1);
        }
    }
}

static void FreeTrie(TrieNode *node) {
    if (!node) return;
    for (int i = 0; i < ALPHA_LEN; ++i)
        if (node->chars[i]) FreeTrie(node->chars[i]);
    free(node);
}

void RunTrieSolution(const char* input_filename) {
    struct TimePoints tp;
    tp.start = clock();

    FILE *fin = fopen(input_filename, "r");
    if (!fin) {
        perror("Input file open failed");
        exit(1);
    }

    TrieNode *root = CreateTrieNode('\0');
    char eid[32], fname[32], lname[32], city[32];
    char combined[NAME_LEN];

    while (fscanf(fin, "%31s %31s %31s %31s", eid, fname, lname, city) == 4) {
        snprintf(combined, sizeof(combined), "%s %s", fname, lname);
        InsertTrie(root, combined);
    }
    fclose(fin);
    tp.read = clock();

    trie_outfile = fopen("output_trie.txt", "w");
    if (!trie_outfile) {
        perror("Output file open failed");
        FreeTrie(root);
        exit(1);
    }
    char buffer[NAME_LEN];
    PrintTrieRec(root, buffer, 0);
    fclose(trie_outfile);
    tp.print = clock();

    FreeTrie(root);
    tp.free = clock();

    printf("Found %d names\n\n", trie_node_count);
    PrintTime(tp);
}
