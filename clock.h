  /**
  @File clock.h
  @Author Ben Snalam and Kirstin Middelkoop
  @Date 6/7/2010
  @Brief timer module used in the ENEL323 anti-collision sofware. This code is broadly based off RTC.c from ATMEL
  */
  
  #ifndef CLOCK_H
  #define CLOCK_H
  
  /**
  Initialises clock
  */
  void clock_init(void);
  
  /**
  displays current clocktime to LCD
  */
  void clock_show(void);
   
  /**
  waits for the end of the clock period
  */
  void clock_wait();
  
  #endif /* CLOCK_H */