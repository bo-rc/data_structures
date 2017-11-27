/**
 * @file quadtree.h
 * quadtree class definition.
 * @date Spring 2008
 * @date Modified Summer 2014
 */

#ifndef QUADTREE_H_
#define QUADTREE_H_

#include <iostream>
#include "epng.h"

namespace cs225
{

/**
 * A tree structure that is used to compress epng::png images.
 */

class quadtree
{
  private:
    /**
     * A simple class representing a single node of a quadtree.
     * You may want to add to this class; in particular, it could
     * probably use a constructor or two...
     */
    class node
    {
      public:
        node() = default;

        node(uint64_t x, uint64_t y, uint64_t w);
        node(uint64_t x, uint64_t y, uint64_t w, const epng::png &img);
        node(uint64_t x, uint64_t y, uint64_t w, const epng::rgba_pixel &pxl);

        // components:
        uint64_t up_left_x; // x coordinate of the upper-left corner of this partition
        uint64_t up_left_y; // y coordinate
        uint64_t width; // size of this partition
        epng::rgba_pixel element; // the pixel stored as this node's "data"

        std::unique_ptr<node> northwest;
        std::unique_ptr<node> northeast;
        std::unique_ptr<node> southwest;
        std::unique_ptr<node> southeast;

    };

  public:
    // *** mp_part1 begins
    quadtree();
    quadtree(const epng::png & 	source, uint64_t resolution);

    // big5
    ~quadtree() = default;
    quadtree(const quadtree& other);
    quadtree(quadtree&& other);
    quadtree& operator=(quadtree other);

    void swap(quadtree& other);

    void build_tree(const epng::png& source, uint64_t resolution);

    const epng::rgba_pixel& operator()(uint64_t x, uint64_t y) const;

    epng::png decompress() const;
    // *** mp_part1 ends

    // *** mp_part2 begins
    void rotate_clockwise();
    void prune (uint32_t tolerance);
    uint64_t pruned_size (uint32_t tolerance) const;
    uint32_t ideal_prune (uint64_t num_leaves) const;
    // *** mp_part2 ends

  private:
    std::unique_ptr<node> root_; // the root of the tree


    // private helpers
    void build_tree(uint64_t x, uint64_t y, uint64_t width, const epng::png& img, std::unique_ptr<node>& subroot);
    void init(std::unique_ptr<node>& subroot);
    void get_avg(epng::rgba_pixel& pxl, std::unique_ptr<node>& subroot);
    void copy_quadtree(std::unique_ptr<node>& this_subroot, const std::unique_ptr<node> &other_subroot);
    const epng::rgba_pixel& get(uint64_t x, uint64_t y, const std::unique_ptr<node>& subroot) const;
    const epng::rgba_pixel& determine(uint64_t x, uint64_t y, const std::unique_ptr<node>& subroot) const;
    void traverse_and_recover(const std::unique_ptr<node>& subroot, epng::png& img) const;

    void rotate_clockwise(std::unique_ptr<node>& subroot);
    void prune(uint32_t t, std::unique_ptr<node>& subroot);
    bool prunable(uint32_t t, const std::unique_ptr<node>& subroot) const;
    uint32_t pxl_diff(const epng::rgba_pixel avg, epng::rgba_pixel pxl) const;

    void count_pxl(const std::unique_ptr<node>& subroot, uint64_t& num) const;
    void pruned_size(const std::unique_ptr<node>& subroot, uint32_t tol, uint64_t& num) const;

    epng::rgba_pixel get_region_color(std::unique_ptr<node>& subroot);

/**** Do not remove this line or copy its contents here! ****/
#include "quadtree_given.h"
};
}
#endif
