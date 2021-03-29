#include "cover_tree.h"
#include <algorithm>

CoverTree::CoverTree(int _cur_p, int _m, coordType eps, uint _k)
{
	root = NULL;
	N = 0;
	base =  1+(1/eps);
	//exp = (((coordType)_cur_p)/(coordType)_m)-1.0f;
	exp = (((coordType)_cur_p)/(coordType)_m)-1.0;
	powdict = compute_pow_table(base, exp);
	assert(base > 1);

	this->k = _k;
	srand((unsigned int) time(NULL));	
	lower_bound = 0;

}

std::vector<coordType> CoverTree::compute_pow_table(coordType base, coordType exp){
	std::vector<coordType> powdict;
	for (size_t i = 0; i < 2048; i++) {
		//powdict[i] = std::pow(base,exp+(coordType)i-1024.0f);	
		powdict.push_back(std::pow(base,exp+(coordType)i-1024.0));	
	}
	return powdict;
}

coordType CoverTree::covdist(int _level) // covering distance of subtree at current node
{
	assert(base > 1);
	assert(_level + 1024 <= 2048);
	assert(_level + 1024 >= 0);
	return powdict[_level+1024];//std::pow(base,exp+_level);//
} 

/******************************* Insert_simplified ***********************************************/
bool CoverTree::insert_simplified(const pointType& p,uint id)
{
	//std::cout << "inserting " << p[0] << " " << p[1] << " " << id << std::endl;
	if (root == NULL)
	{
		N++;
		int ublevel = 0;
		root = new Node(p,id, ublevel, NULL);
		return true;
	}
	
//(base/(base-1.0))*covdist(root->level);
	if(root->dist(p) > covdist(root->level)/(base-1.0)){
		//std::cout << "new root " << id << std::endl;
		N++;
		//root->parent = n;
		//n->children.push_back(root);
		//root = n;
		//successor_dist= ;//(base/(base-1.0))*covdist(n->level);
		while(root->dist(p) > covdist(root->level)/(base-1.0)){
			Node * n = new Node(root->_p,root->ID,root->level+1,NULL);
			n->children.push_back(root);
			root->parent = n;
			root = n;
			//std::cout << "root level new: "  << n->level << std::endl;
		}
		Node* newRoot = new Node(p,id, root->level+1, NULL);
		root->parent = newRoot;
		newRoot->children.push_back(root);
		//std::cout << "root level new: "  << newRoot->level << std::endl;
		root = newRoot;
		return true;
	}

	assert(root!=NULL);
	//assert that the inserted node can be a successor of the root
	//assert(root->dist(p) <= (base/(base-1.0))*covdist(root->level));
	std::vector<Node*> Q = {root};
	return insert_iter(Q,p,id);
}



bool CoverTree::insert_iter(std::vector<Node*>& curQ, const pointType& p, uint id)
{
	Node* n_parent = NULL;
	std::vector<Node*> nextQ;
	while (true)
	{
		coordType d_p_Q = std::numeric_limits<coordType>::max();
		int current_level = 0;

		for (Node* current: curQ){
			current_level = current->level;
			coordType explore_dist = covdist(current->level)/(base-1.0);

			if(current->children.empty()){
				current->children.push_back(new Node(current->_p,current->ID,current->level-1,current));
			}
			for (size_t i = 0; i < current->children.size(); ++i)
			{
				Node* child = current->children[i];
				coordType child_dist = child->dist(p);
				d_p_Q = std::min(d_p_Q,child_dist);

				if(child_dist <= explore_dist) {
					nextQ.push_back(child);
				}
			}
		}
		if(nextQ.empty() && d_p_Q > covdist(current_level))
		{
			break;
		} else{
			for(Node* cur : curQ) {
				coordType parent_dist = cur->dist(p);
				if(parent_dist <= covdist(current_level))	{
					n_parent = cur;
					break;
				}
			}
			curQ.swap(nextQ);
			nextQ.clear();
		}
	}
	N++;
	assert(n_parent != NULL);
	n_parent->setChild(p,id);
	//std::cout << "inserted " << id << std::endl;
	return true;
}

bool CoverTree::delete_node(uint id, const pointType& p ){
	//std::cout << "deleting:" <<  id << " " << p[0] << " " << p[1]  << std::endl;	
	N--;
	assert(root != NULL);
	std::vector<std::vector<Node*>> n;
	//std::cout << "ROOT : " << root->ID << "root level: " << root->level << std::endl;
	n.push_back(std::vector<Node*> {this->root});
	return delete_node_rec(id,p,n,root->level);
}

bool CoverTree::delete_node_rec(uint id, const pointType &p, std::vector<std::vector<Node*>>& all_levels, int curlevel){
	std::vector<Node*> nextQ;
	Node *toDelete = NULL;
	//	int toDelete_idx = 0;
	//	int j=0;
	size_t curSize = all_levels.size()-1;
	//explore current level of search for point, remember we need to go down to bottom because we
	//have copies of the node 

	//std::cout << "checking all_level_back " << "\n";
	all_levels.back().erase(std::remove_if(all_levels.back().begin(), all_levels.back().end(), 
				[&](Node * n) { 
				coordType explore_upper = covdist(n->level)/(base-1);
				//std::cout << "children size of" << n->ID << " is: " <<  n->children.size() << "\n";
				for (size_t i = 0; i < n->children.size(); ++i)
				{
				assert(n->children[i] != NULL);
				Node* child = n->children[i];
				//std::cout << "children " << child->ID << "\n";
				coordType dist_child = child->dist(p);
				//if it is smaller than the explore distance, put it into nextQ
				if (dist_child <= explore_upper)
				{
					//std::cout << "pushing back" << child->ID <<  "\n";
				nextQ.push_back(child);                                    			
				}                                                              			
				}                                                                  			
				if (n->ID == id){
				toDelete = n;
				assert(n->ID == id);
				//std::cout << "found" << n->ID << " equal to " << id << "from level " << n->level << "\n";
				return true;
				}
				return false;
				}),all_levels.back().end());
	//std::cout << "recursing on nextQ " << "\n";
	if(!nextQ.empty()) {
		all_levels.push_back(nextQ);
		delete_node_rec(id,p,all_levels, curlevel-1);
	}

	//std::cout << "coming up from recursion" << std::endl;
	if(toDelete != NULL){
		//remove toDelete from parent if toDelete is not the root
		Node* parent = toDelete->parent;
		if(parent != NULL){
			//std::cout << "fixing parent: with ID: " <<  parent->ID << std::endl;
			//TODO:we could get rid of this loop
			for(size_t i = 0; i<parent->children.size(); i++){
				if (parent->children[i]->ID == toDelete->ID){
					parent->children.erase(parent->children.begin()+i);
					break;
				}
			}
		}

		//std::cout << "fixing children, there are " << toDelete->children.size() << " of them " << std::endl;
		bool new_root = false;
		if(parent == NULL){
			root = NULL;
			new_root = true;
			//std::cout << " NEW ROOT \n" << toDelete->ID << " level: " << toDelete->level;
		}

		for(Node* oldChild : toDelete->children){
			int newlevel = curlevel; 
			Node* curChild = oldChild;

			//	std::cout << "currently fixing child ID: " << curChild->ID << std::endl;
			//	std::cout << "curSize " << curSize << std::endl;
			//	  std::cout << "all_level[curSize].size(): " << all_levels[curSize].size() << std::endl;
			//for (auto vec : all_levels){
			//std::cout << vec.size() << std::endl;
			//}
			//as long as we can lift curChild, do it.
			size_t i = curSize+1;
			while(i-- > 0){
				bool can_lift = true;
				//std::cout << "checking in level "<< i << " for replacement" << std::endl;
				for(Node* n : all_levels[i]) {
					//std::cout << "checking distance to: " << n->ID << std::endl;
					if(n->dist(curChild) <= covdist(newlevel)){
						//found parent
						assert(newlevel == curChild->level+1);
						//std::cout << "we can set new parent for " << curChild->ID << " it is " << n->ID << std::endl;
						//std::cout << "i was " << i << std::endl;
						//std::cout << n->level << " " << curChild->level << std::endl;
						assert(n->level==curChild->level+1);
						n->setChild(curChild);
						can_lift =false;
						break;
					}
				}

				if(can_lift){
					//std::cout << " trying to lift to arrayposition: " << i << std::endl;
					Node* curChild_lifted = new Node(curChild->_p,curChild->ID,curChild->level+1,NULL);
					curChild_lifted->setChild(curChild);
					curChild = curChild_lifted;
					all_levels[i].push_back(curChild);
					//std::cout << "lifting: " << curChild->ID << " to level " << curChild->level<< std::endl;
					newlevel++;
				}else{
					break;
				}
			}
			//std::cout << "root level: " << root->level << " curchild->level: " << curChild->level << std::endl;
		}
		if(new_root){
			//	std::cout << "we have a new root" << std::endl;
			//	assert(root->ID == toDelete->ID);
			for(auto vec : all_levels){
				if (vec.size() > 0){
					//std::cout << all_levels[0].size() << "\n";
					assert(all_levels[0].size() == 1);
					//	if(root->ID != toDelete->ID){
					//			throw std::runtime_error("two new roots in one delete"); 
					//	}
					//std::cout << " NEW ROOT: " << vec.back()->ID <<  "\n";
					root = vec.back(); 
					break;
				}
			}
		}
		assert(root != NULL || N == 0);
		//std::cout << "sucessfully deleted: " << toDelete->ID  << " at level " << toDelete->level<< std::endl;
		delete toDelete;
	}
	return true;
}

update_response CoverTree::k_center_val() {
	//std::cout << "N: " << this->N << " \n";
	if(this->N==0){
		std::vector<int> ret_v; 
		return update_response(0.0,ret_v);
	}
	std::queue<Node*> travel;
	std::unordered_set<uint> check;
	uint sol_missing = std::min(this->k,this->N);	
	Node* curNode = NULL;
	int current_level = root->level;
	travel.push(root);
	while(sol_missing > 0 && travel.size() > 0) {
		curNode = travel.front();
		assert(curNode != NULL);
		travel.pop();
		if(check.find(curNode->ID) == check.end()){
			sol_missing--;
			check.insert(curNode->ID);
			//std::cout << "inserting: " << curNode->ID << std::endl;
		}
		for (const auto& child : curNode->children){

			travel.push(child);
		}
		if(travel.size() > 0){
			Node* nextNode = travel.front();
			if(nextNode->level < curNode->level){
				current_level = curNode->level;
			}
		}else{
			current_level = curNode->level;
		}
	}


	assert(curNode != NULL);

	while(travel.size() > 0 && check.find(travel.front()->ID) != check.end()) {
		if(travel.size() > 0){
			Node* nextNode = travel.front();
			if(nextNode->level < curNode->level){
				current_level = curNode->level;
			}
		}else{
			current_level = curNode->level;
		}
		travel.pop();
	}
	coordType result = base/(base-1)* std::pow(base,exp+(coordType)current_level);
	std::vector<int>v_sol (check.begin(),check.end());
	return update_response(result,v_sol);
}	

update_response CoverTree::update(Update &u){
	switch(u.type){
		case UpdateType::insertion:
			{
				update_response result = insert_simplified(u.p,u.index);
				return result;
			}
			break;
		case UpdateType::deletion:
			{
				update_response result = delete_node(u.index, u.p);
				return result;
				
			}
			break;
		case UpdateType::query:
			{
				update_response result = k_center_val();
				return result;

			}
			break;
		default:
			throw std::runtime_error("Error while updating");
			break;
	}
	return 0;
}

void CoverTree::check_deleted(uint index)
{

	std::stack<Node*> travel;
	if (root != NULL)
		travel.push(root);
	while (travel.size() > 0)
	{
		Node* current = travel.top();
		if(current->ID  == index) {
			std::cout << current->ID <<  " " << index << " levle: " << current->level << std::endl; 
			std::cout << "parent id: " << current->parent->ID << " dist to parent " << current->dist(current->parent) << " covdist:" << covdist(current->level)<< std::endl;
			while(current->parent != NULL){
				current = current->parent;
				std::cout << current->ID <<  " " << index << " levle: " << current->level << std::endl; 
				if(current->parent != NULL){
					std::cout << "parent id: " << current->parent->ID << " dist to parent " << current->dist(current->parent) << " covdist:" << covdist(current->level)<< std::endl;
				}
			}
			throw std::runtime_error("deleted node in tree");
		}
		travel.pop();

		for(const auto& child: current->children){
			if(child !=NULL){
				travel.push(child);
			}
		}
	}
}  
CoverTree::~CoverTree()
{
	std::stack<Node*> travel;

	if (root != NULL)
		travel.push(root);
	while (travel.size() > 0)
	{
		Node* current = travel.top();
		travel.pop();

		for(const auto& child: current->children){
			if(child !=NULL){
				travel.push(child);
			}
		}
		delete current;
	}
}
