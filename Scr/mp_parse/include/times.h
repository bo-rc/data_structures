#ifndef TIMES_H
#define TIMES_H
#include "binary_op.h"

namespace cs225 {
class times : public binary_op
{
public:
    using binary_op::binary_op;
    double combine(double left, double right) const override;
};
}
#endif // TIMES_H

