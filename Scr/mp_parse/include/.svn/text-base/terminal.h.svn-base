#ifndef TERMINAL_H
#define TERMINAL_H
#include "node.h"
#include <memory>

namespace cs225 {
class terminal : public node
{
public:
    virtual double value() const override;
    terminal(double val);

protected:
    double data_;
};

std::unique_ptr<terminal> make_term (double val);
}
#endif // TERMINAL_H

