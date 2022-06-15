#include "graph.h"
#include <memory.h>
#include "utils.h"
#include <stdio.h>

/*Assign a unique mac address to interface */
void interface_assign_mac_address(interface_t *interface){
	memset(IF_MAC(interface), 0, 8); //assign 0s to the mac address of the interface
	strcpy(IF_MAC(interface), interface->att_node->node_name); //assign the node name 
	strcat(IF_MAC(interface), interface->if_name); //concat interface name
}

bool_t node_set_loopback_address(node_t *node, char *ip_addr){
	if(strlen(ip_addr) <= 0){
		printf("INVALID ipaddr");
		return FALSE;
	}
	node->node_nw_prop.is_lb_addr_config = TRUE;
	strncpy(NODE_LO_ADDR(node), ip_addr, 16); //set the loopback address of the node 
	NODE_LO_ADDR(node)[15] = '\0'; //last character = null terminating character. 
	
	return TRUE; //success
}

bool_t node_set_intf_ip_address(node_t *node, char *local_if, char *ip_addr, char mask){
	interface_t *interface = get_node_if_by_name(node, local_if); //get the interface that was passed in 
	if(interface == NULL){
		printf("Error : invalid interface\n"); 
		return FALSE;
	}
	
	strncpy(IF_IP(interface), ip_addr, 16); // set the interface ip address.
	IF_IP(interface)[15] = '\0';
	interface->intf_nw_props.mask = mask; //set the mask 
	interface->intf_nw_props.is_ipadd_config = TRUE; //true : ip address is configured on interface
	return TRUE; //success
}
/*random number generator function */
static unsigned int  hash_code(void *ptr, unsigned int size){
	unsigned  int value=0, i=0;
	char *str = (char*)ptr;
	while(i < size){
		value += *str;
		value *= 97;
		str++;
		i++;
	}
	return value; 
}


/*assign, assign a unique mac address, to interface*/
void interface_assign_mac_address(interface_t *interface){
	node_t *node = interface->att_node; //the node associated with the interface
	
	if(node == NULL){
		printf("Error: invalid interface node");
		return;
	}
	
	unsigned int hash_code_val = 0; 
	hash_code_val = hash_code(node->node_name, NODE_NAME_SIZE);
	hash_code_val *= hash_code(interface->if_name, IF_NAME_SIZE); 
	memset(IF_MAC(interface), 0, sizeof(IF_MAC(interface)); 
	memcpy(IF_MAC(interface), (char*)&hash_code_val, sizeof(unsigned int)); 
}

bool_t node_set_device_type(node_t *node, unsigned int F){
	SET_BIT(node->node_nw_prop.flags, F);
	return TRUE; 
}
