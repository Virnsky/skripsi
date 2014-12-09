/* Program untuk menyisipkan simpul setelah simpul tertentu */
# include <stdio.h>
# include <stdlib.h>
int panjang ( struct simpul * );

struct simpul
{
   int data;
   struct simpul *link;
};

/* fungsi untuk menyambung simpul baru ke senarai yang sudan ada */
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
      while (temp-> link != NULL)
         temp = temp-> link;
      temp-> link = (struct simpul *)malloc(sizeof(struct simpul));
      if(temp -> link == NULL)
	  {
        printf("Error\n");
        exit(0);
      }
      temp = temp-> link;
      temp-> data = n;
      temp-> link= NULL;
    }
    return (p);
 }
 
/* fungsi yang menyisipkan simpul yang baru diciptakan setelah simpul baru */
struct simpul * sisipBaru ( struct simpul *p, int simpul_no, int nilai )
{
   struct simpul *temp, * temp1;
   int i;
   if ( simpul_no <= 0 || simpul_no > panjang (p))
   {
      printf("Error! simpul yang dimaksud tidak ada\n");
      exit(0);
   }
   if ( simpul_no == 0)
   {
      temp = ( struct simpul * )malloc ( sizeof ( struct simpul ));
      if ( temp == NULL )
      {
         printf( " Tidak bisa dialokasi \n");
         exit (0);
      }
      temp -> data = nilai;
      temp -> link = p;
      p = temp ;
   }
   else
   {
      temp = p ;
      i = 1;
      while ( i < simpul_no )
      {
         i = i+1;
         temp = temp-> link ;
      }
      temp1 = ( struct simpul * )malloc ( sizeof(struct simpul));
      if ( temp == NULL )
      {
         printf ("Tidak bisa dialokasi \n");
         exit(0);
      }
      temp1 -> data = nilai ;
      temp1 -> link = temp -> link;
      temp -> link = temp1;
   }
   return (p);
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

/* fungsi untuk menghitung panjang senarai berantai */
int panjang ( struct simpul *p )
{
   int hitung = 0 ;
   while ( p != NULL )
   {
      hitung++;
      p = p->link;
   }
   return ( hitung ) ;
}
 
void main ()
{
   int n;
   int x;
   struct simpul *awal = NULL;
   printf("Masukkan jumlah simpul yang akan diciptakan \n");
   scanf("%d",&n);
   while ( n-- > 0 )
   {
      printf( "Masukkan nilai-nilai data yang akan ditempatkan pada simpul\n");
      scanf("%d",&x);
      awal = sisip ( awal, x );
   }
      printf(" List sebelum penghapusan adalah\n");
      tampilList ( awal );
      printf(" \n Masukkan nomor simpul untuk disisipkan\n");
      scanf ( " %d",&n);
      printf("Masukkan nilai simpul\n");
      scanf("%d",&x);
      awal = sisipBaru(awal,n,x);
      printf("Simpul setelah penyisipan adalah \n");
      tampilList(awal);
   }
