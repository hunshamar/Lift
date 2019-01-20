#include "final_state_machine.h"
#include "orders.h"

int FSM_find_dir(int floor, elev_motor_direction_t direction){
    order_t *temp = get_head();
    while (temp->next != NULL){
        if (direction == 0) return -(floor > temp->floor) + (floor < temp->floor);
        if (floor > temp->floor || floor < temp->floor) return direction;
        temp = temp->next;
    }
    return -direction;
}