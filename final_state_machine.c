#include "final_state_machine.h"
#include "orders.h"

static int a = 0;
static int current_floor;
static int current_direction;

void FSM_init()
{
    while(elev_get_floor_sensor_signal() == -1)
    {   
        elev_set_motor_direction(-1);
    }
    elev_set_motor_direction(0);
    buttons_deluminate_all();

    current_floor = elev_get_floor_sensor_signal();
    current_direction = 0;

}

void FSM_execute_order()
{
    current_floor = elev_get_floor_sensor_signal();
    if (order_executable_on_floor(current_floor, current_direction))
    {
        orders_remove(current_floor);            
        elev_set_motor_direction(0);
        timer_start(3);
        elev_set_door_open_lamp(1);
        buttons_deluminate(current_floor);
    }    
}


int FSM_find_direction(int floor, dir_t current_direction)  // f1oor = 1,  current_direction = -1,,     ligger en ordre på floor 3 med dir = -1 
{
    order_t *ptr = orders_get_head();

    if (ptr == NULL) 
    {
        return 0;
    }

    while (ptr != NULL)
    {   
        if (current_direction == 0)
        {
            return -(floor > ptr->floor) + (floor < ptr->floor);
        }
        if (floor*current_direction < ptr->floor*current_direction)
        {
            return current_direction;
        }
        ptr = ptr->next;
    }
    return -current_direction;
}


void FSM_update_direction() /* Må gi direction når stopp mellom etasjer også */ 
{
    if (FSM_stopped_between_floors()){
        while(orders_is_empty())
        {
            buttons_poll();
            if (elev_get_stop_signal())
            {
                FSM_stop();
            } 
        }
        if (current_direction == -1 && orders_above(current_floor-1))
        {
            current_floor -= 1;
            current_direction = 1;
        }
        if (current_direction == 1 && orders_below(current_floor+1))
        {   
            current_floor+= 1;
            current_direction = -1;
        }
        elev_set_motor_direction(current_direction);
    }
    if (!timer_running() && elev_get_floor_sensor_signal() != -1 )
    {   

        
        elev_set_door_open_lamp(0);
    
        current_direction = FSM_find_direction(current_floor, current_direction);
        
        elev_set_motor_direction(current_direction);
    }
}

bool FSM_stopped_between_floors(){
    return ((current_direction != elev_get_motor_direction() && orders_is_empty()) && elev_get_floor_sensor_signal() == -1);
}


bool FSM_is_on_floor()
{
    return elev_get_floor_sensor_signal() != -1;// && elev_get_floor_sensor_signal() != current_floor;
}

void FSM_stop(){
    elev_set_motor_direction(0);
    orders_remove_all();
    buttons_deluminate_all();
    elev_set_stop_lamp(1);
    while(elev_get_stop_signal()){
        //Tom af
    }
    if (FSM_is_on_floor()){
        orders_add(current_floor, 0);
    }
    elev_set_stop_lamp(0);
}


void print_orders()
{
    int b = elev_get_obstruction_signal();
    if (b == a)
    {
        printf("\n\n");
        printf("\nCurrent floor = %d, current_cirection = %d", current_floor, current_direction);
        orders_print();
        a = !a;
    }

}
