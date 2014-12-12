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


struct huffData
{
	char symbol[10];
	bool encode[16];
	int len;
	int frek;
};

struct huffTable
{
	huffData huff;
	struct huffTable* next;
};

struct listHuff
{
	struct huffTable* first;
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

void huffTableCreate(htree* node, listHuff* hf);
void huffTableRecurPath(htree* node, listHuff* hf, bool dir, bool path[], int pathLen);
void huffTableAdd(listHuff* hf,char symbol[], bool path[], int pathLen);
void huffTablePrint(listHuff* hf);
void printEncodedFile(FILE* fhff,listHuff* hf);

void huffTreeCreateFromBit(htree* node,bool path[16],int pathlen,char sim[10]);


#endif // TREELIBRARY_H_INCLUDED
