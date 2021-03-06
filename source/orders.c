#include "orders.h"


static order_t * head = NULL;


order_t* orders_get_head_order(){
    return head;
}

void orders_add(int floor, dir_t direction){
    order_t *new_order = (order_t*)malloc(sizeof(order_t)); // Allocate memory for new order
    new_order->direction = direction;
    new_order->floor = floor;
    new_order->next = NULL; 

    if (orders_is_empty()){ 
        head = new_order;
    }
    else{
        order_t *ptr = head;
        while(ptr != NULL){ // Itereate to the end of list
            
            if (new_order->floor == ptr->floor){ // If order already exsists on floor
                if (new_order->direction != ptr->direction){ 
                    ptr->direction = DIR_NEUTRAL; //If new order on floor, but with different direction we can set direction to NEUTRAL 
                }
                free(new_order); //we don't need the allocated space
                return;
            }
            if (ptr->next == 0){
                ptr->next = new_order; //Add to end of list
                return;
            }
            ptr = ptr->next;
        }
    }
}


void orders_remove(int floor){
    if (head->floor == floor){ //If the order to be removed is first in the list
        free(head); 
        head = head->next; //Set second order to be first in list
        return;
    }
    order_t* ptr = head;

/*  Iterates through the list and removes the order on the floor, if it exists. 
    The "next" pointer of the order behind the one to be removes is set to the order
    ahead of the one to be removed, erasing it from the list. */
    while (ptr->next != NULL){ 
        if (ptr->next->floor == floor){ 
            free(ptr->next);
            ptr->next = ptr->next->next;
            return;
        }
        ptr = ptr->next;
    }    
}

void orders_remove_all(){
    while(head != NULL){
        orders_remove(head->floor);
    }
}



dir_t order_get_direction_of_order(int floor){
    order_t* ptr = head;
    while (ptr != NULL){
        if (ptr->floor == floor){
            return ptr->direction;
        }
        ptr = ptr->next;
    }
    return DIR_NOT_DEFINED; // No order for floor
}

bool orders_ahead(double floor, dir_t current_direction){
    order_t* ptr = head;

    while (ptr != NULL){   
        if (floor*current_direction < ptr->floor*current_direction){
            return true;
        }
        
        ptr = ptr->next;
    }
    return false;
}

bool order_is_executable_on_floor(int floor, dir_t current_dir){   
    int ord_dir = order_get_direction_of_order(floor);
    if (ord_dir == DIR_NOT_DEFINED){ // No order for the floor
        return false; 
    }
    else{
        if (ord_dir == current_dir || ord_dir == DIR_NEUTRAL){ // Executable if the direction of the order is same as elevator or neutral
            return true; 
        }
        return (!orders_ahead(floor, current_dir)); // Executable if no more orders ahead
    }
}


bool orders_is_empty(){
    return (head == 0);
}


void orders_print(){
   	if (orders_is_empty()){
        printf("\n\tno orders\n");
        return;
    }
	int cnt = 1;
	printf("\n\n\t---------orders--------    \n");
	order_t *ptr = head;
	while (ptr != NULL){
			printf("\tNr: %d:  floor:%d,  dir:%d \n", cnt, ptr->floor, ptr->direction);
			ptr = ptr->next;
			cnt++;
	}
  	printf("\t-----------------------    \n");
} 



