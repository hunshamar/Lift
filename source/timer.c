
#include "timer.h"
#include <stdio.h>
#include <sys/time.h>

static timer lift_timer;

static double get_wall_time(void){ //  Returns seconds and microseconds since 01.01.1970
    struct timeval time; 
    gettimeofday(&time, NULL);
    return (double)time.tv_sec + (double)time.tv_usec * .000001; 
}

void timer_start(int seconds){
    lift_timer.start_time = get_wall_time();
    lift_timer.run_time = seconds;
}

bool timer_running(void){
    double current_time = get_wall_time();
    if (lift_timer.start_time + lift_timer.run_time < current_time){  // Return zero if elapsed time has exceeded run time of timer
        return 0;
    }   
    return 1;
}
