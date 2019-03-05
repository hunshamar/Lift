#ifndef _TIMER_H_
#define _TIMER_H_

#include <stdbool.h>

typedef struct timer{
    double start_time; //Start time in secs and microsecs 
    double run_time; // Run time in secs and microsecs
}timer;



/**
  Starts the timer. 
*/
void timer_start(int seconds);



/**
  Returns 1 if timer is running
  Returns 0 if timer is finished
*/
bool timer_running(void);


#endif


