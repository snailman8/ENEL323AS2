/**
@File main.c
@Author Ben Snalam and Kirstin Middelkoop
@Date 22/7/2010
@Brief test program for double_buffer
*/

#include "double_buffer.h"
#include <config.h>
#include <target.g>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

void main (void)
{
    uint8_t i = 0;
    for (i =0; i<=20; i++)
    {
        uint8_t a;
        printf("Enter a number into the buffer:\n");
        
        scanf ("%d",&a);
        bf_wheel1_add(a);
        test_print_rbuff();
        test_print_wbuff();
        printf("read buffer average: %i\n", bf_wheel1_average());
    }
    printf("end of test program\n");
}