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
void FSM_update_direction();
bool FSM_is_new_floor();