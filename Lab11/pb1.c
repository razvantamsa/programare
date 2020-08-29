#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char *min_list = NULL;
void read_matrix(FILE* in,int n,int m[n][n])
{
    int i,j;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            fscanf(in,"%u",&m[i][j]);
}
void print_matrix(int n,int m[n][n])
{
    int i,j;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(m[i][j] > 0)
                printf("%u ",m[i][j]);
            else
                printf("--- ");
        }
        putchar('\n');
    }
}
void create_starting_list(int *st,int *fin,int n)
{
    *st = rand()%n;
    //get 2 different values
    *fin = rand()%n;
    while(*st == *fin)
    {
        *fin = rand()%n;
    }

    //make first path
    char* path = NULL;
    path = (char*) realloc(path,sizeof(char)*2);
    path[0] = *st + '0';
    path[1] = '\0';
    int i,j,k = 1;
    for(i=0;i<n;i++)
    {
        if(i!=*st && i!=*fin)
        {
            printf("%s\n",path);
            path = (char*) realloc(path,sizeof(char)*(k+1));
            path[k] = i;
            path[k+1] = '\0';
            k++;
        }
    }
    path[k] = *fin + '0';
    path[k+1] = '\0';
    min_list = path;

}

int main()
{
    FILE* in = fopen("text.in","r");
    if(!in)
    {
        printf("No such file or directory...\n");
        return 0;
    }

    srand(time(NULL));
    int n;
    fscanf(in,"%u",&n);
    int m[n][n];
    read_matrix(in,n,m);
    print_matrix(n,m);
    int start,finish;
    create_starting_list(&start,&finish,n);
    printf("%s\n",min_list);


    return 0;
}
