#include <stdio.h> 
#include "graph.h"

extern graph_t *build_first_topo();
extern graph_t * build_first_topo();
extern void insert_link_between_two_nodes(node_t *node1, node_t *node2, char *from_if_name, char *to_if_name, unsigned int cost);
extern graph_t * create_new_graph(char *topology_name); 
extern node_t *create_graph_node(graph_t *graph, char *node_name); 

int main(int argc, char **argv){
	graph_t *topo = build_first_topo();
	dump_graph(topo); 
	return 0; 
}
