/* Pengurutan Quick */
#include <stdio.h>
#define MAKS 10
void tukar(int *x,int *y)
{
   int temp;
   temp = *x;
   *x = *y;
   *y = temp;
}
int posisiKunci(int i,int j )
{
   return((i+j) /2);
}
void pengurutanQuick(int daftar[],int m,int n)
{
   int kunci,i,j,k;
   if( m < n)
   {
      k = posisiKunci(m,n);
      tukar(&daftar[m],&daftar[k]);
      kunci = daftar[m];
      i = m+1;
      j = n;
      while(i <= j)
      {
         while((i <= n) && (daftar[i] <= kunci))
                i++;
         while((j >= m) && (daftar[j] > kunci))
                j--;
         if( i < j)
                tukar(&daftar[i],&daftar[j]);
      }
      tukar(&daftar[m],&daftar[j]);
      pengurutanQuick(daftar,m,j-1);
      pengurutanQuick(daftar,j+1,n);
   }
}
void bacadaftar(int daftar[],int n)
{
   int i;
   printf("Masukkan elemen-elemen\n");
   for(i=0;i<n;i++)
       scanf("%d",&daftar[i]);
}
void tampilDaftar(int daftar[],int n)
{
   int i;
   printf("Elemen-elemen di dalam daftar adalah: \n");
   for(i=0;i<n;i++)
       printf("%d\t",daftar[i]);
}

void main()
{
   int daftar[MAKS], n;
   printf("Masukkan jumlah elemen di dalam daftar maks = 10\n");
   scanf("%d",&n);
   bacadaftar(daftar,n);
   printf("Daftar sebelum pengurutan adalah:\n");
   tampilDaftar(daftar,n);
   pengurutanQuick(daftar,0,n-1);
   printf("\nDaftar setelah pengurutan adalah:\n");
   tampilDaftar(daftar,n);
}
