
/**
 * @file
 * @brief This library includes the functions for manipulating and 
 * analyzing the elevator orders 
 * The orders are a linked list. The head of the linked list is given by a static global variable pointer, that 
 * is manipulated through the functions in this library. 
 */


#ifndef _ORDERS_H_
#define _ORDERS_H_

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


/** 
  * @brief enum for the current direction of the elevator
  */

typedef enum direction{
    DIR_UP = 1,
    DIR_DOWN = -1,
    DIR_NEUTRAL = 0,
    DIR_NOT_DEFINED = 2
}dir_t;


/**
  * @brief Linked list node structure for order handling 
  */
typedef struct order{
    int floor;
    dir_t direction;
    struct order *next;
}order_t;


/**
  * @brief Get the first order in the list (the head)
  * 
  * @return the pointer to the head of the order list, NULL if the list is empty
  */
order_t* orders_get_head_order(void);



/**
  * @brief Adds an order to the order linked list. 
  * Each floor can only have one order.
  * Direction both up and down on a floor gives a neutral direction order.
  *
  * @param [in] floor Floor of the order
  * @param [in] direction Direction of order
  */
void orders_add(int floor, dir_t direction);



/**
  * @brief Removes an order from the order list if it exists.
  *
  * @param [in] floor Floor to clear the orders on
  */
void orders_remove(int floor);



/**
  * @brief Removes all orders from the linked list.
  */
void orders_remove_all(void);



/**
  * @brief A function to check if there is currently an order on the floor
  * 
  * @Return True if there exists an order on given floor.
  * Else it  returns false.
  */
bool order_on_floor(int floor); 



/**
  * @brief A function to check if there are orders ahead of the elevator in the direction it is going
  *
  * @param[in] floor The floor the elevator is on
  * @param[in] current_direction The direction the elevator is traveling in 
  *
  * @return true if there are orders ahead of the floor, in the given current direction of the elevator.
  * Else return false.  
  */
bool orders_ahead(double floor, dir_t current_direction);



/**
  * @brief A function to check if there is an executable order on the floor 
  *
  * @param[in] floor The floor the elevator is on
  * @param[in] current_direction The direction the elevator is traveling in 
  *
  * @return true if the elevator has an executable order on given floor,
  * 
  */
bool order_is_executable_on_floor(int floor, dir_t current_direction);



/**
  * @brief checks if the order linked list is empty
  * 
  * @return true if there are no orders, elsewise false
  */
bool orders_is_empty(void);



/**
  * @brief prints all orders
  */
void orders_print(void);


#endif
