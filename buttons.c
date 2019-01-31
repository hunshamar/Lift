


#include "buttons.h"
#include "orders.h"

void buttons_poll(void){
    for (int floor = 0; floor < 3; floor++){
        if (elev_get_button_signal(BUTTON_CALL_UP, floor)){
            orders_add(floor, DIR_UP);
            elev_set_button_lamp(BUTTON_CALL_UP, floor, 1);
        }
    }
    for (int floor = 1; floor < 4; floor++){
        if (elev_get_button_signal(BUTTON_CALL_DOWN, floor)){
            orders_add(floor, DIR_DOWN);
            elev_set_button_lamp(BUTTON_CALL_DOWN, floor, 1);
        }
    }
    for (int floor = 0; floor < 4; floor++){
        if (elev_get_button_signal(BUTTON_COMMAND, floor)){
            orders_add(floor, DIR_NEUTRAL);
            elev_set_button_lamp(BUTTON_COMMAND, floor, 1);
        }
    }
}

void buttons_deluminate(int floor){
    if (floor != 3){
        elev_set_button_lamp(BUTTON_CALL_UP, floor, 0);
    }
    if (floor != 0){
        elev_set_button_lamp(BUTTON_CALL_DOWN, floor, 0);
    }
    elev_set_button_lamp(BUTTON_COMMAND, floor,0);
}

void buttons_deluminate_all(void){
    for (int floor = 0; floor < 4; floor++){
        buttons_deluminate(floor);
    }
}