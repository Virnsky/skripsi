#ifndef TREELIBRARY_H_INCLUDED
#define TREELIBRARY_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <malloc.h>

struct htree
{
    char symbol[6];
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
void create_tree(htlist_head* L,htree* Tr);
void printPathsRecur(struct htree* node, int path[], int pathLen);
void printArray(int ints[], int len);
void printPaths(struct htree* node);

#endif // TREELIBRARY_H_INCLUDED
