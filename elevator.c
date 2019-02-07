#include "elevator.h"

#include <stdlib.h>
#include <stdio.h>
#include "timer.h"
#include "buttons.h"



/* If elevator stopped between floors, the current_floor is updated with a .5 decimal value,
   to keep track of which two floors the elevator is stopped between. */
static double current_floor;

/* Keeps track of direction of the elevator, is only set to zero when the elevator is idle. */ 
static int current_direction;

/* Updated with readings from the floor sensor signal. */
static int floor_read;


void elevator_init(void){
    buttons_deluminate_all();
    while(elevator_update_floor_read() == -1){   
        elev_set_motor_direction(DIR_DOWN);
    }
    elev_set_motor_direction(DOR_NEUTRAL);
    current_floor = floor_read;
    current_direction = DIR_NEUTRAL;
}


dir_t elevator_find_direction(double floor, dir_t current_direction) {
    if (orders_is_empty()) {
        return DIR_NEUTRAL;
    }
    if (current_direction == 0){ // List has been empty, now new order is placed. Return which direction to go
        if (orders_get_head_order()->floor < floor){
            return DIR_DOWN
        }
        if (orders_get_head_order->floor > floor){
            return DIR_UP
        }
        else{
            return DIR_NEUTRAL
        }
    }
    if (orders_ahead(floor, current_direction)){ 
        return current_direction; //If there are more orders ahead to be executed, continue in current_direction
    }
    else{
        return -current_direction; // If not turn around
    }
}

void elevator_update_direction(void){
    if (!timer_running()){ //Only give new direction to elevator when no door timer running
        elev_set_door_open_lamp(0);
        current_direction = elevator_find_direction(current_floor, current_direction);
        elev_set_motor_direction(current_direction);
    }
}


void elevator_execute_order(void){
    current_floor = floor_read;
    elev_set_floor_indicator(current_floor);
    if (order_is_executable_on_floor(current_floor, current_direction)){
        orders_remove(current_floor);            
        elev_set_motor_direction(DIR_NEUTRAL);
        timer_start(3);
        elev_set_door_open_lamp(1);
        buttons_deluminate(current_floor);
    }    
}


int elevator_update_floor_read(void){
    floor_read = elev_get_floor_sensor_signal();
    return floor_read;
}

bool elevator_is_on_floor(void){
    return floor_read != -1;
}

void elevator_stop(void){
    elev_set_motor_direction(DIR_NEUTRAL);
    orders_remove_all();
    buttons_deluminate_all();
    elev_set_stop_lamp(1);
    if (elevator_is_on_floor()){
        orders_add(current_floor, DIR_NEUTRAL);
        elev_set_door_open_lamp(1);
    }
    else if((int)current_floor == current_floor){ // Keeps track of which floors the elevator is stopped between
        current_floor += current_direction/2.0;
    }
    
    while(elev_get_stop_signal()){
        // Keep stop button light on and ignore orders
    }
    elev_set_stop_lamp(0);
}

void elevator_print_status(void){
	printf("\n############### STATUS ################\n");
    printf("\n\tCurrent floor: %f", current_floor);
    printf("\n\tCurrent direction: %d", current_direction);
    printf("\n\tMotor thrust: %d", elev_get_motor_direction());
    orders_print();
	printf("\n################# END #################\n\n\n\n");
}
