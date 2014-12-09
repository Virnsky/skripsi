/* Gambar 10.19: gambar10_19.c
   Menciptakan pohon biner dan menjelajahinya dengan
   cara preorder, inorder, dan postorder */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* struktur referensi-diri */
struct simpulPohon {
  struct simpulPohon *kiriPtr; /* pointer ke subpohon kiri */
  int data; /* nilai simpul */
  struct simpulPohon *kananPtr; /* pointer ke subpohon kanan */
}; /* akhie struktur simpulPohon */

typedef struct simpulPohon SimpulPohon; /* sinonim untuk struct simpulPohon */
typedef SimpulPohon *SimpulPohonPtr; /* sinonim untuk SimpulPohon* */

/* prototipe */
void sisipkanSimpul( SimpulPohonPtr *pohonPtr, int nilai );
void inOrder( SimpulPohonPtr pohonPtr );
void preOrder( SimpulPohonPtr pohonPtr );
void postOrder( SimpulPohonPtr pohonPtr );

/* fungsi main untuk memulai eksekusi */
int main( void )
{
  int i; /* kounter untuk loop dari 1-10 */
  int item; /* variabel untuk menampung nilai acak */
  SimpulPohonPtr akarPtr = NULL; /* pohon awalnya kosong */

  srand( time( NULL ) );
  printf( "Angka-angka yang akan ditempatkan pada pohon adalah:\n" );

  /* menyisipkan angka acak antara 0 sampai 14 ke dalam pohon */
  for ( i = 1; i <= 10; i++ ) {
    item = rand() % 15;
    printf( "%3d", item );
    sisipkanSimpul( &akarPtr, item );
  } /* akhir for */

  /* menjelajahi pohon secara preOrder */
  printf( "\n\nPenjelajahan preOrder adalah:\n" );
  preOrder( akarPtr );

  /* menjelajahi pohon secara inOrder */
  printf( "\n\nPenjelajahan inOrder adalah:\n" );
  inOrder( akarPtr );

  /* menjelajahi pohon dengan postOrder */
  printf( "\n\nPenjelajahan postOrder adalah:\n" );
  postOrder( akarPtr );
  return 0; /* indikasi terminasi sukses */
} /* akhir main */

/* menyisipkan simpul ke dalam pohon */
void sisipkanSimpul( SimpulPohonPtr *pohonPtr, int nilai )
{
  /* jika pohon kosong */
  if ( *pohonPtr == NULL ) {
    *pohonPtr = malloc( sizeof( SimpulPohon ) );

    /* jika memori telah dialokasikan dan data ditugaskan */
    if ( *pohonPtr != NULL ) {
      ( *pohonPtr )->data = nilai;
      ( *pohonPtr )->kiriPtr = NULL;
      ( *pohonPtr )->kananPtr = NULL;
	} /* akhir if */
    else {
      printf( "%d tidak disisipkan. Memori tidak tersedia.\n", nilai );
	} /* akhir else */
  } /* akhir if */
  else { /* pohon tidak kosong */
    /* data yang akan disisipkan kurang dari data di dalam simpul sekarang */
    if ( nilai < ( *pohonPtr )->data ) {
      sisipkanSimpul( &( ( *pohonPtr )->kiriPtr ), nilai );
	} /* akhir if */

    /* data yang akan disisipkan lebih besar dari data di dalam simpul sekarang */
    else if ( nilai > ( *pohonPtr )->data ) {
      sisipkanSimpul( &( ( *pohonPtr )->kananPtr ), nilai );
	} /* akhir else if */
    else { /* nilai duplikat dibuang */
      printf( "duplikat dibuang" );
	} /* akhir else */
  } /* akhir else */
} /* akhir fungsi sisipkanSimpul */

/* memulai penjelajahan inorder atas pohon */
void inOrder( SimpulPohonPtr pohonPtr )
{
  /* jika pohon tak kosong kemudian jelajahi */
  if ( pohonPtr != NULL ) {
    inOrder( pohonPtr->kiriPtr );
    printf( "%3d", pohonPtr->data );
    inOrder( pohonPtr->kananPtr );
  } /* akhir if */
} /* akhir fungsi inOrder */

/* memulai penjelajahan preorder atas pohon */
void preOrder( SimpulPohonPtr pohonPtr )
{
  /* jika pohon tak kosong kemudian jelajahi */
  if ( pohonPtr != NULL ) {
    printf( "%3d", pohonPtr->data );
    preOrder( pohonPtr->kiriPtr );
    preOrder( pohonPtr->kananPtr );
  } /* akhir if */
} /* akhir fungsi preOrder */

/* memulai penjelajahan postorder atas pohon */
void postOrder( SimpulPohonPtr pohonPtr )
{
  /* jika pohon tak kosong kemudian jelajahi */
  if ( pohonPtr != NULL ) {
    postOrder( pohonPtr->kiriPtr );
    postOrder( pohonPtr->kananPtr );
    printf( "%3d", pohonPtr->data );
  } /* akhir if */
} /* akhir fungsi postOrder */
