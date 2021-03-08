#include <chrono>
#include <iostream>
#include <exception>
#include <ratio>
#include <random>
#include <unordered_set>
#include <limits>
#include <future>
#include <thread>
#include <string>
#include "parameter_defs.h"
#include <boost/algorithm/string.hpp>
#include "data_utils.h"
#include "algorithm.h"

void execute_alg(std::string point_path,int nr_points,std::string update_path, uint k, coordType eps)//, coordType lb, coordType ub)
{
	std::vector<pointType> points = read_points(point_path, nr_points);
	std::vector<Update> updates = parse_updates(update_path, points); 
	std::chrono::steady_clock::time_point ts = std::chrono::steady_clock::now();
	//preprocessing
	Tree_Algorithm alg1(points,updates,k,eps); // lb, ub);
	//do updates
	alg1.run();
	std::chrono::steady_clock::time_point te = std::chrono::steady_clock::now();
	std::chrono::duration<coordType, std::milli> duration = te - ts;
	std::cout << duration.count() << "ms" << std::endl;
}



int main(){

	std::cout << "Random"  << std::endl;
	execute_alg("../../../experiments/datasets/random/random_2M", 200000, "../../../experiments/queries/200000_sliding", 20, 4);//0.00001,2.7 );
	std::cout << "Twitter - 100000 " << std::endl;
	//execute_alg("../../../experiments/datasets/twitter/twitter_nodups.txt", 100000, "../../../queries/100000_insertAll", 20, 0.1);
	execute_alg("../../../experiments/datasets/twitter/twitter_nodups.txt", 200000, "../../../experiments/queries/200000_with_del_0.1", 100, 4);
	execute_alg("../../../experiments/datasets/twitter/twitter_nodups.txt", 200000, "../../../experiments/queries/200000_with_del_0.3", 100, 4);
	execute_alg("../../../experiments/datasets/twitter/twitter_nodups.txt", 200000, "../../../experiments/queries/200000_with_del_0.05", 100, 4);
	////INSERTION ONLY with queries 
	std::cout << "Yfcc - 100000 " << std::endl;
	execute_alg("../../../experiments/datasets/yfcc100/yfcc.csv", 200100, "../../../experiments/queries/200000_with_del_0.1", 100, 4);
}
