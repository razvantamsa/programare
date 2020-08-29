#include <stdio.h>
#include "libmap.h"

int pegs, disks, map[5][3];
FILE* file = fopen("hanoi.svg","w");

void handle_file(int ok)
{
    //ok for beginning and end
    if(ok)
    {
        fprintf(file,"
        <html>
        <body>

        <div class = "column"> <!-- pt toti pasii-->

            <table style = "width : 100%"><!-- pt cate un pas-->
        ");
    }
    else
    {
        fprintf(file,"
            </table>

        </div>
        </body>
        </html>
        ");
    }

}

void solve(int n,char from_peg,char to_peg,char aux_peg)
{
    if(n == 1)
    {
        move_disk(from_peg,to_peg,5,pegs,map);
        print_map(5,pegs,map);
        return;
    }
    else
    {
        solve(n-1,from_peg,aux_peg,to_peg);
        move_disk(from_peg,to_peg,5,pegs,map);
        print_map(5,pegs,map);
        solve(n-1,aux_peg,to_peg,from_peg);
    }
}

int main()
{
    handle_file(1);
    pegs = 3;
    printf("Select the number of disks 2/3/4\n");
    disks = 5;
    while(disks > 4 || disks < 2)
        scanf("%i",&disks);
    init_map(5,pegs,map,disks);
    print_map(5,pegs,map);
    solve(disks,'A','C','B');
    handle_file(0);
    return 0;
}
