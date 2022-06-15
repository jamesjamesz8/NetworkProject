#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <string.h>
#include "gluethread/glthread.h"

#define NODE_NAME_SIZE 16
#define IF_NAME_SIZE 16
#define MAX_INTF_PER_NODE 10 

typedef struct node_ node_t;
typedef struct link_ link_t; 
typedef struct graph_ graph_t;

struct graph_{

        char topology_name[32];
        node_t * node_list; // head pointer
};  
typedef struct interface_{
        char if_name[IF_NAME_SIZE];
        struct node_ *att_node;
	struct link_ *link; 
	intf_nw_props_t intf_nw_props; //interface network properties. 

}interface_t;

struct node_{
        char node_name[NODE_NAME_SIZE]; //name of device
        interface_t *intf[MAX_INTF_PER_NODE]; //empty slots on the device
        node_t* next; 
        //glthread_t graph_glue;
        node_nw_prop_t node_nw_prop; //node network properties. 
};



struct link_{//link between two interfaces 
        interface_t intf1; //interface1
        interface_t intf2;//interface 2
        unsigned int cost; //cost of traveling through the link.
};

/*helper function*/

static inline node_t* get_nbr_node(interface_t *interface){
	if(interface == NULL){
		printf("error : invalid interface. ");
		return NULL; 
	}
	if(interface->link == NULL){
		printf("error : invalid link on interface. ");
		return NULL;	
	}
	link_t *link = interface->link; 
        if(&link->intf1 == interface){
		//nbr is neighbor node?
		return link->intf2.att_node;
	}	
	else{
		return link->intf1.att_node;
	}
	
}

static inline int get_node_intf_available_slot(node_t *node){
	interface_t *tmp[MAX_INTF_PER_NODE];
	memcpy(tmp, node->intf, MAX_INTF_PER_NODE);
	for(int i = 0; i < MAX_INTF_PER_NODE; i++){
		if(tmp[i] == NULL){ // free slot 
			
			printf("\nAt node name %s, empty slot at %d \n",node->node_name, i); 
			return i; //return the index to empty slot. 
		}
	}
	return -1;//no slots available. 


}

static inline interface_t* get_node_if_by_name(node_t *node, char *if_name){
	if(node == NULL){
		printf("error : invalid node\n");
		return NULL; 
	}
	
	for(int i = 0;  i < MAX_INTF_PER_NODE; i++){
		if(node->intf[i] == NULL){
			return NULL //NONE FOUND
		}
		if(strncmp(node->intf[i]->if_name, if_name, IF_NAME_SIZE) == 0){
			return node->intf[i];
		}
	}
	return NULL; //none found 
}

static inline node_t* get_node_by_node_name(graph_t *topo, char *node_name){
	if(topo == NULL || topo->node_list == NULL){
		printf("Error : invalid graph/node list\n");
		return NULL; 
	}
	node_t *curr = topo->node_list->next;
	while(curr != NULL){
		if(strncmp(curr->node_name, node_name, NODE_NAME_SIZE) == 0)
			return curr; 
		
		curr = curr->next; 
	}
	
	return NULL; // none found. 
	
}




/** graph.c functions **/ 
void dump_graph(graph_t *graph);
graph_t * create_new_graph(char *topology_name); //function declaration 
node_t *create_graph_node(graph_t *graph, char *node_name);
void insert_link_between_two_nodes(node_t *node1, node_t *node2, char *from_if_name, char *to_if_name, unsigned int cost);
#endif
