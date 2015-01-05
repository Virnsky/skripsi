#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "treelibrary.h"
#include "fileManipulator.h"

#define _DEBUG_MODE_

FILE* fp;
fpos_t pos1;
char str2[10], str1[10], str3[10], s[10];
int i=0, z=0, k=0, p=0;
int x,sisa,total,limit, huf_var, batas, mulai, hufChoose;
char temp_prio1[10], temp_prio2[10], temp_prio3[10], temp_prio4[10], temp_prio5[10], vt[10];
int temp_ind1 = 0, temp_ind2 = 0, temp_ind3 = 0, temp_ind4 = 0, temp_ind5 = 0,temp_max_fre;
int a=0,b=0,c=0,d=0,e=0,f=0,g=0,h=0;

bool bitEncode[80000000];
int bitLen;

//misc file handler
char tempsajo[50], argv2[50];

char filename1[50];
char filename2[50];
char filename3[50];

struct data_t
{
	char symbol[10];
	int frekuensi;
	int lenght;
};

struct symbol_list
{
	data_t t;
	struct symbol_list* next;
};

struct list
{
	struct symbol_list* first;
};


void add_symbol(char symbol_name[],list *L)
{
	symbol_list* smb=(symbol_list*) malloc(sizeof(symbol_list));

	strcpy(smb->t.symbol, symbol_name);
	smb->t.frekuensi=1;
	smb->next=NULL;

	if(L->first==NULL)
    {
        L->first=smb;
    }else
    {
        symbol_list* last_symbol=L->first;
        while(last_symbol->next!=NULL)
        {
            last_symbol=last_symbol->next;
        }
        last_symbol->next=smb;
    }

	smb=NULL;

}

// bubble sort: prioritize length then frequency if the lengths are equal
void sort_list(list* L){
    if(L->first!=NULL){
		char bubble_burst;
        struct symbol_list *lt, *temp;
        do{
			lt=L->first;
			bubble_burst= 0;
			// first element
			if (
				(strlen(lt->t.symbol) > strlen(lt->next->t.symbol)) ||
				( (strlen(lt->t.symbol) == strlen(lt->next->t.symbol))
					&& (lt->t.frekuensi > lt->next->t.frekuensi))
				){
				temp= lt->next->next;
				L->first = lt->next;
				L->first->next= lt;
				lt->next= temp;
				bubble_burst= 1;
				}
			// second element and forth
			while(lt->next!=NULL && lt->next->next!=NULL){
				//printf("%d. symbol:%s\tfrek:%d\n",i,lt->t.symbol,lt->t.frekuensi);
				if (
					(strlen(lt->next->t.symbol) > strlen(lt->next->next->t.symbol)) ||
					((strlen(lt->next->t.symbol) == strlen(lt->next->next->t.symbol))
						&& (lt->next->t.frekuensi > lt->next->next->t.frekuensi))
				){
					temp= lt->next->next;
					lt->next->next= temp->next;
					temp->next= lt->next;
					lt->next= temp;
					bubble_burst= 1;
					}
				lt=lt->next;
				}
			}
		while(bubble_burst);
    }
    else printf("list masih kosong\n");
}

void print_list(list* L)
{
    if(L->first!=NULL)
    {
        symbol_list* lt=L->first;
        int i=1;
        while(lt!=NULL)
        {
            printf("%d. symbol:%s\tlen:%d\tfrek:%d\n",i,lt->t.symbol,strlen(lt->t.symbol),lt->t.frekuensi);
            //~ if (lt->next !=NULL){
				//~ if (lt->next->next !=NULL){
					//~ printf("boooo!\n");
					//~ }
				//~ }

            lt=lt->next;
            i++;
        }
    }else
    {
        printf("list kosong\n");
    }
}

void check_symbol(char symbol_name[],list* L)
{
    bool found=false;
    symbol_list* srclist=L->first;
    while(srclist!=NULL)
    {
        if(!strcmp(srclist->t.symbol,symbol_name))
        {
            srclist->t.frekuensi++;
            found=true;
        }
        srclist=srclist->next;
    }
    if(found==false)
    {
        add_symbol(symbol_name,L);
    }
}



symbol_list* get_symbol(const char* symbol_name,list* L)
{

    symbol_list* srclist=L->first;
    bool found=false;

    while(srclist!=NULL)
    {
        if(!strcmp(srclist->t.symbol,symbol_name))
        {
            return srclist;
        }
        srclist=srclist->next;
    }
    srclist=NULL;
    return NULL;
}

void var_reset(){
    //printf("\nTahap Var_Reset : Ok");
    temp_max_fre = 0;
    memset(str1, '\0',10);
    memset(str2, '\0',10);
    memset(str3, '\0',10);
    memset(temp_prio1, '\0',10);
    memset(temp_prio2, '\0',10);
    memset(temp_prio3, '\0',10);
    memset(temp_prio4, '\0',10);
    memset(temp_prio5, '\0',10);
    memset(vt, '\0',10);
    total=0;
    k=0;
};

void compare_sysmbol(list *lt,char str[],int index_seek, int limit, char temp_symbol [],int &index_symbol, int &frek_symbol){
    var_reset();
    //printf("\nTahap Awal Comparing Simbol : Ok");
    while(k<limit){
        memset(str, '\0',10);
        total = index_seek+k;
//        fseek(fp,total,SEEK_SET);
        yogaSeek(fp,total,YOGA_SEEK_SET);
        fread(str,1,huf_var,fp);
        symbol_list* yuri=get_symbol(str,lt);
        if(yuri==NULL){
            printf("");
        }
        else{
            int f=yuri->t.frekuensi;
            strcpy(s,str);
            if(frek_symbol<f){
                if((count_char_max(fp)-z)>=huf_var){
                    strncpy(temp_symbol,s,huf_var);
                    index_symbol = k;
                    frek_symbol = f;
                 }
            }
        }
        //printf("\nFound Simbol : %s",str);
    k++;
    }
};
void preadd_parse(list* lt,char str[],int limited,int index, list* L){
    var_reset();
//    fseek(fp,index,SEEK_SET);
    yogaSeek(fp,index,YOGA_SEEK_SET);
    fread(str,1,limited,fp);
    //printf("\nIsi str : %s",str);
    strncpy(vt,str,limited);
    //printf("Isi strncpy : %s",vt);
    add_symbol(vt,lt);
    check_symbol(vt,L);
    if(!strcmp(str,"")) printf("");
};

void hufLengthFix(list *L, char str[]){

};

huffTable* findHuffTable(listHuff* hf,const char* symbol)
{
    huffTable* srclist=hf->first;

    while(srclist!=NULL)
    {
        if(!strcmp(srclist->huff.symbol,symbol))
        {
            return srclist;
        }
        srclist=srclist->next;
    }
    srclist=NULL;
    return NULL;
}

void resetEncodeTable()
{
    bitLen=0;
}

void addEncodeTable(bool val)
{
    bitEncode[bitLen]=val;
    bitLen++;
}

void printBit(char a)
{
//    printf("%d",a/256);
    bool g;
    g=((a&0x80)&&0x80);printf("%d",g);
    g=((a&0x40)&&0x40);printf("%d",g);
    g=((a&0x20)&&0x20);printf("%d",g);
    g=((a&0x10)&&0x10);printf("%d",g);
    g=((a&0x08)&&0x08);printf("%d",g);
    g=((a&0x04)&&0x04);printf("%d",g);
    g=((a&0x02)&&0x02);printf("%d",g);
    g=a&1;printf("%d",g);
}

void createEncodeTable(listHuff* hf,list* L,list* keyList,const char* fFileName,const char* fFileKeyName)
{
        symbol_list* lt=L->first;
        int i;int j;

        FILE* notimportant=fopen("a_debug.txt","w");

        while(lt!=NULL)
        {
            huffTable* huffSrc=findHuffTable(hf,lt->t.symbol);
            if(huffSrc==NULL)
            {
                printf("failed\n");
                resetEncodeTable();
                return;
            }else
            {
//                fprintf(notimportant,"%s",huffSrc->huff.symbol);
                for(i=0;i<huffSrc->huff.len;i++)
                {
                    addEncodeTable(huffSrc->huff.encode[i]);
                }
            }

            lt=lt->next;
        }//for(i=0;i<bitLen;i++){if(i%8==0){printf(" ");}printf("%d",bitEncode[i]);}printf("\nnumber of bit%d\n",bitLen);

    FILE* kk=fopen(fFileKeyName,"w");
    FILE* jj=fopen(fFileName,"w");
    char m=0;
    int countByte=0;
    int countHuffTable=0;

    //count number of keys
    symbol_list* a=keyList->first;
    while(a!=NULL)
    {
        countHuffTable++;
        a=a->next;
    }

    //print number of keys and number of bit
    fprintf(kk,"%d %d ",countHuffTable,bitLen);

    m=0;
    a=keyList->first;
    while(a!=NULL)
    {
        printf("%d %s %d\n",strlen(a->t.symbol),a->t.symbol,a->t.frekuensi);
        fprintf(kk,"%c%s%c",strlen(a->t.symbol),a->t.symbol,a->t.frekuensi);
        fprintf(notimportant,"%d %s %d\n",strlen(a->t.symbol),a->t.symbol,a->t.frekuensi);
        a=a->next;
    }

//    m=0;
//    a=hf->first;
//    while(a!=NULL)
//    {
////        printf("%d %s %d ",strlen(a->huff.symbol),a->huff.symbol,a->huff.len);
//        fprintf(jj,"%c%s%c",strlen(a->huff.symbol),a->huff.symbol,a->huff.len);
//
//        // 4 byte huffman
//        for(j=0;j<4;j++)
//        {
//            for(i=0;i<8;i++)
//            {
//                m=m | (a->huff.encode[i+8*j]<<(7-i));
//            }
//            fprintf(jj,"%c",m);
////            printBit(m);
//            m=0;
//        }
//        a=a->next;
//    }//    printf("\n");



    m=0;
    for(i=0;i<bitLen;i++)
    {
//        printf("%d",bitEncode[i]);
        m=m | (bitEncode[i]<<(7-countByte));
        countByte++;
        if(countByte>=8)
        {
            countByte=0;
            #ifdef _DEBUG_MODE_
//            printBit(m);
            #endif // _DEBUG_MODE_
            fprintf(jj,"%c",m);
            m=0;
        }
    }
    //sisa kode huffman yang belum tertulis
    while(countByte!=0)
    {
        m=m | (0<<(7-countByte));
        countByte++;
        if(countByte>=8)
        {
            countByte=0;
            #ifdef _DEBUG_MODE_
//            printBit(m);
            #endif // _DEBUG_MODE_
            fprintf(jj,"%c",m);
            m=0;
        }
    }
    fclose(jj);
    fclose(kk);
}

void decodeTable(const char* filename,const char* filenameKey)
{
    int keycount=0;
    int encodecount=0;
    int i=0;
    int j=0;
    int maxi;
    bool whatever;
    char b=0;
    char c[4]={0,0,0,0};
    char symbol;
    char tempScan[8000000];
    char huffsimbol[10];
    bool path[32];
    int len;
//    FILE* ja=fopen("decode.txt","w");
    FILE* jj=fopen(filename,"r");
    FILE* kk=fopen(filenameKey,"r");
    if(jj==NULL) return;
    if(kk==NULL) return;
    fseek(kk,4,SEEK_SET);
    fseek(jj,4,SEEK_SET);

    fscanf(kk,"%d",&keycount);
    fscanf(kk,"%d",&encodecount);//printf("%d %d\n",keycount,encodecount);
    fseek(kk,1,SEEK_CUR);

    htree* itsrandom=(htree*)malloc(sizeof(htree));
    listHuff* anorandom=(listHuff*)malloc(sizeof(listHuff));
    itsrandom->left=NULL;
    itsrandom->right=NULL;
    anorandom->first=NULL;

    for(i=0;i<keycount;i++)
    {

        fscanf(kk,"%c",&b);//printf("%d ",b);
        for(j=0;j<b;j++)
        {
            fscanf(kk,"%c",&symbol);
            printf("%c",symbol);
            huffsimbol[j]=symbol;
        }
        huffsimbol[b]='\0';

        fscanf(jj,"%c",&b);
        len=b;              //printf("%d ",b);
        //AMBIL 2 BYTE HUFFMAN CODE
        fscanf(kk,"%c",&c[0]); //printBit(b);printf("\n");
        fscanf(kk,"%c",&c[1]); //printBit(c);printf("\n");
        fscanf(kk,"%c",&c[2]);
        fscanf(kk,"%c",&c[3]);
        printf("%d %c%c%c%c\n",b,c[0],c[1],c[2],c[3]);

        //masa bodo sama koding panjang!! pala udah pusing
/*
        path [0]=c[0]&0x80;path [1]=c[0]&0x40;
        path [2]=c[0]&0x20;path [3]=c[0]&0x10;
        path [4]=c[0]&0x08;path [5]=c[0]&0x04;
        path [6]=c[0]&0x02;path [7]=c[0]&0x01;

        path [8]=c[1]&0x80;path [9]=c[1]&0x40;
        path[10]=c[1]&0x20;path[11]=c[1]&0x10;
        path[12]=c[1]&0x08;path[13]=c[1]&0x04;
        path[14]=c[1]&0x02;path[15]=c[1]&0x01;//for(j=0;j<16;j++){printf("%d",path[j]);}printf("\n");

        path[16]=c[2]&0x80;path[17]=c[2]&0x40;
        path[18]=c[2]&0x20;path[19]=c[2]&0x10;
        path[20]=c[2]&0x08;path[21]=c[2]&0x04;
        path[22]=c[2]&0x02;path[23]=c[2]&0x01;

        path[24]=c[3]&0x80;path[25]=c[3]&0x40;
        path[26]=c[3]&0x20;path[27]=c[3]&0x10;
        path[28]=c[3]&0x08;path[29]=c[3]&0x04;
        path[30]=c[3]&0x02;path[31]=c[3]&0x01;
*/
        //BUAT HUFFMAN TABLE DARI INFORMASI DIATAS
//        huffTreeCreateFromBit(itsrandom,path,len,huffsimbol);

        //reset dulu mas bro
//        for(j=0;j<32;j++)
//        {
//            path[j]=false;
//        }

    }
//    printf("\nprint recently created huffman tree\n\t\t---\n");

//    huffTableCreate(itsrandom,anorandom);

//    huffTablePrint(&anorandom);
//    printf("\ndone\n");

    resetEncodeTable();

    i=0;
    symbol=fgetc(jj);
    while(symbol!=EOF)
    {
        tempScan[i]=symbol;
        i++;
        symbol=fgetc(jj);
    }
    tempScan[i]='\0';
    maxi=i;
    for(i=0;i<maxi;i++)
    {
        for(j=0;j<8;j++)
        {
            switch(j)
            {
                case 0: whatever=tempScan[i]&0x80;break;
                case 1: whatever=tempScan[i]&0x40;break;
                case 2: whatever=tempScan[i]&0x20;break;
                case 3: whatever=tempScan[i]&0x10;break;
                case 4: whatever=tempScan[i]&0x8;break;
                case 5: whatever=tempScan[i]&0x4;break;
                case 6: whatever=tempScan[i]&0x2;break;
                case 7: whatever=tempScan[i]&0x1;break;
            }
            addEncodeTable(whatever);
        }
    }
    //untuk mengubah stream bit sesuai dengan yang ada di File
    bitLen=encodecount;
    printf("\nthis is stream of encode (bitLen:%d encodecount:%d)\n",bitLen,encodecount);
    scanf("%s",filename1);
    FILE* endOfMisery=fopen(filename1,"w");

    //mulai menDECODE dan menulis
    fprintf(endOfMisery,"{this is decoded file}\n");
    htree* tempTree=itsrandom;
    for(i=0;i<encodecount;i++)
    {
        if(bitEncode[i]==false)
        {
            //pindah ke kiri
            tempTree=tempTree->left;
            //apakah sudah di ujung?
            if(tempTree->left==NULL)
            {
                fprintf(endOfMisery,"%s",tempTree->symbol);
                tempTree=itsrandom;
            }
        }
        if(bitEncode[i]==true)
        {
            //pindah ke kanan
            tempTree=tempTree->right;
            //apakah sudah di ujung?
            if(tempTree->right==NULL)
            {
                fprintf(endOfMisery,"%s",tempTree->symbol);
                tempTree=itsrandom;
            }
        }
        printf("%d",bitEncode[i]);
    }
    fclose(jj);fclose(kk);
    fclose(endOfMisery);
	printf("\n");
}


int main (int argc,char **argv){

    if (argc!=3){
//		printf("cara pakai: program INPUT-FILE OUTPUT-FILE\n");
//		printf("cara pakai: pustaka huffman berupa berkas OUTPUT-FILE.dat\n");
//		return(0);
        printf("nama file masukan  :");scanf("%s",&filename1);
        printf("nama file keluaran :");scanf("%s",&filename2);
        strcpy(filename3,filename2);
        strcat(filename2,".dat");
        strcat(filename3,"_key.dat");
    }else
    {
        strcpy(filename1,argv[1]);
        strcpy(filename2,argv[2]);
        strcpy(filename3,filename2);
        strcat(filename2,".dat");
        strcat(filename3,"_key.dat");
    }

    fp=fopen(filename1, "r");
    if(fp==NULL)
    {
        printf("file masukan tidak ada\n");
        return 0;
    }
    list L;
    L.first=NULL;
    list parselist;
    list tabel_huffman;
    parselist.first=NULL;
    tabel_huffman.first=NULL;

    printf("Masukan Panjang Huffman (1 sampai 6): ");
    scanf("%d", &huf_var);
    printf("\nPilih Metode Huffman : \n[1] Variasi Panjang Simbol \n[2] Panjang Simbol Fix\nPilihan : ");
    scanf("%d", &hufChoose);
    if(huf_var==1){
        fseek(fp,0,SEEK_SET);
        printf("%d character left\n",count_char_left(fp));
        for(i=0;i<5;i++) fgetc(fp);
        printf("%d character left\n",count_char_left(fp));
        printf("\nProses Pembentukan dan Pencarian Kemunculan Simbol....... ");
        for(i=0;i<count_char_max(fp)-huf_var; i++){
//            fseek(fp,i,SEEK_SET);
            yogaSeek(fp,i,YOGA_SEEK_SET);
            fread(str2,1,huf_var,fp);
            check_symbol(str2,&tabel_huffman);
            add_symbol(str2,&parselist);
        }
        printf("Selesai\n");
    }
    else{
        if(hufChoose==1){
        fseek(fp,0,SEEK_SET);
        printf("%d character left\n",count_char_left(fp));
        for(i=0;i<5;i++) fgetc(fp);
        printf("%d character left\n",count_char_left(fp));
        printf("\nProses Pembentukan dan Pencarian Kemunculan Simbol....... ");
        for(i=0;i<count_char_max(fp)-(huf_var-1); i++){
//            fseek(fp,i,SEEK_SET);
            yogaSeek(fp,i,YOGA_SEEK_SET);
            fread(str2,1,huf_var,fp);
            check_symbol(str2,&L);
        }
        printf("Selesai\n");
        //print_list(&L);
        //printf("\nTotal Karakter Dalam Berkas Adalah %d\n",count_char_max(fp));

            /* ##### BEGIN OF PARSING SYMBOLS ##### */
        printf("\nProses Parsing Simbol dan Pembentukan Tabel Huffman....... ");
        fseek(fp,0,SEEK_SET);
        for(z; z<=(count_char_max(fp)-huf_var); z){
            var_reset();
            //printf("\n\Proses ke %d",p);
//            fseek(fp,z,SEEK_SET);
            yogaSeek(fp,z,YOGA_SEEK_SET);
            compare_sysmbol(&L,str1,z,huf_var,temp_prio1,temp_ind1,temp_max_fre);                   // Tahap 1

            if (temp_ind1!=0){
                mulai=z+temp_ind1;
                compare_sysmbol(&L,str2,mulai,huf_var,temp_prio2,temp_ind2,temp_max_fre);       // Tahap 2

                if(temp_ind2!=0){
                    batas=temp_ind1+temp_ind2; //????
                    mulai=(z+temp_ind2+temp_ind1);
                    compare_sysmbol(&L,str3,mulai,huf_var,temp_prio3,temp_ind3,temp_max_fre);

                    if(temp_ind3!=0){
                        sisa=temp_ind1+temp_ind2+temp_ind3-1;
                    }
                    else{
                        sisa=temp_ind1+temp_ind2-1;
                    }
                    if(sisa>huf_var){
                        batas=sisa-huf_var+1;
                        compare_sysmbol(&L,str1,z,batas,temp_prio4,temp_ind4,temp_max_fre);
                        strncpy(temp_prio5,temp_prio4,huf_var);

                        if(temp_ind4!=0){
                            batas=temp_ind4-1;
                            preadd_parse(&parselist,str1,batas,z, &tabel_huffman);
                            a++;
                            z=z+temp_ind4;
                            //printf("\n-->PreAdd Symbol : %s",str1);
                            /*if(temp_prio4 != temp_prio5){
                                batas=(sisa+1)-huf_var;
                                compare_sysmbol(&L,str2,z,batas,temp_prio5,temp_ind5,temp_max_fre);
                                add_symbol(temp_prio5,&parselist);
                                check_symbol(temp_prio5,&tabel_huffman);
                                b++;
                            }
                            else{
                                add_symbol(temp_prio4,&parselist);
                                check_symbol(temp_prio4,&tabel_huffman);
                                c++;
                            }
                            z=z+temp_ind4+huf_var;
                        */
                        }
                        else{
                            add_symbol(temp_prio4,&parselist);
                            check_symbol(temp_prio4,&tabel_huffman);
                            z=z+temp_ind4+huf_var;
                            d++;
                            //printf("\n-->Add Symbol : %s",temp_prio4);
                        }
                    }
                    else{
                        batas=sisa;
                        preadd_parse(&parselist,str1,batas,z, &tabel_huffman);
                        z=z+sisa;
                        g++;
                        //printf("\n-->PreAdd Symbol : %s",str1);
                    }
                }
                else{
                    batas=temp_ind1;
                    preadd_parse(&parselist,str2,batas,z, &tabel_huffman);
                    z=z+temp_ind1;
                    e++;
                    //printf("\n-->PreAdd Symbol : %s",str2);
                }
            }
            else{
                add_symbol(temp_prio1,&parselist);
                check_symbol(temp_prio1,&tabel_huffman);
                z=z+huf_var+temp_ind1;
                f++;
                //printf("\n-->Add Symbol : %s",temp_prio1);
            }
            p++;

        }
        batas=count_char_max(fp)-z;
        if(batas!=0){
            preadd_parse(&parselist,str3,batas,z,&tabel_huffman);
        }
        printf("Selesai\n");
        /*  ##### END OF PARSING SYMBOLS #####   */
        }
        else{
            fseek(fp,0,SEEK_SET);
            printf("%d character left\n",count_char_left(fp));
            for(i=0;i<5;i++) fgetc(fp);
            printf("%d character left\n",count_char_left(fp));
            printf("\nProses Pembentukan, Pencarian Kemunculan, dan Parsing Simbol....... ");
            for(i=0;i<count_char_max(fp)-huf_var; i){
//                fseek(fp,i,SEEK_SET);
                yogaSeek(fp,i,YOGA_SEEK_SET);
                fread(str2,1,huf_var,fp);
                check_symbol(str2,&tabel_huffman);
                add_symbol(str2,&parselist);
                i=i+huf_var;
            }
            batas=count_char_max(fp)-i;
            if(batas!=0){
                preadd_parse(&parselist,str3,batas,i,&tabel_huffman);
            }
            printf("Selesai\n");
            }
        }
    fclose(fp);

    printf("\n\nData yang siap dikode kan\n");
    #ifdef _DEBUG_MODE_
    print_list(&parselist);
    #endif
    //printf("\n\nTabel Huffman\n");
    printf("\nProses Sorting Tabel Huffman....... ");
    sort_list(&tabel_huffman);
    printf("Selesai\n");
    //print_list(&tabel_huffman);
    //printf("\na = %d\nb = %d\nc = %d \nd = %d\ne = %d\nf = %d \n",a,b,c,d,e,f);

    //Special test 'untuk pembentukan pohon'
    htlist_head* akarpohon;
    akarpohon->first=NULL;
    printf("\ntes1\n");
    //konversi tabel huffman -> tree branch list
    htree* pohon;
    symbol_list* ksim=tabel_huffman.first;
    while(ksim!=NULL)
    {
        add_tree_list(akarpohon,ksim->t.symbol,ksim->t.frekuensi);
        ksim=ksim->next;
    }
    printf("\ntes2\n");
    //selesai konversi

    //proses mengubah tree branch list menjadi huffman tree
    create_tree(akarpohon);
    //    debug_list(akarpohon);
    //printf("succesfully create tree\n");

    //
    listHuff beta;
    beta.first=NULL;
    huffTableCreate(akarpohon->first->branch,&beta);

    printf("\ntes3\n");
    createEncodeTable(&beta,&parselist,&tabel_huffman,filename2,filename3);

//    printf("\nready to decode table\n");
//    printf("\ntes4\n");
//    decodeTable(filename2,filename3);
//    printf("\ntes5\n");
//    printPaths(akarpohon->first->branch,pp);
//    fclose(pp);
    //print_list(&tabel_huffman);

//test selesai
    return 1;
}

