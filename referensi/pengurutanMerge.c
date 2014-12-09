/* Pengurutan Merge */
#include <stdio.h>
#define MAKS 10
void merge(int list[],int list1[],int k,int m,int n)
{
    int i,j;
   i=k;
   j = m+1;
   while( i <= m && j <= n)
   {
      if(list[i] <= list[j])
      {
             list1[k] = list[i];
         i++;
         k++;
      }
      else
      {
            list1[k] = list[j];
         j++;
         k++;
      }
   }
   while(i <= m)
   {
         list1[k] = list[i];
      i++;
      k++;
   }
   while (i <= n )
   {
         list1[k] = list[j];
      j++;
      k++;
   }
}

void mpass( int list[],int list1[],int l,int n)
{
   int i;
   i = 0;
   while( i <= (n-2*l+1))
   {
      merge(list,list1,i,(i+l-1),(i+2*l-1));
      i = i + 2*l;
   }
   if((i+l-1) < n)
       merge(list,list1,i,(i+l-1),n);
   else
       while (i <= n )
       {
              list1[i] = list[i];
              i++;
       }
   }
   void msort(int list[], int n )
   {
      int l;
      int list1[MAKS];
      l =1;
      while (l <= n )
      {
         mpass(list,list1,l,n);
         l = l*2;
         mpass(list1,list,l,n);
         l = l*2;
      }
   }

   void bacaList(int list[],int n)
   {
      int i;
      printf("Masukkan elemen-elemen\n");
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
   msort(list,n-1);
   printf("List setelah pengurutan adalah:\n");
   tampilList(list,n);
}
