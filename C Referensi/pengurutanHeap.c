/* Pengurutan Heap */
#include <stdio.h>
#define MAKS 10

void tukar(int *x,int *y)
{
   int temp;
   temp = *x;
   *x = *y;
   *y = temp;
}

void ubah( int list[],int i, int n)
{
   int j,k,flag;
   k = list[i];
   flag = 1;
   j = 2 * i;
   while(j <= n && flag)
   {
      if(j < n && list[j] < list[j+1])
      j++;
      if( k >= list[j])
               flag =0;
      else
      {
         list[j/2] = list[j];
         j = j *2;
      }
   }
   list [j/2] = k;
}

void bangun_heap_awal( int list[], int n)
{
   int i;
   for(i=(n/2);i>=0;i--)
       ubah(list,i,n-1);
}

void pengurutanHeap(int list[],int n)
{
   int i;
   bangun_heap_awal(list,n);
   for(i=(n-2); i>=0;i--)
   {
      tukar(&list[0],&list[i+1]);
      ubah(list,0,i);
   }
}

void bacaList(int list[],int n)
{
   int i;
   printf("Masukkan elemen-elemen:\n");
   for(i=0;i<n;i++)
       scanf("%d",&list[i]);
}

void tampilList(int list[],int n)
{
   int i;
   printf("Elemen-elemen adalah: \n");
   for(i=0;i<n;i++)
       printf("%d\t",list[i]);
}

void main()
{
   int list[MAKS], n;
   printf("Masukkan jumlah elemen di dalam list, maks = 10\n");
   scanf("%d",&n);
   bacaList(list,n);
   printf("List sebelum pengurutan adalah:\n");
   tampilList(list,n);
   pengurutanHeap(list,n);
   printf("List setelah pengurutan adalah:\n");
   tampilList(list,n);
}

