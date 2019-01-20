
#include "timer.h"
#include <time.h>
#include <stdio.h>

static timer lift_timer;


void timer_start(int seconds){
    lift_timer.running = 1;
    lift_timer.start_time = time(NULL); //Give seconds in time since 01.01.1970
    lift_timer.run_time = seconds;
}

bool timer_running(){
    int current_time = time(NULL);

    if (lift_timer.start_time + lift_timer.run_time <= current_time){
        lift_timer.running = 0;
    }   
    return lift_timer.running;
}
