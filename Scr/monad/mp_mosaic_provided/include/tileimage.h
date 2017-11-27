/**
 * @file tileimage.h
 * Definition of the tile_image class.
 */

#ifndef TILEIMAGE_H_
#define TILEIMAGE_H_

#include <cstdint>

#include "epng.h"

/**
 * Represents a Tile in the Photomosaic.
 */
class tile_image
{
  private:
    epng::png image_;
    epng::rgba_pixel average_color_;

  public:
    tile_image();
    explicit tile_image(const epng::png& theImage);
    epng::rgba_pixel average_color() const;
    uint64_t resolution() const;
    void paste(epng::png& canvas, int start_x, int startY,
               int resolution) const;

  private:
    epng::rgba_pixel calculate_average_color() const;
    epng::rgba_pixel scaled_pixel(double start_x, double endX, double startY,
                                  double endY) const;
    epng::rgba_pixel scaled_pixel(int start_x, int endX, int startY,
                                  int endY) const;
};

#endif // TILEIMAGE_H
