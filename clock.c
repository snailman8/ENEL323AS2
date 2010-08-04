  /**
@File clock.c 
@Author Ben Snalam and Kirstin Middelkoop
@Date 6/7/2010
@Brief timer module used in the ENEL323 anti-collision sofware. This code is broadly based off RTC.c from ATMEL
*/
  
#include <clock.h>

  void clock_init()
  {
      Delay(1000);                          // allows xtal to warm up
      __disable_interupt;                   // globaly  disables interrupt
      ASSR = BIT(AS2);                      //enables timer2
      
      TCNT2 = 0;                            //restarts counter
      while((ASSR & 0x01) | (ASSR & 0x04));       // wait for TCN2UB and TCR2UB to be cleared
          
      CCR2A |= BIT(1<<CS20);               //no prescaler, overflow every 7.8125ms
      TIMSK2 = BIT(TOIE2) | BIT(OCIE2A);    //I 'think' this is right,enables
                                            //the output compare and overflow interrupt
                                            
      __enable_interrupt();
  }
  
  void clock_show()
  {
      
  }