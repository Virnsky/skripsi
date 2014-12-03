#ifndef TREELIBRARY_H_INCLUDED
#define TREELIBRARY_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <malloc.h>

struct htree
{
    char symbol[10];
    int frekuensi;
    struct htree* right;
    struct htree* left;
};

struct tree_root
{
    struct htree* root;
};

struct htree_list
{
	struct htree* branch;
	struct htree_list* next;
};

struct htlist_head
{
	struct htree_list* first;
};

void add_tree_list(htlist_head* L,char symbol[6],int frek);
void add_tree_list(htlist_head* L,htree* t_tree);
void sort_tree_list(htlist_head* L);
void del_htlist_front(htlist_head* L);
void create_tree(htlist_head* L);
void debug_list(struct htlist_head* L);
void printPathsRecur(htree* node, int path[], int pathLen);
void printArray(int ints[], int len);
void printPaths(htree* node);

//debug
void printPathsRecur(htree* node, int path[], int pathLen, FILE* fp);
void printArray(int ints[], int len, FILE* fp);
void printPaths(htree* node, FILE* fp);
//end debug

void huffTableCreate(htree* node);
void huffTableRecurPath(htree* node, char dir, char path[], int pathLen);
void huffTablePrint(char ints[], int len);

#endif // TREELIBRARY_H_INCLUDED
