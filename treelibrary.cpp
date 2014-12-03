#include "treelibrary.h"

void add_tree_list(htlist_head* L,char symbol[6],int frek)
{

    htree_list* hlist=(htree_list*) malloc(sizeof(htree_list));
    htree*  t_branch=(htree*) malloc(sizeof(htree));

	strcpy(t_branch->symbol,symbol);
//	printf("add symbol %s\n",t_branch->symbol);
	t_branch->frekuensi=frek;
	t_branch->left=NULL;
	t_branch->right=NULL;
	hlist->branch=t_branch;
	hlist->next=NULL;

	if(L->first==NULL)
    {
        L->first=hlist;
    }else
    {
        htree_list* last_symbol=L->first;
        while(last_symbol->next!=NULL)
        {
            last_symbol=last_symbol->next;
        }
        last_symbol->next=hlist;
    }
    t_branch=NULL;
	hlist=NULL;
}

void add_tree_list(htlist_head* L,htree* t_tree)
{
    htree_list* hlist=(htree_list*) malloc(sizeof(htree_list));

	hlist->branch=t_tree;
	hlist->next=NULL;

	if(L->first==NULL)
    {
        L->first=hlist;
    }else
    {
        htree_list* last_symbol=L->first;
        while(last_symbol->next!=NULL)
        {
            last_symbol=last_symbol->next;
        }
        last_symbol->next=hlist;
    }

	hlist=NULL;
}

void sort_tree_list(htlist_head* L)
{
    int count_tree=0;

    if(L->first!=NULL)
    {
        htree_list* l1=L->first;
        htree_list* l2=NULL;
        while(l1->next!=NULL)
        {
            l2=l1->next;
            while(l2!=NULL)
            {
                if(l1->branch->frekuensi > l2->branch->frekuensi)
                {
                    htree* t_branch=l1->branch;
                    l1->branch=l2->branch;
                    l2->branch=t_branch;
                }
                l2=l2->next;
            }
            l1=l1->next;
        }

    }else
    {
        printf("list NULL\n");
    }
}

void del_htlist_front(htlist_head* L)
{
    if(L->first!=NULL)
    {
        htree_list* t_l=L->first;
        t_l->branch=NULL;
        L->first=L->first->next;
        t_l->next=NULL;
        free(t_l);
    }
}
void create_tree(struct htlist_head* L)
{
    if(L->first!=NULL)
    {
        while(L->first->next!=NULL)
        {
            sort_tree_list(L);
            htree* b=(htree*) malloc(sizeof(htree));
            b->left=L->first->branch;
            b->right=L->first->next->branch;
            b->frekuensi=b->left->frekuensi + b->right->frekuensi;
            add_tree_list(L,b);
            del_htlist_front(L);
            del_htlist_front(L);
            printf("branch created %d\n",b->frekuensi);
        }

    }else
    {
        printf("list NULL\n");
    }
}

void debug_list(struct htlist_head* L)
{
    if(L->first!=NULL)
    {
        htree_list* lt=L->first;
        int i=1;
        while(lt!=NULL)
        {
            printf("%d. symbol branch:%s\tfrek:%d\n",i,lt->branch->symbol,lt->branch->frekuensi);
            //~ if (lt->next !=NULL){
				//~ if (lt->next->next !=NULL){
					//~ printf("boooo!\n");
					//~ }
				//~ }

            lt=lt->next;
            i++;
        }
    }else
    {
        printf("list kosong\n");
    }
}

void printPathsRecur(htree* node, int path[], int pathLen)
{

    if (node==NULL)
        return;

  /* append this node to the path array */
    path[pathLen] = node->frekuensi;
    pathLen++;
//    printf("show path %d\n",node->frekuensi);
  /* it's a leaf, so print the path that led to here  */
    if (node->left==NULL && node->right==NULL)
    {
        printArray(path, pathLen);
        printf("%s\n",node->symbol);
    }
    else
    {
    /* otherwise try both subtrees */
//        printf("rekurse left\n");
        printPathsRecur(node->left, path, pathLen);
//        printf("rekurse right\n");
        printPathsRecur(node->right, path, pathLen);
    }
}

void printArray(int ints[], int len)
{
    int i;
    for (i=0; i<len; i++)
    {
        printf("%d ", ints[i]);
    }
//    printf("\n");
}

//debug with file
void printPathsRecur(htree* node, int path[], int pathLen, FILE* fp)
{

    if (node==NULL)
        return;

  /* append this node to the path array */
    path[pathLen] = node->frekuensi;
    pathLen++;
//    printf("show path %d\n",node->frekuensi);
  /* it's a leaf, so print the path that led to here  */
    if (node->left==NULL && node->right==NULL)
    {
        printArray(path, pathLen,fp);
        printf("%s\n",node->symbol);
        fwrite(node->symbol,sizeof(char),sizeof(node->symbol),fp);
        fprintf(fp,"\n");
    }
    else
    {
    /* otherwise try both subtrees */
//        printf("rekurse left\n");
        printPathsRecur(node->left, path, pathLen,fp);
//        printf("rekurse right\n");
        printPathsRecur(node->right, path, pathLen,fp);
    }
}

void printArray(int ints[], int len, FILE* fp)
{
    int i;
    for (i=0; i<len; i++)
    {
        printf("%d-", ints[i]);
        fprintf(fp,"%d ", ints[i]);
    }
}

void printPaths(htree* node, FILE* fp)
{
    int path[1000];
    printPathsRecur(node, path, 0, fp);
}
//end debug
void printPaths(htree* node)
{
    int path[1000];
    printPathsRecur(node, path, 0);
}

void huffTableCreate(htree* node, listHuff* hf)
{
    char path[500];
    huffTableRecurPath(node, hf,'L',path,0);
    huffTableRecurPath(node, hf,'R',path,0);
}
void huffTableRecurPath(htree* node, listHuff* hf, char dir, char path[], int pathLen)
{
    if (node==NULL)
        return;
    int i;
  /* append this node to the path array */
    path[pathLen]=dir;
    pathLen++;

//    printf("show path %d\n",node->frekuensi);
  /* it's a leaf, so print the path that led to here  */
    if (node->left==NULL && node->right==NULL)
    {
        huffTableAdd(hf,node->symbol,path,pathLen);
    }
    else
    {
    /* otherwise try both subtrees */

            huffTableRecurPath(node->left ,hf,'L',path,pathLen);
            huffTableRecurPath(node->right,hf,'R',path,pathLen);
    }
}
void huffTableAdd(listHuff* hf,char symbol[], char path[], int pathLen)
{
    int i;
    huffTable* hh=(huffTable*) malloc(sizeof(huffTable));
    hh->next=NULL;
    strcpy(hh->huff.symbol,symbol);

    for (i=0; i<pathLen; i++)
    {
        hh->huff.encode[i]=path[i];
    }

    if(hf->first==NULL)
    {
        hf->first=hh;
    }else
    {
        huffTable* last_symbol=hf->first;
        while(last_symbol->next!=NULL)
        {
            last_symbol=last_symbol->next;
        }
        last_symbol->next=hh;
    }
    hh=NULL;
}
void huffTablePrint(listHuff* hf)
{
    huffTable* a=hf->first;
    while(a!=NULL)
    {
        printf("%s %s\n",a->huff.encode,a->huff.symbol);
        a=a->next;
    }
}

///* Prototypes for funtions needed in printPaths() */
//void printPathsRecur(struct node* node, int path[], int pathLen);
//void printArray(int ints[], int len);
//
///*Given a binary tree, print out all of its root-to-leaf
// paths, one per line. Uses a recursive helper to do the work.*/
//void printPaths(struct node* node)
//{
//  int path[1000];
//  printPathsRecur(node, path, 0);
//}
//
///* Recursive helper function -- given a node, and an array containing
// the path from the root node up to but not including this node,
// print out all the root-leaf paths.*/
//void printPathsRecur(struct node* node, int path[], int pathLen)
//{
//  if (node==NULL)
//    return;
//
//  /* append this node to the path array */
//  path[pathLen] = node->data;
//  pathLen++;
//
//  /* it's a leaf, so print the path that led to here  */
//  if (node->left==NULL && node->right==NULL)
//  {
//    printArray(path, pathLen);
//  }
//  else
//  {
//    /* otherwise try both subtrees */
//    printPathsRecur(node->left, path, pathLen);
//    printPathsRecur(node->right, path, pathLen);
//  }
//}
//
//
///* UTILITY FUNCTIONS */
///* Utility that prints out an array on a line. */
//void printArray(int ints[], int len)
//{
//  int i;
//  for (i=0; i<len; i++)
//  {
//    printf("%d ", ints[i]);
//  }
//  printf("\n");
//}
//
///* utility that allocates a new node with the
//   given data and NULL left and right pointers. */
//struct node* newnode(int data)
//{
//  struct node* node = (struct node*)
//                       malloc(sizeof(struct node));
//  node->data = data;
//  node->left = NULL;
//  node->right = NULL;
//
//  return(node);
//}
//
///* Driver program to test above functions*/
//int main()
//{
//
//  /* Constructed binary tree is
//            10
//          /   \
//        8      2
//      /  \    /
//    3     5  2
//  */
//  struct node *root = newnode(10);
//  root->left        = newnode(8);
//  root->right       = newnode(2);
//  root->left->left  = newnode(3);
//  root->left->right = newnode(5);
//  root->right->left = newnode(2);
//
//  printPaths(root);
//
//  getchar();
//  return 0;
//}
