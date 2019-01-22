#include "orders.h"


static order_t * head = NULL;

order_t* get_head(){
    return head;
}
void orders_add(int floor, dir_t direction){

    order_t * temp = head;

    if (head == NULL){
        head = malloc(sizeof(order_t));
        temp = head;
    }else{
        while (temp->next != NULL){
            if (temp->floor == floor){
                if (temp->direction != direction){
                    temp->direction = DIR_NEUTRAL; //FLoor already has order, so the new must result in a stop order
                }
                return;
            }
            temp = temp->next;
        }
    }
    temp->floor = floor;
    if (floor == 0 || floor == 3){
        temp ->direction = DIR_NEUTRAL;
    }else{
        temp ->direction = direction;
    }
    temp->next = malloc(sizeof(order_t));
    temp->next->next = NULL;
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
    order_t *temp = head;
    order_t *temp_prev = NULL;
    while(temp != NULL){
        if (temp->floor == floor){
            if (temp_prev == NULL){
                head = temp->next;
            }
            else{
                temp_prev->next = temp->next;
            }
            free(temp);
            return;
        }
        temp_prev = temp;
        temp = temp->next;
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
        return 0;
    }
    if (head == NULL) {
        printf("Error elevator moving without orders\n"); 
        return false;
    }
    order_t *temp = head;
    while(temp->next != NULL){
        if (temp->floor == floor && (temp->direction == DIR_NEUTRAL || temp->direction == elev_dir)){
            return true;
        }
        temp = temp->next;
    }
    return false;
}


