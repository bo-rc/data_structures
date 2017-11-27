#include "unary_op.h"
#include "uplus.h"
#include "uminus.h"
#include <stdexcept>
#include <string>

namespace cs225 {

unary_op::unary_op(std::unique_ptr<node> arg)
    : arg_{std::move(arg)}
{
    //nothing to do
}

double unary_op::value() const
{
    return compute(arg_->value());
}

std::unique_ptr<node> make_unary_op(const std::string& op, std::unique_ptr<node> arg)
{
    if(op == "#")
    {
        return std::unique_ptr<uplus>{new uplus{std::move(arg)}};
    }
    else if (op == "~")
    {
        return std::unique_ptr<uminus>{new uminus{std::move(arg)}};
    }
    else
    {
        throw std::runtime_error("operation string does not represent a unary operation");
    }
}

}
