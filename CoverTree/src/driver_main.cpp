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

#include "math.h"
#include "cover_tree.h"
#include "updates.h"
#include "algorithm.h"
#include "data_utils.h"



int main(int argc, char** argv){
	if(argc < 4){
		throw std::runtime_error("Usage: /kcenter <path_to_points> <path_to_updates> k epsilon nr_of_points");
	}

	std::string instance_path {argv[1]};
	std::string updates_path {argv[2]};
	uint k = stoui(argv[3]);
	coordType eps = std::stod(argv[4]);

	int nr_of_points  {std::numeric_limits<int>::max()}; 


	if(argc >= 5){ 
		nr_of_points = std::stoi(argv[5]);
	}

	assert(nr_of_points >= k);


	std::vector<pointType> points = read_points(instance_path, nr_of_points);
	std::vector<Update> updates = parse_updates(updates_path,points); 

	std::chrono::steady_clock::time_point ts = std::chrono::steady_clock::now();
	Tree_Algorithm alg(points,updates,k ,eps);
	alg.run();


	std::chrono::steady_clock::time_point te = std::chrono::steady_clock::now();
	std::chrono::duration<coordType, std::milli> duration = te - ts;
	std::cout << duration.count() << "ms" << std::endl;
}

//DEBUGGING A SOLUTION (this checks if the pairwise distance between points is at least the
//covdist of the least level
//std::cout << "debugging solution for " << base << " and exp " << exp << std::endl;
//for(size_t i = 0; i<solution.size(); i++){
//	for(size_t j = 0; j<solution.size(); j++){
//		if(j==i) continue;
//		if(solution[i]->dist(solution[j]) <= covdist(lastlevel)){
//			std::cout << solution[i]->ID << " " << solution[j]->ID <<  " sepdist: " << covdist(lastlevel) << " dist: " << solution[i]->dist(solution[j]) << " lastlevel: " << lastlevel << " level i: " << solution[i]->level << " level j: " << solution[j]->level << std::endl;
//		}
//		//assert(solution[i]->dist(solution[j]) > covdist(lastlevel));
//	}
//}
//for(uint id: check){
//	std::cout << id << std::endl;
//}
//std::cout << "debugging done" << std::endl;


