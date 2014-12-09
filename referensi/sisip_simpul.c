   /* Menyisipkan simpul dengan program rekursif*/
   # include <stdio.h>
   # include <stdlib.h>
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
         p->link = sisip(p->link,n);/* loop while digantikan pemanggilan rekursif */
      return (p);
   }
   
   void tampilList ( struct simpul *p )
   {
         printf("Data di dalam list adalah\n");
         while (p!= NULL)
         {
            printf("%d\t",p-> data);
            p = p-> link;
         }
   }
   
   void main()
   {
         int n;
         int x;
         struct simpul *awal = NULL ;
         printf("Masukkan simpula yang akan diciptakan \n");
         scanf("%d",&n);
         while ( n-- > 0 )
         {
            printf( "Masukkan nilai-nilai yang akan ditempatkan ke dalam suatu simpul\n");
            scanf("%d",&x);
            awal = sisip ( awal, x );
         }
         printf("List yang diciptakan adalah\n");
         tampilList ( awal );
   }

