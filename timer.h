#ifndef _TIMER_
#define _TIMER_

#include <stdbool.h>

typedef struct timer{
    int start_time; 
    int run_time;
    int running; //1 if timer is running, 0 if not
}timer;


void timer_start(int seconds);

bool timer_running();



#endif


