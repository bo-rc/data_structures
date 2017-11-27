#include <string>
#include <cassert>
#include <stdexcept>
#include "binary_op.h"
#include "plus.h"
#include "minus.h"
#include "times.h"
#include "divide.h"
#include "exponent.h"

namespace cs225 {
binary_op::binary_op(std::unique_ptr<node> left,
                     std::unique_ptr<node> right)
    : left_{std::move(left)}, right_{std::move(right)}
{
    // nothing to do
}

double binary_op::value() const
{
    return combine(left_->value(), right_->value());
}

std::unique_ptr<node> make_binary_op(const std::string& op,
                                     std::unique_ptr<node> left,
                                     std::unique_ptr<node> right)
{
    if(op == "+")
    {
        return std::unique_ptr<plus>{new plus{std::move(left), std::move(right)}};
    }
    else if (op == "-")
    {
        return std::unique_ptr<minus>{new minus{std::move(left), std::move(right)}};
    }
    else if (op == "*")
    {
        return std::unique_ptr<times>{new times{std::move(left), std::move(right)}};
    }
    else if (op == "/")
    {
        return std::unique_ptr<divide>{new divide{std::move(left), std::move(right)}};
    }
    else if (op == "^")
    {
        return std::unique_ptr<exponent>{new exponent{std::move(left), std::move(right)}};
    }
    else
    {
        throw std::runtime_error("operation string does not represent a binary operation");
    }
}
}
