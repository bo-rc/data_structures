#ifndef MAZEREADER_H
#define MAZEREADER_H

#include <cstdint>
#include <vector>
#include "epng.h"
#include "maze.h"

using namespace cs225;

// Avoid students predefined macros messing up our enums
#undef NOWALLS
#undef RIGHTWALL
#undef DOWNWALL
#undef BOTHWALLS
#undef RIGHT
#undef DOWN
#undef LEFT
#undef UP

using namespace std;

class MazeReader
{
  public:
    enum wall_t
    {
        NOWALLS = 0x0,
        RIGHTWALL = 0x1,
        DOWNWALL = 0x2,
        BOTHWALLS = RIGHTWALL | DOWNWALL
    };

  private:
    uint64_t width;
    uint64_t height;
    vector<uint64_t> walls;
    vector<direction> solution;
    uint64_t destination_x;
    uint64_t destination_y;

  public:
    MazeReader(const epng::png& image);
    bool isWall(uint64_t x, uint64_t y, wall_t wall) const
    {
        return (walls[y * height + x] & wall) != 0;
    }
    bool isWallInDir(uint64_t x, uint64_t y, direction dir) const;
    uint64_t getWidth() const
    {
        return width;
    }
    uint64_t getHeight() const
    {
        return height;
    }
    uint64_t getDestinationX() const
    {
        return destination_x;
    }
    uint64_t getDestinationY() const
    {
        return destination_y;
    }
    size_t getSolutionSize() const
    {
        return solution.size();
    }
    direction getSolutionAt(size_t index) const
    {
        return solution[index];
    }
};

#endif
