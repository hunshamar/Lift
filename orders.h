#ifndef _ORDERS_H_
#define _ORDERS_H_

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>



typedef enum direction{
    DIR_UP = 1,
    DIR_DOWN = -1,
    DIR_NEUTRAL = 0,
    DIR_NOT_DEFINED = 2
}dir_t;


/**
   Linked list for order handling 
*/
typedef struct order{
    int floor;
    dir_t direction;
    struct order *next;
}order_t;




/**
    Return the pointer to the head of the order list.
*/
order_t* orders_get_head(void);



/**
   Adds an order to the order list. 
   Each floor can only have one order.
   Direction both up and down on a floor gives a neutral direction order.
*/
void orders_add(int floor, dir_t direction);



/**
    Removes an order from the order list if it exists.
*/
void orders_remove(int floor);



/**
   Removes all orders.
*/
void orders_remove_all(void);



/**
   Returns true if there exists an order on given floor.
   Else returns false.
*/
bool order_on_floor(int floor); 



/**
   Returns true if there are orders ahead of the floor, in the given current direction of the elevator.
   Else return false. 
*/
bool orders_ahead(double floor, dir_t current_direction);



/**
   Returns true if the elevator has an executable order on given floor,
   dependant on the current direction of the elevator.
*/
bool order_is_executable_on_floor(int floor, dir_t current_direction);



/**
   Returns true if elevator has no orders, elsewise false.
*/
bool orders_is_empty(void);



/**
   Prints all orders
*/
void orders_print(void);



#endif
