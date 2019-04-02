/**
 * @file
 * @brief This library includes the functions for the elevator timer
 * A static global timer variable is manipulated with the functions in this library
 */

#ifndef _TIMER_H_
#define _TIMER_H_

#include <stdbool.h>

/**
  * @brief struct for the timer 
  */
typedef struct timer{
    double start_time; // @brief Start time in secs and microsecs 
    double run_time; // @brief Run time in secs and microsecs
}timer;


/**
  * @brief Starts the timer. The function updates the start_time of the timer to the current 
  * time and sets the run_time to the input paramtet
  *
  * @param[in] seconds Number of seconds before the timer runs out  
  */
void timer_start(int seconds);


/**
  * @brief Check if the timer is running, or has timed out
  * @return true if timer is running
  * ,false if timer is finished
  */
bool timer_running(void);


#endif


