/**
@File main.c
@Author Ben Snalam and Kirstin Middelkoop
@Date 22/7/2010
@Brief test program for RTOS
*/


#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "clock.h"
#include "double_buffer.h"
void main (void)
{
    clock_init;
    
    while(1)
    {
        clock_show();
    }
}   