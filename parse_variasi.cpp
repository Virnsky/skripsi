#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "treelibrary.h"
#include "fileManipulator.h"

FILE* fp;
fpos_t pos1;
char str2[10], str1[10], str3[10], s[10];
int i=0, z=0, k=0, p=0;
int x,sisa,total,limit, huf_var, batas, mulai, hufChoose;
char temp_prio1[10], temp_prio2[10], temp_prio3[10], temp_prio4[10], temp_prio5[10], vt[10];
int temp_ind1 = 0, temp_ind2 = 0, temp_ind3 = 0, temp_ind4 = 0, temp_ind5 = 0,temp_max_fre;
int a=0,b=0,c=0,d=0,e=0,f=0,g=0,h=0;

bool bitEncode[50000];
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

int  count_char_max(FILE* t_fp)
{
    fpos_t pos;
    int count_char=0;
    char char_scan;

    fgetpos(t_fp,&pos);
    fseek(t_fp,0,SEEK_SET);
    char_scan=fgetc(t_fp);
    while(char_scan!=EOF)
    {
        count_char++;
        char_scan=fgetc(t_fp);
    }
    fsetpos(t_fp,&pos);
    return count_char;
}

int count_char_left(FILE* t_fp)
{
    fpos_t pos;
    int count_char=0;
    char char_scan;

    fgetpos(t_fp,&pos);

    char_scan=fgetc(t_fp);
    while(char_scan!=EOF)
    {
        count_char++;
        char_scan=fgetc(t_fp);
    }
    fsetpos(t_fp,&pos);
    return count_char;
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
        fseek(fp,total,SEEK_SET);
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
    fseek(fp,index,SEEK_SET);
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
    char g;
    g=a&0b10000000;
    g=g>>7;
    g=g&1;
    printf("%d",g);
    g=a&0b01000000;
    g=g>>6;
    printf("%d",g);
    g=a&0b00100000;
    g=g>>5;
    printf("%d",g);
    g=a&0b00010000;
    g=g>>4;
    printf("%d",g);
    g=a&0b00001000;
    g=g>>3;
    printf("%d",g);
    g=a&0b00000100;
    g=g>>2;
    printf("%d",g);
    g=a&0b00000010;
    g=g>>1;
    printf("%d",g);
    g=a&1;
    printf("%d",g);
}

void createEncodeTable(list* L,listHuff* hf,const char* fFileName)
{
        symbol_list* lt=L->first;
        int i;
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
                for(i=0;i<huffSrc->huff.len;i++)
                {
                    addEncodeTable(huffSrc->huff.encode[i]);
                }
            }

            lt=lt->next;
        }//for(i=0;i<bitLen;i++){if(i%8==0){printf(" ");}printf("%d",bitEncode[i]);}printf("\nnumber of bit%d\n",bitLen);

    FILE* jj=fopen(fFileName,"w");
    char m=0;
    int countByte=0;
    int countHuffTable=0;
    fprintf(jj,"%c%c",0xA7,0x7A);

    //count number of keys
    huffTable* a=hf->first;
    while(a!=NULL)
    {
        countHuffTable++;
        a=a->next;
    }

    //print number of keys and number of bit
    fprintf(jj,"%d %d ",countHuffTable,bitLen);

    m=0;
    a=hf->first;
    while(a!=NULL)
    {
//        printf("%d %s %d ",strlen(a->huff.symbol),a->huff.symbol,a->huff.len);
        fprintf(jj,"%c%s%c",strlen(a->huff.symbol),a->huff.symbol,a->huff.len);
        // 8 bit pertama huffman code
        for(i=0;i<8;i++)
        {
            m=m | (a->huff.encode[i]<<(7-i));
        }
        fprintf(jj,"%c",m);//printBit(m);printf("\n");
        m=0;
        //8 bit ke dua
        for(i=0;i<8;i++)
        {
            m=m | (a->huff.encode[i+8]<<(7-i));
        }
        fprintf(jj,"%c",m);//printBit(m);printf("\n");
        m=0;

        a=a->next;
    }

    printf("\n");

    m=0;
    for(i=0;i<bitLen;i++)
    {
//        printf("%d",bitEncode[i]);
        m=m | (bitEncode[i]<<(7-countByte));
        countByte++;
        if(countByte>=8)
        {
            countByte=0;
//            printBit(m);
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
//            printBit(m);
            fprintf(jj,"%c",m);
            m=0;
        }
    }
    fclose(jj);
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
    char c=0;
    char symbol;
    char tempScan[5000];
    char huffsimbol[10];
    bool path[16];
    int len;
//    FILE* ja=fopen("decode.txt","w");
    FILE* jj=fopen(filename,"r");
    if(jj==NULL) return;
    fseek(jj,2,SEEK_SET);

    fscanf(jj,"%d",&keycount);
    fscanf(jj,"%d",&encodecount);//printf("%d %d\n",keycount,encodecount);
    fseek(jj,1,SEEK_CUR);

    htree itsrandom;
    listHuff anorandom;
    itsrandom.left=NULL;
    itsrandom.right=NULL;
    anorandom.first=NULL;

    for(i=0;i<keycount;i++)
    {

        fscanf(jj,"%c",&b);//printf("%d ",b);
        for(j=0;j<b;j++)
        {
            fscanf(jj,"%c",&symbol);//printf("%c",symbol);
            huffsimbol[j]=symbol;
        }
        huffsimbol[b]='\0';

        fscanf(jj,"%c",&b);
        len=b;              //printf("%d ",b);
        //AMBIL 2 BYTE HUFFMAN CODE
        fscanf(jj,"%c",&b); //printBit(b);printf("\n");
        fscanf(jj,"%c",&c); //printBit(c);printf("\n");

        //masa bodo sama koding panjang!! pala udah pusing
        path [0]=b&0x80;path [1]=b&0x40;
        path [2]=b&0x20;path [3]=b&0x10;
        path [4]=b&0x08;path [5]=b&0x04;
        path [6]=b&0x02;path [7]=b&0x01;
        path [8]=c&0x80;path [9]=c&0x40;
        path[10]=c&0x20;path[11]=c&0x10;
        path[12]=c&0x08;path[13]=c&0x04;
        path[14]=c&0x02;path[15]=c&0x01;//for(j=0;j<16;j++){printf("%d",path[j]);}printf("\n");

        //BUAT HUFFMAN TABLE DARI INFORMASI DIATAS
        huffTreeCreateFromBit(&itsrandom,path,len,huffsimbol);

        //reset dulu mas bro
        for(j=0;j<16;j++)
        {
            path[j]=false;
        }

    }
//    printf("\nprint recently created huffman tree\n\t\t---\n");
    huffTableCreate(&itsrandom,&anorandom);
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
    FILE* endOfMisery=fopen(filename2,"w");

    //mulai menDECODE dan menulis
    fprintf(endOfMisery,"{this is decoded file}\n");
    htree* tempTree=&itsrandom;
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
                tempTree=&itsrandom;
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
                tempTree=&itsrandom;
            }
        }
        printf("%d",bitEncode[i]);
    }
    fclose(jj);
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
    if(fp==NULL) printf("file masukan tidak ada\n");
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
    print_list(&parselist);
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
    htree* pohon;
    symbol_list* ksim=tabel_huffman.first;
    while(ksim!=NULL)
    {
        add_tree_list(akarpohon,ksim->t.symbol,ksim->t.frekuensi);
        ksim=ksim->next;
    }
    printf("\ntes2\n");
//    FILE* pp=fopen("pohon.txt", "w");
//    sort_tree_list(akarpohon);
//    debug_list(akarpohon);
    //printf("create tree\n");
    create_tree(akarpohon);

//    debug_list(akarpohon);

    //printf("succesfully create tree\n");
    listHuff beta;
    beta.first=NULL;
    huffTableCreate(akarpohon->first->branch,&beta);
//    huffTablePrint(&beta);
    printf("\ntes3\n");
    createEncodeTable(&parselist,&beta);

    printf("\nready to decode table\n");
    printf("\ntes4\n");
    decodeTable(filename2,filename3);
    printf("\ntes5\n");
//    printPaths(akarpohon->first->branch,pp);
//    fclose(pp);
    //print_list(&tabel_huffman);

//test selesai
    return 1;
}

