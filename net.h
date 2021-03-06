
#ifndef NET_H
#define NET_H 


typedef struct ip_add_{
	char ip_addr[16]; 
}ip_add_t; 

typedef struct mac_add_{
	char mac[48];  // 8 byte mac address
}mac_add_t; 

typedef struct node_nw_prop_{
	/*l3 properties*/
	bool_t is_lb_addr_config;
	ip_add_t lb_addr; /*loopback address of node only accessed if bool is true*/ 
}node_nw_prop_t;

static inline void init_node_new_prop(node_nw_prop_t *node_nw_prop){
	node_nw_prop->is_lb_addr_config = FALSE;
	memset(node_nw_prop->lb_addr.ip_addr, 0, 16); 
}

typedef struct intf_nw_props_{
	/*l2 properties */
	mac_add_t mac_add; /*MAC are hard brunt in interface Network Interface Card(NIC)*/
	
	/*l3 properties */
	bool_t is_ipadd_config; /*Set to TRUE if ip add is configured, intf operates in L3 mode if ip address is configured on it */ 
	ip_add_t ip_add;
	char mask; 
}intf_nw_props_t;

static inline void init_intf_nw_prop(intf_nw_props_t *intf_nw_props){ //initialize the interface network properties. 
	memset(intf_nw_props->mac_add.mac, 0, 48);
	intf_nw_props->is_ipadd_config = FALSE;
	memset(intf_nw_props->ip_add.ip_addr, 0, 16);
	intf_nw_props->mask =0;
}

void interface_assign_mac_address(interface_t *interface);

#define IF_MAC(intf_ptr) ((intf_ptr)->intf_nw_props.mac_add.mac) //interface mac address macro
#define IF_IP(intf_ptr)  ((intf_ptr)->intf_nw_props.ip_add.ip_addr) //interface ip address macro

#define NODE_LO_ADDR(node_ptr) (node_ptr->node_nw_prop.lb_addr.ip_addr) //loopback
#define IS_INTF_L3_MODE(intf_ptr) (intf_ptr->node_nw_prop.is_lb_addr_config) 


/* APIs to set Network Node Properties */
bool_t node_set_loopback_address(node_t *node, char *ip_addr);
bool_t node_set_intf_ip_address(node_t *node, char *local_if, char *ip_addr, char mask); 
bool_t node_unset_intf_ip_address(node_t *node, char *local_if); 

#endif /**NET_H**/
