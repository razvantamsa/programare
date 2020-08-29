#include <stdio.h>
#include <math.h>

struct gshape{
    int type; /* 0/1/2 */
    int ID;
    union{
        struct
        {
            float radius;
        }circle;
        struct
        {
            float a,b,c;
        }triangle;
        struct
        {
            float w,h;
        }rectangle;
    }gshape;
    // function pointers in struct provide contained intelligence
    void (*read_gshape)(struct gshape *gs);
    // like an object having both data and code
    void (*area_gshape)(struct gshape *gs);
};

void read_circle(struct gshape *gs){
    printf("Circle #%u radius length\n",gs->ID);
    scanf("%f", &(gs->gshape.circle.radius));
}

void area_circle(struct gshape *gs){
    //radius
    float r;
    r = gs->gshape.circle.radius;
    printf("Area #%u = %.3f\n",gs->ID,3.14*r*r);
}

void read_triangle(struct gshape *gs){
    printf("Triangle #%u sides length\n",gs->ID);
    scanf("%f%f%f",
        &(gs->gshape.triangle.a),
        &(gs->gshape.triangle.b),
        &(gs->gshape.triangle.c)
    );
}

void area_triangle(struct gshape *gs){
    //sides
    float a,b,c,s;
    a = gs->gshape.triangle.a;
    b = gs->gshape.triangle.b;
    c = gs->gshape.triangle.c;
    s = (a+b+c)/2;
    printf("Area #%u = %.3f\n",gs->ID,sqrt(s*(s-a)*(s-b)*(s-c)));
}

void read_rectangle(struct gshape *gs){
    printf("Rectangle #%u sides length\n",gs->ID);
    scanf("%f%f",
        &(gs->gshape.rectangle.w),
        &(gs->gshape.rectangle.h)
    );
}

void area_rectangle(struct gshape *gs){
    //width,height
    float w,h;
    w = gs->gshape.rectangle.w;
    h = gs->gshape.rectangle.h;
    printf("Area #%u = %.3f\n",gs->ID,w*h);
}

int main(void){
    int i,type,N;
    printf("How many shapes do we have? ");
    scanf("%u",&N);
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
                    gs[i].area_gshape = &area_circle;
                    break;
                case 1:
                    gs[i].read_gshape = &read_triangle;
                    gs[i].area_gshape = &area_triangle;
                    break;
                case 2:
                    gs[i].read_gshape = &read_rectangle;
                    gs[i].area_gshape = &area_rectangle;
                    break;
                default:
                    printf("Wrong shape!!!!!\n");
            }
        }while((gs[i].type != 0 ) && (gs[i].type != 1) && (gs[i].type != 2));
    }
    printf("Reading all the rectangles from our collection\n");
    for(i=0;i<N;i++){
        if(gs[i].type == 2){
            gs[i].read_gshape(&gs[i]);
        }
    }
    printf("Printing all the rectangles from our collection\n");
    for(i=0;i<N;i++){
        if(gs[i].type == 2){
            gs[i].area_gshape(&gs[i]);
        }
    }
    return 1;
}
