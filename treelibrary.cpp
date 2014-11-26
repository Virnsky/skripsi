#include "treelibrary.h"

void add_tree_list(htlist_head* L,char symbol[6],int frek)
{

    htree_list* hlist=(htree_list*) malloc(sizeof(htree_list));
    htree*  t_branch=(htree*) malloc(sizeof(htree));

	strcpy(t_branch->symbol,symbol);
	printf("add symbol %s\n",t_branch->symbol);
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
        L->first=L->first->next;
        t_l->next=NULL;
        free(t_l);
    }
}
void create_tree(struct htlist_head* L,struct htree* Tr)
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
        Tr=L->first->branch;
    }else
    {
        printf("list NULL\n");
    }
}

void printPathsRecur(struct htree* node, int path[], int pathLen)
{

    if (node==NULL)
        return;

  /* append this node to the path array */
    path[pathLen] = node->frekuensi;
    pathLen++;
    printf("show path %d\n",node->frekuensi);
  /* it's a leaf, so print the path that led to here  */
    if (node->left==NULL && node->right==NULL)
    {
        printArray(path, pathLen);
//        printf("%s\n",node->symbol);
    }
    else
    {
    /* otherwise try both subtrees */
        printf("rekurse left\n");
        printPathsRecur(node->left, path, pathLen);
        printf("rekurse right\n");
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

void printPaths(struct htree* node)
{
    int path[1000];
    printPathsRecur(node, path, 0);
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
