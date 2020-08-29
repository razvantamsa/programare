#include <stdio.h>
#include <ctype.h>

unsigned int n,m; //size of maze
unsigned int stop = 0;
unsigned int maze[10][10];
#include <stdio.h>
#include <ctype.h>

unsigned int n,m; // size of maze
unsigned int maze[10][10];

void clean_up() // clean up path that leads nowhere
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            if(maze[i][j] == '-')
                maze[i][j] = '.';
        }
    }
}

int check(int x,int y,int x2,int y2) // see if its end or if its atleast available
{
    /*if(x == x1 && y == y1)
        return 3; // we are back to the beginning
    */
    if(maze[x][y] == '.')
        return 1; // avaliable position
    return 0; // none of the above :(
}

void read_maze(FILE* in) // read maze
{
    int c,i = 0,j = 0;
    while( (c = fgetc(in)) != EOF )
    {
        if(!isspace(c)) // skip spaces because we read characters
        {
            maze[i][j] = c;
            j++;
            if(j == m)
            {
                j = 0;
                i++;
            }
        }
    }
}

void print_maze() // print maze
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
            printf("%c ",maze[i][j]);
        putchar('\n');
    }
}

void margin(int *x,int *y,int ok) // find start and end
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            if(maze[i][j] == '.')
            {
                if(i == 0 || i == n-1 || j == 0 || j == m-1)
                {
                    if(ok == 1) // condition to control the purpose
                    {
                        *x = i;
                        *y = j;
                        return;
                    }
                    else
                        ok++;
                }
            }
        }
    }
}

int backtrack(int x,int y,int x2,int y2,int path) // stop when we are back to the start
{
    if(x == x2 && y == y2)
    {
        maze[x][y] = 'x';
        return 1; // found a path!
    }
    else
    {
        if(check(x-1,y,x2,y2)) // go down
        {
            maze[x][y] = '-';
            path = (backtrack(x-1,y,x2,y2,0)|path);
        }
        if(check(x,y+1,x2,y2)) // go right
        {
            maze[x][y] = '-';
            path = (backtrack(x,y+1,x2,y2,0)|path);
        }
        if(check(x+1,y,x2,y2)) // go up
        {
            maze[x][y] = '-';
            path = (backtrack(x+1,y,x2,y2,0)|path);
        }
        if(check(x,y-1,x2,y2)) // go right
        {
            maze[x][y] = '-';
            path = (backtrack(x,y-1,x2,y2,0)|path);
        }
        if(path == 1) // if we are on the right path we pass down the information
        {
            maze[x][y] = 'x';
            return path;
        }
    }
    return 0;
}

void brain(FILE* in) // problem solving
{
    fscanf(in,"%u%u",&n,&m);
    read_maze(in);
    print_maze();
    int x1,y1,x2,y2;
    margin(&x1,&y1,1); // start
    margin(&x2,&y2,0); // finish
    printf("start = (%u,%u)\nend = (%u,%u)\n",x1,y1,x2,y2);
    backtrack(x1,y1,x2,y2,0);
    clean_up();
    print_maze(); // now all of the possible paths will have x on them
}
unsigned int win = 0; // to see if we return from a win
int main(void)
{
    FILE* in = fopen("text.in","r");
    if(!in) // if there is no such file we stop
        return 0;
    brain(in);
    return 0;
}

void read_maze(FILE* in)
{
    int c,i = 0,j = 0;
    while( (c = fgetc(in)) != EOF )
    {
        if(!isspace(c))
        {
            maze[i][j] = c;
            j++;
            if(j == m)
            {
                j = 0;
                i++;
            }
        }
    }
}

void print_maze()
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
            printf("%c ",maze[i][j]);
        putchar('\n');
    }
}

void find_start(int *x1,int *y1)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            if(maze[i][j] == '.')
            {
                if(i == 0 || i == n-1 || j == 0 || j == m-1)
                {
                    *x1 = i;
                    *y1 = j;
                    return;
                }
            }
        }
    }
}

void backtrack(int x,int y,int x1,int y1)
{
    //check for end
    if(x == 0 || x == n-1 || y == 0 || y == m-1){
        if(x != x1 || y != y1){
            maze[x][y] = '-';
            stop = 1;
        }
    }
    //continue
    if(maze[x-1][y] == '.')
    {
        maze[x][y] = '-';
        backtrack(x-1,y,x1,y1);
        if(stop == 1)
            return;
        maze[x][y] = 'x';
    }
    if(maze[x+1][y] == '.')
    {
        maze[x][y] = '-';
        backtrack(x+1,y,x1,y1);
        if(stop == 1)
            return;
        maze[x][y] = 'x';
    }
    if(maze[x][y+1] == '.')
    {
        maze[x][y] = '-';
        backtrack(x,y+1,x1,y1);
        if(stop == 1)
            return;
        maze[x][y] = 'x';
    }
    if(maze[x][y-1] == '.')
    {
        maze[x][y] = '-';
        backtrack(x,y-1,x1,y1);
        if(stop == 1)
            return;
        maze[x][y] = 'x';
    }
    if(stop == 1)
        return;
    maze[x][y] = 'x';
}

int main()
{
    FILE* in = fopen("text.in","r");
    if(!in)
    {
        printf("No such file or directory\n");
        return 0;
    }
    fscanf(in,"%u%u",&n,&m);
    read_maze(in);
    print_maze();
    int x1 = 0,y1 = 0; //coordinates of starting point
    find_start(&x1,&y1);
    printf("Starting point coord: (%u,%u)\n",x1,y1);
    backtrack(x1,y1,x1,y1);
    print_maze();
    return 0;
}
