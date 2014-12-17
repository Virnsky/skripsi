#ifndef FILEMANIPULATOR_H_INCLUDED
#define FILEMANIPULATOR_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define YOGA_SEEK_SET   0
#define YOGA_SEEK_CUR   1

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

void yogaSeek(FILE* fp,int offset,char mode)
{
    int i=0;
    if(mode==YOGA_SEEK_SET) fseek(fp,0,SEEK_SET);
    for(i=0;i<offset;i++)
    {
        fgetc(fp);
    }
}


#endif // FILEMANIPULATOR_H_INCLUDED
