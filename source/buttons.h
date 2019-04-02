/**
 * @file
 * @brief This library includes the functions for polling for button inputs and 
 * handeling the button lights
 */

#ifndef _BUTTONS_H_
#define _BUTTONS_H_

#include "elev.h"



/**
  * @brief Poll for button input for order buttons.
  * Add order if button pressed and illuminate button.
  */
void buttons_poll(void);


/**
  * @brief Turn light of the bottons on a specific floor.
  * @param[in] floor 
  */ 
void buttons_deluminate(int floor);


/**
  * @brief Delimunate all buttons.
  */
void buttons_deluminate_all(void);

#endif