#ifndef FILEMANIPULATOR_H_INCLUDED
#define FILEMANIPULATOR_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define YOGA_SEEK_SET   0
#define YOGA_SEEK_CUR   1

void yogaSeek(FILE* fp,int offset,char mode);

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
