void orders_print(){

    if(elev_get_obstruction_signal()){
    printf("orders up:   [%d, %d, %d, %d] \norders down: [%d, %d, %d, %d]\n",
        ord.orders_up[0], ord.orders_up[1], ord.orders_up[2],ord.orders_up[3],
        ord.orders_down[0], ord.orders_down[1], ord.orders_down[2],ord.orders_down[3]);
    }
}