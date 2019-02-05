#ifndef _ORDERS_H_
#define _ORDERS_H_

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>



typedef enum direction{
    DIR_UP = 1,
    DIR_DOWN = -1,
    DIR_NEUTRAL = 0
}dir_t;


/* Linked list for order handling */
typedef struct order{
    int floor;
    dir_t direction;
    struct order *next;
}order_t;




order_t* orders_get_head(void);
void orders_add(int floor, dir_t direction);
void orders_remove(int floor);
void orders_remove_all(void);
bool order_on_floor(int floor); 
bool order_is_executable_on_floor(int floor, dir_t current_direction);
bool orders_is_empty(void);
void orders_print(void);

#endif
