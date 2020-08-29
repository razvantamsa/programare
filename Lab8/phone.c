#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct entry
{
    char repair[50];
    long int IMEI;
    int price,investment,profit,totalpr,totalinf,blacklisted;
}e[100];

void add_entry()
{
    FILE* db = fopen("binarydb.bdb","ab+");
    printf("Add Entry\n");
    struct entry aux;
    //reading
    printf("Repair type?\n");
    scanf("%s",aux.repair);
    printf("IMEI?\n");
    scanf("%lu",&aux.IMEI);
    printf("Price?\n");
    scanf("%u",&aux.price);
    printf("Investment?\n");
    scanf("%u",&aux.investment);
    aux.profit = aux.price - aux.investment;
    aux.totalpr = 0;
    aux.totalinf = 0;
    aux.blacklisted = 0;
    //check for TOTAL PROFIT TOTAL INFLUX
    fwrite(&aux,sizeof(aux),1,db);
    fclose(db);
}

void delete_entry()
{
    printf("Delete Entry\n");
    FILE* db = fopen("binarydb.bdb","r+b");
    int count = 0,search,pos;
    struct entry aux;
    printf("What position?\n");
    scanf("%u",&search);
    while(!feof(db))
    {
        fread(&aux,sizeof(struct entry),1,db);
        if(count == search)
        {
            while(!feof(db))
            {
                pos = ftell(db);
                fread(&aux,sizeof(struct entry),1,db);
                fseek(db,pos-sizeof(struct entry),SEEK_SET);
                fwrite(&aux,sizeof(struct entry),1,db);
            }
        }
        count++;
    }
    fclose(db);
}

void display_for_imei()
{
    FILE* db = fopen("binarydb.bdb","ab+");
    int count = 0;
    printf("Display for IMEI\n");
    printf("What IMEI?\n");
    long unsigned int imei;
    scanf("%lu",&imei);
    struct entry aux;
    while(!feof(db))
    {
        fread(&aux,sizeof(struct entry),1,db);
        if((!feof(db) && imei == aux.IMEI) && aux.blacklisted == 0){
            printf("%u.%s %u %u\n",count,aux.repair,aux.price,aux.investment);
            if(count == 0)
                printf("%u %u\n",aux.totalpr,aux.totalinf);
        }
        count++;
    }
    fclose(db);
}

void toggle()
{
    FILE* db = fopen("binarydb.bdb","r+b");
    printf("Mark/Unmark\n");
    int count = 0,search,pos;
    struct entry aux;
    printf("What position?\n");
    scanf("%u",&search);
    while(!feof(db))
    {
        pos = ftell(db);
        fread(&aux,sizeof(struct entry),1,db);
        if(count == search)
        {
            fseek(db,pos,SEEK_SET);
            aux.blacklisted = ~(aux.blacklisted)&0x1;
            fwrite(&aux,sizeof(struct entry),1,db);
            break;
        }
        count++;
    }
    fclose(db);
}

void update()
{
    if(sizeof(e[0]) == 0)
        return;
    FILE* db = fopen("binarydb.bdb","r+b");
    int totalprofit = 0,totalinflux = 0,first_position;
    struct entry first,aux;
    first_position = ftell(db);
    fread(&first,sizeof(struct entry),1,db);
    while(!feof(db))
    {
        fread(&aux,sizeof(struct entry),1,db);
        totalprofit += aux.profit;
        totalinflux += aux.price;
    }
    first.totalpr = first.profit + totalprofit;
    first.totalinf = first.price + totalinflux;
    fseek(db,first_position,SEEK_SET);
    fwrite(&first,sizeof(struct entry),1,db);
}

int main(void)
{
    int ok = 0;
    printf("1. Add Entry\n"
    "2. Delete Entry\n"
    "3. Display All Entries of an IMEI\n"
    "4. Mark/Unmark Blacklisted\n"
    "0. Exit\n\n");
    scanf("%u",&ok);
    switch(ok)
    {
        case 1:
            add_entry();
            break;
        case 2:
            delete_entry();
            break;
        case 3:
            display_for_imei();
            break;
        case 4:
            toggle();
            break;
        default:
            if(ok)
                printf("Unknown case... %u\n",ok);
    }
    update();
    return 0;
}
