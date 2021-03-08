# ifndef _UPDATES_H
# define _UPDATES_H

#include "parameter_defs.h"

enum class UpdateType {insertion, deletion, query};

struct Update
{
	UpdateType type;	
	unsigned int index;
	pointType p;
	Update(UpdateType _u)
	{
		assert(_u == UpdateType::query);

		if(_u == UpdateType::query){
			type = _u; 
		}else{
			throw  std::runtime_error("update type is not correct");
		}
	}
	Update(UpdateType _u, uint _index, pointType _p): type{_u}, index{_index}, p {_p} 
	{
		assert(_u == UpdateType::insertion || _u == UpdateType::deletion );
	}
};

struct update_response
{
	bool success;
	coordType value;
	std::vector<int> solution;
	update_response(bool _result): success {_result}
	{
		value = 0;
	}

	update_response(coordType _value, std::vector<int>& _solution): value {_value}
	{
		assert(_value >= 0);
		assert(value >= 0);
		std::swap(solution,_solution);
	}
};


#endif //_UPDATES_H
