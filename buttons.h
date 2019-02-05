#ifndef _BUTTONS_H_
#define _BUTTONS_H_

#include "elev.h"



/**
   Poll for button input for order buttons.
   Add order if button pressed and illuminate button.
*/
void buttons_poll(void);


/**
   Turn light of specified button.
*/
void buttons_deluminate(int floor);


/**
   Delimunate all buttons.
*/
void buttons_deluminate_all(void);

#endif