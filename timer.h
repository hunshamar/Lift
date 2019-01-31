#ifndef _TIMER_H_
#define _TIMER_H_

#include <stdbool.h>

/* TODO ENDRE TIMER TIL MS */

typedef struct timer{
    double start_time; //Start time in secs and microsecs 
    double run_time; // Run time in secs and microsecs
}timer;

double get_wall_time(void); //Returns seconds and miliseconds since 01.01.1970

void timer_start(int seconds);

bool timer_running(void);


#endif


