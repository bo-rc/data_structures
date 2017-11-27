#ifndef UNARY_OP_H
#define UNARY_OP_H
#include "node.h"
#include <memory>

namespace cs225 {
class unary_op : public node
{
public:
    unary_op(std::unique_ptr<node> arg);
    virtual double value() const override;
    virtual double compute(double val) const = 0;

protected:
    std::unique_ptr<node> arg_;

};
std::unique_ptr<node> make_unary_op(const std::string& op, std::unique_ptr<node> arg);

}
#endif // UNARY_OP_H

