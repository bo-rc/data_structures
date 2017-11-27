#ifndef UPLUS_H
#define UPLUS_H
#include "unary_op.h"

namespace cs225 {
class uplus : public unary_op
{
public:
    using unary_op::unary_op;
    virtual double compute(double arg) const override;
};
}

#endif // UPLUS_H

