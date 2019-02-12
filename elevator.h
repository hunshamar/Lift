#ifndef _ELEVATOR_H_
#define _ELEVATOR_H_



#include <stdbool.h>
#include "elev.h"
#include "orders.h"


/**
  Deluminates all buttons.
  Positions the elevator at nearest floor below the initial position.
  Sets starting parameters for the elevator.
*/
void elevator_init(void);



/**
   Logic to calculate which direction the elevator is to go.
*/
dir_t elevator_find_direction(double floor, dir_t current_direction);



/**
   Feeds updated direction to the elevator, starting the motor and if necessary closing the door. 
*/
void elevator_update_direction(void);



/**
  This function is called when the elevator is on a floor.
  Updates current_floor and sets the floor indicator.
  If there exists an executable order on the floor, the order is removed, the elevator stops,
   the timer starts, and the door opens for 3 seconds.
*/
void elevator_execute_orders(void);



/**
   Updates the floor_read variable with a reading from the floor indicator sensor.
 */
void elevator_update_floor_read(void);



/**
   Return true if the floor_read variable is set to a floor.
   Return false if -1.
 */
bool elevator_is_on_floor(void);



/**
   Called when stop button is pressed.
   The motor is shut of.
   All orders are removed, and buttons are deluminated.
   If elevator is stopped at a floor, the door is opened for 3 seconds.
   If between floors, the elevator is stopped between the floors until a new order arrives.
*/
void elevator_stop(void);



/**
   Sexy printout of the elevator variables and orders.
*/
void elevator_print_status(void);




#endif