#include "cover_tree_node.h"
Node::Node(const pointType& p, unsigned int id, int level, Node *parent){
//	std::cout << "id: " << id << " level lol :" << level << std::endl;
	assert(level + 1024 >= 0);
	this->parent = parent;
	this->children = std::vector<Node*>();
	this->level = level; //implicit lower bound of the distance between nodes
	this->ID = id;
	this->_p = p;
}



