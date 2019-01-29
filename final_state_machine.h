#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "timer.h"
#include "buttons.h"

#include "elev.h"

int FSM_find_dir(int floor, elev_motor_direction_t direction);
void FSM_init();
void FSM_execute_order();
void print_orders();

int FSM_find_direction(int floor, dir_t current_direction);
void FSM_update_direction();
bool FSM_is_on_floor();
void FSM_stop();
bool FSM_stopped_between_floors();