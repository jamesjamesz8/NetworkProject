#include <stdio.h>
#include "gluethread/glthread.h"

#define NODE_NAME_SIZE 16
#define IF_NAME_SIZE 16
#define MAX_INTF_PER_NODE 10 

typedef struct node_ node_t;


struct node_{
        char node_name[NODE_NAME_SIZE]; //name of device
        interface_t *intf[MAX_INTF_PER_NODE]; //empty slots on the device
        glthread_t graph_glue;
}

typedef struct interface_{
        char if_name[IF_NAME_SIZE];
        struct node_ *att_node;

}interface_t;

/*helper function*/

static inline node_t* get_nbr_node(interface_t *interface){
	return interface->att_node; 
}

static inline int get_node_intf_available_slot(node_t *node){
	interface_t *tmp[] = node->intf;
	for(int i = 0; i < MAX_INTF_PER_NODE; i++){
		if(tmp[i] == NULL){ // free slot 
			return i; //return the index to empty slot. 
		}
	}
	return -1;//no slots available. 
}
