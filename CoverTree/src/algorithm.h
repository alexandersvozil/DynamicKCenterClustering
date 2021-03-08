# ifndef _TREE_ALGORITHM_H
# define _TREE_ALGORITHM_H
#include "cover_tree.h"


class Tree_Algorithm{
	std::vector<pointType> points;
	std::vector<Update> updates;
	std::vector<CoverTree> trees;
	uint k;

	public:
	Tree_Algorithm(std::vector<pointType>& _points, std::vector<Update>& _updates, 	uint _k, coordType eps){
		points.swap(_points);
		updates.swap(_updates);
		this->k = _k;
		trees = create_covertree_instances(eps);
	}
	void run();
	bool run_test(std::vector<coordType>& arr);
	std::vector<CoverTree> create_covertree_instances(coordType eps);
};
#endif
