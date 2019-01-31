#ifndef _ELEVATOR_H_
#define _ELEVATOR_H_



#include <stdbool.h>
#include "elev.h"
#include "orders.h"


/**
  
*/
int elevator_find_dir(int floor, elev_motor_direction_t direction);

/**
  
*/
void elevator_init(void);

/**
  
*/
void elevator_execute_order(void);

/**
  
*/
void elevator_print_status(void);

/**
  
*/
int elevator_find_direction(int floor, dir_t current_direction);

/**
  
*/
void elevator_update_direction(void);

/**
  
*/
bool elevator_is_on_floor(void);

/**
  
*/
void elevator_stop(void);

/**
  
*/
bool elevator_stopped_between_floors(void);

#endif