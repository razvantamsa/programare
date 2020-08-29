#include <stdio.h>
#include <stdlib.h>

void unix2dos(char *s)
{
    FILE* mod = fopen(s,"r+");
    char c;
    while( (c=fgetc(mod)) != EOF)
    {
        if(c == '\n')
        {
            //fseek(mod,0,SEEK_CUR);
            fputc('\r',mod);
        }
    }
    fclose(mod);
}

int main(int argc,char *argv[])
{
    int i = 1;
    while(i < argc)
    {
        unix2dos(argv[i]);
        //printf("Avem fisierul %s\n",argv[i]);
        i++;
    }
    return 0;
}
