/**
 * @file maze.cpp
 * Definition of a maze class.
 *
 * @author Chase Geigle
 * @date Summer 2014
 */

#include <random>

#include "tools.h"
#include "maze.h"

namespace cs225
{

std::ostream& operator<<(std::ostream& os, direction dir)
{
    switch (dir)
    {
        case direction::RIGHT:
            return os << "RIGHT";
        case direction::DOWN:
            return os << "DOWN";
        case direction::LEFT:
            return os << "LEFT";
        case direction::UP:
            return os << "UP";
    }
}

maze::maze(uint64_t width, uint64_t height) : width_{width}, height_{height}
{
    std::random_device rd;
    std::mt19937_64 rng{rd()};
    // use rng for your random numbers: it's a functor that returns you
    // random numbers

    /// @todo your code here
}

bool maze::can_travel(uint64_t x, uint64_t y, direction dir) const
{
    /// @todo your code here
    return false;
}

void maze::set_wall(uint64_t x, uint64_t y, direction dir, bool exists)
{
    /// @todo your code here
    /// DON'T THROW EXCEPTIONS FROM THIS FUNCTION
}

std::vector<direction> maze::solve()
{
    /// @todo your code here
}

epng::png maze::draw() const
{
    /// @todo your code here
}

epng::png maze::draw_with_solution()
{
    auto result = draw();

    /// @todo your code here

    return result;
}
}
