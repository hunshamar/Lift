#ifndef _ORDERS_
#define _ORDERS_

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "elev.h"


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




order_t* get_head();
void orders_add(int floor, dir_t direction);
void orders_print();
void orders_remove(int floor);
void orders_remove_all();

void elevator_check_buttons();

bool order_check_if_executable_on_floor(int floor, dir_t elev_dir);

#endif