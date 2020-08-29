#include <stdio.h>

void init_map(int n1,int n2,int map[n1][n2],int d)
{
    int i,j;
    j = 0;
    for(i = n1-d;i < n1; i++)
        map[i][j] = i - n1 + d + 1;
}

void print_map(int n1,int n2,int map[n1][n2])
{
    putchar('\n');
    int i,j;
    for(i=0;i<n1;i++)
    {
        for(j=0;j<n2;j++)
            {
                if(map[i][j] == 0)
                    printf("|  ");
                else
                    printf("%u  ",map[i][j]);
            }
            putchar('\n');
    }
    printf("-------------\n");
}

void move_disk(char from_peg,char to_peg,int n1,int n2,int map[n1][n2])
{
    int col1 = from_peg - 'A';
    int col2 = to_peg - 'A';
    int depth = 0;
    int val;
    while(map[depth][col1] == 0 && depth < n1)
        depth++;
    val = map[depth][col1];
    map[depth][col1] = 0;
    depth = 0;
    while(map[depth][col2] == 0 && depth < n1)
        depth++;
    map[depth-1][col2] = val;
}
