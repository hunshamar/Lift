
#include <stdio.h>
#include "timer.h"
#include "orders.h"
#include "elevator.h"
#include "buttons.h"



/*
    Improvements to do:

    -fix timer to ms                                                     [x]
    -fix curcly braces in code                                           [x]
    -More and better comments, remove comments that are not useful       [ ]  
    -header include guards                                               [x]
    -add error handling ect. for functions, i.e. fault tolerance         [ ]
    -Perhaps improve update_direction() function                         [ ]
    -change all functions that takes no arguments to: void foo(void) ?   [x]

    about commenting:

        comments about how to use function in header file
        comment about how function work in source file


*/

int main(void) {

    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    while(1){
        elevator_update_direction();
        buttons_poll();

        if (elevator_is_on_floor()){
            
            if (elev_get_floor_sensor_signal() < 0){
                printf("DET GÅR IKKE!");
            }

            elev_set_floor_indicator(elev_get_floor_sensor_signal());
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
