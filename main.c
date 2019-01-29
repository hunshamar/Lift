
#include <stdio.h>
#include "timer.h"
#include "orders.h"
#include "final_state_machine.h"
#include "buttons.h"



int main() {
    // Initialize hardware jeg endret her
        if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    printf("Press STOP button to stop elevator and exit program.\n");

    FSM_init();


    
    while(1){


        
        if (FSM_is_on_floor()){
            FSM_execute_order();
        }

        FSM_update_direction();
        buttons_poll();
        print_orders();

        if (elev_get_stop_signal()){
            FSM_stop();
        } 
    }

    return 0;
}

/*
int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    printf("Press STOP button to stop elevator and exit program.\n");

    elev_set_motor_direction(DIRN_UP);

    while (1) {
        // Change direction when we reach top/bottom floor
        if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
            elev_set_motor_direction(DIRN_DOWN);
        } else if (elev_get_floor_sensor_signal() == 0) {
            elev_set_motor_direction(DIRN_UP);
        }

        // Stop elevator and exit program if the stop button is pressed
        if (elev_get_stop_signal()) {
            elev_set_motor_direction(DIRN_STOP);
            break;
        }
    }

    return 0;
}*/