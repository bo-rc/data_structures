#include "terminal.h"

namespace cs225 {

terminal::terminal(double val) : data_{val}
{
    // nothing to do
}

double terminal::value() const
{
    return data_;
}

std::unique_ptr<terminal> make_term(double val)
{
    return std::unique_ptr<terminal>{new terminal{val}};
}

}
