#ifndef UMINUS_H
#define UMINUS_H
#include "unary_op.h"

namespace cs225 {
class uminus : public unary_op
{
public:
    using unary_op::unary_op;
    virtual double compute(double arg) const override;
};
}

#endif // UMINUS_H

