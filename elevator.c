#include "elevator.h"
#include "orders.h"

//Static global variables, only accessible in this source file
static int current_floor;
static int current_direction;

void elevator_init(){
    while(elev_get_floor_sensor_signal() == -1){   
        elev_set_motor_direction(-1);
    }
    elev_set_motor_direction(0);
    buttons_deluminate_all();
    current_floor = elev_get_floor_sensor_signal();
    current_direction = 0;
}

void elevator_execute_order(){
    current_floor = elev_get_floor_sensor_signal();
    elev_set_floor_indicator(current_floor);
    if (order_is_executable_on_floor(current_floor, current_direction)){
        orders_remove(current_floor);            
        elev_set_motor_direction(0);
        timer_start(3);
        elev_set_door_open_lamp(1);
        buttons_deluminate(current_floor);
    }    
}

int elevator_find_direction(int floor, dir_t current_direction) {
    if (orders_is_empty()) {
        return 0;
    }
    order_t *ptr = orders_get_head();
    while (ptr != NULL){   
        if (current_direction == 0){
            return -(floor > ptr->floor) + (floor < ptr->floor);
        }
        if (floor*current_direction < ptr->floor*current_direction){
            return current_direction;
        }
        ptr = ptr->next;
    }
    return -current_direction;
}

void elevator_update_direction() 
{
    if (elevator_stopped_between_floors() && !orders_is_empty()) {
        if (current_direction == -1 && orders_above(current_floor-1)){
            current_floor    -=  1;
            current_direction =  1;
        }
        if (current_direction == 1 && orders_below(current_floor+1)){   
            current_floor    +=  1;
            current_direction = -1;
        }
        elev_set_motor_direction(current_direction);
    }
    else if (!timer_running() && elevator_is_on_floor()){ //Only give new direction to elevator when elevator still at floor with no door timer running
        elev_set_door_open_lamp(0);
        current_direction = elevator_find_direction(current_floor, current_direction);
        elev_set_motor_direction(current_direction);
    }
}

bool elevator_stopped_between_floors(){
    return (current_direction != elev_get_motor_direction() && elev_get_floor_sensor_signal() == -1);
}

bool elevator_is_on_floor(){
    return elev_get_floor_sensor_signal() != -1;
}

void elevator_stop(){
    elev_set_motor_direction(0);
    orders_remove_all();
    buttons_deluminate_all();
    elev_set_stop_lamp(1);
    if (elevator_is_on_floor()){
        orders_add(current_floor, 0);
        elev_set_door_open_lamp(1);
    }
    while(elev_get_stop_signal()){
        // Keep stop button light on and ignore orders
    }
    elev_set_stop_lamp(0);
}



void elevator_print_status(){
	printf("\n############### STATUS ################\n");
    printf("\n\tCurrent floor: %d", current_floor);
    printf("\n\tCurrent direction: %d", current_direction);
    printf("\n\tMotor thrust: %d", elev_get_motor_direction());
    orders_print();
	printf("\n################# END #################\n\n\n\n");
}
