
#include "timer.h"
#include <time.h>

static timer t;


void timer_start(int ms){
    t.running = 1;
    t.start_time = clock()*(CLOCKS_PER_SEC/1000);
    t.run_time = ms;
}

bool timer_running(){
    int current_time_ms = clock()*(CLOCKS_PER_SEC/1000);

    if (t.start_time + t.run_time < current_time_ms){
        t.running = 0;
    }
    
    return t.running;
}
