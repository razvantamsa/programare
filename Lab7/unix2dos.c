#include <stdio.h>

int main(void)
{
    char c;
    while((c = fgetc(stdin)) != EOF)
    {
        if(c == '\n')
            putchar('\r');
        putchar(c);
    }
    return 0;
}
