#include "elevator.h"

#include <stdlib.h>
#include <stdio.h>
#include "timer.h"
#include "buttons.h"



//Static global variables, only accessible in this source file
static double current_floor; 
static int current_direction;
static int floor_read;

void elevator_init(void){
    buttons_deluminate_all();
    while(elevator_update_floor_read() == -1){   
        elev_set_motor_direction(-1);
    }
    elev_set_motor_direction(0);
    current_floor = floor_read;
    current_direction = 0;
}

void elevator_execute_order(void){
    current_floor = floor_read;
    elev_set_floor_indicator(current_floor);
    if (order_is_executable_on_floor(current_floor, current_direction)){
        orders_remove(current_floor);            
        elev_set_motor_direction(0);
        timer_start(3);
        elev_set_door_open_lamp(1);
        buttons_deluminate(current_floor);
    }    
}

int elevator_find_direction(double floor, dir_t current_direction) {
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

void elevator_update_direction(void) {
    if (!timer_running()){ //Only give new direction to elevator when elevator still at floor with no door timer running
        elev_set_door_open_lamp(0);
        current_direction = elevator_find_direction(current_floor, current_direction);
        elev_set_motor_direction(current_direction);
    }
}

bool elevator_stopped_between_floors(void){
    return (current_direction != elev_get_motor_direction() && floor_read == -1);
}

int elevator_update_floor_read(){
    floor_read = elev_get_floor_sensor_signal();
    return floor_read;
}

bool elevator_is_on_floor(void){
    return floor_read != -1;
}

void elevator_stop(void){
    elev_set_motor_direction(0);
    orders_remove_all();
    buttons_deluminate_all();
    elev_set_stop_lamp(1);
    if (elevator_is_on_floor()){
        orders_add(current_floor, 0);
        elev_set_door_open_lamp(1);
    }
    else if((int)current_floor == current_floor){
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
