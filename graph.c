/**Graph.c**/
/** graph contains the routines to construct the Network Graph**/ 


#include <stdio.h>
#include "gluethread/glthread.h"
#include <string.h>
#include "stdlib.h" 
#include "graph.h"


#define NODE_NAME_SIZE 16
#define IF_NAME_SIZE 16
#define MAX_INTF_PER_NODE 10 

/* forward declarations */
/*
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
}*/



graph_t * build_first_topo(){
	graph_t *topo = create_new_graph("Hello World Generic Graph");  //creating the new graph
	node_t *R0_re = create_graph_node(topo, "R0_re");
	node_t *R1_re = create_graph_node(topo, "R1_re");
	node_t *R2_re = create_graph_node(topo, "R2_re");	
	
	insert_link_between_two_nodes(R0_re, R1_re, "eth0/0", "eth0/1", 1);  //nodes, name of interface for each node, cost; 
	insert_link_between_two_nodes(R1_re, R2_re, "eth0/2", "eth0/3", 1); 
	insert_link_between_two_nodes(R0_re, R2_re, "eth0/4", "eth0/5", 1); 
	
	return topo;
}

//inserting a link between two nodes
void insert_link_between_two_nodes(node_t *node1, node_t *node2, char *from_if_name, char *to_if_name, unsigned int cost){
	link_t *link = calloc(1, sizeof(link_t)); 
	/*set interface properties */
	strncpy(link->intf1.if_name, from_if_name, IF_NAME_SIZE); 
	link->intf1.if_name[IF_NAME_SIZE -1] = '\0';
	strncpy(link->intf2.if_name, to_if_name, IF_NAME_SIZE); 
	link->intf2.if_name[IF_NAME_SIZE -1] = '\0';
	
	link->intf1.link = link; /*set back pointer to link*/
	link->intf2.link = link; 
	
	link->intf1.att_node = node1;
	link->intf2.att_node = node2; 
	link->cost = cost;
	
	int empty_intf_slot;
	
	/*Plugin interface end into Node*/
	empty_intf_slot = get_node_intf_available_slot(node1);
	node1->intf[empty_intf_slot] = &link->intf1;
	
	empty_intf_slot = get_node_intf_available_slot(node2); // plugging the links into slots. 
	node2->intf[empty_intf_slot] = &link->intf2; 
	
}

//void initializeList(

graph_t * create_new_graph(char *topology_name){
	graph_t *graph = calloc(1, sizeof(graph_t)); 
	strncpy(graph->topology_name, topology_name, 32); //strncpy copies a based on how many characters specified. 
	graph->topology_name[31] = '\0'; 
	//init_glthread(&graph->node_list); //initializing linked list.  *TODO* -> insert my own linkedlist functions
	graph->node_list = (node_t *)calloc(1, sizeof(node_t)); //allocates memory for 
	return graph; 
}

node_t *create_graph_node(graph_t *graph, char *node_name){
	node_t *node = calloc(1, sizeof(node_t)); 
	strncpy(node->node_name, node_name, NODE_NAME_SIZE);
	node->node_name[NODE_NAME_SIZE] = '\0'; 
	
	node_t *curr = graph->node_list; //current pointer to node_list of the graph
	if(graph->node_list == NULL){
		printf("error the node_list hasn't been initialized");
		return NULL; 
	}
	while(curr->next != NULL){
		curr = curr->next;
	}
	curr->next = node; //set tail to new node; 
	return node; 
}



void dump_graph(graph_t *graph){

    node_t *node;
    node_t* curr; 
    curr = graph->node_list->next; // head will return the head of the linked list of nodes. 
    
    printf("Topology Name = %s\n", graph->topology_name);

   /** ITERATE_GLTHREAD_BEGIN(&graph->node_list, curr){ // -- given code

        node = graph_glue_to_node(curr);
        dump_node(node);    
    } ITERATE_GLTHREAD_END(&graph->node_list, curr);**/
    // topology name
   // printf("Topology Name = %s\n", graph->topology_name); 
    while(curr != NULL){
    	
    	
    	//current node's name
    	printf("Node Name = %s\n", curr->node_name); 
    	//neighbor nodes
    	interface_t *interfaces[MAX_INTF_PER_NODE];
    	for(int i = 0 ; i < MAX_INTF_PER_NODE; i++){
    		interfaces[i] = curr->intf[i]; 
    	} 
    	for(int i = 0;  i < MAX_INTF_PER_NODE; i++){
    		if(interfaces[i] == NULL){
    			break;
    		}
    		if(curr->intf[i] != NULL && curr->intf[0] == NULL){
    			printf("i = %d , error invalid link for Node Name : %s, Interface : %s\n",i, curr->node_name, "fef");
    			break;  
    		}
    		printf(" Local Node: %s, Interface Name = %s, Nbr Node %s, cost = %d\n", curr->node_name
    										    , curr->intf[i]->if_name, 
    										      get_nbr_node(curr->intf[i])->node_name,
    										      curr->intf[i]->link->cost);
	
    	}
    	
    	curr = curr->next;
    }
}



