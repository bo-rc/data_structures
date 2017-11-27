/**
 * @file moveonly.cpp
 * @author Chase Geigle
 * @date Summer 2015
 */
#include "moveonly.h"

moveonly::moveonly() : x_{0}
{
    // nothing
}

moveonly::moveonly(uint64_t x) : x_{x}
{
    // nothing
}

uint64_t moveonly::get() const
{
    return x_;
}
