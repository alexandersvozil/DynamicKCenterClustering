# ifndef _PARAMETER_DEFS_H
# define _PARAMETER_DEFS_H

#include "Eigen/Core"
#include "Eigen/Eigen"

typedef Eigen::VectorXd pointType;
typedef double coordType;
typedef pointType::Scalar dtype;

inline unsigned int stoui(const std::string& s)
{
    std::istringstream reader(s);
    unsigned int val = 0;
    reader >> val;
    return val;
}

#endif
