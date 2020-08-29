#include <stdio.h>

int cb[8][8]; // chess board
int count_sol = 0;

void print_cb() // show solution
{
    if(count_sol)
        printf("Solution #%u\n",count_sol);
    int i,j;
    for(i=0;i<8;i++)
    {
        for(j=0;j<8;j++)
        {
            printf("%u ",cb[i][j]);
        }
        putchar('\n');
    }
    putchar('\n');
    count_sol++;
}

int check_boundaries(int x,int y) // check if it s out of chess board
{
    if(x < 0 || y < 0 || x >= 8 || y >= 8)
        return 0;
    return 1;
}

int check_attack(int x,int y) // check if it s a wrong position
{
    if(!check_boundaries(x,y)) // also include boundary control
        return 0;
    int i,j;
    // check row
    for(j=0;j<8;j++)
    {
        if(cb[x][j] == 1)
            return 0;
    }
    // check diagonals
    for(i=0;i<8;i++)
    {
        if(cb[x-i][y+i] == 1)
            return 0;
        if(cb[x-i][y-i] == 1)
            return 0;
    }
    return 1;
}

void backtrack(int x,int y)
{
    if(y == 7 && check_attack(x,y)) // we found a good formation
    {
        cb[x][y] = 1;
        print_cb();
        cb[x][y] = 0;
    }
    else
    {
        int i;
        for(i=0;i<8;i++)
        {
            if(check_attack(i,y+1))
            {
                cb[x][y] = 1;
                backtrack(i,y+1);
                cb[x][y] = 0;
            }
        }
    }
}

int main(void)
{
    print_cb();
    backtrack(0,0);
    return 0;
}
