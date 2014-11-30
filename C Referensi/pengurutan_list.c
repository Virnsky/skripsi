/* Program mengurutkan list */
#include <stdio.h>
#include <stdlib.h>
struct simpul
{
   int data;
   struct simpul *link;
};
struct simpul *sisip(struct simpul *p, int n)
{
   struct simpul *temp;
   if(p==NULL)
   {
      p=(struct simpul *)malloc(sizeof(struct simpul));
      if(p==NULL)
      {
            printf("Error\n");
         exit(0);
      }
      p-> data = n;
      p-> link = NULL;
   }
   else
   {
      temp = p;
      while (temp-> link!= NULL)
      temp = temp-> link;
      temp-> link = (struct simpul *)malloc(sizeof(struct simpul));
      if(temp -> link == NULL)
      {
         printf("Error\n");
         exit(0);
      }
       temp = temp-> link;
       temp-> data = n;
       temp-> link = NULL;
   }
   return(p);
}

void tampilList ( struct simpul *p )
{
   printf("Nilai-nilai data di dalam list adalah\n");
   while (p!= NULL)
   {
      printf("%d\t",p-> data);
      p = p-> link;
   }
}

/* fungsi untuk membalikkan */
struct simpul *terbalik(struct simpul *p)
{
   struct simpul *prev, *curr;
   prev = NULL;
   curr = p;
   while (curr != NULL)
   {
      p = p-> link;
      curr-> link = prev;
      prev = curr;
      curr = p;
   }
   return(prev);
}
/* fungsi untuk mengurutkan list */
struct simpul *urutList(struct simpul *p)
{
   struct simpul *temp1,*temp2,*min,*prev,*q;
   q = NULL;
   while(p != NULL)
   {
      prev = NULL;
      min = temp1 = p;
      temp2 = p -> link;
      while ( temp2 != NULL )
      {
         if (min -> data > temp2 -> data)
         {
            min = temp2;
            prev = temp1;
         }
         temp1 = temp2;
         temp2 = temp2-> link;
      }
      if(prev == NULL)
         p = min -> link;
      else
         prev -> link = min -> link;
      min -> link = NULL;
      if( q == NULL)
         q = min; /* memindahkan simpul dengan nilai data terendah di 
                     dalam list yang ditunjuk oleh p ke list
                     yang ditunjuk oleh q sebagai simpul pertama */
      else
      {
         temp1 = q;
         /* menjelajah list yang ditunjuk oleh q untuk 
            mendapatkan pointer ke simpul terakhir */
         while( temp1 -> link != NULL)
            temp1 = temp1 -> link;
         /* memindahkan simpul dengan nilai data terendah
            di dalam list yang ditunjuk oleh p ke list yang
            ditunjuk oleh q di akhir list yang ditunjuk q */
         temp1 -> link = min; 
      }
   }
   return (q);
}

void main()
{
   int n;
   int x;
   struct simpul *awal = NULL ;
   printf("Masukkan simpul yang akan diciptakan \n");
   scanf("%d",&n);
   while ( n-- > 0 )
   {
      printf( "Masukkan nilai data yang akan ditempatkan ke suatu simpul\n");
      scanf("%d",&x);
      awal = sisip ( awal,x);
   }
   printf("List yang diciptakan adalah\n");
   tampilList ( awal );
   awal = urutList(awal);
   printf("List yang terurut adalah\n");
   tampilList ( awal );
   awal = terbalik(awal);
   printf("List yang terbalik adalah\n");
   tampilList ( awal );
}
