#include "mazereader.h"

MazeReader::MazeReader(const epng::png& image)
    : width((image.width() - 1) / 10),
      height((image.height() - 1) / 10),
      walls(width * height)
{
    epng::rgba_pixel black(0, 0, 0);
    for (uint64_t y = 0; y < height; y++)
    {
        for (uint64_t x = 0; x < width; x++)
        {
            if (*image(x * 10 + 10, y * 10 + 5) == black)
                walls[y * height + x] |= RIGHTWALL;
            if (*image(x * 10 + 5, y * 10 + 10) == black)
                walls[y * height + x] |= DOWNWALL;
        }
    }

    uint64_t x = 0;
    uint64_t y = 0;
    epng::rgba_pixel red(255, 0, 0);
    while (true)
    {
        if (*image(x * 10 + 6, y * 10 + 5) == red &&
            (solution.empty() || solution.back() != direction::LEFT))
        {
            solution.push_back(direction::RIGHT);
            x++;
        }
        else if (*image(x * 10 + 5, y * 10 + 6) == red &&
                 (solution.empty() || solution.back() != direction:: UP))
        {
            solution.push_back(direction::DOWN);
            y++;
        }
        else if (*image(x * 10 + 4, y * 10 + 5) == red &&
                 (solution.empty() || solution.back() != direction::RIGHT))
        {
            solution.push_back(direction::LEFT);
            x--;
        }
        else if (*image(x * 10 + 5, y * 10 + 4) == red &&
                 (solution.empty() || solution.back() != direction::DOWN))
        {
            solution.push_back(direction::UP);
            y--;
        }
        else
            break;
    }

    destination_x = x;
    destination_y = y;
}

bool MazeReader::isWallInDir(uint64_t x, uint64_t y, direction dir) const
{
    if (dir == direction::LEFT)
    {
        x--;
        dir = direction::RIGHT;
    }
    if (dir == direction::UP)
    {
        y--;
        dir = direction::DOWN;
    }
    if (x >= width || y >= height)
        return true;
    wall_t wall = (dir == direction::RIGHT) ? RIGHTWALL : DOWNWALL;
    return isWall(x, y, wall);
}
