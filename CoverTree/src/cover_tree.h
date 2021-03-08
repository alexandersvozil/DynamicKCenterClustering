# ifndef _COVER_TREE_H
# define _COVER_TREE_H

#include <numeric>
#include <unordered_set>
#include <assert.h>
#include <queue>
#include <math.h>
#include <set>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <atomic>
#include <unordered_map>
#include <fstream>
#include <stack>
#include <shared_mutex>
#include <iomanip>
#include <random>

#include "cover_tree_node.h"
#include "updates.h"
#include "cover_tree_node.h"
#include "parameter_defs.h"
#include "updates.h"

class CoverTree
{
	public:
		//std::map<int,unsigned> level_count;
		coordType base;
		coordType exp;
		CoverTree(CoverTree&& other)
		{
			root=other.root;
			N = 0;
			base = other.base;
			exp = other.exp;
			powdict = other.powdict;
//			upper_bound = other.upper_bound;
//			lower_bound = other.lower_bound;
			k = other.k;
		}

		CoverTree(const CoverTree& other)
		{
			root=other.root;
			N = 0;
			base = other.base;
			exp = other.exp;
			powdict = other.powdict;
//			upper_bound = other.upper_bound;
//			lower_bound = other.lower_bound;
			k = other.k;
		}

		CoverTree(int cur_p, int m, coordType eps, uint k);
		//CoverTree(int cur_p, int m, coordType eps, coordType lower_bound, coordType upper_bound, uint k);

		update_response update(Update &u);

		/*** Destructor: deallocating all memories by a post order traversal ***/
		~CoverTree();

		/*** Insert point p into the cover tree ***/
		bool insert_simplified(const pointType& p, uint);
		bool insert_lazy(std::vector<Node*>& curQ, const pointType &p, uint id, uint comparison_bound);
		bool insert_fast(Node * current, const pointType &p, uint id, Node* n_parent );

		/*** Remove point p into the cover tree ***/
		bool remove(const pointType& p, uint);

		/*** k-Center ***/
		update_response k_center_val();
		//std::vector<uint> k_center_sol(unsigned int k);

	protected:
		std::vector<coordType> powdict;
		std::unordered_map <uint,Node*> nodeid_map;
		Node* root;                         // Root of the tree
//		coordType upper_bound;
		coordType lower_bound;
		unsigned int N;            // Number of points in the cover tree
		uint k;

		void check_deleted(uint index);

		coordType covdist(int _level);
		std::vector<coordType> compute_pow_table(coordType exp, coordType m);
		bool insert_simplified(std::vector<Node*>& current, const pointType& p, uint id);
		bool insert_iter(std::vector<Node*>& curQ, const pointType& p, uint id);
		bool insert_simplified(Node* current, const pointType& p, uint id, int curlevel);
		bool delete_node(uint id, const pointType& p);
		bool delete_node_rec(uint id, const pointType &p, std::vector<std::vector<Node*>>& all_levels, int curlevel);
};
#endif //_COVER_TREE_H
