#include <stdio.h>
#include <unistd.h>

#define DURATION 5
#define RATE 8000
#define SIZE 8
#define CHANNELS 1

unsigned char buf[DURATION*RATE*SIZE*CHANNELS/8];

int main(int argc,char *argv[])
{
    FILE* soundcard;
    int n,filenum;

    if(argc == 2)
        soundcard = fopen(argv[1],"r+b");
    else
        soundcard = fopen("dev/dsp","r+b");
    if(soundcard == NULL)
    {
        perror("Can not talk to soundcard :X..");
        return -1;
    }
    filenum = fileno(soundcard);
    printf("Recording for %d seconds (mic): ",DURATION);
    n = read(filenum,buf,sizeof(buf));
    if(n!= sizeof(buf))
        perror("wrong size");
    printf("You said: \n");
    n = write(filenum,buf,sizeof(buf));

    if(n != sizeof(buf))
        perror("wrong size");

    fclose(soundcard);

    return 0;
}
