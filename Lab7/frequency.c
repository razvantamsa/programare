#include <stdio.h>
#include <ctype.h>

int frq[128];

int main(void)
{
    char c;

    while( (c = fgetc(stdin) ) != EOF){
        c = tolower(c);
        frq[(int)c]++;
    }

    int i;
    for(i=0;i<128;i++)
        if(isalpha((char)i) && (char)i == tolower((char)i))
            printf("%c -> %u\n",(char)i,frq[i]);

    return 0;
}
