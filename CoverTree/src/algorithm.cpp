#include "cover_tree.h"
#include "algorithm.h"


void Tree_Algorithm::run(){
	for(Update u : updates){
		
		if(u.type == UpdateType::query){
			coordType sol_val = std::numeric_limits<double>::max();
			std::vector<int> cur_k_centers;

			for(size_t i = 0; i<trees.size(); i++){
				update_response curSol = trees[i].update(u);
				if(curSol.value < sol_val){
					sol_val = curSol.value; 
					cur_k_centers.swap(curSol.solution);
					if (i != 0) break; //optimization to only care for the first one that is better
				}
			}
			assert(cur_k_centers.size() >= 0);

			std::cout << "RESULT: ";
			for (size_t i = 0; i < cur_k_centers.size(); ++i) {
				std::cout << cur_k_centers[i] << " " ;
			}
			std::cout << std::endl;

		}else{
			//#pragma omp parallel for
			for(size_t i = 0; i<trees.size(); i++){
				trees[i].update(u);
			}
		}

	}
}


std::vector<CoverTree> Tree_Algorithm::create_covertree_instances(coordType eps) // coordType lowerB, coordType upperB)
{
	std::vector<CoverTree> trees;
	eps =  (1.0/2)*(std::sqrt(2.0)*std::sqrt(eps+2.0)-2);


	int m = (int)std::ceil((1.0/std::log(1+eps))*std::log(1.0+1.0/eps));
	std::cout << "m: " << m << std::endl;
	for(int p = 1; p <= m; p++) {
			CoverTree cTree{p,m,eps,this->k};
			trees.push_back(cTree);
	}

	return trees;
}


