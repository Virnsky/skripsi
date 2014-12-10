/* Tumpukan dengan senarai berantai */
# include <stdio.h>
# include <stdlib.h>

struct simpul
{
   int data;
   struct simpul *link;
};

struct simpul *tempatkanPadaTumpukan(struct simpul *p, int nilai)
{
   struct simpul *temp;
   temp=(struct simpul *)malloc(sizeof(struct simpul));
       /* menciptakan simpul baru menggunakan
          nilai yang dilewatkan sebagai parameter */
   if(temp==NULL)
   {
      printf("Memori tidak tersedia\n");
      exit(0);
   }
   temp->data = nilai;
   temp->link = p;
   p = temp;
   return(p);
}

struct simpul *ambilDariTumpukan(struct simpul *p, int *nilai)
{
   struct simpul *temp;
   if(p==NULL)
   {
      printf(" Tumpukan kosong, tidak bisa diambil\n");
      exit(0);
   }
   *nilai = p->data;
   temp = p;
   p = p->link;
   free(temp);
   return(p);
}

void main()
{
   struct simpul *top = NULL;
   int n,nilai;
   do
   {
      do
      { 
         printf("Masukkan elemen yang akan ditempatkan pada tumpukan:\n");
         scanf("%d",&nilai);
         top = tempatkanPadaTumpukan(top,nilai);
         printf("Masukkan 1 untuk lanjut\n");
         scanf("%d",&n);
      } while(n == 1);

      printf("Masukkan 1 untuk mengambil elemen dari tumpukan\n");
      scanf("%d",&n);
      while( n == 1)
      {
         top = ambilDariTumpukan(top,&nilai);
         printf("Nilai yang diambil dari tumpukan adalah %d\n",nilai);
         printf("Masukkan 1 untuk mengambil elemen dari tumpukan\n");
         scanf("%d",&n);
      }
      printf("Masukkan 1 untuk lanjut\n");
      scanf("%d",&n);
   } while(n == 1);
}

