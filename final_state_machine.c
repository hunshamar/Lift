#include "final_state_machine.h"
#include "orders.h"

static int a = 0;
static int current_floor;
static int current_direction;

int FSM_find_dir(int floor, elev_motor_direction_t direction){
    printf("before get head\n;");
    order_t *order_node = get_head();
    printf("after get head\n;");
    while (order_node->next != NULL){
        printf("current: %d", order_node->floor);
        if (direction == 0){ 
            return -(floor > order_node->floor) + (floor < order_node->floor);
        }
        if (floor > order_node->floor || floor < order_node->floor){
            return direction;
        }
        order_node = order_node->next;
    }
    return (-1)*direction;
}

void FSM_init(){
    while(elev_get_floor_sensor_signal() == -1){
        elev_set_motor_direction(-1);
    }
    elev_set_motor_direction(0);
    current_floor = elev_get_floor_sensor_signal();
    current_direction = 0;
    
}

void FSM_execute_order(){
    current_floor = elev_get_floor_sensor_signal();
    printf("oppdatert, current direction: %d\n", current_direction);
    if (order_check_if_executable_on_floor(current_floor, current_direction)){
        orders_remove(current_floor);            
        elev_set_motor_direction(0);
        timer_start(3);
        if (orders_is_empty()){
            current_direction = 0;
        }
        buttons_deluminate(current_floor);
    }
    else{
        printf("\n NON EXECUTABLE ON FLOOR! \n");
    }
    
}
void print_orders(){

    int b = elev_get_obstruction_signal();
    if (b == a){
        printf("\n\n");
        printf("\nCurrent floor = %d, current_cirection = %d", current_floor, current_direction);
        orders_print();
        a = !a;
    }

}

void FSM_update_direction(){
    if(!timer_running()){
        current_direction = orders_find_dir(current_floor, current_direction);
        elev_set_motor_direction(current_direction);
    }   
}

bool FSM_is_new_floor(){
    return elev_get_floor_sensor_signal() != -1 && elev_get_floor_sensor_signal() != current_floor;
}