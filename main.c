#include "elev.h"
#include <stdio.h>
#include "timer.h"
#include "orders.h"

int main() {
    // Initialize hardware jeg endret her
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    printf("Press STOP button to stop elevator and exit program.\n");

    elev_set_motor_direction(0);

    int a = 1;
    while(1){


        int b = elev_get_obstruction_signal();
        if (b == a){
            orders_print();
            a = !a;
        }

        elevator_check_buttons();

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

    return 0;
}
*/
