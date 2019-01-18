#ifndef _TIMER_
#define _TIMER_

#include <stdbool.h>

typedef struct timer{
    int start_time; //In ms
    int run_time;
    int running; //1 if timer is running, 0 if not
}timer;


void timer_start(int ms);

bool timer_running();



#endif