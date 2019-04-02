
#include <stdio.h>
#include "elevator.h"
#include "buttons.h"



int main(void) {

    if (!elevator_init()){
        printf("Unable to initialize elevator hardware! \n");
        return 1;
    }

    int a = elev_get_obstruction_signal();
    int b;

    while(1){
        elevator_update_direction();
        buttons_poll();
        elevator_update_floor_read();

        if (elevator_is_on_floor()){
            elevator_execute_orders();
        }
        if (elev_get_stop_signal()){
            elevator_stop();
        } 

        b = elev_get_obstruction_signal(); 
        if (b == a){
            elevator_print_status(); //When obstruction toggles
            a = !a;
        }
    }
    return 0;
}
