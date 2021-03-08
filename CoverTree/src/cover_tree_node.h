# ifndef _COVER_TREE_NODE_H
# define _COVER_TREE_NODE_H
#include "parameter_defs.h"
#include <unordered_map>
#include <vector>
#include <iostream>
#include <math.h>


class Node
{
	private:
	public:
		pointType _p;                       // point associated with the node
		std::vector<Node*> children;
		int level;                          // current level of the node
		unsigned int ID;                        // unique ID of current node
		Node* parent;                       // parent of current node
		
		Node(const pointType& p, unsigned int id, int level, Node* parent);
		Node(const pointType& p, unsigned int id, int level, Node* parent, coordType dist_parent);


		inline coordType dist(const pointType& pp) const  // L2 distance between current node and point pp
		{
			//coordType x1 = std::abs(_p[1] - pp[1]);
			//coordType x2 = std::min(std::abs(_p[0]-pp[0]), 360-std::abs(_p[0]-pp[0]));
			////assert(std::sqrt(x1*x1 + x2*x2) > 0 && "Distance is not greater zero");
			//if(std::sqrt(x1*x1 + x2*x2) <= 0){
			//	std::cout << _p[0] << " "<< _p[1] << " and " << pp[0] << " " << pp[1] << std::endl;
			//}
			//assert(std::sqrt(x1*x1 + x2*x2) > 0);
			//return std::sqrt(x1*x1 + x2*x2);
			return (_p-pp).norm();
		}
		inline coordType dist(Node* n) const              // L2 distance between current node and node n
		{
			//pointType pp = n->_p;
			//coordType dist = this->dist(pp);
			//assert(dist > 0 && "Distance is not greater zero");
			//return dist;
			return (_p-n->_p).norm();//dist;
		}
		inline Node* setChild(const pointType& pIns, uint new_id)
		{
			Node* temp = new Node(pIns,new_id,this->level-1, this);
			children.push_back(temp);
			return temp;
		}
		inline void setChild(Node* n) {
			Node *parent = this;
			parent->children.push_back(n);
			n->parent = parent;
		}


};

#endif //_COVER_TREE_NODE_H
