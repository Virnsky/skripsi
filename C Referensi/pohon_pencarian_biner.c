/* Pohon pencarian biner */
#include <stdio.h>
#include <stdlib.h>

struct tsimpul
{
   int data;
   struct tsimpul *L_anak, *R_anak;
};

struct tsimpul *sisip(struct tsimpul *p,int nilai)
{
   struct tsimpul *temp1,*temp2;
   if(p == NULL)
   {
      p = (struct tsimpul *) malloc(sizeof(struct tsimpul)); /* sisip simpul baru sebagai akar */
      if(p == NULL)
      {
         printf("Tidak bisa dialokasi\n");
         exit(0);
      }
      p->data = nilai;
      p->L_anak=p->R_anak=NULL;
   }
   else
   {
      temp1 = p;
      /* menjelajah pohon untuk mendapatkan pointer ke simpul yang memiliki anak yang simpulnya baru dibuat*/
      while(temp1 != NULL)
	  {
         temp2 = temp1;
         if( temp1 ->data > nilai)
          temp1 = temp1->L_anak;
         else
          temp1 = temp1->R_anak;
	  }
      if( temp2->data > nilai)
	  {
          temp2->L_anak = (struct tsimpul*)malloc(sizeof(struct tsimpul));/*sisip simpul yang baru dibuat menjadi anak kiri*/
          temp2 = temp2->L_anak;
          if(temp2 == NULL)
               {
          printf("Tidak dapat dialokasi\n");
          exit(0);
              }
          temp2->data = nilai;
          temp2->L_anak=temp2->R_anak = NULL;
	  }
      else
	  {
         temp2->R_anak = (struct tsimpul*)malloc(sizeof(struct tsimpul));/*sisip simpul yang baru dibuat menjadi anak kiri*/
         temp2 = temp2->R_anak;
         if(temp2 == NULL)
         {
            printf("Tidak dapat dialokasi\n");
            exit(0);
          }
          temp2->data = nilai;
          temp2->L_anak=temp2->R_anak = NULL;
	  }
   }
   return(p);
}

/* fungsi yang menciptakan pohon biner */
void inorder(struct tsimpul *p)
{
   if(p != NULL)
   {
      inorder(p->L_anak);
      printf("%d\t",p->data);
      inorder(p->R_anak);
    }
}

void main()
{
   struct tsimpul *akar = NULL;
   int n,x;
   printf("Masukkan jumlah simpul\n");
   scanf("%d",&n);
   while( n-- > 0)
     {
         printf("Masukkan nilai data\n");
         scanf("%d",&x);
         akar = sisip(akar,x);
    }
     inorder(akar);
 }
