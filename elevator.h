#ifndef _ELEVATOR_H_
#define _ELEVATOR_H_



#include <stdbool.h>
#include "elev.h"
#include "orders.h"


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
int elevator_find_direction(double floor, dir_t current_direction);

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

/**

 */
int elevator_update_floor_read();


#endif