#include <stdio.h>
#include "gluethread/glthread.h"

#define NODE_NAME_SIZE 16
#define IF_NAME_SIZE 16
#define MAX_INTF_PER_NODE 10 

/* forward declarations */
typedef struct linknode_ linknode_t;
typedef struct link_ link_t; //don't need to declare struct anymore. 

typedef  struct Node{
	int value;
	struct Node* next; 
}Node_t;

typedef struct interface_{
	char if_name[IF_NAME_SIZE];
	struct node_ *att_node;

}interface_t;

struct link_{//link between two interfaces 
	interface_t intf1; //interface1
	interface_t intf2;//interface 2
	unsigned int cost; //cost of traveling through the link.
};

struct linknode_{
	char node_name[NODE_NAME_SIZE]; //name of device
	interface_t *intf[MAX_INTF_PER_NODE]; //empty slots on the device
	glthread_t graph_glue; 
}

typedef struct graph_{
	
	char topology_name[32];
        Node_t * node_list; // glthread_t form of linked list
}
