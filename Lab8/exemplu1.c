#include <stdio.h>

int main(void)
{
    FILE* fp;
    fp = fopen("binary.bin","rb");
    if(fp == NULL)
    {
        perror("fopen()");
        return -1;
    }
    return 0;
}
