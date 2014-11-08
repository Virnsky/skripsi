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

void add_symbol1(char symbol_name[],list *parselist)
{
	symbol_list* smb=(symbol_list*) malloc(sizeof(symbol_list));

	strcpy(smb->t.symbol, symbol_name);
	smb->t.frekuensi=1;
	smb->next=NULL;

	if(parselist->first==NULL)
    {
        parselist->first=smb;
    }else
    {
        symbol_list* last_symbol=parselist->first;
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

FILE * fp;
    fpos_t pos1;
    char str2[6];
    char jan[6];
    char arr[6][20] = {};
    char s[20];
    int i=0;
    int x,sisa,z, total;
    int k=0;
    int huf_var;
    char temp_prio1[10];
    char temp_prio2[10];
    int temp_ind1 = 0;
    int temp_ind2 = 0;
    int temp_max_fre;

int main (){
    fp=fopen("kucing.txt", "r");
    list L;
    L.first=NULL;
    list parselist;

    printf("Enter Length: ");
    scanf("%d", &huf_var);

    fseek(fp,0,SEEK_SET);
    printf("%d character left\n",count_char_left(fp));
    for(i=0;i<5;i++) fgetc(fp);
    printf("%d character left\n",count_char_left(fp));

   // symbol_list* tt=get_symbol("setiap",fp);
    //int frek=tt->t.frekuensi;

    for(i=0;i<count_char_max(fp)-(huf_var-1); i++){
        fseek(fp,i,SEEK_SET);
        fread(str2,1,huf_var,fp);
        //printf("%s\n",arr[0]);

        check_symbol(str2,&L);
        // printf ("%s\n",arr[i]);

    }

    print_list(&L);
    printf("\nTotal Karakter Dalam Berkas Adalah %d\n",count_char_max(fp));
    fseek(fp,0,SEEK_SET);
    fgetpos(fp, &pos1);
    for(z=0; z<=(count_char_max(fp)-(huf_var-1)); z++){
            for(k=0; k<=(huf_var-1); k++){
            total = z+k;
            fseek(fp,total,SEEK_SET);
            fread(str2,1,huf_var,fp);
            symbol_list* yuri=get_symbol(str2,&L);
            if(yuri==NULL)  printf("symbol tidak ada\n");
            int f=yuri->t.frekuensi;
            strcpy(s,str2);
            printf("\n nilai f : %d", f);
            if(temp_max_fre<f){
                if(count_char_left(fp)>huf_var){
                    strcpy(temp_prio1,s);
                    temp_ind1 = k+1;
                    temp_max_fre = f;
                    printf("\nsimbol : %s",temp_prio1);
                    printf("\nfrek : %d", f);

                }
            }
            fsetpos(fp,&pos1);
        }
        if (temp_ind1!=1){
            printf("\nindex : %d", temp_ind1);
            temp_max_fre=0;
            total=0;
            for(int l = 0; l < huf_var-1; l++){
                total = temp_ind1+l-1;
                fsetpos(fp, &pos1);
                fseek(fp,total,SEEK_SET);
                fread(str2,1,huf_var,fp);
                symbol_list* yuri=get_symbol(str2,&L);
                int f=yuri->t.frekuensi;
                strcpy(s,str2);
                if(temp_max_fre<f){
                    if(count_char_left(fp)>huf_var){
                        strcpy(temp_prio1,s);
                        temp_ind1 = temp_ind1+l;
                        temp_max_fre = f;
                    }
                }
            }
            sisa=temp_ind1-1;
            if(sisa>huf_var){
                temp_max_fre=0;
                printf("\n 5\n");
                for(int l=0;l<(sisa-huf_var); l++){
                    fread(str2,(l+1),huf_var,fp);
                    symbol_list* yuri=get_symbol(str2,&L);
                    int f=yuri->t.frekuensi;
                    strcpy(s,str2);
                    if(temp_max_fre<f){
                        if(count_char_left(fp)>huf_var){
                            strcpy(temp_prio2,s);
                            temp_ind2 = l+1;
                            printf("\n 6\n");
                        }
                    }
                }

                if(temp_ind2==1){
                    add_symbol(temp_prio2,&parselist);
                    printf("\ntemp_prio 2: %s",temp_prio2);
                    fread(str2,(temp_ind2+1),(temp_ind1-1),fp);
                    add_symbol(str2,&parselist);
                    printf("\nstr2 == 1 : %s", str2);
                }
                else{
                    fread(str2,1,(temp_ind2-1),fp);
                    add_symbol(str2,&parselist);
                    printf("\nstr2 != 1 : %s",str2);
                    add_symbol(temp_prio2,&parselist);
                    printf("\ntemp_prio2 != 1 : %s",temp_prio2);
                }
                z = z+temp_ind1+temp_ind2+huf_var-1;
                fsetpos(fp, &pos1);
            }
            else{
                total=temp_ind1-1;
                fsetpos(fp,&pos1);
                printf("\ntemp index yang di pakai : %d", temp_ind1);
                fread(jan,1,total,fp);
                printf("\npars 1 : %s", jan);
                printf("\npars 2 : %s", temp_prio1);
                add_symbol1(jan,&parselist);
                printf("\napa seh");
                printf("\nstr2 sisa < huff : %s", jan);
                z=z+temp_ind1+huf_var-1;
                fsetpos(fp, &pos1);
            }
        }
        else{
            printf("\n 7\n");
            add_symbol(temp_prio1,&parselist);
            printf("\n temp prio paling depan : %s",temp_prio1);
            fsetpos(fp, &pos1);
            z=z+temp_ind1-1;
        }
    }
    print_list(&parselist);
    fclose (fp);
    return 0;
}

