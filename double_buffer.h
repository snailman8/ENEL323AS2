    /**
@File double_buffer Datatype .h file
@Author Ben Snalam and Kirstin Middelkoop
@Date 6/7/2010
@Brief cirular double buffer used in the ENEL323 anti-collision sofware.
 
 methods provided by double_buffer:
*/
    
#ifndef DOUBLE_BUFFER_H
#define DOUBLE_BUFFER_H
#include <stdint.h>

#include <stdlib.h>

/** adds a value to the buffer, copys write buffer into read
    buffer if required
    @param value value to be read into the buffer
*/
void bf_wheel1_add(uint16_t value);

/**
prints the contents of the read buffer to terminal
*/
void test_print_rbuff(void);

/**
prints the contents of the write buffer to terminal
*/
void test_print_wbuff(void);


/** gives the 'speed' of wheel_1
    @returns the average length from the wheel one read buffer
*/
uint16_t bf_wheel1_average(void);

#endif
