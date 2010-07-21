    /**
    @File double_buffer.c 
    @Author Ben Snalam and Kirstin Middelkoop
    @Date 6/7/2010
    @Brief cirular double buffers used in the ENEL323 anti-collision sofware.
    */

#include "double_buffer.h"


#define WHEEL_BUFFER_SIZE 10

static uint16_t bf_wheel1_w[WHEEL_BUFFER_SIZE];  //the array new data is written to.
static uint16_t bf_wheel1_r[WHEEL_BUFFER_SIZE];  //the array data is calculated from
static uint8_t bf_wheel1_index = 0;


void bf_wheel1_add(uint16_t value)
{
    bf_wheel1_w[bf_wheel1_index] = value;
    
    if(bf_wheel1_index < WHEEL_BUFFER_SIZE - 1)
    {
        bf_wheel1_index++;
        
    }
    else
    {
        bf_wheel1_index = 0;
        bf_wheel1_r = bf_wheel1_w; //can I do this, or do I need a loop?
    }
}

void test_print_rbuff()
{
    uint8_t bf_i;
    printf("read buffer: [
    for(bf_i = 0; bf_i < WHEEL_BUFFER_SIZE; bf_i++)
    {
        fprint("%i ", bf_wheel1_r[bf_i]);
    }
    printf("]\n");
}

void test_print_rbuff()
{
    uint8_t bf_i;
    printf("write buffer: [
    for(bf_i = 0; bf_i < WHEEL_BUFFER_SIZE; bf_i++)
    {
        fprint("%i ", bf_wheel1_w[bf_i]);
    }
    printf("]\n");
}

uint16_t bf_wheel1_average(void)
{
    uint8_t bf_i;
    double average = 0;
    for(bf_i = 0; bf_i < WHEEL_BUFFER_SIZE; i++)
    {
        average += bf_wheel1_r[i];
    }
    return average;
}