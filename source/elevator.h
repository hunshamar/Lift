/**
 * @file
 * @brief This library includes the functions for controlling the elevator
 * The elevator has three static global paramters that are manipulated with the functions in this library. 
 * current_floor 
 * current_direction
 * floor read 
 * Functions from the elev library are run to give the correct inputs to the elevator motor, lights etc. 
 */

#ifndef _ELEVATOR_H_
#define _ELEVATOR_H_



#include <stdbool.h>
#include "elev.h"
#include "orders.h"


/**
  * @brief Deluminates all buttons.
  * Positions the elevator at nearest floor below the initial position.
  * Initialize starting parameters for the elevator.
  * @return 1 if not able to initialize elevator hardware
  */
int elevator_init(void);



/**
  * @brief Update current_direciton and feed to the elevator, starting the motor and if necessary closing the door. 
  */
void elevator_update_direction(void);



/**
  * @brief This function is called when the elevator is on a floor.
  * Updates current_floor and sets the floor indicator light.
  * If there exists an executable order on the floor, the order is removed, the elevator stops,
  * the timer starts, and the door is opened for 3 seconds.
  */
void elevator_execute_orders(void);



/**
  * @brief Updates the floor_read variable with a reading from the floor indicator sensor.
  */
void elevator_update_floor_read(void);



/**
  * @return true if the floor_read variable is set to a floor.
  * false if floor_read returns that the elevator is between floors.
  */
bool elevator_is_on_floor(void);



/**
  * @brief Called when stop button is pressed.
  * The motor is shut of.
  * All orders are removed, and buttons are deluminated.
  * If elevator is stopped at a floor, the door is opened for 3 seconds.
  * If between floors, the elevator is stopped between the floors until a new order arrives.
  */
void elevator_stop(void);



/**
  * @brief Sexy printout of elevator states and orders
  */
void elevator_print_status(void);

#endif