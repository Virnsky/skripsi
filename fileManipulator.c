#include "fileManipulator.h"

void yogaSeek(FILE* fp,int offset,char mode)
{
    int i=0;
    if(mode==YOGA_SEEK_SET) fseek(fp,0,SEEK_SET);

    for(i=0;i<offset;i++)
    {
        fgetc(fp);
    }
}
