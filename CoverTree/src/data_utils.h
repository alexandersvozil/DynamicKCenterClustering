# ifndef _DATA_UTILS_H
# define _DATA_UTILS_H

#include <fstream>
#include "updates.h"
#include "parameter_defs.h"
#include <boost/algorithm/string.hpp>
#include <vector>
#include <iostream>

std::vector<pointType> read_points(const std::string& instance_path, int nr_of_points)
{
	std::ifstream fin(instance_path);
	if(!fin) throw std::runtime_error("File not found : " + instance_path);
	std::vector<pointType> pointList;
	std::string linebuffer;

	int line_nr = 0;
	while(fin && getline(fin,linebuffer)){
		if(nr_of_points == line_nr) break;
		std::vector<std::string> tokens;
		boost::split(tokens, linebuffer, boost::is_any_of("\t "));
		pointType newPt{2};

		/* doubles  */
		newPt[0]= stod(tokens[1]);
		newPt[1]= stod(tokens[2]);
		pointList.push_back(newPt);
		line_nr++;
	}
	fin.close();
	return pointList;
}



std::vector<Update> parse_updates(const std::string& filepath, std::vector<pointType> &points){

	std::ifstream file; 
	file.open(filepath.c_str()); 

	if (!file) { 
		std::cout << "Error in openening file " <<  filepath; 
		throw std::runtime_error("File not found: "+ filepath); 
	} 

	std::string linebuffer; 
	std::vector<Update> updates;
	while(std::getline(file, linebuffer)) { 
		switch(linebuffer[0]) {
			case 'i':
				{
					//std::cout << linebuffer;
					UpdateType cur_ut {UpdateType::insertion};
					uint index = stoui(linebuffer.substr(1));
					Update u {cur_ut,index,points[index] };
					updates.push_back(u);
				}
				break;
			case 'd':
				{
					UpdateType cur_ut {UpdateType::deletion};
					uint index = stoui(linebuffer.substr(1));
					Update u {cur_ut,index,points[index]};
					updates.push_back(u);
				}
				break;
			case 'q':
				{
					UpdateType cur_ut {UpdateType::query};
					Update u {cur_ut};
					updates.push_back(u);
				}
				break;

			default:
				throw std::runtime_error("Error parsing updates");
				break;
		}
	} 

	file.close();
	return updates;
}

#endif //_data_utils.h
