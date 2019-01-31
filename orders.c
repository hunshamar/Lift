#include "orders.h"


static order_t * head = NULL;


order_t* orders_get_head(){
    return head;
}

void orders_add(int floor, dir_t direction)
{
    order_t *new_order = (order_t*)malloc(sizeof(order_t)); // Allocate memory for new order
    new_order->direction = direction;
    new_order->floor = floor;
    new_order->next = NULL; 

    if (head == NULL) //Empty list
    {
        head = new_order;
    }
    else
    {
        //Loop through list
        order_t *ptr = head;
        while(ptr != NULL) // Itereate to the end of list
        {
            /* If order already exsists on floor*/
            if (new_order->floor == ptr->floor)
            {   
                if (new_order->direction != ptr->direction)
                { 
                    /* If new order on floor, but with different direction we can set direction to NEUTRAL */
                    ptr->direction = DIR_NEUTRAL;
                }
                free(new_order); //we don't need the allocated space
                

                return;
            }
            if (ptr->next == 0)
            {
                ptr->next = new_order; //Add to end of list

                return;
            }
            ptr = ptr->next;
        }
    }
}

void orders_print()
{
   	if (orders_is_empty())
    {
        printf("\n\tno orders\n");
        return;
    }

	int cnt = 1;
	printf("\n\n\t---------orders---------    \n");
	order_t *ptr = head;

	while (ptr != NULL)
	{
			printf("\tNr: %d:  floor:%d,  dir:%d \n", cnt, ptr->floor, ptr->direction);
			ptr = ptr->next;
			cnt++;
	}
  	printf("\t------------------------    \n");

}    

void orders_remove(int floor)
{
    if (head->floor == floor)
    {   
        free(head);
        head = head->next;
        return;
    }

    order_t* ptr = head;

    while (ptr->next != NULL)
    {
        if (ptr->next->floor == floor)
        {   
            free(ptr->next);
            ptr->next = ptr->next->next;
            return;
        }
        ptr = ptr->next;
    }    
}

void orders_remove_all()
{
    while(head != NULL)
    {
        orders_remove(head->floor);
    }
}

bool orders_above(int floor)
{
    order_t* ptr = head;
    while (ptr != NULL)
    {
        if (ptr->floor > floor)
        {
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}


bool orders_below(int floor)
{
    order_t* ptr = head;
    while (ptr != NULL)
    {
        if (ptr->floor < floor)
        {
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}

bool order_on_floor(int floor)
{
    order_t* ptr = head;
    while (ptr != NULL)
    {
        if (ptr->floor == floor)
        {
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}    

dir_t order_get_direction(int floor)
{
    if (!order_on_floor(floor))
    {
        return 0;
    }

    order_t* ptr = head;
    while (ptr != NULL)
    {
        if (ptr->floor == floor)
        {
            return ptr->direction;
        }
        ptr = ptr->next;
    }
    return 0;
}


bool order_is_executable_on_floor(int floor, dir_t current_dir)
{   
    if (order_on_floor(floor))
    {
        dir_t ord_dir = order_get_direction(floor);
        if (ord_dir == current_dir || ord_dir == DIR_NEUTRAL)
        {
            return true;
        }
        if (ord_dir ==  DIR_UP && !orders_below(floor))
        {
            return true;
        }
        if (ord_dir == DIR_DOWN && !orders_above(floor))
        {
            return true;
        }
    } 
    return false;
}





bool orders_is_empty(){
    return (head == NULL);
}