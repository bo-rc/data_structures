#include "exponent.h"
#include <cmath>

namespace cs225 {
double exponent::combine(double left, double right) const
{
    return std::pow(left, right);
}
}
