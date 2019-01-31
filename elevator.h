#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "timer.h"
#include "buttons.h"
#include "elev.h"

int elevator_find_dir(int floor, elev_motor_direction_t direction);
void elevator_init();
void elevator_execute_order();
void elevator_print_status();
int elevator_find_direction(int floor, dir_t current_direction);
void elevator_update_direction();
bool elevator_is_on_floor();
void elevator_stop();
bool elevator_stopped_between_floors();