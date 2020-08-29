#include <stdio.h>
#include <stdarg.h>

#define INT_MAX 1000000
#define INT_MIN -1000000

/*float is automatically promoted to double via ...
*because of the stack memory requirements
*/
void minmax(unsigned int n, ...){
    va_list valist;
    float minv = (float)INT_MAX, maxv = (float)INT_MIN;
    unsigned int i;

    // initialize valist for n arguments
    va_start(valist,n);

    //parse n arguments of type float from valist
    for(i=0;i<n;i++){
        double aux;
        aux = (float)va_arg(valist, double);
        if(aux < minv)
            minv = aux;
        if(aux > maxv)
            maxv = aux;
    }
    //clean valist
    va_end(valist);

    printf("Max = %.2f\nMin = %.2f\n",maxv,minv);
}

int main(void){
    printf("For args of 1.2, 3.14, 4.0, 5.0\n");
    minmax(4,1.2,3.14,4.0,5.0);
    printf("For args of 1.0, 2.0, 3.0\n");
    minmax(3,1.0,2.0,3.0);
}
