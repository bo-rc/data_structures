#ifndef MINUS_H
#define MINUS_H
#include "binary_op.h"

namespace cs225 {
class minus : public binary_op
{
public:
    using binary_op::binary_op;
    double combine(double left, double right) const override;
};
}
#endif // MINUS_H

