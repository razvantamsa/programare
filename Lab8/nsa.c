#include <x86intrin.h>
#include <stdio.h>
#include <string.h>

#define LCS _lrotl // left circular shift
#define RCS _lrotr // right circular shift
#define u64 unsigned long long
#define R(x,y,k) (x = RCS(x,8), x+=y, x^=k, y = LCS(y,3), y^=x)
#define INV_R(x,y,k) (y^=x, y = RCS(y,3), x^=k, x-=y,x=LCS(x,8))

void Speck128ExpandKeyAndEncrypt(u64 pt[],u64 ct[],u64 K[])
{
    u64 i,B = K[1],A = K[0];
    ct[0] = pt[0]; ct[1] = pt[1];
    for(i=0;i<32;i++)
    {
        R(ct[1],ct[0],A);
        R(B,A,i);
    }
}

void Speck128Encrypt(u64 pt[],u64 ct[],u64 k[])
{
    u64 i;
    ct[0] = pt[0]; ct[1] = pt[1];
    for(i=0;i<32;i++)
    {
        R(ct[1],ct[0],k[i]);
    }
}

void Speck128Decrypt(u64 pt[],u64 ct[],u64 K[])
{
    long long i;
    for(i=31;i>=0;i--)
    {
        INV_R(ct[1],ct[0],K[i]);
    }
}

static void speck_keyexpand(u64 K[])
{
    u64 tmp[32], *p;
    memcpy(tmp,K,sizeof(tmp));
    //K[0] stays the same
    u64 i;
    for(i=0;i<(31);)
    {
        p = tmp + (1+(i%(2-1)));
        R(*p,tmp[0],i);
        ++i;
        K[i] = tmp[0];
    }
}

int main(int argc,char* argv[])
{

    if(argc != 2)
        return -1;
    FILE* bin = fopen(argv[1],"r+b");
    if(!bin)
        return -1;
    char k1[16],k2[16],*ptr;
    int i;
    fgets(k1,16,stdin);
    fgets(k2,16,stdin);

    u64 k[32];
    k[1] = strtoll(k1,&ptr,16);
    k[0] = strtoll(k2,&ptr,16);

    u64 pt[2];
    pt[1] = 0x6c61766975716520;
    pt[0] = 0x7469206564616d20;

    u64 ct[] = {0x0, 0x0};

    //Speck128Speck128ExpandKeyAndEncrypt(pt,ct,k)
    speck_keyexpand(k);
    int ok = 0;
    do{
        scanf("%i",ok);
        switch(ok){
            case 1:
                Speck128Encrypt(pt,ct,k);
            case 2:
                Speck128Decrypt(pt,ct,k);
        }
    }while(ok == 1 || ok == 2 );

    fclose(bin);
    return 0;
}
