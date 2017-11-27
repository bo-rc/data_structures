/**
 * @file main.cpp
 * CS 225 lab_lab
 *
 * boliu1@illinois.edu
 * lab_lab
 *
 *
 */

#include "epng.h"    // to use the PNG class

void removeColor()
{
  using namespace epng;
  png image("in.png");  
  for(size_t w = 0; w < image.width(); w++)
    for(size_t h = 0; h < image.height(); h++)
      image(w, h)->green = 0;
  
  image.save("removed.png");
}

int main()
{
    removeColor();
    return 0;
}
