#include <stdio.h>

#define N 5

struct gshape{
    int type; /* 0/1/2 */
    int ID;
    union{
        struct
        {
            float radius;
            float x,y;
        }circle;
        struct
        {
            float x1,y1, x2,y2, x3,y3;
        }triangle;
        struct
        {
            float x1,y1; // upper left
            float x4,y4; // right bottom
        }rectangle;
    }gshape;
    // function pointers in struct provide contained intelligence
    void (*read_gshape)(struct gshape *gs);
    // like an object having both data and code
    void (*write_gshape)(struct gshape *gs);
};

void read_circle(struct gshape *gs){
    printf("radius? ");
    scanf("%f", &(gs->gshape.circle.radius));
    printf("X center? ");
    scanf("%f", &(gs->gshape.circle.x));
    printf("Y center? ");
    scanf("%f", &(gs->gshape.circle.y));
}

void write_circle(struct gshape *gs){
    printf("Printing circle ID = %d\n", gs->ID);
}

void read_triangle(struct gshape *gs){
    printf("Reading triangle\n");
    scanf("%f%f%f%f%f%f",
        &(gs->gshape.triangle.x1),
        &(gs->gshape.triangle.y1),
        &(gs->gshape.triangle.x2),
        &(gs->gshape.triangle.y2),
        &(gs->gshape.triangle.x3),
        &(gs->gshape.triangle.y3)
    );
}

void write_triangle(struct gshape *gs){
    printf("Triangle (%f,%f) (%f,%f) (%f,%f)\n",
        gs->gshape.triangle.x1,
        gs->gshape.triangle.y1,
        gs->gshape.triangle.x2,
        gs->gshape.triangle.y2,
        gs->gshape.triangle.x3,
        gs->gshape.triangle.y3
    );
}

void read_rectangle(struct gshape *gs){
    printf("Reading rectangle\n");
    scanf("%f%f%f%f",
        &(gs->gshape.rectangle.x1),
        &(gs->gshape.rectangle.y1),
        &(gs->gshape.rectangle.x4),
        &(gs->gshape.rectangle.y4)
    );
}

void write_rectangle(struct gshape *gs){
    printf("Rectangle (%f,%f) (%f,%f)\n",
    gs->gshape.rectangle.x1,
    gs->gshape.rectangle.y1,
    gs->gshape.rectangle.x4,
    gs->gshape.rectangle.y4
    );
}

int main(void){
    int i,type;
    struct gshape gs[N];

    printf("Inintializing the geometric shapes collection\n");
    for(i=0;i<N;i++){
        do{
            printf("Shape ID :%d\n",i);
            printf("What type of shape is it? (0 = circle 1 = triangle 2 = rectangular)");
            scanf("%d",&type);
            gs[i].type = type;
            gs[i].ID = i;
            switch(gs[i].type){
                case 0:
                    gs[i].read_gshape = &read_circle;
                    gs[i].write_gshape = &write_circle;
                    break;
                case 1:
                    gs[i].read_gshape = &read_triangle;
                    gs[i].write_gshape = &write_triangle;
                    break;
                case 2:
                    gs[i].read_gshape = &read_rectangle;
                    gs[i].write_gshape = &write_rectangle;
                    break;
                default:
                    printf("Bruh I really donno what to say rn\n");
            }
        }while((gs[i].type != 0 ) && (gs[i].type != 1) && (gs[i].type != 2));
    }
    printf("Printing all the circles from our collection\n");
    for(i=0;i<N;i++)
        if(gs[i].type == 0)
            gs[i].write_gshape(&gs[i]);
    return 1;
}
