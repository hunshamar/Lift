
#include <stdio.h>
#include "timer.h"
#include "orders.h"
#include "final_state_machine.h"
#include "buttons.h"



int main() {
    // Initialize hardware jeg endret her

    printf("Press STOP button to stop elevator and exit program.\n");

    orders_append(1,-1);
    orders_append(3,-1);
    orders_print();

    /*

    FSM_init();
    
    while(1){

        if(elev_get_stop_signal()){
            elev_set_motor_direction(0);
            break;
        }

        if (FSM_is_new_floor()){
            print_orders();
            FSM_execute_order();
            printf("\n\nexecuted\n\n");
        }

        FSM_update_direction();

        buttons_poll();

        print_orders();
    }

    return 0;
}

/*
    while (1) {
        // Change direction when we reach top/bottom floor
        if (elev_get_floor_sensor_signal() == N_FLOORS - 1) {
            elev_set_motor_direction(DIRN_DOWN);
        } else if (elev_get_floor_sensor_signal() == 0) {
            elev_set_motor_direction(DIRN_UP);
        }

        timer_start(1);
        while (timer_running()){
            printf("1\n");
        }
        timer_start(1);
        while (timer_running()){

            printf("0\n");
        }

        // Stop elevator and exit program if the stop button is pressed
        if (elev_get_stop_signal()) {
            elev_set_motor_direction(DIRN_STOP);
            break;
        }
    }
    */

    return 0;
}

