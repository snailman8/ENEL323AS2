    /**
    @File double_buffer.c 
    @Author Ben Snalam and Kirstin Middelkoop
    @Date 6/7/2010
    @Brief circular double buffers used in the ENEL323 anti-collision sofware.
    */

#include "double_buffer.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>


#define WHEEL_BUFFER_SIZE 10

static uint16_t bf_wheel1_w[WHEEL_BUFFER_SIZE];  //the array new data is written to.
static uint16_t bf_wheel1_r[WHEEL_BUFFER_SIZE];  //the array data is calculated from
static uint8_t bf_wheel1_index = 0;


void bf_wheel1_add(uint16_t value)
{
    uint8_t bf_i = 0;
    printf("break1 %i\n", value);
    bf_wheel1_w[bf_wheel1_index] = value;
    printf("break2\n");
    if(bf_wheel1_index < WHEEL_BUFFER_SIZE - 1)
    {
        bf_wheel1_index++;
        printf("break3\n");
    }
    else
    {
        bf_wheel1_index = 0;
        for(bf_i = 0; bf_i < WHEEL_BUFFER_SIZE; bf_i++)
        {
            bf_wheel1_r[bf_i] = bf_wheel1_w[bf_i];
        }
    }
}


void test_print_rbuff()
{
    uint8_t bf_i;
    printf("read buffer: [");
    for(bf_i = 0; bf_i < WHEEL_BUFFER_SIZE; bf_i++)
    {
        printf("%i ", bf_wheel1_r[bf_i]);
    }
    printf("]\n");
}


void test_print_wbuff()
{
    uint8_t bf_i;
    printf("write buffer: [");
    for(bf_i = 0; bf_i < WHEEL_BUFFER_SIZE; bf_i++)
    {
       printf("%i ", bf_wheel1_w[bf_i]);
    }
    printf("]\n");
}


uint16_t bf_wheel1_average()
{
    uint8_t bf_i;
    uint16_t bf_average = 0;
    for(bf_i = 0; bf_i < WHEEL_BUFFER_SIZE; bf_i++)
    {
        bf_average += bf_wheel1_r[bf_i];
    }
    bf_average = bf_average/WHEEL_BUFFER_SIZE;
    return bf_average;
}
