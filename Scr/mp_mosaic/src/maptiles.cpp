/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>

#include "maptiles.h"

mosaic_canvas map_tiles(const source_image& source,
                        const std::vector<tile_image>& tiles)
{
    /**
     * @todo Implement this function!
     */

    if (source.rows() == 0 || tiles.size() == 0)
        throw std::runtime_error("empty source image or tile images");

    // 1. construct canvas according to source
    auto rows = source.rows();
    auto columns = source.columns();
    mosaic_canvas canvas(rows, columns);

    // 2. build a kd_tree storing tile images, organized according
    //    to their average colors
    // 2.1 build vector<point<3>> from vector<tile_image>
    auto tiles_size = tiles.size();
    std::vector<point<3>> points;
    points.reserve(tiles_size);

    // 2.2 build map: point -> tile_image
    std::map<point<3>, typename std::vector<tile_image>::size_type> point_to_tileImg;

    for (typename std::vector<tile_image>::size_type i = 0; i < tiles.size(); ++i)
    {
        // derive average_color to represent tile image
        auto color = tiles[i].average_color();

        // construct averagec_color points to vector<point<3>>
        point<3> point {color.red, color.green, color.blue};

        // 2.1
        points.push_back(point);

        // 2.2
        point_to_tileImg[point] = i;
    }

    // 2.3 build kd_tree
    kd_tree<3> tile_tree(points);


    // 3. build canvas:
    // 3.1 read region avg color
    // 3.2 find point in kd_tree
    // 3.3 find tile in vector<tile_image>
    // 3.4 canvas.set_tile

    for (auto w = 0; w < columns; ++w)
        for (auto h = 0; h < rows; ++h)
        {
            auto avg_color = source.region_color(h, w);
            point<3> avg_color_point {avg_color.red, avg_color.green, avg_color.blue};

            auto point_kd_tree = tile_tree.find_nearest_neighbor(avg_color_point);

            auto i = point_to_tileImg[point_kd_tree];

            const auto& img = tiles[i];
            canvas.set_tile(h, w, img);
        }

    return canvas;
}
