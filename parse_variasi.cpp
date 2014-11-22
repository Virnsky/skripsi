#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <treelibrary.h>

FILE * fp;
fpos_t pos1;
char str2[10], str1[10], str3[10], s[10];
int i=0, z=0, k=0, p=0;
int x,sisa,total,limit, huf_var, batas, mulai;
char temp_prio1[10], temp_prio2[10], temp_prio3[10], temp_prio4[10], temp_prio5[10], vt[10];
int temp_ind1 = 0, temp_ind2 = 0, temp_ind3 = 0, temp_ind4 = 0, temp_ind5 = 0,temp_max_fre;

struct data_t
{
	char symbol[6];
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

void sort_list(list* L)
{
    if(L->first!=NULL)
    {
        symbol_list* lt=L->first;
        int i=0;
        while(lt!=NULL)
        {
            symbol_list* lu=lt;
            while(lu!=NULL)
            {
                if(lu->t.frekuensi > lu->next->t.frekuensi)
                {

                }
                lu=lu->next;
            }
            lt=lt->next;
        }
    }
}

void print_list(list* L)
{
    if(L->first!=NULL)
    {
        symbol_list* lt=L->first;
        int i=1;
        while(lt!=NULL)
        {
            printf("%d. symbol:%s   frek:%d\n",i,lt->t.symbol,lt->t.frekuensi);
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
        total = index_seek+k;
        fseek(fp,total,SEEK_SET);
        fread(str,1,huf_var,fp);
        symbol_list* yuri=get_symbol(str,lt);
        if(yuri==NULL){
            printf("\nYuri = Null");
        }
        else{
            int f=yuri->t.frekuensi;
            strcpy(s,str);
            if(frek_symbol<f){
                if(count_char_left(fp)>huf_var){
                    strncpy(temp_symbol,s,huf_var);
                    index_symbol = k;
                    frek_symbol = f;
                    printf("\nLoop Selesi Simbol %d : %s || %d || %d",k,temp_symbol,index_symbol,frek_symbol);

                 }
            }
        }
    k++;
    }
};
void preadd_parse(list* lt,char str[],int limited,int index){
    var_reset();
    fseek(fp,index,SEEK_SET);
    fread(str,1,(limited+1),fp);
    //printf("\nIsi str : %s",str);
    strncpy(vt,str,(limited+1));
    //printf("Isi strncpy : %s",vt);
    add_symbol(vt,lt);
    if(!strcmp(str,"")) printf(" Kosong");
};

int main (){
    fp=fopen("kucing.txt", "r");
    if(fp==NULL)    printf("kucing tidak ada\n");
    list L;
    L.first=NULL;
    list parselist;
    parselist.first=NULL;

    printf("Enter Length: ");
    scanf("%d", &huf_var);

    fseek(fp,0,SEEK_SET);
    printf("%d character left\n",count_char_left(fp));
    for(i=0;i<5;i++) fgetc(fp);
    printf("%d character left\n",count_char_left(fp));

    for(i=0;i<count_char_max(fp)-(huf_var-1); i++){
        fseek(fp,i,SEEK_SET);
        fread(str2,1,huf_var,fp);
        check_symbol(str2,&L);
    }
    print_list(&L);/*
//Special test 'untuk pembentukan pohon'
    htlist_head* akarpohon;
    akarpohon->first=NULL;
    htree* pohon;
    symbol_list* ksim=L.first;
    while(ksim!=NULL)
    {
        add_tree_list(akarpohon,ksim->t.symbol,ksim->t.frekuensi);
        ksim=ksim->next;
    }
    printf("create tree\n");
    create_tree(akarpohon,pohon);
    printf("succesfully create tree\n");
    printPaths(pohon);

    return 0;
//test selesai
*/
    printf("\nTotal Karakter Dalam Berkas Adalah %d\n",count_char_max(fp));

        /* ##### BEGIN OF PARSING SYMBOLS ##### */

    fseek(fp,0,SEEK_SET);
    for(z; z<=(count_char_max(fp)-(huf_var-1)); z){
        printf("\n\nProses Ke %d",p);
        fgetpos(fp, &pos1);
        compare_sysmbol(&L,str1,z,huf_var,temp_prio1,temp_ind1,temp_max_fre);                   // Tahap 1
        printf("\ntemp_prio1 adalah %s",temp_prio1);

        if (temp_ind1!=0){
            printf("\nMasuk ke Proses temp_ind1!=0");
            printf("\nIsi Sebelum proses, temp_prio2 adalah %s", temp_prio2);
            mulai=z+temp_ind1;
            compare_sysmbol(&L,str2,mulai,huf_var,temp_prio2,temp_ind2,temp_max_fre);       // Tahap 2
            printf("\ntemp_prio2 adalah %s",temp_prio2);

            if(temp_ind2!=0){
                printf("\nMasuk ke Proses temp_ind2!=0");
                batas=temp_ind1+temp_ind2;
                mulai=(z+temp_ind2+temp_ind1);
                compare_sysmbol(&L,str3,mulai,huf_var,temp_prio3,temp_ind3,temp_max_fre);
                printf("\ntemp_prio3 adalah %s",temp_prio3);
                sisa=temp_ind1+temp_ind2+temp_ind3+1;

                if(sisa>=huf_var){
                    printf("\nMasuk ke Proses sisa>=Huf_var");
                    batas=(sisa+1)-huf_var;
                    compare_sysmbol(&L,str1,z,batas,temp_prio4,temp_ind4,temp_max_fre);
                    printf("\ntemp_prio4 adalah %s",temp_prio4);

                    if(temp_ind4!=0){
                        printf("\nMasuk ke Proses temp_ind4!=0");
                        batas=temp_ind4-1;
                        preadd_parse(&parselist,str1,batas,z);
                        add_symbol(temp_prio4,&parselist);
                        printf("\nSimbol yang dimasukan Ke List adalah %s dan %s",str1,temp_prio4);
                        z=z+temp_ind4+huf_var;
                    }
                    else{
                        printf("\nMasuk ke Proses temp_ind4==0");
                        add_symbol(temp_prio4,&parselist);
                        printf("\nSimbol yang dimasukan Ke List adalah %s",temp_prio4);
                        z=z+temp_ind4+huf_var;
                    }
                }
            }
            else{
                printf("\nMasuk ke Proses Sisa<huf_var");
                batas=temp_ind1-1;
                preadd_parse(&parselist,str2,batas,z);
                printf("\nSimbol yang dimasukan Ke List adalah %s",str2);
                z=z+temp_ind1;
            }
        }
        else{
            printf("\nMasuk ke Proses temp_ind1==0");
            add_symbol(temp_prio1,&parselist);
            printf("\nSimbol yang dimasukan Ke List adalah %s",temp_prio1);
            z=z+huf_var;
        }
        p++;
        batas=count_char_max(fp)-z;
        printf("\nMax Char : %d dan Current Char : %d dan sisa %d",count_char_max(fp),z,batas);
    }
    batas=count_char_max(fp)-z;
    preadd_parse(&parselist,str3,batas,z);
    printf("\nSimbol Akhir yang dimasukan adalah %s\n\n",str3);

    /*  ##### END OF PARSING SYMBOLS #####   */

    print_list(&parselist);
    fclose (fp);
    return 1;
}

