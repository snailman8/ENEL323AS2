/**
@File main.c
@Author Ben Snalam and Kirstin Middelkoop
@Date 22/7/2010
@Brief main program
*/

#include "double_buffer.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

void main (void)
{
    int i = 0;
    for (i =0; i<20; i++)
    {
        int a;
        printf("Enter a number into the buffer:\n");
        
        scanf ("%d",&a);
        bf_wheel1_add(a);
        test_print_rbuff();
        test_print_wbuff();
        printf("read buffer average: %i\n", bf_wheel1_average());
    }
    printf("end of test program");
}