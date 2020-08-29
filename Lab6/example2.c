#include <stdio.h>
#include <stdarg.h>

/*float is automatically promoted to double via ...
*because of the stack memory requirements
*/
double arithmetic_mean(unsigned int n, ...){
    va_list valist;
    float sum = 0;
    unsigned int i;

    // initialize valist for n arguments
    va_start(valist,n);

    //parse n arguments of type float from valist
    for(i=0;i<n;i++)
        sum += va_arg(valist, double);

    //clean valist
    va_end(valist);

    return sum/n;
}

int main(void){
    printf("Average of 1.2, 3.14, 4, 5 = %f\n",
        arithmetic_mean(4,1.2,3.14,4.0,5.0)
    );
    printf("Average of 1, 2, 3 = %f\n",
        arithmetic_mean(3,1.0,2.0,3.0)
    );
}
