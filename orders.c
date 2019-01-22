#include "orders.h"


static order_t * head = NULL;

order_t* get_head(){
    return head;
}
void orders_add(int floor, dir_t direction){

    order_t * order_node = head;

    if (head == NULL){
        head = malloc(sizeof(order_t));
        order_node = head;
    }else{
        while (order_node->next != NULL){
            if (order_node->floor == floor){
                if (order_node->direction != direction){
                    order_node->direction = DIR_NEUTRAL; //FLoor already has order, so the new must result in a stop order
                }
                return;
            }
            order_node = order_node->next;
        }
    }
    order_node->floor = floor;
    if (floor == 0 || floor == 3){
        order_node ->direction = DIR_NEUTRAL;
    }else{
        order_node ->direction = direction;
    }
    order_node->next = malloc(sizeof(order_t));
    order_node->next->next = NULL;
}

void orders_print() {
	int cnt = 1;
	printf("\nPrinter liste:\n");
	order_t *ptr = head;
	if (head == NULL){
        printf("\tLISTEN ER TOM!"); 
        return;
    }
	while (ptr->next != NULL)
	{
			printf("\tNr: %d, \t floor:%d, \t dir:%d \n", cnt, ptr->floor, ptr->direction);
			ptr = ptr->next;
			cnt++;
	}
	printf("SLUTT\n\n");
}
void orders_remove(int floor){
    printf("Fjerner %d \n", floor);
    if (head == NULL){
        return;
    }
    if (head->floor == floor && head->next->next == NULL){
        free(head->next);
        free(head);
        head = NULL;
        return;
    }
    order_t *order_node = head;
    order_t *order_node_prev = NULL;
    while(order_node != NULL){
        if (order_node->floor == floor){
            if (order_node_prev == NULL){
                head = order_node->next;
            }
            else{
                order_node_prev->next = order_node->next;
            }
            free(order_node);
            return;
        }
        order_node_prev = order_node;
        order_node = order_node->next;
    }
    orders_print();
}
void orders_remove_all(){
    while(head != NULL){
        orders_remove(head->floor);
    }
}

//up = 1
//down = -1
//command = 0



void elevator_check_buttons(){
    for (int floor = 0; floor < 3; floor++){
        if (elev_get_button_signal(BUTTON_CALL_UP, floor)){
            orders_add(floor, DIR_UP);
            elev_set_button_lamp(BUTTON_CALL_UP, floor, 1);
        }
    }
    for (int floor = 1; floor < 4; floor++){
        if (elev_get_button_signal(BUTTON_CALL_DOWN, floor)){
            orders_add(floor, DIR_DOWN);
            elev_set_button_lamp(BUTTON_CALL_DOWN, floor, 1);
        }
    }
    for (int floor = 0; floor < 4; floor++){
        if (elev_get_button_signal(BUTTON_COMMAND, floor)){
            orders_add(floor, DIR_NEUTRAL);
            elev_set_button_lamp(BUTTON_COMMAND, floor, 1);
        }
    }
}


bool order_check_if_executable_on_floor(int floor, dir_t elev_dir){ // sjekker om det finnes en ordre i en etasje
    if (!elev_dir){
        return false;
    }
    if (head == NULL) {
        printf("Error elevator moving without orders\n"); 
        return false;
    }
    order_t *order_node = head;
    while(order_node->next != NULL){
        if (order_node->floor == floor && (order_node->direction == DIR_NEUTRAL || order_node->direction == elev_dir)){
            return true;
        }
        order_node = order_node->next;
    }
    return false;
}


