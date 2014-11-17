#include <stdio.h>
#include <string.h>
#include <malloc.h>

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
    int temp_max_fre = 0;
    char strcpy(str1,"");
    char strcpy(str2,"");
    char strcpy(str3,"");
    int total=0;
};

void compare_sysmbol(char str[],int index_seek, int limit, char temp_symbol [],int index_symbol, int frek_symbol){
    var_reset();
    while(k<limit){
        total = index_seek+k;

        fseek(fp,total,SEEK_SET);
        fread(str,1,huf_var,fp);
        symbol_list* yuri=get_symbol(str,&L);

        if(yuri==NULL) printf("\nYuri = Null"); return(1);

        int f=yuri->t.frekuensi;
        strcpy(s,str);

        if(frek_symbol<f){
            if(count_char_left(fp)>huf_var){
                strcpy(temp_symbol,s);
                index_symbol = k+1;
                frek_symbol = f;
            }
        }
        k++
    }
};
void preadd_parse(char str[],int limited){
    var_reset()
    fsetpos(fp, &pos1);
    fread(str1,1,(limited-1),fp);
    add_symbol(str,&parselist);
};

FILE * fp;
    fpos_t pos1;
    char str2[10], str1[10], str3[10], char s[10];
    int i=0, z=0, k=0;
    int x,sisa,total,limit, huf_var;
    char temp_prio1[5], temp_prio2[5];
    int temp_ind1 = 0, temp_ind2 = 0, temp_max_fre;

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

    print_list(&L);
    printf("\nTotal Karakter Dalam Berkas Adalah %d\n",count_char_max(fp));

    for(z; z<=(count_char_max(fp)-(huf_var-1)); z){
        fgetpos(fp, &pos1);
        compare_sysmbol(str1,z,huf_var,temp_ind1,temp_prio1,temp_max_fre);
        sisa=temp_ind1-1;

        if(sisa>huf_var){
            batas=huf_var-sisa;
            compare_sysmbol(str2,z,batas,temp_ind2,temp_prio2,temp_max_fre);

            if(temp_ind2==temp_ind1){
                preadd_parse(str1,temp_ind1);
                add_symbol(temp_prio2,&parselist);
                z=z+temp_ind2+huf_var-1;
            }
            else{
                preadd_parse(str1,temp_ind2);
                add_symbol(temp_prio2,&parselist);
                z=z+temp_ind2+temp_ind1+huf_var-1;
            }
            else{
                preadd_parse(str3,temp_ind1);
                z=z+temp_ind1+huf_var-1;
            }
        }
        else{
            printf("\n7\n");
            add_symbol(temp_prio1,&parselist);
            printf("\ntemp prio paling depan : %s",temp_prio1);
            printf("\nind1 : %d",temp_ind1);
            z=z+temp_ind1+huf_var-1;
            printf("\nIndex seek : %d", z);
        }
    }
    print_list(&parselist);
    fclose (fp);
    return 1;
}

