#ifndef _TIMER_H_
#define _TIMER_H_

#include <stdbool.h>

/* TODO ENDRE TIMER TIL MS */

typedef struct timer{
    int start_time; 
    int run_time;
}timer;


void timer_start(int seconds);

bool timer_running();


#endif


