
#include <stdio.h>

#include "timer.h"
#include "elevator.h"
#include "buttons.h"


int main(void) {

    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    elevator_init();

    while(1){
        elevator_update_direction();
        buttons_poll();
        elevator_update_floor_read();

        if (elevator_is_on_floor()){
            elevator_execute_order();
        }
        if (elev_get_stop_signal()){
            elevator_stop();
        } 
        if (elev_get_obstruction_signal_toggle()){
            elevator_print_status();
        }
    }
    return 0;
}
